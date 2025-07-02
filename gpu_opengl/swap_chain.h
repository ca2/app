#pragma once


#include "bred/gpu/swap_chain.h"
#include "gpu_opengl/render_target.h"


namespace gpu_opengl
{


   class swap_chain :
      virtual public ::gpu::swap_chain
   {
   public:


      //VkSwapchainKHR                m_vkswapchain;
      //uint32_t                      m_uCurrentSwapChainImage;
      //::pointer < ::gpu::context >  m_pgpucontextSwapChain;
      //GLuint m_VAOFullScreenQuad;
      //GLuint m_VBOFullScreenQuad;
      ::pointer < ::gpu_opengl::texture > m_ptextureSwapChain;
      ::pointer < ::gpu::shader > m_pshaderCopyTextureOnEndDraw;

      //static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

      //swap_chain(renderer* pgpurenderer, VkExtent2D windowExtent);
      swap_chain();
      ~swap_chain();


///      void initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous) override;


   //   void endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* pgpurendererSrc) override;


      //::gpu::texture* current_texture() override;
      void present(::gpu::texture* ptexture) override;


   };


}  // namespace gpu_opengl


