#define JSON_DECODER
#define COGCHEF_RETURN(_type) _type

#define COGCHEF_int(_f, _js, _var, _type)                                     \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = (int)strtol(_js + _f->v.pos, NULL, 10)
#define COGCHEF_bool(_f, _js, _var, _type)                                    \
    if (_f && _f->type == JSMN_PRIMITIVE)                                     \
        _var = ('t' == _js[_f->v.pos])
#define COGCHEF_PTR_char(_f, _js, _var, _type)                                \
    if (_f && _f->type == JSMN_STRING) {                                      \
        long _ret;                                                            \
        _var = calloc(1, _f->v.len + 1);                                      \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = jsmnf_unescape(_var, _f->v.len, _js + _f->v.pos, _f->v.len);   \
        if (_ret < 0) return _ret;                                            \
        ret += _ret;                                                          \
    }
#define COGCHEF_STRUCT_PTR(_f, _js, _var, _type)                              \
    if (_f && (_f->type == JSMN_OBJECT || _f->type == JSMN_ARRAY)) {          \
        long _ret;                                                            \
        _var = calloc(1, sizeof *_var);                                       \
        if (NULL == _var) return JSMN_ERROR_NOMEM;                            \
        _ret = _type##_from_jsmnf(_f, _js, _var);                             \
        if (_ret < 0) return _ret;                                            \
        ret += sizeof *_var + _ret;                                           \
    }

#ifdef COGCHEF_JSON_DECODER
#ifdef COGCHEF_HEADER

/*#! #define JSMN_STRICT */
/*#! #define JSMN_HEADER */
/*#! #include "jsmn.h" */
/*#! #include "jsmn-find.h" */

#define COGCHEF_STRUCT_public(_type)                                          \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self);                              \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *self);
#define COGCHEF_LIST_public(_type) COGCHEF_STRUCT_public(_type)

#include "cogchef-assemble.ACTION.h"

#elif defined(COGCHEF_FORWARD)
/*#! #include "carray.h" */

#define COGCHEF_STRUCT_private(_type)                                         \
    static long _type##_from_jsmnf(jsmnf_pair *root, const char *js,          \
                                   struct _type *self);
#define COGCHEF_LIST_private(_type) COGCHEF_STRUCT_private(_type)

#include "cogchef-assemble.ACTION.h"

static char *
_cc_strndup(const char *src, size_t len)
{
    char *dest = malloc(len + 1);
    if (!dest) return NULL;
    memcpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}

#else

#define COGCHEF_STRUCT_public(_type)                                          \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self)                               \
    {                                                                         \
        jsmnf_pair *f;                                                        \
        long ret = 0;
#define COGCHEF_STRUCT_private(_type)                                         \
    static COGCHEF_STRUCT_public(_type)
#define COGCHEF_FIELD_CUSTOM(_name, _key, _type, _decor, _decoder,            \
                             _default_value)                                  \
        f = jsmnf_find(root, js, _key, sizeof(_key) - 1);                     \
        _decoder(f, js, self->_name, _type);
#define COGCHEF_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)         \
        f = jsmnf_find(root, js, #_name, sizeof(#_name) - 1);                 \
        if (f) sscanf(js + f->v.pos, _scanf_type, &self->_name);
#define COGCHEF_STRUCT_END                                                    \
        return ret;                                                           \
    }

#define COGCHEF_LIST_public(_type)                                            \
    long _type##_from_jsmnf(jsmnf_pair *root, const char *js,                 \
                            struct _type *self)                               \
    {                                                                         \
        long ret = sizeof *self * root->size;                                 \
        int i;                                                                \
        if (!ret) return 0;
#define COGCHEF_LIST_private(_type)                                           \
    static COGCHEF_LIST_public(_type)
#define COGCHEF_LISTTYPE(_type)                                               \
        __carray_init(self, root->size, _type, , );                           \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            _type o;                                                          \
            COGCHEF_##_type(f, js, o, _type);                                 \
            carray_insert(self, i, o);                                        \
        }

#define COGCHEF_LISTTYPE_STRUCT(_type)                                        \
        __carray_init(self, root->size, struct _type, , );                    \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            struct _type o = { 0 };                                           \
            long _ret = _type##_from_jsmnf(f, js, &o);                        \
            if (_ret < 0) return _ret;                                        \
            ret += _ret;                                                      \
            carray_insert(self, i, o);                                        \
        }
#define COGCHEF_LISTTYPE_PTR(_type, _decor)                                   \
        __carray_init(self, root->size, _type _decor, , );                    \
        for (i = 0; i < root->size; ++i) {                                    \
            jsmnf_pair *f = root->fields + i;                                 \
            _type *o;                                                         \
            COGCHEF_PTR_##_type(f, js, o, _type);                             \
            carray_insert(self, i, o);                                        \
        }
#define COGCHEF_LIST_END                                                      \
        return ret;                                                           \
    }

#include "cogchef-assemble.ACTION.h"

#define COGCHEF_STRUCT_public(_type)                                          \
    size_t _type##_from_json(const char buf[], size_t size,                   \
                             struct _type *self)                              \
    {                                                                         \
        size_t nbytes = 0;                                                    \
        jsmn_parser parser;                                                   \
        jsmntok_t *tokens = NULL;                                             \
        unsigned tmp = 0;                                                     \
        jsmn_init(&parser);                                                   \
        if (0 < jsmn_parse_auto(&parser, buf, size, &tokens, &tmp)) {         \
            jsmnf_loader loader;                                              \
            jsmnf_pair *pairs = NULL;                                         \
            tmp = 0;                                                          \
            jsmnf_init(&loader);                                              \
            if (0 < jsmnf_load_auto(&loader, buf, tokens, parser.toknext,     \
                                    &pairs, &tmp)) {                          \
                long ret;                                                     \
                if (0 < (ret = _type##_from_jsmnf(pairs, buf, self)))         \
                    nbytes = ret;                                             \
                free(pairs);                                                  \
            }                                                                 \
            free(tokens);                                                     \
        }                                                                     \
        return nbytes;                                                        \
    }
#define COGCHEF_LIST_public(_type) COGCHEF_STRUCT_public(_type)

#include "cogchef-assemble.ACTION.h"

#endif /* COGCHEF_HEADER */
#endif /* COGCHEF_JSON_DECODER */

#undef JSON_DECODER
#undef COGCHEF_RETURN

#undef COGCHEF_int
#undef COGCHEF_PTR_char
#undef COGCHEF_bool
#undef COGCHEF_STRUCT_PTR
