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


         // ::u32 m_iWidth, m_iHeight;
         // ::u32 m_iMipWidth, m_iMipHeight;
         // ::u32 m_iMipLevel;

         // ::u32 m_uFramebufferId;
         // ::u32 m_uDepthRenderbufferId;
         // ::u32 m_uCubemapTextureId;


         aaa_mipmap_cubemap_framebuffer();


         ~aaa_mipmap_cubemap_framebuffer() override;


         //virtual void initialize_mipmap_cubemap_framebuffer(::u32 width, ::u32 height);

         void on_initialize_mipmap_cubemap_framebuffer() override;

         void bind() override;


         /**
          * Set the mip level to render with.
          * @param mipLevel
          */
         void set_current_mip(::i32 iCurrentMip) override;


         // /**
         //  * Get the current width based on the mip level.
         //  * @return
         //  */
         // ::u32 getWidth();
         //
         //
         // /**
         //  * Get the current height based on the mip level.
         //  * @return
         //  */
         // ::u32 getHeight();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         void set_cube_face(::i32 iFace) override;


         ::u32 getCubemapTextureId();

      };


   } // namespace ibl


} // namespace gpu_opengl
