#pragma once


namespace windows
{


   class CLASS_DECL_APEX print_job :
      virtual public ::user::print_task
   {
   public:


      print_job();
      virtual ~print_job();


      virtual ::e_status     run() override;


   };


} // namespace windows




