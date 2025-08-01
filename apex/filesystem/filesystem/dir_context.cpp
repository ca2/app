#include "framework.h"
#include "directory_context.h"
#include "file_context.h"
#include "directory_system.h"
#include "acme/filesystem/filesystem/link.h"
//#include "apex/compress/not_dir.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/prototype/prototype/url.h"
#include "acme/parallelization/happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task_flag.h"
#include "acme/prototype/string/_string.h"
#include "acme/prototype/string/str.h"
//#include "acme/prototype/string/tokenizer.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
//#include "acmepex/filesystem/filesystem/directory_system.h"
//#include "apex/networking/http/context.h"


namespace zip
{

   class Util;

}

#ifdef WINDOWS

#define DIR_SEPARATOR "\\"

#else

#define DIR_SEPARATOR "/"

#endif


//namespace file
//{
//
//
//
//   directory_context * directory_context::g_pthis = nullptr;
//

directory_context::directory_context()
{

   m_bDropboxCalculated = false;

   //if (::file::directory_context::g_pthis == nullptr)
   //{

   //   ::file::directory_context::g_pthis = this;

   //   increment_reference_count();

   //}

   //m_pziputil = nullptr;

   //         m_isdirmap.m_timeTimeout = 180000;



}


directory_context::~directory_context()
{

   //::acme::del(m_pziputil);

}


