// From windows/x264.h on 2023-07-26 16:02 <3ThomasBorregaardSørensen!!
#pragma once


#include "build.h"


namespace console_integration
{


   class x265 :
      virtual public build
   {
   public:


      x265();
      ~x265() override;


      void initialize(::particle * pparticle) override;

      


   };


} // namespace console_integration


