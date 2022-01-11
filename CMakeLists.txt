cmake_minimum_required(VERSION 3.17)
project(
        ip
        VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE c_sources CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "include/*.h")

add_executable(ip ${sources} ${c_sources} ${headers})

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(kissfft REQUIRED)
find_package(glm REQUIRED)
find_library(portaudio portaudio REQUIRED)
find_library(sndfile sndfile REQUIRED)

target_include_directories(ip PRIVATE include)
target_link_libraries(ip PUBLIC kissfft-float glfw OpenGL::GL glm::glm portaudio sndfile ${CMAKE_DL_LIBS})
target_compile_options(ip PRIVATE -Wall -Wextra)
