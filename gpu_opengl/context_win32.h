#pragma once


#include "gpu_opengl/context.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL context_win32 :
      virtual public ::gpu_opengl::context
   {
   public:


      bool                             m_bMesa;
      HGLRC                            m_hrc;
      HDC                              m_hdc;
      HWND                             m_hwnd;
      HDC                              m_hdcGraphics;


      context_win32();
      ~context_win32() override;


      virtual void _create_offscreen_window(const ::int_size & size);

      void defer_create_window_context(::windowing::window * pwindow) override;
      void _defer_create_window_context(::windowing::window * pwindow) override;
      virtual void _create_window_context(::windowing::window * pwindow);

      virtual void _create_window_buffer();
      void _create_offscreen_buffer(const ::int_size& size) override;
      void resize_offscreen_buffer(const ::int_size& size) override;
      void destroy_offscreen_buffer() override;

      void make_current() override;

      bool is_mesa() override;

      void render();

      string get_shader_version_text() override;

      void _translate_shader(string_array & straFragment) override;

      void swap_buffers() override;


   };


} // namespace gpu_opengl



