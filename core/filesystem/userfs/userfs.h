#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::aura::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual ::estatus initialize(::object * pobjectContext) override;

      virtual ::estatus init1() override;


   };



} // namespace userfs



