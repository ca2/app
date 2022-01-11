#pragma once


#include "aura/operating_system.h"


#include "aura/node/operating_system/_operating_system.h"
//#include "windowing_x11/_.h"
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


      virtual void _create_offscreen_buffer(const ::size_i32& size) override;
      virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      virtual void destroy_offscreen_buffer() override;

      virtual void make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



