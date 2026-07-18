// From vk_swapchain by camilo on 2025-05-09 01:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/render_target.h"
#include "context.h"

//// directx11 headers
//#include "_gpu_directx11.h"



namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL render_target :
      virtual public ::gpu::render_target
   {
   public:


      //GLuint m_gluDepthStencilTex;

      ::i32_array_base imageAvailable;

      bool  m_bNeedRebuild;

      render_target();
      ~render_target();


      void initialize_render_target(::gpu::renderer* prenderer, const ::i32_size& size, ::pointer <::gpu::render_target>previous) override;

      virtual void on_before_begin_render(::gpu::layer * pgpulayer);



      ::f32 extentAspectRatio() 
      {
         return (::f32) width() / (::f32) height();
      }

      void on_init() override;
      virtual void createRenderPassImpl();
      virtual void createImageViews();
      virtual void createDepthResources();
      virtual void createRenderPass();
      virtual void createFramebuffers();
      virtual void createSyncObjects();


      //::i32 get_frame_index() override;


   };


}  // namespace gpu_opengl



