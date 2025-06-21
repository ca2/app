// Created by camilo on 2025-06-10 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED swap_chain :
      virtual public ::particle
   {
   public:


      bool                                m_bWindowInitialized;
      bool                                m_bSwapChainInitialized;

      ::pointer < ::gpu::device >         m_pgpudevice;
      ::pointer < ::gpu::renderer >       m_pgpurenderer;
      ::pointer < ::windowing::window >   m_pwindow;

      swap_chain();
      ~swap_chain() override;


      virtual void initialize_swap_chain_window(::gpu::device * pgpudevice, ::windowing::window* pwindow);
      virtual void initialize_gpu_swap_chain(::gpu::renderer * pgpurenderer);

      //virtual void endDraw(::draw2d_gpu::graphics* pgraphics, ::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc);
      virtual void present(::gpu::texture * pgputexture);

      //virtual ::gpu::texture* current_texture();

   };


} // namespace gpu



