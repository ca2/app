#include "framework.h"
#include "hdr_texture.h"
#include "acme/filesystem/filesystem/file_context.h"

#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>
//
// namespace gpu_opengl
// {
//
//
//    hdr_texture::hdr_texture()
//    {
//
//    }
//
//
//    hdr_texture::~hdr_texture()
//    {
//
//    }
//
//
//    void hdr_texture::initialize_hdr_texture(const ::file::path & path)
//    {
//
//       int width, height, numChannels;
//
//       auto memory = file()->as_memory(path);
//       float *data = stbi_loadf_from_memory(memory.data(), memory.size(), &width, &height, &numChannels, 0);
//
//       if (!data) {
//          std::cout << "Failed to load texture data" << std::endl;
//          stbi_image_free(data);
//          return;
//       }
//
//       glGenTextures(1, &m_uId);
//       glBindTexture(GL_TEXTURE_2D, m_uId);
//
//       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
//
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//       stbi_image_free(data);
//
//    }
//
//    unsigned int hdr_texture::getId()
//    {
//
//       return m_uId;
//
//    }
//
//
// } // namespace gpu_opengl
//
//
