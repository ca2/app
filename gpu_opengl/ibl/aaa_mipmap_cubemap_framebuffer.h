// From github:/tristancalderbank/OpenGL-PBR-Renderer/mipmap_cubemap_framebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once
#include "gpu/ibl/aaa_mipmap_cubemap_framebuffer.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap. The faces themselves are mipmapped.
       */
      class aaa_mipmap_cubemap_framebuffer :
         virtual public ::gpu::ibl::aaa_mipmap_cubemap_framebuffer
      {
      public:


         // unsigned int m_iWidth, m_iHeight;
         // unsigned int m_iMipWidth, m_iMipHeight;
         // unsigned int m_iMipLevel;

         // unsigned int m_uFramebufferId;
         // unsigned int m_uDepthRenderbufferId;
         // unsigned int m_uCubemapTextureId;


         aaa_mipmap_cubemap_framebuffer();


         ~aaa_mipmap_cubemap_framebuffer() override;


         //virtual void initialize_mipmap_cubemap_framebuffer(unsigned int width, unsigned int height);

         void on_initialize_mipmap_cubemap_framebuffer() override;

         void bind() override;


         /**
          * Set the mip level to render with.
          * @param mipLevel
          */
         void set_current_mip(int iCurrentMip) override;


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
         void set_cube_face(int iFace) override;


         unsigned int getCubemapTextureId();

      };


   } // namespace ibl


} // namespace gpu_opengl
