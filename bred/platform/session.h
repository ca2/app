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


      virtual void initialize(::object * pobject) override;


      virtual void on_instantiate_application(::apex::application* papp) override;


   };


} // namespace base




