// Created by camilo on 2025-05-31 15:27 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/gpu.h"
#include "aura/graphics/draw2d/graphics.h"
#include "bred/gpu/compositor.h"


namespace draw2d_gpu
{


   class CLASS_DECL_BRED graphics :
      virtual public ::draw2d::graphics,
      virtual public ::gpu::compositor
   {
   public:


      //::pointer < ::gpu::context >           m_pgpucontextDraw2d;
      //::gpu::enum_output                     m_eoutputOnEndDraw;
      //::pointer < ::gpu::context >           m_pgpucontextOutput;
      ::pointer < ::gpu::frame >             m_pgpuframe;
      ::geometry2d::matrix                   m_m1;
      //::pointer < ::draw2d_gpu::end_draw >   m_penddraw;


      graphics();
      ~graphics() override;


      void initialize(::particle* pparticle) override;
      bool _is_ok() const override;
      
      void on_begin_draw() override;
      void on_end_draw() override;


      //void start_gpu_layer() override;
      //void end_gpu_layer() override;


      //virtual ::gpu::renderer* end_draw_renderer_output();


      //virtual void create_end_draw();


      //void set_hint_window_output() override;


      void thread_select() override;

      void _set(const ::geometry2d::matrix& matrix);

      void do_on_context(const ::procedure& procedure) override;
 
      ///void create_offscreen_graphics_for_swap_chain_blitting(::user::interaction* puserinteraction, const ::int_size& size = {}) override;
      void create_for_window_draw2d(::user::interaction * puserinteraction, const ::int_size& size) override;


      virtual void bind_draw2d_compositor();
      virtual void soft_unbind_draw2d_compositor();


   };


} // namespace gpu