void directory_context::initialize(::particle * pparticle)
{

   /*auto estatus = */ ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void directory_context::init_system()
{

   //return ::success;

}



void directory_context::init_context()
{

   //return ::success;

}


inline bool myspace(char ch)
{
   return ch == ' ' ||
      ch == '\t' ||
      ch == '\r' ||
      ch == '\n';
}

#define string_STRCAT2_beg_char_end(strCat, ch, str1, str2, beg1, end1, beg2, end2) \
{ \
   string & psz = strCat.get_buffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
   ansi_count_copy(scopedstr, &((const string &)str1)[beg1], end1 - beg1 + 1); \
   psz[end1 - beg1 + 1] = ch; \
   ansi_count_copy(&psz[end1 - beg1 + 2], &((const string &)str2)[beg2], end2 - beg2 + 1); \
   strPath.ReleaseBuffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
}

//::file::path directory_context::simple_path(const ::scoped_string & scopedstrFolder, const ::scoped_string & scopedstrRelative)
//{

//   if(strRelative.is_empty())
//   {
//      if(strFolder.is_empty())
//         return "";
//      return strFolder;
//   }

//   character_count iFolderBeg = 0;

//   character_count iFolderEnd = strFolder.length() - 1;

//   if(iFolderEnd >= iFolderBeg)
//   {
//      //strFolder.trim();
//      // passive left trimming
//      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
//         iFolderBeg++;
//      // passive right trimming
//      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
//         iFolderEnd--;
//      //better than following 2 together
//      //strFolder.ends_eat("\\");
//      //strFolder.ends_eat("/");
//      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
//         iFolderEnd--;
//   }

//   character_count iRelativeBeg = 0;

//   character_count iRelativeEnd = strRelative.length() - 1;

//   if(iRelativeEnd >= iRelativeBeg)
//   {
//      //strFolder.trim();
//      // passive left trimming
//      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
//         iFolderBeg++;
//      // passive right trimming
//      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
//         iFolderEnd--;
//      //better than following 2 together
//      //strFolder.ends_eat("\\");
//      //strFolder.ends_eat("/");
//      while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
//         iRelativeBeg++;
//   }

//   string strPath;
//   if(iFolderBeg > iFolderEnd)
//   {
//      strPath = strRelative;
//   }
//   else
//   {
//      string & psz = strPath.get_buffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
//      ansi_count_copy(scopedstr, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
//      #if defined(LINUX) || defined(__APPLE__)
//      psz[iFolderEnd - iFolderBeg + 1] = '/';
//      #else
//      psz[iFolderEnd - iFolderBeg + 1] = '\\';
//      #endif
//      ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
//      strPath.ReleaseBuffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
//   }


//   return strPath;
//}

//::file::path directory_context::simple_path(const ::scoped_string & scopedstrFolder, const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstr2)
//{

//   if(strRelative.is_empty())
//   {
//      if(str2.is_empty())
//      {
//         if(strFolder.is_empty())
//            return "";
//         return strFolder;
//      }
//      else
//      {
//         if(strFolder.is_empty())
//            return str2;
//         return simple_path(strFolder, str2);
//      }
//   }
//   else if(strFolder.is_empty())
//   {
//      if(str2.is_empty())
//      {
//         return strRelative;
//      }
//      else
//      {
//         return simple_path(strRelative, str2);
//      }
//   }
//   else if(str2.is_empty())
//   {
//      return simple_path(strFolder, strRelative);
//   }

//   // none of them - 3 - are empty

//   character_count iFolderBeg = 0;

//   character_count iFolderEnd = strFolder.length() - 1;

//   if(iFolderEnd >= iFolderBeg)
//   {
//      //strFolder.trim();
//      // passive left trimming
//      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
//         iFolderBeg++;
//      // passive right trimming
//      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
//         iFolderEnd--;
//      //better than following 2 together
//      //strFolder.ends_eat("\\");
//      //strFolder.ends_eat("/");
//      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
//         iFolderEnd--;
//   }

//   character_count iRelativeBeg = 0;

//   character_count iRelativeEnd = strRelative.length() - 1;

//   if(iRelativeEnd >= iRelativeBeg)
//   {
//      //strFolder.trim();
//      // passive left trimming
//      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
//         iFolderBeg++;
//      // passive right trimming
//      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
//         iFolderEnd--;
//      //better than following 2 together
//      //strFolder.ends_eat("\\");
//      //strFolder.ends_eat("/");
//      while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
//         iRelativeBeg++;
//   }


//   character_count iBeg2 = 0;

//   character_count iEnd2 = str2.length() - 1;

//   if(iEnd2 >= iBeg2)
//   {
//      //strFolder.trim();
//      // passive left trimming
//      while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iBeg2]))
//         iBeg2++;
//      // passive right trimming
//      while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iEnd2]))
//         iEnd2--;
//      //better than following 2 together
//      //strFolder.ends_eat("\\");
//      //strFolder.ends_eat("/");
//      while(iBeg2 <= iEnd2 && (str2[iBeg2] == '/' || str2[iBeg2] == '\\'))
//         iBeg2++;
//   }

//   if(iRelativeBeg > iRelativeEnd)
//   {
//      if(iBeg2 > iEnd2)
//      {
//         if(iFolderBeg > iFolderEnd)
//            return "";
//         return strFolder.substr(iFolderBeg, iFolderEnd - iFolderBeg + 1);
//      }
//      else
//      {
//         if(iFolderBeg > iFolderEnd)
//            return str2.substr(iBeg2, iEnd2 - iBeg2 + 1);
//         string strPath;
//         string_STRCAT2_beg_char_end(strPath, '\\', strFolder, str2, iFolderBeg, iFolderEnd, iBeg2, iEnd2);
//         return strPath;
//      }
//   }
//   else if(strFolder.is_empty())
//   {
//      if(str2.is_empty())
//      {
//         return strRelative;
//      }
//      else
//      {
//         string strPath;
//         #if defined(LINUX) || defined(__APPLE__)
//         string_STRCAT2_beg_char_end(strPath, '/', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
//         #else
//         string_STRCAT2_beg_char_end(strPath, '\\', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
//         #endif
//         return strPath;
//      }
//   }
//   else if(str2.is_empty())
//   {
//      string strPath;
//      #if defined(LINUX) || defined(__APPLE__)
//      string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
//      #else
//      string_STRCAT2_beg_char_end(strPath, '/', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
//      #endif
//      return strPath;
//   }

//   string strPath;

//   string & psz = strPath.get_buffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
//   ansi_count_copy(scopedstr, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
//   #if defined(LINUX) || defined(__APPLE__)
//   psz[iFolderEnd - iFolderBeg + 1] = '/';
//   #else
//   psz[iFolderEnd - iFolderBeg + 1] = '\\';
//   #endif
//   ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
//   #if defined(LINUX) || defined(__APPLE__)
//   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '/';
//   #else
//   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '\\';
//   #endif
//   ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1 + 1], &((const string &)str2)[iBeg2], iEnd2 - iBeg2 + 1);
//   strPath.ReleaseBuffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);

//   return strPath;

//}


//::file::path directory_context::relpath(const string & pcszSource,const string & lpcszRelative)

//{
//   __UNREFERENCED_PARAMETER(pcszSource);

//   __UNREFERENCED_PARAMETER(pcszRelative);

//   throw ::interface_only("this is an interface");
//}


//::file::path directory_context::relpath(const string & pcszSource, const string & lpcszRelative, const ::scoped_string & scopedstr2)

//{
//   __UNREFERENCED_PARAMETER(pcszSource);

//   __UNREFERENCED_PARAMETER(pcszRelative);

//   __UNREFERENCED_PARAMETER(scopedstr2);
//   throw ::interface_only("this is an interface");
//}


::file::listing& directory_context::root_ones(::file::listing& listing)
{

   throw ::interface_only("this is an interface");

   return listing;

}


//bool directory_context::enumerate(::file::listing & listing, const ::file::path & path, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   listing.m_pathUser = path;
//
//   listing.m_eflag = eflag;
//
//   listing.m_edepth = edepth;
//
//   return enumerate(listing);
//
//}
//
//
//bool directory_context::enumerate_pattern(::file::listing & listing, const ::file::path & path, const ::string_array & straPattern, ::file::e_flag eflag, enum_depth edepth)
//{
//
//   listing.m_straPattern = straPattern;
//
//   return enumerate(listing, path, eflag, edepth);
//
//}


//bool directory_context::enumerates(::file::listing & listing)
//{
//
//
//   return true;
//
//}


bool directory_context::enumerate(::file::listing& listing)
{

   if(_enumerate(listing))
   {

      return true;

   }

   return directory_system()->enumerate(listing);

}


bool directory_context::_enumerate(::file::listing& listing)
{

   directory_system()->defer_enumerate_media_library(listing);

   listing.m_pathFinal = m_papplication->defer_process_matter_path(listing.m_pathUser);

   if (listing.m_pathFinal.case_insensitive_begins("matter://"))
   {

      listing.m_pathFinal.case_insensitive_begins_eat("matter://");

      if (matter_enumerate(listing.m_pathFinal, listing))
      {

         return true;

      }

   }
   else if (listing.m_pathFinal.case_insensitive_begins("zipresource://"))
   {

      listing.m_pathFinal.case_insensitive_begins_eat("zipresource://");

      auto pfolder = file()->resource_folder();

      if (pfolder->enumerate(listing))
      {

         ::file::path pathBase("zipresource://");

         for (auto& path : listing)
         {

            path = pathBase / path;

         }

         return true;

      }

   }

   if (listing.m_bRecursive)
   {

      return false;

   }

   if (listing.m_pathFinal.case_insensitive_begins("http://") || listing.m_pathFinal.case_insensitive_begins("https://"))
   {

      ::property_set set;

      string str = http()->get(listing.m_pathFinal, set);

      listing.add_tokens(str, "\n", false);

      return true;

   }
   else if (task_flag().is_set(e_task_flag_compress_is_dir) && (listing.m_pathFinal.case_insensitive_ends(".zip") || ::str::find_file_extension("zip:", listing.m_pathFinal) >= 0))
   {

      auto& pfactory = system()->folder_factory();

      if (!pfactory)
      {

         throw ::exception(error_no_factory);

      }
      else
      {

         auto pfolder = pfactory->create < ::folder >();

         if (!pfolder)
         {

            throw ::exception(error_no_factory);

         }
         else
         {

            file_pointer pfile;

            {

               compress_not_dir notdir;

               pfolder->enumerate(listing);

               return true;

               //   pfile = 

               //pfilecontainer->open_for_reading()

               //zip_context zip(this);

               //zip.ls(listing);

            }

         }

      }

   }

   return false;

}


//bool directory_context::ls_relative_name(::file::listing & listing)
//{
//
//   if (listing.m_bRecursive)
//   {
//
//      return false;
//
//   }
//
//   if (case_insensitive_string_begins(listing.m_pathUser, "http://") || case_insensitive_string_begins(listing.m_pathUser, "https://"))
//   {
//
//      ::property_set set;
//
//      string str = http()->get(listing.m_pathUser, set);
//
//      listing.add_tokens(str, "\n", false);
//
//      return true;
//
//   }
//   else if (::task_flag().is_set(e_task_flag_compress_is_dir) && (case_insensitive_string_ends(listing.m_pathUser, ".zip") || ::str::find_file_extension("zip:", listing.m_pathUser) >= 0))
//   {
//
//      auto & pfactory = system()->folder_factory();
//
//      if (!pfactory)
//      {
//
//         throw ::exception(error_no_factory);
//
//      }
//      else
//      {
//
//         auto pfolder = pfactory->create < ::folder >();
//
//         if (!pfolder)
//         {
//
//            throw ::exception(error_no_factory);
//
//         }
//         else
//         {
//
//            file_pointer pfile;
//
//            {
//
//               compress_not_dir notdir;
//
//               pfolder->perform_file_relative_name_listing(listing);
//
//               return true;
//
//               //   pfile = 
//
//               //pfilecontainer->open_for_reading()
//
//               //zip_context zip(this);
//
//               //zip.ls(listing);
//
//            }
//
//         }
//
//      }
//
//
//   }
//
//   return false;
//
//}


//bool directory_context::rls(::file::listing& listing)
//{
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = true;
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::rls_relative_name(::file::listing& listing)
//{
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = true;
//
//   return ls_relative_name(listing);
//
//}
//
//
//bool directory_context::ls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
//{
//
//   listing.m_pathUser = path;
//
//   listing.m_bRecursive = false;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = true;
//
//   listing.m_straPattern = straPattern;
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::ls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
//{
//
//   listing.m_pathUser = path;
//
//   listing.m_bRecursive = false;
//
//   listing.m_bDir = false;
//
//   listing.m_bFile = true;
//
//   listing.m_straPattern = straPattern;
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::rls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
//{
//
//   listing.m_pathUser = path;
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = true;
//
//   listing.m_straPattern = straPattern;
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::rls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
//{
//
//   listing.m_pathUser = path;
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = false;
//
//   listing.m_bFile = true;
//
//   listing.m_straPattern = straPattern;
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::ls_file(::file::listing& listing)
//{
//
//   listing.m_bRecursive = false;
//
//   listing.m_bDir = false;
//
//   listing.m_bFile = true;
//
//   //listing.m_straPattern.erase_all();
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::ls_dir(::file::listing& listing)
//{
//
//   listing.m_bRecursive = false;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = false;
//
//   listing.m_straPattern.erase_all();
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::rls_file(::file::listing& listing)
//{
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = false;
//
//   listing.m_bFile = true;
//
//   listing.m_straPattern.erase_all();
//
//   return ls(listing);
//
//}
//
//
//bool directory_context::rls_dir(::file::listing& listing)
//{
//
//   listing.m_bRecursive = true;
//
//   listing.m_bDir = true;
//
//   listing.m_bFile = false;
//
//   listing.m_straPattern.erase_all();
//
//   return ls(listing);
//
//}


bool directory_context::has_subdir(const ::file::path& pathFolder)
{

   ::file::listing listing;

   listing.set_folder_listing(pathFolder);

   enumerate(listing);

   return listing.has_element();

}


bool directory_context::is_cached(bool& bIs, const ::file::path& path)
{

   bIs = false;

#ifdef WINDOWS_DESKTOP
#ifdef WINDOWS_DESKTOP
   if (case_insensitive_string_ends(path, ".lnk"))
   {
#endif

      ::file::path pathTarget;

      auto plink = path_system()->resolve_link(pathTarget);

      bIs = plink && plink->m_pathTarget.has_character();

      return true;

      //}

#ifdef WINDOWS_DESKTOP
   }
#endif
#endif

   //bIs = false;

   //if (case_insensitive_string_begins(pcszPath, "http://") || case_insensitive_string_begins(lpcszPath, "https://"))

   //{

   //   ::property_set set;

   //   bIs = Sess(papp).http()->exists(pcszPath, set);


   //   return true;

   //}

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (case_insensitive_string_ends(path, ".zip")))
   {

      bIs = true;

      return true;
   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      //            unsigned int dwLastError;

                  //if (m_isdirmap.lookup(pcszPath, bHasSubFolder, dwLastError))

                  //{

                  //   bIs = bHasSubFolder;

                  //   return true;

                  //}

//      zip_context zip(this);

  //    bHasSubFolder = zip.has_sub_folder(path);


      auto& pfactory = system()->folder_factory();

      if (!pfactory)
      {

         return false;

      }
      else
      {

         auto pfolder = pfactory->create < ::folder >();

         if (!pfolder)
         {

            return false;

         }
         else
         {

            file_pointer pfile;

            {

               compress_not_dir notdir;

               bHasSubFolder = pfolder->has_sub_folder(path);

               //   pfile = 

               //pfilecontainer->open_for_reading()

               //zip_context zip(this);

               //zip.ls(listing);

            }

         }

      }

      //m_isdirmap.set(pcszPath, bHasSubFolder, ::get_last_error());


      bIs = bHasSubFolder;

      return true;

   }

   //#ifdef WINDOWS_DESKTOP
   //#ifdef WINDOWS_DESKTOP
   //         if (case_insensitive_string_ends(pcszPath, ".lnk"))

   //         {
   //#endif
   //
   //            string strTarget;
   //
   //            string strFolder;
   //
   //            string strParams;
   //
   //            if (file()->resolve_link(strTarget, strFolder, strParams, pcszPath))

   //            {
   //
   //               bIs = is(strTarget, pparticle);
   //
   //               return true;
   //
   //            }
   //
   //#ifdef WINDOWS_DESKTOP
   //         }
   //#endif
   //#endif

   //         bool bHasSubFolder;

   //         unsigned int dwLastError;

            //if (!m_isdirmap.lookup(pcszPath, bHasSubFolder, dwLastError))

            //{
            //   return false;
            //}
   //         bIs = bHasSubFolder;
   return false;

}


