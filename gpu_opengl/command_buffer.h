// Created by camilo on 2025-06-30 22:38 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/command_buffer.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL command_buffer :
      virtual public ::gpu::command_buffer
   {
   public:


      command_buffer();
      ~command_buffer() override;


      void draw(int a) override;


   };


} // namespace gpu_opengl



