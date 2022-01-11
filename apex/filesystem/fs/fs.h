#pragma once


namespace fs
{


   class CLASS_DECL_APEX fs :
      virtual public ::acme::department
   {
   public:


      fs();
      virtual ~fs();


      virtual void initialize(::object * pobject) override;


   };


} // namespace fs



