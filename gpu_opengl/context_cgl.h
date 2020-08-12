//
//  context_cgl.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Tsumanuma on 24/07/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#pragma once


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
      

      virtual ::estatus _create_offscreen_buffer(const ::size& size) override;
      //virtual ::estatus resize_offscreen_buffer(const ::size& size) override;
      virtual ::estatus destroy_offscreen_buffer() override;

      virtual ::estatus make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



