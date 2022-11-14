#include "keywords.h"

#include <stdlib.h> /* NULL */
#include <string.h>

struct keyword_lookup {
    char * name;
    enum yf_token_type value;
} keywords[] = {
    { "return", YFT_RETURN },
    { "if", YFT_IF },
    { "else", YFT_ELSE },
    { "true", YFT_LITERAL },
    { "false", YFT_LITERAL },
    { "extc", YFT_EXTC },
    { NULL, YFT_EOF },
};

enum yf_token_type yf_keyword_type(char * str) {

    struct keyword_lookup * k;

    for (k = keywords; k->name; k++) {
        if (strcmp(k->name, str) == 0) {
            return k->value;
        }
    }

    return YFT_INVALID;

}
