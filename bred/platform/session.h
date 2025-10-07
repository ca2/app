#pragma once


#include "berg/platform/session.h"


namespace bred
{


   class CLASS_DECL_BRED session :
      virtual public ::berg::session
   {
   public:


      session();
      ~session() override;


      void common_construct();


      void initialize(::particle * pparticle) override;


      void on_instantiate_application(::platform::application* papp) override;


   };


} // namespace berg