bool directory_context::is(const ::file::path& pathParam)
{

   if (::is_empty(pathParam))
   {

      return false;

   }

   ::file::path path;

   auto psystem = system();

   if (pathParam.case_insensitive_begins("appmatter://"))
   {

      path = psystem->m_pdirectorysystem->m_pathLocalAppMatterFolder / path.substr(12);

   }
   else
   {

      path = m_papplication->defer_process_matter_path(pathParam);

   }

   bool bIs = false;

   if (!(pathParam.flags() & ::file::e_flag_bypass_cache) && is_cached(bIs, path))
   {

      return bIs;

   }

   return _is(path);

}


bool directory_context::_is(const ::file::path& path)
{

   bool bDir = false;

   if (__is(path, bDir))
   {

      return bDir;

   }

   return directory_system()->is(path);

}


bool directory_context::__is(const ::file::path& path, bool& bDir)
{

   if (path.case_insensitive_ends("://") || path.case_insensitive_ends(":/") || path.case_insensitive_ends(":"))
   {

      bDir = true;

      return true;

   }

   if (case_insensitive_string_begins(path, "http://") || case_insensitive_string_begins(path, "https://"))
   {

      ::property_set set;

      if (path.flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      bDir = http()->exists(path, set);

      return true;

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (case_insensitive_string_ends(path, ".zip")))
   {

      bDir = true;

      return true;

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      auto& pfactory = system()->folder_factory();

      if (!pfactory)
      {

         bHasSubFolder = false;

      }
      else
      {

         auto pfolder = pfactory->create < ::folder >();

         if (!pfolder)
         {

            bHasSubFolder = false;

         }
         else
         {

            file_pointer pfile;

            {

               compress_not_dir notdir;

               bHasSubFolder = pfolder->has_sub_folder(path);

               //   pfile = 

               //pfilecontainer->open_for_reading()

               //zip_context zip(this);

               //zip.ls(listing);

            }

         }

      }

      //zip_context zip(this);

      //bHasSubFolder = zip.has_sub_folder(path);

      //            m_isdirmap.set(path, bHasSubFolder, get_last_error());

      bDir = bHasSubFolder;

      return true;

   }

   return false;

}


bool directory_context::name_is(const ::file::path& strPath)
{

   //information(strPath);
   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (case_insensitive_string_ends(strPath, ".zip")))
   {
      //            m_isdirmap.set(strPath, true, 0);
      return true;
   }
   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", strPath) >= 0))
   {
      bool bHasSubFolder;

      auto& pfactory = system()->folder_factory();

      if (!pfactory)
      {

         bHasSubFolder = false;

      }
      else
      {

         auto pfolder = pfactory->create < ::folder >();

         if (!pfolder)
         {

            bHasSubFolder = false;

         }
         else
         {

            file_pointer pfile;

            {

               compress_not_dir notdir;

               bHasSubFolder = pfolder->has_sub_folder(strPath);

               //   pfile = 

               //pfilecontainer->open_for_reading()

               //zip_context zip(this);

               //zip.ls(listing);

            }

         }

      }

      //      zip_context zip(this);
            //            unsigned int dwLastError;
                        //if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
                        //   return bHasSubFolder;
        //    bHasSubFolder = zip.has_sub_folder(strPath);
            //m_isdirmap.set(strPath, bHasSubFolder, get_last_error());
      return bHasSubFolder;
   }
   return false;


}




