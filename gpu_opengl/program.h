#pragma once


#include "aura/gpu/gpu/program.h"


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL program :
      virtual public ::gpu::program
   {
   public:


      //__creatable_from_base(program, ::gpu::program);


      program();
      ~program() override;


      void create_program(::object * pobject, const string& strVertex, const string& strFragment, const string& strGeometry = "") override;


   };


} // namespace opengl


