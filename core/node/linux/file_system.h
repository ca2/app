#pragma once


namespace linux
{


   class CLASS_DECL_CORE file_system:
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual ::estatus init_system() override;


      virtual ::estatus update_module_path() override;


   };


} // namespace linux



