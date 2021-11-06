#pragma once


namespace linux
{


   class CLASS_DECL_CORE file_system:
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status init_system() override;


      virtual ::e_status update_module_path() override;


   };


} // namespace linux



