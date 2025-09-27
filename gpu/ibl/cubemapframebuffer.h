// From github:/tristancalderbank/OpenGL-PBR-Renderer/CubemapFramebuffer.h by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap.
       */
      class CubemapFramebuffer :
         virtual public ::particle
      {
      public:


         int m_uWidth, m_uHeight;
         // unsigned int m_uFramebufferId;
         // unsigned int m_uDepthRenderbufferId;
         // unsigned int m_uCubemapTextureId;

         CubemapFramebuffer();


         ~CubemapFramebuffer() override;


         virtual void initialize_CubemapFramebuffer(int width, int height);


         virtual void on_initialize_CubemapFramebuffer();


         virtual void bind();


         virtual void generateMipmap();


         /**
          * Set which cube face texture to render to.
          * @param index
          */
         virtual void setCubeFace(unsigned int index);


         //virtual unsigned int getCubemapTextureId();


      };


   } // namespace ibl


} // namespace gpu
