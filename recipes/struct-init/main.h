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
#define COGCHEF_FIELD_CUSTOM(_name, _type, _decor, _func, _default_value)     \
        self->_name = _default_value;
#define COGCHEF_FIELD_PRINTF(_name, _type, printf_type, _scanf_type)          \
        self->_name = (_type)0;
#define COGCHEF_STRUCT_END                                                    \
    }
#define COGCHEF_STRUCT_private static COGCHEF_STRUCT_public

#include "cogchef-assemble.ACTION.h"

#define COGCHEF_STRUCT_public(_type)                                          \
    void _type##_cleanup(struct _type *self)                                  \
    {
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
#define COGCHEF_STRUCT_private static COGCHEF_STRUCT_public

#define COGCHEF_LIST_public(_type)                                            \
    void _type##_cleanup(struct _type *self)                                  \
    {                                                                         \
        while (--self->size >= 0)
#define COGCHEF_ELEMENT_STRUCT(_type)                                         \
            _type##_cleanup(self->array[self->size]);
#define COGCHEF_ELEMENT_PTR(_type, _decor)                                    \
            free(self->array[self->size]);
#define COGCHEF_LIST_END                                                      \
        free(self->array);                                                    \
    }
#define COGCHEF_LIST_private static COGCHEF_LIST_public

#include "cogchef-assemble.ACTION.h"

#endif /* COGCHEF_HEADER */
#endif /* COGCHEF_STRUCT_INIT */

#undef STRUCT_INIT
#undef COGCHEF_RETURN
