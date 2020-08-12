#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CORE calculator :
      virtual public ::aura::department
   {
   public:


      calculator();
      virtual ~calculator();


      virtual ::estatus initialize(::object * pobjectContext) ;


   };


} // namespace calculator


