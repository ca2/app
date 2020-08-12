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



      virtual ::estatus _create_offscreen_buffer(const ::size& size) override;
      virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      virtual ::estatus destroy_offscreen_buffer() override;

      virtual ::estatus make_current() override;


      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array & straFragment) override;


   };


} // namespace opengl



