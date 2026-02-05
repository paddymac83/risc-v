#include "scanner.hpp"
#include <cassert>
#include <iostream>

#define ASSERT_TOKEN(scanner, expected_type, expected_lexeme) do { \
    Token t = scanner.scanToken(); \
    assert(t.type == expected_type && "Wrong token type"); \
    assert(t.lexeme == expected_lexeme && "Wrong lexeme"); \
} while(0)

#define ASSERT_TYPE(scanner, expected_type) do { \
    Token t = scanner.scanToken(); \
    assert(t.type == expected_type && "Wrong token type"); \
} while(0)

void test_single_char_tokens() {
    Scanner s("( ) { } , . - + ; / *");
    ASSERT_TOKEN(s, TokenType::LEFT_PAREN, "(");
    ASSERT_TOKEN(s, TokenType::RIGHT_PAREN, ")");
    ASSERT_TOKEN(s, TokenType::LEFT_BRACE, "{");
    ASSERT_TOKEN(s, TokenType::RIGHT_BRACE, "}");
    ASSERT_TOKEN(s, TokenType::COMMA, ",");
    ASSERT_TOKEN(s, TokenType::DOT, ".");
    ASSERT_TOKEN(s, TokenType::MINUS, "-");
    ASSERT_TOKEN(s, TokenType::PLUS, "+");
    ASSERT_TOKEN(s, TokenType::SEMICOLON, ";");
    ASSERT_TOKEN(s, TokenType::SLASH, "/");
    ASSERT_TOKEN(s, TokenType::STAR, "*");
    ASSERT_TYPE(s, TokenType::END_OF_FILE);
}

void test_two_char_tokens() {
    Scanner s("! != = == < <= > >=");
    ASSERT_TOKEN(s, TokenType::BANG, "!");
    ASSERT_TOKEN(s, TokenType::BANG_EQUAL, "!=");
    ASSERT_TOKEN(s, TokenType::EQUAL, "=");
    ASSERT_TOKEN(s, TokenType::EQUAL_EQUAL, "==");
    ASSERT_TOKEN(s, TokenType::LESS, "<");
    ASSERT_TOKEN(s, TokenType::LESS_EQUAL, "<=");
    ASSERT_TOKEN(s, TokenType::GREATER, ">");
    ASSERT_TOKEN(s, TokenType::GREATER_EQUAL, ">=");
}

void test_keywords() {
    Scanner s("and class else false for fun if nil or print return super this true var while");
    ASSERT_TYPE(s, TokenType::AND);
    ASSERT_TYPE(s, TokenType::CLASS);
    ASSERT_TYPE(s, TokenType::ELSE);
    ASSERT_TYPE(s, TokenType::FALSE);
    ASSERT_TYPE(s, TokenType::FOR);
    ASSERT_TYPE(s, TokenType::FUN);
    ASSERT_TYPE(s, TokenType::IF);
    ASSERT_TYPE(s, TokenType::NIL);
    ASSERT_TYPE(s, TokenType::OR);
    ASSERT_TYPE(s, TokenType::PRINT);
    ASSERT_TYPE(s, TokenType::RETURN);
    ASSERT_TYPE(s, TokenType::SUPER);
    ASSERT_TYPE(s, TokenType::THIS);
    ASSERT_TYPE(s, TokenType::TRUE);
    ASSERT_TYPE(s, TokenType::VAR);
    ASSERT_TYPE(s, TokenType::WHILE);
}

void test_identifiers() {
    Scanner s("foo _bar baz123 andy classy");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "foo");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "_bar");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "baz123");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "andy");   // not "and"
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "classy"); // not "class"
}

void test_numbers() {
    Scanner s("123 45.67 0 3.14159");
    ASSERT_TOKEN(s, TokenType::NUMBER, "123");
    ASSERT_TOKEN(s, TokenType::NUMBER, "45.67");
    ASSERT_TOKEN(s, TokenType::NUMBER, "0");
    ASSERT_TOKEN(s, TokenType::NUMBER, "3.14159");
}

void test_strings() {
    Scanner s("\"hello\" \"world with spaces\" \"\"");
    ASSERT_TOKEN(s, TokenType::STRING, "\"hello\"");
    ASSERT_TOKEN(s, TokenType::STRING, "\"world with spaces\"");
    ASSERT_TOKEN(s, TokenType::STRING, "\"\"");
}

void test_unterminated_string() {
    Scanner s("\"oops");
    Token t = s.scanToken();
    assert(t.type == TokenType::ERROR);
    assert(t.lexeme == "Unterminated string.");
}

void test_comments_ignored() {
    Scanner s("foo // this is a comment\nbar");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "foo");
    ASSERT_TOKEN(s, TokenType::IDENTIFIER, "bar");
}

void test_line_tracking() {
    Scanner s("a\nb\n\nc");
    Token t1 = s.scanToken(); assert(t1.line == 1);
    Token t2 = s.scanToken(); assert(t2.line == 2);
    Token t3 = s.scanToken(); assert(t3.line == 4);
}

void test_unexpected_char() {
    Scanner s("@");
    Token t = s.scanToken();
    assert(t.type == TokenType::ERROR);
    assert(t.lexeme == "Unexpected character.");
}

int main() {
    test_single_char_tokens();
    test_two_char_tokens();
    test_keywords();
    test_identifiers();
    test_numbers();
    test_strings();
    test_unterminated_string();
    test_comments_ignored();
    test_line_tracking();
    test_unexpected_char();

    std::cout << "All 10 tests passed.\n";
    return 0;
}
