// From ffmpeg.cpp on 2023-01-23 17:26 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "x264.h"
#include "application.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/filesystem/filesystem/acme_directory.h"
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

         m_pcontext->m_bMsys = true;

      }


      void x264::build()
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


      void x264::prepare()
      {

         ::string strRelease = acmesystem()->datetime()->international().get_date_for_file();

         strRelease.trim();

         strRelease.case_insensitive_ends_eat(".git");

         strRelease.find_replace(" ", "_");

         m_pcontext->m_strRelease = strRelease;

         m_pcontext->m_pathDownloadURL = "https://code.videolan.org/videolan/x264.git/";

         m_pcontext->prepare();

         if (m_pcontext->m_pathPrefix.is_empty())
         {

            m_pcontext->m_pathPrefix = calculate_prefix_path(m_pcontext->m_strPlatform, m_pcontext->m_strConfiguration);

         }

         if (m_pcontext->m_strConfiguration.case_insensitive_contains("Static"))
         {

            m_strShared = "";

            m_strStatic = "--enable-static";

            if (m_pcontext->m_strConfiguration.case_insensitive_contains("Debug"))
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

         m_pcontext->prepare_compile_and_link_environment();

      }


      void x264::clean()
      {

         //m_pcontext->change_to_source_directory();

         m_pcontext->clean();

      }


      void x264::download()
      {

         m_pcontext->create_source_directory();

         m_pcontext->change_to_source_directory();

         //preempt(15_s);

         //auto s = stdout;

         m_pcontext->git_clone();

      }


      void x264::configure()
      {

         m_pcontext->change_to_source_directory();

         string strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);

         string strCommand;

         strCommand += "./configure";
         strCommand += " " + m_strShared + " " + m_strStatic;
         strCommand += m_strCFlags;
         strCommand += " --prefix=" + strPrefix;

         m_pcontext->bash(strCommand);

      }


      void x264::compile()
      {

         m_pcontext->change_to_source_directory();

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform / m_pcontext->m_strConfiguration;

         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);

         printf("Storage-Folder: %s\n", strStorage.c_str());

         //::pointer < application > papplication = acmeapplication();

         //m_pcontext->bash("make" + papplication->m_strMakeOptions);
         m_pcontext->bash("make");

      }


      void x264::install()
      {

         m_pcontext->change_to_source_directory();

         m_pcontext->bash("make install");

         auto pathOperatingSystemIncludeFolder = m_pcontext->m_pathOperatingSystemIncludeFolder;

         auto pathOperatingSystemStorageFolder = m_pcontext->m_pathOperatingSystemStorageFolder / m_pcontext->m_strPlatform / m_pcontext->m_strConfiguration;

         auto strPrefix = m_pcontext->prepare_path(m_pcontext->m_pathPrefix);

         auto strInclude = m_pcontext->prepare_path(pathOperatingSystemIncludeFolder);

         auto strStorage = m_pcontext->prepare_path(pathOperatingSystemStorageFolder);

         acmedirectory()->create(strInclude + "/include/");
         acmedirectory()->create(strStorage + "/binary/");
         acmedirectory()->create(strStorage + "/library/");

         if (!m_pcontext->m_strConfiguration.case_insensitive_contains("static"))
         {

            m_pcontext->bash("mv " + strPrefix + "/lib/libx264.dll.lib " + strPrefix + "/lib/libx264.lib");

         }

         m_pcontext->bash("cp -Rf " + strPrefix + "/include/* " + strInclude + "/include/");
         m_pcontext->bash("cp -Rf " + strPrefix + "/bin/* " + strStorage + "/binary/");
         //m_pcontext->bash("cp -f " + strPrefix + "/bin/*.dll " + strStorage + "/binary/");
         //m_pcontext->bash("cp -f " + strPrefix + "/bin/*.lib " + strStorage + "/library/");
         m_pcontext->bash("cp -Rf " + strPrefix + "/lib/* " + strStorage + "/library/");

      }


   } // namespace windows


} // namespace console_integration



