#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_AXIS calculator :
      virtual public ::acme::department
   {
   public:


      calculator();
      virtual ~calculator();


      virtual ::e_status initialize(::object * pobject) ;


   };


} // namespace calculator


