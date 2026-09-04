// Created by camilo on 2025-06-08 18:14 < 3ThomasBorregaardSørensen!!
#include "platform.h"
#include "texture.h"
#include "_gpu_opengl.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/graphics/image/pixmap.h"
#include "aura/graphics/image/image.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/texture_site.h"
#include "context.h"
#include "device.h"
#include "gpu/_ktx.h"
#include "lock.h"
#include "context.h"

#include <stb/stb_image.h>


namespace
{


   class scoped_pixel_transfer_state
   {
   public:


      GLint m_iReadFramebuffer = 0;
      GLint m_iDrawFramebuffer = 0;
      GLint m_iRenderbuffer = 0;
      GLint m_iReadBuffer = 0;
      GLint m_iTexture2d = 0;
      GLint m_iPackAlignment = 0;
      GLint m_iPackRowLength = 0;
      GLint m_iUnpackAlignment = 0;
      GLint m_iUnpackRowLength = 0;


      scoped_pixel_transfer_state()
      {

         glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &m_iReadFramebuffer);
         glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &m_iDrawFramebuffer);
         glGetIntegerv(GL_RENDERBUFFER_BINDING, &m_iRenderbuffer);
         glGetIntegerv(GL_READ_BUFFER, &m_iReadBuffer);
         glGetIntegerv(GL_TEXTURE_BINDING_2D, &m_iTexture2d);
         glGetIntegerv(GL_PACK_ALIGNMENT, &m_iPackAlignment);
         glGetIntegerv(GL_PACK_ROW_LENGTH, &m_iPackRowLength);
         glGetIntegerv(GL_UNPACK_ALIGNMENT, &m_iUnpackAlignment);
         glGetIntegerv(GL_UNPACK_ROW_LENGTH, &m_iUnpackRowLength);

      }


      ~scoped_pixel_transfer_state() noexcept
      {

         glBindFramebuffer(GL_READ_FRAMEBUFFER, m_iReadFramebuffer);
         glReadBuffer(m_iReadBuffer);
         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_iDrawFramebuffer);
         glBindRenderbuffer(GL_RENDERBUFFER, m_iRenderbuffer);
         glBindTexture(GL_TEXTURE_2D, m_iTexture2d);
         glPixelStorei(GL_PACK_ALIGNMENT, m_iPackAlignment);
         glPixelStorei(GL_PACK_ROW_LENGTH, m_iPackRowLength);
         glPixelStorei(GL_UNPACK_ALIGNMENT, m_iUnpackAlignment);
         glPixelStorei(GL_UNPACK_ROW_LENGTH, m_iUnpackRowLength);

      }


   };


   GLenum pixmap_pixel_format(const ::pixmap_t * ppixmap)
   {

      const auto & indexes = ppixmap->m_colorindexes;

      if (indexes.red() == 2 && indexes.green() == 1 &&
          indexes.blue() == 0 && indexes.opacity() == 3)
      {

         return GL_BGRA;

      }

      if (indexes.red() == 0 && indexes.green() == 1 &&
          indexes.blue() == 2 && indexes.opacity() == 3)
      {

         return GL_RGBA;

      }

      throw ::exception(
         error_not_supported,
         "Unsupported GPU image CPU pixel channel order.");

   }


} // namespace


namespace gpu_opengl
{


   texture::texture()
   {

      m_gluTextureID = 0;
      m_gluDepthStencilRBO = 0;
      m_gluType = 0;
      //m_gluFbo = 0;
      m_glsyncGpuCommandsCompleteFence = 0;


   }


   texture::~texture()
   {

      if (m_gluTextureID)
      {
         glDeleteTextures(1, &m_gluTextureID);
         m_gluTextureID = 0;
      }

      if (m_gluDepthStencilRBO)
      {

         glDeleteRenderbuffers(1, &m_gluDepthStencilRBO);
         m_gluDepthStencilRBO = 0;

      }

   }


   void texture::create_hdr_texture_on_memory(::gpu::context * pgpucontext, const ::block & block)
   {

      ::gpu::context_lock contextlock(pgpucontext);

      m_pgpucontext = pgpucontext;

      auto data = block.data();

      auto size = block.size();

      ::i32 width, height, channels;

      stbi_set_flip_vertically_on_load(1);

      auto imagedata = stbi_loadf_from_memory(data, (::i32)size, &width, &height, &channels, 0);

      stbi_set_flip_vertically_on_load(0);

      if (!imagedata)
      {

         warning() << "Failed to load texture data";

         stbi_image_free(imagedata);

         return;

      }

      // m_etexture = etype;
      m_textureattributes.m_size = { width, height };

      m_textureflags.m_bWithDepth = false;

      m_gluType = GL_TEXTURE_2D;

      glGenTextures(1, &m_gluTextureID);
      ::opengl::check_error("");
      glBindTexture(m_gluType, m_gluTextureID);
      ::opengl::check_error("");

      ::f32 * rgbaData = nullptr;
      if (channels == 3)
      {

         size_t pixelCount = (size_t)width * height;
         rgbaData = (::f32 *)malloc(pixelCount * 4 * sizeof(::f32));

         for (size_t i = 0; i < pixelCount; ++i)
         {
            rgbaData[i * 4 + 0] = imagedata[i * 3 + 0];
            rgbaData[i * 4 + 1] = imagedata[i * 3 + 1];
            rgbaData[i * 4 + 2] = imagedata[i * 3 + 2];
            rgbaData[i * 4 + 3] = 1.0f; // synthesized alpha
         }
         channels = 4;
      }

      //glTexImage2D(m_gluType, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, imagedata);
      glTexImage2D(m_gluType, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, rgbaData ? rgbaData : imagedata);
      ::opengl::check_error("");

      glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      ::opengl::check_error("");
      glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      ::opengl::check_error("");
      glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      ::opengl::check_error("");
      glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      ::opengl::check_error("");


      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      stbi_image_free(imagedata);

      if (rgbaData)
      {

         free(rgbaData);

      }

      glBindTexture(m_gluType, 0);

   }


   void texture::create_with_image_data(::gpu::context * pgpucontext, const ::i32_size & size,
                                            ::i32 numChannels, bool bSrgb, const void * pdata, ::gpu::enum_texture etexture)
   {

      //  if (m_rectangleTarget == rectangleTarget)
      //{

      //   return;
      //}

      ::gpu::texture_attributes textureattributes(size);

      textureattributes.m_iChannelCount = numChannels;
      textureattributes.m_iFloat = bSrgb ? 1 : 0;
      textureattributes.m_etexture = etexture;

      ::gpu::texture_flags textureflags;


      pixmap_t pixmap;

      pixmap.m_pimage32 = (::image32_t *)pdata;
      pixmap.m_pimage32Raw = (::image32_t *)pdata;

      ::gpu::texture_data texturedata(pixmap);

      //      auto sizeCurrent = m_textureattributes.m_rectangleTarget.size();

      create_texture(pgpucontext, textureattributes, textureflags, texturedata);



      //::gpu::texture::initialize_texture(pgpucontext, rectangleTarget, false, {} , etype);

      //::gpu::context_lock contextlock(m_pgpucontext);


      // glGenTextures(1, &m_gluTextureID);
      // glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
      // m_gluType = GL_TEXTURE_2D;
      // // generate the texture
      // glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_textureattributes.m_rectangleTarget.width(), m_textureattributes.m_rectangleTarget.height(), 0,
      //              format, GL_UNSIGNED_BYTE,
      //              pdata);
      //  glGenerateMipmap(GL_TEXTURE_2D);
      //
      // // texture wrapping/filtering options
      //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // image is resized using bilinear filtering
      //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // image is enlarged using bilinear filtering
      //

   }

