// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "renderer.h"
#include "swap_chain.h"
#include "aura/windowing/window.h"


namespace gpu
{


   swap_chain::swap_chain()
   {

      m_iCurrentSwapChainFrame = 0;

      m_bWindowInitialized = false;
      m_bSwapChainInitialized = false;

   }
      
   
   swap_chain::~swap_chain()
   {

   }


   void swap_chain::create_images()
   {


   }


   void swap_chain::defer_check_swap_chain()
   {

      if (::is_set(m_ptextureaSwapChain) && m_iSwapSeed == m_iCurrentSwapSerial)
      {

         return;

      }

      m_iCurrentSwapSerial = m_iSwapSeed;

      on_new_swap_chain();

   }


   void swap_chain::on_new_swap_chain()
   {

      create_images();

   }


   void swap_chain::initialize_swap_chain_window(::gpu::context * pgpucontext, ::acme::windowing::window* pwindow)
   {

      ASSERT(pgpucontext && pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpucontext = pgpucontext;

      m_pwindowSwapChain = pwindow;

      m_bWindowInitialized = true;

      ::string strType = ::type(pwindow->m_pacmeuserinteraction).name();

      const char *pszType = strType.c_str();

      information("initialize_swap_chain_window {}", pszType);

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      ASSERT(m_bWindowInitialized && m_pwindowSwapChain);

      ASSERT(pgpurenderer->m_pgpucontext == m_pgpucontext
      && m_pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::present()
   {


   }


   void swap_chain::set_present_state()
   {


   }


   void swap_chain::swap_buffers()
   {


   }


   int swap_chain::swap_chain_frame_index()
   {

      return m_iCurrentSwapChainFrame;

   }


   int swap_chain::swap_chain_frame_count()
   {

      return -1;

   }


   ::gpu::texture* swap_chain::current_swap_chain_texture()
   {

      defer_check_swap_chain();

      return m_ptextureaSwapChain->element_at(m_iCurrentSwapChainFrame);

   }



void swap_chain::on_gpu_context_render_frame(int w, int h)
{
   
   
}

} // namespace direct2d



