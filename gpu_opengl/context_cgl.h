//
//  context_cgl.hpp
//  gpu_opengl
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 24/07/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
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
      

      virtual void _create_offscreen_buffer(const ::size_i32& size) override;
      //virtual void resize_offscreen_buffer(const ::size_i32& size) override;
      virtual void destroy_offscreen_buffer() override;

      virtual void make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace opengl



