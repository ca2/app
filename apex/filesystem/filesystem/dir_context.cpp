#include "framework.h"
//#include "apex/platform/app_core.h"
//#include "apex/compress/zip/_.h"
#include "acme/id.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"


///CLASS_DECL_ACME const char* get_server_ca2_cc();


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
//   dir_context * dir_context::g_pthis = nullptr;
//

dir_context::dir_context()
{

   m_bDropboxCalculated = false;

   //if (::file::dir_context::g_pthis == nullptr)
   //{

   //   ::file::dir_context::g_pthis = this;

   //   increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   //}

   //m_pziputil = nullptr;

   //         m_isdirmap.m_durationTimeout = 180000;



}


dir_context::~dir_context()
{

   //::acme::del(m_pziputil);

}


void dir_context::initialize(::object * pobject)
{

   /*auto estatus = */ ::object::initialize(pobject);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


void dir_context::init_system()
{

   //return ::success;

}



void dir_context::init_context()
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
   string & psz = strCat.get_string_buffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
   ansi_count_copy(psz, &((const string &)str1)[beg1], end1 - beg1 + 1); \
   psz[end1 - beg1 + 1] = ch; \
   ansi_count_copy(&psz[end1 - beg1 + 2], &((const string &)str2)[beg2], end2 - beg2 + 1); \
   strPath.ReleaseBuffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
}

//::file::path dir_context::simple_path(const ::string & strFolder, const ::string & strRelative)
//{

//   if(strRelative.is_empty())
//   {
//      if(strFolder.is_empty())
//         return "";
//      return strFolder;
//   }

//   strsize iFolderBeg = 0;

//   strsize iFolderEnd = strFolder.get_length() - 1;

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
//      //::str::ends_eat(strFolder, "\\");
//      //::str::ends_eat(strFolder, "/");
//      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
//         iFolderEnd--;
//   }

//   strsize iRelativeBeg = 0;

//   strsize iRelativeEnd = strRelative.get_length() - 1;

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
//      //::str::ends_eat(strFolder, "\\");
//      //::str::ends_eat(strFolder, "/");
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
//      string & psz = strPath.get_string_buffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
//      ansi_count_copy(psz, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
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

//::file::path dir_context::simple_path(const ::string & strFolder, const ::string & strRelative, const ::string & str2)
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

//   strsize iFolderBeg = 0;

//   strsize iFolderEnd = strFolder.get_length() - 1;

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
//      //::str::ends_eat(strFolder, "\\");
//      //::str::ends_eat(strFolder, "/");
//      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
//         iFolderEnd--;
//   }

//   strsize iRelativeBeg = 0;

//   strsize iRelativeEnd = strRelative.get_length() - 1;

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
//      //::str::ends_eat(strFolder, "\\");
//      //::str::ends_eat(strFolder, "/");
//      while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
//         iRelativeBeg++;
//   }


//   strsize iBeg2 = 0;

//   strsize iEnd2 = str2.get_length() - 1;

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
//      //::str::ends_eat(strFolder, "\\");
//      //::str::ends_eat(strFolder, "/");
//      while(iBeg2 <= iEnd2 && (str2[iBeg2] == '/' || str2[iBeg2] == '\\'))
//         iBeg2++;
//   }

//   if(iRelativeBeg > iRelativeEnd)
//   {
//      if(iBeg2 > iEnd2)
//      {
//         if(iFolderBeg > iFolderEnd)
//            return "";
//         return strFolder.Mid(iFolderBeg, iFolderEnd - iFolderBeg + 1);
//      }
//      else
//      {
//         if(iFolderBeg > iFolderEnd)
//            return str2.Mid(iBeg2, iEnd2 - iBeg2 + 1);
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

//   string & psz = strPath.get_string_buffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
//   ansi_count_copy(psz, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
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


//::file::path dir_context::relpath(const string & pcszSource,const string & lpcszRelative)

//{
//   __UNREFERENCED_PARAMETER(pcszSource);

//   __UNREFERENCED_PARAMETER(pcszRelative);

//   throw ::interface_only("this is an interface");
//}


//::file::path dir_context::relpath(const string & pcszSource, const string & lpcszRelative, const string & psz2)

//{
//   __UNREFERENCED_PARAMETER(pcszSource);

//   __UNREFERENCED_PARAMETER(pcszRelative);

//   __UNREFERENCED_PARAMETER(psz2);
//   throw ::interface_only("this is an interface");
//}


::file::listing & dir_context::root_ones(::file::listing & listing)
{

   throw ::interface_only("this is an interface");

   return listing;

}


