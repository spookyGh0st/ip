#ifndef IP_TEST_H
#define IP_TEST_H

#include <memory>
#include <ip/Syntax.h>
#include <iostream>
#include <ip/Parser.hpp>
#include <ip/Tape.h>
#include <sndfile.h>
#include <portaudio.h>

std::unique_ptr<Expr> testParsing();
void testTape();
void testAudio();

#endif //IP_TEST_H
