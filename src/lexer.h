#ifndef UAI_LEXER_H
#define UAI_LEXER_H

#include "token.h"

typedef struct {
  const char *source;
  const char *start;
  const char *current;
  int line;
} Lexer;

Token nextToken(Lexer *lexer);

Lexer *makeLexer(const char *source);

void freeLexer(Lexer *lexer);

#endif
