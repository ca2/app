﻿// Created by camilo on 2023-01-15 16:16 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "integration_context.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"
#include "libarchive/archive.h"
#include "libarchive/archive_entry.h"


namespace integration
{


   context::context()
   {

      m_bMsys = false;

   }


   context::~context()
   {


   }


   void context::prepare_compile_and_link_environment()
   {

   }


   int context::command_system(const ::scoped_string & scopedstrCommand)
   {

      int iExitCode = 0;

      acmenode()->command_system(m_straOutput, iExitCode, scopedstrCommand, e_command_system_inline_log);

      return iExitCode;

   }


   void context::clean()
   {

      string strCommand;

      string strPath;

      strPath = this->prepare_path(m_pathFolder / m_path);

      if (strPath.length() > 20)
      {

         strCommand = "shopt -s dotglob; rm -Rf " + strPath + "/*";

         this->bash(strCommand);

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

      command_system("git clone " + m_pathDownloadURL + " .");

   }


   void context::bash(const ::scoped_string & scopedstr)
   {

      string strEscaped = scopedstr;

      ::string strCommand;

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
      memory2.set_size(1_mb);
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
               pfile->write(memory2.data(), size);
               //write(1, buff, size);
            }

            ::output_debug_string(strPathName + "\n");

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


