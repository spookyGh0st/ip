

#ifndef IP_TEXTURE_H
#define IP_TEXTURE_H

#include "ShaderProgram.h"

/*
 * This is horrible and I should instead use a decent texture loader
 * Too bad!
 */

class DuckTexture {
    unsigned int texture;
public:
    DuckTexture();
    void bind(ShaderProgram &shaderProgram);

};
class WoodTexture {
    unsigned int texture;
public:
    WoodTexture();
    void bind(ShaderProgram &shaderProgram);

};


#endif //IP_TEXTURE_H
