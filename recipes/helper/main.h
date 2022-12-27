#define HELPER

#ifdef COGCHEF_HELPER
#ifdef COGCHEF_HEADER

/*#! #include "utils/tablec.h" */

enum cogchef_modes { COGCHEF_MODES_WRITE, COGCHEF_MODES_READONLY };

enum cogchef_types {
    COGCHEF_TYPES__char,
    COGCHEF_TYPES__short,
    COGCHEF_TYPES__int,
    COGCHEF_TYPES__long,
    COGCHEF_TYPES__float,
    COGCHEF_TYPES__double,
    COGCHEF_TYPES__bool,
    COGCHEF_TYPES__struct,
    COGCHEF_TYPES__EXTEND
};

/* forward definition */
struct cogchef;
/**/

typedef struct cogchef *(*const cogchef_from_type_t)(void *, enum cogchef_modes, struct cogchef *);

struct cogchef_field {
    const unsigned ptr_depth;
    const size_t size;
    const struct {
        const size_t len;
        const char *const buf;
    } name;
    const enum cogchef_types type;
    cogchef_from_type_t init;
    void *value;
};

struct cogchef {
    size_t size;
    size_t nfields;
    struct tablec_ht fields;
    enum cogchef_modes mode;
};

/*#!
#define cogchef_get(cogchef, key) (*(void **)tablec_get(&cogchef->fields, key))
#define cogchef_set(cogchef, key, value) ((cogchef->mode & COGCHEF_MODES_WRITE) ? tablec_set(&cogchef->fields, key, value) : (abort(), NULL))
*/

#define COGCHEF_STRUCT_public(_type)                                          \
    struct cogchef *cogchef_from_##_type(struct _type *self,                  \
                                         enum cogchef_modes mode,             \
                                         struct cogchef *saveptr);

#include "cogchef-assemble.ACTION.h"

#elif defined(COGCHEF_FORWARD)

/*#! #include <stdlib.h> */
/*#! #include <string.h> */

#define COGCHEF_STRUCT_private(_type)                                         \
    static struct cogchef *cogchef_from_##_type(struct _type *self,           \
                                                enum cogchef_modes mode,      \
                                                struct cogchef *saveptr);

#include "cogchef-assemble.ACTION.h"

#define PTR_DEPTH(_decor) #_decor[0] == '*' ? sizeof(#_decor) - 1 : 0

#define COGCHEF_STRUCT_private(_type)                                         \
    static const struct cogchef_field _type##__fields[] = {
#define COGCHEF_FIELD_CUSTOM(_name, _type, _decor, _func, _default_value)     \
        { PTR_DEPTH(_decor), sizeof(_type _decor),                            \
            { sizeof(#_name) - 1, #_name }, COGCHEF_TYPES__##_type, NULL,     \
            NULL },
#define COGCHEF_FIELD_STRUCT_PTR(_name, _type, _decor)                        \
        { PTR_DEPTH(_decor), sizeof(struct _type _decor),                     \
            { sizeof(#_name) - 1, #_name }, COGCHEF_TYPES__struct,            \
            (cogchef_from_type_t)cogchef_from_##_type, NULL },
#define COGCHEF_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)         \
        { 0, sizeof(_type), { sizeof(#_name) - 1, #_name },                   \
            COGCHEF_TYPES__##_type, NULL, NULL },
#define COGCHEF_FIELD_ENUM(_name, _type)                                      \
        { 0, sizeof(enum _type), { sizeof(#_name) - 1, #_name },              \
            COGCHEF_TYPES__int, NULL, NULL },
#define COGCHEF_STRUCT_END                                                    \
    };
#define COGCHEF_STRUCT_public COGCHEF_STRUCT_private

#include "cogchef-assemble.ACTION.h"

#else

#define COGCHEF_STRUCT_public(_type)                                          \
    struct cogchef *                                                          \
    cogchef_from_##_type(                                                     \
        struct _type *self, enum cogchef_modes mode, struct cogchef *saveptr) \
    {                                                                         \
        struct cogchef_field *fields;                                         \
        if (!saveptr && !(saveptr = malloc(sizeof *saveptr))) return NULL;    \
        saveptr->size = sizeof *self;                                         \
        saveptr->nfields = sizeof(_type##__fields) / sizeof *_type##__fields; \
        fields = malloc(sizeof(_type##__fields));                             \
        memcpy(fields, _type##__fields, sizeof(_type##__fields));             \
        tablec_init(&saveptr->fields, saveptr->nfields);
#define COGCHEF_FIELD_CUSTOM(_name, _type, _decor, _func, _default_value)     \
        tablec_set(&saveptr->fields, #_name, (fields->value = &self->_name)); \
        ++fields;
#define COGCHEF_STRUCT_END                                                    \
        saveptr->mode = mode;                                                 \
        return saveptr;                                                       \
    }
#define COGCHEF_STRUCT_private static COGCHEF_STRUCT_public

#include "cogchef-assemble.ACTION.h"

#endif /* COGCHEF_HEADER */
#endif /* COGCHEF_HELPER */

#undef HELPER
