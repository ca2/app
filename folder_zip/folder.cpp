#include "framework.h"
#include "folder.h"
#include "file.h"
#include "file_function_definitions.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/dos_time1.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/prototype/memory.h"

#include "acme/_operating_system.h"

//#ifdef POSIX_PLATFORM

//#include <utime.h>

//#endif

#ifndef _MAX_PATH
#define _MAX_PATH 400
#endif


#ifdef UNIVERSAL_WINDOWS
#define TICKSPERSEC        10000000
#define SECSPERDAY         86400
#define SECS_1601_TO_1970  ((369 * 365 + 89) * (ULONGLONG)SECSPERDAY)
#define TICKS_1601_TO_1970 (SECS_1601_TO_1970 * TICKSPERSEC)
void WINAPI RtlSecondsSince1970ToFileTime(DWORD Seconds, LPFILETIME ft) {
   ULONGLONG secs = Seconds * (ULONGLONG)TICKSPERSEC + TICKS_1601_TO_1970;
   ft->dwLowDateTime = (DWORD)secs;
   ft->dwHighDateTime = (DWORD)(secs >> 32);
   //TRACEN((printf("RtlSecondsSince1970ToFileTime %lx => %lx %lx\n", (long)Seconds, (long)ft->dwHighDateTime, (long)ft->dwLowDateTime)))
}


BOOL WINAPI DosDateTimeToFileTime(WORD fatdate, WORD fattime, LPFILETIME ft) {
   struct tm newtm;
#ifndef HAVE_TIMEGM

   struct tm * gtm;
   time_t time1, time2;
#endif

   //TRACEN((printf("DosDateTimeToFileTime\n")))
   newtm.tm_sec = (fattime & 0x1f) * 2;
   newtm.tm_min = (fattime >> 5) & 0x3f;
   newtm.tm_hour = (fattime >> 11);
   newtm.tm_mday = (fatdate & 0x1f);
   newtm.tm_mon = ((fatdate >> 5) & 0x0f) - 1;
   newtm.tm_year = (fatdate >> 9) + 80;
#ifdef HAVE_TIMEGM

   TRACEN((printf("DosDateTimeToFileTime-1\n")))
      RtlSecondsSince1970ToFileTime(timegm(&newtm), ft);
#else

   //TRACEN((printf("DosDateTimeToFileTime-2\n")))
   time1 = mktime(&newtm);
   gtm = gmtime(&time1);
   time2 = mktime(gtm);
   RtlSecondsSince1970ToFileTime((DWORD) (2 * time1 - time2), ft);
#endif

   return TRUE;
}

#endif

namespace folder_zip
{


   file_function_definitions g_filefunctiondefinitions;


   folder::folder() :
      m_unzip_file(nullptr),
      m_zipfile(nullptr)
   {

      //m_pzlibfilefuncdef = zip_filefuncdef_malloc();

   }


