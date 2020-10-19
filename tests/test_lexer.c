#include "unity.h"
#include "../src/token.h"
#include "../src/lexer.h"

void setUp(void) {}
void tearDown(void) {}

void test_eat_spaces(void) {
  lexer_t *lexer = lexer_new(" var 	foo1  =  \n10.5 != 5f;	");

  TEST_ASSERT_EQUAL(T_VAR, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(1, lexer->line);

  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NOT_EQ, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_EOF, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(2, lexer->line);

  lexer_free(lexer);
}

void test_tokens(void) {
  lexer_t *lexer = lexer_new(
	  "var foo1 = 10;\n"
	  "foo_bar;\n"
	  "_bar;\n"
	  "var add = fn(x, y) { x + y };\n"
	  "var result = add(five, ten);\n"
	  "!-/*;\n"
	  "0.1 < 1.5 > 1;\n"
	  "return false;\n"
	  "return true;\n"
	  "if (5 < 10) { true } else { false };\n"
	  "10 == 10;\n"
	  "10 != 9;\n"
	  "10 >= 2;\n"
	  "10 <= 2;\n"
	  "[1, 2];\n"
	  "true && false;\n"
	  "true || false;\n"
	  "10 % 2;\n"
	  "2 ** 2;\n"
	  "while (true) { 1 };\n"
	  "a++;\n"
	  "a--;\n"
	  "a = 0xFF;\n"
	  "a = \"foo\";\n"
  );

  // var foo1 = 10
  TEST_ASSERT_EQUAL(T_VAR, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  // foo_bar
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  // _bar
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  // var add = fn(x, y) { x + y }
  TEST_ASSERT_EQUAL(T_VAR, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_FN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_COMMA, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_PLUS, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  // var result = add(five, ten)
  TEST_ASSERT_EQUAL(T_VAR, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_COMMA, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  // !-/*
  TEST_ASSERT_EQUAL(T_NOT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_MINUS, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SLASH, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASTERISK, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //0.1 < 1.5 > 1
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_GT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //return false
  TEST_ASSERT_EQUAL(T_RETURN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_FALSE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //return true
  TEST_ASSERT_EQUAL(T_RETURN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_TRUE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //if (5 < 10) { true } else { false }
  TEST_ASSERT_EQUAL(T_IF, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_TRUE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ELSE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_FALSE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //10 == 10
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_EQ, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //10 != 9
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NOT_EQ, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //10 >= 2
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_GT_EQ, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //10 <= 2
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LT_EQ, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //[1, 2]
  TEST_ASSERT_EQUAL(T_LBRACKET, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_COMMA, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RBRACKET, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //true && false
  TEST_ASSERT_EQUAL(T_TRUE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_AND, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_FALSE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //true || false
  TEST_ASSERT_EQUAL(T_TRUE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_OR, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_FALSE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //10 % 2
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_MODULO, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //2 ** 2
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_POWER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //while (true) { 1 }
  TEST_ASSERT_EQUAL(T_WHILE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_TRUE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RPAREN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_LBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_RBRACE, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //a++
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_PLUS_PLUS, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //a--
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_MINUS_MINUS, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //a = 0xFF
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_NUMBER, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  //a = "foo";
  TEST_ASSERT_EQUAL(T_IDENT, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_ASSIGN, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_STRING, lexer_next_token(lexer)->type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, lexer_next_token(lexer)->type);

  lexer_free(lexer);
}

void test_tokens_names(void) {
  lexer_t *lexer = lexer_new("var a = 10 + 1;");
  TEST_ASSERT_EQUAL_STRING("VAR", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING("IDENT", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING("=", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING("NUMBER", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING("+", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING("NUMBER", token_name(lexer_next_token(lexer)->type));
  TEST_ASSERT_EQUAL_STRING(";", token_name(lexer_next_token(lexer)->type));

  lexer_free(lexer);
}

void test_string(void) {
  token_t *token;
  lexer_t *lexer = lexer_new("var foo = \"bar\";");

  token = lexer_next_token(lexer);
  TEST_ASSERT_EQUAL(T_VAR, token->type);
  TEST_ASSERT_EQUAL_STRING("var", token->literal);
  token_free(token);

  token = lexer_next_token(lexer);
  TEST_ASSERT_EQUAL(T_IDENT, token->type);
  TEST_ASSERT_EQUAL_STRING("foo", token->literal);
  token_free(token);

  token = lexer_next_token(lexer);
  TEST_ASSERT_EQUAL(T_ASSIGN, token->type);
  TEST_ASSERT_EQUAL_STRING("=", token->literal);
  token_free(token);

  token = lexer_next_token(lexer);
  TEST_ASSERT_EQUAL(T_STRING, token->type);
  TEST_ASSERT_EQUAL_STRING("bar", token->literal);

  token = lexer_next_token(lexer);
  TEST_ASSERT_EQUAL_STRING(";", token->literal);
  token_free(token);

  lexer_free(lexer);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_tokens);
  RUN_TEST(test_string);
  RUN_TEST(test_eat_spaces);
  RUN_TEST(test_tokens_names);

  return UNITY_END();
}
