// From impact.h on 2023-01-15 19:26 <3ThomasBorregaardSørensen!!
#pragma once


#include "../lame.h"
#include "build.h"


namespace console_integration
{


   namespace macos
   {

   
      class lame :
      virtual public ::console_integration::lame,
      virtual public ::console_integration::macos::build
      {
      public:
         

         
//         ::string       m_strArch;
//         //::string       m_strTargetting;
////         ::string       m_strTarget;
////         ::string       m_strHost;
         
         
         lame();
         ~lame() override;
         
         
         void initialize(::particle * pparticle) override;
         
//         void initialize_lame(
//                              const ::scoped_string & scopedstrArch,
//                              const ::scoped_string & scopedstrTargetting,
//                              const ::scoped_string & scopedstrTarget,
//                              const ::scoped_string & scopedstrHost);
//
         
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


