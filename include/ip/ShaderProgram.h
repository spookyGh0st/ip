

#ifndef IP_SHADERPROGRAM_H
#define IP_SHADERPROGRAM_H

#include <filesystem>
#include "log.h"

class ShaderProgram {
private:
    unsigned int programID;
    static std::string StrFromPath(std::filesystem::path &vert);
    static unsigned int createShader(const char *code, int i);
public:
    ShaderProgram(std::filesystem::path vert, std::filesystem::path frag);
    ~ShaderProgram();

    static unsigned int createProgram(unsigned int vShader, unsigned int fShader);

    void use() const;
};


#endif //IP_SHADERPROGRAM_H
