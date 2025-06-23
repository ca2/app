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

      m_bWindowInitialized = false;
      m_bSwapChainInitialized = false;

   }
      
   
   swap_chain::~swap_chain()
   {

   }


   void swap_chain::initialize_swap_chain_window(::gpu::device * pgpudevice, ::windowing::window* pwindow)
   {

      ASSERT(pgpudevice && pgpudevice->m_edevicetarget == ::gpu::e_device_target_swap_chain);

      m_pgpudevice = pgpudevice;

      m_pwindow = pwindow;

      m_bWindowInitialized = true;

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer)
   {

      ASSERT(m_bWindowInitialized && m_pwindow);

      ASSERT(pgpurenderer->m_pgpucontext->m_pgpudevice == m_pgpudevice
      && m_pgpudevice->m_edevicetarget == ::gpu::e_device_target_swap_chain);

      m_pgpurenderer = pgpurenderer;

      m_bSwapChainInitialized = true;

   }


   //void swap_chain::endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc)
   //{

   //   ASSERT(m_pgpudevice->m_edevicetarget == ::gpu::e_device_target_swap_chain);

   //}


   void swap_chain::present(::gpu::texture * pgputexture)
   {


   }


   void swap_chain::set_present_state()
   {


   }


   void swap_chain::swap_buffers()
   {


   }


   void swap_chain::get_new_swap_chain_index()
   {


   }


   //::gpu::texture* swap_chain::current_texture()
   //{

   //   return nullptr;

   //}


} // namespace direct2d



