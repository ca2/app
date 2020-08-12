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

      virtual ::estatus _create_offscreen_buffer(const ::size& size) override;
      virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      virtual ::estatus destroy_offscreen_buffer() override;

      virtual ::estatus make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



