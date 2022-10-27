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


      virtual void initialize(::particle * pparticle) ;


   };


} // namespace calculator


