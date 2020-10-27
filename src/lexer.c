#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "token.h"
#include "memory.h"

static const Keyword keywords[] = {
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

static bool is_end(Lexer *lexer) {
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

static char peek(Lexer *lexer) {
  return *(lexer->current + 1);
}

static void advance(Lexer *lexer) {
  if (!is_end(lexer)) {
	lexer->current++;
  }
}

static TOKEN_TYPE ident_type(Lexer *lexer) {
  const size_t length = lexer->current - lexer->start;
  for (short i = 0; keywords[i].literal != NULL; i++) {
	if (length == keywords[i].length && strncmp(lexer->start, keywords[i].literal, length) == 0) {
	  return keywords[i].type;
	}
  }
  return T_IDENT;
}

static void read_ident(Lexer *lexer) {
  while (is_alpha(*lexer->current) || is_digit(*lexer->current)) {
	advance(lexer);
  }
}

static void read_int(Lexer *lexer) {
  while (is_digit(*lexer->current)) {
	advance(lexer);
  }
}

static void increment_line(Lexer *lexer, const char ch) {
  lexer->line += ch == '\n' ? 1 : 0;
}

static void read_string(Lexer *lexer) {
  do {
	advance(lexer);
	increment_line(lexer, *lexer->current);
  } while (*lexer->current != '"' && !is_end(lexer));
}

static void skip_whitespace(Lexer *lexer) {
  while (is_space(*lexer->current)) {
	increment_line(lexer, *lexer->current);
	advance(lexer);
  }
}

static char *get_literal(Lexer *lexer) {
  const size_t length = lexer->current - lexer->start;

  char *literal = uai_malloc((length + 1) * (sizeof *lexer->current));
  strncpy(literal, (lexer->current - length), length);
  *(literal + length) = '\0';

  return literal;
}

Token *lexer_next_token(Lexer *lexer) {
  skip_whitespace(lexer);
  lexer->start = lexer->current;

  Token *token = uai_malloc(sizeof *token);
  token->line = lexer->line;

  if (is_alpha(*lexer->current)) {
	read_ident(lexer);
	token->type = ident_type(lexer);
	token->literal = get_literal(lexer);
	return token;
  }

  if (is_digit(*lexer->current)) {
	read_int(lexer);
	token->type = T_INT;
	token->literal = get_literal(lexer);
	return token;
  }

  switch (*lexer->current) {
	case '=': {
	  if (peek(lexer) == '=') {
		token->type = T_EQ;
		token->literal = strdup("==");
		advance(lexer);
	  } else {
		token->type = T_ASSIGN;
		token->literal = strdup("=");
	  }
	  break;
	}
	case '!': {
	  if (peek(lexer) == '=') {
		token->type = T_NOT_EQ;
		token->literal = strdup("!=");
		advance(lexer);
	  } else {
		token->type = T_NOT;
		token->literal = strdup("!");
	  }
	  break;
	}
	case '<': {
	  if (peek(lexer) == '=') {
		token->type = T_LT_EQ;
		token->literal = strdup("<=");
		advance(lexer);
	  } else {
		token->type = T_LT;
		token->literal = strdup("<");
	  }
	  break;
	}
	case '>': {
	  if (peek(lexer) == '=') {
		token->type = T_GT_EQ;
		token->literal = strdup(">=");
		advance(lexer);
	  } else {
		token->type = T_GT;
		token->literal = strdup(">");
	  }
	  break;
	}
	case '&': {
	  if (peek(lexer) == '&') {
		token->type = T_AND;
		token->literal = strdup("&&");
		advance(lexer);
		break;
	  }
	}
	case '|': {
	  if (peek(lexer) == '|') {
		token->type = T_OR;
		token->literal = strdup("||");
		advance(lexer);
		break;
	  }
	}
	case '*': {
	  if (peek(lexer) == '*') {
		token->type = T_POWER;
		token->literal = strdup("**");
		advance(lexer);
	  } else {
		token->type = T_ASTERISK;
		token->literal = strdup("*");
	  }
	  break;
	}
	case '+': {
	  if (peek(lexer) == '+') {
		token->type = T_PLUS_PLUS;
		token->literal = strdup("++");
		advance(lexer);
	  } else {
		token->type = T_PLUS;
		token->literal = strdup("+");
	  }
	  break;
	}
	case '-': {
	  if (peek(lexer) == '-') {
		token->type = T_MINUS_MINUS;
		token->literal = strdup("--");
		advance(lexer);
	  } else {
		token->type = T_MINUS;
		token->literal = strdup("-");
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
	  token->literal = strdup("/");
	  break;
	}
	case '%': {
	  token->type = T_MODULO;
	  token->literal = strdup("%");
	  break;
	}
	case ',': {
	  token->type = T_COMMA;
	  token->literal = strdup(",");
	  break;
	}
	case ';': {
	  token->type = T_SEMICOLON;
	  token->literal = strdup(";");
	  break;
	}
	case ':': {
	  token->type = T_COLON;
	  token->literal = strdup(":");
	  break;
	}
	case '(': {
	  token->type = T_LPAREN;
	  token->literal = strdup("(");
	  break;
	}
	case ')': {
	  token->type = T_RPAREN;
	  token->literal = strdup(")");
	  break;
	}
	case '{': {
	  token->type = T_LBRACE;
	  token->literal = strdup("{");
	  break;
	}
	case '}': {
	  token->type = T_RBRACE;
	  token->literal = strdup("}");
	  break;
	}
	case '[': {
	  token->type = T_LBRACKET;
	  token->literal = strdup("[");
	  break;
	}
	case ']': {
	  token->type = T_RBRACKET;
	  token->literal = strdup("]");
	  break;
	}
	case '\0': {
	  token->type = T_EOF;
	  token->literal = strdup("\0");
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

Lexer *lexer_new(const char *input) {
  Lexer *lexer = uai_malloc(sizeof *lexer);

  lexer->input = uai_malloc((strlen(input) + 1) * (sizeof *input));
  strcpy(lexer->input, input);

  lexer->line = 1;
  lexer->start = lexer->input;
  lexer->current = lexer->input;

  return lexer;
}

void lexer_free(Lexer *lexer) {
  uai_free(lexer->input);
  uai_free(lexer);
}
