#pragma once


namespace android
{


   class CLASS_DECL_AXIS file_system :
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual ::e_status initialize(::context_object * pcontextobject) override;



      virtual ::e_status update_module_path() override;


   };


} // namespace ca2


