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



      virtual ::e_status _create_offscreen_buffer(const ::size& size) override;
      virtual ::e_status resize_offscreen_buffer(const ::size& size) override;
      virtual ::e_status destroy_offscreen_buffer() override;

      virtual ::e_status make_current() override;


      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array & straFragment) override;


   };


} // namespace opengl



