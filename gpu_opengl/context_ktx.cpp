// Created by camilo on 2025-12-18 23:11 <3ThomasBorregaardSørensen!!
#include "framework.h"
#define STB_USE_HUNTER
#include "_gpu_opengl.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "frame_buffer.h"
// #include "gpu/gltf/model.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/binding.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/layer.h"
#include "bred/gpu/types.h"
#include "gpu/gltf/model.h"
#include "lock.h"
#include "model_buffer.h"
#include "program.h"
#include "render_target.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
//
// #include <assimp/Common/StbCommon.h>


// ```cpp
// #include <iostream>
// #include <vector>
// #include <fstream>
//
// #include <GL/glew.h>       // or glad, depending on your setup
// #include <GLFW/glfw3.h>
//
#include <ktx.h>
// #include <ktxvulkan.h>     // not needed for GL, but included in libktx installs
//
//  // Utility: load whole file into memory
//  std::vector<unsigned char> loadFile(const char* filename) {
//     std::ifstream file(filename, std::ios::binary | std::ios::ate);
//     if (!file) throw std::runtime_error("Failed to open file");
//     std::streamsize size = file.tellg();
//     file.seekg(0, std::ios::beg);
//
//     std::vector<unsigned char> buffer(size);
//     if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
//        throw std::runtime_error("Failed to read file");
//     return buffer;
//  }

#if defined(WINDOWS_DESKTOP)
#include "device_win32.h"
#endif
#include <assimp/material.h>

#include <stb/stb_image.h>

#include "bred/gpu/block.h"


namespace gpu_opengl
{

   void context::load_ktxTexture(::pointer<::gpu::texture> &ptexture, void *p_ktxTexture)
   {

      auto pktxtexture = (ktxTexture *)p_ktxTexture;

      GLuint textureId = 0;
      GLenum glTarget = 0;


      // Upload to OpenGL
      GLenum glerror = 0;
      // auto result2 = ktxTexture_GLUpload(kTexture, &textureId, nullptr, &glerror);
      auto result2 = ktxTexture_GLUpload(pktxtexture, &textureId, &glTarget, &glerror);

      if (result2 != KTX_SUCCESS)
      {
         warning() << "Failed to upload KTX to OpenGL\n";
         return;
      }

      information() << "Texture uploaded to OpenGL with ID " << textureId << "\n";

      ::cast<::gpu_opengl::texture> popengltexture = ptexture;
      popengltexture->m_gluType = glTarget;
      popengltexture->m_gluTextureID = textureId;
      ptexture->set_ok_flag();

      //GLuint texture; // The name (ID) of your texture object
      //GLint format;
      //GLenum target = GL_TEXTURE_2D; // The target the texture was created with
      //GLint mipmapLevel = 0;

      //// 1. Bind the texture
      //glBindTexture(target, textureId);

      //// 2. Get the internal format
      //glGetTexLevelParameteriv(target, mipmapLevel, GL_TEXTURE_INTERNAL_FORMAT, &format);

      ////if (format = GL_FORM)

      //// 3. (Optional) Unbind the texture to avoid issues with other operations
      //glBindTexture(target, 0);

   }


      void context::load_ktxTexture_cube_map(::pointer<::gpu::texture> &pgputexture, void *p_ktxTexture)
   {

      auto pktxtexture = (ktxTexture *)p_ktxTexture;


      ::cast<::gpu_opengl::texture> ptexture = pgputexture;

      ptexture->KtxLoadCubemapFrom_ktxTexture("", pktxtexture, false);

      ptexture->set_ok_flag();

   }


} // namespace gpu_opengl
