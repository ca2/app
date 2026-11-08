// From integration/x264.h on 2023-08-17 02:42 <3ThomasBorregaardSørensen!!
#pragma once


#include "build.h"


namespace console_integration
{


   class openssl :
      virtual public build
   {
   public:


      openssl();
      ~openssl() override;


      void initialize(::particle* pparticle) override;



   };


} // namespace console_integration


