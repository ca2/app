#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif
#include "acme/filesystem/filesystem/acme_file.h"


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

      defer_create_mutex();
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




   void folder::initialize(::object* pobject)
   {

      //auto estatus =
      ::object::initialize(pobject);

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

      __memset(&zipfi,0,sizeof(zipfi));

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

      while((uRead = pfile->read(mem,mem.get_size())) > 0)
      {

         zipWriteInFileInZip(m_zipfile,mem.get_data(),(u32)uRead);

      }

      zipCloseFileInZip(m_zipfile);

   }


   bool folder::enumerate(::file::listing & listing)
   {

      synchronous_lock synchronouslock(mutex());

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

         if (strPrefix.is_empty() || strTitle.begins_eat_ci(strPrefix))
         {

            if (listing.m_bRecursive || strTitle.find("/") < 0 || strTitle.find("/") == (strTitle.get_length() - 1))
            {
               
               if (strTitle.has_char())
               {

                  path = pathBaseFolder / strTitle;

                  path.m_iBasePathLength = pathBaseFolder.get_length() + 1;

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

   
   ::file_pointer folder::get_file(const char* pszFile)
   {

      synchronous_lock synchronouslock(mutex());

      if (::is_set(pszFile))
      {

         if (!locate_file(pszFile))
         {

            return nullptr;

         }

      }

      auto pfile = __new(::folder_zip::file);

      pfile->m_pfolder = this;

      return pfile;

   }


   void folder::extract(memory& m, const char* pszFile)
   {

      auto pfile = get_file(pszFile);

      pfile->full_read(m);

   }


   bool folder::is_compressed(const char* pszFileName)
   {

      return false;

   }


   void folder::extract_all(const char* pszTargetDir, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
   {

      ::file::listing listing;

      enumerate(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pszTargetDir;

      for (auto & path : listing)
      {

         ::memory memory;

         extract(memory, path);

         if (memory.has_data())
         {

            auto pathTarget = pathTargetFolder / path;

            m_psystem->m_pacmefile->put_block(pathTarget, memory);

         }

      }

   }


   bool folder::locate_file(const char* pszFileName)
   {

      m_iFilePosition = -1;

      string strFile(pszFileName);

      index iFind = strFile.find(":");

      if (iFind >= 0)
      {

         strFile = strFile.Left(iFind);

      }
      
      strFile.replace_with("/", "\\");

      if (!locate([strFile](const char* psz) {return strFile.compare_ci(psz) == 0; }))
      {

         strFile.replace_with("\\", "/");

         if (!locate([strFile](const char* psz) {return strFile.compare_ci(psz) == 0; }))
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

      synchronous_lock synchronouslock(mutex());

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


   bool folder::locate_folder(const char * pszFolderName)
   {

      if (::is_empty(pszFolderName))
      {

         throw exception(::error_bad_argument);

      }

      string strPrefix(pszFolderName);

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

      bool bLocated = locate([strPrefix](const char* pszItem)
         {

            string strItem(pszItem);

            if (strItem.begins_ci(strPrefix))
            {

               return true;

            }

            return false;

         });

      return bLocated;

   }


   bool folder::has_sub_folder(const char* pszFolderName)
   {

      if (::is_empty(pszFolderName))
      {

         throw exception(::error_bad_argument);

      }

      string strPrefix(pszFolderName);

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

      bool bLocated = locate([strPrefix](const char* pszItem)
         {

            string strItem(pszItem);

            if (strItem.begins_eat_ci(strPrefix))
            {

               if (strItem.contains('/'))
               {

                  return true;

               }

            }

            return false;

         });

      return bLocated;

   }


} // namespace zip



