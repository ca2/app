// From github:/tristancalderbank/OpenGL-PBR-Renderer/cubemap_framebuffer.h by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/ibl/cubemap_framebuffer.h"


namespace gpu_opengl
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap.
       */
      class cubemap_framebuffer :
         virtual public ::gpu::ibl::cubemap_framebuffer
      {
      public:



         ///::i32 m_iWidth, m_iHeight;
         //::u32 m_uFramebufferId;
         //::u32 m_uDepthRenderbufferId;
         //::u32 m_uCubemapTextureId;




         cubemap_framebuffer();


         ~cubemap_framebuffer() override;


         //virtual void initialize_cubemap_framebuffer(::i32 width, ::i32 height);


         void on_initialize_cubemap_framebuffer() override;

         void bind(::gpu::command_buffer *pgpucommandbuffer) override;


         void generateMipmap();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         void setCubeFace(::u32 index, ::gpu::shader * pgpushader) override;


         ::u32 getCubemapTextureId();


      };


   } // namespace ibl


} // namespace gpu_opengl
