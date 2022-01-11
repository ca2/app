//
//  context_fbo.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Tsumanuma on 25/07/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#pragma once


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
      virtual ~context_fbo();
      
      virtual void lock_context() override;
      virtual void unlock_context() override;

      virtual void _create_offscreen_buffer(const ::size_i32& size) override;
      //virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      virtual void destroy_offscreen_buffer() override;

      virtual void make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;

      virtual void render() override;
      
      virtual void start() override;
      
      virtual void prepare_for_gpu_read() override;
      
      virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      

   };


} // namespace opengl



