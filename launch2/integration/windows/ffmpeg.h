// From impact.h on 2023-01-15 09:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "build.h"
#include "../ffmpeg.h"


namespace integration { class context; }


namespace console_integration
{

   
   namespace windows
   {

      class x264;
      class x265;

      class ffmpeg :
         virtual public ::console_integration::ffmpeg,
         virtual public ::console_integration::windows::build
      {
      public:



         string m_strArch;
         string m_strDebug;
         string m_strShared;
         string m_strStatic;


         ::pointer < ::integration::context > m_papplication;

         ::pointer < x264 > m_px264;
         ::pointer < x265 > m_px265;

         ::string_array m_strax264;
         ::string_array m_strax265;



         ffmpeg();
         ~ffmpeg() override;


         void initialize(::particle* pparticle);


         void build_dependencies();

         void build_x264();

         void build_x265();

         void build();

         void clean();

         void prepare();

         void download();

         void configure();

         void compile();

         void install_lib(const ::scoped_string& scopedstr);

         void install();


      };


   } // namespace windows


} // namespace console_integration



