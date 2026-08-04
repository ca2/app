// Created by camilo on 2026-08-03 17:43 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "bred/gpu/draw2d_window_attachment.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL draw2d_window_attachment :
      virtual public ::gpu::draw2d_window_attachment
   {
   public:




      //::pointer< ::gpu::context >m_pgpucontextWindow;


      draw2d_window_attachment();
      ~draw2d_window_attachment() override;


      void initialize_window_attachment(::windowing::window * pwindow) override;


      ::i32 get_frame_index3() override;

      ::i32 get_frame_count() override;



   };


} // namespace draw2d_direct2d



