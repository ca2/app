// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../openssl.h"
#include "build.h"


namespace integration { class context; }


namespace console_integration
{


   namespace macos
   {


      class openssl :
   virtual public ::console_integration::openssl,
      virtual public ::console_integration::macos::build
      {
      public:


         ::pointer < ::integration::context > m_pcontext;


         ::string       m_strConfigure;
         ::string       m_strDebug;
         ::string       m_strShared;


         openssl();
         ~openssl() override;


         void initialize(::particle* pparticle) override;


         void build();

         void clean();

         void prepare();

         void download();

         void configure();

         void compile();

         void install();


      };

   } // namespace macos



} // namespace console_integration


