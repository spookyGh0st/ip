cmake_minimum_required(VERSION 3.17)
project(
        ip
        VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "clang++")
add_executable(ip src/main.cpp src/glad.c
        src/Window.cpp include/ip/Window.h
        include/ip/Clause.h src/Clause.cpp
        include/ip/Syntax.h src/Syntax.cpp
        src/Scanner.cpp include/ip/Scanner.h
        src/GeometricalObject.cpp include/ip/GeometricalObject.h
        src/Parser.cpp include/ip/Parser.hpp src/Display.cpp include/ip/Display.h src/Tape.cpp include/ip/Tape.h)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(ip PRIVATE include)
target_link_libraries(ip PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
