#ifndef UAI_LEXER_H
#define UAI_LEXER_H

#include "token.h"

typedef struct {
  const char *start;
  const char *peek;
  const char *current;
  int line;
} Lexer;

Token nextToken(Lexer *lexer);

Lexer newLexer(const char *source);

#endif
