#pragma once


namespace fs
{


   class CLASS_DECL_APEX fs :
      virtual public ::acme::department
   {
   public:


      fs();
      virtual ~fs();


      virtual ::e_status initialize(::object * pobject) override;


   };


} // namespace fs



