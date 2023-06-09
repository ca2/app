#pragma once


#include "axis/platform/system.h"


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system
   {
   public:


      system();
      ~system() override;

      void common_construct();
      void initialize(::particle * pparticle) override;

      //void on_add_session(::acme::session * papexsession) override;

   };

   
} // namespace base



