// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_AURA swap_chain :
      virtual public ::particle
   {
   public:


      bool m_bSwapChainInitialized = false;
      //::pointer < ::draw2d_gpu::graphics > m_pgraphics;
      ::pointer < ::gpu::device > m_pgpudevice;
      ::pointer < ::windowing::window > m_pwindow;

      swap_chain();
      ~swap_chain() override;


      virtual void initialize_gpu_swap_chain(::gpu::device* pdevice, ::windowing::window* pwindow);

      virtual void endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc);
      virtual void present();

   };


} // namespace gpu