bool dir_context::ls(::file::listing & listing)
{

   listing.m_pathFinal = m_pcontext->m_papexcontext->defer_process_path(listing.m_pathUser);

   if (listing.m_pathFinal.begins_ci("matter://"))
   {

      ::str::begins_eat_ci(listing.m_pathFinal, "matter://");

      if (matter_ls(listing.m_pathFinal, listing))
      {

         return true;

      }

   }

   if (listing.m_bRecursive)
   {

      return false;

   }

   if (::str::begins_ci(listing.m_pathFinal, "http://") || ::str::begins_ci(listing.m_pathFinal, "https://"))
   {

      property_set set;

      string str =m_pcontext->m_papexcontext->http().get(listing.m_pathFinal, set);

      listing.add_tokens(str, "\n", false);

      return true;

   }
   else if (task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends_ci(listing.m_pathFinal, ".zip") || ::str::find_file_extension("zip:", listing.m_pathFinal) >= 0))
   {

      auto & pfactory = m_psystem->folder_factory();

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

               pfolder->perform_file_listing(listing);

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


bool dir_context::ls_relative_name(::file::listing & listing)
{

   if (listing.m_bRecursive)
   {

      return false;

   }

   if (::str::begins_ci(listing.m_pathUser, "http://") || ::str::begins_ci(listing.m_pathUser, "https://"))
   {

      property_set set;

      string str = m_pcontext->m_papexcontext->http().get(listing.m_pathUser, set);

      listing.add_tokens(str, "\n", false);

      return true;

   }
   else if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends_ci(listing.m_pathUser, ".zip") || ::str::find_file_extension("zip:", listing.m_pathUser) >= 0))
   {

      auto & pfactory = m_psystem->folder_factory();

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

               pfolder->perform_file_relative_name_listing(listing);

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


bool dir_context::rls(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   return ls(listing);

}


bool dir_context::rls_relative_name(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   return ls_relative_name(listing);

}


bool dir_context::ls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = false;

   listing.m_bDir = true;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


bool dir_context::ls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = false;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


bool dir_context::rls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


bool dir_context::rls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = true;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


bool dir_context::ls_file(::file::listing& listing)
{

   listing.m_bRecursive = false;

   listing.m_bDir = false;

   listing.m_bFile = true;

   //listing.m_straPattern.erase_all();

   return ls(listing);

}


bool dir_context::ls_dir(::file::listing& listing)
{

   listing.m_bRecursive = false;

   listing.m_bDir = true;

   listing.m_bFile = false;

   listing.m_straPattern.erase_all();

   return ls(listing);

}


bool dir_context::rls_file(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern.erase_all();

   return ls(listing);

}


bool dir_context::rls_dir(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = false;

   listing.m_straPattern.erase_all();

   return ls(listing);

}


bool dir_context::has_subdir(const ::file::path & pathFolder)
{

   ::file::listing ls;

   m_pcontext->m_papexcontext->dir().ls_dir(ls, pathFolder);

   return ls.get_count() > 0;

}


bool dir_context::is_cached(bool & bIs, const ::file::path & path)
{

   bIs = false;

#ifdef WINDOWS_DESKTOP
#ifdef WINDOWS_DESKTOP
   if (::str::ends_ci(path, ".lnk"))
   {
#endif

      ::file::path pathTarget;

      m_pcontext->m_papexcontext->file().resolve_link(pathTarget, path);
      //{

         bIs = is(pathTarget);

         return true;

      //}

#ifdef WINDOWS_DESKTOP
   }
#endif
#endif

   //bIs = false;

   //if (::str::begins_ci(pcszPath, "http://") || ::str::begins_ci(lpcszPath, "https://"))

   //{

   //   property_set set;

   //   bIs = Sess(papp).http().exists(pcszPath, set);


   //   return true;

   //}

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends_ci(path, ".zip")))
   {

      bIs = true;

      return true;
   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      //            u32 dwLastError;

                  //if (m_isdirmap.lookup(pcszPath, bHasSubFolder, dwLastError))

                  //{

                  //   bIs = bHasSubFolder;

                  //   return true;

                  //}

//      zip_context zip(this);

  //    bHasSubFolder = zip.has_sub_folder(path);


      auto & pfactory = m_psystem->folder_factory();

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
   //         if (::str::ends_ci(pcszPath, ".lnk"))

   //         {
   //#endif
   //
   //            string strTarget;
   //
   //            string strFolder;
   //
   //            string strParams;
   //
   //            if (m_pcontext->m_papexcontext->file().resolve_link(strTarget, strFolder, strParams, pcszPath))

   //            {
   //
   //               bIs = is(strTarget, pobject);
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

   //         u32 dwLastError;

            //if (!m_isdirmap.lookup(pcszPath, bHasSubFolder, dwLastError))

            //{
            //   return false;
            //}
   //         bIs = bHasSubFolder;
   return false;

}


bool dir_context::is(const ::file::path & pathParam)
{

   ::file::path path;

   auto psystem = get_system()->m_papexsystem;

   if (pathParam.begins_ci("appmatter://"))
   {

      path = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / path.Mid(12);

   }
   else
   {

      path = m_pcontext->m_papexcontext->defer_process_path(pathParam);

   }

   bool bIs = false;

   if (!(pathParam & ::file::e_flag_bypass_cache) && is_cached(bIs, path))
   {

      return bIs;

   }

   return is_impl(path);

}


bool dir_context::is_impl(const ::file::path & path)
{

   if (path.ends_ci("://") || path.ends_ci(":/") || path.ends_ci(":"))
   {

      return true;

   }

   if (::str::begins_ci(path, "http://") || ::str::begins_ci(path, "https://"))
   {

      property_set set;

      if (path & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

      return m_pcontext->m_papexcontext->http().exists(path, set);

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends_ci(path, ".zip")))
   {

      //m_isdirmap.set(path, true, 0);

      return true;

   }

   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      auto & pfactory = m_psystem->folder_factory();

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

      return bHasSubFolder;

   }

   return false;

}


