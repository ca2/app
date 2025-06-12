// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "device.h"
#include "swap_chain.h"
#include "aura/windowing/window.h"


namespace gpu
{



   swap_chain::swap_chain()
   {

   }
      
   
   swap_chain::~swap_chain()
   {

   }


   void swap_chain::initialize_gpu_swap_chain(::gpu::device* pdevice, ::windowing::window* pwindow)
   {

      ASSERT(pdevice->m_edevicetarget == ::gpu::e_device_target_swap_chain);

      m_pgpudevice = pdevice;

      m_pwindow = pwindow;

      m_bSwapChainInitialized = true;

   }


   void swap_chain::endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc)
   {

      ASSERT(m_pgpudevice->m_edevicetarget == ::gpu::e_device_target_swap_chain);

   }


   void swap_chain::present()
   {


   }


} // namespace direct2d



