//
//  application.cpp
//  console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 15:37.
//
#include "framework.h"
#include "application.h"
#include "ffmpeg.h"
#include "x264.h"
#include "x265.h"
#include "fdk_aac.h"
#include "lame.h"
#include "freetype.h"
#include "openssl.h"
#include <stdio.h>
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/integration_context.h"
//#include "apex/networking/http/context.h"


namespace application_build_helper
{


   bool application::integrate()
   {


      auto psystem = acmesystem();

      auto psubsystem = psystem->m_psubsystem;

      string strArgument = psubsystem->get_argument1(0);
      
      bool bOnlyInstall = psubsystem->has_argument1("--only-install");

      bool bBuildDependencies = true;
      
      if (psubsystem->has_argument1("--dont-build-dependencies"))
      {

         bBuildDependencies = false;

      }

      string strModule = file_system()->module().title();

      if (this->has_property("j"))
      {

         m_strMakeOptions = " -j" + this->payload("j");

      }

      // At macos generally just building the release shared version of libraries with x86_64/arm64 lipo
      
      if (strArgument.case_insensitive_equals("ffmpeg"))
      {
         
         try {
         
         auto strConfiguration = psubsystem->get_argument1(1);
//
//         if (!strConfiguration.case_insensitive_equals("Debug")
//            && !strConfiguration.case_insensitive_equals("Release")
//            && !strConfiguration.case_insensitive_equals("StaticDebug")
//            && !strConfiguration.case_insensitive_equals("StaticRelease"))
//         {
//
//            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Debug --no-prefix-clean");
//
//            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Release --no-prefix-clean");
//
//            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticDebug --no-prefix-clean");
//
//            acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticRelease --no-prefix-clean");
//
//            return;
//
//         }
            
            if(strConfiguration.is_empty())
            {
               
               strConfiguration = "Release";
               
            }

         auto pffmpeg = øcreate_new < ::console_integration::macos::ffmpeg >();
            
         pffmpeg->m_papplication->m_pathFolder = m_pathFolder;

         //pffmpeg->m_papplication->m_strPlatform = strPlatform;

         pffmpeg->m_papplication->m_strConfiguration = strConfiguration;

         pffmpeg->build();

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
         
         } catch (...) {
            
         }

         
         return true;

      }
      else if (strArgument.case_insensitive_equals("openssl"))
      {
         
         try
         {
            
            auto popenssl = øcreate_new < ::console_integration::macos::openssl >();
            
            
            popenssl->m_papplication->m_pathFolder = m_pathFolder;

            popenssl->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
            popenssl->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);
            
            popenssl->build();
            
         }
         catch(...)
         {
            
            
            
         }
         
         return true;

      }
      else if (strArgument.case_insensitive_equals("x264"))
      {
         
         try
         {
            
            auto px264 = øcreate_new < ::console_integration::macos::x264 >();
            
//            px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
            px264->m_papplication->m_pathFolder = m_pathFolder;
            
            px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(1);
            
            px264->m_pathPrefixBase = psubsystem->get_argument1(2);
            
            px264->build();
            
         }
         catch(...)
         {
            
            m_iExitCode = 1;
            
         }

      }
      else if (strArgument.case_insensitive_equals("x265"))
      {
         
         try
         {
            
                     auto px265 = øcreate_new < ::console_integration::macos::x265 >();
            
            
            px265->m_papplication->m_pathFolder = m_pathFolder;

 //                     px265->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
                     px265->m_papplication->m_strConfiguration = psubsystem->get_argument1(1);
            
                     px265->m_pathPrefixBase = psubsystem->get_argument1(2);
            
                     px265->build();
            
         }
         catch(...)
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
      else if (strArgument.case_insensitive_equals("fdk_aac"))
      {
         
         try
         {
            
                     auto pfdkaac = øcreate_new < ::console_integration::macos::fdk_aac >();
            
            
            pfdkaac->m_papplication->m_pathFolder = m_pathFolder;

 //                     px265->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
            pfdkaac->m_papplication->m_strConfiguration = psubsystem->get_argument1(1);
            
            pfdkaac->m_pathPrefixBase = psubsystem->get_argument1(2);
            
            pfdkaac->build();
            
         }
         catch(...)
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

      }      else if (strArgument.case_insensitive_equals("lame"))
      {
         
         try
         {
            
                     auto plame = øcreate_new < ::console_integration::macos::lame >();
            
            
            plame->m_papplication->m_pathFolder = m_pathFolder;

 //                     px265->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
            plame->m_papplication->m_strConfiguration = psubsystem->get_argument1(1);
            
            plame->m_pathPrefixBase = psubsystem->get_argument1(2);
            
            plame->build();
            
         }
         catch(...)
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
      else if (strArgument.case_insensitive_equals("freetype"))
      {
         
         try
         {
            
                     auto pfreetype = øcreate_new < ::console_integration::macos::freetype >();
            
            
            pfreetype->m_papplication->m_pathFolder = m_pathFolder;

 //                     px265->m_papplication->m_strPlatform = psubsystem->get_argument1(1);
            
            pfreetype->m_papplication->m_strConfiguration = psubsystem->get_argument1(1);
            
            pfreetype->m_pathPrefixBase = psubsystem->get_argument1(2);
            
            pfreetype->build();
            
         }
         catch(...)
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
      else if (strArgument.case_insensitive_equals("third"))
      {

         try
         {
            //         auto pthirdwinrt = øcreate_new < macos::third >();
            
            //pthirdwinrt->m_papplication->m_pathFolder = m_pathFolder;

            //
            //pthirdwinrt->build();
            
         }
         catch(...)
         {
         }
         
         
         return true;

      }

      return false;

   }

} // namespace console_integration



