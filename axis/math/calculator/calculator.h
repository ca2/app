#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_AXIS calculator :
      virtual public ::apex::department
   {
   public:


      calculator();
      virtual ~calculator();


      virtual ::estatus initialize(::layered * pobjectContext) ;


   };


} // namespace calculator


