// From impact.h on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "build.h"


namespace console_integration
{


   namespace linux
   {

      class x264;
      class x265;
      class fdk_aac;
      class lame;
      class freetype;

      class ffmpeg :
      virtual public ::console_integration::linux::build
      {
      public:
         
         
         
         string                     m_strArch;
         string                     m_strDebug;
         //string                     m_strShared;
         //string                     m_strStatic;
         string                     m_strCrossCompile;
         
         bool                       m_bX264;
         bool                       m_bX265;
         bool                       m_bFdkAac;
         bool                       m_bLame;
         bool                       m_bFreetype;
         
         
         ::pointer < x264 >         m_px264;
         ::pointer < x265 >         m_px265;
         ::pointer < fdk_aac >      m_pfdkaac;
         ::pointer < lame >         m_plame;
         ::pointer < freetype >     m_pfreetype;
         
         ::string_array_base             m_straX264;
         ::string_array_base             m_straX265;
         ::string_array_base             m_straFdkAac;
         ::string_array_base             m_straLame;
         ::string_array_base             m_straFreetype;
         
         
         
         ffmpeg();
         ~ffmpeg() override;
         
         
         void initialize(::particle * pparticle) override;
         
         
         void build_dependencies();
         
         void build_x264();
         
         void build_x265(const ::scoped_string & scopedstrConfiguration);
         
         void build_fdk_aac();
         
         void build_lame();
         
         void build_freetype();
         
         void build();
         
         void clean();
         
         void prepare();
         
         void download();
         
         void configure();
         
         void compile();
         
         void install_lib(const ::scoped_string & scopedstr);
         
         void install();
         
         void remap_dependencies(const ::scoped_string & scopedstrLibraryName) override;
         
         
      };

      
   } // namespace linux


} // namespace console_integration



