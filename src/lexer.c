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

static bool isAtEnd(Lexer *lexer) {
  return *lexer->current == '\0';
}

static bool isSpace(const char ch) {
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

static bool isAlpha(const char ch) {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

static bool isDigit(const char ch) {
  return ch >= '0' && ch <= '9';
}

static char peek(Lexer *lexer) {
  return *(lexer->current + 1);
}

static void readChar(Lexer *lexer) {
  if (isAtEnd(lexer)) return;
  lexer->current++;
}

static TokenType identifierType(Lexer *lexer) {
  const size_t length = lexer->current - lexer->start;
  for (short i = 0; keywords[i].literal != NULL; i++) {
	if (length == keywords[i].length && strncmp(lexer->start, keywords[i].literal, length) == 0) {
	  return keywords[i].type;
	}
  }
  return T_IDENT;
}

static void readIdentifier(Lexer *lexer) {
  while (isAlpha(*lexer->current) || isDigit(*lexer->current)) {
	readChar(lexer);
  }
}

static void readNumber(Lexer *lexer) {
  const char *list = ".xXaAbBcCdDeEfF";
  while (isDigit(*lexer->current) || strchr(list, *lexer->current) != NULL) {
	readChar(lexer);
  }
}

static void incrementLine(Lexer *lexer, const char ch) {
  lexer->line += ch == '\n' ? 1 : 0;
}

static void readString(Lexer *lexer) {
  do {
	readChar(lexer);
	incrementLine(lexer, *lexer->current);
  } while (*lexer->current != '"' && !isAtEnd(lexer));
}

static void skipWhitespace(Lexer *lexer) {
  while (isSpace(*lexer->current)) {
	incrementLine(lexer, *lexer->current);
	readChar(lexer);
  }
}

static Token makeToken(Lexer *lexer, TokenType type) {
  const size_t length = lexer->current - lexer->start;

  Token token;
  token.type = type;
  token.line = lexer->line;
  token.start = lexer->current - length;
  token.length = length == 0 ? 1 : length;
  token.end = length == 0 ? token.start : (lexer->current - 1);

  return token;
}

Token nextToken(Lexer *lexer) {
  skipWhitespace(lexer);
  lexer->start = lexer->current;

  if (isAlpha(*lexer->current)) {
	readIdentifier(lexer);
	return makeToken(lexer, identifierType(lexer));
  }

  if (isDigit(*lexer->current)) {
	readNumber(lexer);
	return makeToken(lexer, T_NUMBER);
  }

  Token token;
  switch (*lexer->current) {
	case '\0': token = makeToken(lexer, T_EOF);
	  break;
	case '=': {
	  if (peek(lexer) == '=') {
		token = makeToken(lexer, T_EQ);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_ASSIGN);
	  }
	  break;
	}
	case '!': {
	  if (peek(lexer) == '=') {
		token = makeToken(lexer, T_NOT_EQ);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_NOT);
	  }
	  break;
	}
	case '<': {
	  if (peek(lexer) == '=') {
		token = makeToken(lexer, T_LT_EQ);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_LT);
	  }
	  break;
	}
	case '>': {
	  if (peek(lexer) == '=') {
		token = makeToken(lexer, T_GT_EQ);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_GT);
	  }
	  break;
	}
	case '&': {
	  if (peek(lexer) == '&') {
		token = makeToken(lexer, T_AND);
		readChar(lexer);
		break;
	  }
	}
	case '|': {
	  if (peek(lexer) == '|') {
		token = makeToken(lexer, T_OR);
		readChar(lexer);
		break;
	  }
	}
	case '*': {
	  if (peek(lexer) == '*') {
		token = makeToken(lexer, T_POWER);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_ASTERISK);
	  }
	  break;
	}
	case '+': {
	  if (peek(lexer) == '+') {
		token = makeToken(lexer, T_PLUS_PLUS);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_PLUS);
	  }
	  break;
	}
	case '-': {
	  if (peek(lexer) == '-') {
		token = makeToken(lexer, T_MINUS_MINUS);
		readChar(lexer);
	  } else {
		token = makeToken(lexer, T_MINUS);
	  }
	  break;
	}
	case '"': {
	  readString(lexer);
	  token = makeToken(lexer, T_STRING);
	  token.end++;
	  token.length++;
	  break;
	}
	case '/': token = makeToken(lexer, T_SLASH);
	  break;
	case '%': token = makeToken(lexer, T_MODULO);
	  break;
	case ',': token = makeToken(lexer, T_COMMA);
	  break;
	case ';': token = makeToken(lexer, T_SEMICOLON);
	  break;
	case ':': token = makeToken(lexer, T_COLON);
	  break;
	case '(': token = makeToken(lexer, T_LPAREN);
	  break;
	case ')': token = makeToken(lexer, T_RPAREN);
	  break;
	case '{': token = makeToken(lexer, T_LBRACE);
	  break;
	case '}': token = makeToken(lexer, T_RBRACE);
	  break;
	case '[': token = makeToken(lexer, T_LBRACKET);
	  break;
	case ']': token = makeToken(lexer, T_RBRACKET);
	  break;
	default: token = makeToken(lexer, T_ILLEGAL);
	  break;
  }
  readChar(lexer);
  return token;
}

Lexer *makeLexer(const char *source) {
  Lexer *lexer = uai_malloc(sizeof(Lexer));

  const size_t size = strlen(source) + 1;
  lexer->source = uai_malloc(size);
  strncpy(lexer->source, source, size);

  lexer->line = 1;
  lexer->start = lexer->source;
  lexer->current = lexer->source;

  return lexer;
}

void freeLexer(Lexer *lexer) {
  uai_free((void *)lexer->source);
  uai_free((void *)lexer);
}
