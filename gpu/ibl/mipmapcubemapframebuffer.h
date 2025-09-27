// From github:/tristancalderbank/OpenGL-PBR-Renderer/MipmapCubemapFramebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   namespace ibl
   {
      /**
       * Framebuffer for rendering to faces of a cubemap. The faces themselves are mipmapped.
       */
      class MipmapCubemapFramebuffer :
         virtual public ::particle
      {
      public:


         unsigned int m_uWidth, m_uHeight;
         unsigned int m_uMipWidth, m_uMipHeight;
         unsigned int m_uMipLevel;

         // unsigned int m_uFramebufferId;
         // unsigned int m_uDepthRenderbufferId;
         // unsigned int m_uCubemapTextureId;


         MipmapCubemapFramebuffer();


         ~MipmapCubemapFramebuffer() override;


         virtual void initialize_MipmapCubemapFramebuffer(unsigned int width, unsigned int height);
         virtual void on_initialize_MipmapCubemapFramebuffer();

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
