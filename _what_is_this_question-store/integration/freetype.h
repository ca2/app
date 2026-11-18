// From windows/x264.h on 2023-07-26 16:02 <3ThomasBorregaardSørensen!!
#pragma once


#include "build.h"


namespace console_integration
{


   class freetype :
      virtual public build
   {
   public:


      freetype();
      ~freetype() override;


      void initialize(::particle * pparticle) override;

      


   };
} // namespace console_integration


