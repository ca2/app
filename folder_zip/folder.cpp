#include "framework.h"
#include "folder.h"
#include "file.h"
#include "file_function_definitions.h"
#include "acme/filesystem/file/status.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/operating_system/dos_time.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/primitive/memory.h"

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
      m_unzfile(nullptr),
      m_zipfile(nullptr)
   {

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

      auto unzfile = unzOpen2("pad", (zlib_filefunc_def*)&g_filefunctiondefinitions, pfile.m_p);

      m_pfile = pfile;

      m_unzfile = unzfile;

   }


   void folder::add_file(const ::file::path& pszRelative, ::file::file* pfile)
   {

      //::file::path strPath(pszDir / pszRelative);

      zip_fileinfo zipfi;

      memory_set(&zipfi, 0, sizeof(zipfi));

      auto timeModification = pfile->modification_time();

      ::earth::time earthtimeCreation(timeModification.m_iSecond);

      zipfi.tmz_date.tm_hour = earthtimeCreation.hour();
      zipfi.tmz_date.tm_sec = earthtimeCreation.second();
      zipfi.tmz_date.tm_min = earthtimeCreation.minute();
      zipfi.tmz_date.tm_year = earthtimeCreation.year();
      zipfi.tmz_date.tm_mon = earthtimeCreation.month();
      zipfi.tmz_date.tm_mday = earthtimeCreation.day();

#ifdef WINDOWS_DESKTOP

      FILETIME filetimeLocal;

      ::time_to_file_time((file_time_t *) & filetimeLocal, &timeModification);

      WORD dosDate = 0;
      WORD dosTime = 0;

      ::FileTimeToDosDateTime(&filetimeLocal, &dosDate, &dosTime);

      zipfi.dosDate = (dosDate << 16) | (dosTime);

#endif

      zipOpenNewFileInZip(m_zipfile, pszRelative, &zipfi, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

      memory mem;

      mem.set_size(256 * 1024);

      memsize uRead;

      while ((uRead = pfile->read(mem)) > 0)
      {

         zipWriteInFileInZip(m_zipfile, mem.begin(), (u32)uRead);

      }

      zipCloseFileInZip(m_zipfile);

   }


   bool folder::enumerate(::file::listing& listing)
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


   ::file_pointer folder::get_file(const ::file::path& pathFile)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (pathFile.has_char())
      {

         if (pathFile.contains("-256.png"))
         {

            ::information("-256.png");

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

      auto pfile = __create_new < ::folder_zip::file >();

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


   void didnt_locate_file(const char * pszFile)
   {

      ::information("The file \"" + ::string(pszFile) + "\" wasn't find in the zip folder.");

      ::fflush(stdout);

   }

   class ::time folder::get_modification_time() const
   {

      class ::time time;

#ifdef WINDOWS


      auto dosDate = m_unzfileinfo.dosDate;


#ifdef WINDOWS_DESKTOP

      ::file_time_t filetimeLocal;
      ::file_time_t filetime;

      ::DosDateTimeToFileTime((WORD)(dosDate >> 16), (WORD)dosDate, (LPFILETIME)&filetimeLocal);

      ::LocalFileTimeToFileTime((LPFILETIME)&filetimeLocal, (LPFILETIME)&filetime);

      ::file_time_to_time(&time, &filetime);

#else

      time.m_iSecond = dos_time_unix_time((dostime_t) dosDate);
      time.m_iNanosecond = 0;

#endif

#else

      auto tmu_date = m_unzfileinfo.tmu_date;

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


   void folder::e_extract_all(const ::file::path& pathTargetDir, ::file::path_array* ppatha, string_array* pstraFilter, bool_array* pbaBeginsFilterEat)
   {

      ::file::listing listing;

      listing.m_bRecursive = true;

      enumerate(listing);

      ::file::path pathTargetFolder;

      pathTargetFolder = pathTargetDir;

      for (auto& path : listing)
      {

         ::memory memory;

         extract(memory, path);

         if (memory.is_set())
         {

            auto pathTarget = pathTargetFolder / path;

            acmefile()->put_block(pathTarget, memory);

            auto time = get_modification_time();

            acmefile()->set_modification_time(pathTarget, time);

         }

      }

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

      strFile.trim_left("\\/");

      strFile.replace_with("/", "\\");

      if (!locate([strFile](const char* psz) {return strFile.case_insensitive_equals(psz); }))
      {

         strFile.replace_with("\\", "/");

         if (!locate([strFile](const char* psz) {return strFile.case_insensitive_equals(psz); }))
         {

            didnt_locate_file(strFile);

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


   bool folder::locate(const ::function < bool(const char*) >& function)
   {

      synchronous_lock synchronouslock(this->synchronization());

      unzFile pf = m_unzfile;

      if (pf == nullptr)
      {

         throw ::exception(error_failed);

      }

      int err = unzGoToFirstFile(pf);

      unz_file_info unzfileinfo;

      int i = 0;

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

         if (function(szItem))
         {

            return true;

         }

         err = unzGoToNextFile(pf);

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

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      bool bLocated = locate([strPrefix](const char* pszItem)
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

      if (strPrefix.has_char())
      {

         strPrefix += "/";

      }

      strPrefix.replace_with("/", "\\");

      bool bLocated = locate([strPrefix](const char* pszItem)
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



