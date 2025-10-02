// From github:/tristancalderbank/OpenGL-PBR-Renderer/brdf_convolution_framebuffer.h by
// camilo on 2025-09-26 19:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "gpu/ibl/brdf_convolution_framebuffer.h"


namespace gpu_opengl
{


   namespace ibl
   {

      /**
       * Framebuffer for rendering brdf convolution map.
       */
      class brdf_convolution_framebuffer :
         virtual public ::gpu::ibl::brdf_convolution_framebuffer
      {

public:


         // unsigned int width, height;

         // unsigned int m_uFramebufferId;
         // unsigned int m_uDepthRenderbufferId;
         // unsigned int m_uColorTextureId;


         brdf_convolution_framebuffer();


         ~brdf_convolution_framebuffer() override;


         ///virtual void initialize_BrdfConvolutionFramebuffer(unsigned int width, unsigned int height);

         void on_initialize_BrdfConvolutionFramebuffer() override;
         /**
          * Activate this framebuffer for drawing.
          */
         void bind() override;


         /**
          * Get the width.
          * @return
          */
         //unsigned int getWidth();


         /**
          * Get the height.
          * @return
          */
         //unsigned int getHeight();


         /**
          * Get the GL color texture id.
          * @return
          */
         unsigned int getColorTextureId();


      };


   } // namespace ibl


} // namespace gpu_opengl
