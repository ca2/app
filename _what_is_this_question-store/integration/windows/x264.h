// From impact.h on 2023-01-23 17:27 <3ThomasBorregaardSørensen!!
#pragma once


#include "../x264.h"
#include "build.h"


namespace console_integration
{


   namespace windows
   {

      class x264 :
         virtual public ::console_integration::x264,
         virtual public ::console_integration::windows::build
      {
      public:



         string m_strShared;
         string m_strStatic;
         string m_strCFlags;


         x264();
         ~x264() override;


         void initialize(::particle* pparticle);


         void build();

         void clean();

         void prepare();

         void download();

         void configure();

         void compile();

         void install();


      };


   } // namespace windows



} // namespace console_integration