bool dir_context::name_is(const ::file::path & strPath)
{

   //output_debug_string(strPath);
   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::ends_ci(strPath, ".zip")))
   {
      //            m_isdirmap.set(strPath, true, 0);
      return true;
   }
   if (::task_flag().is_set(e_task_flag_compress_is_dir) && (::str::find_file_extension("zip:", strPath) >= 0))
   {
      bool bHasSubFolder;

      auto & pfactory = m_psystem->folder_factory();

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
      //            u32 dwLastError;
                  //if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
                  //   return bHasSubFolder;
  //    bHasSubFolder = zip.has_sub_folder(strPath);
      //m_isdirmap.set(strPath, bHasSubFolder, get_last_error());
      return bHasSubFolder;
   }
   return false;


}




//      dir_context::is_dir_map::is_dir_map()
//      {
//
//      }
//
//
//      bool dir_context::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, u32 & dwLastError)
//      {
//
//         return lookup(path, bIsDir, dwLastError, (i32) path.length());
//
//      }
//
//
//      bool dir_context::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, u32 &dwLastError, i32 iLastChar)
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
//      bool dir_context::is_dir_map::lookup_dynamic(const ::file::path & path, bool &bIsDir, u32 & dwLastError, i32 iLastChar)
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
//               find.m_str = path.Mid(iFind0);
//
//            }
//            else
//            {
//
//               find.m_str = path.Mid(iFind0, iFind3 - iFind0);
//
//            }
//
//            index iFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return t1->m_str.compare_ci(t2->m_str) < 0;
//
//            });
//
//            if (iFind < 0)
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
//         if (::get_fast_tick_count() > pdir->m_durationLastCheck + m_durationTimeout)
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
//      bool dir_context::is_dir_map::lookup_small(const ::file::path & path,bool &bIsDir,u32 &dwLastError, i32 iLastChar)
//      {
//
//         const char * pszEnd = path.c_str() + iLastChar;
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
//         while (psz3 != nullptr && psz3 < pszEnd)
//         {
//
//            char * psz1 = strchr(find.m_psz, '/');
//
//            char * psz2 = strchr(find.m_psz, '\\');
//
//            psz3 = min_non_null(psz1, psz2);
//
//            if (psz3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            index iFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return ansi_compare_ci(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (iFind < 0)
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
//            if (psz1 == nullptr)
//            {
//
//               goto lookup_backslash;
//
//            }
//            else if (psz2 == nullptr)
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
//         while (psz3 != nullptr && psz3 < pszEnd)
//         {
//
//            psz3 = strchr(find.m_psz, '/');
//
//            if (psz3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            index iFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return ansi_compare_ci(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (iFind < 0)
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
//         while (psz3 != nullptr && psz3 < pszEnd)
//         {
//
//            psz3 = strchr(find.m_psz, '\\');
//
//            if (psz3 != nullptr)
//            {
//
//               *psz3 = '\0';
//
//            }
//
//            index iFind = pdir->predicate_binary_search(&find, [&](auto & t1, auto & t2)
//            {
//
//               return ansi_compare_ci(t1->c_str(), t2->c_str()) < 0;
//
//            });
//
//            if (iFind < 0)
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
//         if (::get_fast_tick_count() > pdir->m_durationLastCheck + m_durationTimeout)
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
//      void dir_context::is_dir_map::set(const ::file::path & path,bool bIsDir,u32 dwLastError)
//      {
//
//         critical_section_lock synchronouslock(m_criticalsection);
//
//         string strPath(path);
//
//         is_dir * pdir = this;
//
//         __pointer(is_dir) pfind(__new(is_dir));
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
//               pfind->m_str = strPath.Mid(iFind0);
//            }
//            else
//            {
//               pfind->m_str = strPath.Mid(iFind0, iFind3 - iFind0);
//            }
//
//            index iFind = pdir->predicate_binary_search(pfind, [&](auto & t1, auto & t2)
//            {
//
//               return t1->m_str.compare_ci(t2->m_str) < 0;
//
//            });
//
//            if (iFind < 0)
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
//                     pfind->m_str = strPath.Mid(iFind0);
//                  }
//                  else
//                  {
//                     pfind->m_str = strPath.Mid(iFind0, iFind3 - iFind0);
//                  }
//                  pfind->m_iIsDir = bIsDir ? 1 : (iFind3 >= 0 ? -1 : 0);
//
//                  pfind->m_dwError = dwLastError;
//
//                  pfind->m_durationLastCheck = ::get_fast_tick_count();
//
//                  pdir->add(pfind);
//
//                  pdir->predicate_sort([&](auto & t1, auto & t2)
//                  {
//
//                     return t1->m_str.compare_ci(t2->m_str) < 0;
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
//                  pfind = __new(is_dir);
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
//            pdir->m_durationLastCheck = ::get_fast_tick_count();
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


