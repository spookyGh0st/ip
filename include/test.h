#ifndef IP_TEST_H
#define IP_TEST_H

#include <memory>
#include "Syntax.h"
#include <iostream>
#include "Parser.hpp"
#include "Tape.h"

std::unique_ptr<Expr> testParsing();
void testTape();
void testAudio();

#endif //IP_TEST_H
