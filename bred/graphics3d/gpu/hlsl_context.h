// Created by camilo on 2025-07-05 07:12 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context.h"


namespace gpu
{


   class CLASS_DECL_BRED hlsl_context :
      virtual public ::gpu::context
   {
   public:


      hlsl_context();
      ~hlsl_context() override;



      ::memory rectangle_shader_vert() override;
      ::memory rectangle_shader_frag() override;


      //void white_to_color_sampler_shader_setup(gpu::shader* pshader) override;
      ::memory white_to_color_sampler_vert() override;
      ::memory white_to_color_sampler_frag() override;


   };


} // namespace gpu



