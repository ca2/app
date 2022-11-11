#pragma once


#include "acme/platform/department.h"


namespace fs
{


   class CLASS_DECL_APEX fs :
      virtual public ::acme::department
   {
   public:


      fs();
      ~fs() override;


      virtual void initialize(::particle * pparticle) override;


   };


} // namespace fs