//      directory_context::is_dir_map::is_dir_map()
//      {
//
//      }
//
//
//      bool directory_context::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, unsigned int & dwLastError)
//      {
//
//         return lookup(path, bIsDir, dwLastError, (int) path.length());
//
//      }
//
//
//      bool directory_context::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, unsigned int &dwLastError, int iLastChar)
//      {
//
//         if (path.get_length() <= 0)
//         {
//
//            bIsDir = false;
//
//            return true;
//
//         }
//
//         if (iLastChar < 0)
//         {
//
//            bIsDir = true; // root_ones dir
//
//            return true;
//
//         }
//
//         critical_section_lock synchronouslock(m_criticalsection);
//
//         if (path.length() + 1 < 2048)
//         {
//
//            return lookup_small(path, bIsDir, dwLastError, iLastChar);
//
//         }
//         else
//         {
//
//            return lookup_dynamic(path, bIsDir, dwLastError, iLastChar);
//
//         }
//
//      }
//
//
//      bool directory_context::is_dir_map::lookup_dynamic(const ::file::path & path, bool &bIsDir, unsigned int & dwLastError, int iLastChar)
//      {
//
//         is_dir * pdir = this;
//
//         is_dir find;
//
//         index iFind0 = 0;
//
//         index iFind3 = 0;
//
//         while (iFind3 >= 0 && iFind3 < iLastChar)
//         {
//
//            index iFind1 = path.find('/', iFind0);
//
//            index iFind2 = path.find('\\', iFind0);
//
//            iFind3 = minimum_non_negative(iFind1, iFind2);
//
//            if (iFind3 < 0)
//            {
//
//               find.m_str = path.substr(iFind0);
//
//            }
//            else
//            {
//
//               find.m_str = path.substr(iFind0, iFind3 - iFind0);
//
//            }
//
//            auto pFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return t1->m_str.case_insensitive_order(t2->m_str) < 0;
//
//            });
//
//            if (::is_null(pFind))
//            {
//
//               return false;
//
//            }
//
//            pdir = pdir->element_at(iFind);
//
//            iFind0 = iFind3 + 1;
//
//         }
//
//         if (::get_fast_tick_count() > pdir->m_timeLastCheck + m_timeTimeout)
//         {
//
//            return false;
//
//         }
//
//         if (pdir->m_iIsDir < 0)
//         {
//
//            return false;
//
//         }
//
//         bIsDir = pdir->m_iIsDir == 1;
//
//         dwLastError = pdir->m_dwError;
//
//         return true;
//
//      }
//
//
//      bool directory_context::is_dir_map::lookup_small(const ::file::path & path,bool &bIsDir,unsigned int &dwLastError, int iLastChar)
//      {
//
//         const_char_pointer pszEnd = path.c_str() + iLastChar;
//
//         char sz[2048];
//
//         is_dir_work find;
//
//         find.m_psz = sz;
//
//         strcpy(sz, path);
//
//         is_dir * pdir = this;
//
//         char * psz3 = find.m_psz;
//
//         while (scopedstr3 != nullptr && psz3 < pszEnd)
//         {
//
//            char * psz1 = strchr(find.m_psz, '/');
//
//            char * psz2 = strchr(find.m_psz, '\\');
//
//            psz3 = min_non_null(scopedstr1, psz2);
//
//            if (scopedstr3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            auto pFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return case_insensitive_ansi_compare(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (::is_null(pFind))
//            {
//
//               return false;
//
//            }
//
//            pdir = pdir->element_at(iFind);
//
//            find.m_psz = psz3 + 1;
//
//            if (scopedstr1 == nullptr)
//            {
//
//               goto lookup_backslash;
//
//            }
//            else if (scopedstr2 == nullptr)
//            {
//
//               goto lookup_slash;
//
//            }
//
//         }
//
//         goto end;
//
//lookup_slash:
//
//         while (scopedstr3 != nullptr && psz3 < pszEnd)
//         {
//
//            psz3 = strchr(find.m_psz, '/');
//
//            if (scopedstr3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            auto pFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return case_insensitive_ansi_compare(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (::is_null(pFind))
//            {
//
//               return false;
//
//            }
//
//            pdir = pdir->element_at(iFind);
//
//            find.m_psz = psz3 + 1;
//
//         }
//
//         goto end;
//
//lookup_backslash:
//         while (scopedstr3 != nullptr && psz3 < pszEnd)
//         {
//
//            psz3 = strchr(find.m_psz, '\\');
//
//            if (scopedstr3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            auto pFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return case_insensitive_ansi_compare(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (::is_null(pFind))
//            {
//
//               return false;
//
//            }
//
//            pdir = pdir->element_at(iFind);
//
//            find.m_psz = psz3 + 1;
//
//         }
//
//end:
//         if (::get_fast_tick_count() > pdir->m_timeLastCheck + m_timeTimeout)
//         {
//
//            return false;
//
//         }
//
//         if (pdir->m_iIsDir < 0)
//         {
//
//            return false;
//
//         }
//
//         bIsDir = pdir->m_iIsDir == 1;
//
//         dwLastError = pdir->m_dwError;
//
//         return true;
//
//      }
//
//
//      void directory_context::is_dir_map::set(const ::file::path & path,bool bIsDir,unsigned int dwLastError)
//      {
//
//         critical_section_lock synchronouslock(m_criticalsection);
//
//         string strPath(path);
//
//         is_dir * pdir = this;
//
//         ::pointer<is_dir>pfind(__allocate is_dir());
//
//         index iFind0 = 0;
//         index iFind3 = 0;
//         while (iFind3 >= 0)
//         {
//
//            index iFind1 = strPath.find('/', iFind0);
//            index iFind2 = strPath.find('\\', iFind0);
//            iFind3 = minimum_non_negative(iFind1, iFind2);
//            if (iFind3 < 0)
//            {
//               pfind->m_str = strPath.substr(iFind0);
//            }
//            else
//            {
//               pfind->m_str = strPath.substr(iFind0, iFind3 - iFind0);
//            }
//
//            auto pFind = pdir->predicate_binary_search(pfind, [&](auto & t1, auto & t2)
//            {
//
//               return t1->m_str.case_insensitive_order(t2->m_str) < 0;
//
//            });
//
//            if (::is_null(pFind))
//            {
//               while (true)
//               {
//
//
//                  index iFind1 = strPath.find('/', iFind0);
//                  index iFind2 = strPath.find('\\', iFind0);
//                  iFind3 = minimum_non_negative(iFind1, iFind2);
//                  if (iFind3 < 0)
//                  {
//                     pfind->m_str = strPath.substr(iFind0);
//                  }
//                  else
//                  {
//                     pfind->m_str = strPath.substr(iFind0, iFind3 - iFind0);
//                  }
//                  pfind->m_iIsDir = bIsDir ? 1 : (iFind3 >= 0 ? -1 : 0);
//
//                  pfind->m_dwError = dwLastError;
//
//                  pfind->m_timeLastCheck = ::get_fast_tick_count();
//
//                  pdir->add(pfind);
//
//                  pdir->predicate_sort([&](auto & t1, auto & t2)
//                  {
//
//                     return t1->m_str.case_insensitive_order(t2->m_str) < 0;
//
//                  });
//
//                  if (iFind3 < 0)
//                  {
//
//                     return;
//
//                  }
//
//                  pdir = pfind;
//
//                  pfind = __allocate is_dir();
//                  iFind0 = iFind3 + 1;
//               }
//            }
//
//            pdir = pdir->element_at(iFind);
//
//            if (bIsDir)
//            {
//
//               pdir->m_iIsDir = 1;
//
//            }
//
//            pdir->m_timeLastCheck = ::get_fast_tick_count();
//            iFind0 = iFind3 + 1;
//         }
//
//
//         pdir->m_iIsDir = bIsDir ? 1 : 0;
//
//         pfind->m_dwError = dwLastError;
//
//      }
//


