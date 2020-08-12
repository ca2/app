#pragma once



namespace opengl
{


   class CLASS_DECL_GPU_OPENGL program :
      virtual public ::gpu::program
   {
   public:


      program();
      virtual ~program();


      virtual ::estatus create_program(const string& strVertex, const string& strFragment, const string& strGeometry = "") override;


   };


} // namespace opengl


