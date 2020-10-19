#ifndef UAI_LEXER_H
#define UAI_LEXER_H

#include "token.h"

typedef struct lexer_t {
  char *input;
  const char *start;
  const char *current;
  int line;
} lexer_t;

token_t lexer_next_token(lexer_t *lexer);
lexer_t *lexer_new(const char *input);
void lexer_free(lexer_t *lexer);

#endif
