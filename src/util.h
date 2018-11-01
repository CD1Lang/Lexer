#pragma once

#include <lexer.h>
#include "tokens.h"

extern void cdo_pipe(const char* fmt, ...);

extern void cdo_pipe_token(lab_lexer_token_t* tok);