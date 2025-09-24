// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../openssl.h"
#include "build.h"


namespace console_integration
{


   namespace windows
   {


      class openssl :
         virtual public ::console_integration::openssl,
         virtual public ::console_integration::windows::build
      {
      public:


         //::pointer < ::integration::context > m_papplication;


         ::string       m_strConfigure;
         ::string       m_strDebug;
         ::string       m_strShared;


         openssl();
         ~openssl() override;


         void initialize(::particle* pparticle);


         void build();

         void clean();

         void prepare();

         void download();

         void configure();

         void compile();

         void install();

         void copy_to_operating_system_storage();


      };


   } // namespace windows



} // namespace console_integration


