// From github:/tristancalderbank/OpenGL-PBR-Renderer/brdf_convolution_framebuffer.h by
// camilo on 2025-09-26 19:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/graphics3d/scene_object.h"


namespace gpu
{


   namespace ibl
   {

      /**
       * Framebuffer for rendering brdf convolution map.
       */
      class CLASS_DECL_GPU brdf_convolution_framebuffer :
         virtual public ::graphics3d::scene_object
      {
      public:


         //::u32 m_uWidth, m_uHeight;

         ::pointer < ::gpu::texture > m_ptexture;

         // ::u32 m_uFramebufferId;
         // ::u32 m_uDepthRenderbufferId;
         // ::u32 m_uColorTextureId;

         brdf_convolution_framebuffer();


         ~brdf_convolution_framebuffer() override;


         virtual void initialize_BrdfConvolutionFramebuffer(::graphics3d::scene_base * pscenebase, ::u32 width, ::u32 height);


         virtual void on_initialize_BrdfConvolutionFramebuffer();


         /**
          * Activate this pframebuffer for drawing.
          */
         virtual void bind();


         /**
          * Get the width.
          * @return
          */
         ::u32 getWidth();


         /**
          * Get the height.
          * @return
          */
         ::u32 getHeight();


         /**
          * Get the GL color texture id.
          * @return
          */
         //::u32 getColorTextureId();

      };


   } // namespace ibl


} // namespace gpu
