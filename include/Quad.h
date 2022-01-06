#ifndef IP_QUAD_H
#define IP_QUAD_H

class Quad {
private:
    unsigned  int quad_vao{};
    unsigned  int quad_vbo{};
public:
    Quad();
    ~Quad();
    void render() const;
};

#include "ShaderProgram.h"
#include "Syntax.h"
#include "Tape.h"
#include "Audio.h"

#endif //IP_QUAD_H
