

#include <glad/glad.h>
#include <fstream>
#include "ip/ShaderProgram.h"

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

void ShaderProgram::bindTexArr() {
    unsigned int bufferID;
    glGenBuffers(1,&bufferID);
    glBindBuffer(GL_TEXTURE_BUFFER, bufferID);

    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_BUFFER, texID);

    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA8UI, bufferID);

    // todo convert tape to this
    uint8_t data[] { 1,1,0,1 };
    glBufferStorage(GL_TEXTURE_BUFFER,4,data,0);


    // unsigned int blockIndex {glGetUniformBlockIndex(programID, name.c_str()) };
    // glUniformBlockBinding(programID, blockIndex,  )
}

