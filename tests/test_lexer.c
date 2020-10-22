#include "unity.h"
#include "../src/token.h"
#include "../src/lexer.h"

void setUp(void) {}
void tearDown(void) {}

void test_tokens(void) {
  Lexer *lexer = lexer_new(
	  "var foo1 = 10;\n"
	  "foo_bar ;\n"
	  "_bar;\n"
	  "var add = fn( x, y) { x + y };\n"
	  "!-/*;\n"
	  "1 < 2 > 1;\n"
	  "return false;\n"
	  "return true ;\n"
	  "if (5 < 10) { true  } else { false };\n"
	  "10 == 10;\n"
	  "10 != 10;\n"
	  "10 >= 10;\n"
	  "10 <= 10;\n"
	  "[1, 2 ];\n"
	  "true && false;\n"
	  "true || false;\n"
	  "10 % 2;\n"
	  "10 ** 2;\n"
	  "while (true) { 1 };\n"
	  "a++;\n"
	  "a-- ;\n"
	  "a = \"foo\";\n"
  );

  Token tokens[] = {
	  // var foo1 = 10;
	  {T_VAR, "var", 1},
	  {T_IDENT, "foo1", 1},
	  {T_ASSIGN, "=", 1},
	  {T_INT, "10", 1},
	  {T_SEMICOLON, ";", 1},

	  // foo_bar;
	  {T_IDENT, "foo_bar", 1},
	  {T_SEMICOLON, ";", 1},

	  // _bar;
	  {T_IDENT, "_bar", 1},
	  {T_SEMICOLON, ";", 1},

	  // var add = fn(x, y) { x + y };
	  {T_VAR, "var", 1},
	  {T_IDENT, "add", 1},
	  {T_ASSIGN, "=", 1},
	  {T_FN, "fn", 1},
	  {T_LPAREN, "(", 1},
	  {T_IDENT, "x", 1},
	  {T_COMMA, ",", 1},
	  {T_IDENT, "y", 1},
	  {T_RPAREN, ")", 1},
	  {T_LBRACE, "{", 1},
	  {T_IDENT, "x", 1},
	  {T_PLUS, "+", 1},
	  {T_IDENT, "y", 1},
	  {T_RBRACE, "}", 1},
	  {T_SEMICOLON, ";", 1},

	  // !-/*;
	  {T_NOT, "!", 1},
	  {T_MINUS, "-", 1},
	  {T_SLASH, "/", 1},
	  {T_ASTERISK, "*", 1},
	  {T_SEMICOLON, ";", 1},

	  // 0.1 < 1.5 > 1;
	  {T_INT, "1", 1},
	  {T_LT, "<", 1},
	  {T_INT, "2", 1},
	  {T_GT, ">", 1},
	  {T_INT, "1", 1},
	  {T_SEMICOLON, ";", 1},

	  // return false;
	  {T_RETURN, "return", 1},
	  {T_FALSE, "false", 1},
	  {T_SEMICOLON, ";", 1},

	  // return true;
	  {T_RETURN, "return", 1},
	  {T_TRUE, "true", 1},
	  {T_SEMICOLON, ";", 1},

	  // if (5 < 10) { true } else { false };
	  {T_IF, "if", 1},
	  {T_LPAREN, "(", 1},
	  {T_INT, "5", 1},
	  {T_LT, "<", 1},
	  {T_INT, "10", 1},
	  {T_RPAREN, ")", 1},
	  {T_LBRACE, "{", 1},
	  {T_TRUE, "true", 1},
	  {T_RBRACE, "}", 1},
	  {T_ELSE, "else", 1},
	  {T_LBRACE, "{", 1},
	  {T_FALSE, "false", 1},
	  {T_RBRACE, "}", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 == 10;
	  {T_INT, "10", 1},
	  {T_EQ, "==", 1},
	  {T_INT, "10", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 != 10;
	  {T_INT, "10", 1},
	  {T_NOT_EQ, "!=", 1},
	  {T_INT, "10", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 >= 10;
	  {T_INT, "10", 1},
	  {T_GT_EQ, ">=", 1},
	  {T_INT, "10", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 <= 10;
	  {T_INT, "10", 1},
	  {T_LT_EQ, "<=", 1},
	  {T_INT, "10", 1},
	  {T_SEMICOLON, ";", 1},

	  // [1, 2];
	  {T_LBRACKET, "[", 1},
	  {T_INT, "1", 1},
	  {T_COMMA, ",", 1},
	  {T_INT, "2", 1},
	  {T_RBRACKET, "]", 1},
	  {T_SEMICOLON, ";", 1},

	  // true && false;
	  {T_TRUE, "true", 1},
	  {T_AND, "&&", 1},
	  {T_FALSE, "false", 1},
	  {T_SEMICOLON, ";", 1},

	  // true || false;
	  {T_TRUE, "true", 1},
	  {T_OR, "||", 1},
	  {T_FALSE, "false", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 % 2;
	  {T_INT, "10", 1},
	  {T_MODULO, "%", 1},
	  {T_INT, "2", 1},
	  {T_SEMICOLON, ";", 1},

	  // 10 ** 2;
	  {T_INT, "10", 1},
	  {T_POWER, "**", 1},
	  {T_INT, "2", 1},
	  {T_SEMICOLON, ";", 1},

	  // while (true) { 1 };
	  {T_WHILE, "while", 1},
	  {T_LPAREN, "(", 1},
	  {T_TRUE, "true", 1},
	  {T_RPAREN, ")", 1},
	  {T_LBRACE, "{", 1},
	  {T_INT, "1", 1},
	  {T_RBRACE, "}", 1},
	  {T_SEMICOLON, ";", 1},

	  // a++;
	  {T_IDENT, "a", 1},
	  {T_PLUS_PLUS, "++", 1},
	  {T_SEMICOLON, ";", 1},

	  // a--;
	  {T_IDENT, "a", 1},
	  {T_MINUS_MINUS, "--", 1},
	  {T_SEMICOLON, ";", 1},

	  // a = "foo";
	  {T_IDENT, "a", 1},
	  {T_ASSIGN, "=", 1},
	  {T_STRING, "foo", 1},
	  {T_SEMICOLON, ";", 1},

	  {T_EOF, "\0", 1},
  };

  for (size_t i = 0; i < sizeof(tokens) / sizeof(*tokens); i++) {
	Token *token = lexer_next_token(lexer);
	TEST_ASSERT_EQUAL(tokens[i].type, token->type);
	TEST_ASSERT_EQUAL_STRING(tokens[i].literal, token->literal);
	token_free(token);
  }

  lexer_free(lexer);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_tokens);
  return UNITY_END();
}
