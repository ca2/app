#include "hdrtexture.h"

#include <iostream>

#include "glad/glad.h"
#include "stb_image.h"

HDRTexture::HDRTexture(const std::string &path) {
    int width, height, numChannels;
    float *data = stbi_loadf(path.c_str(), &width, &height, &numChannels, 0);

    if (!data) {
        std::cout << "Failed to load texture data" << std::endl;
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
}

unsigned int
HDRTexture::getId() {
    return mId;
}