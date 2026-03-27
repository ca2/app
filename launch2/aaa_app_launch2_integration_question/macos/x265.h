// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../x265.h"
#include "build.h"



namespace console_integration
{


   namespace macos
   {


      class x265 :
         virtual public ::console_integration::x265,
         virtual public ::console_integration::macos::build
      {
      public:


         ::file::path      m_pathSourceBits;
         ::string          m_strTargetName;
         //   ::string       m_strArch;
         //   ::string       m_strTargetting;
         //   ::string       m_strTarget;
         //   ::string       m_strHost;


         x265();
         ~x265() override;


         void initialize(::particle* pparticle) override;

         void initialize_x265(
            const ::scoped_string& scopedstrArch,
            const ::scoped_string& scopedstrTargetting,
            const ::scoped_string& scopedstrTarget,
            const ::scoped_string& scopedstrHost);


         void build();

         void clean();

         void prepare();

         void download();

         void configure(int iBits);

         void compile();

         void install();



      };


   } // namespace macos

} // namespace console_integration


