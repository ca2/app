// Created by camilo on 2023-01-15 16:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "integration_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/summary.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
//#include "acme/filesystem/filesystem/file_context.h"
//#include "apex/networking/http/context.h"
//#include "apex/platform/application.h"
//#include "apex/platform/system.h"
#include "acme/platform/sequencer.h"


#include "acme/_operating_system.h"
#ifdef STATIC_CUBE
#define LIBARCHIVE_STATIC
#endif
#include <archive.h>
#include <archive_entry.h>


namespace integration
{


   context::context()
   {

      m_bBuildDependencies = true;

   }


   context::~context()
   {


   }


   void context::initialize(::particle* pparticle)
   {

      ::acme::shell::initialize(pparticle);

      m_pshellComposite = node();

      m_pmutexLines = node()->create_mutex();

   }


   void context::prepare()
   {

      m_pathBase = m_strName / m_strRelease;
      
      m_pathPlatformConfiguration = m_strPlatform / m_strConfiguration;

      m_pathBuild = m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "build";

      m_pathSource = m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source";

      //acmedirectory()->create(m_pathSource2);

   }


   ::file::path context::get_source_folder_path(const ::scoped_string& scopedstr)
   {

      ::file::path path;

      path = m_pathSource;

      if (scopedstr.has_char())
      {

         path /= scopedstr;

      }

      return path;

   }


   ::file::path context::get_build_folder_path(const ::scoped_string& scopedstr)
   {

      ::file::path path;

      path = m_pathBuild;

      if (scopedstr.has_char())
      {

         path /= scopedstr;

      }

      return path;

   }


   void context::create_source_directory(const ::scoped_string& scopedstr)
   {

      ::file::path pathSourceFolder = get_source_folder_path(scopedstr);

      acmedirectory()->create(pathSourceFolder);

   }


   void context::change_to_source_directory(const ::scoped_string & scopedstr)
   {

      ::file::path pathSourceFolder = get_source_folder_path(scopedstr);

      acmedirectory()->create(pathSourceFolder);

      acmedirectory()->change_current(pathSourceFolder);

   }


   void context::prepare_compile_and_link_environment()
   {

      if (m_pathPrefix.has_char())
      {

         acmedirectory()->create(m_pathPrefix);

      }

   }


   void context::prepare_compilation_script(::string & str)
   {

      // introjection/compiler
      //str.find_replace("%VS_VARS%", m_strContext);
      //str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
      //str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);
      //str.find_replace("%PLATFORM%",m_strPlatform);
      //str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);

      //str.find_replace("%SDK1%",m_strSdk1);



      // programming/compiler
//      str.find_replace("%VS_VARS%", m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);
//      str.find_replace("%SDK1%", m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);

      str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);

      str.find_replace("%PLATFORM%", m_strPlatform);

   }

   void context::prepare_linking_script(::string & str)
   {

      //prepare_compilation_script(str);


//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 2
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 3
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);


