#define DEFINITIONS
#define COGCHEF_RETURN(_type) void

#ifdef COGCHEF_DEFINITIONS

/*#! #include <stddef.h> */
/*#! #include <stdbool.h> */

#define COGCHEF_STRUCT_private(_type)                                         \
    struct _type {
#define COGCHEF_FIELD(_name, _type, _default_value)                           \
        _type _name;
#define COGCHEF_FIELD_STRUCT_PTR(_name, _type, _decor)                        \
        struct _type _decor _name;
#define COGCHEF_FIELD_PTR(_name, _type, _decor)                               \
        _type _decor _name;
#define COGCHEF_FIELD_CUSTOM(_name, _key, _type, _decor, _func,               \
                             _default_value)                                  \
        _type _decor _name;
#define COGCHEF_FIELD_PRINTF(_name, _type, printf_type, _scanf_type)          \
        _type _name;
#define COGCHEF_FIELD_ENUM(_name, _type)                                      \
        enum _type _name;
#define COGCHEF_STRUCT_END                                                    \
    };

#define COGCHEF_LIST_private(_type)                                           \
    struct _type {                                                            \
        int size;
#define COGCHEF_LISTTYPE(_type)                                               \
        _type *array;
#define COGCHEF_LISTTYPE_STRUCT(_type)                                        \
        struct _type *array;
#define COGCHEF_LISTTYPE_PTR(_type, _decor)                                   \
        _type * _decor array;
#define COGCHEF_LIST_END                                                      \
        /** @private */                                                       \
        int realsize;                                                         \
    };
#define COGCHEF_LIST_public(_type) COGCHEF_LIST_private(_type)

#define COGCHEF_ENUM(_name)                                                   \
    enum _name {
#define COGCHEF_ENUMERATOR(_enumerator, _value)                               \
        _enumerator _value,
#define COGCHEF_ENUMERATOR_LAST(_enumerator, _value)                          \
        _enumerator _value
#define COGCHEF_ENUM_END                                                      \
    };

#define COGCHEF_STRUCT_public(_type) COGCHEF_STRUCT_private(_type)
#define COGCHEF_LIST_public(_type) COGCHEF_LIST_private(_type)

#include "cogchef-assemble.ACTION.h"

#endif /* COGCHEF_DEFINITIONS */

#undef DEFINITIONS
#undef COGCHEF_RETURN
