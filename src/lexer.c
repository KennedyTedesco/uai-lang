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

static token_t new_token(lexer_t *lexer, token_type type) {
  const size_t length = lexer->current - lexer->start;

  token_t token;
  token.type = type;
  token.line = lexer->line;
  token.start = lexer->current - length;
  token.length = length == 0 ? 1 : length;
  token.end = length == 0 ? token.start : (lexer->current - 1);

  return token;
}

token_t lexer_next_token(lexer_t *lexer) {
  skip_whitespace(lexer);
  lexer->start = lexer->current;

  if (is_alpha(*lexer->current)) {
	read_ident(lexer);
	return new_token(lexer, ident_type(lexer));
  }

  if (is_digit(*lexer->current)) {
	read_number(lexer);
	return new_token(lexer, T_NUMBER);
  }

  token_t token;
  switch (*lexer->current) {
	case '\0': token = new_token(lexer, T_EOF);
	  break;
	case '=': {
	  if (peek(lexer) == '=') {
		token = new_token(lexer, T_EQ);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_ASSIGN);
	  }
	  break;
	}
	case '!': {
	  if (peek(lexer) == '=') {
		token = new_token(lexer, T_NOT_EQ);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_NOT);
	  }
	  break;
	}
	case '<': {
	  if (peek(lexer) == '=') {
		token = new_token(lexer, T_LT_EQ);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_LT);
	  }
	  break;
	}
	case '>': {
	  if (peek(lexer) == '=') {
		token = new_token(lexer, T_GT_EQ);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_GT);
	  }
	  break;
	}
	case '&': {
	  if (peek(lexer) == '&') {
		token = new_token(lexer, T_AND);
		advance(lexer);
		break;
	  }
	}
	case '|': {
	  if (peek(lexer) == '|') {
		token = new_token(lexer, T_OR);
		advance(lexer);
		break;
	  }
	}
	case '*': {
	  if (peek(lexer) == '*') {
		token = new_token(lexer, T_POWER);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_ASTERISK);
	  }
	  break;
	}
	case '+': {
	  if (peek(lexer) == '+') {
		token = new_token(lexer, T_PLUS_PLUS);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_PLUS);
	  }
	  break;
	}
	case '-': {
	  if (peek(lexer) == '-') {
		token = new_token(lexer, T_MINUS_MINUS);
		advance(lexer);
	  } else {
		token = new_token(lexer, T_MINUS);
	  }
	  break;
	}
	case '"': {
	  read_string(lexer);
	  token = new_token(lexer, T_STRING);
	  token.end++;
	  token.length++;
	  break;
	}
	case '/': token = new_token(lexer, T_SLASH);
	  break;
	case '%': token = new_token(lexer, T_MODULO);
	  break;
	case ',': token = new_token(lexer, T_COMMA);
	  break;
	case ';': token = new_token(lexer, T_SEMICOLON);
	  break;
	case ':': token = new_token(lexer, T_COLON);
	  break;
	case '(': token = new_token(lexer, T_LPAREN);
	  break;
	case ')': token = new_token(lexer, T_RPAREN);
	  break;
	case '{': token = new_token(lexer, T_LBRACE);
	  break;
	case '}': token = new_token(lexer, T_RBRACE);
	  break;
	case '[': token = new_token(lexer, T_LBRACKET);
	  break;
	case ']': token = new_token(lexer, T_RBRACKET);
	  break;
	default: token = new_token(lexer, T_ILLEGAL);
	  break;
  }
  advance(lexer);
  return token;
}

lexer_t *lexer_new(const char *input) {
  lexer_t *lexer = uai_malloc(sizeof(lexer_t));

  lexer->input = uai_malloc(sizeof(input) * (strlen(input) + 1));
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
