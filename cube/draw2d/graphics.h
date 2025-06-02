// Created by camilo on 2025-05-31 15:27 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/gpu.h"
#include "aura/graphics/draw2d/graphics.h"


namespace draw2d_gpu
{


   class CLASS_DECL_CUBE graphics :
      virtual public ::draw2d::graphics
   {
   public:


      ::pointer < ::gpu::context >     m_pgpucontext;
      ::gpu::enum_output               m_eoutputOnEndDraw;
      ::pointer < ::gpu::context >     m_pgpucontextOutput;
      ::pointer < ::gpu::frame >       m_pgpuframe;
      ::geometry2d::matrix             m_m1;

      graphics();
      ~graphics() override;


      void initialize(::particle* pparticle) override;
      
      
      void on_begin_draw() override;
      void on_end_draw() override;


      void set_hint_window_output() override;


      void thread_select() override;

      void _set(const ::geometry2d::matrix& matrix);

   };


} // namespace draw2d_gpu



