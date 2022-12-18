#ifndef COGCHEF_H
#define COGCHEF_H

#define COGCHEF_STRUCT(_visibility, _name)                                    \
    COGCHEF_STRUCT_ ## _visibility(_name)
#define COGCHEF_LIST(_visibility, _name)                                      \
    COGCHEF_LIST_ ## _visibility(_name)

/* Allow symbols usage without COGCHEF_ prefix */
#ifndef COGCHEF_USE_PREFIX
#   define COND_WRITE COGCHEF_COND_WRITE
#   define COND_END COGCHEF_COND_END

#   define STRUCT COGCHEF_STRUCT
#   define FIELD_CUSTOM COGCHEF_FIELD_CUSTOM
#   define FIELD_PRINTF COGCHEF_FIELD_PRINTF
#   define FIELD COGCHEF_FIELD
#   define FIELD_STRUCT_PTR COGCHEF_FIELD_STRUCT_PTR
#   define FIELD_PTR COGCHEF_FIELD_PTR
#   define FIELD_ENUM COGCHEF_FIELD_ENUM
#   define STRUCT_END COGCHEF_STRUCT_END

#   define LIST COGCHEF_LIST
#   define LISTTYPE COGCHEF_LISTTYPE
#   define LISTTYPE_STRUCT COGCHEF_LISTTYPE_STRUCT
#   define LISTTYPE_PTR COGCHEF_LISTTYPE_PTR
#   define LIST_END COGCHEF_LIST_END

#   define ENUM COGCHEF_ENUM
#   define ENUM_END COGCHEF_ENUM_END
#   define ENUMERATOR COGCHEF_ENUMERATOR
#   define ENUMERATOR_LAST COGCHEF_ENUMERATOR_LAST
#   define ENUMERATOR_END COGCHEF_ENUMERATOR_END
#endif /* COGCHEF_USE_PREFIX */

#endif /* COGCHEF_H */
