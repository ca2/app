//
//  application.cpp
//  console_integration
//
//  From macos/integration.cpp by Camilo Sasuke Thomas 
//            Borregaard Sørensen on 17/08/2023 02:19.
//
#include "framework.h"
#include "application.h"
#include "ffmpeg.h"
#include "x264.h"
#include "x265.h"
//#include "fdk_aac.h"
//#include "lame.h"
//#include "freetype.h"
#include "openssl.h"
#include <stdio.h>
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/integration_context.h"
//#include "apex/networking/http/context.h"



namespace application_build_helper
{


   bool application::integrate()
   {

      //acmenode()->speak("This is a simple TTS test");

      auto psystem = acmesystem();

      auto psubsystem = psystem->m_psubsystem;

      string strArgument = psubsystem->get_argument1(0);

      bool bOnlyInstall = psubsystem->has_argument1("--only-install");

      bool bBuildDependencies = true;

      if (psubsystem->has_argument1("--dont-build-dependencies"))
      {

         bBuildDependencies = false;

      }

      string strModule = "application_build_helper";

      if (this->has_property("j"))
      {

         m_strMakeOptions = " -j" + this->payload("j");

      }

      // At macos generally just building the release shared version of libraries with x86_64/arm64 lipo

      if (strArgument.case_insensitive_equals("ffmpeg"))
      {

         auto strPlatform = psubsystem->get_argument1(1);

         if (strPlatform.case_insensitive_equals("Static"))
         {

            ::string strExtraParameters;

            if (this->has_property("j"))
            {

               strExtraParameters = " --j=" + this->payload("j");

            }


            acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticDebug" + strExtraParameters);

            acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticRelease" + strExtraParameters);

            acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticDebug" + strExtraParameters);

            acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticRelease" + strExtraParameters);

            return true;

         }


         if (!strPlatform.case_insensitive_equals("Win32")
            && !strPlatform.case_insensitive_equals("x64"))
         {

            acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32");

            acmenode()->open_terminal_and_run(strModule + " ffmpeg x64");

            return true;

         }

         auto strConfiguration = psubsystem->get_argument1(2);

         if (!strConfiguration.case_insensitive_equals("Debug")
            && !strConfiguration.case_insensitive_equals("Release")
            && !strConfiguration.case_insensitive_equals("StaticDebug")
            && !strConfiguration.case_insensitive_equals("StaticRelease"))
         {

            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Debug --no-prefix-clean");

            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Release --no-prefix-clean");

            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticDebug --no-prefix-clean");

            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticRelease --no-prefix-clean");

            return true;

         }

         //while (true)
         //{

         //   printf("Enter s to start.\n");

         //   if (getchar() == 's')
         //   {

         //      break;

         //   }

         //}

         auto pffmpeg = __create_new < ::console_integration::windows::ffmpeg >();

         pffmpeg->m_pcontext->m_bOnlyInstall = bOnlyInstall;

         pffmpeg->m_pcontext->m_bBuildDependencies = bBuildDependencies;

         pffmpeg->m_pcontext->m_strPlatform = strPlatform;

         pffmpeg->m_pcontext->m_strConfiguration = strConfiguration;

         pffmpeg->build();

         while (true)
         {

            printf("Enter q to quit.\n");

            if (getchar() == 'q')
            {

               break;

            }

         }

         return true;

      }
      else if (strArgument.case_insensitive_equals("openssl"))
      {

         auto strPlatform = psubsystem->get_argument1(1);


         if (!strPlatform.case_insensitive_equals("Win32")
            && !strPlatform.case_insensitive_equals("x64"))
         {

            acmenode()->open_terminal_and_run("application_build_helper openssl Win32");

            acmenode()->open_terminal_and_run("application_build_helper openssl x64");

            return true;

         }

         auto strConfiguration = psubsystem->get_argument1(2);

         if (!strConfiguration.case_insensitive_equals("Debug")
            && !strConfiguration.case_insensitive_equals("Release")
            && !strConfiguration.case_insensitive_equals("StaticDebug")
            && !strConfiguration.case_insensitive_equals("StaticRelease"))
         {

            acmenode()->open_terminal_and_run("application_build_helper openssl " + strPlatform + " Debug");

            acmenode()->open_terminal_and_run("application_build_helper openssl " + strPlatform + " Release");

            acmenode()->open_terminal_and_run("application_build_helper openssl " + strPlatform + " StaticDebug");

            acmenode()->open_terminal_and_run("application_build_helper openssl " + strPlatform + " StaticRelease");

            return true;

         }


         try
         {

            auto popenssl = __create_new < ::console_integration::windows::openssl >();

            popenssl->m_pcontext->m_bOnlyInstall = bOnlyInstall;

            popenssl->m_pcontext->m_strPlatform = strPlatform;

            popenssl->m_pcontext->m_strConfiguration = strConfiguration;

            popenssl->build();

         }
         catch (...)
         {



         }

         return true;

      }
      else if (strArgument.case_insensitive_equals("x264"))
      {

         try
         {

            auto px264 = __create_new < ::console_integration::windows::x264 > ();

            px264->m_pcontext->m_bOnlyInstall = bOnlyInstall;

            px264->m_pcontext->m_strPlatform = psubsystem->get_argument1(1);

            px264->m_pcontext->m_strConfiguration = psubsystem->get_argument1(2);

            px264->m_pathPrefixBase = psubsystem->get_argument1(3);

            px264->build();

         }
         catch (...)
         {

            m_iExitCode = 1;

         }

      }
      else if (strArgument.case_insensitive_equals("x265"))
      {

         try
         {

            auto px265 = __create_new < ::console_integration::windows::x265 >();

            px265->m_pcontext->m_pathFolder = m_pathFolder;

            px265->m_pcontext->m_bOnlyInstall = bOnlyInstall;

            px265->m_pcontext->m_strPlatform = psubsystem->get_argument1(1);

            px265->m_pcontext->m_strConfiguration = psubsystem->get_argument1(2);

            px265->m_pathPrefixBase = psubsystem->get_argument1(3);

            px265->build();

         }
         catch (...)
         {


         }

         //         while (true)
         //         {
         //
         //            printf("Enter q to quit.\n");
         //
         //            if (getchar() == 'q')
         //            {
         //
         //               break;
         //
         //            }
         //
         //         }


         return true;

      }
      //else if (strArgument.case_insensitive_equals("fdk_aac"))
      //{

      //   try
      //   {

      //      auto pfdkaac = __create_new < ::console_integration::windows::fdk_aac >();


      //      pfdkaac->m_pcontext->m_pathFolder = m_pathFolder;

      //      //                     px265->m_pcontext->m_strPlatform = psubsystem->get_argument1(1);

      //      pfdkaac->m_pcontext->m_strConfiguration = psubsystem->get_argument1(1);

      //      pfdkaac->m_pathPrefixBase = psubsystem->get_argument1(2);

      //      pfdkaac->build();

      //   }
      //   catch (...)
      //   {


      //   }

      //   //         while (true)
      //   //         {
      //   //
      //   //            printf("Enter q to quit.\n");
      //   //
      //   //            if (getchar() == 'q')
      //   //            {
      //   //
      //   //               break;
      //   //
      //   //            }
      //   //
      //   //         }


      //   return true;

      //}
      //else if (strArgument.case_insensitive_equals("lame"))
      //{

      //   try
      //   {

      //      auto plame = __create_new < ::console_integration::macos::lame >();


      //      plame->m_pcontext->m_pathFolder = m_pathFolder;

      //      //                     px265->m_pcontext->m_strPlatform = psubsystem->get_argument1(1);

      //      plame->m_pcontext->m_strConfiguration = psubsystem->get_argument1(1);

      //      plame->m_pathPrefixBase = psubsystem->get_argument1(2);

      //      plame->build();

      //   }
      //   catch (...)
      //   {


      //   }

      //   //         while (true)
      //   //         {
      //   //
      //   //            printf("Enter q to quit.\n");
      //   //
      //   //            if (getchar() == 'q')
      //   //            {
      //   //
      //   //               break;
      //   //
      //   //            }
      //   //
      //   //         }


      //   return true;

      //}
      //else if (strArgument.case_insensitive_equals("freetype"))
      //{

      //   try
      //   {

      //      auto pfreetype = __create_new < ::console_integration::macos::freetype >();


      //      pfreetype->m_pcontext->m_pathFolder = m_pathFolder;

      //      //                     px265->m_pcontext->m_strPlatform = psubsystem->get_argument1(1);

      //      pfreetype->m_pcontext->m_strConfiguration = psubsystem->get_argument1(1);

      //      pfreetype->m_pathPrefixBase = psubsystem->get_argument1(2);

      //      pfreetype->build();

      //   }
      //   catch (...)
      //   {


      //   }

      //   //         while (true)
      //   //         {
      //   //
      //   //            printf("Enter q to quit.\n");
      //   //
      //   //            if (getchar() == 'q')
      //   //            {
      //   //
      //   //               break;
      //   //
      //   //            }
      //   //
      //   //         }


      //   return true;

      //}
      else if (strArgument.case_insensitive_equals("third"))
      {

         try
         {
            //         auto pthirdwinrt = __create_new < macos::third >();

            //pthirdwinrt->m_pcontext->m_pathFolder = m_pathFolder;

            //
            //pthirdwinrt->build();

         }
         catch (...)
         {
         }


         return true;

      }

      return false;

   }

} // namespace console_integration



