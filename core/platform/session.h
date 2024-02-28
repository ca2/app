#pragma once


#include "bred/platform/session.h"


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::bred::session
   {
   public:


      session();
      ~session() override;


      inline ::core::system* system() const;


      void common_construct();


      void initialize(::particle * pparticle) override;


      void on_instantiate_application(::acme::application* papp) override;


   };


} // namespace core




