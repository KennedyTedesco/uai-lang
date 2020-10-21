#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "token.h"
#include "memory.h"

static const keyword_t keywords[] = {
	{2, T_IF, "if"},
	{2, T_FN, "fn"},
	{3, T_VAR, "var"},
	{4, T_TRUE, "true"},
	{5, T_FALSE, "false"},
	{4, T_ELSE, "else"},
	{5, T_WHILE, "while"},
	{6, T_RETURN, "return"},
	{0, T_EOF, NULL}
};

static bool is_end(lexer_t *lexer) {
  return *lexer->current == '\0';
}

static bool is_space(const char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

static bool is_alpha(const char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

static bool is_digit(const char ch) {
  return ch >= '0' && ch <= '9';
}

static char peek(lexer_t *lexer) {
  return *(lexer->current + 1);
}

static void advance(lexer_t *lexer) {
  if (!is_end(lexer)) {
	lexer->current++;
  }
}

static token_type ident_type(lexer_t *lexer) {
  const size_t length = lexer->current - lexer->start;
  for (short i = 0; keywords[i].literal != NULL; i++) {
	if (length == keywords[i].length && strncmp(lexer->start, keywords[i].literal, length) == 0) {
	  return keywords[i].type;
	}
  }
  return T_IDENT;
}

static void read_ident(lexer_t *lexer) {
  while (is_alpha(*lexer->current) || is_digit(*lexer->current)) {
	advance(lexer);
  }
}

static void read_number(lexer_t *lexer) {
  const char *list = ".xXaAbBcCdDeEfF";
  while (is_digit(*lexer->current) || strchr(list, *lexer->current) != NULL) {
	advance(lexer);
  }
}

static void increment_line(lexer_t *lexer, const char ch) {
  lexer->line += ch == '\n' ? 1 : 0;
}

static void read_string(lexer_t *lexer) {
  do {
	advance(lexer);
	increment_line(lexer, *lexer->current);
  } while (*lexer->current != '"' && !is_end(lexer));
}

static void skip_whitespace(lexer_t *lexer) {
  while (is_space(*lexer->current)) {
	increment_line(lexer, *lexer->current);
	advance(lexer);
  }
}

static char *get_literal(lexer_t *lexer) {
  const size_t length = lexer->current - lexer->start;

  char *literal = uai_malloc((length + 1) * sizeof lexer->current);
  strncpy(literal, (lexer->current - length), length);
  *(literal + length) = '\0';

  return literal;
}

token_t *lexer_next_token(lexer_t *lexer) {
  skip_whitespace(lexer);
  lexer->start = lexer->current;

  token_t *token = uai_malloc(sizeof *token);
  token->line = lexer->line;

  if (is_alpha(*lexer->current)) {
	read_ident(lexer);
	token->type = ident_type(lexer);
	token->literal = get_literal(lexer);
	return token;
  }

  if (is_digit(*lexer->current)) {
	read_number(lexer);
	token->type = T_NUMBER;
	token->literal = get_literal(lexer);
	return token;
  }

  switch (*lexer->current) {
	case '=': {
	  token->type = T_ASSIGN;
	  token->literal = dup_string("=");
	  if (peek(lexer) == '=') {
		token->type = T_EQ;
		token->literal = dup_string("==");
		advance(lexer);
	  }
	  break;
	}
	case '!': {
	  token->type = T_NOT;
	  token->literal = dup_string("!");
	  if (peek(lexer) == '=') {
		token->type = T_NOT_EQ;
		token->literal = dup_string("!=");
		advance(lexer);
	  }
	  break;
	}
	case '<': {
	  token->type = T_LT;
	  token->literal = dup_string("<");
	  if (peek(lexer) == '=') {
		token->type = T_LT_EQ;
		token->literal = dup_string("<=");
		advance(lexer);
	  }
	  break;
	}
	case '>': {
	  token->type = T_GT;
	  token->literal = dup_string(">");
	  if (peek(lexer) == '=') {
		token->type = T_GT_EQ;
		token->literal = dup_string(">=");
		advance(lexer);
	  }
	  break;
	}
	case '&': {
	  if (peek(lexer) == '&') {
		token->type = T_AND;
		token->literal = dup_string("&&");
		advance(lexer);
		break;
	  }
	}
	case '|': {
	  if (peek(lexer) == '|') {
		token->type = T_OR;
		token->literal = dup_string("||");
		advance(lexer);
		break;
	  }
	}
	case '*': {
	  token->type = T_ASTERISK;
	  token->literal = dup_string("*");
	  if (peek(lexer) == '*') {
		token->type = T_POWER;
		token->literal = dup_string("**");
		advance(lexer);
	  }
	  break;
	}
	case '+': {
	  token->type = T_PLUS;
	  token->literal = dup_string("+");
	  if (peek(lexer) == '+') {
		token->type = T_PLUS_PLUS;
		token->literal = dup_string("++");
		advance(lexer);
	  }
	  break;
	}
	case '-': {
	  token->type = T_MINUS;
	  token->literal = dup_string("-");
	  if (peek(lexer) == '-') {
		token->type = T_MINUS_MINUS;
		token->literal = dup_string("--");
		advance(lexer);
	  }
	  break;
	}
	case '"': {
	  lexer->start++;
	  read_string(lexer);
	  token->type = T_STRING;
	  token->literal = get_literal(lexer);
	  break;
	}
	case '/': {
	  token->type = T_SLASH;
	  token->literal = dup_string("/");
	  break;
	}
	case '%': {
	  token->type = T_MODULO;
	  token->literal = dup_string("%");
	  break;
	}
	case ',': {
	  token->type = T_COMMA;
	  token->literal = dup_string(",");
	  break;
	}
	case ';': {
	  token->type = T_SEMICOLON;
	  token->literal = dup_string(";");
	  break;
	}
	case ':': {
	  token->type = T_COLON;
	  token->literal = dup_string(":");
	  break;
	}
	case '(': {
	  token->type = T_LPAREN;
	  token->literal = dup_string("(");
	  break;
	}
	case ')': {
	  token->type = T_RPAREN;
	  token->literal = dup_string(")");
	  break;
	}
	case '{': {
	  token->type = T_LBRACE;
	  token->literal = dup_string("{");
	  break;
	}
	case '}': {
	  token->type = T_RBRACE;
	  token->literal = dup_string("}");
	  break;
	}
	case '[': {
	  token->type = T_LBRACKET;
	  token->literal = dup_string("[");
	  break;
	}
	case ']': {
	  token->type = T_RBRACKET;
	  token->literal = dup_string("]");
	  break;
	}
	case '\0': {
	  token->type = T_EOF;
	  token->literal = dup_string("\0");
	  break;
	}
	default: {
	  token->type = T_ILLEGAL;
	  token->literal = NULL;
	  break;
	}
  }
  advance(lexer);
  return token;
}

lexer_t *lexer_new(const char *input) {
  lexer_t *lexer = uai_malloc(sizeof *lexer);

  lexer->input = uai_malloc((strlen(input) + 1) * sizeof input);
  strcpy(lexer->input, input);

  lexer->line = 1;
  lexer->start = lexer->input;
  lexer->current = lexer->input;

  return lexer;
}

void lexer_free(lexer_t *lexer) {
  uai_free(lexer->input);
  uai_free(lexer);
}