   folder::~folder()
   {

      if (m_unzip_file)
      {

         unzip_Close(m_unzip_file);

         m_unzip_file = nullptr;

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




   void folder::initialize(::particle* pparticle)
   {

      //auto estatus =
      ::object::initialize(pparticle);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void folder::open_for_writing(file_pointer pfile)
   {

      auto zipfile = zipOpen2("pad", APPEND_STATUS_CREATE, nullptr, (zlib_filefunc_def*)&g_filefunctiondefinitions, pfile.m_p);

      m_zipfile = zipfile;

   }


   void folder::open_for_reading(::file_pointer pfile, int iBufferLevel)
   {

      auto unzip_file = unzip_Open2("pad", (zlib_filefunc_def*)&g_filefunctiondefinitions, pfile.m_p);

      m_pfile = pfile;

      m_unzip_file = unzip_file;

   }


   void folder::add_file(const ::file::path & pathRelative, ::file::file* pfile)
   {

      //::file::path strPath(scopedstrDir / pszRelative);

      zip_fileinfo zipfi;

      memory_set(&zipfi, 0, sizeof(zipfi));

      auto timeModification = pfile->modification_time();

      ::earth::time earthtimeCreation(timeModification);

      zipfi.tmz_date.tm_hour = earthtimeCreation.hour();
      zipfi.tmz_date.tm_sec = earthtimeCreation.second();
      zipfi.tmz_date.tm_min = earthtimeCreation.minute();
      zipfi.tmz_date.tm_year = earthtimeCreation.year();
      zipfi.tmz_date.tm_mon = earthtimeCreation.month();
      zipfi.tmz_date.tm_mday = earthtimeCreation.day();

#ifdef WINDOWS_DESKTOP

      auto filetimeLocal = as_FILETIME(file_time(timeModification));

      WORD dosDate = 0;
      WORD dosTime = 0;

      ::FileTimeToDosDateTime(&filetimeLocal, &dosDate, &dosTime);

      zipfi.dosDate = (dosDate << 16) | (dosTime);

#endif

      zipOpenNewFileInZip(m_zipfile, pathRelative, &zipfi, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

      memory mem;

      mem.set_size(256_KiB);

      memsize uRead;

      while ((uRead = pfile->read(mem)) > 0)
      {

         zipWriteInFileInZip(m_zipfile, mem.begin(), (unsigned int)uRead);

      }

      zipCloseFileInZip(m_zipfile);

   }


   bool folder::enumerate(::file::listing_base& listing)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      unzip_File pf = m_unzip_file;

      if (pf == nullptr)
      {

         throw ::exception(error_failed);

         //return listing;

      }

      string str;
      string wstrFolder;
      string_array_base wstraFolder;

      unzip__file_info unzip_fileinfo;

      string strPrefix = listing.m_pathFinal;

      strPrefix.trim("\\/");

      if (strPrefix.has_character())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      int err = unzip_GoToFirstFile(pf);

      ::file::path path;

      ::file::path pathBaseFolder(strPrefix);

      while (err == UNZ_OK)
      {

         char szTitle[_MAX_PATH];

         unzip_GetCurrentFileInfo(
            pf,
            &unzip_fileinfo,
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

               if (strTitle.has_character())
               {

                  path = pathBaseFolder / strTitle;

                  path.m_iBasePathLength = pathBaseFolder.length() + 1;

                  if(strTitle.ends("/") || strTitle.ends("\\") || strTitle.ends(".zip"))
                  {

                     path.set_folder_path();

                  }
                  else
                  {

                     path.set_file_path();

                  }

                  path.m_iSize = unzip_fileinfo.uncompressed_size;

                  listing.defer_add(path);

               }

            }

         }

         err = unzip_GoToNextFile(pf);

      }

      return true;

   }


   ::file_pointer folder::get_file(const ::file::path& pathFile)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (pathFile.has_character())
      {

         if (pathFile.contains("-256.png"))
         {

            informationf("-256.png");

         }

         if (!locate_file(pathFile))
         {

            return nullptr;

         }

      }

      return this->get_file();

   }



   ::file_pointer folder::get_file()
   {

      auto pfile = øcreate_new < ::folder_zip::file >();

      pfile->m_pfolder = this;

      pfile->m_estatus = ::success;

      pfile->set_ok_flag();

      return pfile;

   }


   void folder::extract(memory& m, const ::file::path& pathFile)
   {

      auto pfile = get_file(pathFile);

      if (!pfile || pfile.nok())
      {

         m.clear();

         return;

      }

      m = pfile->full_memory();

   }


   bool folder::is_compressed(const ::file::path& path)
   {

      return false;

   }


   void folder::didnt_locate_file(const_char_pointer pszFile)
   {

      m_strLogNotFound.append("The file \"" + ::string(pszFile) + "\" wasn't find in the zip folder.");

      //::fflush(stdout);

   }

   class ::time folder::get_modification_time() const
   {

      class ::time time;

#ifdef WINDOWS


      auto dosDate = m_unzip_fileinfo.dosDate;


#ifdef WINDOWS_DESKTOP

      ::FILETIME filetimeLocal;
      ::FILETIME filetime;

      ::DosDateTimeToFileTime((WORD)(dosDate >> 16), (WORD)dosDate, &filetimeLocal);

      ::LocalFileTimeToFileTime(&filetimeLocal, &filetime);

      time = class ::time(as_file_time(filetime));

#else

      time.m_iSecond = dos_time_unix_time((dostime_t) dosDate).m_iSecond;
      time.m_iNanosecond = 0;

#endif

#else

      auto tmu_date = m_unzip_fileinfo.tmu_date;

      struct tm newdate;

      newdate.tm_sec = tmu_date.tm_sec;
      newdate.tm_min = tmu_date.tm_min;
      newdate.tm_hour = tmu_date.tm_hour;
      newdate.tm_mday = tmu_date.tm_mday;
      newdate.tm_mon = tmu_date.tm_mon;

      if (tmu_date.tm_year > 1900)
         newdate.tm_year = tmu_date.tm_year - 1900;
      else
         newdate.tm_year = tmu_date.tm_year;

      newdate.tm_isdst = -1;

      time.m_iSecond = mktime(&newdate);
      time.m_iNanosecond = 0;

#endif

      return time;

   }


   void folder::e_extract_all(const ::file::path& pathTargetDir, ::file::path_array_base* ppatha, string_array_base* pstraFilter, bool_array* pbaBeginsFilterEat, ::function<bool(const::scoped_string& scopedstr) > functionCallback)
   {

      ::file::listing_base listing;

      listing.m_bRecursive = true;

      enumerate(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pathTargetDir;

      for (auto& pathItem : listing)
      {
         
         auto range = pathItem.get_count_parts_from_beginning(m_iConsumeFromPathBeginningWhenExtracting);
         
         if(::is_null(range.m_begin))
         {
            
            continue;
            
         }
      
         ::memory memory;

         bool bExtract = true;

         if (functionCallback)
         {

            bExtract = functionCallback(pathItem);

         }

         if (bExtract)
         {

            extract(memory, pathItem);

            if (memory.is_set())
            {

               auto pathTarget = pathTargetFolder / range;

               file_system()->put_block(pathTarget, memory);

               auto time = get_modification_time();

               file_system()->set_modification_time(pathTarget, time);

            }

         }

      }

   }


   ::file::path folder::e_extract_first_ends(const ::file::path& pathTargetDir, const ::scoped_string & scopedstrSuffix)
   {

      ::file::listing_base listing;

      listing.m_bRecursive = true;

      enumerate(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pathTargetDir;

      for (auto& path : listing)
      {

         ::memory memory;

         if (path.case_insensitive_ends(scopedstrSuffix))
         {

            extract(memory, path);

            if (!memory.is_set())
            {

               throw ::exception(error_failed);

            }

            {

               auto pathTarget = pathTargetFolder / path;

               file_system()->put_block(pathTarget, memory);

               auto time = get_modification_time();

               file_system()->set_modification_time(pathTarget, time);

               return pathTarget;

            }

         }

      }

      return {};

   }


   bool folder::locate_file(const ::file::path& pathFileName)
   {

      m_iFilePosition = -1;

      string strFile(pathFileName);

      auto pFind = strFile.find(":");

      if (::found(pFind))
      {

         strFile = strFile(0, pFind);

      }

      if (!locate([strFile](const_char_pointer psz) {return strFile.case_insensitive_equals(psz); }))
      {

         return false;

      }

      if (unzip_OpenCurrentFile(m_unzip_file) != UNZ_OK)
      {

         return false;

      }

      if (unzip_GetCurrentFileInfo(m_unzip_file,
         &m_unzip_fileinfo,
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


   bool folder::locate(const ::function < bool(const_char_pointer )>& function)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      unzip_File pf = m_unzip_file;

      if (pf == nullptr)
      {

         throw ::exception(error_failed);

      }

      int err = unzip_GoToFirstFile(pf);

      unzip__file_info unzip_fileinfo;

      int i = 0;

      while (err == UNZ_OK)
      {

         char szItem[_MAX_PATH];

         unzip_GetCurrentFileInfo(
            pf,
            &unzip_fileinfo,
            szItem,
            _MAX_PATH,
            nullptr, // extra Field
            0,
            nullptr, // comment
            0);

         //         if (::const_ansi_range(szItem).begins("game/"))
         //         {
         //
         //            printf("%s\n", szItem);
         //
         //         }
         //         else if(i == 237)
         //         {
         //
         //            printf("237 %s\n", szItem);
         //
         //            const_ansi_range range("app/_matter/main/_std/_std/Thomas Borregaard Soerensen.dedicatory");
         //
         //            const_ansi_range rangeBlock(szItem);
         //
         //            auto equality = ::comparison::comparison < char >();
         //
         //            while (range.begin() < range.end())
         //            {
         //
         //               if (!equality.equals(*range.begin(), *rangeBlock.begin()))
         //               {
         //
         //                  printf("237 different\n");
         //
         //                  break;
         //
         //               }
         //
         //               range.begin()++;
         //
         //               rangeBlock.begin()++;
         //
         //            }
         //
         //            printf("237 equal if not different\n");
         //
         //         } else{
         //
         //            printf("%05d %s\n", i, szItem);
         //
         //         }

     /*    if (strstr(szItem, "certificate") != nullptr)
         {

            output_debug_string("certificate!!");

         }

         information() << "zipresource://" << szItem;*/

         // output_debug_string(szItem);
         //
         // ::string strDebug(szItem);
         //
         // if (strDebug.case_insensitive_ends("/wavefront.vert")
         //    && strDebug.case_insensitive_contains("/_std/_std/"))
         // {
         //
         //    information("/wavefront.vert with /_std/_std/");
         //
         // }
         //
         // ::print_line(strDebug);

         if (function(szItem))
         {

            return true;

         }

         //if (strstr(szItem, "Thomas Borregaard") != nullptr)
         //{

         //   output_debug_string("Thommi!!");

         //}

         err = unzip_GoToNextFile(pf);

         i++;

      }

      return false;

   }


   bool folder::locate_folder(const ::file::path& pathFolderName)
   {

      if (pathFolderName.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      string strPrefix(pathFolderName);

      strPrefix.trim_left("\\/");

      strPrefix.trim("\\/");

      if (strPrefix.is_empty())
      {

         throw exception(::error_bad_argument);

      }

      if (strPrefix.has_character())
      {

         strPrefix += "/";

      }

      bool bLocated = locate([strPrefix](const_char_pointer pszItem)
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


   bool folder::has_sub_folder(const ::file::path& pathFolderName)
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

      if (strPrefix.has_character())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      bool bLocated = locate([strPrefix](const_char_pointer pszItem)
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


} // namespace folder_zip



