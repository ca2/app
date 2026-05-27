// From github:/tristancalderbank/OpenGL-PBR-Renderer/mipmap_cubemap_framebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/graphics3d/scene_object.h"


namespace gpu
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap. The faces themselves are mipmapped.
       */
      class CLASS_DECL_GPU mipmap_cubemap_framebuffer : 
         virtual public ::graphics3d::scene_object
      {
      public:


         //::u32 m_uWidth, m_uHeight;
         //::u32 m_uMipWidth, m_uMipHeight;
         //::u32 m_uMipLevel;

         ::pointer < ::gpu::texture > m_ptexture;

         // ::u32 m_uFramebufferId;
         // ::u32 m_uDepthRenderbufferId;
         // ::u32 m_uCubemapTextureId;


         mipmap_cubemap_framebuffer();


         ~mipmap_cubemap_framebuffer() override;


         virtual void initialize_mipmap_cubemap_framebuffer(::graphics3d::scene_base * pscenebase, ::i32 iWidth, ::i32 iHeight);
         virtual void on_initialize_mipmap_cubemap_framebuffer();

         virtual void bind();


         /**
          * Set the mip level to render with.
          * @param mipLevel
          */
         virtual void set_current_mip(::i32 level);


         /**
          * Get the current width based on the mip level.
          * @return
          */
         virtual ::i32 mip_width();


         /**
          * Get the current height based on the mip level.
          * @return
          */
         virtual ::i32 mip_height();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         virtual void set_cube_face(::i32 iFace);


         //::u32 getCubemapTextureId();

      };


   } // namespace ibl


} // namespace gpu