   // void texture::initialize_image_texture(::gpu::context *pcontext, const ::i32_rectangle &rectangleTarget,
   //                                        bool bWithDepth, const ::pointer_array<::image::image> * pimagea,
   //                                        enum_type etype)
   // {
   //
   //    if (m_pgpucontext != pcontext
   //       && rectangleTarget != m_rectangleTarget
   //       && etype != m_etexture)
   //    {
   //
   //       ::gpu::texture::initialize_image_texture(pcontext, rectangleTarget, bWithDepth, imagea, etype);
   //
   //       create_image(pimagea);
   //
   //    }
   //
   //    if (m_rectangleTarget == rectangleTarget)
   //    {
   //
   //       return;
   //
   //    }
   //
   //    if (etype == ::gpu::e_texture_cube_map)
   //    {
   //
   //       m_gluType = GL_TEXTURE_CUBE_MAP;
   //
   //    }
   //    else
   //    {
   //
   //       m_gluType = GL_TEXTURE_2D;
   //
   //    }
   //
   //    auto sizeCurrent = m_rectangleTarget.size();
   //
   //    ::gpu::texture::initialize_image_texture(pcontext, rectangleTarget, bWithDepth, pimagea, etype);
   //
   //    ::gpu::context_lock contextlock(m_pgpucontext);
   //
   //    if (sizeCurrent != rectangleTarget.size())
   //    {
   //
   //       if (!m_gluTextureID)
   //       {
   //
   //          glGenTextures(1, &m_gluTextureID); // 1. Generate a texture ID
   //          ::opengl::check_error("");
   //       }
   //
   //       glBindTexture(m_gluType, m_gluTextureID); // 2. Bind the texture to the 2D texture target
   //       ::opengl::check_error("");
   //
   //       glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   //       ::opengl::check_error("");
   //       glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   //       ::opengl::check_error("");
   //       if (m_gluType == GL_TEXTURE_CUBE_MAP)
   //       {
   //          glTexParameteri(m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
   //          ::opengl::check_error("");
   //       }
   //       glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   //       ::opengl::check_error("");
   //       glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   //       ::opengl::check_error("");
   //
   //       if (m_gluType == GL_TEXTURE_2D)
   //       {
   //
   //          ::memory memory;
   //
   //          if (imagea.has_element())
   //          {
   //
   //             auto scan_area = m_rectangleTarget.area() * 4;
   //
   //             memory.set_size(scan_area);
   //
   //             if (imagea.size() != rectangleTarget.size())
   //             {
   //
   //                throw ::exception(error_wrong_state);
   //             }
   //
   //             auto pimage32 = (image32_t *)memory.data();
   //
   //             pimage32->copy(imagea.first());
   //          }
   //
   //          auto data = memory.data();
   //
   //          ::i32 w = m_rectangleTarget.width();
   //
   //          ::i32 h = m_rectangleTarget.height();
   //
   //          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
   //                       GL_UNSIGNED_BYTE, data);
   //          ::opengl::check_error("");
   //
   //
   //
   //          ::i32 samples = 0;
   //          glGetIntegerv(GL_SAMPLES, &samples);
   //          printf("MSAA samples: %d\n", samples);
   //
   //
   //          //if (m_gluFbo)
   //          //{
   //          //   glDeleteFramebuffers(1, &m_gluFbo);
   //          //   m_gluFbo = 0;
   //          //   //glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
   //          //   //::opengl::check_error("");
   //          //   //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_gluTextureID, 0);
   //          //   //::opengl::check_error("");
   //          //   //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
   //          //   //{
   //          //   //   ::opengl::check_error("");
   //          //   //   throw ::exception(error_wrong_state);
   //
   //          //   //}
   //          //   //::opengl::check_error("");
   //
   //          //   //i32_rectangle r(pcontext->m_pgpucontext->size());
   //
   //          //   //glViewport(r.left, r.top, r.width(), r.height());
   //          //   //::opengl::check_error("");
   //
   //          //   //glScissor(r.left, r.top, r.width(), r.height());
   //          //   //::opengl::check_error("");
   //
   //          //   //pgpulayer->getCurrentCommandBuffer4()->set_scissor(r);
   //
   //          //}
   //       }
   //       else if (m_gluType == GL_TEXTURE_CUBE_MAP)
   //       {
   //
   //          if (imagea.first()->width() <= 0 || imagea.first()->height() <= 0)
   //          {
   //
   //             throw ::exception(error_wrong_state);
   //          }
   //          else if (imagea.first()->height() != imagea.first()->width())
   //          {
   //
   //             throw ::exception(error_wrong_state);
   //          }
   //
   //          ::memory memory;
   //
   //          memory.set_size(imagea.first()->area() * 4);
   //
   //          ::i32_point point(0, 0);
   //
   //          ::i32_size size(imagea.first()->size());
   //
   //          ::i32 scan = size.width() * 4;
   //
   //          ::i32 iImage;
   //
   //          for (::u32 i = 0; i < 6; i++)
   //          {
   //
   //             auto pimage32 = (::image32_t *)memory.data();
   //
   //             iImage = i;
   //
   //             if (iImage == 2)
   //             {
   //
   //                iImage = 3;
   //
   //             }
   //             else if(iImage == 3)
   //             {
   //
   //                iImage = 2;
   //
   //             }
   //
   //
   //             pimage32->vertical_swap_copy(size.cx, size.cy, scan, imagea[iImage]->image32(), imagea[iImage]->m_iScan);
   //
   //             if (pimage32)
   //             {
   //
   //                // Load the texture data into the cubemap
   //                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_BGRA, size.cx, size.cy, 0, GL_BGRA,
   //                             GL_UNSIGNED_BYTE, pimage32);
   //
   //                ::opengl::check_error("");
   //
   //                // stbi_image_free(data);
   //             }
   //             // else if (data) {
   //             //    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
   //             //       0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   //             //    stbi_image_free(data);
   //             // }
   //             // else {
   //             //    std::cout << "Failed to load cubemap texture at path: " << facesCubemap[i] << std::endl;
   //             //    stbi_image_free(data);
   //             // }
   //          }
   //       }
   //       else
   //       {
   //
   //          throw ::exception(error_wrong_state);
   //       }
   //
   //       // Optional: generate mipmaps
   //       // glGenerateMipmap(GL_TEXTURE_2D);
   //
   //       // free(data);
   //
   //       glBindTexture(m_gluType, 0); // Unbind when done
   //       ::opengl::check_error("");
   //    }
   // }


   // void texture::blend(::gpu::texture* ptexture, const ::i32_rectangle& rectangleTarget)
   //{

   //   m_pgpucontext->blend(this, ptexture, rectangleTarget);

   //}
   void blit_texture_scaled(GLuint sourceTexture, int sourceWidth, int sourceHeight, GLuint destinationTexture,
                            int destinationWidth, int destinationHeight, int iGluType)
   {
      GLuint readFramebuffer = 0;
      GLuint drawFramebuffer = 0;

      glGenFramebuffers(1, &readFramebuffer);
      ::opengl::check_error("");
      glGenFramebuffers(1, &drawFramebuffer);
      ::opengl::check_error("");
      // Source texture
      glBindFramebuffer(GL_READ_FRAMEBUFFER, readFramebuffer);
      ::opengl::check_error("");

      glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, iGluType, sourceTexture, 0);

      if (glCheckFramebufferStatus(GL_READ_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      {
         glDeleteFramebuffers(1, &readFramebuffer);
         ::opengl::check_error("");
         glDeleteFramebuffers(1, &drawFramebuffer);
         ::opengl::check_error("");
         return;
      }

      // Destination texture
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFramebuffer);
      ::opengl::check_error("");

      glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, iGluType, destinationTexture, 0);

      if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      {
         ::opengl::check_error("");
         glDeleteFramebuffers(1, &readFramebuffer);
         ::opengl::check_error("");
         glDeleteFramebuffers(1, &drawFramebuffer);
         ::opengl::check_error("");
         return;
      }

      glReadBuffer(GL_COLOR_ATTACHMENT0);
      ::opengl::check_error("");
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      ::opengl::check_error("");

      GLboolean bScissorTestEnabled = glIsEnabled(GL_SCISSOR_TEST);
      GLboolean baColorWriteMask[4]{};
      glGetBooleanv(GL_COLOR_WRITEMASK, baColorWriteMask);
      ::opengl::check_error("");

      if (bScissorTestEnabled)
      {

         glDisable(GL_SCISSOR_TEST);
         ::opengl::check_error("");

      }

      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
      ::opengl::check_error("");

      const GLfloat faTransparent[4]{};
      glClearBufferfv(GL_COLOR, 0, faTransparent);
      ::opengl::check_error("");

      glColorMask(
         baColorWriteMask[0],
         baColorWriteMask[1],
         baColorWriteMask[2],
         baColorWriteMask[3]);
      ::opengl::check_error("");

      if (bScissorTestEnabled)
      {

         glEnable(GL_SCISSOR_TEST);
         ::opengl::check_error("");

      }

