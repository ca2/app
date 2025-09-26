// From vk_swapchain by camilo on 2025-05-09 02:01 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "render_target.h"
#include "renderer.h"


namespace gpu_opengl
{

   
   render_target::render_target()
   {

      m_bNeedRebuild = false;

      m_gluDepthStencilTex = 0;

   }


   void render_target::initialize_render_target(::gpu::renderer* pgpurenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous)
   {

      ::gpu::render_target::initialize_render_target(pgpurenderer, size, previous);

   }

      
   void render_target::on_init() 
   {

      createRenderPassImpl();
      createImageViews();
      createRenderPass();
      createDepthResources();
      createFramebuffers();
      createSyncObjects();
      
      m_prendertargetOld = nullptr;

   }


   render_target::~render_target()
   {


   }


   int render_target::get_frame_index()
   {

      return 0;

   }


   void render_target::on_before_begin_render(::gpu::frame* pframe)
   {


   }


   //int render_target::get_image_index() const
   //{
   //   
   //   return m_pgpurenderer->get_frame_index(); 
   //
   //}


   
   void render_target::createRenderPassImpl() 
   {


   }

   
   void render_target::createImageViews() 
   {


   }


   void render_target::createRenderPass() 
   {


   }


   void render_target::createFramebuffers() 
   {


   }


   void render_target::createDepthResources()
   {

      glGenTextures(1, &m_gluDepthStencilTex);
      glBindTexture(GL_TEXTURE_2D, m_gluDepthStencilTex);

      // Allocate storage for a 24-bit depth + 8-bit stencil buffer
      glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 
         m_size.cx(), m_size.cy(),
         0,
         GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

      // Set texture parameters
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      glBindTexture(GL_TEXTURE_2D, 0);


   }


   void render_target::createSyncObjects() 
   {


   }

   

} // namespace gpu_opengl



