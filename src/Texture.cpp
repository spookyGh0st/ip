
#include "Texture.h"
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WIMAGE_PATH "/home/user/uni/sem7/ip/assets/materials/wood/Wood066_1K_Color.jpg"
#define DIMAGE_PATH "/home/user/uni/sem7/ip/assets/materials/duck/mariana_texture.png"


WoodTexture::WoodTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(WIMAGE_PATH, &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void WoodTexture::bind(ShaderProgram &shaderProgram) {
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texture);
    std::string name  = "woodTexture";
    shaderProgram.bind(name,2);
}

DuckTexture::DuckTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(DIMAGE_PATH, &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

void DuckTexture::bind(ShaderProgram &shaderProgram) {
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texture);
    std::string name  = "duckTexture";
    shaderProgram.bind(name,3);
}
