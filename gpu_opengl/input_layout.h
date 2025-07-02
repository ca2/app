// From gpu_directx12/input_layout.h by
// camilo on 2025-06-29 08:34 <3ThomasBorregaardSørensen!!
// From gpu_directx11/input_layout.h by
// camilo on 2025-06-29 06:04 <3ThomasBorregaardSørensen!!
// From gpu_vulkan/input_layout.h by camilo on 2025-06-29 03:49 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/input_layout.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL input_layout :
      virtual public ::gpu::input_layout
   {
   public:


      


      input_layout();
      ~input_layout();


      //void on_initialize_input_layout() override;


      void _do_opengl_vao_and_vbo_input_layout(GLuint gluVAO, GLuint gluVBO);


   };


} // namespace gpu_directx11



