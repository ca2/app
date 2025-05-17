//
//  context_cgl.hpp
//  gpu_vulkan
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 24/07/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


#include "context.h"

#include <Vulkan/Vulkan.h>

namespace vulkan
{


   class CLASS_DECL_GPU_VULKAN context_cgl :
      virtual public ::vulkan::context
   {
   public:

      
      CGLPBufferObj                    m_pbuffer;
      CGLContextObj                    m_context;
      CGLContextObj                    m_contextOld;


      context_cgl();
      virtual ~context_cgl();
      

      virtual void _create_offscreen_buffer(const ::int_size& size) override;
      //virtual void resize_offscreen_buffer(const ::int_size& size) override;
      virtual void destroy_offscreen_buffer() override;

      virtual void make_current() override;

      virtual string get_shader_version_text() override;

      virtual void _translate_shader(string_array& stra) override;


   };


} // namespace vulkan



