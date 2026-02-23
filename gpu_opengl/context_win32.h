//
// Created by camilo on 2026-Jan <3ThomasBorregaardSørensen!!
//
#pragma once


#include "gpu_opengl/context.h"

#include "gpu_opengl/wgl_context.h"


namespace gpu_opengl
{




   class CLASS_DECL_GPU_OPENGL context_win32 :
      virtual public ::gpu_opengl::context,
      virtual public wgl_context
   {
   public:



      context_win32();
      ~context_win32() override;


      void destroy() override;


      void _create_window_context(::acme::windowing::window *pwindowParam) override;


      void _create_cpu_buffer(const ::int_size &size) override;


      void assert_there_is_current_context() override;


      void swap_buffers() override;


      virtual void _create_window_buffer();


      void _context_lock() override;
      void _context_unlock() override;


   };

} // namespace gpu_opengl



