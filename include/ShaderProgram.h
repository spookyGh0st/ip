

#ifndef IP_SHADERPROGRAM_H
#define IP_SHADERPROGRAM_H

#include <filesystem>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
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

    void bind(std::string &name, int value) const;
    void bindFloat(std::string &name, float value) const;

    void bindUnsignedInt(std::string &name, unsigned int value) const;

    void bindTapeBuffer(std::string name, uint8_t value[], std::string sizeName, unsigned int size, int count) const;
    void bindRamBuffer(std::string name, float value[], std::string sizeName, unsigned int size, int count) const;
    void bindVec2(std::string &name, float width, float height) const;
    void bindVec3(const char *name, glm::vec3) const;
    void bindVec4(const char *name, glm::vec4) const;
    void bindMat4(const char *name, glm::mat4) const;
};


#endif //IP_SHADERPROGRAM_H