      glBlitFramebuffer(0, 0, sourceWidth, sourceHeight, 0, 0, destinationWidth, destinationHeight, GL_COLOR_BUFFER_BIT,
                        GL_LINEAR);
      ::opengl::check_error("");

      //GLenum error = glGetError();

      glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      ::opengl::check_error("");
      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
      ::opengl::check_error("");

      glDeleteFramebuffers(1, &readFramebuffer);
      ::opengl::check_error("");
      glDeleteFramebuffers(1, &drawFramebuffer);
      ::opengl::check_error("");

      //return error == GL_NO_ERROR;
   }

   ::i32 texture::effective_sample_count() const
   {

      if (!m_bMultisample)
      {

         return 1;

      }

      auto iSampleCount = m_iSampleCount;

      if (iSampleCount <= 1 && m_papplication)
      {

         iSampleCount = m_papplication->m_gpu.m_iSampleCount;

      }

      if (iSampleCount < 2)
      {

         throw ::exception(
            error_bad_argument,
            "An OpenGL multisample texture requires at least two samples.");

      }

      return iSampleCount;

   }


   void texture::invalidate_framebuffer_attachments()
   {

      if (m_gluDepthStencilRBO)
      {

         glDeleteRenderbuffers(1, &m_gluDepthStencilRBO);
         m_gluDepthStencilRBO = 0;

      }

      for (auto & pair : m_mapContextHandleObject)
      {

         pair.element2().m_bBound = false;

      }

   }


   void texture::create_texture(
      ::gpu::context * pgpucontext,
      const ::gpu::texture_attributes & textureattributes,
      const ::gpu::texture_flags & textureflags,
      const ::gpu::texture_data & texturedata)
   {

      if (textureattributes.m_sizeRaw.is_empty()
         && textureattributes.m_size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      auto gluDesiredType =
         textureattributes.m_etexture == ::gpu::e_texture_cube_map
         ? GL_TEXTURE_CUBE_MAP
         : (m_bMultisample
               ? GL_TEXTURE_2D_MULTISAMPLE
               : GL_TEXTURE_2D);
      auto iDesiredSampleCount =
         gluDesiredType == GL_TEXTURE_2D_MULTISAMPLE
         ? effective_sample_count()
         : 1;
      auto sizeDesired = textureattributes.m_size;
      auto bAllocationChanged =
         m_gluAllocatedType != 0 &&
         (m_gluAllocatedType != gluDesiredType ||
            m_sizeAllocated != sizeDesired ||
            m_iAllocatedSampleCount != iDesiredSampleCount);

      if (bAllocationChanged &&
         m_pgpucontext == pgpucontext &&
         m_textureattributes == textureattributes)
      {

         m_pgpucontext = nullptr;

      }

      ::gpu::texture::create_texture(
         pgpucontext,
         textureattributes,
         textureflags,
         texturedata);

   }


   void texture::_create_texture(const ::gpu::texture_data & data)
   {

      if (m_textureattributes.m_sizeRaw.is_empty()
         && m_textureattributes.m_size.is_empty())
      {

         throw ::exception(error_wrong_state);

      }

      ::gpu::context_lock contextlock(m_pgpucontext);

      auto gluDesiredType =
         m_textureattributes.m_etexture == ::gpu::e_texture_cube_map
         ? GL_TEXTURE_CUBE_MAP
         : (m_bMultisample
               ? GL_TEXTURE_2D_MULTISAMPLE
               : GL_TEXTURE_2D);
      auto sizeRaw = m_textureattributes.m_sizeRaw;

      if (sizeRaw.is_empty())
      {

         m_textureattributes.m_sizeRaw = m_textureattributes.m_size;

         sizeRaw = m_textureattributes.m_sizeRaw;

      }
      m_iSampleCount =
         gluDesiredType == GL_TEXTURE_2D_MULTISAMPLE
         ? effective_sample_count()
         : 1;

      auto bAllocationChanged =
         m_gluAllocatedType != 0 &&
         (m_gluAllocatedType != gluDesiredType ||
            m_sizeAllocated != sizeRaw ||
            m_iAllocatedSampleCount != m_iSampleCount);

      if (bAllocationChanged)
      {

         invalidate_framebuffer_attachments();

      }

      if (m_gluTextureID && bAllocationChanged)
      {

         glDeleteTextures(1, &m_gluTextureID);
         m_gluTextureID = 0;

      }

      m_gluType = gluDesiredType;

      if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
      {

         GLint iMaximumSamples = 0;
         GLint iMaximumColorTextureSamples = 0;
         glGetIntegerv(GL_MAX_SAMPLES, &iMaximumSamples);
         ::opengl::check_error("GL_MAX_SAMPLES");
         glGetIntegerv(
            GL_MAX_COLOR_TEXTURE_SAMPLES,
            &iMaximumColorTextureSamples);
         ::opengl::check_error("GL_MAX_COLOR_TEXTURE_SAMPLES");

         if (m_iSampleCount > iMaximumSamples ||
            m_iSampleCount > iMaximumColorTextureSamples)
         {

            ::string strMessage;
            strMessage.formatf(
               "OpenGL MSAA sample count %d exceeds GL_MAX_SAMPLES=%d "
               "or GL_MAX_COLOR_TEXTURE_SAMPLES=%d.",
               m_iSampleCount,
               iMaximumSamples,
               iMaximumColorTextureSamples);
            throw ::exception(error_not_supported, strMessage);

         }

      }

      GLenum format;

      auto iChannelCount = m_textureattributes.m_iChannelCount;

      switch (iChannelCount)
      {
      case 1:
         format = GL_RED;
         break;
      case 2:
         format = GL_RG8;
         break;
      case 3:
         format = GL_RGB8;
         break;
      case 4:
         format = GL_RGBA8;
         break;
      default:
         throw ::exception(error_wrong_state, "Not supported channel count");
         break;
      }

      GLenum internalFormat = format;

      // account for sRGB textures here
      //
      // diffuse textures are in sRGB space (non-linear)
      // metallic/roughness/normals are usually in linear
      // AO depends
      if (m_textureattributes.m_iFloat >= 1)
      {
         if (internalFormat == GL_RGB)
         {
            internalFormat = GL_SRGB;
         }
         else if (internalFormat == GL_RGBA)
         {
            internalFormat = GL_SRGB_ALPHA;
         }
      }


      if (m_textureattributes.m_etexture == ::gpu::e_texture_cube_map)
      {

         m_gluType = GL_TEXTURE_CUBE_MAP;
      }
      else
      {

         //if (m_bMultisample || m_pgpucontext->m_pgpudevice->m_bMultisample)
         if (m_bMultisample)
         {

            m_gluType = GL_TEXTURE_2D_MULTISAMPLE;

            glEnable(GL_MULTISAMPLE);

         }
         else
         {

            m_gluType = GL_TEXTURE_2D;
         }

      }

      if (!m_gluTextureID)
      {

         glGenTextures(1, &m_gluTextureID); // 1. Generate a texture ID
         ::opengl::check_error("");
      }

      glBindTexture(m_gluType, m_gluTextureID); // 2. Bind the texture to the 2D texture target
      ::opengl::check_error("");

      if (m_gluType != GL_TEXTURE_2D_MULTISAMPLE && m_gluType != GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
      {
         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("GL_TEXTURE_WRAP_S");

         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("GL_TEXTURE_WRAP_T");

         if (m_gluType == GL_TEXTURE_CUBE_MAP || m_gluType == GL_TEXTURE_CUBE_MAP_ARRAY)
         {
            glTexParameteri(m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            ::opengl::check_error("GL_TEXTURE_WRAP_R");
         }

         glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         ::opengl::check_error("GL_TEXTURE_MIN_FILTER");

         glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         ::opengl::check_error("GL_TEXTURE_MAG_FILTER");
      }

      /*glTexParameteri(m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      ::opengl::check_error("");
      glTexParameteri(m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      ::opengl::check_error("");
      if (m_gluType == GL_TEXTURE_CUBE_MAP)
      {
         glTexParameteri(m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
      }
      glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      ::opengl::check_error("");
      glTexParameteri(m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      ::opengl::check_error("");*/

      if (m_gluType == GL_TEXTURE_2D || m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
      {

         ::memory memory;

         int wSrc = -1;

         int hSrc = -1;

         int iRedLower = 0;

         const void * pdata = nullptr;

         if (data.is_pixmap_array())
         {

            auto scan_area = m_textureattributes.m_size.area() * 4;

            memory.set_size(scan_area);

            if (data.pixmapa().first()->size() != m_textureattributes.m_size)
            {

               throw ::exception(error_wrong_state);

            }

            auto pimage32 = (image32_t *)memory.data();

            pimage32->copy(data.pixmapa().first());

            pdata = pimage32;

         }
         else if (data.is_raw_scoped_pixmap())
         {

            pdata = data.raw_scoped_pixmap().m_pimage32Raw;

            wSrc = data.raw_scoped_pixmap().m_size.cx;

            hSrc = data.raw_scoped_pixmap().m_size.cy;

            iRedLower = data.raw_scoped_pixmap().m_iRedLower;

            if (data.raw_scoped_pixmap().m_bTopLeft)
            {

               auto scan_area = data.raw_scoped_pixmap().m_size.area() * 4;

               memory.set_size(scan_area);

               auto pimage32 = (image32_t *)memory.data();

               pimage32->y_swap_copy(data.raw_scoped_pixmap());

               pdata = pimage32;

            }

        }

         ::i32 w = m_textureattributes.m_sizeRaw.cx;

         ::i32 h = m_textureattributes.m_sizeRaw.cy;

         if (data.is_gpu_texture())
         {

            pdata = nullptr;
         }


         if (!iRedLower)
         {

            if (internalFormat == GL_RGBA8)
            {

               format = GL_BGRA;

            }

         }

         if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
         {

            if (::is_set(pdata))
            {
               throw ::exception(error_wrong_state);
            }

            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_iSampleCount, GL_RGBA8, w, h, GL_TRUE);
            ::opengl::check_error("");

            GLint sampleBuffers = 0; GLint samples = 0;

            glGetIntegerv(GL_SAMPLE_BUFFERS, &sampleBuffers);
            ::opengl::check_error("");
            glGetIntegerv(GL_SAMPLES, &samples);
            ::opengl::check_error("");


            GLint colorSamples = 0;
            GLint colorWidth = 0;
            GLint colorHeight = 0;
            GLint fixedSampleLocations = 0;

            glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_SAMPLES, &colorSamples);

            glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_WIDTH, &colorWidth);

            glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_HEIGHT, &colorHeight);

            glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_FIXED_SAMPLE_LOCATIONS,
                                     &fixedSampleLocations);


            informationf("colorSamples=%d colorWidth=%d colorHeight=%d fixedSampleLocations=%d", colorSamples,
                         colorWidth, colorHeight, fixedSampleLocations);

            informationf("sampleBuffers=%d samples=%d", sampleBuffers, samples);

            information("");
         }
         else
         {


            glTexImage2D(m_gluType, 0, internalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, pdata);
            ::opengl::check_error("");
         }


         if (data.is_gpu_texture())
         {
            ::cast<::gpu_opengl::texture> popengltexture = data.gpu_texture();

            if (!popengltexture)
            {

               throw ::exception(
                  error_wrong_state,
                  "OpenGL texture copy requires an OpenGL source texture");

            }

            popengltexture->wait_fence();

            auto sourceWidth = minimum(popengltexture->width(), w);
            auto sourceHeight = minimum(popengltexture->height(), h);
            auto x = 0;
            auto y = 0;
            blit_texture_scaled(popengltexture->m_gluTextureID, sourceWidth, sourceHeight, m_gluTextureID, sourceWidth,
                                sourceHeight, m_gluType);
            glFinish();
            ::opengl::check_error("");
            //glBlitFramebuffer(0, 0, sourceWidth, sourceHeight, x, y, x + sourceWidth, y + sourceHeight,
                              //GL_COLOR_BUFFER_BIT, GL_NEAREST);
            //::opengl::check_error("");


         }



         // if (m_gluFbo)
         //{
         //    glDeleteFramebuffers(1, &m_gluFbo);
         //    m_gluFbo = 0;
         //    //glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
         //    //::opengl::check_error("");
         //    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_gluTextureID, 0);
         //    //::opengl::check_error("");
         //    //if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         //    //{
         //    //   ::opengl::check_error("");
         //    //   throw ::exception(error_wrong_state);

         //   //}
         //   //::opengl::check_error("");

         //   //i32_rectangle r(pcontext->m_pgpucontext->size());

         //   //glViewport(r.left, r.top, r.width(), r.height());
         //   //::opengl::check_error("");

         //   //glScissor(r.left, r.top, r.width(), r.height());
         //   //::opengl::check_error("");

         //   //pgpulayer->getCurrentCommandBuffer4()->set_scissor(r);

         //}
      //}
      }
      else if (m_gluType == GL_TEXTURE_CUBE_MAP)
      {

         ::memory memory;

         if (data.is_pixmap_array())
         {

            if (data.pixmapa().first()->size() != sizeRaw)
            {

               throw ::exception(error_wrong_state);

            }

            memory.set_size(sizeRaw.area() * 4);

            //::i32_point point(0, 0);

            //::i32_size size(pimagea->first()->size());
         }

         ::i32 scan = sizeRaw.width() * 4;

         ::i32 iImage;

         for (::u32 i = 0; i < 6; i++)
         {

            image32_t * pimage32 = nullptr;

            if (data.is_pixmap_array())
            {

               pimage32 = (::image32_t *)memory.data();

               iImage = i;

               if (iImage == 2)
               {

                  iImage = 3;

               }
               else if (iImage == 3)
               {

                  iImage = 2;

               }


               auto pimage32Source = data.pixmapa()[iImage]->image32();

               pimage32->y_swap_copy(sizeRaw.cx, sizeRaw.cy, scan,
                  pimage32Source, data.pixmapa()[iImage]->m_iScan);



               //if (pimage32)
               //{
            }
            //}
#if defined(__APPLE__)
               // Load the texture data into the cubemap
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8,
               sizeRaw.cx, sizeRaw.cy, 0, GL_BGRA,
                         GL_UNSIGNED_BYTE, pimage32);

#else
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_BGRA,
               sizeRaw.cx, sizeRaw.cy, 0, GL_BGRA,
                         GL_UNSIGNED_BYTE, pimage32);