::file::path dir_context::time()
{
   
   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::stage()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::stageapp()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::netseed()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::install()
{

   synchronous_lock synchronouslock(mutex());

   auto psystem = get_system()->m_papexsystem;

   return psystem->m_pdirsystem->m_pathInstall;

}


::file::path dir_context::config()
{

   synchronous_lock synchronouslock(mutex());

   auto psystem = get_system()->m_papexsystem;

   return psystem->m_pdirsystem->m_pathCa2Config;

}


::file::path dir_context::home()
{

   synchronous_lock synchronouslock(mutex());

   auto psystem = get_system()->m_papexsystem;

   return psystem->m_pdirsystem->m_pathHome;

}


//::file::path dir_context::userfolder(::object * pobject)
//{

//   __UNREFERENCED_PARAMETER(pobject);

//   synchronous_lock synchronouslock(mutex());

//   return m_pathUser;

//}


::file::path dir_context::module()
{

   synchronous_lock synchronouslock(mutex());

   auto psystem = get_system()->m_papexsystem;

   return psystem->m_pdirsystem->m_pathModule;

}


//::file::path dir_context::ca2module()
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   auto psystem = get_system()->m_papexsystem;
//
//   return psystem->m_pdirsystem->m_pathCa2Module;
//
//}


::file::path dir_context::time_square()
{

   return time() / "time";

}


::file::path dir_context::time_log(const string & pszId)
{

   __UNREFERENCED_PARAMETER(pszId);
   
   throw ::interface_only("this is an interface");

   return "";

}


void dir_context::create(const ::file::path & path)
{

   m_psystem->m_pacmedir->create(path);

}


void dir_context::erase(const ::file::path& path, bool bRecursive)
{

   if (bRecursive)
   {

      ::file::listing patha;

      ls(patha, path);

      for (auto& pathItem : patha)
      {

         if (is(pathItem))
         {

            erase(pathItem, true);

         }
         else
         {

            m_psystem->m_pacmefile->erase(pathItem);

         }

      }

   }

   m_psystem->m_pacmedir->erase(path);

}



::file::path dir_context::locale_schema_matter(const ::string & strLocale, const ::string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain)
{

   string strHint = pathRoot / "_matter" / pathDomain / get_app()->m_papplication->get_locale_schema_dir(strLocale, strSchema);

   return strHint;

}


::file::path dir_context::matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain)
{

   string strMatter = ::file::path("appmatter://") / pathRoot / "_matter" / pathDomain / "_std/_std" / path;

   return strMatter;

}


bool dir_context::matter_ls(const ::file::path & path, ::file::listing & stra)
{

   auto psystem = get_system()->m_papexsystem;

   synchronous_lock synchronouslock(psystem->m_pmutexMatter);

   string strDir = matter(path, true);

   if (psystem->m_pdirsystem->m_bMatterFromHttpCache)
   {

      string strMatter = strDir;

      if (::str::begins_eat_ci(strMatter, "appmatter://"))
      {

         strMatter = "/matter/" + strMatter;

      }
      else
      {

         strsize iFind1 = strMatter.find_ci("/matter/");

         strsize iFind2 = strMatter.find_ci("\\matter\\");

         strsize iFind = minimum_non_negative(iFind1, iFind2);

         if (iFind > 0)
         {

            strMatter = strMatter.Mid(iFind);

         }

      }

      property_set set;

      set["raw_http"] = true;

      ::file::path strFile = m_pcontext->m_papexcontext->dir().cache() / strMatter / "list_dir.list_dir";

      strsize iFind = strFile.find(DIR_SEPARATOR);

      if (iFind > 0)
      {

         strFile.replace_with("_", ":", iFind + 1);

      }

      strFile.replace_with("//", "////");

      strFile.replace_with("\\", "\\\\", 1);

      ::file::path strLs;

      if (m_pcontext->m_papexcontext->file().exists(strFile))
      {

         strLs = m_pcontext->m_papexcontext->file().as_string(strFile);

      }
      else
      {

         // todo: keep cache timeout information;

         auto psystem = m_psystem;

         auto purl = psystem->url();

         string strUrl = "https://api.ca2.software/api/matter/list_dir?dir=" + purl->url_encode(strMatter);

         strLs = m_pcontext->m_papexcontext->http().get(strUrl, set);

         m_pcontext->m_papexcontext->file().put_text(strFile, strLs);

      }

      string_array straLs;

      string_array straSep;

      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");

      straLs.add_smallest_tokens(strLs, straSep, false);

      for (index i = 0; i < straLs.get_count(); i++)
      {

         ::file::path strPath = strDir / straLs[i];

         if (::str::ends(straLs[i], "/"))
         {

            strPath.m_iDir = 1;

         }

         stra.add(strPath);

      }

   }
   else if (psystem->m_pdirsystem->m_bMatterFromResource)
   {

      auto pfolder = m_pcontext->m_papexcontext->file().resource_folder();

   string strPrefix(strDir);
   strPrefix.begins_eat_ci("zipresource:");
   strPrefix.trim("\\/");

   stra.m_pathFinal = strPrefix;
   stra.m_pathUser = strPrefix;

   pfolder->perform_file_listing(stra);

   for (auto& path : stra)
   {
      path = "zipresource://" + path;
   }
   }
   else
   {

      strDir = m_pcontext->m_papexcontext->get_matter_cache_path(strDir);

      m_pcontext->m_papexcontext->dir().ls(stra, strDir);

   }

   return true;

}


