// Created by camilo on 2023-01-15 02:59 <3ThomasBorregaardSorensen!!
#pragma once


#include "framework.h"
#include "acme/console.h"
#include <stdio.h>
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/networking/http/context.h"


namespace console
{


   namespace build_library
   {


      class application :
         virtual public ::apex::application
      {
      public:


         ::file::path m_pathFolder;




         application()
         {

            m_bNetworking = true;

            m_bCrypto = false;

            m_bResource = false;

            m_strAppId = "console/http_get";

            m_pathFolder = "C:\\";


         }


         void main() override
         {

            auto psystem = acmesystem();

            auto psubsystem = psystem->m_psubsystem;

            for (int i = 0; i < psubsystem->get_argument_count1(); i++)
            {

               string strArgument = psubsystem->get_argument1(i);

               if (strArgument.case_insensitive_equals("ffmpeg"))
               {

                  ffmpeg();

               }
               else if (strArgument.case_insensitive_equals("openssl"))
               {

                  openssl();

               }

            }


         }

         void ffmpeg()
         {

            ffmpeg("Win32", "Debug");
            ffmpeg("Win32", "Release");
            ffmpeg("Win32", "StaticDebug");
            ffmpeg("Win32", "StaticRelease");

            ffmpeg("x64", "Debug");
            ffmpeg("x64", "Release");
            ffmpeg("x64", "StaticDebug");
            ffmpeg("x64", "StaticRelease");


         }


         void ffmpeg(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
         {

            printf("Building ffmpeg");

            ::file::path path;

            path = "ffmpeg" / strVersion / scopedstrPlatform / scopedstrConfiguration;

            ::file::path pathPrefix = m_pathFolder / path / "build"

               string strCommand;

            strCommand =
               "configure --enable-asm --enable-yasm --arch=" + strArch +
               " --disable-doc " + strShared + strStatic +
               " --disable-bzlib --disable-libopenjpeg --disable-iconv --disable-zlib" +
               " --prefix=" + strBaseDir + "/" + strPath + "/build$BASE_DIR / $PATH / build --toolchain = msvc $DEBUG


         }

         void openssl()
         {

            printf("Building openssl");


         }


      };


   } // namespace build_library


} // namespace console



