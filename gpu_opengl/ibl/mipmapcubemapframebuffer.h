// From github:/tristancalderbank/OpenGL-PBR-Renderer/MipmapCubemapFramebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once
#include "gpu/ibl/mipmapcubemapframebuffer.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap. The faces themselves are mipmapped.
       */
      class MipmapCubemapFramebuffer :
         virtual public ::gpu::ibl::MipmapCubemapFramebuffer
      {
      public:


         // unsigned int m_iWidth, m_iHeight;
         // unsigned int m_iMipWidth, m_iMipHeight;
         // unsigned int m_iMipLevel;

         unsigned int m_uFramebufferId;
         unsigned int m_uDepthRenderbufferId;
         unsigned int m_uCubemapTextureId;


         MipmapCubemapFramebuffer();


         ~MipmapCubemapFramebuffer() override;


         //virtual void initialize_MipmapCubemapFramebuffer(unsigned int width, unsigned int height);

         void on_initialize_MipmapCubemapFramebuffer() override;

         void bind() override;


         /**
          * Set the mip level to render with.
          * @param mipLevel
          */
         void setMipLevel(unsigned int level) override;


         // /**
         //  * Get the current width based on the mip level.
         //  * @return
         //  */
         // unsigned int getWidth();
         //
         //
         // /**
         //  * Get the current height based on the mip level.
         //  * @return
         //  */
         // unsigned int getHeight();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         void setCubeFace(unsigned int faceIndex) override;


         unsigned int getCubemapTextureId();

      };


   } // namespace ibl


} // namespace gpu_opengl
