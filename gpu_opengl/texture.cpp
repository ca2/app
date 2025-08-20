// Created by camilo on 2025-06-08 18:14 < 3ThomasBorregaardSørensen!!
#include "framework.h"
#include "lock.h"
#include "texture.h"
#include "renderer.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/context_lock.h"


namespace gpu_opengl
{


   texture::texture()
   {

      m_gluTextureID = 0;
      m_gluDepthStencilRBO = 0;
      m_gluFbo = 0;

   }


   texture::~texture()
   {

   }


   void texture::initialize_image_texture(::gpu::renderer* prenderer, const ::int_rectangle& rectangleTarget, bool bWithDepth, const ::pointer_array < ::image::image >& imagea, enum_type etype)
   {

      if (m_rectangleTarget == rectangleTarget)
      {

         return;

      }

      if (etype == e_type_cube_map)
      {

         m_gluType = GL_TEXTURE_CUBE_MAP;

      }
      else
      {

         m_gluType = GL_TEXTURE_2D;

      }

      auto sizeCurrent = m_rectangleTarget.size();

      ::gpu::texture::initialize_image_texture(prenderer, rectangleTarget, bWithDepth, imagea, etype);

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);

      if (sizeCurrent != rectangleTarget.size())
      {

         if (!m_gluTextureID)
         {

            glGenTextures(1, &m_gluTextureID);             // 1. Generate a texture ID
            GLCheckError("");

         }

         glBindTexture(m_gluType, m_gluTextureID);  // 2. Bind the texture to the 2D texture target
         GLCheckError("");

         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         if (m_gluType == GL_TEXTURE_CUBE_MAP)
         {
            glTexParameteri(m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            GLCheckError("");
         }
         glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         GLCheckError("");
         glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         GLCheckError("");

         if (m_gluType == GL_TEXTURE_2D)
         {

            ::memory memory;

            if (imagea.has_element())
            {

               auto scan_area = m_rectangleTarget.area() * 4;

               memory.set_size(scan_area);

               if (imagea.size() != rectangleTarget.size())
               {

                  throw ::exception(error_wrong_state);

               }

               auto pimage32 = (image32_t*)memory.data();

               pimage32->copy(imagea.first());

            }

            auto data = memory.data();

            glTexImage2D(
               GL_TEXTURE_2D, 0, GL_RGBA,
               m_rectangleTarget.width(),
               m_rectangleTarget.height(),
               0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            GLCheckError("");
         }
         else if (m_gluType == GL_TEXTURE_CUBE_MAP)
         {

            if (imagea.first()->width() <= 0 || imagea.first()->height() <= 0)
            {

               throw ::exception(error_wrong_state);

            }
            else if (imagea.first()->height() != imagea.first()->width())
            {

               throw ::exception(error_wrong_state);

            }
            
            ::memory memory;
            
            memory.set_size(imagea.first()->area() * 4);
            
            ::int_point point(0, 0);
            
            ::int_size size(imagea.first()->size());
            
            int scan = size.width() * 4;

            for (unsigned int i = 0; i < 6; i++) 
            {
               
               auto pimage32 = (::image32_t *) memory.data();

               pimage32->copy(size.cx(),size.cy(), scan,
                  imagea[i]->image32(), imagea[i]->m_iScan);
               
               if (pimage32) 
               {

                  // Load the texture data into the cubemap
                  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_BGRA, size.cx(), size.cy(), 0, GL_BGRA, GL_UNSIGNED_BYTE, pimage32);

                  GLCheckError("");

                  //stbi_image_free(data);
               }
               //else if (data) {
               //   glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
               //      0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
               //   stbi_image_free(data);
               //}
               //else {
               //   std::cout << "Failed to load cubemap texture at path: " << facesCubemap[i] << std::endl;
               //   stbi_image_free(data);
               //}
            }
         }
         else
         {

            throw ::exception(error_wrong_state);

         }

         // Optional: generate mipmaps
         // glGenerateMipmap(GL_TEXTURE_2D);

         //free(data);

         glBindTexture(m_gluType, 0);  // Unbind when done
         GLCheckError("");

      }

   }


   //void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   //{

   //   m_pgpurenderer->blend(this, ptexture, rectangleTarget);

   //}


   void texture::create_render_target()
   {

      if (m_gluFbo)
      {

         return;

      }

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);


      //GLuint fboSrc, fboDst;
      glGenFramebuffers(1, &m_gluFbo);
      GLCheckError("");
      glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

      if (m_gluTextureID)
      {

         glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
         GLCheckError("");

         glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, m_gluTextureID, 0);
         GLCheckError("");

         // Set draw buffer
         GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
         glDrawBuffers(1, drawBufs); // REQUIRED for user-defined FBOs
         GLCheckError("");

      }

      if (m_gluDepthStencilRBO)
      {

         glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");

         glFramebufferRenderbuffer(
            GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");

      }

      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         warning() << "Framebuffer attachment is not complete";

      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

   }


   void texture::create_depth_resources()
   {

      if (m_gluDepthStencilRBO)
      {

         return;

      }

      int width = m_rectangleTarget.width();

      int height = m_rectangleTarget.height();

      glGenRenderbuffers(1, &m_gluDepthStencilRBO);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
      GLCheckError("");

      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      GLCheckError("");

   }


   void texture::bind_render_target()
   {

      if (!m_gluFbo)
      {

         create_render_target();

      }

      if (!m_gluFbo)
      {

         throw ::exception(error_wrong_state);

      }

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      GLCheckError("");

   }


   void texture::set_pixels(const ::int_rectangle& rectangle, const void* data)
   {

      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
      glTexSubImage2D(
         GL_TEXTURE_2D,
         0,                 // mip level
         rectangle.left(), rectangle.top(),              // offset inside the texture
         rectangle.width(), rectangle.height(),
         GL_RGBA,           // format of the new data
         GL_UNSIGNED_BYTE,  // type of the new data
         data         // pointer to new pixels
      );

      glBindTexture(GL_TEXTURE_2D, 0);

   }



} // namespace gpu_opengl




