

#include "glad.h"
#include <fstream>
#include "ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::~ShaderProgram(){
    if (programID != 0){
        glDeleteProgram(programID);
    }
}

ShaderProgram::ShaderProgram(std::filesystem::path vert, std::filesystem::path frag) {
    auto vShaderCodeStr {StrFromPath(vert) };
    const char* vShaderCode { vShaderCodeStr.c_str() };
    auto fShaderCodeStr {StrFromPath(frag) };
    const char* fShaderCode { fShaderCodeStr.c_str() };
    logDebug("creating vertex Shader");
    auto vShader {createShader(vShaderCode, GL_VERTEX_SHADER)};
    logDebug("creating fragment Shader");
    auto fShader {createShader(fShaderCode, GL_FRAGMENT_SHADER)};
    logDebug("creating shader program");
    programID = createProgram(vShader, fShader);
}

unsigned int ShaderProgram::createProgram(unsigned int vShader, unsigned int fShader){
    auto id { glCreateProgram() };
    glAttachShader(id, vShader);
    glAttachShader(id, fShader);
    glLinkProgram(id);

    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success){
        int logLength;
        // glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        // if (logLength == 0)
            logLength = 512;
        char infoLog[logLength];
        glGetShaderInfoLog(id, logLength, NULL, infoLog);
        logError("Shader Program creation failed");
        logError(infoLog);
        throw std::runtime_error("");
    }
    logDebug("Deleting linked Shaders");
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return id;
}

unsigned int ShaderProgram::createShader(const char* code, int shaderType){
    int success, logLength;

    unsigned int shaderID = glCreateShader(shaderType);
    if (shaderID == 0) {
        logError("Failed to create Shader, this should never happen, maybe reboot?");
    }
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (!success){
        // glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
        // if (logLength == 0)
            logLength = 512;
        char infoLog[logLength];
        glGetShaderInfoLog(shaderID, logLength, nullptr, infoLog);
        logError("Shader Compilation failed");
        logError(infoLog);
    }
    return shaderID;
}

std::string ShaderProgram::StrFromPath(std::filesystem::path &vert)  {
    std::ifstream ShaderFile;
    ShaderFile.open(vert);
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << ShaderFile.rdbuf();
    ShaderFile.close();
    return vShaderStream.str();
}

void ShaderProgram::use() const {
    glUseProgram(programID);
}

void ShaderProgram::bindRamBuffer(std::string name, float value[], std::string sizeName, unsigned int size, int count) const {
    unsigned int bufferID;
    glGenBuffers(1,&bufferID);
    glBindBuffer(GL_TEXTURE_BUFFER, bufferID);

    unsigned int texID;
    glGenTextures(1, &texID);
    glActiveTexture(GL_TEXTURE0+count);
    glBindTexture(GL_TEXTURE_BUFFER, texID);

    glTexBuffer(GL_TEXTURE_BUFFER,GL_R32F, bufferID);
    // since we have 4 components, set the size to size * 4
    glBufferStorage(GL_TEXTURE_BUFFER,size*4,value,0);
    bind(name, count);
    bindUnsignedInt(sizeName, size);
}

void ShaderProgram::bindTapeBuffer(std::string name, uint8_t value[], std::string sizeName, unsigned int size, int count) const {
    unsigned int bufferID;
    glGenBuffers(1,&bufferID);
    glBindBuffer(GL_TEXTURE_BUFFER, bufferID);

    unsigned int texID;
    glGenTextures(1, &texID);
    glActiveTexture(GL_TEXTURE0+count);
    glBindTexture(GL_TEXTURE_BUFFER, texID);

    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA8UI, bufferID);
    // since we have 4 components, set the size to size * 4
    glBufferStorage(GL_TEXTURE_BUFFER,size * 4,value,0);
    bind(name, count);
    bindUnsignedInt(sizeName, size);
}

void ShaderProgram::bind(std::string &name, int value) const {
    auto location { glGetUniformLocation(programID, name.c_str()) };
    glUniform1i(location, value);
}
void ShaderProgram::bindFloat(std::string &name, float value) const {
    auto location { glGetUniformLocation(programID, name.c_str()) };
    glUniform1f(location, value);
}

void ShaderProgram::bindUnsignedInt(std::string &name, unsigned int value) const {
    auto location { glGetUniformLocation(programID, name.c_str()) };
    glUniform1ui(location, value);
}

void ShaderProgram::bindVec2(std::string &name, float width, float height) const {
    auto location { glGetUniformLocation(programID, name.c_str()) };
    glUniform2f(location, width, height);
}

void ShaderProgram::bindVec3(const char *name, glm::vec3 value) const {
    auto location { glGetUniformLocation(programID, name) };
    glUniform3f(location, value.x,value.y,value.z);
}

void ShaderProgram::bindVec4(const char *name, glm::vec4 value) const {
    auto location { glGetUniformLocation(programID, name) };
    glUniform4f(location, value.x,value.y,value.z,value.w);
}

void ShaderProgram::bindMat4(const char *name, glm::mat4 value) const {
    auto location { glGetUniformLocation(programID, name) };
    glUniformMatrix4fv(location, 1,GL_FALSE,glm::value_ptr(value));
}