bool dir_context::matter_ls_file(const ::file::path & str, ::file::listing & stra)
{

   ::file::path strDir = matter(str, true);

   auto psystem = get_system()->m_papexsystem;

   if (psystem->m_pdirsystem->m_bMatterFromHttpCache)
   {

      property_set set;

      set["raw_http"] = true;

      string strFile = m_pcontext->m_papexcontext->dir().cache() / strDir / "list_dir.list_dir";

      strsize iFind = strFile.find(DIR_SEPARATOR);

      if (iFind > 0)
      {

         strFile.replace_with("_", ":", iFind + 1);

      }

      strFile.replace_with("//", "////");
      strFile.replace_with("\\", "\\\\", 1);

      string strLs;

      if (m_pcontext->m_papexcontext->file().exists(strFile))
      {

         strLs = m_pcontext->m_papexcontext->file().as_string(strFile);

      }


      ::file::path_array straLs;

      string_array straSep;

      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");

      straLs.add_smallest_tokens(strLs, straSep, false);

      for (index i = 0; i < straLs.get_count(); i++)
      {

         if (!::str::ends(straLs[i], "/"))
         {
            ::file::path strPath = strDir / straLs[i];
            stra.add(strPath);
         }

      }

   }
   else
   {

      m_pcontext->m_papexcontext->dir().ls(stra, strDir);

   }

   return true;

}


::file::path dir_context::matter_from_locator(const ::file::path_array & patha, const string_array & straMatterLocator, bool bDir)
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

   if(patha[0].contains("yesno.xhtml"))
   {

      output_debug_string("test");

   }

   auto psystem = get_system()->m_papexsystem;

   if (psystem->m_pdirsystem->m_bMatterFromHttpCache)
   {

      if (psystem->m_pdirsystem->m_pathLocalAppMatterCacheFolder.has_char())
      {

         ::file::path pathLs0 = straMatterLocator.first();

         pathLs0 /= m_pcontext->m_papexcontext->get_locale_schema_dir();

         pathCache = psystem->m_pdirsystem->m_pathLocalAppMatterCacheFolder / pathLs0 / patha[0] + ".map_question";

         INFORMATION("cache map path: " << pathCache);

         path = m_pcontext->m_papexcontext->file().as_string(pathCache);

         if (::str::begins_eat_ci(path, "itdoesntexist."))
         {

            ::duration t = INTEGRAL_MILLISECOND(ansi_to_i64(path));

            auto elapsed = t.elapsed();

            if (elapsed < 5_s)
            {

               if (false)
               {

                  return "itdoesntexist";

               }

            }

            path.Empty();

         }

         if (!(patha[0] & ::file::e_flag_bypass_cache) && path.has_char())
         {

            string strFinal(path);

            if (strFinal.begins_ci("appmatter://"))
            {

               strFinal = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / strFinal.Mid(12);

            }

            if (m_psystem->m_pacmepath->is_file_or_dir(strFinal, nullptr))
            {

               INFORMATION("!!Cache Hit: " << strFinal);

               return path;

            }

            INFORMATION("...Cache Miss: " << strFinal);

         }

      }

   }

   string strLocale;

   string strSchema;

   string_array straLs;

   m_pcontext->m_papexcontext->locale_schema_matter(straLs, straMatterLocator, strLocale, strSchema);

   auto psession = get_session();

   ::text::context * ptextcontext = psession->text_context();

   if (psystem->m_pdirsystem->m_bMatterFromHttpCache)
   {

      string_array stra;

      string strMatter;

      for (auto & strLs : straLs)
      {

         for (auto & pathItem : patha)
         {

            strMatter = strLs / pathItem;

            path = m_psystem->m_pacmedir->ca2roaming() / "_matter" / strMatter;

            //                  if (::m_psystem->m_pacmepath->is_file_or_dir(path, nullptr))
            //                  {
            //
            //                     goto ret;
            //
            //                  }

            stra.add(strMatter);

         }

      }

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      if (patha[0] & ::file::e_flag_required)
      {

         set["required"] = true;

      }

      if (patha[0] & ::file::e_flag_bypass_cache)
      {

         set["nocache"] = true;

      }

//      TRACE("");
      INFORMATION("Topic: " << patha[0]);
//      TRACE("");

      string strCandidate = stra.implode("|");

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strParam = purl->url_encode(strCandidate);

      string strUrl;

      if (bDir)
      {

         strUrl = "https://ca2.software/api/matter/query_dir?candidate=" + strParam;

      }
      else
      {

         strUrl = "https://ca2.software/api/matter/query_file?candidate=" + strParam;

      }

      const char * pszUrl = strUrl;

      strMatter = m_pcontext->m_papexcontext->http().get(strUrl, set);

      //strMatter.replace("https://server.ca2.software/", string(get_server_ca2_cc()));
      strMatter.replace_with("https://ca2.software/", "https://server.ca2.software/");

      //TRACE("");
      //TRACE("");
      INFORMATION("matter = " << strMatter);
      //TRACE("");
      //TRACE("");

      strMatter.trim();

      string strToken = "/matter/";

      auto iFind = strMatter.find_ci(strToken);

      if (strMatter.has_char() && iFind >= 0)
      {

         iFind += strToken.get_length();

         path = "appmatter://" + strMatter.Mid(iFind);

         if (bDir)
         {

            m_psystem->m_pacmedir->create(psystem->m_papexsystem->m_pdirsystem->m_pathLocalAppMatterFolder / strMatter);

         }

         goto ret;

      }

   }
   else if(psystem->m_pdirsystem->m_bMatterFromResource)
   {

   string strMatter;

   for (auto& strLs : straLs)
   {

      for (auto& pathItem : patha)
      {

         strMatter = strLs / pathItem;

         strMatter.replace_with("/", "\\");

         if (m_psystem->m_papexsystem->file().resource_is_file_or_dir(strMatter))
         {

            path = "zipresource://" + strMatter;

            goto ret;

         }

      }

   }

   }
   else
   {



   string strMatter;

   for (auto& strLs : straLs)
   {

      for (auto& pathItem : patha)
      {

         strMatter = strLs / pathItem;

         path = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / strMatter;

         if (m_psystem->m_pacmepath->is_file_or_dir(path, nullptr))
         {

            goto ret;

         }

      }

   }

   }
   
   bOk = false;
   
   path = "itdoesntexist." + __string(get_integral_millisecond().m_i);

