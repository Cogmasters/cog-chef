#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char COMMENT_OPEN[] = "/*#!"; /* TODO: custom comment opener */
static const char COMMENT_CLOSE[] = "*/";

#define MAX_SZBUF(sizeof_a, sizeof_b)                                         \
    ((sizeof_a > sizeof_b) ? sizeof_a : sizeof_b)

int
main(void)
{
    char buf[MAX_SZBUF(sizeof(COMMENT_OPEN), sizeof(COMMENT_CLOSE))];
    unsigned open_comment = 0;
    size_t szbuf;
    int c;

    while ((buf[0] = c = fgetc(stdin)) != EOF) {
        if (COMMENT_OPEN[0] == buf[0]) {
            if (!fgets(buf + 1, sizeof(COMMENT_OPEN) - 1, stdin)) break;

            if (!open_comment
                && 0 == memcmp(buf, COMMENT_OPEN, sizeof(COMMENT_OPEN) - 1)) {
                open_comment = 1;
                continue;
            }
            szbuf = sizeof(COMMENT_OPEN) - 1;
        }
        else if (COMMENT_CLOSE[0] == buf[0]) {
            if (!fgets(buf + 1, sizeof(COMMENT_CLOSE) - 1, stdin)) break;

            if (open_comment
                && 0 == memcmp(buf, COMMENT_CLOSE, sizeof(COMMENT_CLOSE) - 1))
            {
                open_comment = 0;
                continue;
            }
            szbuf = sizeof(COMMENT_CLOSE) - 1;
        }
        else {
            szbuf = 1;
        }

        /* check individual special characters */
        switch (buf[0]) {
#if 0
        case '*':
            if (open_comment) continue; /* TODO: must be first character */
        /* fall-through */
        case '\\': /* TODO: save 'escape' state */
        case '"': /* TODO: consume entire string */
        case '\n': /* TODO: save newline state */
#endif
        default:
            fwrite(buf, szbuf, 1, stdout);
            break;
        }
    }

    return EXIT_SUCCESS;
}
