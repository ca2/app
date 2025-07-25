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


   void swap_chain::initialize_swap_chain_window(::gpu::context * pgpucontext, ::windowing::window* pwindow)
   {

      ASSERT(pgpucontext && pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpucontext = pgpucontext;

      m_pwindow = pwindow;

      m_bWindowInitialized = true;

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      ASSERT(m_bWindowInitialized && m_pwindow);

      ASSERT(pgpurenderer->m_pgpucontext == m_pgpucontext
      && m_pgpucontext->m_etype == ::gpu::context::e_type_window);

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::present(::gpu::texture * pgputexture)
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


   ::gpu::texture* swap_chain::current_swap_chain_texture()
   {

      if (!m_ptextureaSwapChain)
      {

         create_images();

      }

      return m_ptextureaSwapChain->element_at(m_iCurrentSwapChainFrame);

   }


} // namespace direct2d



