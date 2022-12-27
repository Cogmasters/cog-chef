#define BLANK

#ifndef COGCHEF_COND_WRITE
#   define COGCHEF_COND_WRITE(_condition)
#endif
#ifndef COGCHEF_COND_END
#   define COGCHEF_COND_END
#endif

#ifndef COGCHEF_STRUCT_public
#   define COGCHEF_STRUCT_public(_type)
#endif
#ifndef COGCHEF_STRUCT_private
#   define COGCHEF_STRUCT_private(_type)
#endif
#ifndef COGCHEF_FIELD_CUSTOM
#   define COGCHEF_FIELD_CUSTOM(_name, _type, _decor, _func, _default_value)
#endif
#ifndef COGCHEF_FIELD
#   define COGCHEF_FIELD(_name, _type, _default_value)                        \
        COGCHEF_FIELD_CUSTOM(_name, _type, BLANK, COGCHEF_##_type,            \
                             _default_value)
#endif
#ifndef COGCHEF_FIELD_STRUCT_PTR
#   define COGCHEF_FIELD_STRUCT_PTR(_name, _type, _decor)                     \
        COGCHEF_FIELD_CUSTOM(_name, _type, _decor, COGCHEF_STRUCT_PTR, NULL)
#endif
#ifndef COGCHEF_FIELD_PTR
#   define COGCHEF_FIELD_PTR(_name, _type, _decor)                            \
        COGCHEF_FIELD_CUSTOM(_name, _type, _decor, COGCHEF_PTR_##_type, NULL)
#endif
#ifndef COGCHEF_FIELD_PRINTF
#   define COGCHEF_FIELD_PRINTF(_name, _type, _printf_type, _scanf_type)
#endif
#ifndef COGCHEF_FIELD_ENUM
#   define COGCHEF_FIELD_ENUM(_name, _type) COGCHEF_FIELD(_name, int, 0)
#endif
#ifndef COGCHEF_STRUCT_END
#   define COGCHEF_STRUCT_END
#endif

#ifndef COGCHEF_LIST_public
#   define COGCHEF_LIST_public(_type)
#endif
#ifndef COGCHEF_LIST_private
#   define COGCHEF_LIST_private(_type)
#endif
#ifndef COGCHEF_ELEMENT
#   define COGCHEF_ELEMENT(_type)
#endif
#ifndef COGCHEF_ELEMENT_STRUCT
#   define COGCHEF_ELEMENT_STRUCT(_type)
#endif
#ifndef COGCHEF_ELEMENT_PTR
#   define COGCHEF_ELEMENT_PTR(_type, _decor)
#endif
#ifndef COGCHEF_LIST_END
#   define COGCHEF_LIST_END
#endif

#ifndef COGCHEF_ENUM
#   define COGCHEF_ENUM(_name)
#endif
#ifndef COGCHEF_ENUM_END
#   define COGCHEF_ENUM_END
#endif
#ifndef COGCHEF_ENUMERATOR
#   define COGCHEF_ENUMERATOR(_enumerator, _value)
#endif
#ifndef COGCHEF_ENUMERATOR_LAST
#   define COGCHEF_ENUMERATOR_LAST(_enumerator, _value)
#endif
#ifndef COGCHEF_ENUMERATOR_END
#   define COGCHEF_ENUMERATOR_END(_name)
#endif

#include COGCHEF_ENTRY

#undef COGCHEF_COND_WRITE
#undef COGCHEF_COND_END

#undef COGCHEF_STRUCT_public
#undef COGCHEF_STRUCT_private
#undef COGCHEF_FIELD
#undef COGCHEF_FIELD_STRUCT_PTR
#undef COGCHEF_FIELD_PTR
#undef COGCHEF_FIELD_CUSTOM
#undef COGCHEF_FIELD_PRINTF
#undef COGCHEF_FIELD_ENUM
#undef COGCHEF_STRUCT_END

#undef COGCHEF_LIST_public
#undef COGCHEF_LIST_private
#undef COGCHEF_ELEMENT
#undef COGCHEF_ELEMENT_STRUCT
#undef COGCHEF_ELEMENT_PTR
#undef COGCHEF_LIST_END

#undef COGCHEF_ENUM
#undef COGCHEF_ENUM_END
#undef COGCHEF_ENUMERATOR
#undef COGCHEF_ENUMERATOR_LAST
#undef COGCHEF_ENUMERATOR_END
