#define INIT
#define COGCHEF_RETURN(_type) void

#ifdef COGCHEF_STRUCT_INIT
#ifdef COGCHEF_HEADER

#define COGCHEF_STRUCT_public(_type)                                          \
    void _type##_init(struct _type *self);                                    \
    void _type##_cleanup(struct _type *self);
#define COGCHEF_LIST_public(_type)                                            \
    void _type##_cleanup(struct _type *self);

#include "cogchef-assemble.ACTION.h"

#elif defined(COGCHEF_FORWARD)

/*#! #include <stdio.h> */
/*#! #include <stdlib.h> */
/*#! #include <string.h> */
/*#! #include "carray.h" */

#define COGCHEF_STRUCT_private(_type)                                         \
    static void _type##_init(struct _type *self);                             \
    static void _type##_cleanup(struct _type *self);
#define COGCHEF_LIST_private(_type)                                           \
    static void _type##_cleanup(struct _type *self);
#include "cogchef-assemble.ACTION.h"

#else

#define COGCHEF_STRUCT_public(_type)                                          \
    void _type##_init(struct _type *self)                                     \
    {
#define COGCHEF_STRUCT_private(_type)                                         \
    static COGCHEF_STRUCT_public(_type)
#define COGCHEF_FIELD_CUSTOM(_name, _key, _type, _decor, _func,               \
                             _default_value)                                  \
        self->_name = _default_value;
#define COGCHEF_FIELD_PRINTF(_name, _type, printf_type, _scanf_type)          \
        self->_name = (_type)0;
#define COGCHEF_STRUCT_END                                                    \
    }

#include "cogchef-assemble.ACTION.h"

#define COGCHEF_STRUCT_public(_type)                                          \
    void _type##_cleanup(struct _type *self)                                  \
    {
#define COGCHEF_STRUCT_private(_type)                                         \
    static COGCHEF_STRUCT_public(_type)
#define COGCHEF_FIELD(_name, _type, _default_value)
#define COGCHEF_FIELD_STRUCT_PTR(_name, _type, _decor)                        \
        if (self->_name) {                                                    \
            _type##_cleanup(self->_name);                                     \
            free(self->_name);                                                \
        }
#define COGCHEF_FIELD_PTR(_name, _type, _decor)                               \
        if (self->_name) free(self->_name);
#define COGCHEF_STRUCT_END                                                    \
    }

#define COGCHEF_LIST_public(_type)                                            \
    void _type##_cleanup(struct _type *self)                                  \
    {
#define COGCHEF_LIST_private(_type)                                           \
    static COGCHEF_LIST_public(_type)
#define COGCHEF_LISTTYPE(_type)                                               \
        __carray_free(self, _type, NULL, NULL);
#define COGCHEF_LISTTYPE_STRUCT(_type)                                        \
        __carray_free(self, struct _type, NULL,                               \
                      _type##_cleanup(&__CARRAY_OPERAND_A));
#define COGCHEF_LISTTYPE_PTR(_type, _decor)                                   \
        __carray_free(self, _type _decor, NULL, free(__CARRAY_OPERAND_A));
#define COGCHEF_LIST_END                                                      \
    }

#include "cogchef-assemble.ACTION.h"

#endif /* COGCHEF_HEADER */
#endif /* COGCHEF_STRUCT_INIT */

#undef STRUCT_INIT
#undef COGCHEF_RETURN
