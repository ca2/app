#pragma once


#include "bred/gpu/swap_chain.h"
#include "gpu_opengl/render_target.h"


namespace gpu_opengl
{


   class swap_chain :
      virtual public ::gpu::swap_chain
   {
   public:


      const_char_pointer m_pszCopyTextureVertexShader;
      const_char_pointer m_pszCopyTextureFragmentShader;
      //int m_iFbo = 0;
      //int m_iFboTex = 0;
      //VkSwapchainKHR                m_vkswapchain;
      //uint32_t                      m_uCurrentSwapChainImage;
      //::pointer < ::gpu::context >  m_pgpucontextSwapChain;
      //GLuint m_VAOFullScreenQuad;
      //GLuint m_VBOFullScreenQuad;
      ::pointer < ::gpu_opengl::texture > m_ptexturePresent;
      //::pointer < ::gpu_opengl::texture > m_ptextureRender;
      ::pointer < ::gpu::shader > m_pshaderPresent;
      ::pointer < ::gpu::shader > m_pshaderRender;
      ::pointer < ::gpu::model_buffer > m_pmodelbufferRender;

      //static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

      //swap_chain(renderer* pgpurenderer, VkExtent2D windowExtent);
      swap_chain();
      ~swap_chain();


///      void initialize_render_target(::gpu::renderer* prenderer, const ::int_size& size, ::pointer <::gpu::render_target>previous) override;


   //   void endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* pgpurendererSrc) override;


      //::gpu::texture* current_texture() override;
      //void present(::gpu::texture* ptexture) override;
      void present(::gpu::texture * pgputexture) override;

      void swap_buffers() override;
      
      void on_gpu_context_render_frame(int w, int h) override;

      virtual ::pointer < ::gpu::shader > create_copy_texture_shader();
      virtual ::gpu::shader * present_shader();
      virtual ::gpu::shader * render_shader(int w, int h);
      virtual void defer_update_swap_chain_textures(const ::int_size & size);

      
   };


}  // namespace gpu_opengl


