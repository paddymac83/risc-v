#include "scanner.hpp"
#include <cstring>

Scanner::Scanner(std::string_view source)
    : source_(source)
    , start_(source_.data())
    , current_(source_.data())
    , line_(1)
{
}

bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAtEnd() const {
    return current_ >= source_.data() + source_.size();
}

char Scanner::advance() {
    current_++;
    return current_[-1];
}

char Scanner::peek() const {
    if (isAtEnd()) return '\0';
    return *current_;
}

char Scanner::peekNext() const {
    if (current_ + 1 >= source_.data() + source_.size()) return '\0';
    return current_[1];
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (*current_ != expected) return false;
    current_++;
    return true;
}

Token Scanner::makeToken(TokenType type) const {
    return Token(type,
                 std::string_view(start_, current_ - start_),
                 line_);
}

Token Scanner::errorToken(const char* message) const {
    return Token(TokenType::ERROR,
                 std::string_view(message, std::strlen(message)),
                 line_);
}

void Scanner::skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                line_++;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    // Comment goes until end of line
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

TokenType Scanner::checkKeyword(int start, int length,
                                 std::string_view rest, TokenType type) const {
    if (current_ - start_ == start + length &&
        std::memcmp(start_ + start, rest.data(), length) == 0) {
        return type;
    }
    return TokenType::IDENTIFIER;
}

TokenType Scanner::identifierType() const {
    switch (start_[0]) {
        case 'a': return checkKeyword(1, 2, "nd", TokenType::AND);
        case 'c': return checkKeyword(1, 4, "lass", TokenType::CLASS);
        case 'e': return checkKeyword(1, 3, "lse", TokenType::ELSE);
        case 'f':
            if (current_ - start_ > 1) {
                switch (start_[1]) {
                    case 'a': return checkKeyword(2, 3, "lse", TokenType::FALSE);
                    case 'o': return checkKeyword(2, 1, "r", TokenType::FOR);
                    case 'u': return checkKeyword(2, 1, "n", TokenType::FUN);
                }
            }
            break;
        case 'i': return checkKeyword(1, 1, "f", TokenType::IF);
        case 'n': return checkKeyword(1, 2, "il", TokenType::NIL);
        case 'o': return checkKeyword(1, 1, "r", TokenType::OR);
        case 'p': return checkKeyword(1, 4, "rint", TokenType::PRINT);
        case 'r': return checkKeyword(1, 5, "eturn", TokenType::RETURN);
        case 's': return checkKeyword(1, 4, "uper", TokenType::SUPER);
        case 't':
            if (current_ - start_ > 1) {
                switch (start_[1]) {
                    case 'h': return checkKeyword(2, 2, "is", TokenType::THIS);
                    case 'r': return checkKeyword(2, 2, "ue", TokenType::TRUE);
                }
            }
            break;
        case 'v': return checkKeyword(1, 2, "ar", TokenType::VAR);
        case 'w': return checkKeyword(1, 4, "hile", TokenType::WHILE);
    }
    return TokenType::IDENTIFIER;
}

Token Scanner::identifier() {
    while (isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

Token Scanner::number() {
    while (isDigit(peek())) advance();

    // Look for fractional part
    if (peek() == '.' && isDigit(peekNext())) {
        // Consume the '.'
        advance();
        while (isDigit(peek())) advance();
    }

    return makeToken(TokenType::NUMBER);
}

Token Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line_++;
        advance();
    }

    if (isAtEnd()) return errorToken("Unterminated string.");

    // The closing quote
    advance();
    return makeToken(TokenType::STRING);
}

Token Scanner::scanToken() {
    skipWhitespace();
    start_ = current_;

    if (isAtEnd()) return makeToken(TokenType::END_OF_FILE);

    char c = advance();

    if (isAlpha(c)) return identifier();
    if (isDigit(c)) return number();

    switch (c) {
        case '(': return makeToken(TokenType::LEFT_PAREN);
        case ')': return makeToken(TokenType::RIGHT_PAREN);
        case '{': return makeToken(TokenType::LEFT_BRACE);
        case '}': return makeToken(TokenType::RIGHT_BRACE);
        case ';': return makeToken(TokenType::SEMICOLON);
        case ',': return makeToken(TokenType::COMMA);
        case '.': return makeToken(TokenType::DOT);
        case '-': return makeToken(TokenType::MINUS);
        case '+': return makeToken(TokenType::PLUS);
        case '/': return makeToken(TokenType::SLASH);
        case '*': return makeToken(TokenType::STAR);
        case '!':
            return makeToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        case '=':
            return makeToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        case '<':
            return makeToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        case '>':
            return makeToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        case '"': return string();
    }

    return errorToken("Unexpected character.");
}

const char* tokenTypeName(TokenType type) {
    switch (type) {
        case TokenType::LEFT_PAREN:     return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN:    return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE:     return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE:    return "RIGHT_BRACE";
        case TokenType::COMMA:          return "COMMA";
        case TokenType::DOT:            return "DOT";
        case TokenType::MINUS:          return "MINUS";
        case TokenType::PLUS:           return "PLUS";
        case TokenType::SEMICOLON:      return "SEMICOLON";
        case TokenType::SLASH:          return "SLASH";
        case TokenType::STAR:           return "STAR";
        case TokenType::BANG:           return "BANG";
        case TokenType::BANG_EQUAL:     return "BANG_EQUAL";
        case TokenType::EQUAL:          return "EQUAL";
        case TokenType::EQUAL_EQUAL:    return "EQUAL_EQUAL";
        case TokenType::GREATER:        return "GREATER";
        case TokenType::GREATER_EQUAL:  return "GREATER_EQUAL";
        case TokenType::LESS:           return "LESS";
        case TokenType::LESS_EQUAL:     return "LESS_EQUAL";
        case TokenType::IDENTIFIER:     return "IDENTIFIER";
        case TokenType::STRING:         return "STRING";
        case TokenType::NUMBER:         return "NUMBER";
        case TokenType::AND:            return "AND";
        case TokenType::CLASS:          return "CLASS";
        case TokenType::ELSE:           return "ELSE";
        case TokenType::FALSE:          return "FALSE";
        case TokenType::FOR:            return "FOR";
        case TokenType::FUN:            return "FUN";
        case TokenType::IF:             return "IF";
        case TokenType::NIL:            return "NIL";
        case TokenType::OR:             return "OR";
        case TokenType::PRINT:          return "PRINT";
        case TokenType::RETURN:         return "RETURN";
        case TokenType::SUPER:          return "SUPER";
        case TokenType::THIS:           return "THIS";
        case TokenType::TRUE:           return "TRUE";
        case TokenType::VAR:            return "VAR";
        case TokenType::WHILE:          return "WHILE";
        case TokenType::ERROR:          return "ERROR";
        case TokenType::END_OF_FILE:    return "EOF";
    }
    return "UNKNOWN";
}
