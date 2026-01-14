//
//  context_cgl.hpp
//  gpu_opengl
//
//  From context_cgl.h by camilo on 2025-12-26 03:28 <3ThomasBorregaardSørensen!!
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


#include "gpu_opengl/context.h"
#include "_gpu_opengl.h"
//#include <OpenGL/OpenGL.h>
//#include <CGL/CGL.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL context_egl :
      virtual public ::gpu_opengl::context
   {
   public:

      
      // CGLPBufferObj                    m_pbuffer;
      // CGLContextObj                    m_context;
      // CGLContextObj                    m_contextOld;
      EGLContext                       m_eglcontext;
      EGLSurface                       m_eglsurface;
      bool                             m_bEGLWindowSurface;


      context_egl();
      ~context_egl() override;


      virtual void __create_egl_context(bool bForWindow);
      virtual void __create_egl_window_surface(::acme::windowing::window* pacmewindowingwindow);
      virtual void __create_egl_pbuffer_surface(const ::int_size & size);
      virtual void __on_after_egl_context_and_surface_creation();
      //void _create_window_buffer() override;
      //void _create_offscreen_window(const ::int_size &size) override;
      void _create_window_context(::acme::windowing::window* pacmewindwoingwindow) override;
      void _create_cpu_buffer(const ::int_size& size) override;
      //void resize_offscreen_buffer(const ::int_size& size) override;
      void destroy_cpu_buffer() override;

      //void defer_make_current() override;
      //void defer_release_current() override;

      string get_shader_version_text() override;

      void _translate_shader(string_array_base& stra) override;

      void assert_there_is_current_context() override;

      void _context_lock() override;
      void _context_unlock() override;


      void swap_buffers() override;

   };


} // namespace gpu_opengl



