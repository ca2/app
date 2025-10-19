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


         //unsigned int m_uWidth, m_uHeight;
         //unsigned int m_uMipWidth, m_uMipHeight;
         //unsigned int m_uMipLevel;
         unsigned int m_uCurrentMip;
         unsigned int m_uCurrentFace;

         ::pointer < ::gpu::texture > m_ptexture;

         // unsigned int m_uFramebufferId;
         // unsigned int m_uDepthRenderbufferId;
         // unsigned int m_uCubemapTextureId;


         mipmap_cubemap_framebuffer();


         ~mipmap_cubemap_framebuffer() override;


         virtual void initialize_mipmap_cubemap_framebuffer(::graphics3d::scene_base * pscenebase, unsigned int width, unsigned int height);
         virtual void on_initialize_mipmap_cubemap_framebuffer();

         virtual void bind();


         /**
          * Set the mip level to render with.
          * @param mipLevel
          */
         virtual void setMipLevel(unsigned int level);


         /**
          * Get the current width based on the mip level.
          * @return
          */
         virtual unsigned int getWidth();


         /**
          * Get the current height based on the mip level.
          * @return
          */
         virtual unsigned int getHeight();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         virtual void setCubeFace(unsigned int faceIndex);


         //unsigned int getCubemapTextureId();

      };


   } // namespace ibl


} // namespace gpu
