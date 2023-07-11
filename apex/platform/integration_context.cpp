// Created by camilo on 2023-01-15 16:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "integration_context.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"


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

      m_bMsys = false;

   }


   context::~context()
   {


   }


   void context::initialize(::particle* pparticle)
   {

      ::particle::initialize(pparticle);

      m_pmutexLines = acmenode()->create_mutex();

   }


   void context::prepare()
   {

      m_path = m_strName / m_strRelease / m_strPlatform / m_strConfiguration;

      m_pathSource2 = m_pathFolder / m_path / "source";

      //acmedirectory()->create(m_pathSource2);

   }


   ::file::path context::get_source_folder_path(const ::scoped_string& scopedstr)
   {

      ::file::path path;

      path = m_pathSource2;

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
      //str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
      //str.find_replace("%PLATFORM%",m_strPlatform);
      //str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);

      //str.find_replace("%SDK1%",m_strSdk1);



      // programming/compiler
//      str.find_replace("%VS_VARS%", m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
//      str.find_replace("%SDK1%", m_strSdk1);


// script_compiler cl
//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PLATFORM%",m_strPlatform);
//      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
//      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
//      str.find_replace("%SDK1%",m_strSdk1);

      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);

      str.find_replace("%PLATFORM%", m_strPlatform);

   }

   void context::prepare_linking_script(::string & str)
   {

      //prepare_compilation_script(str);


//      str.find_replace("%VS_VARS%",m_strContext);
//      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
//      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
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

      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);

      str.find_replace("%PLATFORM%", m_strPlatform);

   }


   int context::command_system(const ::scoped_string & scopedstrCommand)
   {

//      auto functionTrace = [&](auto etracelevel, auto & str)
//      {
//
//         fprintf(trace_level_FILE(etracelevel), "%c: %s\n", trace_level_letter(etracelevel), str.c_str());
//
//      };
//
      //auto iExitCode = acmenode()->command_system(scopedstrCommand, ::std_inline_log());
      auto iExitCode = acmenode()->command_system(scopedstrCommand, 12_h);

      return iExitCode;

   }


   void context::clean()
   {

      ::file::path path;

      path = this->prepare_path(m_pathFolder / m_path / "source");

      if (acmeapplication()->payload("no-source-clean").is_true())
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

                  this->bash(strCommand);

               }

            }

         }

      }

      if(!acmeapplication()->payload("no-prefix-clean").is_true())
      {

         string strPath;

         strPath = this->prepare_path(m_pathPrefix);

         if (strPath.length() > 20)
         {

            {

               ::string strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

               this->bash(strCommand);

            }

         }

      }

   }


   void context::download_and_uncompress()
   {

      if (m_pathDownloadURL.case_insensitive_ends(".tar.gz"))
      {

         property_set set;

         acmesystem()->url()->defer_raw_http(set);

         set["disable_common_name_cert_check"] = true;

         //auto path = m_pathFolder / m_path / (m_strName + ".tar.gz");

         auto pmemoryFileTarGz = create_memory_file();

         auto url = m_pathDownloadURL;

         acmeapplication()->m_papexapplication->http().download(url, pmemoryFileTarGz, set);

         //auto pathTar = m_pathFolder / m_path / (m_strName + ".tar");

         pmemoryFileTarGz->seek_to_begin();

         auto pmemoryFileTar = create_memory_file();

         acmesystem()->uncompress(pmemoryFileTar, pmemoryFileTarGz, "zlib");

         pmemoryFileTar->seek_to_begin();

         this->untar(m_pathFolder / m_path, pmemoryFileTar, 1);

      }

   }


   void context::git_clone()
   {
      //preempt(15_s);

      bash("git clone " + m_pathDownloadURL + " .");

   }


   void context::bash(const ::scoped_string & scopedstr)
   {

      string strEscaped = scopedstr;

      ::string strCommand;

      printf("Current Directory: %s\n", acmedirectory()->get_current().c_str());
      printf("%s\n", strEscaped.c_str());

      if (m_bMsys)
      {

         strCommand = "\"C:\\msys64\\usr\\bin\\bash.exe\" -c \'" + strEscaped + "\'";

      }
      else
      {

         strCommand = "\"C:\\Program Files\\Git\\bin\\bash.exe\" -c \'" + strEscaped + "\'";

      }

      //

      command_system(strCommand);

      ///command_system("cmd.exe -c \"C:\\msys64\\msys2_shell.cmd\" \"" + strEscaped + "\"");

      
      

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

               p = path(p).skip_any_character_in("/\\");

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

            ::information(strPathName + "\n");

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


} // namespace integration



