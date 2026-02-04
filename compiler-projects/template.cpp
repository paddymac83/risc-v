#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Token types
enum TokenType {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EOF
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Simple lexer
class Lexer {
    std::string input;
    size_t pos = 0;
    
public:
    Lexer(const std::string& input) : input(input) {}
    
    Token nextToken() {
        // Skip whitespace
        while (pos < input.length() && isspace(input[pos])) pos++;
        
        if (pos >= input.length()) {
            return {TOKEN_EOF, ""};
        }
        
        // Number
        if (isdigit(input[pos])) {
            std::string num;
            while (pos < input.length() && isdigit(input[pos])) {
                num += input[pos++];
            }
            return {TOKEN_NUMBER, num};
        }
        
        // Operators
        char c = input[pos++];
        if (c == '+') return {TOKEN_PLUS, "+"};
        if (c == '-') return {TOKEN_MINUS, "-"};
        
        throw std::runtime_error("Unknown character");
    }
};

int main() {
    std::string input = "10 + 20 - 5";
    Lexer lexer(input);
    
    Token tok;
    while ((tok = lexer.nextToken()).type != TOKEN_EOF) {
        std::cout << "Token: " << tok.value << "\n";
    }
    
    return 0;
}
