#ifndef UAI_LEXER_H
#define UAI_LEXER_H

#include "token.h"

typedef struct Lexer {
  char *input;
  const char *start;
  const char *current;
  int line;
} Lexer;

Token *lexer_next_token(Lexer *lexer);
Lexer *lexer_new(const char *input);
void lexer_free(Lexer *lexer);

#endif