::file::path directory_context::time()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::stage()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::stageapp()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::netseed()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::install()
{

   synchronous_lock synchronouslock(this->synchronization());

   auto psystem = system();

   return psystem->m_pdirectorysystem->m_pathInstall;

}


::file::path directory_context::config()
{

   synchronous_lock synchronouslock(this->synchronization());

   auto psystem = system();

   return psystem->m_pdirectorysystem->m_pathCa2Config;

}


::file::path directory_context::home()
{

   synchronous_lock synchronouslock(this->synchronization());

   auto psystem = system();

   return psystem->m_pdirectorysystem->m_pathHome;

}


//::file::path directory_context::userfolder(::particle * pparticle)
//{

//   __UNREFERENCED_PARAMETER(pparticle);

//   synchronous_lock synchronouslock(this->synchronization());

//   return m_pathUser;

//}


::file::path directory_context::module()
{

   //synchronous_lock synchronouslock(this->synchronization());

   auto papplication = application();

   return papplication->get_module_folder();

}


//::file::path directory_context::ca2module()
//{
//
//   synchronous_lock synchronouslock(this->synchronization());
//
//   auto psystem = system();
//
//   return psystem->m_pdirectorysystem->m_pathCa2Module;
//
//}


::file::path directory_context::time_square()
{

   return time() / "time";

}


::file::path directory_context::time_log(const ::scoped_string & scopedstrId)
{

   __UNREFERENCED_PARAMETER(scopedstrId);

   throw ::interface_only("this is an interface");

   return "";

}


void directory_context::create(const ::file::path& path)
{

   directory_system()->create(path);

}


void directory_context::erase(const ::file::path& path, bool bRecursive)
{

   if (bRecursive)
   {

      ::file::listing listing;

      listing.set_listing(path);

      enumerate(listing);

      for (auto& path : listing)
      {

         if (is(path))
         {

            erase(path, true);

         }
         else
         {

            file_system()->erase(path);

         }

      }

   }

   directory_system()->erase(path);

}


void directory_context::get_matter_locator(string_array& straMatterLocator, bool bIncludeMain)
{

   synchronous_lock synchronouslock(this->synchronization());

   straMatterLocator.erase_all();

   straMatterLocator.append(m_papplication->m_straMatterLocatorPriority);

   if (bIncludeMain)
   {

      straMatterLocator.add(m_papplication->matter_locator("app/main"));

   }

}


::file::path directory_context::locale_schema_matter(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema, const ::file::path& pathRoot, const ::file::path& pathDomain)
{

   string strHint = pathRoot / "_matter" / pathDomain / get_app()->get_locale_schema_dir(strLocale, strSchema);

   return strHint;

}


::file::path directory_context::matter(const ::file::path& path, const ::file::path& pathRoot, const ::file::path& pathDomain)
{

   string strMatter = ::file::path("appmatter://") / pathRoot / "_matter" / pathDomain / "_std/_std" / path;

   return strMatter;

}


bool directory_context::matter_enumerate(const ::file::path& path, ::file::listing& listing, ::file::e_flag eflag, enum_depth edepth)
{

   auto psystem = system();

   synchronous_lock synchronouslock(psystem->m_pmutexMatter);

   string strDir = matter(path);

   if (psystem->m_pdirectorysystem->m_bMatterFromHttpCache)
   {

      string strMatter = strDir;

      if (strMatter.case_insensitive_begins_eat("appmatter://"))
      {

         strMatter = "/matter/" + strMatter;

      }
      else
      {

         character_count iFind1 = strMatter.case_insensitive_find_index("/matter/");

         character_count iFind2 = strMatter.case_insensitive_find_index("\\matter\\");

         auto iFind = minimum_non_negative(iFind1, iFind2);

         if (iFind > 0)
         {

            strMatter = strMatter(iFind);

         }

      }

      ::property_set set;

      set["raw_http"] = true;

      ::file::path strFile = directory()->cache() / strMatter / "list_dir.list_dir";

      auto iFind = strFile.find_index(DIR_SEPARATOR);

      if (iFind > 0)
      {

         strFile.replace_with("_", ":", iFind + 1);

      }

      strFile.replace_with("//", "////");

      strFile.replace_with("\\", "\\\\", 1);

      ::file::path strLs;

      if (file()->exists(strFile))
      {

         strLs = file()->as_string(strFile);

      }
      else
      {

         // todo: keep cache timeout information;

         auto psystem = system();

         auto purl = psystem->url();

         string strUrl = "https://api.ca2.network/api/matter/list_dir?dir=" + ::url::encode(strMatter);

         strLs = http()->get(strUrl, set);

         file()->put_text(strFile, strLs);

      }

      string_array straLocaleSchema;

      string_array straSep;

      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");

      fix_file_listing_flag(listing.m_eflag);

      straLocaleSchema.add_smallest_tokens(strLs, straSep, false);

      for (::collection::index i = 0; i < straLocaleSchema.get_count(); i++)
      {

         ::file::path path = strDir / straLocaleSchema[i];

         path.m_iDir = straLocaleSchema[i].ends("/") ? 1 : 0;

         listing.defer_add(path);

      }

   }
   else if (psystem->m_pdirectorysystem->m_bMatterFromResource)
   {

      auto pfolder = file()->resource_folder();

      string strPrefix(strDir);

      strPrefix.case_insensitive_begins_eat("zipresource:");

      strPrefix.trim("\\/");

      listing.m_pathFinal = strPrefix;

      listing.m_pathUser = strPrefix;

      pfolder->enumerate(listing);

      ::file::path pathBasePath;

      pathBasePath = "zipresource://";

      pathBasePath /= strPrefix;

      listing.patch_base_path(pathBasePath);

   }
   else
   {

      strDir = m_papplication->get_matter_cache_path(strDir);

      listing.set_listing(strDir);

      directory()->enumerate(listing);

   }

   return true;

}


