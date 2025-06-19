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


      GLuint m_gluDepthStencilTex;

      ::int_array imageAvailable;

      bool  m_bNeedRebuild;

      render_target();
      ~render_target();


      void initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous) override;

      virtual void on_before_begin_render(::gpu::frame* pframe);



      float extentAspectRatio() 
      {
         return (float) width() / (float) height();
      }

      void on_init() override;
      virtual void createRenderPassImpl();
      virtual void createImageViews();
      virtual void createDepthResources();
      virtual void createRenderPass();
      virtual void createFramebuffers();
      virtual void createSyncObjects();


   };


}  // namespace gpu_opengl