ret:

   if (pathCache.has_char() && psystem->m_pdirsystem->m_bMatterFromHttpCache)
   {

      m_pcontext->m_papexcontext->file().put_text(pathCache, path);

      //::file::path pathCache2 = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / path;

      //if ((path & ::file::e_flag_get_local_path)
      //   || (!(path & ::file::e_flag_bypass_cache) && m_psystem->m_pacmepath->is_file_or_dir(pathCache, nullptr)))
      //{

      //   return pathCache;

      //}

      string strMatter(path);

      ::str::begins_eat_ci(strMatter, "appmatter://");

      auto psystem = get_system()->m_papexsystem;

      ::file::path pathCache = psystem->m_pdirsystem->m_pathLocalAppMatterFolder / strMatter;

      ::file::path pathMeta = pathCache + ".meta_information";

      psystem->file().erase(pathMeta);

      ((enumeration < ::file::enum_flag >&)path) = patha[0];

   }
   
   if(!bOk)
   {
      
      return {};
      
      //throw exception(error_not_found);
      
   }

   return path;

}


::file::path dir_context::matter_from_locator(::file::path path, const string_array & straMatterLocator, bool bDir)
{

   ::file::path_array patha;

   ::str::begins_eat_ci((string &) path, "matter://");

   patha.add(path);

   return matter_from_locator(patha, straMatterLocator, bDir);

}


::file::path dir_context::matter(const ::file::path_array & patha, bool bDir)
{

   string_array straMatterLocator;
   {

      synchronous_lock synchronouslock(mutex());

      straMatterLocator = get_app()->m_papplication->m_straMatterLocator;

   }

   return matter_from_locator(patha, straMatterLocator, bDir);

}


::file::path dir_context::matter(::file::path path, bool bDir)
{

   string_array straMatterLocator;

   {

      synchronous_lock synchronouslock(mutex());

      straMatterLocator = m_pcontext->m_papexcontext->m_straMatterLocator;

   }

   return matter_from_locator(path, straMatterLocator, bDir);

}


::file::path dir_context::appmatter(string strApp, ::file::path pathRel)
{

   strsize iFind = strApp.find('/');

   string strRepo;

   if (iFind > 0)
   {

      strRepo = strApp.Left(iFind);

      strApp = strApp.Mid(iFind + 1);

   }
   else
   {

      strApp.replace_with("_", "-");

      strApp.replace_with("_",  "\\");

      if (::str::begins_eat_ci(strApp, "app_veriwell_"))
      {

         strRepo = "app-veriwell";

      }
      else if (::str::begins_eat_ci(strApp, "app_core_"))
      {

         strRepo = "app-core";

      }
      else if (::str::begins_eat_ci(strApp, "app_cidadedecuritiba_"))
      {

         strRepo = "app-cidadedecuritiba";

      }
      else if (::str::begins_eat_ci(strApp, "app_"))
      {

         strRepo = "app";

      }
      else
      {

         return "";

      }

   }

   auto psystem = get_system()->m_papexsystem;

   ::file::path point = psystem->local_get_matter_cache_path(
      ::file::path(strRepo) / "_matter" / strApp / "_std" / "_std" / pathRel);

   return point;

}




::file::path dir_context::commonappdata(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration)
{

   synchronous_lock synchronouslock(mutex());

   string strAppId(pszAppId);

   string strPlatform(pszPlatform);

   auto psystem = get_system()->m_papexsystem;

   if (strPlatform.is_empty())
   {

      strPlatform = psystem->get_system_platform();

   }

   string strConfiguration(pszConfiguration);

   if (strConfiguration.is_empty())
   {

      strConfiguration = psystem->get_system_configuration();

   }

   string strBuild(pszBuild);

   return commonappdata() / strBuild / strPlatform / strConfiguration / strAppId;

}


