// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/windowing/window.h"

namespace gpu
{


   class CLASS_DECL_BRED swap_chain :
      virtual public ::acme::windowing::gpu_context_render_frame
   {
   public:


      ::collection::index                                m_iSwapSeed;
      ::collection::index                                m_iCurrentSwapSerial;
      bool                                               m_bWindowInitialized;
      bool                                               m_bSwapChainInitialized;

      ::pointer < ::gpu::context >                       m_pgpucontext;
      ::pointer < ::gpu::renderer >                      m_pgpurenderer;
      ::pointer < ::windowing::window >                  m_pwindowSwapChain;
      int                                                m_iSwapChainIndex;

      ::pointer < ::pointer_array < ::gpu::texture > >   m_ptextureaSwapChain;
      int                                                m_iCurrentSwapChainFrame;
      ::pointer_array<::gpu::semaphore>                  m_gpusemaphoreaWait;



      swap_chain();
      ~swap_chain() override;


      virtual void create_images();

      virtual void defer_check_swap_chain();

      virtual void on_new_swap_chain();

      virtual void initialize_swap_chain_window(::gpu::context * pcontext, ::acme::windowing::window* pwindow);
      virtual void initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer);

      //virtual void endDraw(::gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc);
      //virtual void present(::gpu::texture * pgputexture);
      virtual void present(::gpu::texture * pgputexture);
      virtual void set_present_state();
      virtual void swap_buffers();
      virtual int swap_chain_frame_index();
      virtual int swap_chain_frame_count();
      virtual ::gpu::texture* current_swap_chain_texture();

      void on_gpu_context_render_frame(int w, int h) override;

   };


} // namespace gpu



