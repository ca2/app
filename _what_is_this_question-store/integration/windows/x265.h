// From x264.h on 2023-05-19 13:50 <3ThomasBorregaardSørensen!!
#pragma once


#include "../x265.h"
#include "build.h"


namespace console_integration
{


   namespace windows
   {


      class x265 :
         virtual public ::console_integration::x265,
         virtual public ::console_integration::windows::build
      {
      public:


         string m_strShared;
         string m_strStatic;


         //::pointer < ::integration::context > m_papplication;


         x265();
         ~x265() override;


         void initialize(::particle* pparticle);


         void build();

         void clean();

         void prepare();

         void download();

         void insert_cmp0091_new_in_cmake();

         void configure();

         void compile();

         void install();


      };


   } // namespace windows


} // namespace console_integration



