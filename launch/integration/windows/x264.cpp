// From ffmpeg.cpp on 2023-01-23 17:26 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "x264.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/directory_system.h"
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


      x264::x264()
      {

      }


      x264::~x264()
      {

      }


      void x264::initialize(::particle* pparticle)
      {

         ::console_integration::windows::build::initialize(pparticle);
         ::console_integration::x264::initialize(pparticle);

         m_papplication->m_bMsys = true;

      }


      void x264::build()
      {

         prepare();

         //clean();

         if (!m_papplication->m_bOnlyInstall)
         {

            download();

            configure();

            compile();

         }

         install();

      }


      void x264::prepare()
      {

         ::string strRelease = acmesystem()->datetime()->international().get_date_for_file();

         strRelease.trim();

         strRelease.case_insensitive_ends_eat(".git");

         strRelease.find_replace(" ", "_");

         m_papplication->m_strRelease = strRelease;

         m_papplication->m_pathDownloadURL = "https://code.videolan.org/videolan/x264.git/";

         m_papplication->prepare();

         if (m_papplication->m_pathPrefix.is_empty())
         {

            m_papplication->m_pathPrefix = calculate_prefix_path(m_papplication->m_strPlatform, m_papplication->m_strConfiguration);

         }

         if (m_papplication->m_strConfiguration.case_insensitive_contains("Static"))
         {

            m_strShared = "";

            m_strStatic = "--enable-static";

            if (m_papplication->m_strConfiguration.case_insensitive_contains("Debug"))
            {

               m_strCFlags = " --extra-cflags=\"-MTd\"";

            }
            else
            {

               m_strCFlags = " --extra-cflags=\"-MT\"";

            }

         }
         else
         {

            m_strShared = "--enable-shared";

            m_strStatic = "";

         }

         m_papplication->prepare_compile_and_link_environment();

      }


      void x264::clean()
      {

         //m_papplication->change_to_source_directory();

         m_papplication->clean();

      }


      void x264::download()
      {

         m_papplication->create_source_directory();

         m_papplication->change_to_source_directory();

         //preempt(15_s);

         //auto s = stdout;

         m_papplication->git_clone();

      }


      void x264::configure()
      {

         m_papplication->change_to_source_directory();

         string strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);

         string strCommand;

         strCommand += "./configure";
         strCommand += " " + m_strShared + " " + m_strStatic;
         strCommand += m_strCFlags;
         strCommand += " --prefix=" + strPrefix;

         m_papplication->bash(strCommand);

      }


      void x264::compile()
      {

         m_papplication->change_to_source_directory();

         auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform / m_papplication->m_strConfiguration;

         auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);

         printf("Storage-Folder: %s\n", strStorage.c_str());

         //::pointer < application > papplication = acmeapplication();

         //m_papplication->bash("make" + papplication->m_strMakeOptions);
         m_papplication->bash("make");

      }


      void x264::install()
      {

         m_papplication->change_to_source_directory();

         m_papplication->bash("make install");

         auto pathOperatingSystemIncludeFolder = m_papplication->m_pathOperatingSystemIncludeFolder;

         auto pathOperatingSystemStorageFolder = m_papplication->m_pathOperatingSystemStorageFolder / m_papplication->m_strPlatform / m_papplication->m_strConfiguration;

         auto strPrefix = m_papplication->prepare_path(m_papplication->m_pathPrefix);

         auto strInclude = m_papplication->prepare_path(pathOperatingSystemIncludeFolder);

         auto strStorage = m_papplication->prepare_path(pathOperatingSystemStorageFolder);

         directory_system()->create(strInclude + "/include/");
         directory_system()->create(strStorage + "/binary/");
         directory_system()->create(strStorage + "/library/");

         if (!m_papplication->m_strConfiguration.case_insensitive_contains("static"))
         {

            m_papplication->bash("mv " + strPrefix + "/lib/libx264.dll.lib " + strPrefix + "/lib/libx264.lib");

         }

         m_papplication->bash("cp -Rf " + strPrefix + "/include/* " + strInclude + "/include/");
         m_papplication->bash("cp -Rf " + strPrefix + "/bin/* " + strStorage + "/binary/");
         //m_papplication->bash("cp -f " + strPrefix + "/bin/*.dll " + strStorage + "/binary/");
         //m_papplication->bash("cp -f " + strPrefix + "/bin/*.lib " + strStorage + "/library/");
         m_papplication->bash("cp -Rf " + strPrefix + "/lib/* " + strStorage + "/library/");

      }


   } // namespace windows


} // namespace console_integration



