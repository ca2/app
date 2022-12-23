﻿#include "framework.h"
#include "folder.h"
#include "file.h"
#include "file_function_definitions.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/primitive/memory.h"


#ifndef _MAX_PATH
#define _MAX_PATH 400
#endif


namespace folder_zip
{


   file_function_definitions g_filefunctiondefinitions;


   folder::folder() :
      m_unzfile(nullptr),
      m_zipfile(nullptr)
   {

      defer_create_synchronization();
      //m_pzlibfilefuncdef = zip_filefuncdef_malloc();
          
   }


   folder::~folder()
   {

      if (m_unzfile)
      {

         unzClose(m_unzfile);

         m_unzfile = nullptr;

      }

      if (m_zipfile)
      {

         zipClose(m_zipfile, "zipFile");

         m_zipfile = nullptr;

      }

      //if (m_pzlibfilefuncdef)
      //{

      //   ::free(m_pzlibfilefuncdef);

      //   m_pzlibfilefuncdef = nullptr;

      //}

   }




   void folder::initialize(::particle * pparticle)
   {

      //auto estatus =
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void folder::open_for_writing(file_pointer pfile)
   {

      auto zipfile = zipOpen2("pad", APPEND_STATUS_CREATE, nullptr, (zlib_filefunc_def *)&g_filefunctiondefinitions, pfile.m_p);

      m_zipfile = zipfile;

   }


   void folder::open_for_reading(::file_pointer pfile, int iBufferLevel)
   {

      auto unzfile = unzOpen2("pad", (zlib_filefunc_def*)&g_filefunctiondefinitions, pfile.m_p);

      m_pfile = pfile;

      m_unzfile = unzfile;

   }

   
   void folder::add_file(const ::file::path & pszRelative, ::file::file * pfile)
   {

      //::file::path strPath(pszDir / pszRelative);

      ::file::file_status status;

      pfile->get_status(status);

      zip_fileinfo zipfi;

      memory_set(&zipfi,0,sizeof(zipfi));

      zipfi.tmz_date.tm_hour = status.m_ctime.hour();
      zipfi.tmz_date.tm_sec  = status.m_ctime.second();
      zipfi.tmz_date.tm_min  = status.m_ctime.minute();
      zipfi.tmz_date.tm_year = status.m_ctime.year();
      zipfi.tmz_date.tm_mon  = status.m_ctime.month();
      zipfi.tmz_date.tm_mday = status.m_ctime.day();

      zipOpenNewFileInZip(m_zipfile,pszRelative,&zipfi,nullptr,0,nullptr,0,nullptr,Z_DEFLATED,Z_DEFAULT_COMPRESSION);

      memory mem;

      mem.set_size(256 * 1024);

      memsize uRead;

      while((uRead = pfile->read(mem,mem.size())) > 0)
      {

         zipWriteInFileInZip(m_zipfile,mem.begin(),(u32)uRead);

      }

      zipCloseFileInZip(m_zipfile);

   }


   bool folder::enumerate(::file::listing & listing)
   {

      synchronous_lock synchronouslock(this->synchronization());

      unzFile pf = m_unzfile;

      if (pf == nullptr)
      {

         throw ::exception(error_failed);

         //return listing;

      }

      string str;
      string wstrFolder;
      string_array wstraFolder;

      unz_file_info unzfileinfo;

      string strPrefix = listing.m_pathFinal;

      strPrefix.trim("\\/");

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      int err = unzGoToFirstFile(pf);

      ::file::path path;

      ::file::path pathBaseFolder(strPrefix);

      while (err == UNZ_OK)
      {

         char szTitle[_MAX_PATH];

         unzGetCurrentFileInfo(
         pf,
         &unzfileinfo,
         szTitle,
         _MAX_PATH,
         nullptr, // extra Field
         0,
         nullptr, // comment
         0);
            
         string strTitle(szTitle);

         if (strPrefix.is_empty() || strTitle.case_insensitive_begins_eat(strPrefix))
         {

            if (listing.m_bRecursive || !strTitle.contains("/") || strTitle.find_index("/") == (strTitle.length() - 1))
            {
               
               if (strTitle.has_char())
               {

                  path = pathBaseFolder / strTitle;

                  path.m_iBasePathLength = pathBaseFolder.length() + 1;

                  path.m_iDir = strTitle.ends("/") || strTitle.ends("\\") || strTitle.ends(".zip");

                  path.m_iSize = unzfileinfo.uncompressed_size;

                  listing.defer_add(path);

               }

            }

         }

         err = unzGoToNextFile(pf);

      }

      return true;

   }

   
   ::file_pointer folder::get_file(const ::file::path & pathFile)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (::is_set(pathFile))
      {

         if (!locate_file(pathFile))
         {

            return nullptr;

         }

      }

      auto pfile = __new(::folder_zip::file);

      pfile->m_pfolder = this;

      return pfile;

   }


