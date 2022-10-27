#pragma once


#include "base/platform/system.h"


namespace bred
{


   class CLASS_DECL_BRED system :
      virtual public ::base::system
   {
   public:


      system();
      ~system() override;


      void common_construct();


      virtual void initialize(::particle * pparticle) override;

      virtual void on_add_session(::apex::session * papexsession) override;


   };


} // namespace bred




