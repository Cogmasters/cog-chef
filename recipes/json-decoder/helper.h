#ifndef JSON_DECODER_HELPER
#define JSON_DECODER_HELPER

#define JSMN_STRICT
#define JSMN_HEADER
#include "jsmn.h"
#include "jsmn-find.h"

typedef helper_from_jsmnf_t long (*from_jsmnf)(jsmnf_pair *root,
                                               const char *js,
                                               void *self);

size_t helper_from_json(const char buf[],
                        size_t size,
                        void *self,
                        helper_from_jsmnf_t from_jsmnf);

#endif /* JSON_DECODER_HELPER */
