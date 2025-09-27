// From github:/tristancalderbank/OpenGL-PBR-Renderer/CubemapFramebuffer.h by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/ibl/cubemapframebuffer.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap.
       */
      class CubemapFramebuffer :
         virtual public ::gpu::ibl::CubemapFramebuffer
      {
      public:


         ///int m_iWidth, m_iHeight;
         unsigned int m_uFramebufferId;
         unsigned int m_uDepthRenderbufferId;
         unsigned int m_uCubemapTextureId;


         CubemapFramebuffer();


         ~CubemapFramebuffer() override;


         //virtual void initialize_CubemapFramebuffer(int width, int height);


         void on_initialize_CubemapFramebuffer() override;

         void bind() override;


         void generateMipmap();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         void setCubeFace(unsigned int index);


         unsigned int getCubemapTextureId();


      };


   } // namespace ibl


} // namespace gpu_opengl
