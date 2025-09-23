// Created by camilo on 2023-01-15 07:10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "ffmpeg.h"
#include "acme/platform/integration_context.h"



namespace console_integration
{

   /*  namespace build_library
     {
  */

   //class ffmpeg
      //{
      //public:

      //   ::file::path m_pathFolder

      //   ffmpeg


//function prepare()
//{
//
//
//   PATH = "openssl/$RELEASE/$PLATFORM/$CONFIGURATION"
//
//
//      if["$PLATFORM" == "Win32"]; then
//
//         ARCH = "i386"
//
//         elif["$PLATFORM" == "x64"]; then
//
//         ARCH = "x86_64"
//
//      else
//
//         echo "Unsupported Platform \"$PLATFORM\"?!?"
//
//         exit - 1
//
//         fi
//
//         if["$CONFIGURATION" == *"Debug" *]; then
//
//            DEBUG = "--enable-debug"
//
//         else
//
//            DEBUG = "--disable-debug"
//
//            fi
//
//            if["$CONFIGURATION" == *"Static" *]; then
//
//               SHARED = ""
//
//               STATIC = ""
//
//            else
//
//               SHARED = "--enable-shared"
//
//               STATIC = "--disable-static"
//
//               fi
//
//
//}

ffmpeg::ffmpeg()
   {

   }

   ffmpeg::~ffmpeg()
   {

   }

   void ffmpeg::initialize(::particle* pparticle)
   {

      ::console_integration::build::initialize(pparticle);

      m_papplication->m_strName = "ffmpeg";

      m_papplication->m_pathDownloadURL = "https://git.ffmpeg.org/ffmpeg.git";

   }


} // namespace console_integration



