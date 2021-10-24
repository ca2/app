#pragma once



namespace opengl
{


   class CLASS_DECL_GPU_OPENGL program :
      virtual public ::gpu::program
   {
   public:


      program();
      ~program() override;


      ::e_status create_program(::object * pobject, const string& strVertex, const string& strFragment, const string& strGeometry = "") override;


   };


} // namespace opengl