::file::path dir_context::commonappdata_locale_schema(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
{

   synchronous_lock synchronouslock(mutex());

   string strLocale(pszLocale);

   if (strLocale.is_empty())
   {

      auto psession = get_session();

      strLocale = psession->m_strLocale;

   }

   string strSchema(pszSchema);

   if (strSchema.is_empty())
   {

      auto psession = get_session();

      strSchema = psession->m_strSchema;

   }

   return commonappdata(pszAppId, pszBuild, pszPlatform, pszConfiguration) / strLocale / strSchema;

}


::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
{

   __UNREFERENCED_PARAMETER(psz);

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::appdata(const ::string & strAppId)
{

   if (strAppId.is_empty())
   {

      auto psystem = get_system()->m_papexsystem;

      //throw ::interface_only("this is an interface");

      return psystem->m_pdirsystem->m_pathAppData;

   }
   else
   {

      string strAppFolder = _002Underscore(strAppId);

      return m_psystem->m_pacmedir->home() / "application" / strAppFolder;

   }

}

::file::path dir_context::cache()
{

   return m_psystem->m_pacmedir->ca2roaming() / "cache";

}


::file::path dir_context::commonappdata_root()
{

   return "/::payload/lib";

}


::file::path dir_context::commonappdata()
{

   return element_commonappdata(install());

}

::file::path dir_context::element_commonappdata(const ::string & strElement)
{

   string strRelative;

   strRelative = strElement;

   index iFind = strRelative.find(':');

   if (iFind >= 0)
   {

      strsize iFind1 = strRelative.reverse_find("\\", iFind);

      strsize iFind2 = strRelative.reverse_find("/", iFind);

      strsize iStart = maximum(iFind1 + 1, iFind2 + 1);

      strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);

   }

   return commonappdata_root() / strRelative;

}


//::file::path dir_context::usersystemappdata(const string & pcszPrefix)

//{
//   __UNREFERENCED_PARAMETER(pobject);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   throw ::interface_only("this is an interface");
//}


//::file::path dir_context::userappdata(::object * pobject)
//{

//   __UNREFERENCED_PARAMETER(pobject);

//   throw ::interface_only("this is an interface");

//}


//::file::path dir_context::userdata(::object * pobject)
//{

//   __UNREFERENCED_PARAMETER(pobject);

//   throw ::interface_only("this is an interface");

//}


//::file::path dir_context::default_os_user_path_prefix(::object * pobject)
//{

//   __UNREFERENCED_PARAMETER(pobject);

//   throw ::interface_only("this is an interface");

//}


//::file::path dir_context::default_userappdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pobject);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}

//::file::path dir_context::default_userdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pobject);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}

//::file::path dir_context::default_userfolder(const string & pcszPrefix, const string & lpcszLogin)

//{
//   __UNREFERENCED_PARAMETER(pobject);
//   __UNREFERENCED_PARAMETER(pcszPrefix);

//   __UNREFERENCED_PARAMETER(pcszLogin);

//   throw ::interface_only("this is an interface");
//}


::file::path dir_context::userquicklaunch()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::userprograms()
{

   throw ::interface_only("this is an interface");

   return "";

}


::file::path dir_context::commonprograms()
{

   throw ::interface_only("this is an interface");

   return "";

}


bool dir_context::is_inside_time(const ::file::path & pszPath)
{

   __UNREFERENCED_PARAMETER(pszPath);

   throw ::interface_only("this is an interface");

   return false;

}


bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
{

   __UNREFERENCED_PARAMETER(pszDir);
   __UNREFERENCED_PARAMETER(pszPath);

   throw ::interface_only("this is an interface");

   return false;

}


::file::watcher & dir_context::watcher()
{

   auto psystem = get_system()->m_papexsystem;

   return *psystem->m_pdirsystem->m_pfilewatcher;

}


//::file::path dir_context::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
//{
//
//   ::file::path_array stra;
//
//   stra.add_tokens(pszEnv, ":", false);
//
//   string strCandidate;
//
//   for (i32 i = 0; i < stra.get_count(); i++)
//   {
//
//      strCandidate = stra[i] / pszTopic;
//
//      if (m_pcontext->m_papexcontext->file().exists(strCandidate))
//      {
//         return strCandidate;
//      }
//
//   }
//
//   return "";
//
//}

//      ::file::path dir_context::get_api_cc()
//      {
//
//         if(m_strApiCc.has_char())
//            return m_strApiCc;
//
//         synchronous_lock synchronouslock(&m_mutex);
//
//
//
//         return m_strApiCc;
//
//      }




::file::path dir_context::bookmark()
{

   return m_psystem->m_pacmedir->bookmark();

}


//::file::path dir_context::home()
//{

//   return m_psystem->m_pacmedir->home();

//}

::file::path dir_context::desktop()
{

   return home() / "Desktop";

}


::file::path dir_context::document()
{

   return home() / "Document";

}


::file::path dir_context::document2()
{

#ifdef _UWP

    return image();

#else

    return document();

#endif

}


::file::path dir_context::download()
{

   return home() / "Downloads";

}


::file::path dir_context::music()
{

   return home() / "Music";

}


::file::path dir_context::video()
{

   return home() / "Video";

}


::file::path dir_context::image()
{

   return home() / "Image";

}


::file::path dir_context::dropbox()
{

   if(m_bDropboxCalculated)
   {


      return m_pathDropbox;

   }

   ::file::path pathNetworkPayload = m_pcontext->m_papexcontext->file().dropbox_info_network_payload();

   if (!m_pcontext->m_papexcontext->file().exists(pathNetworkPayload))
   {

      auto pathHome =  m_pcontext->m_papexcontext->dir().home();

      auto pathTxt = pathHome / "dropbox.txt";

      string strPath = m_pcontext->m_papexcontext->file().as_string(pathTxt);

      strPath.trim();

      m_pathDropbox = strPath;

      m_bDropboxCalculated = true;

      return strPath;

   }

   string strNetworkPayload = m_pcontext->m_papexcontext->file().as_string(pathNetworkPayload);

   ::property_set set;

   set.parse_network_payload(strNetworkPayload);

   m_pathDropbox = set["personal"]["path"];

   m_bDropboxCalculated = true;

   return m_pathDropbox;

}


::file::path dir_context::onedrive()
{

   ::file::path pathIni = m_pcontext->m_papexcontext->file().onedrive_cid_ini();

   string strIni = m_pcontext->m_papexcontext->file().as_string(pathIni);

   if(strIni.is_empty())
   {

      return "";

   }

   ::property_set set;

   set.parse_ini(strIni);

   string strLibrary;
   
   strLibrary = set["library"];

   ::str::tokenizer token(strLibrary);

   token.skip_word(7);

   string strWork = token.get_word();

   strWork.trim("\"");

   return strWork;

}


::file::path dir_context::dropbox_app()
{

   if (!m_psystem)
   {

      throw ::exception(error_wrong_state, "m_psystem is null");

   } 
   
   if (m_psystem->m_pappStartup)
   {

      if (m_psystem->m_pappStartup->m_strAppId.is_empty())
      {

         throw ::exception(error_wrong_state, "Application Startup App Id is empty");

      }

      return dropbox() / "application" / m_psystem->m_pappStartup->m_strAppId;

   }

   if (m_psystem->m_pappMain)
   {

      if (m_psystem->m_pappMain->m_strAppId.is_empty())
      {

         throw ::exception(error_wrong_state, "Application Main App Id is empty");

      }

      return dropbox() / "application" / m_psystem->m_pappMain->m_strAppId;

   }

   throw ::exception(error_wrong_state, "Neither Application Startup or Application Main are set");

   return {};
}


::file::path dir_context::standalone()
{

   auto psystem = get_system()->m_papexsystem;

   return m_psystem->m_pacmedir->roaming() / psystem->m_strStandalone;

}


//string_array dir_context::locale_schema_matter(string & strLocale, const ::string & strStyle)
//{

//   return psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle);

//}


//string_array dir_context::locale_schema_matter(string & strLocale, const ::string & strStyle, const string & pathRoot, const ::file::path & pathDomain)
//{

//   return psystem->m_spdir->locale_schema_matter(get_app(), strLocale, strStyle, pathRoot, pathDomain);

//}

//
//string dir_context::matter(const ::file::path_array & patha, bool bDir)
//{
//
//   return psystem->m_spdir->matter(get_app(), patha, bDir);
//
//}


//string dir_context::matter(const ::file::path & path, bool bDir)
//{
//
//   return psystem->m_spdir->matter(get_app(), path, bDir);
//
//}
////
//
//void dir_context::matter_ls(const ::file::path & str, ::file::path_array & stra)
//{
//   psystem->m_spdir->matter_ls(get_app(), str, stra);
//}
//
//void dir_context::matter_ls_file(const ::file::path & str, ::file::path_array & stra)
//{
//   psystem->m_spdir->matter_ls_file(get_app(), str, stra);
//}


//::file::path dir_context::matter_file(const ::file::path & pcsz, bool bDir)
//
//{
//
//   string strPath = psystem->m_spdir->matter(get_app(), pcsz, bDir);
//
//
//   return strPath;
//
//}


//::file::path dir_context::userquicklaunch()
//{
//
//   return psystem->m_spdir->userquicklaunch(this);
//
//}

//
//::file::path dir_context::userprograms()
//{
//
//   return psystem->m_spdir->userprograms(this);
//
//}


//::file::listing & dir_context::ls(listing & listing)
//{
//
//   return psystem->m_spdir.m_p->ls(get_app(), listing);
//
//}

//::file::listing & dir_context::ls_relative_name(listing & listing)
//{
//
//   return psystem->m_spdir.m_p->ls_relative_name(get_app(), listing);
//
//}
//

//bool dir_context::has_subdir(const ::file::path & pcsz)
//
//{
//
//   return psystem->m_spdir.m_p->has_subdir(get_app(), pcsz);
//
//
//}
//

//bool dir_context::is(const ::file::path & pcsz)
//
//{
//
//   return psystem->m_spdir.m_p->is(pcsz, get_app());
//
//
//}
//

//bool dir_context::is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath)
//
//{
//
//   return psystem->m_spdir.m_p->is_inside(pcszDir, lpcszPath, get_app());
//
//
//}
//

//bool dir_context::is_inside_time(const ::file::path & pcsz)
//
//{
//   return psystem->m_spdir.m_p->is_inside_time(pcsz, get_app());
//
//}


//::file::listing & dir_context::root_ones(::file::listing & listing)
//{
//   return psystem->m_spdir.m_p->root_ones(listing, get_app());
//}
//

//bool dir_context::mk(const ::file::path & path)
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


//bool dir_context::rm(const ::file::path & path, bool bRecursive)
//{
//
//   return psystem->m_spdir.m_p->rm(get_app(), path, bRecursive);
//
//}


::file::path dir_context::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
{

   return m_psystem->m_pacmedir->pathfind(pszEnv, pszTopic, pszMode);

}


//::file::path dir_context::dropbox()
//{
//
//   return psystem->m_spdir->dropbox(get_app());
//
//}


//::file::path dir_context::onedrive()
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