   void folder::extract(memory& m, const ::file::path & pathFile)
   {

      auto pfile = get_file(pathFile);

      m = pfile->as_memory();

   }


   bool folder::is_compressed(const ::file::path & path)
   {

      return false;

   }


   void folder::e_extract_all(const ::file::path & pathTargetDir, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
   {

      ::file::listing listing;

      enumerate(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pathTargetDir;

      for (auto & path : listing)
      {

         ::memory memory;

         extract(memory, path);

         if (memory.is_set())
         {

            auto pathTarget = pathTargetFolder / path;

            acmefile()->put_block(pathTarget, memory);

         }

      }

   }


   bool folder::locate_file(const ::file::path & pathFileName)
   {

      m_iFilePosition = -1;

      string strFile(pathFileName);

      auto pFind = strFile.find(":");

      if (::is_set(pFind))
      {

         strFile = strFile(0, pFind);

      }
      
      strFile.replace_with("/", "\\");

      if (!locate([strFile](const char * psz) {return strFile.case_insensitive_equals(psz); }))
      {

         strFile.replace_with("\\", "/");

         if (!locate([strFile](const char * psz) {return strFile.case_insensitive_equals(psz); }))
         {

            return false;

         }

      }

      if (unzOpenCurrentFile(m_unzfile) != UNZ_OK)
      {

         return false;

      }

      if (unzGetCurrentFileInfo(m_unzfile,
         &m_unzfileinfo,
         nullptr,
         0,
         nullptr,
         0,
         nullptr,
         0) != UNZ_OK)
      {

         return false;

      }

      m_iFilePosition = 0;

      m_strCurrent = strFile;

      return true;

   }

   
   bool folder::locate(const ::function < bool(const char*) > & function)
   {

      synchronous_lock synchronouslock(this->synchronization());

      unzFile pf = m_unzfile;

      if (pf == nullptr)
      {

         throw ::exception(error_failed);

      }

      int err = unzGoToFirstFile(pf);

      unz_file_info unzfileinfo;

      while (err == UNZ_OK)
      {

         char szItem[_MAX_PATH];

         unzGetCurrentFileInfo(
            pf,
            &unzfileinfo,
            szItem,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);

         if (function(szItem))
         {

            return true;

         }

         err = unzGoToNextFile(pf);

      }

      return false;

   }


   bool folder::locate_folder(const ::file::path & pathFolderName)
   {

      if (pathFolderName.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      string strPrefix(pathFolderName);

      strPrefix.trim("\\/");

      if (strPrefix.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      bool bLocated = locate([strPrefix](const char * pszItem)
         {

            string strItem(pszItem);

            if (strItem.case_insensitive_begins(strPrefix))
            {

               return true;

            }

            return false;

         });

      return bLocated;

   }


   bool folder::has_sub_folder(const ::file::path & pathFolderName)
   {

      if (pathFolderName.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      string strPrefix(pathFolderName);

      strPrefix.trim("\\/");

      if (strPrefix.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      bool bLocated = locate([strPrefix](const char * pszItem)
         {

            string strItem(pszItem);

            if (strItem.case_insensitive_begins_eat(strPrefix))
            {

               if (strItem.contains("/"))
               {

                  return true;

               }

            }

            return false;

         });

      return bLocated;

   }


} // namespace zip



