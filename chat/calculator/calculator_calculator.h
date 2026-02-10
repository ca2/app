#pragma once


namespace calculator
{


   class calculator;


   class CLASS_DECL_CA2_MATH calculator :
      virtual public ::platform::department
   {
   public:


      calculator(::particle * pparticle);
      virtual ~calculator();


      bool initialize();


   };


} // namespace calculator


