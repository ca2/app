#pragma once


namespace fs
{


   class CLASS_DECL_APEX fs :
      virtual public ::apex::department
   {
   public:


      fs();
      virtual ~fs();


      virtual ::e_status initialize(::layered * pobjectContext) override;


   };


} // namespace fs



