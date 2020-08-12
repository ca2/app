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
      
      virtual ::estatus lock_context() override;
      virtual ::estatus unlock_context() override;

      virtual ::estatus _create_offscreen_buffer(const ::size& size) override;
      //virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      virtual ::estatus destroy_offscreen_buffer() override;

      virtual ::estatus make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;

      virtual ::estatus render() override;
      
      virtual ::estatus start() override;
      
      virtual ::estatus prepare_for_gpu_read() override;
      
      virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      

   };


} // namespace opengl



