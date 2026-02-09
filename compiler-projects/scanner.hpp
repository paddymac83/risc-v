#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <string>
#include <string_view>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS,
    SEMICOLON, SLASH, STAR,

    // One or two character tokens
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE,
    FOR, FUN, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS,
    TRUE, VAR, WHILE,

    ERROR, END_OF_FILE
};

struct Token {
    TokenType type;
    std::string_view lexeme;
    int line;

    Token() : type(TokenType::END_OF_FILE), lexeme(), line(0) {}
    Token(TokenType type, std::string_view lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {}
};

class Scanner {
public:
    explicit Scanner(std::string_view source);

    Token scanToken();

private:
    bool isAtEnd() const;
    char advance();
    char peek() const;
    char peekNext() const;
    bool match(char expected);

    Token makeToken(TokenType type) const;
    Token errorToken(const char* message) const;

    void skipWhitespace();
    TokenType checkKeyword(int start, int length,
                           std::string_view rest, TokenType type) const;
    TokenType identifierType() const;

    Token identifier();
    Token number();
    Token string();

    static bool isAlpha(char c);
    static bool isDigit(char c);

    std::string_view source_;
    const char* start_;
    const char* current_;
    int line_;
};

// Utility function to get token type name (for debugging)
const char* tokenTypeName(TokenType type);

#endif // SCANNER_HPP
