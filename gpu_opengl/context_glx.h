#pragma once


#include "aura/os/_os.h"
#include <GL/glx.h>
#include <GL/glu.h>


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context_glx :
      virtual public ::opengl::context
   {
   public:

      GLXFBConfig *                    m_pconfig;
      GLXContext                       m_context;
      GLXPbuffer                       m_pbuffer;


      context_glx();
      virtual ~context_glx();


      virtual ::estatus _create_offscreen_buffer(const ::size& size) override;
      virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      virtual ::estatus destroy_offscreen_buffer() override;

      virtual ::estatus make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



