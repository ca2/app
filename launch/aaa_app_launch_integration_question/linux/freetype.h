// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../freetype.h"
#include "build.h"


namespace console_integration
{


   namespace linux
   {

   
      class freetype :
         virtual public ::console_integration::freetype,
         virtual public ::console_integration::linux::build
      {
      public:
         

         
//         ::string       m_strArch;
//         ::string       m_strTarget;
//         
//         
         freetype();
         ~freetype() override;
         
         
         void initialize(::particle * pparticle) override;
         
         
         
         void build();
         
         void clean();
         
         void prepare();
         
         void download();
         
         void configure();
         
         void compile();
         
         void install();
         

         
      };


   } // namespace linux


} // namespace console_integration


