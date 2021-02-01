#pragma once

//#include "aura/os/_os.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context_egl :
      virtual public ::opengl::context
   {
   public:


      EGLDisplay                       m_display;
      EGLConfig                        m_config;
      EGLContext                       m_context;
      EGLSurface                       m_surface;


      context_egl();
      virtual ~context_egl();

      virtual ::e_status _create_offscreen_buffer(const ::size_i32& size) override;
      virtual ::e_status resize_offscreen_buffer(const ::size_i32& size) override;
      virtual ::e_status destroy_offscreen_buffer() override;

      virtual ::e_status make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



