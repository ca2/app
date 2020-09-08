#pragma once


namespace fs
{


   class CLASS_DECL_APEX fs :
      virtual public ::apex::department
   {
   public:


      fs();
      virtual ~fs();


      virtual ::estatus initialize(::object * pobjectContext) override;


   };


} // namespace fs



