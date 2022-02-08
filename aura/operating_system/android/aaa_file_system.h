#pragma once


namespace android
{


   class CLASS_DECL_AURA file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual void initialize(::object * pobject) override;



      virtual void update_module_path() override;


   };


} // namespace ca2


