#pragma once


#include "base/platform/session.h"


namespace bred
{


   class CLASS_DECL_BRED session :
      virtual public ::base::session
   {
   public:


      session();
      ~session() override;


      void common_construct();


      void initialize(::particle * pparticle) override;


      void on_instantiate_application(::acme::application* papp) override;


   };


} // namespace base




