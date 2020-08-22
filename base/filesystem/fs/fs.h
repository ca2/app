#pragma once


namespace fs
{


   class CLASS_DECL_AURA fs :
      virtual public ::aura::department
   {
   public:


      fs();
      virtual ~fs();


      virtual ::estatus initialize(::object * pobjectContext) override;


   };


} // namespace fs



