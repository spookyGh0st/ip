#ifndef IP_PARSER_HPP
#define IP_PARSER_HPP


#include <ip/Syntax.h>
#include <memory>
#include <ip/Scanner.h>
#include <optional>

namespace ip{
    class Parser {
    private:
        ip::Scanner scanner;
        ip::Token current;
        ip::Token previous;

        void advance();

        void consume(ip::TokenType type, const std::string& expected);

        [[nodiscard]] std::unique_ptr<Expr> parseExpr();
        [[nodiscard]] std::unique_ptr<Expr> parseBinary(short minBP);
        [[nodiscard]] std::unique_ptr<Expr> parseAtom();
        [[nodiscard]] std::unique_ptr<Expr> parseParenthesized();
        [[nodiscard]] std::unique_ptr<Expr> parseNumber();
        [[nodiscard]] std::unique_ptr<Expr> parseIdentifier();
        [[nodiscard]] std::unique_ptr<Expr> parseBinaryFunction(Operator op);

        [[nodiscard]] std::optional<Operator> parseOperator() const;
        static std::pair<short, short> bindingPower(Operator op);
    public:
        explicit Parser(const std::string_view &src);
        std::unique_ptr<Expr> parse();

    };

}

#endif //IP_PARSER_HPP
