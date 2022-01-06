#ifndef IP_TOKEN_H
#define IP_TOKEN_H

namespace ip{
    typedef enum {
        // Single-character tokens.
        TOKEN_LEFT_PAREN,
        TOKEN_RIGHT_PAREN,
        TOKEN_COMMA,
        TOKEN_MINUS,
        TOKEN_PLUS,
        TOKEN_STAR,
        TOKEN_SLASH,
        TOKEN_POW,
        TOKEN_PERCENT,
        // One or two character tokens.
        // todo maybe useful when simple compare operations
        // TOKEN_BANG, TOKEN_BANG_EQUAL,
        // TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
        // TOKEN_GREATER, TOKEN_GREATER_EQUAL,
        // TOKEN_LESS, TOKEN_LESS_EQUAL,
        // Literals.
        TOKEN_IDENTIFIER,
        // TOKEN_STRING, // not needed currently
        TOKEN_NUMBER, TOKEN_EOF
    } TokenType;

    class Token{
    public:
        TokenType type;
        std::string_view data;
    };

    class Scanner{
    private:
        const std::string_view src;

        std::size_t start;
        std::size_t current;

        Token number();
        Token identifier();
        void skipWhitespace();
        Token makeToken(TokenType type);
        bool isAtEnd();
        char8_t peek();
        char8_t peekNext();
        char8_t advance();
    public:
        Token scanToken();
        explicit Scanner(const std::string_view &source);
    };
}

#endif //IP_TOKEN_H
