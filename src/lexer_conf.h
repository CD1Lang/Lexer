#pragma once

#include <logger.h>
#include <lexer.h>
#include "tokens.h"


extern char* tok_to_string(tokens_e tok);

extern lab_lexer_token_t alpha_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern lab_lexer_token_t whitespace_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern lab_lexer_token_t numeric_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern lab_lexer_token_t symbol_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern lab_lexer_token_t operator_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern lab_lexer_token_t string_callback(const char* code, lab_lexer_iterator_t* iter, size_t max_len, void* user_data);

extern int cdo_lex_string(const char* code, size_t len, lab_lexer_token_container_t* token_container);