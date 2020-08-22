#pragma once


namespace windows
{


   class CLASS_DECL_BASE print_job :
      virtual public ::user::print_task
   {
   public:


      print_job();
      virtual ~print_job();


      virtual ::estatus     run() override;


   };


} // namespace windows




