#include "scanner.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

void runScanner(std::string_view source) {
    Scanner scanner(source);

    int line = -1;
    for (;;) {
        Token token = scanner.scanToken();

        if (token.line != line) {
            std::cout << std::setw(4) << token.line << " ";
            line = token.line;
        } else {
            std::cout << "   | ";
        }

        std::cout << std::setw(16) << std::left << tokenTypeName(token.type)
                  << " '" << token.lexeme << "'" << std::endl;

        if (token.type == TokenType::END_OF_FILE) break;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // Read from file
        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "Could not open file: " << argv[1] << std::endl;
            return 1;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        runScanner(source);
    } else {
        // Demo with sample code
        std::string source = R"(
// Variable declarations
var x = 10;
var name = "hello";

// Function
fun add(a, b) {
    return a + b;
}

// Control flow
if (x >= 5) {
    print x;
} else {
    print "small";
}

// Loop
while (x > 0) {
    x = x - 1;
}

// Class
class Point {
    init(x, y) {
        this.x = x;
        this.y = y;
    }
}
)";
        std::cout << "Scanning sample Lox code:\n";
        std::cout << "========================\n";
        runScanner(source);
    }

    return 0;
}
