#pragma once


namespace fs
{


   class CLASS_DECL_AQUA fs :
      virtual public ::aqua::department
   {
   public:


      fs();
      virtual ~fs();


      virtual ::estatus initialize(::object * pobjectContext) override;


   };


} // namespace fs



