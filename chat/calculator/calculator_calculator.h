#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CA2_MATH calculator :
      virtual public ::acme::department
   {
   public:


      calculator(::object * pobject);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


