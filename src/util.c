#include "util.h"

#include <stdio.h>
#include <stdarg.h>

void cdo_pipe(const char* fmt, ...) {
    va_list args; 
    va_start(args, fmt);

    vfprintf(stdout, fmt, args);

    va_end(args);
}

void cdo_pipe_token(lab_lexer_token_t* tok) {

    if(tok->data==NULL) {
        cdo_pipe("%c%c%c%c%s", tok->id, tok->id + 1, tok->id + 2, tok->id + 3, "\n");
    } else {
        cdo_pipe("%c%c%c%c%s%s", tok->id, tok->id + 1, tok->id + 2, tok->id + 3, tok->data, "\n");
    }

}