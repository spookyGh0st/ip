#include <iostream>
#include "ip/Scanner.hpp"

using namespace ip;

Scanner::Scanner(const std::string_view &source): src(source), start(0), current(0) { }

Token Scanner::scanToken() {
    skipWhitespace();
    start = current;
    if (isAtEnd())
        return makeToken(TOKEN_EOF);
    auto c = advance();

    if (std::isdigit(c)) return number();
    if (std::isalpha(c)) return identifier();

    switch (c) {
        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '*': return makeToken(TOKEN_STAR);
        case '/': return makeToken(TOKEN_SLASH);
        case '^': return makeToken(TOKEN_POW);
        case '%': return makeToken(TOKEN_PERCENT);
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case ',': return makeToken(TOKEN_COMMA);
        default: throw std::runtime_error("Unexpected character: " + std::string{static_cast<char>(c)});
    }
}

Token Scanner::number() {
    while (std::isdigit(peek()))
        advance();
    if (peek() == '.' && std::isdigit(peekNext())){
        advance();
        while (std::isdigit(peek()))
            advance();
    }
    return makeToken(TOKEN_NUMBER);
}

Token Scanner::identifier() {
    while(std::isalnum(peek()))
        advance();
    return makeToken(TOKEN_IDENTIFIER);
}

void Scanner::skipWhitespace() {
    while (std::isspace(peek()))
        advance();
}

Token Scanner::makeToken(TokenType type) {
    auto data = src.substr(start, current-start);
    return Token{ type, data };
}

bool Scanner::isAtEnd() {
    return  (current >= src.length());
}

char8_t Scanner::peek(){
    return src[current];
}

char8_t Scanner::peekNext(){
    if (isAtEnd()) return '\0';
    return src[current+1];
}

char8_t Scanner::advance() {
    current++;
    return src[current-1];
}
