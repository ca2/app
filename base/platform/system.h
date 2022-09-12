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
      virtual void initialize(::object * pobject) override;

      virtual void on_add_session(::apex::session * papexsession) override;

   };

   
} // namespace base



