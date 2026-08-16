// Created by camilo on 2026-08-03 17:43 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "bred/gpu/window_attachment.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL window_attachment :
      virtual public ::gpu::window_attachment
   {
   public:




      //::pointer< ::gpu::context >m_pgpucontextWindow;


      window_attachment();
      ~window_attachment() override;


      void initialize_gpu_window_attachment(::acme::windowing::window * pwindow) override;


      ::i32 get_frame_index3() override;

      ::i32 get_frame_count() override;



   };


} // namespace draw2d_direct2d



