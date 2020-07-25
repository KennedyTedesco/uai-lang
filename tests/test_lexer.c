#include "unity.h"
#include "../src/token.h"
#include "../src/lexer.h"

void setUp(void) {}
void tearDown(void) {}

void test_eat_spaces(void) {
  Lexer lexer = newLexer(" var 	foo1  =  \n10.5 != 5f;");

  TEST_ASSERT_EQUAL(T_VAR, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASSIGN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(1, lexer.line);

  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NOT_EQ, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_EOF, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(2, lexer.line);
}

void test_len(void) {
  Token token;
  Lexer lexer = newLexer("var a = 10 + 1;");

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_VAR, token.type);
  TEST_ASSERT_EQUAL('v', *token.start);
  TEST_ASSERT_EQUAL('a', *(token.start + token.length - 2));
  TEST_ASSERT_EQUAL('r', *(token.start + token.length - 1));
  TEST_ASSERT_EQUAL(3, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_IDENT, token.type);
  TEST_ASSERT_EQUAL('a', *token.start);
  TEST_ASSERT_EQUAL('a', *(token.start + token.length - 1));
  TEST_ASSERT_EQUAL(1, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_ASSIGN, token.type);
  TEST_ASSERT_EQUAL('=', *token.start);
  TEST_ASSERT_EQUAL('=', *(token.start + token.length - 1));
  TEST_ASSERT_EQUAL(1, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_NUMBER, token.type);
  TEST_ASSERT_EQUAL('1', *token.start);
  TEST_ASSERT_EQUAL('0', *(token.start + token.length - 1));
  TEST_ASSERT_EQUAL(2, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_PLUS, token.type);
  TEST_ASSERT_EQUAL('+', *token.start);
  TEST_ASSERT_EQUAL(1, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_NUMBER, token.type);
  TEST_ASSERT_EQUAL('1', *token.start);
  TEST_ASSERT_EQUAL(1, token.length);

  token = nextToken(&lexer);
  TEST_ASSERT_EQUAL(T_SEMICOLON, token.type);
  TEST_ASSERT_EQUAL(';', *token.start);
  TEST_ASSERT_EQUAL(1, token.length);
}

void test_tokens(void) {
  Lexer lexer = newLexer(
	  "var foo1 = 10;\n"
	  "foo_bar\n"
	  "_bar\n"
	  "var add = fn(x, y) { x + y }\n"
	  "var result = add(five, ten)\n"
	  "!-/*\n"
	  "0.1 < 1.5 > 1\n"
	  "return false\n"
	  "return true\n"
	  "if (5 < 10) { true } else { false }\n"
	  "10 == 10\n"
	  "10 != 9\n"
	  "10 >= 2\n"
	  "10 <= 2\n"
	  "[1, 2]\n"
	  "true && false\n"
	  "true || false\n"
	  "10 % 2\n"
	  "2 ** 2\n"
	  "while (true) { 1 }\n"
	  "a++\n"
	  "a--\n"
	  "a = 0xFF\n"
  );

  // var foo1 = 10
  TEST_ASSERT_EQUAL(T_VAR, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASSIGN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_SEMICOLON, nextToken(&lexer).type);

  // foo_bar
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);

  // _bar
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);

  // var add = fn(x, y) { x + y }
  TEST_ASSERT_EQUAL(T_VAR, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASSIGN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_FN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_COMMA, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LBRACE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_PLUS, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RBRACE, nextToken(&lexer).type);

  // var result = add(five, ten)
  TEST_ASSERT_EQUAL(T_VAR, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASSIGN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_COMMA, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RPAREN, nextToken(&lexer).type);

  // !-/*
  TEST_ASSERT_EQUAL(T_NOT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_MINUS, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_SLASH, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASTERISK, nextToken(&lexer).type);

  //0.1 < 1.5 > 1
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_GT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //return false
  TEST_ASSERT_EQUAL(T_RETURN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_FALSE, nextToken(&lexer).type);

  //return true
  TEST_ASSERT_EQUAL(T_RETURN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_TRUE, nextToken(&lexer).type);

  //if (5 < 10) { true } else { false }
  TEST_ASSERT_EQUAL(T_IF, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LBRACE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_TRUE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RBRACE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ELSE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LBRACE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_FALSE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RBRACE, nextToken(&lexer).type);

  //10 == 10
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_EQ, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //10 != 9
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NOT_EQ, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //10 >= 2
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_GT_EQ, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //10 <= 2
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LT_EQ, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //[1, 2]
  TEST_ASSERT_EQUAL(T_LBRACKET, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_COMMA, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RBRACKET, nextToken(&lexer).type);

  //true && false
  TEST_ASSERT_EQUAL(T_TRUE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_AND, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_FALSE, nextToken(&lexer).type);

  //true || false
  TEST_ASSERT_EQUAL(T_TRUE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_OR, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_FALSE, nextToken(&lexer).type);

  //10 % 2
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_MODULO, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //2 ** 2
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_POWER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);

  //while (true) { 1 }
  TEST_ASSERT_EQUAL(T_WHILE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_TRUE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RPAREN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_LBRACE, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_RBRACE, nextToken(&lexer).type);

  //a++
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_PLUS_PLUS, nextToken(&lexer).type);

  //a--
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_MINUS_MINUS, nextToken(&lexer).type);

  //a = 0xFF
  TEST_ASSERT_EQUAL(T_IDENT, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_ASSIGN, nextToken(&lexer).type);
  TEST_ASSERT_EQUAL(T_NUMBER, nextToken(&lexer).type);
}

void test_tokens_names(void) {
  Lexer lexer = newLexer("var a = 10 + 1;");
  TEST_ASSERT_EQUAL_STRING("VAR", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING("IDENT", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING("=", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING("NUMBER", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING("+", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING("NUMBER", tokenName(nextToken(&lexer).type));
  TEST_ASSERT_EQUAL_STRING(";", tokenName(nextToken(&lexer).type));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_len);
  RUN_TEST(test_tokens);
  RUN_TEST(test_eat_spaces);
  RUN_TEST(test_tokens_names);

  return UNITY_END();
}