//bool directory_context::matter_ls_file(const ::file::path & str, ::file::listing & stra)
//{
//
//   ::file::path strDir = matter(str, true);
//
//   auto psystem = system();
//
//   if (psystem->m_pdirectorysystem->m_bMatterFromHttpCache)
//   {
//
//      ::property_set set;
//
//      set["raw_http"] = true;
//
//      string strFile = directory()->cache() / strDir / "list_dir.list_dir";
//
//      auto pFind = strFile.find(DIR_SEPARATOR);
//
//      if (iFind > 0)
//      {
//
//         strFile.replace_with("_", ":", iFind + 1);
//
//      }
//
//      strFile.replace_with("//", "////");
//      strFile.replace_with("\\", "\\\\", 1);
//
//      string strLs;
//
//      if (file()->exists(strFile))
//      {
//
//         strLs = file()->as_string(strFile);
//
//      }
//
//
//      ::file::path_array straLocaleSchema;
//
//      string_array straSep;
//
//      straSep.add("\r");
//      straSep.add("\n");
//      straSep.add("\r\n");
//
//      straLocaleSchema.add_smallest_tokens(strLs, straSep, false);
//
//      for (::collection::index i = 0; i < straLocaleSchema.get_count(); i++)
//      {
//
//         if (!string_ends(straLocaleSchema[i], "/"))
//         {
//            ::file::path strPath = strDir / straLocaleSchema[i];
//            stra.add(strPath);
//         }
//
//      }
//
//   }
//   else
//   {
//
//      directory()->ls(stra, strDir);
//
//   }
//
//   return true;
//
//}


