//
//  application.cpp
//  console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 15:37.
//
#include "framework.h"
#include "build.h"
#include "ffmpeg.h"
#include "x264.h"
#include "x265.h"
#include "third_winrt.h"
#include <stdio.h>
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/platform/integration_context.h"
//#include "apex/networking/http/context.h"
//#include "acme/_operating_system.h"
//#include <shellapi.h>
#ifdef WINDOWS
#include "openssl.h"
#include "third.h"
#endif


namespace console_integration
{


   namespace windows
   {


      build::build()
      {



      }


      build::~build()
      {


      }



      void build::initialize(::particle* pparticle)
      {

         ::console_integration::build::initialize(pparticle);


         m_papplication->m_pathOperatingSystemStorageFolder = "C:/workspace/operating_system/storage-macos";

      }


      ::file::path build::calculate_prefix_path(const ::scoped_string& scopedstrPlatform, const ::scoped_string& scopedstrConfiguration)
      {

         return m_pathPrefixBase / scopedstrPlatform / m_papplication->m_strConfiguration / "build";


      }



      //void build::remap_dependencies(const ::scoped_string& scopedstrLibraryName)
      //{


      //}



      //void build::remap_dependency(const ::scoped_string& scopedstrLibraryName,
      //   const ::scoped_string& scopedstrLibraryDependency)
      //{
      // /*  auto pathDependency = library_source_path(scopedstrLibraryDependency);

      //   if (pathDependency.has_character())
      //   {
      //      ::string str = "lib" + scopedstrLibraryName + ".dylib";

      //      ::file::path path = m_papplication->m_pathPrefix / "lib" / ("lib" + scopedstrLibraryName + ".dylib");

      //      ::string strDependency = "lib" + scopedstrLibraryDependency + ".dylib";

      //      {

      //         ::string strCommand = "install_name_tool -change " + pathDependency + " @executable_path/" + strDependency + " " + path;

      //         m_papplication->bash(strCommand);

      //      }

      //      ::file::path pathName = pathDependency.name();

      //      auto pathFolder = pathDependency.folder();

      //      ::string strExtension = pathDependency.final_extension();

      //      pathName.ends_eat("." + strExtension);

      //      while (true)
      //      {

      //         ::string strExtension1 = pathName.final_extension();

      //         if (strExtension1.is_empty())
      //         {

      //            break;

      //         }

      //         pathName.ends_eat("." + strExtension1);

      //         auto pathDependency = pathFolder / (pathName + "." + strExtension);

      //         ::string strCommand = "install_name_tool -change " + pathDependency + " @executable_path/" + strDependency + " " + path;

      //         m_papplication->bash(strCommand);

      //      }


      //   }*/

      //}
      //void build::main()
      //{

      //   auto psystem = acmesystem();

      //   auto psubsystem = psystem->m_psubsystem;

      //   string strArgument = psubsystem->get_argument1(0);

      //   string strModule = file_system()->module().title();

      //   if (this->has_property("j"))
      //   {

      //      m_strMakeOptions = " -j" + this->payload("j");

      //   }

      //   if (strArgument.case_insensitive_equals("ffmpeg"))
      //   {

      //      auto strPlatform = psubsystem->get_argument1(1);

      //      if (strPlatform.case_insensitive_equals("Static"))
      //      {

      //         ::string strExtraParameters;

      //         if (this->has_property("j"))
      //         {

      //            strExtraParameters = " --j=" + this->payload("j");

      //         }


      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticDebug" + strExtraParameters);

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32 StaticRelease" + strExtraParameters);

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticDebug" + strExtraParameters);

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg x64 StaticRelease" + strExtraParameters);

      //         return;

      //      }


      //      if (!strPlatform.case_insensitive_equals("Win32")
      //         && !strPlatform.case_insensitive_equals("x64"))
      //      {

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg Win32");

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg x64");

      //         return;

      //      }

      //      auto strConfiguration = psubsystem->get_argument1(2);

      //      if (!strConfiguration.case_insensitive_equals("Debug")
      //         && !strConfiguration.case_insensitive_equals("Release")
      //         && !strConfiguration.case_insensitive_equals("StaticDebug")
      //         && !strConfiguration.case_insensitive_equals("StaticRelease"))
      //      {

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Debug --no-prefix-clean");

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " Release --no-prefix-clean");

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticDebug --no-prefix-clean");

      //         acmenode()->open_terminal_and_run(strModule + " ffmpeg " + strPlatform + " StaticRelease --no-prefix-clean");

      //         return;

      //      }

      //      //while (true)
      //      //{

      //      //   printf("Enter s to start.\n");

      //      //   if (getchar() == 's')
      //      //   {

      //      //      break;

      //      //   }

      //      //}

      //      auto pffmpeg = øcreate_new < ffmpeg >();

      //      pffmpeg->m_papplication->m_strPlatform = strPlatform;

      //      pffmpeg->m_papplication->m_strConfiguration = strConfiguration;

      //      pffmpeg->build();

      //      while (true)
      //      {

      //         printf("Enter q to quit.\n");

      //         if (getchar() == 'q')
      //         {

      //            break;

      //         }

      //      }

      //   }
      //   else if (strArgument.case_insensitive_equals("openssl"))
      //   {

      //      auto popenssl = øcreate_new < openssl >();

      //      popenssl->m_papplication->m_strPlatform = psubsystem->get_argument1(1);

      //      popenssl->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);

      //      popenssl->build();

      //   }
      //   else if (strArgument.case_insensitive_equals("x264"))
      //   {

      //      auto px264 = øcreate_new < x264 >();

      //      px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);

      //      px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);

      //      px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);

      //      px264->build();

      //   }
      //   else if (strArgument.case_insensitive_equals("x265"))
      //   {

      //      auto px264 = øcreate_new < x265 >();

      //      px264->m_papplication->m_strPlatform = psubsystem->get_argument1(1);

      //      px264->m_papplication->m_strConfiguration = psubsystem->get_argument1(2);

      //      px264->m_papplication->m_pathPrefix = psubsystem->get_argument1(3);

      //      px264->build();

      //   }
      //   else if (strArgument.case_insensitive_equals("third_winrt"))
      //   {

      //      auto pthirdwinrt = øcreate_new < third_winrt >();

      //      pthirdwinrt->build();

      //   }
      //   else if (strArgument.case_insensitive_equals("third"))
      //   {

      //      auto pthirdwinrt = øcreate_new < third >();

      //      pthirdwinrt->build();

      //   }


      //}


   } // namespace windows


} // namespace console_integration



