// From vk_swapchain by camilo on 2025-05-09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "offscreen_render_target.h"
//#include "initializers.h"
//#include "physical_device.h"
#include "renderer.h"
#include "texture.h"

//using namespace directx11;


namespace gpu_opengl
{


   offscreen_render_target::offscreen_render_target()
   {


   }


   offscreen_render_target::~offscreen_render_target()
   {


   }



   void offscreen_render_target::initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
   {

      ::gpu::render_target::initialize_render_target(pgpurenderer, size, previous);
   
   }


   void offscreen_render_target::on_init()
   {

      create_images();
      createRenderPassImpl();
      createImageViews();
      createRenderPass();
      createDepthResources();
      createFramebuffers();
      createSyncObjects();

   }


   void offscreen_render_target::defer_resize(const ::int_size& size)
   {


   }


   void offscreen_render_target::createRenderPassImpl()
   {

     
   }


   void offscreen_render_target::createImageViews()
   {

      render_target::createImageViews();


   }


   void offscreen_render_target::createRenderPass()
   {


   }


   void offscreen_render_target::createFramebuffers()
   {

      render_target::createFramebuffers();

   }


   void offscreen_render_target::createDepthResources()
   {
   
      render_target::createDepthResources();

   }


   void offscreen_render_target::createSyncObjects()
   {

      render_target::createSyncObjects();

   }


} // namespace gpu_opengl



