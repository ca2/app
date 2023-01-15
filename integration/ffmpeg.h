// Created by camilo on 2023-01-15 07:15 <3ThomasBorregaardSørensen!!
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


      class ffmpeg :
         virtual public ::build_library
      {
      public:


         ffmpeg()
         {

            m_strName = "ffmpeg";

         }


         void run() override
         {

            build_library::run();

            acmeapplication()->fork([])

            compile("Win32", "Debug");
            compile("Win32", "Release");
            compile("Win32", "StaticDebug");
            compile("Win32", "StaticRelease");

            compile("x64", "Debug");
            compile("x64", "Release");
            compile("x64", "StaticDebug");
            compile("x64", "StaticRelease");

            install("Win32", "Debug");
            install("Win32", "Release");
            install("Win32", "StaticDebug");
            install("Win32", "StaticRelease");

            install("x64", "Debug");
            compile("x64", "Release");
            install("x64", "StaticDebug");
            install("x64", "StaticRelease");

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



