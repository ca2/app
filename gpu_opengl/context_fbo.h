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
      GL::u32                  m_renderbuffer;
      GL::u32                  m_framebuffer;


      context_fbo();
      virtual ~context_fbo();
      
      virtual ::e_status lock_context() override;
      virtual ::e_status unlock_context() override;

      virtual ::e_status _create_offscreen_buffer(const ::size_i32& size) override;
      //virtual ::e_status resize_offscreen_buffer(const ::size_i32& size) override;
      virtual ::e_status destroy_offscreen_buffer() override;

      virtual ::e_status make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;

      virtual ::e_status render() override;
      
      virtual ::e_status start() override;
      
      virtual ::e_status prepare_for_gpu_read() override;
      
      virtual ::e_status resize_offscreen_buffer(const ::size_i32& size) override;
      

   };


} // namespace opengl



