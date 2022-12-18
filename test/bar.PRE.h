#ifdef COGCHEF_DEFINITIONS
/*#! #define HELLO 1 */
#endif

STRUCT(private, bar)
    FIELD(boolean, bool, false)
    FIELD(number, int, 0)
    FIELD_PTR(string, char, *)
STRUCT_END

STRUCT(public, baz)
    FIELD_STRUCT_PTR(data, bar, *)
STRUCT_END