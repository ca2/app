//
//  context_cgl.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/07/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


#include "context.h"

#include <OpenGL/OpenGL.h>

namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context_cgl :
      virtual public ::opengl::context
   {
   public:

      
      CGLPBufferObj                    m_pbuffer;
      CGLContextObj                    m_context;
      CGLContextObj                    m_contextOld;


      context_cgl();
      virtual ~context_cgl();
      

      virtual void _create_cpu_buffer(const ::int_size& size) override;
      //virtual void resize_offscreen_buffer(const ::int_size& size) override;
      virtual void destroy_cpu_buffer() override;

      virtual void defer_make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array_base& stra) override;


   };


} // namespace opengl



