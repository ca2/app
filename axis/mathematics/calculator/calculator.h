#pragma once


#include "acme/platform/department.h"


namespace calculator
{


   class calculator;


   class CLASS_DECL_AXIS calculator :
      virtual public ::acme::department
   {
   public:


      calculator();
      ~calculator() override;


      virtual void initialize(::particle * pparticle) ;


   };


} // namespace calculator