#endif

            ::opengl::check_error("");

            if (m_textureattributes.m_iMipCount > 0)
            {

               ::i32 w = sizeRaw.cx;
               ::i32 h = sizeRaw.cy;

               for (::i32 level = 1; level < m_textureattributes.m_iMipCount; ++level) {
                  w = std::max(1, w / 2);
                  h = std::max(1, h / 2);
                  glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, GL_BGRA,
                               w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, nullptr);

                  ::opengl::check_error("");

               }

            }
            // stbi_image_free(data);
         }
         // else if (data) {
         //    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
         //       0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
         //    stbi_image_free(data);
         // }
         // else {
         //    std::cout << "Failed to load cubemap texture at path: " << facesCubemap[i] << std::endl;
         //    stbi_image_free(data);
         // }
      //}
      }
      else
      {

         throw ::exception(error_wrong_state);
      }

      // Optional: generate mipmaps
      // glGenerateMipmap(GL_TEXTURE_2D);


      // GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      //
      // if (status != GL_FRAMEBUFFER_COMPLETE)
      // {
      //
      //    auto pszFramebufferStatusText = ::opengl::check_framebuffer_status_text(status);
      //
      //    if (::is_set(pszFramebufferStatusText))
      //    {
      //
      //       warning("glCheckFramebufferStatus(GL_FRAMEBUFFER) return \"{}\".", pszFramebufferStatusText);
      //
      //    }
      //
      // }


      // free(data);

      glBindTexture(m_gluType, 0); // Unbind when done
      ::opengl::check_error("");

      m_gluAllocatedType = m_gluType;
      m_sizeAllocated = sizeRaw;
      m_iAllocatedSampleCount = m_iSampleCount;


   }


   void texture::_create_frame_buffer_object(base_context_handle::object & object)
   {

      //      if (m_gluFbo)
      //      {
      //
      //         return;
      //
      //      }

            //GLint drawFboOld = 0;
            //glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboOld);

            //GLint readFboOld = 0;
            //glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboOld);

            //::gpu::context_lock contextlock(m_pgpucontext);

      if (object.m_bCreated)
      {

         throw ::exception(error_wrong_state);

      }

      object.m_handle = 0;

      // GLuint fboSrc, fboDst;
      glGenFramebuffers(1, &object.m_handle);
      ::opengl::check_error("");
      ::opengl::ensure_non_null_handle(object.m_handle, "glGenFramebuffers(1, ...)");

      object.m_bCreated = true;

   }


   void texture::_defer_bind_to_render_target(base_context_handle::object & object)
   {

      if (!object.m_bCreated)
      {

         throw ::exception(error_wrong_state);

      }

      if (object.m_bTargetBound)
      {

         throw ::exception(error_wrong_state);

      }

      if (!object.m_handle)
      {

         throw ::exception(error_failed);

      }

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, object.m_handle);
      ::opengl::check_error("");

      if (m_gluTextureID)
      {

         if (m_textureattributes.m_etexture != ::gpu::e_texture_cube_map)
         {

            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_gluType, m_gluTextureID, 0);
            ::opengl::check_error("");

         }

      }

      if (m_gluDepthStencilRBO)
      {

         //glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         //::opengl::check_error("");

         glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_gluDepthStencilRBO);
         ::opengl::check_error("");

      }

      GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         warning() << "Framebuffer attachment is not complete";

         auto pszFramebufferStatusText = ::opengl::check_framebuffer_status_text(status);

         if (::is_set(pszFramebufferStatusText))
         {

            warning("glCheckFramebufferStatus(GL_FRAMEBUFFER) return \"{}\".", pszFramebufferStatusText);

            throw ::exception(error_wrong_state);

         }

      }

      // Set draw buffer
      GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
      glDrawBuffers(1, drawBufs); // REQUIRED for user-defined FBOs
      ::opengl::check_error("");

      object.m_bTargetBound = true;

      //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboOld);
      //glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboOld);
   }


   void texture::_defer_bind_to_render_source(base_context_handle::object & object)
   {

      if (!object.m_bCreated)
      {

         throw ::exception(error_wrong_state);
      }

      if (object.m_bSourceBound)
      {

         throw ::exception(error_wrong_state);
      }

      if (!object.m_handle)
      {

         throw ::exception(error_failed);
      }

      if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
      {

         if (!m_resolveframebuffer.m_framebuffer)
         {
            throw ::exception(error_wrong_state);
         }

         glBindFramebuffer(GL_READ_FRAMEBUFFER, m_resolveframebuffer.m_framebuffer);
         ::opengl::check_error("");

      }
      else
      {

         glBindFramebuffer(GL_READ_FRAMEBUFFER, object.m_handle);
         ::opengl::check_error("");

         if (m_gluTextureID)
         {

            if (m_textureattributes.m_etexture != ::gpu::e_texture_cube_map)
            {

               glFramebufferTexture2D(
                  GL_READ_FRAMEBUFFER,
                  GL_COLOR_ATTACHMENT0,
                  GL_TEXTURE_2D,
                  m_gluTextureID,
                  0);
               ::opengl::check_error("");
               //      glBindTexture(m_gluType, m_gluTextureID);
                 //    ::opengl::check_error("");

                     // if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
                     //{

                     //   glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_gluTextureID);

                     //   GLint colorSamples = 0;
                     //   GLint colorWidth = 0;
                     //   GLint colorHeight = 0;
                     //   GLint fixedSampleLocations = 0;

                     //   glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_SAMPLES, &colorSamples);

                     //   glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_WIDTH, &colorWidth);

                     //   glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_HEIGHT, &colorHeight);

                     //   glGetTexLevelParameteriv(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_TEXTURE_FIXED_SAMPLE_LOCATIONS,
                     //                            &fixedSampleLocations);


                     //   informationf("colorSamples=%d colorWidth=%d colorHeight=%d fixedSampleLocations=%d", colorSamples,
                     //                colorWidth, colorHeight, fixedSampleLocations);

                     //   information("");
                     //}

                     // glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_gluType, m_gluTextureID, 0);
                     //::opengl::check_error("");

                     //// Set draw buffer
                     // GLenum drawBufs[] = {GL_COLOR_ATTACHMENT0};
                     // glDrawBuffers(1, drawBufs); // REQUIRED for user-defined FBOs
                     //::opengl::check_error("");

                     // glBindTexture(m_gluType, 0);
            }
         }
      }

      if (m_gluDepthStencilRBO)
      {

         glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         ::opengl::check_error("");

         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_gluDepthStencilRBO);
         ::opengl::check_error("");
      }

      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         warning() << "Framebuffer attachment is not complete";

         auto pszFramebufferStatusText = ::opengl::check_framebuffer_status_text(status);

         if (::is_set(pszFramebufferStatusText))
         {

            warning("glCheckFramebufferStatus(GL_FRAMEBUFFER) return \"{}\".", pszFramebufferStatusText);

            throw ::exception(error_wrong_state);
         }
      }

      object.m_bBound = true;

      // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboOld);
      // glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboOld);
   }

   ::gpu::texture * texture::resolved_texture(const ::i32_rectangle & rectangle)
   {

      if (m_ptextureResolved == this)
      {

         throw ::exception(
            error_wrong_state,
            "An OpenGL texture cannot resolve into itself.");

      }

      if (m_iSampleCount <= 1)
      {

         return this;

      }

      if (m_gluType != GL_TEXTURE_2D_MULTISAMPLE)
      {

         throw ::exception(
            error_wrong_state,
            "Only GL_TEXTURE_2D_MULTISAMPLE textures can be resolved.");

      }

      ::cast < ::gpu_opengl::context > pcontext = m_pgpucontext;

      if (!pcontext)
      {

         throw ::exception(
            error_wrong_state,
            "The multisample texture has no OpenGL context for resolution.");

      }

      defer_constructø(m_ptextureResolved);

      auto textureattributes = m_textureattributes;
      textureattributes.m_etexture = ::gpu::e_texture_image;
      textureattributes.m_iLayerCount = 1;
      textureattributes.m_iMipCount = 1;

      ::gpu::texture_flags textureflags;
      textureflags.m_bWithDepth = false;
      //textureflags.m_bRenderTarget = true;
      textureflags.m_bRenderTarget = false;
      textureflags.m_bShaderResource = true;
      textureflags.m_bTransferSource = true;
      textureflags.m_bTransferTarget = true;

      m_ptextureResolved->m_bMultisample = false;
      m_ptextureResolved->m_iSampleCount = 1;
      m_ptextureResolved->create_texture(
         pcontext,
         textureattributes,
         textureflags);

      ::gpu::texture_site siteOutput;

      siteOutput.m_pgputextureSite = m_ptextureResolved;
      siteOutput.m_pointOutput = rectangle.origin();

      ::gpu::texture_site siteInput;

      siteInput.m_pgputextureSite = this;
      siteInput.m_pointInput = rectangle.origin();

      pcontext->copy(&siteOutput, &siteInput, nullptr, nullptr);

      return m_ptextureResolved.cast < ::gpu_opengl::texture >();

   }


   void texture::create_depth_resources()
   {

      //::i32 width = m_textureattributes.m_rectangleTarget.width();
      ::i32 width = m_textureattributes.m_sizeRaw.cx;

      //::i32 height = m_textureattributes.m_rectangleTarget.height();
      ::i32 height = m_textureattributes.m_sizeRaw.cy;

      if (!m_gluDepthStencilRBO)
      {

         glGenRenderbuffers(1, &m_gluDepthStencilRBO);
         ::opengl::check_error("");

         glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         ::opengl::check_error("");

         if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
         {


            glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_iSampleCount, GL_DEPTH24_STENCIL8, width, height);
            ::opengl::check_error("");
         }
         else
         {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            ::opengl::check_error("");
         }

         glBindRenderbuffer(GL_RENDERBUFFER, 0);
         ::opengl::check_error("");

         for (auto & pair : m_mapContextHandleObject)
         {

            pair.element2().m_bBound = false;

         }

      }

   }

   ::i32 g_iGpuOpenGlFramebufferObject = 0;
   GLuint texture::target_frame_buffer_object()
   {
      g_iGpuOpenGlFramebufferObject++;
      auto & object = context_handle_object();

      auto & gluFramebufferObject = object.m_handle;

      if (!object.m_bCreated)
      {

         _create_frame_buffer_object(object);

         //      glGenVertexArrays(1, &gluVertexArrayObject);
         //      ::opengl::check_error("");
         //
         //      if(gluVertexArrayObject == 74)
         //      {
         //
         //         information("gluVertexArrayObject == 74");
         //
         //      }

         //glBindVertexArray(vertexarrayobject.m_gluVertexArrayObject);
         //::opengl::check_error("");

         //      ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
         //
         //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
         //
         //      if(::is_set(pbufferVertex))
         //      {
         //
         //         ::cast < input_layout > pinputlayout = m_pinputlayout;
         //
         //         pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
         //                                                gluVertexArrayObject,
         //                                                                pbufferVertex->m_gluVbo,
         //                                                                pbufferIndex ? pbufferIndex->m_gluVbo : 0
         //                                                                );
         //
         //      }

         //glBindVertexArray(0);
         //::opengl::check_error("");

      }

      if (object.m_bCreated)
      {

         //if(m_pinputlayout && !object.m_bBound)
         if (!object.m_bTargetBound)
         {

            _defer_bind_to_render_target(object);

         }

      }

      return gluFramebufferObject;

   }

   GLuint texture::source_frame_buffer_object()
   {
      g_iGpuOpenGlFramebufferObject++;

      auto & object = context_handle_object();

      auto & gluFramebufferObject = object.m_handle;

      if (!object.m_bCreated)
      {

         _create_frame_buffer_object(object);

         //      glGenVertexArrays(1, &gluVertexArrayObject);
         //      ::opengl::check_error("");
         //
         //      if(gluVertexArrayObject == 74)
         //      {
         //
         //         information("gluVertexArrayObject == 74");
         //
         //      }

         // glBindVertexArray(vertexarrayobject.m_gluVertexArrayObject);
         //::opengl::check_error("");

         //      ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
         //
         //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
         //
         //      if(::is_set(pbufferVertex))
         //      {
         //
         //         ::cast < input_layout > pinputlayout = m_pinputlayout;
         //
         //         pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
         //                                                gluVertexArrayObject,
         //                                                                pbufferVertex->m_gluVbo,
         //                                                                pbufferIndex ? pbufferIndex->m_gluVbo : 0
         //                                                                );
         //
         //      }

         // glBindVertexArray(0);
         //::opengl::check_error("");
      }


      if (m_gluType == GL_TEXTURE_2D)
      {
         if (object.m_bCreated)
         {

            // if(m_pinputlayout && !object.m_bBound)
            if (!object.m_bSourceBound)
            {

               _defer_bind_to_render_source(object);
            }
         }
         return gluFramebufferObject;
      }
      else if (m_gluType == GL_TEXTURE_2D_MULTISAMPLE)
      {

         if (!m_resolveframebuffer.m_framebuffer)
         {

            opengl::create_resolve_framebuffer(m_resolveframebuffer, m_sizeAllocated.cx, m_sizeAllocated.cy);

         }

         if (!resolve_multisampled_framebuffer(object.m_handle, m_resolveframebuffer, m_sizeAllocated.cx,
            m_sizeAllocated.cy))
         {

            information("failed to resolved multisampled framebuffer");
         }
         return m_resolveframebuffer.m_framebuffer;

      }
      else
      {

         return gluFramebufferObject;

      }

   }


   ::i32 g_iGpuOpenGlBindRenderTarget = 0;
   void texture::bind_render_target()
   {
      g_iGpuOpenGlBindRenderTarget++;
      //      if (!m_gluFbo)
      //      {
      //
      //         create_render_target();
      //
      //      }

      auto gluFbo = target_frame_buffer_object();

      if (!gluFbo)
      {

         throw ::exception(error_wrong_state);

      }

      GLint drawFbo = 0;
      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
      ::opengl::check_error("");

      if (drawFbo != gluFbo)
      {

         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gluFbo);
         ::opengl::check_error("");

      }

      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      ::opengl::check_error("");

      GLenum statusFramebuffer = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (statusFramebuffer != GL_FRAMEBUFFER_COMPLETE)
      {

         auto pszFramebufferStatusText = ::opengl::check_framebuffer_status_text(statusFramebuffer);

         if (::is_set(pszFramebufferStatusText))
         {
            warning("glCheckFramebufferStatus(GL_FRAMEBUFFER) return \"{}\".", pszFramebufferStatusText);

         }
         throw ::exception(error_failed);
      }

   }


   void texture::read_pixels(::gpu::command_buffer * pgpucommandbuffer, ::pixmap_t * ppixmap, const ::i32_point & pointOutput)
   {

      auto sizePixmap = ppixmap->size();

      auto sizeThis = this->size();

      if (!ppixmap || ppixmap->raw_size() != raw_size() ||
          ppixmap->m_iScan < width() * (int)sizeof(::image32_t) ||
          !ppixmap->m_pimage32 || !m_gluTextureID ||
          (m_gluType != GL_TEXTURE_2D && m_gluType != GL_TEXTURE_2D_MULTISAMPLE))
      {

         throw ::exception(error_bad_argument);

      }

      scoped_pixel_transfer_state state;

      auto gluFramebuffer = source_frame_buffer_object();

      glBindFramebuffer(GL_READ_FRAMEBUFFER, gluFramebuffer);
      ::opengl::check_error("");

      //glFramebufferTexture2D(
      //   GL_READ_FRAMEBUFFER,
      //   GL_COLOR_ATTACHMENT0,
      //   m_gluType,
      //   m_gluTextureID,
      //   0);
      //::opengl::check_error("");

      auto eStatus = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);

      if (eStatus != GL_FRAMEBUFFER_COMPLETE)
      {

         auto pszStatus = ::opengl::check_framebuffer_status_text(eStatus);

         throw ::exception(
            error_wrong_state,
            "GPU image framebuffer is incomplete during CPU mapping.");

      }

      glReadBuffer(GL_COLOR_ATTACHMENT0);
      glPixelStorei(GL_PACK_ALIGNMENT, 1);
      glPixelStorei(
         GL_PACK_ROW_LENGTH,
         ppixmap->m_iScan / (int)sizeof(::image32_t));

      auto x = pointOutput.x;

      auto w = m_textureattributes.m_size.width();

      auto h = m_textureattributes.m_size.height();

      auto y = raw_height() - pointOutput.y - h;

      glReadPixels(
         x,
         y,
         w,
         h,
         pixmap_pixel_format(ppixmap),
         GL_UNSIGNED_BYTE,
         ppixmap->m_pimage32);
      ::opengl::check_error("");

      ppixmap->vertical_swap();

   }


   void texture::write_pixels(bool bSync, const ::pixmap_t * ppixmap, const ::i32_point & pointInput)
   {

      auto sizePixmap = ppixmap->size();

      auto iRequiredScan = ppixmap->width() * (int)sizeof(::image32_t);

      if (not ppixmap 
         or sizePixmap.is_empty()
         or ppixmap->m_iScan < iRequiredScan
         or not ppixmap->m_pimage32 
         or not m_gluTextureID 
         or m_gluType != GL_TEXTURE_2D)
      {

         throw ::exception(error_bad_argument);

      }

      //::memory memoryFlipped = m_pixmapFlipped;
      auto &pixmapFlipped = m_pixmapFlipped;
      pixmapFlipped.create_as_descriptor(ppixmap->size(), DEFAULT_CREATE_IMAGE_FLAG, ppixmap->m_iScan);
      pixmapFlipped.m_colorindexes = ppixmap->m_colorindexes;
      pixmapFlipped.copy(ppixmap);
      pixmapFlipped.vertical_swap();

      int cx = ppixmap->width();
      int cy = ppixmap->height();

      scoped_pixel_transfer_state state;

      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
      ::opengl::check_error("");

      auto textureWidth = raw_width();
      auto textureHeight = raw_height();
      auto x = pointInput.x;
      auto y = pointInput.y;

      auto requiredWidth = x + cx;

      auto requiredHeight = y + cy;

      if (textureWidth < requiredWidth ||
          textureHeight < requiredHeight)
      {
         glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            requiredWidth,
            requiredHeight,
            0,
            GL_BGRA,
            GL_UNSIGNED_BYTE,
            nullptr);
         ::opengl::check_error("");
      }

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      ::opengl::check_error("");
      glPixelStorei(
         GL_UNPACK_ROW_LENGTH,
         pixmapFlipped.m_iScan / (int)sizeof(::image32_t));
      ::opengl::check_error("");

      auto iPixelFormatFlipped = pixmap_pixel_format(&pixmapFlipped);
      glTexSubImage2D(
         GL_TEXTURE_2D,
         0,
         x, 
         y,
         cx,
         cy,
         iPixelFormatFlipped,
         GL_UNSIGNED_BYTE,
         pixmapFlipped.m_pimage32);
      ::opengl::check_error("");

      if (m_textureattributes.m_size.cx < requiredWidth)
      {

         m_textureattributes.m_size.cx = requiredWidth;

      }

      if (m_textureattributes.m_size.cy < requiredHeight)
      {

         m_textureattributes.m_size.cy = requiredHeight;

      }

      if (m_textureattributes.m_sizeRaw.cx < requiredWidth)
      {

         m_textureattributes.m_sizeRaw.cx = requiredWidth;

      }

      if (m_textureattributes.m_sizeRaw.cy < requiredHeight)
      {

         m_textureattributes.m_sizeRaw.cy = requiredHeight;

      }

   }


   //void texture::write_pixels(::gpu::command_buffer * pgpucommandbuffer, const ::pixmap_t * ppixmap, const ::i32_point & pointInput)
   //{

   //   write_pixels(ppixmap, pointInput);

   //}


   void texture::set_pixels(bool bSync, const ::i32_rectangle & rectangle, const void * data)
   {

      if (::is_null(data))
      {

         throw ::exception(error_bad_argument);

      }

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      ::opengl::check_error("");

      // ::i32 w = rectangle.width();
      // ::i32 h = rectangle.height();
      //
      // ::memory memory;
      //
      // memory.set_size(w*h*4);
      //
      // auto src = (char_pointer )data);
      // auto rgba = (char_pointer ) memory.data();
      //
      // for (::i32 y = 0; y < h; ++y)
      // {
      //    for (::i32 x = 0; x < w; ++x)
      //    {
      //       ::u8 a = bm->buffer[y * bm->pitch + x];
      //       rgba[(y*w + x)*4 + 0] = 255;
      //       rgba[(y*w + x)*4 + 1] = 255;
      //       rgba[(y*w + x)*4 + 2] = 255;
      //       rgba[(y*w + x)*4 + 3] = a;
      //    }
      // }

      glBindTexture(m_gluType, m_gluTextureID);
      ::opengl::check_error("");
      glTexSubImage2D(m_gluType,
                      0, // mip level
                      rectangle.left, rectangle.top, // offset inside the texture
                      rectangle.width(), rectangle.height(),
                      GL_RGBA, // format of the new data
                      GL_UNSIGNED_BYTE, // type of the new data
                      data // pointer to new pixels

      );

      ::opengl::check_error("");

      glBindTexture(m_gluType, 0);
      ::opengl::check_error("");
   }


   // Loads a cubemap from a single KTX file
   void texture::KtxLoadCubemapFromFile(const ::scoped_string & scopedstrName, ::string filename, bool b32)
      // VkFormat format,
      // VkQueue copyQueue,
      // VkImageUsageFlags imageUsageFlags,
      // VkImageLayout imageLayout)
   {
      m_textureattributes.m_etexture = ::gpu::e_texture_cube_map;

      ktxTexture * ktxTexture;
      ktxResult result = loadKTXFile(this, filename, &ktxTexture);
      if (result != KTX_SUCCESS)
      {

         throw ::exception(error_failed);

         return;
      }

      KtxLoadCubemapFrom_ktxTexture(scopedstrName, ktxTexture, b32);

   }




   // Loads a cubemap from a single KTX file
   void texture::KtxLoadCubemapFrom_ktxTexture(const ::scoped_string & name, void * p_ktxTexture, bool b32)
      // VkFormat format,
      // VkQueue copyQueue,
      // VkImageUsageFlags imageUsageFlags,
      // VkImageLayout imageLayout)
   {
      m_textureattributes.m_etexture = ::gpu::e_texture_cube_map;
      ::gpu::context_lock lockcontext(m_pgpucontext);
      auto pktxtexture = (ktxTexture *)p_ktxTexture;
      //ktxResult result = loadKTXFile(this, filename, &ktxTexture);
      //if (result != KTX_SUCCESS)
      //{

      //   throw ::exception(error_failed);

      //   return;
      //}

      GLenum glError = 0;

      ktxResult resultUpload = ktxTexture_GLUpload(pktxtexture, &m_gluTextureID, &m_gluType, &glError);

      if (resultUpload != KTX_SUCCESS)
      {

         throw ::exception(error_failed);

         return;
      }

      // ::cast<::gpu_opengl::context> pcontext = m_pgpucontext;
      //
      // ::cast<::gpu_opengl::device> pgpudevice = pcontext->m_pgpudevice;
      //
      // //auto pphysicaldevice = pgpudevice->m_pphysicaldevice;
      //
      // m_rectangleTarget.left = 0;
      // m_rectangleTarget.top = 0;
      // //this->m_pDevice = pdevice;
      // m_rectangleTarget.right = pktxtexture->baseWidth;
      // m_rectangleTarget.bottom = pktxtexture->baseHeight;
      // m_iMipCount = pktxtexture->numLevels;
      //
      // ktx_uint8_t *ktxTextureData = ktxTexture_GetData(pktxtexture);
      // ktx_size_t ktxTextureSize = ktxTexture_GetDataSize(pktxtexture);
      //
      // // VkMemoryAllocateInfo memAllocInfo = vkinit::memoryAllocateInfo();
      // // VkMemoryRequirements memReqs;
      // //
      // // // Create a host-visible staging buffer that contains the raw image data
      // // VkBuffer stagingBuffer;
      // // VkDeviceMemory stagingMemory;
      // //
      // // VkBufferCreateInfo bufferCreateInfo = vkinit::bufferCreateInfo();
      // // bufferCreateInfo.size = ktxTextureSize;
      // // // This buffer is used as a transfer source for the buffer copy
      // // bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
      // // bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
      // //
      // // VK_CHECK_RESULT(vkCreateBuffer(pcontext->logicalDevice(), &bufferCreateInfo, nullptr, &stagingBuffer));
      // //
      // // // Get memory requirements for the staging buffer (alignment, memory type bits)
      // // vkGetBufferMemoryRequirements(pcontext->logicalDevice(), stagingBuffer, &memReqs);
      // //
      // // memAllocInfo.allocationSize = memReqs.size;
      // // // Get memory type index for a host visible buffer
      // // memAllocInfo.memoryTypeIndex = pphysicaldevice->findMemoryType(
      // //    memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
      // //
      // // VK_CHECK_RESULT(vkAllocateMemory(pcontext->logicalDevice(), &memAllocInfo, nullptr, &stagingMemory));
      // // VK_CHECK_RESULT(vkBindBufferMemory(pcontext->logicalDevice(), stagingBuffer, stagingMemory, 0));
      // //
      // // // Copy texture data into staging buffer
      // // uint8_t *data;
      // // VK_CHECK_RESULT(vkMapMemory(pcontext->logicalDevice(), stagingMemory, 0, memReqs.size, 0, (void **)&data));
      // // memcpy(data, ktxTextureData, ktxTextureSize);
      // // vkUnmapMemory(pcontext->logicalDevice(), stagingMemory);
      //
      // // Setup buffer copy regions for each face including all of its mip levels
      // ::array_base<VkBufferImageCopy> bufferCopyRegions;
      //
      // for (uint32_t face = 0; face < 6; face++)
      // {
      //    for (uint32_t level = 0; level < m_iMipCount; level++)
      //    {
      //       ktx_size_t offset;
      //       KTX_error_code result = ktxTexture_GetImageOffset(pktxtexture, level, 0, face, &offset);
      //       ASSERT(result == KTX_SUCCESS);
      //
      //       VkBufferImageCopy bufferCopyRegion = {};
      //       bufferCopyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      //       bufferCopyRegion.imageSubresource.mipLevel = level;
      //       bufferCopyRegion.imageSubresource.baseArrayLayer = face;
      //       bufferCopyRegion.imageSubresource.layerCount = 1;
      //       bufferCopyRegion.imageExtent.width = pktxtexture->baseWidth >> level;
      //       bufferCopyRegion.imageExtent.height = pktxtexture->baseHeight >> level;
      //       bufferCopyRegion.imageExtent.depth = 1;
      //       bufferCopyRegion.bufferOffset = offset & ~0xF;
      //
      //       bufferCopyRegions.add(bufferCopyRegion);
      //    }
      // }
      //
      // // Create optimal tiled target image
      // VkImageCreateInfo imageCreateInfo = vkinit::imageCreateInfo();
      // imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
      // imageCreateInfo.format = format;
      // imageCreateInfo.mipLevels = m_iMipCount;
      // imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
      // imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
      // imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
      // imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      // imageCreateInfo.extent =
      // {
      //    (uint32_t) m_rectangleTarget.width(),
      //    (uint32_t) m_rectangleTarget.height(),
      //    1
      // };
      // imageCreateInfo.usage = imageUsageFlags;
      // // Ensure that the TRANSFER_DST bit is set for staging
      // if (!(imageCreateInfo.usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT))
      // {
      //    imageCreateInfo.usage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
      // }
      // // Cube faces count as array layers in Vulkan
      // imageCreateInfo.arrayLayers = 6;
      // // This flag is required for cube map images
      // imageCreateInfo.flags = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT;
      //
      //
      // VK_CHECK_RESULT(vkCreateImage(pcontext->logicalDevice(), &imageCreateInfo, nullptr, &m_vkimage));
      //
      // vkGetImageMemoryRequirements(pcontext->logicalDevice(), m_vkimage, &memReqs);
      //
      // memAllocInfo.allocationSize = memReqs.size;
      // memAllocInfo.memoryTypeIndex =
      //    pphysicaldevice->findMemoryType(memReqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
      //
      // VK_CHECK_RESULT(vkAllocateMemory(pcontext->logicalDevice(), &memAllocInfo, nullptr, &m_vkdevicememory));
      // VK_CHECK_RESULT(vkBindImageMemory(pcontext->logicalDevice(), m_vkimage, m_vkdevicememory, 0));
      //
      // // Use a separate command buffer for texture loading
      // //VkCommandBuffer pcommandbufferCopy->m_vkcommandbuffer =
      // pdevice->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);
      //
      // auto pgpucommandbufferCopy = pcontext->beginSingleTimeCommands(pcontext->transfer_queue());
      //
      // ::cast<command_buffer> pcommandbufferCopy = pgpucommandbufferCopy;
      //
      // // Image barrier for optimal image (target)
      // // Set initial layout for all array layers (faces) of the optimal (target) tiled texture
      // VkImageSubresourceRange subresourceRange = {};
      // subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      // subresourceRange.baseMipLevel = 0;
      // subresourceRange.levelCount = m_iMipCount;
      // subresourceRange.layerCount = 6;
      //
      // vulkan::setImageLayout(pcommandbufferCopy->m_vkcommandbuffer, m_vkimage, VK_IMAGE_LAYOUT_UNDEFINED,
      // VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      //                       subresourceRange);
      //
      // // Copy the cube map faces from the staging buffer to the optimal tiled image
      // vkCmdCopyBufferToImage(pcommandbufferCopy->m_vkcommandbuffer, stagingBuffer, m_vkimage,
      // VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      //                        static_cast<uint32_t>(bufferCopyRegions.size()), bufferCopyRegions.data());
      //
      // // Change texture image layout to shader read after all faces have been copied
      // m_state.m_vkimagelayout = imageLayout;
      // vulkan::setImageLayout(pcommandbufferCopy->m_vkcommandbuffer, m_vkimage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      // imageLayout, subresourceRange);
      //
      // //pdevice->flushCommandBuffer(pcommandbufferCopy->m_vkcommandbuffer, copyQueue);
      //
      // pcontext->endSingleTimeCommands(pcommandbufferCopy);
      //
      // // Create sampler
      // VkSamplerCreateInfo samplerCreateInfo = vkinit::samplerCreateInfo();
      // samplerCreateInfo.magFilter = VK_FILTER_LINEAR;
      // samplerCreateInfo.minFilter = VK_FILTER_LINEAR;
      // samplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
      // samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
      // samplerCreateInfo.addressModeV = samplerCreateInfo.addressModeU;
      // samplerCreateInfo.addressModeW = samplerCreateInfo.addressModeU;
      // samplerCreateInfo.mipLodBias = 0.0f;
      // samplerCreateInfo.maxAnisotropy =
      //    pphysicaldevice->m_vkphysicaldevicefeatures.samplerAnisotropy ?
      //    pphysicaldevice->m_vkphysicaldeviceproperties.limits.maxSamplerAnisotropy
      //                                      : 1.0f;
      // samplerCreateInfo.anisotropyEnable =
      //    pphysicaldevice->m_vkphysicaldevicefeatures.samplerAnisotropy ? VK_TRUE : VK_FALSE;
      // samplerCreateInfo.compareOp = VK_COMPARE_OP_NEVER;
      // samplerCreateInfo.minLod = 0.0f;
      // samplerCreateInfo.maxLod = (::f32)m_iMipCount;
      // samplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
      // VK_CHECK_RESULT(vkCreateSampler(pcontext->logicalDevice(), &samplerCreateInfo, nullptr,
      // &m_vksamplerDedicated));
      //
      // // Create image view
      // VkImageViewCreateInfo viewCreateInfo = vkinit::imageViewCreateInfo();
      // viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
      // viewCreateInfo.format = format;
      // viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
      // viewCreateInfo.subresourceRange.baseMipLevel = 0;
      // viewCreateInfo.subresourceRange.levelCount = m_iMipCount;
      // viewCreateInfo.subresourceRange.baseArrayLayer = 0;
      // viewCreateInfo.subresourceRange.layerCount = 6;
      // viewCreateInfo.image = m_vkimage;
      // VK_CHECK_RESULT(vkCreateImageView(pcontext->logicalDevice(), &viewCreateInfo, nullptr, &m_vkimageview));
      //
      // // Clean up staging resources
      // ktxTexture_Destroy(pktxtexture);
      // vkDestroyBuffer(pcontext->logicalDevice(), stagingBuffer, nullptr);
      // vkFreeMemory(pcontext->logicalDevice(), stagingMemory, nullptr);
      //
      // // Update descriptor image info member that can be used for setting up descriptor sets
      // UpdateDescriptor();
   }


   void texture::set_cube_face(::i32 iFace, ::gpu::shader * pgpushader)
   {
      //   ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;


      //glFramebufferTexture2D(
      //   GL_FRAMEBUFFER,
      //   GL_COLOR_ATTACHMENT0,
      //   GL_TEXTURE_CUBE_MAP_POSITIVE_X + iFace,
      //   m_gluTextureID,
      //   m_iCurrentMip);

      //::opengl::check_error("");


      //glBindTexture(m_gluType, m_gluTextureID);
      //::opengl::check_error("");

   }


   void texture::set_current_mip(::i32 iCurrentMip) { ::gpu::texture::set_current_mip(iCurrentMip); }


   void texture::generate_mipmap(::gpu::command_buffer * pcommandbuffer)
   {

      glBindTexture(m_gluType, m_gluTextureID);
      glTexParameteri(m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glGenerateMipmap(m_gluType);

   }


   void texture::defer_fence()
   {

      if (m_glsyncGpuCommandsCompleteFence)
      {

         return;

      }

      m_glsyncGpuCommandsCompleteFence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
      ::opengl::check_error("glFenceSync");

      if (!m_glsyncGpuCommandsCompleteFence)
      {

         throw ::exception(error_failed, "OpenGL failed to create a texture completion fence");

      }

      glFlush(); // push commands to GPU
      ::opengl::check_error("glFlush after glFenceSync");

   }


   void texture::wait_fence()
   {

      if (!m_glsyncGpuCommandsCompleteFence)
      {

         return;

      }

      auto glsync = m_glsyncGpuCommandsCompleteFence;

      m_glsyncGpuCommandsCompleteFence = nullptr;

      // The producer flushes immediately after creating this fence.  Queue a
      // server-side dependency in the consuming context so subsequent texture
      // use waits for the upload/render without stalling the CPU.  In contrast,
      // GL_TIMEOUT_IGNORED is not a portable glClientWaitSync timeout and causes
      // GL_INVALID_VALUE on some Windows OpenGL drivers.
      try
      {

         glWaitSync(glsync, 0, GL_TIMEOUT_IGNORED);
         ::opengl::check_error("glWaitSync for texture completion");

      }
      catch (...)
      {

         glDeleteSync(glsync);
         throw;

      }

      glDeleteSync(glsync);
      ::opengl::check_error("glDeleteSync for texture completion");

   }


   bool texture::has_pending_fence() const
   {

      return m_glsyncGpuCommandsCompleteFence != nullptr;

   }


} // namespace gpu_opengl
