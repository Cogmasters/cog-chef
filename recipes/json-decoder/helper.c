#include <stddef.h>>

#include "helper.h"

size_t
helper_from_json(const char buf[],
                 size_t size,
                 void *self,
                 helper_from_jsmnf_t from_jsmnf)
{
    size_t nbytes = 0;
    jsmn_parser parser;
    jsmntok_t *tokens = NULL;
    unsigned tmp = 0;
    jsmn_init(&parser);
    if (0 < jsmn_parse_auto(&parser, buf, size, &tokens, &tmp)) {
        jsmnf_loader loader;
        jsmnf_pair *pairs = NULL;
        tmp = 0;
        jsmnf_init(&loader);
        if (0 < jsmnf_load_auto(&loader, buf, tokens, parser.toknext, &pairs,
                                &tmp)) {
            long ret;
            if (0 < (ret = from_jsmnf(pairs, buf, self))) nbytes = ret;
            free(pairs);
        }
        free(tokens);
    }
    return nbytes;
}
