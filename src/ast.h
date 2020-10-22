#ifndef UAI_AST_H
#define UAI_AST_H

#include <stdio.h>
#include "token.h"

typedef enum NODE_TYPE {
  PROGRAM,
  STATEMENT,
  EXPRESSION,
} NODE_TYPE;

typedef enum STATEMENT_TYPE {
  LET_STATEMENT,
  BLOCK_STATEMENT,
  ASSIGN_STATEMENT,
  RETURN_STATEMENT,
  EXPRESSION_STATEMENT,
} STATEMENT_TYPE;

typedef enum EXPRESSION_TYPE {
  BINARY_EXPRESSION,
  CALL_EXPRESSION,
  IDENTIFIER_EXPRESSION,
  IF_EXPRESSION,
  INDEX_EXPRESSION,
  POSTFIX_EXPRESSION,
  UNARY_EXPRESSION,
  WHILE_EXPRESSION,
} EXPRESSION_TYPE;

typedef struct Node {
  enum NODE_TYPE type;
  char *(*token_literal)(void *);
  char *(*to_string)(void *);
} Node;

typedef struct Statement {
  Node node;
  STATEMENT_TYPE type;
} Statement;

typedef struct Expression {
  Node node;
  EXPRESSION_TYPE type;
} Expression;

typedef struct Program {
  Node node;
  Statement **statements;
  size_t total_statements;
  size_t array_size;
} Program;

typedef struct Identifier {
  Expression expression;
  Token *token;
  char *value;
} Identifier;

typedef struct StringLiteral {
  Expression expression;
  Token *token;
  char *value;
  size_t length;
} StringLiteral;

typedef struct BooleanLiteral {
  Expression expression;
  Token *token;
  _Bool *value;
} BooleanLiteral;

typedef struct IntegerLiteral {
  Expression expression;
  Token *token;
  long *value;
} IntegerLiteral;

#endif
