#pragma once


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
      virtual ~context_win32();



      virtual void _create_offscreen_buffer(const ::size_i32& size) override;
      virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      virtual void destroy_offscreen_buffer() override;

      virtual void make_current() override;


      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array & straFragment) override;


   };


} // namespace opengl



