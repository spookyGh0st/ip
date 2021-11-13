cmake_minimum_required(VERSION 3.17)
project(
        ip
        VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "clang++")
add_executable(ip src/main.cpp src/glad.c
        src/Window.cpp include/ip/Window.hpp
        src/Syntax.cpp
        include/ip/Syntax.hpp
        src/GeometricalObject.cpp
        src/Scanner.cpp include/ip/Scanner.hpp
        include/ip/GeometricalObject.hpp src/Parser.cpp src/Parser.hpp src/Display.cpp src/Display.hpp src/Instruction.cpp include/ip/Instruction.hpp)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(ip PRIVATE include)
target_link_libraries(ip PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
