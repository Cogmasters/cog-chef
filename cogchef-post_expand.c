#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char COMMENT_OPEN[] = "/*#!";
static const char COMMENT_CLOSE[] = "*/";

enum cogchef_comment_state { COGCHEF_COMMENT_OFF = 0, COGCHEF_COMMENT_ON };

void
expandComments(char *buf, enum cogchef_comment_state state)
{
    while (*buf != '\0') {
        switch (state) {
        case COGCHEF_COMMENT_OFF:
            if (0 != strncmp(buf, COMMENT_OPEN, sizeof(COMMENT_OPEN) - 1))
                break;
            /* make sure directive is on a new line */
            buf[sizeof(COMMENT_OPEN) - 1] = '\n';
            buf += sizeof(COMMENT_OPEN) - 1;
            state = COGCHEF_COMMENT_ON;

            continue;
        case COGCHEF_COMMENT_ON:
            if (0 != strncmp(buf, COMMENT_CLOSE, sizeof(COMMENT_CLOSE) - 1))
                break;

            buf += sizeof(COMMENT_CLOSE) - 1;
            state = COGCHEF_COMMENT_OFF;

            continue;
        }

        fputc(*buf, stdout);
        ++buf;
    }
}

int
main()
{
    enum cogchef_comment_state state = COGCHEF_COMMENT_OFF;
    unsigned count;
    char buf[2048];

    while ((count = fread(buf, sizeof(char), sizeof(buf), stdin))) {
        buf[count - 1] = '\0';
        expandComments(buf, state);
    }

    return EXIT_SUCCESS;
}
