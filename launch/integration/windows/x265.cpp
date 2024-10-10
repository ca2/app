// From x265.cpp on 2023-05-19 13:49 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "x265.h"
#include "application.h"
#include "../../windows/visual_studio.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/prototype/url.h"
//#include "apex/networking/http/context.h"
#include "acme/platform/integration_context.h"


namespace console_integration
{


   namespace windows
   {


      x265::x265()
      {

      }


      x265::~x265()
      {

      }


      void x265::initialize(::particle* pparticle)
      {

         ::console_integration::windows::build::initialize(pparticle);
         ::console_integration::x265::initialize(pparticle);

         m_pcontext->m_bMsys = true;

      }


      void x265::build()
      {

         prepare();

         //clean();

         if (!m_pcontext->m_bOnlyInstall)
         {

            download();

            configure();

            compile();

         }

         install();

      }


      void x265::prepare()
      {

         ::string strRelease = acmesystem()->datetime()->international().get_date_for_file();

         strRelease.trim();

         strRelease.case_insensitive_ends_eat(".git");

         strRelease.find_replace(" ", "_");

         m_pcontext->m_strRelease = strRelease;

         m_pcontext->m_pathDownloadURL = "https://github.com/videolan/x265.git";

         m_pcontext->prepare();

         if (m_pcontext->m_pathPrefix.is_empty())
         {

            m_pcontext->m_pathPrefix = calculate_prefix_path(m_pcontext->m_strPlatform, m_pcontext->m_strConfiguration);

         }

         //if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
         //{

         //   m_strShared = "";

         //   m_strStatic = "--enable-static";

         //}
         //else
         //{

         //   m_strShared = "--enable-shared";

         //   m_strStatic = "";

         //}

         m_pcontext->prepare_compile_and_link_environment();

      }


      void x265::clean()
      {

         //m_pcontext->change_to_source_directory();

         m_pcontext->clean();

      }


      void x265::download()
      {

         m_pcontext->create_source_directory();

         m_pcontext->change_to_source_directory();

         m_pcontext->git_clone();

      }


      void x265::insert_cmp0091_new_in_cmake()
      {

         auto pathCMakeLists = acmedirectory()->get_current() / "source/CMakeLists.txt";

         auto straLines = acmefile()->lines(pathCMakeLists);

         ::index iFind = straLines.find_first_contains("POLICY CMP0054");

         if (iFind >= 0)
         {

            iFind = straLines.find_first_contains("endif", iFind);

            if (iFind >= 0)
            {

               straLines.insert_at(iFind + 1, "if(POLICY CMP0091)");

               straLines.insert_at(iFind + 2, "     cmake_policy(SET CMP0091 NEW) # Interpret MSVC_RUNTIME_LIBRARY (Patched by integration_console_integration)");

               straLines.insert_at(iFind + 3, "endif()");

               acmefile()->put_lines(pathCMakeLists, straLines);

            }

         }

      }


      void x265::configure()
      {

         m_pcontext->change_to_source_directory();

         string strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);

         string strCommand;

         strCommand += "cmake -G \"Visual Studio 17 2022\"";
         strCommand += " -A " + m_pcontext->m_strPlatform;
         strCommand += " -S source";
         strCommand += " -B \"" + m_pcontext->m_pathBuild + "\"";
         strCommand += " -DCMAKE_INSTALL_PREFIX=\"" + strPrefix + "\"";
         //strCommand += " " + m_strShared + " " + m_strStatic;
         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
         {

            insert_cmp0091_new_in_cmake();

            if (m_pcontext->m_strConfiguration.case_insensitive_contains("Debug"))
            {

               strCommand += " -DCMAKE_MSVC_RUNTIME_LIBRARY=\"MultiThreadedDebug\"";

            }
            else
            {

               strCommand += " -DCMAKE_MSVC_RUNTIME_LIBRARY=\"MultiThreaded\"";

            }

         }

         m_pcontext->bash(strCommand);

      }


      void x265::compile()
      {

         m_pcontext->change_to_source_directory("source");

         trace_function functionTrace = [&](auto etracelevel, auto& str)
            {

               //m_straLine2.append_format("%c: %s\n", trace_level_letter(etracelevel), str.c_str());

               std_inline_log()(etracelevel, str);

               //pfileLog->write(str + "\r\n");

            };

         ::string strProject;


         ::string strConfiguration(m_pcontext->m_strConfiguration);

         if (strConfiguration.case_insensitive_begins_eat("static"))
         {

            strProject = "x265-static";

         }
         else
         {

            strProject = "x265-shared";

         }

         ::file::path pathBuildSln;

         ::file::path pathPrefix = m_pcontext->prepare_path(m_pcontext->m_pathBuild);

         pathBuildSln = pathPrefix / "x265.sln";

         auto pvisualstudio = __create_new <::microsoft::visual_studio>();

         auto pathVSInstallLocation = pvisualstudio->get_an_existing_visual_studio_2022_install_location();

         auto pathDevenv = pathVSInstallLocation / "Common7/IDE/devenv.com";

         ::string strParameters;

         strParameters = " \"" + pathBuildSln.windows_path() + "\" /Build \"" + strConfiguration + "|" + m_pcontext->m_strPlatform + "\" /Project \"" + strProject + "\"";

         ::string strCommand;

         ::string strCmd = acmenode()->get_environment_variable("ComSpec");

         //strCommand = "\"" + strCmd + "\" /c \"\"" + pathDevenv.windows_path() + "\"" + strParameters + "\"";

         strCommand = "\"" + pathDevenv.windows_path() + "\"" + strParameters;

         //strCommand = "\"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\Common7\\IDE\\devenv.exe\" ;

         //strCommand = "devenv \"" + pathBuildSln.windows_path() + "\" /Build \"" + strConfiguration + "|" + m_pcontext->m_strPlatform + "\" /Project \"INSTALL\"";

         printf("%s\n", strCommand.c_str());

         acmenode()->command_system(strCommand, 2_h);

      }


