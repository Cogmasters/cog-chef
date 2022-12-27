#include <stdio.h>
#include <stdlib.h>

#include "out.h"

#include "greatest.h"

TEST
check_loop_through(void)
{
    struct bar bar = { true, 10, "hello" }, *p_bar;
    struct baz baz = { 0 };
    struct cogchef *cogchef;

    baz.data = &bar;
    cogchef = cogchef_from_baz(&baz, COGCHEF_MODES_READONLY, NULL);

    ASSERT_EQ(&bar, (p_bar = cogchef_get(cogchef, "data")));

    PASS();
}

SUITE(helper)
{
    RUN_TEST(check_loop_through);
}

GREATEST_MAIN_DEFS();

int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(helper);

    GREATEST_MAIN_END();
}
