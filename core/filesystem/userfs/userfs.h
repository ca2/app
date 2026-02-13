#pragma once


#include "acme/platform/department.h"


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::platform::department
   {
   public:


      userfs();
      ~userfs() override;

      virtual void initialize(::particle * pparticle) override;

      virtual void init1() override;


   };



} // namespace userfs



