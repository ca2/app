//
//  context_cgl.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/07/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


#include "gpu_opengl/context.h"
#include "_gpu_opengl.h"
//#include <OpenGL/OpenGL.h>
//#include <CGL/CGL.h>

namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL context_cgl :
      virtual public ::gpu_opengl::context
   {
   public:

      
      //CGLPBufferObj                    m_pbuffer;
      CGLContextObj                    m_context;
      CGLContextObj                    m_contextOld;

      int m_iFbo;
      int m_iTex;
      ::int_size m_sizeFbo;

      context_cgl();
      virtual ~context_cgl();
      

      virtual void _create_cpu_buffer(const ::int_size& size) override;
      //virtual void resize_offscreen_buffer(const ::int_size& size) override;
      virtual void destroy_cpu_buffer() override;

      virtual void _context_lock() override;
      
      virtual void _context_unlock() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array_base& stra) override;
      void _create_window_context(::acme::windowing::window* pacmewindowingwindow) override;

      virtual void _defer_update_render_frame_buffer();
      
      virtual void _defer_update_render_frame_buffer_unlocked();
      void on_cube_map_face_image(::image::image * pimage) override;
   };


} // namespace gpu_opengl