      void x265::install()
      {

         m_pcontext->change_to_source_directory("source");

         //m_pcontext->bash("make install");

         auto pathOperatingSystemIncludeFolder = m_pcontext->m_pathOperatingSystemIncludeFolder;

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform / m_pcontext->m_strConfiguration;

         auto strSource = m_pcontext->prepare_path(m_pcontext->m_pathSource);

         auto strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);

         auto strInclude = m_pcontext->prepare_path(pathOperatingSystemIncludeFolder);

         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);

         auto strBuild = m_pcontext->prepare_path(m_pcontext->m_pathBuild);

         auto strConfiguration2 = m_pcontext->m_strConfiguration;

         bool bStatic = strConfiguration2.case_insensitive_begins_eat("Static");

         acmedirectory()->create(strStorage + "/binary");
         acmedirectory()->create(strPrefix + "/bin");
         acmedirectory()->create(strPrefix + "/lib/pkgconfig");
         acmedirectory()->create(strPrefix + "/include");

         //m_pcontext->bash("mv " + strPrefix + "/lib/libx264.dll.lib " + strPrefix + "/lib/libx264.lib");

         //m_pcontext->bash("cp -f " + m_pcontext->m_pathSource + "/source/x265.h " + strInclude + "/include/");
         //m_pcontext->bash("cp -f " + strPrefix + "/Deub/*.exe " + strStorage + "/binary/");
         ::string strConfiguration(m_pcontext->m_strConfiguration);
         if (bStatic)
         {

            acmefile()->copy(strPrefix + "/lib/x265.lib", strBuild + "/" + strConfiguration2 + "/x265-static.lib", true);
            acmefile()->copy(strStorage + "/library/x265.lib", strBuild + "/" + strConfiguration2 + "/x265-static.lib", true);
//            m_pcontext->bash("cp -f " +  " + ");
  //          m_pcontext->bash("cp -f " + strPrefix + "/" + strConfiguration2 + "/x265-static.lib " + strStorage + "/library/x265.lib");

         }
         else
         {

            m_pcontext->bash("cp -f " + strBuild + "/" + strConfiguration2 + "/*.dll " + strStorage + "/binary/");
            m_pcontext->bash("cp -f " + strBuild + "/" + strConfiguration2 + "/*.dll " + strPrefix + "/bin/");
            //m_pcontext->bash("cp -f " + strPrefix + "/" + strConfiguration2 + "/libx265.lib " + strPrefix + "/lib/x265.lib");
            //m_pcontext->bash("cp -f " + strPrefix + "/" + strConfiguration2 + "/libx265.lib " + strStorage + "/library/x265.lib");

            acmefile()->copy(strPrefix + "/lib/x265.lib", strBuild + "/" + strConfiguration2 + "/libx265.lib", true);
            acmefile()->copy(strStorage + "/library/x265.lib", strBuild + "/" + strConfiguration2 + "/libx265.lib", true);

         }


         //m_pcontext->bash("cp -f " + m_pcontext->m_pathSource + "/source/x265.h " + strPrefix + "/include/");
         //m_pcontext->bash("cp -f " + strPrefix + "/x265.pc " + strPrefix + "/lib/pkgconfig/");
         //m_pcontext->bash("cp -f " + strPrefix + "/x265_config.h " + strPrefix + "/include/");
         
         acmefile()->copy(strInclude + "/include/x265.h", strSource + "/source/x265.h", true);
         acmefile()->copy(strInclude + "/include/x265_config.h", strBuild + "/x265_config.h", true);
         acmefile()->copy(strStorage + "/library/pkgconfig/x265.pc", strBuild + "/x265.pc", true);

         acmefile()->copy(strPrefix + "/include/x265.h", strSource + "/source/x265.h", true);
         acmefile()->copy(strPrefix + "/include/x265_config.h", strBuild + "/x265_config.h", true);
         acmefile()->copy(strPrefix + "/lib/pkgconfig/x265.pc", strBuild + "/x265.pc", true);
         
         
         
         //m_pcontext->bash("cp -f " + strPrefix + "/lib/* " + strStorage + "/library/");

      }


   } // namespace windows


} // namespace console_integration



