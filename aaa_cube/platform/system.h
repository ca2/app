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


      //void on_set_platform() override;


      //virtual void initialize(::particle * pparticle) override;

      //virtual void on_add_session(::platform::session * pacmesession) override;


   };


} // namespace bred




