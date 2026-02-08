#include "compiler.hpp"
#include "scanner.hpp"
#include <cstdio>

bool compile(std::string_view source) {
    Scanner scanner(source);

    int line = -1;
    bool hadError = false;

    for (;;) {
        Token token = scanner.scanToken();

        if (token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }

        printf("%2d '%.*s'\n",
               static_cast<int>(token.type),
               static_cast<int>(token.lexeme.size()),
               token.lexeme.data());

        if (token.type == TokenType::ERROR) {
            hadError = true;
        }

        if (token.type == TokenType::END_OF_FILE) break;
    }

    return !hadError;
}
