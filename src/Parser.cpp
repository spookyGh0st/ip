#include <charconv>
#include "Parser.hpp"

using namespace ip;

Parser::Parser(const std::string_view& src)
    :scanner(ip::Scanner(src)) { }

std::unique_ptr<Expr> Parser::parse() {
    advance();
    return parseExpr();
}

std::unique_ptr<Expr> Parser::parseExpr() {
    return parseBinary(0);
}

std::unique_ptr<Expr> Parser::parseBinary(short minBP){
    auto lhs { parseAtom() };
    while (true){
        auto op { parseOperator() };
        if (op == std::nullopt) {
            break;
        }
        auto [leftBP, rightBP] { bindingPower(op.value())};
        if (leftBP < minBP) break;
        advance();
        auto rhs { parseBinary(rightBP) };
        lhs = std::make_unique<Binary>(std::move(lhs),std::move(rhs),op.value());
    }
    return lhs;
}

std::unique_ptr<Expr> Parser::parseAtom() {
    switch (current.type) {
        case TOKEN_NUMBER: return parseNumber();
        case TOKEN_IDENTIFIER: return parseIdentifier();
        default: throw std::runtime_error("Expected Expression, but saw error");
    }
}

std::unique_ptr<Expr> Parser::parseNumber() {
    consume(ip::TOKEN_NUMBER,"a number");
    double number;
    auto [ptr, ec] { std::from_chars(previous.data.data(), previous.data.data() + previous.data.size(), number) };

    if(ec == std::errc::invalid_argument){
        throw std::runtime_error("Expected Number, but got "+std::string{previous.data} + " to a number");
    }
    if(ec == std::errc::result_out_of_range){
        throw std::runtime_error("Number is larger then a double: "+std::string{previous.data} + " to a number");
    }
    // todo debug return values
    return std::make_unique<Number>(number);
}


void Parser::advance() {
    if (current.type != TOKEN_EOF){
        previous = current;
        current = scanner.scanToken();
    }
}

void Parser::consume(ip::TokenType type, const std::string& expected) {
    if (current.type == type){
        advance();
        return;
    }else {
        auto msg { "expected " + expected + "got " + std::string{current.data} };
        throw std::runtime_error(msg);
    }
}

std::pair<short, short> Parser::bindingPower(Operator op){
    switch (op) {
        case Operator::OP_PLUS: case Operator::OP_MINUS:
            return std::pair(3,4);
        case Operator::OP_MULTIPLY: case Operator::OP_DIVIDE:
            return std::pair(5,6);
        case Operator::OP_POW: case Operator::OP_MODULO:
            return std::pair(7,8);
        case Operator::OP_MAXIMAL: case Operator::OP_MINIMAL:
            return std::pair(9,10);
    }
}


std::optional<Operator> Parser::parseOperator() const {
    switch (current.type) {
        case TOKEN_PLUS: return Operator::OP_PLUS;
        case TOKEN_MINUS: return Operator::OP_MINUS;
        case TOKEN_STAR: return Operator::OP_MULTIPLY;
        case TOKEN_SLASH: return Operator::OP_DIVIDE;
        case TOKEN_POW: return Operator::OP_POW;
        default: return std::nullopt;
    }
}

std::unique_ptr<Expr> Parser::parseIdentifier() {
   consume(ip::TOKEN_IDENTIFIER,"Identifier");
   if (previous.data == "sqrt")
       return std::make_unique<Sqrt>(parseParenthesized());
    if (previous.data == "max")
        return parseBinaryFunction(Operator::OP_MAXIMAL);
    if (previous.data == "min")
        return parseBinaryFunction(Operator::OP_MINIMAL);
    if (previous.data == "x")
        return std::make_unique<Var>(X);
    if (previous.data == "y")
        return std::make_unique<Var>(Y);
    if (previous.data == "z")
        return std::make_unique<Var>(Z);
    throw std::runtime_error("Unknown identifier" + std::string(current.data));
}

std::unique_ptr<Expr> Parser::parseParenthesized() {
    consume(ip::TOKEN_LEFT_PAREN,"(");
    auto inner = parseExpr();
    consume(ip::TOKEN_RIGHT_PAREN,")");
    return inner;
}

std::unique_ptr<Expr> Parser::parseBinaryFunction(Operator op) {
    consume(ip::TOKEN_LEFT_PAREN,"(");
    auto X = parseExpr();
    consume(TOKEN_COMMA,",");
    auto Y = parseExpr();
    consume(ip::TOKEN_RIGHT_PAREN,")");
    return std::make_unique<Binary>(std::move(X),std::move(Y),op);
}

