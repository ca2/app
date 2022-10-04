//
//  context_fbo.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 25/07/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#pragma once


#include "context.h"


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL context_fbo :
      virtual public ::opengl::context
   {
   public:

      CGLContextObj           m_context;
      CGLContextObj           m_contextOld;
      GLuint                  m_renderbuffer;
      GLuint                  m_framebuffer;


      context_fbo();
      ~context_fbo() override;
      
      void lock_context() override;
      void unlock_context() override;

      void _create_offscreen_buffer(const ::size_i32& size) override;
      //virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      void destroy_offscreen_buffer() override;

      void make_current() override;

      string get_shader_version_text() override;

      void _translate_shader(string_array& stra) override;

      void render() override;
      
      void start_drawing() override;
      
      void prepare_for_gpu_read() override;
      
      void resize_offscreen_buffer(const ::size_i32& size) override;
      

   };


} // namespace opengl



