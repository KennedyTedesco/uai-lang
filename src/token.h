#ifndef UAI_TOKEN_H
#define UAI_TOKEN_H

#include "stdio.h"

typedef enum {
  T_EOF,
  T_ILLEGAL,
  T_IDENT,
  T_STRING,
  T_NUMBER,
  T_ASSIGN,
  T_PLUS,
  T_MINUS,
  T_ASTERISK,
  T_SLASH,
  T_MODULO,
  T_POWER,
  T_PLUS_PLUS,
  T_MINUS_MINUS,
  T_NOT,
  T_AND,
  T_OR,
  T_COMMA,
  T_SEMICOLON,
  T_COLON,
  T_LPAREN,
  T_RPAREN,
  T_LBRACE,
  T_RBRACE,
  T_LBRACKET,
  T_RBRACKET,
  T_LT,
  T_GT,
  T_EQ,
  T_LT_EQ,
  T_GT_EQ,
  T_NOT_EQ,
  T_FN,
  T_VAR,
  T_TRUE,
  T_FALSE,
  T_IF,
  T_ELSE,
  T_RETURN,
  T_WHILE,
} token_type;

static const char *token_names[] = {
	"EOF",
	"ILLEGAL",
	"IDENT",
	"STRING",
	"NUMBER",
	"=",
	"+",
	"-",
	"*",
	"/",
	"%",
	"**",
	"++",
	"--",
	"!",
	"&&",
	"||",
	",",
	";",
	":",
	"(",
	")",
	"{",
	"}",
	"[",
	"]",
	"<",
	">",
	"==",
	"<=",
	">=",
	"!=",
	"FUNCTION",
	"VAR",
	"TRUE",
	"FALSE",
	"IF",
	"ELSE",
	"RETURN",
	"WHILE",
};

typedef struct keyword_t {
  size_t length;
  token_type type;
  const char *literal;
} keyword_t;

typedef struct token_t {
  size_t length;
  token_type type;
  const char *end;
  const char *start;
  int line;
} token_t;

const char *token_name(token_type type);

#endif
