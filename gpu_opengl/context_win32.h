#pragma once


#include "gpu_opengl/context.h"


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context_win32 :
      virtual public ::opengl::context
   {
   public:



      HGLRC                            m_hrc;
      HDC                              m_hdc;
      HWND                             m_hwnd;
      HDC                              m_hdcGraphics;


      context_win32();
      ~context_win32() override;


      virtual void _create_offscreen_window(const ::size_i32 & size);


      virtual void _create_window_buffer();
      void _create_offscreen_buffer(const ::size_i32& size) override;
      void resize_offscreen_buffer(const ::size_i32& size) override;
      void destroy_offscreen_buffer() override;

      void make_current() override;

      void render();

      string get_shader_version_text() override;

      void _translate_shader(string_array & straFragment) override;

      void swap_buffers() override;


   };


} // namespace opengl