// script_compiler cl 4
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);

      str.find_replace("%PROJECT_DIR%", m_pathProjectFolder);

      str.find_replace("%PLATFORM%", m_strPlatform);

   }


   int context::command_system(const ::scoped_string & scopedstrCommand, const class ::time& timeOut)
   {

//      auto functionTrace = [&](auto etracelevel, auto & str)
//      {
//
//         fprintf(trace_level_FILE(etracelevel), "%c: %s\n", trace_level_letter(etracelevel), str.c_str());
//
//      };
//
      //auto iExitCode = node()->command_system(scopedstrCommand, ::std_inline_log());
      auto iExitCode = node()->command_system(scopedstrCommand, 12_h);
      
      if (iExitCode != 0)
      {

         auto psequencer = message_box("Command :\n\""+scopedstrCommand+"\"\n\nFailed with code : \"" + ::as_string(iExitCode) + "\"");

         psequencer->do_synchronously();

         throw ::exception(error_exception);

      }

      return iExitCode;

   }


   void context::clean()
   {

      ::file::path path;

      path = this->prepare_path(m_pathFolder / m_pathBase / m_pathPlatformConfiguration / "source");

      if (application()->payload("no-source-clean").is_true())
      {

         if (acmedirectory()->is(path))
         {

            throw ::exception(error_failed, "Source Directory \""+path+"\" already exists.");

         }

      }
      else
      {

         if (acmedirectory()->is(path))
         {

            if (path.length() > 20)
            {

               {

                  ::string strCommand = "shopt -s dotglob; rm -Rf " + path + "/*";

                  this->bash(strCommand, 5_min);

               }

            }

         }

      }

      if(!application()->payload("no-prefix-clean").is_true())
      {

         string strPath;

         strPath = this->prepare_path(m_pathPrefix);

         if (strPath.length() > 20)
         {

            {

               ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

               this->bash(strCommand, 5_min);

            }

         }

      }

   }


   void context::download_and_uncompress()
   {

      if (!acmefile()->exists(acmedirectory()->get_current() / "Configure"))
      {

         if (m_pathDownloadURL.case_insensitive_ends(".tar.gz"))
         {

            property_set set;

            system()->url()->defer_raw_http(set);

            set["disable_common_name_cert_check"] = true;

            //auto path = m_pathFolder / m_path / (m_strName + ".tar.gz");

            auto pmemoryFileTarGz = create_memory_file();

            auto url = m_pathDownloadURL;

            information() << "Downloading \"" << url << "\"...";

            ::particle * pparticle = this;

            pparticle->context()->http_download(pmemoryFileTarGz, url, set);

            //auto pathTar = m_pathFolder / m_path / (m_strName + ".tar");

            pmemoryFileTarGz->seek_to_begin();

            auto pmemoryFileTar = create_memory_file();

            information() << "Uncompressing...";

            system()->uncompress(pmemoryFileTar, pmemoryFileTarGz, "zlib");

            pmemoryFileTar->seek_to_begin();

            information() << "Untarring to \"" << acmedirectory()->get_current() << "\"...";

            this->untar(acmedirectory()->get_current(), pmemoryFileTar, 1);

         }

      }

   }


   void context::git_clone()
   {
      //preempt(15_s);
      
      information() << "Current Directory: " << acmedirectory()->get_current();

      bash("git clone " + m_pathDownloadURL + " .", 2_hour);

   }


   ::i32 context::bash(const ::scoped_string & scopedstr, const class ::time & timeTimeout)
   {

      throw interface_only();

      return -1;

   }


   ::i32 context::zsh(const ::scoped_string & scopedstr, const class ::time & timeTimeout)
   {

      throw interface_only();

      return -1;

   }


   void context::untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent)
   {
      struct archive * a;
      struct archive_entry * entry;
      int r;

      a = archive_read_new();
      archive_read_support_filter_all(a);
      archive_read_support_format_all(a);

      ::memory memory;

      memory = file()->as_memory(payloadTar);

      //struct archive * a = archive_read_new();
      //archive_read_support_compression_gzip(a);
      //archive_read_support_format_tar(a);
      r = archive_read_open_memory(a, memory.data(), memory.size());
      //r = archive_read_open_filename(a, "archive.tar", 10240); // Note 1
      if (r != ARCHIVE_OK)
      {
         
         throw exception(error_failed);

      }
      ::memory memory2;
      memory2.set_size(1_MiB);
      while (archive_read_next_header(a, &entry) == ARCHIVE_OK) 
      {
         //printf("%s\n", archive_entry_pathname(entry));
         string strPathName(archive_entry_pathname(entry));
         if (!strPathName.ends("/") && !strPathName.ends("\\"))
         {
            
            ::file::path path(strPathName);

            for(int i = 0; i < iStripComponent; i++)
            {

               auto p = path.find_first_character_in("/\\");

               if (!p)
               {

                  goto next;

               }

               p = path(p).skip_any_character_in("/\\").begin();

               path = p;

            }

            auto pfile = file()->get_writer(pathFolder / path);

            for (;;) {
               auto size = archive_read_data(a, memory2.data(), memory2.size());
               if (size < 0) {
                  throw ::exception(error_failed);
               }
               if (size == 0)
                  break;
               pfile->write(memory2(0, size));
               //write(1, buff, size);
            }

            ::acme::get()->platform()->informationf(strPathName + "\n");

         }
         next:
         archive_read_data_skip(a);  // Note 2
      }
      r = archive_read_free(a);  // Note 3
      if (r != ARCHIVE_OK)
      {

         throw exception(error_failed);

      }

   }


   ::string context::prepare_path(const ::file::path & path)
   {

      return path;

   }


   ::file::path context::base_integration_folder()
   {

      return {};

   }


   ::file::path context::host_integration_folder()
   {

      return base_integration_folder() / "_____" / node()->operating_system_summary()->m_strSlashedIntegration;

   }


   //::file::path context::integration_folder()
   //{

   //   return host_integration_folder() / m_strIntegration;

   //}


   void context::list_host_builds()
   {

      auto pathHostIntegrationFolder = host_integration_folder();

      ::string_array straPattern;

      straPattern.add("\?\?\?\?-\?\?-\?\? \?\?-\?\?-\?\?");

      m_listingBuild.set_pattern_folder_listing(pathHostIntegrationFolder, straPattern);

      acmedirectory()->enumerate(m_listingBuild);

   }


   void context::defer_nasm()
   {

      if (!node()->has_command("nasm"))
      {

         throw ::exception(error_file_not_found, "nasm should be installed.");

      }

   }


   void context::defer_yasm()
   {

      if (!node()->has_command("yasm"))
      {

         throw ::exception(error_file_not_found, "yasm should be installed.");

      }

   }


   void context::defer_has_unix_shell_command(const ::scoped_string& scopedstr)
   {

      if (!has_unix_shell_command(scopedstr))
      {

         throw ::exception(error_file_not_found, ::string("\"") + scopedstr + "\" was not found.");

      }

   }


#ifdef WINDOWS_DESKTOP


   void context::set_msys2(bool bSet)
   {

      UNREFERENCED_PARAMETER(bSet);

      throw interface_only();

   }


#endif


} // namespace integration



