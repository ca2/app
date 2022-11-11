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


      inline ::core::system* get_system() const;


      void common_construct();


      virtual void initialize(::particle * pparticle) override;


      virtual void on_instantiate_application(::apex::application* papp) override;


   };


} // namespace core




