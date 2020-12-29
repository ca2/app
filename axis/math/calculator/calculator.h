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


      virtual ::e_status initialize(::layered * pobjectContext) ;


   };


} // namespace calculator