::file::path directory_context::matter_from_locator(const ::file::path_array& patha, const string_array& straMatterLocator)
{

   bool bOk = true;

   if (patha.is_empty())
   {

      return "";

   }

   if (straMatterLocator.is_empty())
   {

      return "";

   }

   ::file::path pathCache;

   ::file::path path;

   if (patha[0].contains("yesno.xhtml"))
   {

      informationf("matter_from_locator yesno.xhtml");

   }

   auto psystem = system();

   if (psystem->m_pdirectorysystem->m_bMatterFromHttpCache)
   {

      if (psystem->m_pdirectorysystem->m_pathLocalAppMatterCacheFolder.has_character())
      {

         ::file::path pathLs0 = straMatterLocator.first();

         pathLs0 /= m_papplication->get_locale_schema_dir();

         pathCache = psystem->m_pdirectorysystem->m_pathLocalAppMatterCacheFolder / pathLs0 / patha[0] + ".map_question";

         information() << "cache map path: " << pathCache;

         path = file()->as_string(pathCache);

         if (path.case_insensitive_begins_eat("itdoesntexist."))
         {

            class ::time t = millisecond_time(::as_long_long(path));

            auto elapsed = t.elapsed();

            if (elapsed < 5_s)
            {

               if (false)
               {

                  return "itdoesntexist";

               }

            }

            path.empty();

         }

         if (!(patha[0].flags() & ::file::e_flag_bypass_cache) && path.has_character())
         {

            string strFinal(path);

            if (strFinal.case_insensitive_begins("appmatter://"))
            {

               strFinal = psystem->m_pdirectorysystem->m_pathLocalAppMatterFolder / strFinal.substr(12);

            }

            auto etype = path_system()->get_type(strFinal);

            if (etype == ::file::e_type_file || etype == ::file::e_type_folder)
            {

               information() << "!!Cache Hit: " << strFinal;

               return path;

            }

            information() << "...Cache Miss: " << strFinal;

         }

      }

   }

   string strLocale;

   string strSchema;

   string_array straLocaleSchema;

   m_papplication->locale_schema_matter(straLocaleSchema, straMatterLocator, strLocale, strSchema);

   //::text::context * ptextcontext = nullptr;

   //if (application()->m_bSession)
   //{

   //   ptextcontext = session()->text_context();

   //}

   if (psystem->m_pdirectorysystem->m_bMatterFromHttpCache)
   {

      string_array stra;

      string strMatter;

      for (auto& strLs : straLocaleSchema)
      {

         for (auto& pathItem : patha)
         {

            strMatter = strLs / pathItem;

            path = directory_system()->ca2roaming() / "_matter" / strMatter;

            //                  if (::path_system()->is_file_or_dir(path, nullptr))
            //                  {
            //
            //                     goto ret;
            //
            //                  }

            stra.add(strMatter);

         }

      }

      ::property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      if (patha[0].flags() & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (patha[0].flags() & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      //      informationf("");
      information() << "Topic: " << patha[0];
      //      informationf("");

      string strCandidate = stra.implode("|");

      auto psystem = system();

      auto purl = psystem->url();

      string strParam = ::url::encode(strCandidate);

      string strUrl;

      //if (bDir)
      //{

      strUrl = "https://ca2.network/api/matter/query?candidate=" + strParam;

      //}
      //else
      //{

        // strUrl = "https://ca2.network/api/matter/query_file?candidate=" + strParam;

      //}

      const ::scoped_string & scopedstrUrl = strUrl;

      strMatter = http()->get(strUrl, set);

      bool bDir = strMatter.ends("/");

      //strMatter.replace("https://ca2.network/", string(get_server_ca2_cc()));
      strMatter.replace_with("https://ca2.network/", "https://ca2.network/");


      //informationf("");
      //informationf("");
      information() << "matter = " << strMatter;
      //informationf("");
      //informationf("");

      strMatter.trim();

      string strToken = "/matter/";

      auto iFind = strMatter.case_insensitive_find_index(strToken);

      if (strMatter.has_character() && ::found(iFind))
      {

         iFind += strToken.length();

         path = "appmatter://" + strMatter(iFind);

         path.m_iDir = bDir ? 1 : 0;

         if (bDir)
         {

            directory_system()->create(psystem->m_pdirectorysystem->m_pathLocalAppMatterFolder / strMatter);

         }

         goto ret;

      }

   }
   else if (psystem->m_pdirectorysystem->m_bMatterFromResource)
   {

      string strMatter;

      for (auto& strLs : straLocaleSchema)
      {

         for (auto& pathItem : patha)
         {

            strMatter = strLs / pathItem;

            strMatter.replace_with("/", "\\");

            auto etype = file()->resource_get_type(strMatter);

            if (::is_file_or_folder(etype))
            {

               path = "zipresource://" + strMatter;

               path.m_iDir = etype == ::file::e_type_folder ? 1 : 0;

               goto ret;

            }

         }

      }
      
   }
   else
   {

      string strMatter;

      for (auto& strLs : straLocaleSchema)
      {

         for (auto& pathItem : patha)
         {

            strMatter = strLs / pathItem;

            path = psystem->m_pdirectorysystem->m_pathLocalAppMatterFolder / strMatter;

            auto etype = path_system()->get_type(path);

            if (::is_file_or_folder(etype))
            {

               path.m_iDir = etype == ::file::e_type_folder ? 1 : 0;

               goto ret;

            }

         }

      }

   }

   bOk = false;

   path = "itdoesntexist." + ::as_string(::long_long_millisecond());

ret:

   if (pathCache.has_character() && psystem->m_pdirectorysystem->m_bMatterFromHttpCache)
   {

      string strPath;

      strPath = path;

      if (path.m_iDir > 0)
      {

         strPath += "/";

      }

      file()->put_text(pathCache, strPath);

      //::file::path pathCache2 = psystem->m_pdirectorysystem->m_pathLocalAppMatterFolder / path;

      //if ((path & ::file::e_flag_get_local_path)
      //   || (!(path & ::file::e_flag_bypass_cache) && path_system()->is_file_or_dir(pathCache, nullptr)))
      //{

      //   return pathCache;

      //}

      string strMatter(path);

      strMatter.case_insensitive_begins_eat("appmatter://");

      ::file::path pathCache = directory_system()->m_pathLocalAppMatterFolder / strMatter;

      ::file::path pathMeta = pathCache + ".meta_information";

      file()->erase(pathMeta);

      path.flags() = patha[0].flags();

   }

   if (!bOk)
   {

      return {};

      //throw exception(error_not_found);

   }

   return path;

}


::file::path directory_context::matter_from_locator(::file::path path, const string_array& straMatterLocator)
{

   ::file::path_array patha;

   path.case_insensitive_begins_eat("matter://");

   path.case_insensitive_begins_eat("appmatter://");

   patha.add(path);

   return matter_from_locator(patha, straMatterLocator);

}


::file::path directory_context::matter(const ::file::path_array& patha)
{

   string_array straMatterLocator;
   {

      synchronous_lock synchronouslock(this->synchronization());

      straMatterLocator = get_app()->m_straMatterLocator;

   }

   return matter_from_locator(patha, straMatterLocator);

}


::file::path directory_context::matter(::file::path path)
{

   string_array straMatterLocator;

   get_matter_locator(straMatterLocator, true);

   return matter_from_locator(path, straMatterLocator);

}


::file::path directory_context::appmatter(::file::path path)
{

   string_array straMatterLocator;

   get_matter_locator(straMatterLocator, false);

   return matter_from_locator(path, straMatterLocator);

}


::file::path directory_context::appmatter(const ::scoped_string & scopedstrApp, ::file::path pathRel)
{

   auto iFind = strApp.find_index('/');

   string strRepo;

   if (iFind > 0)
   {

      strRepo = strApp(0, iFind);

      strApp = strApp(iFind + 1);

   }
   else
   {

      strApp.replace_with("_", "-");

      strApp.replace_with("_", "\\");

      if (strApp.case_insensitive_begins_eat("app_veriwell_"))
      {

         strRepo = "app-veriwell";

      }
      else if (strApp.case_insensitive_begins_eat("app_core_"))
      {

         strRepo = "app-core";

      }
      else if (strApp.case_insensitive_begins_eat("app_cidadedecuritiba_"))
      {

         strRepo = "app-cidadedecuritiba";

      }
      else if (strApp.case_insensitive_begins_eat("app_"))
      {

         strRepo = "app";

      }
      else
      {

         return "";

      }

   }

   auto psystem = system();

   ::file::path path = psystem->local_get_matter_cache_path(
      ::file::path(strRepo) / "_matter" / strApp / "_std" / "_std" / pathRel);

   return path;

}


::file::path directory_context::commonappdata(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrBuild, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration)
{

   synchronous_lock synchronouslock(this->synchronization());

   string strAppId(scopedstrAppId);

   string strPlatform(scopedstrPlatform);

   auto psystem = system();

   if (strPlatform.is_empty())
   {

      strPlatform = psystem->get_system_platform();

   }

   string strConfiguration(scopedstrConfiguration);

   if (strConfiguration.is_empty())
   {

      strConfiguration = psystem->get_system_configuration();

   }

   string strBuild(scopedstrBuild);

   return commonappdata() / strBuild / strPlatform / strConfiguration / strAppId;

}


::file::path directory_context::commonappdata_locale_schema(
   const ::scoped_string & scopedstrAppId,
   const ::scoped_string & scopedstrBuild, 
   const ::scoped_string & scopedstrPlatform, 
   const ::scoped_string & scopedstrConfiguration,
   const ::scoped_string & scopedstrLocale, 
   const ::scoped_string & scopedstrSchema)
{

   synchronous_lock synchronouslock(this->synchronization());

   string strLocale(scopedstrLocale);

   if (strLocale.is_empty())
   {

      strLocale = session()->m_strLocale;

   }

   string strSchema(scopedstrSchema);

   if (strSchema.is_empty())
   {

      strSchema = session()->m_strSchema;

   }

   return commonappdata(scopedstrAppId, scopedstrBuild, scopedstrPlatform, scopedstrConfiguration) / strLocale / strSchema;

}


::file::path directory_context::trash_that_is_not_trash(const ::file::path & path)
{

   __UNREFERENCED_PARAMETER(scopedstr);

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::appdata(const ::scoped_string & scopedstrAppIdParameter)
{

   ::string strAppId(strAppIdParameter);

   if (strAppId.is_empty())
   {

      strAppId = application()->m_strAppId;

   }

   return directory_system()->roaming() / strAppId;

}


::file::path directory_context::cache()
{

   return directory_system()->ca2roaming() / "cache";

}


::file::path directory_context::commonappdata_root()
{

   return "/::payload/lib";

}


::file::path directory_context::commonappdata()
{

   return element_commonappdata(install());

}

::file::path directory_context::element_commonappdata(const ::scoped_string & scopedstrElement)
{

   string strRelative;

   strRelative = strElement;

   auto pFind = strRelative.find(':');

   if (::is_set(pFind))
   {

      auto pFind1 = strRelative(pFind).rear_find("\\");

      auto pFind2 = strRelative(pFind).rear_find("/");

      auto pStart = maximum(pFind1 + 1, pFind2 + 1);

      strRelative = strRelative.left(pFind - 1) + "_" + strRelative.substr(pStart, pFind - pStart) + strRelative(pFind + 1);

   }

   return commonappdata_root() / strRelative;

}


::file::path directory_context::localfolder()
{

   return m_pathLocalFolder;

}


//::file::path directory_context::usersystemappdata(const string & pcszPrefix)

//{
//   __UNREFERENCED_PARAMETER(pparticle);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   throw ::interface_only("this is an interface");
//}


//::file::path directory_context::userappdata(::particle * pparticle)
//{

//   __UNREFERENCED_PARAMETER(pparticle);

//   throw ::interface_only("this is an interface");

//}


//::file::path directory_context::userdata(::particle * pparticle)
//{

//   __UNREFERENCED_PARAMETER(pparticle);

//   throw ::interface_only("this is an interface");

//}


//::file::path directory_context::default_os_user_path_prefix(::particle * pparticle)
//{

//   __UNREFERENCED_PARAMETER(pparticle);

//   throw ::interface_only("this is an interface");

//}


//::file::path directory_context::default_userappdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pparticle);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}

//::file::path directory_context::default_userdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pparticle);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}

//::file::path directory_context::default_userfolder(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pparticle);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}


::file::path directory_context::userquicklaunch()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::userprograms()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path directory_context::commonprograms()
{

   throw ::interface_only("this is an interface");

   return "";

}


bool directory_context::is_inside_time(const ::file::path & path)
{

   __UNREFERENCED_PARAMETER(scopedstrPath);

   throw ::interface_only("this is an interface");

   return false;

}


bool directory_context::is_inside(const ::file::path & pathFolder, const ::file::path & path)
{

   __UNREFERENCED_PARAMETER(scopedstrDir);
   __UNREFERENCED_PARAMETER(scopedstrPath);

   throw ::interface_only("this is an interface");

   return false;

}


::file::watcher& directory_context::watcher()
{

   auto psystem = system();

   return *psystem->m_pdirectorysystem->m_pfilewatcher;

}


//::file::path directory_context::pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode)
//{
//
//   ::file::path_array stra;
//
//   stra.add_tokens(scopedstrEnv, ":", false);
//
//   string strCandidate;
//
//   for (int i = 0; i < stra.get_count(); i++)
//   {
//
//      strCandidate = stra[i] / pszTopic;
//
//      if (file()->exists(strCandidate))
//      {
//         return strCandidate;
//      }
//
//   }
//
//   return "";
//
//}

//      ::file::path directory_context::get_api_cc()
//      {
//
//         if(m_strApiCc.has_character())
//            return m_strApiCc;
//
//         synchronous_lock synchronouslock(m_pmutex);
//
//
//
//         return m_strApiCc;
//
//      }




::file::path directory_context::bookmark()
{

   return directory_system()->bookmark();

}


//::file::path directory_context::home()
//{

//   return directory_system()->home();

//}

::file::path directory_context::desktop()
{

   return home() / "Desktop";

}


::file::path directory_context::document()
{

   return home() / "Document";

}


::file::path directory_context::document2()
{

#ifdef UNIVERSAL_WINDOWS

   return image();

#else

   return document();

#endif

}


::file::path directory_context::download()
{

   return home() / "Downloads";

}


::file::path directory_context::music()
{

   return home() / "Music";

}


::file::path directory_context::video()
{

   return home() / "Video";

}


::file::path directory_context::image::image()
{

   return home() / "Image";

}


::file::path directory_context::dropbox()
{

   if (m_bDropboxCalculated)
   {


      return m_pathDropbox;

   }

   ::file::path pathNetworkPayload = file()->dropbox_info_network_payload();

   if (!file()->exists(pathNetworkPayload))
   {

      auto pathHome = directory()->home();

      auto pathTxt = pathHome / "dropbox.txt";

      string strPath = file()->safe_get_string(pathTxt);

      strPath.trim();

      m_pathDropbox = strPath;

      m_bDropboxCalculated = true;

      return strPath;

   }

   string strNetworkPayload = file()->as_string(pathNetworkPayload);

   ::property_set set;

   set.parse_network_payload(strNetworkPayload);

   m_pathDropbox = set["personal"]["path"];

   m_bDropboxCalculated = true;

   return m_pathDropbox;

}


::file::path directory_context::onedrive()
{

   ::file::path pathIni = file()->onedrive_cid_ini();

   string strIni = file()->safe_get_string(pathIni);

   if (strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strLibrary;

   strLibrary = set["library"];

   ::tokenizer token(strLibrary);

   token.skip_word(7);

   string strWork = token.get_word();

   strWork.trim("\"");

   return strWork;

}


::file::path directory_context::dropbox_app()
{

   if (!system())
   {

      throw ::exception(error_wrong_state, "system() is null");

   }

   auto papplication = application();

   if (papplication)
   {

      if (papplication->m_strAppId.is_empty())
      {

         throw ::exception(error_wrong_state, "Application Startup App Id is empty");

      }

      return dropbox() / "application" / papplication->m_strAppId;

   }

   throw ::exception(error_wrong_state, "No application is set");

   return {};

}


::file::path directory_context::standalone()
{

   return directory_system()->roaming() / application()->m_strStandalone;

}


//string_array directory_context::locale_schema_matter(string & strLocale, const ::scoped_string & scopedstrStyle)
//{

//   return psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle);

//}


//string_array directory_context::locale_schema_matter(string & strLocale, const ::scoped_string & scopedstrStyle, const string & pathRoot, const ::file::path & pathDomain)
//{

//   return psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle, pathRoot, pathDomain);

//}

//
//string directory_context::matter(const ::file::path_array & patha, bool bDir)
//{
//
//   return psystem->m_spdir->matter(get_app(), patha, bDir);
//
//}


//string directory_context::matter(const ::file::path & path, bool bDir)
//{
//
//   return psystem->m_spdir->matter(get_app(), path, bDir);
//
//}
////
//
//void directory_context::matter_ls(const ::file::path & str, ::file::path_array & stra)
//{
//   psystem->m_spdir->matter_ls(get_app(), str, stra);
//}
//
//void directory_context::matter_ls_file(const ::file::path & str, ::file::path_array & stra)
//{
//   psystem->m_spdir->matter_ls_file(get_app(), str, stra);
//}


//::file::path directory_context::matter_file(const ::file::path & path, bool bDir)
//
//{
//
//   string strPath = psystem->m_spdir->matter(get_app(), pcsz, bDir);
//
//
//   return strPath;
//
//}


//::file::path directory_context::userquicklaunch()
//{
//
//   return psystem->m_spdir->userquicklaunch(this);
//
//}

//
//::file::path directory_context::userprograms()
//{
//
//   return psystem->m_spdir->userprograms(this);
//
//}


//::file::listing & directory_context::ls(listing & listing)
//{
//
//   return psystem->m_spdir.m_p->ls(get_app(), listing);
//
//}

//::file::listing & directory_context::ls_relative_name(listing & listing)
//{
//
//   return psystem->m_spdir.m_p->ls_relative_name(get_app(), listing);
//
//}
//

//bool directory_context::has_subdir(const ::file::path & path)
//
//{
//
//   return psystem->m_spdir.m_p->has_subdir(get_app(), pcsz);
//
//
//}
//

//bool directory_context::is(const ::file::path & path)
//
//{
//
//   return psystem->m_spdir.m_p->is(pcsz, get_app());
//
//
//}
//

//bool directory_context::is_inside(const ::file::path & pathFolder, const ::file::path & lpcszPath)
//
//{
//
//   return psystem->m_spdir.m_p->is_inside(pcszDir, lpcszPath, get_app());
//
//
//}
//

//bool directory_context::is_inside_time(const ::file::path & path)
//
//{
//   return psystem->m_spdir.m_p->is_inside_time(pcsz, get_app());
//
//}


//::file::listing & directory_context::root_ones(::file::listing & listing)
//{
//   return psystem->m_spdir.m_p->root_ones(listing, get_app());
//}
//

//bool directory_context::mk(const ::file::path & path)
//{
//
//   if (path.is_empty())
//   {
//
//      return true;
//
//   }
//
//   return psystem->m_spdir.m_p->mk(path, get_app());
//
//}


//bool directory_context::rm(const ::file::path & path, bool bRecursive)
//{
//
//   return psystem->m_spdir.m_p->rm(get_app(), path, bRecursive);
//
//}


::file::path directory_context::pathfind(const ::scoped_string & scopedstrEnv, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrMode)
{

   return directory_system()->pathfind(scopedstrEnv, pszTopic, pszMode);

}


//::file::path directory_context::dropbox()
//{
//
//   return psystem->m_spdir->dropbox(get_app());
//
//}


//::file::path directory_context::onedrive()
//{
//
//   return psystem->m_spdir->onedrive(get_app());
//
//}


//
//
//} // namespace file
//
//


