#pragma once


#include "apex/platform/session.h"


namespace aqua
{


   class CLASS_DECL_AQUA session :
      virtual public ::apex::session
   {
   public:


      session();
      ~session() override;

      void common_construct();


      void initialize(::particle * pparticle) override;

      void on_instantiate_application(::acme::application* papplication) override;


   };


} // namespace aqua




