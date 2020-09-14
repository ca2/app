#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CA2_MATH calculator :
      virtual public ::apex::department
   {
   public:


      calculator(::layered * pobjectContext);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


