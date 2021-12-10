#ifndef IP_TEST_H
#define IP_TEST_H

#include <memory>
#include <ip/Syntax.h>
#include <iostream>
#include <ip/Parser.hpp>
#include <ip/Tape.h>

std::unique_ptr<Expr> testParsing();
void testTape();

#endif //IP_TEST_H
