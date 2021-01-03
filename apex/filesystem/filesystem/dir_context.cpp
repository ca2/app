#include "framework.h"
#include "apex/platform/app_core.h"
#include "apex/compress/zip/_.h"
#include "apex/const/id.h"

//extern const char* g_pszServerCa2Cc;


CLASS_DECL_ACME const char* get_server_ca2_cc();


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

   //if (::file::dir_context::g_pthis == nullptr)
   //{

   //   ::file::dir_context::g_pthis = this;

   //   add_ref(OBJ_REF_DBG_ARGS);

   //}

   //m_pziputil = nullptr;

   //         m_isdirmap.m_millisTimeout = 180000;



}


dir_context::~dir_context()
{

   //::acme::del(m_pziputil);

}


::e_status dir_context::initialize(::layered * pobjectContext)
{

   auto estatus = ::object::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::e_status dir_context::init_system()
{

   return ::success;

}



::e_status dir_context::init_context()
{

   return ::success;

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

//::file::path dir_context::simple_path(const string & strFolder, const string & strRelative)
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

//::file::path dir_context::simple_path(const string & strFolder, const string & strRelative, const string & str2)
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
//   UNREFERENCED_PARAMETER(pcszSource);

//   UNREFERENCED_PARAMETER(pcszRelative);

//   __throw(interface_only_exception("this is an interface"));
//}


//::file::path dir_context::relpath(const string & pcszSource, const string & lpcszRelative, const string & psz2)

//{
//   UNREFERENCED_PARAMETER(pcszSource);

//   UNREFERENCED_PARAMETER(pcszRelative);

//   UNREFERENCED_PARAMETER(psz2);
//   __throw(interface_only_exception("this is an interface"));
//}


::file::listing & dir_context::root_ones(::file::listing & listing)
{

   __throw(interface_only_exception("this is an interface"));

}


::file::listing & dir_context::ls(::file::listing & l)
{

   l.m_pathFinal = Context.defer_process_path(l.m_pathUser);

   if (l.m_pathFinal.begins_ci("matter://"))
   {

      ::str::begins_eat_ci(l.m_pathFinal, "matter://");

      matter_ls(l.m_pathFinal, l);

      return l;

   }

   if (l.m_bRecursive)
   {

      if (l.m_eextract != extract_none && thread_is_set(id_thread_zip_is_dir) && (icmp(l.m_pathFinal.ext(), ".zip") == 0 || l.m_pathFinal.find_ci("zip:") >= 0))
      {

         //__throw(::exception::exception("should implement recursive zip"));

         //m_pziputil->ls(papp,l);

         l = ::error_failed;

      }
      else
      {

         l = ::error_failed;


      }


   }
   else
   {

      if (::str::begins_ci(l.m_pathFinal, "http://") || ::str::begins_ci(l.m_pathFinal, "https://"))
      {

         property_set set;

         string str =Context.http().get(l.m_pathFinal, set);

         l.add_tokens(str, "\n", false);

      }
      else if (thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(l.m_pathFinal, ".zip") || ::str::find_file_extension("zip:", l.m_pathFinal) >= 0))
      {

         zip_context zip(get_context_object());

         zip.ls(l);

      }
      else
      {

         l = ::error_failed;

      }

   }

   return l;

}

::file::listing & dir_context::ls_relative_name(::file::listing & l)
{

   if (l.m_bRecursive)
   {

      if (l.m_eextract != extract_none && ::thread_is_set(id_thread_zip_is_dir) && (icmp(l.m_pathUser.ext(), ".zip") == 0 || l.m_pathUser.find_ci("zip:") >= 0))
      {

         //__throw(::exception::exception("should implement recursive zip"));

         //m_pziputil->ls(papp,l);

         l = ::error_failed;

      }
      else
      {

         l = ::error_failed;

      }

   }
   else
   {

      if (::str::begins_ci(l.m_pathUser, "http://") || ::str::begins_ci(l.m_pathUser, "https://"))
      {

         property_set set;

         string str = Context.http().get(l.m_pathUser, set);

         l.add_tokens(str, "\n", false);

      }
      else if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(l.m_pathUser, ".zip") || ::str::find_file_extension("zip:", l.m_pathUser) >= 0))
      {

         zip_context zip(get_context_object());

         zip.ls(l);

      }
      else
      {

         l = ::error_failed;

      }

   }

   return l;

}


::file::listing& dir_context::rls(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   return ls(listing);

}


::file::listing& dir_context::rls_relative_name(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   return ls_relative_name(listing);

}


::file::listing& dir_context::ls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = false;

   listing.m_bDir = true;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


::file::listing& dir_context::ls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = false;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


::file::listing& dir_context::rls_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


::file::listing& dir_context::rls_file_pattern(::file::listing& listing, const ::file::path& path, const string_array& straPattern)
{

   listing.m_pathUser = path;

   listing.m_bRecursive = true;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern = straPattern;

   return ls(listing);

}


::file::listing& dir_context::ls_file(::file::listing& listing)
{

   listing.m_bRecursive = false;

   listing.m_bDir = false;

   listing.m_bFile = true;

   //listing.m_straPattern.remove_all();

   return ls(listing);

}


::file::listing& dir_context::ls_dir(::file::listing& listing)
{

   listing.m_bRecursive = false;

   listing.m_bDir = true;

   listing.m_bFile = false;

   listing.m_straPattern.remove_all();

   return ls(listing);

}


::file::listing& dir_context::rls_file(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = false;

   listing.m_bFile = true;

   listing.m_straPattern.remove_all();

   return ls(listing);

}


::file::listing& dir_context::rls_dir(::file::listing& listing)
{

   listing.m_bRecursive = true;

   listing.m_bDir = true;

   listing.m_bFile = false;

   listing.m_straPattern.remove_all();

   return ls(listing);

}


bool dir_context::has_subdir(const ::file::path & pathFolder)
{

   ::file::listing ls;

   Context.dir().ls_dir(ls, pathFolder);

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

      if (Context.file().resolve_link(pathTarget, path))
      {

         bIs = is(pathTarget);

         return true;

      }

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

   if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(path, ".zip")))
   {

      bIs = true;

      return true;
   }

   if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      //            u32 dwLastError;

                  //if (m_isdirmap.lookup(pcszPath, bHasSubFolder, dwLastError))

                  //{

                  //   bIs = bHasSubFolder;

                  //   return true;

                  //}

      zip_context zip(get_context_object());

      bHasSubFolder = zip.has_sub_folder(path);

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
   //            if (Context.file().resolve_link(strTarget, strFolder, strParams, pcszPath))

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

   if (pathParam.begins_ci("appmatter://"))
   {

      path = System.m_pdirsystem->m_pathLocalAppMatterFolder / path.Mid(12);

   }
   else
   {

      path = pathParam;

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

      return Context.http().exists(path, set);

   }

   if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(path, ".zip")))
   {

      //m_isdirmap.set(path, true, 0);

      return true;

   }

   if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
   {

      bool bHasSubFolder;

      zip_context zip(get_context_object());

      bHasSubFolder = zip.has_sub_folder(path);

      //            m_isdirmap.set(path, bHasSubFolder, get_last_error());

      return bHasSubFolder;

   }

   return false;

}


bool dir_context::name_is(const ::file::path & strPath)
{

   //output_debug_string(strPath);
   if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(strPath, ".zip")))
   {
      //            m_isdirmap.set(strPath, true, 0);
      return true;
   }
   if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", strPath) >= 0))
   {
      bool bHasSubFolder;

      zip_context zip(get_context_object());
      //            u32 dwLastError;
                  //if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
                  //   return bHasSubFolder;
      bHasSubFolder = zip.has_sub_folder(strPath);
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
//         cslock sl(&m_cs);
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
//            iFind3 = min_non_neg(iFind1, iFind2);
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
//            index iFind = pdir->pred_binary_search(&find, [&](auto & t1, auto & t2)
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
//         if (::get_fast_tick_count() > pdir->m_millisLastCheck + m_millisTimeout)
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
//            index iFind = pdir->pred_binary_search(&find, [&](auto & t1, auto & t2)
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
//            index iFind = pdir->pred_binary_search(&find, [&](auto & t1, auto & t2)
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
//            index iFind = pdir->pred_binary_search(&find, [&](auto & t1, auto & t2)
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
//         if (::get_fast_tick_count() > pdir->m_millisLastCheck + m_millisTimeout)
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
//         cslock sl(&m_cs);
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
//            iFind3 = min_non_neg(iFind1, iFind2);
//            if (iFind3 < 0)
//            {
//               pfind->m_str = strPath.Mid(iFind0);
//            }
//            else
//            {
//               pfind->m_str = strPath.Mid(iFind0, iFind3 - iFind0);
//            }
//
//            index iFind = pdir->pred_binary_search(pfind, [&](auto & t1, auto & t2)
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
//                  iFind3 = min_non_neg(iFind1, iFind2);
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
//                  pfind->m_millisLastCheck = ::get_fast_tick_count();
//
//                  pdir->add(pfind);
//
//                  pdir->pred_sort([&](auto & t1, auto & t2)
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
//            pdir->m_millisLastCheck = ::get_fast_tick_count();
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
   __throw(interface_only_exception("this is an interface"));
}

::file::path dir_context::stage()
{
   __throw(interface_only_exception("this is an interface"));
}


::file::path dir_context::stageapp()
{

   __throw(interface_only_exception("this is an interface"));

}


::file::path dir_context::netseed()
{

   __throw(interface_only_exception("this is an interface"));

}


::file::path dir_context::install()
{

   sync_lock sl(mutex());

   return System.m_pdirsystem->m_pathInstall;

}


::file::path dir_context::config()
{

   sync_lock sl(mutex());

   return System.m_pdirsystem->m_pathCa2Config;

}


::file::path dir_context::home()
{

   sync_lock sl(mutex());

   return System.m_pdirsystem->m_pathHome;

}

//::file::path dir_context::userfolder(::layered * pobjectContext)
//{

//   UNREFERENCED_PARAMETER(pobject);

//   sync_lock sl(mutex());

//   return m_pathUser;

//}


::file::path dir_context::module()
{

   sync_lock sl(mutex());

   return System.m_pdirsystem->m_pathModule;

}


::file::path dir_context::ca2module()
{

   sync_lock sl(mutex());

   return System.m_pdirsystem->m_pathCa2Module;

}


::file::path dir_context::time_square()
{

   return time() / "time";

}


::file::path dir_context::time_log(const string & pszId)
{

   UNREFERENCED_PARAMETER(pszId);
   __throw(interface_only_exception("this is an interface"));

}


bool dir_context::mk(const ::file::path & path)
{

   UNREFERENCED_PARAMETER(path);
   __throw(interface_only_exception("this is an interface"));

}


bool dir_context::rm(const ::file::path & path, bool bRecursive)
{

   UNREFERENCED_PARAMETER(path);
   UNREFERENCED_PARAMETER(bRecursive);
   __throw(interface_only_exception("this is an interface"));

}


::file::path dir_context::locale_schema_matter(const string & strLocale, const string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain)
{

   string strHint = pathRoot / "_matter" / pathDomain / Application.get_locale_schema_dir(strLocale, strSchema);

   return strHint;

}


::file::path dir_context::matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain)
{

   string strMatter = ::file::path("appmatter://") / pathRoot / "_matter" / pathDomain / "_std/_std" / path;

   return strMatter;

}


void dir_context::matter_ls(const ::file::path & path, ::file::listing & stra)
{

   sync_lock sl(System.m_spmutexMatter);

   string strDir = matter(path, true);

   if (System.m_pdirsystem->m_bMatterFromHttpCache)
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

         strsize iFind = min_non_neg(iFind1, iFind2);

         if (iFind > 0)
         {

            strMatter = strMatter.Mid(iFind);

         }

      }

      property_set set;

      set["raw_http"] = true;

      ::file::path strFile = Context.dir().cache() / strMatter / "list_dir.list_dir";

      strsize iFind = strFile.find(DIR_SEPARATOR);

      if (iFind > 0)
      {

         strFile.replace(":", "_", iFind + 1);

      }

      strFile.replace("////", "//");
      strFile.replace("\\\\", "\\", 1);

      ::file::path strLs;

      if (Context.file().exists(strFile))
      {

         strLs = Context.file().as_string(strFile);

      }
      else
      {

         // todo: keep cache timeout information;

         string strUrl = "https://api.ca2.cc/api/matter/list_dir?dir=" + System.url().url_encode(strMatter);

         strLs = Context.http().get(strUrl, set);

         Context.file().put_contents(strFile, strLs);

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
   else
   {

      strDir = Context.get_matter_cache_path(strDir);

      Context.dir().ls(stra, strDir);

   }

}


void dir_context::matter_ls_file(const ::file::path & str, ::file::listing & stra)
{

   ::file::path strDir = matter(str, true);

   if (System.m_pdirsystem->m_bMatterFromHttpCache)
   {

      property_set set;

      set["raw_http"] = true;

      string strFile = Context.dir().cache() / strDir / "list_dir.list_dir";

      strsize iFind = strFile.find(DIR_SEPARATOR);

      if (iFind > 0)
      {

         strFile.replace(":", "_", iFind + 1);

      }

      strFile.replace("////", "//");
      strFile.replace("\\\\", "\\", 1);

      string strLs;

      if (Context.file().exists(strFile))
      {

         strLs = Context.file().as_string(strFile);

      }


      ::file::patha straLs;

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

      Context.dir().ls(stra, strDir);

   }

}


::file::path dir_context::matter_from_locator(const ::file::patha & patha, const string_array & straMatterLocator, bool bDir)
{

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

   if(System.m_pdirsystem->m_pathLocalAppMatterCacheFolder.has_char())
   {

      ::file::path pathLs0 = straMatterLocator.first();

      pathLs0 /= Context.get_locale_schema_dir();

      pathCache = System.m_pdirsystem->m_pathLocalAppMatterCacheFolder / pathLs0 / patha[0] + ".map_question";

      TRACE("cache map path: %s", pathCache.c_str());

      path = Context.file().as_string(pathCache);

      if (::str::begins_eat_ci(path, "itdoesntexist."))
      {

         millis t = ansi_to_i64(path);

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

            strFinal = System.m_pdirsystem->m_pathLocalAppMatterFolder / strFinal.Mid(12);

         }

         if (::is_file_or_dir_dup(strFinal, nullptr))
         {

            TRACE("!!Cache Hit: %s", strFinal.c_str());

            return path;

         }

         TRACE("...Cache Miss: %s", strFinal.c_str());

      }

   }

   string strLocale;

   string strSchema;

   string_array straLs;

   Context.locale_schema_matter(straLs, straMatterLocator, strLocale, strSchema);

   auto psession = Session;

   ::apex::str_context * pcontext = psession->str_context();

   if (System.m_pdirsystem->m_bMatterFromHttpCache)
   {

      string_array stra;

      string strMatter;

      for (auto & strLs : straLs)
      {

         for (auto & pathItem : patha)
         {

            strMatter = strLs / pathItem;

            path = ::dir::ca2roaming() / "_matter" / strMatter;

            //                  if (::is_file_or_dir_dup(path, nullptr))
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

      TRACE("");
      TRACE("Topic: %s", patha[0].c_str());
      TRACE("");

      string strCandidate = stra.implode("|");

      string strParam = System.url().url_encode(strCandidate);

      string strUrl;

      if (bDir)
      {

         strUrl = "https://ca2.cc/api/matter/query_dir?candidate=" + strParam;

      }
      else
      {

         strUrl = "https://ca2.cc/api/matter/query_file?candidate=" + strParam;

      }

      const char * pszUrl = strUrl;

      strMatter = Context.http().get(strUrl, set);

      strMatter.replace("https://server.ca2.cc/", string(get_server_ca2_cc()));

      TRACE("");
      TRACE("");
      TRACE("matter = ::: %s", strMatter.c_str());
      TRACE("");
      TRACE("");

      strMatter.trim();

      if (strMatter.has_char() && ::str::begins_eat_ci(strMatter, string(get_server_ca2_cc()) + "matter/"))
      {

         path = "appmatter://" + strMatter;

         if (bDir)
         {

            ::dir::mk(System.m_pdirsystem->m_pathLocalAppMatterFolder / strMatter);

         }

         goto ret;

      }

   }
   else
   {

      string strMatter;

      for (auto & strLs : straLs)
      {

         for (auto & pathItem : patha)
         {

            strMatter = strLs / pathItem;

            path = System.m_pdirsystem->m_pathLocalAppMatterFolder / strMatter;

            if (::is_file_or_dir_dup(path, nullptr))
            {

               goto ret;

            }

         }

      }

   }

   path = "itdoesntexist." + __str(millis::now().m_iMilliseconds);

ret:

   if (pathCache.has_char() && System.m_pdirsystem->m_bMatterFromHttpCache)
   {

      Context.file().put_contents(pathCache, path);

      //::file::path pathCache2 = System.m_pdirsystem->m_pathLocalAppMatterFolder / path;

      //if ((path & ::file::e_flag_get_local_path)
      //   || (!(path & ::file::e_flag_bypass_cache) && is_file_or_dir_dup(pathCache, nullptr)))
      //{

      //   return pathCache;

      //}

      string strMatter(path);

      ::str::begins_eat_ci(strMatter, "appmatter://");

      ::file::path pathCache = System.m_pdirsystem->m_pathLocalAppMatterFolder / strMatter;

      ::file::path pathMeta = pathCache + ".meta_information";

      System.file().del(pathMeta);

      ((cflag < ::file::enum_flag >&)path) = patha[0];

   }

   return path;

}


::file::path dir_context::matter_from_locator(::file::path path, const string_array & straMatterLocator, bool bDir)
{

   ::file::patha patha;

   ::str::begins_eat_ci((string &) path, "matter://");

   patha.add(path);

   return matter_from_locator(patha, straMatterLocator, bDir);

}


::file::path dir_context::matter(const ::file::patha & patha, bool bDir)
{

   string_array straMatterLocator;
   {

      sync_lock sl(mutex());

      straMatterLocator = Application.m_straMatterLocator;

   }

   return matter_from_locator(patha, straMatterLocator, bDir);

}


::file::path dir_context::matter(::file::path path, bool bDir)
{

   string_array straMatterLocator;

   {

      sync_lock sl(mutex());

      straMatterLocator = Context.m_straMatterLocator;

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

      strApp.replace("-", "_");

      strApp.replace("\\", "_");

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

   ::file::path point = System.local_get_matter_cache_path(
      ::file::path(strRepo) / "_matter" / strApp / "_std" / "_std" / pathRel);

   return point;

}




::file::path dir_context::commonappdata(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration)
{

   sync_lock sl(mutex());

   string strAppId(pszAppId);

   string strPlatform(pszPlatform);

   if (strPlatform.is_empty())
   {

      strPlatform = System.get_system_platform();

   }

   string strConfiguration(pszConfiguration);

   if (strConfiguration.is_empty())
   {

      strConfiguration = System.get_system_configuration();

   }

   string strBuild(pszBuild);

   return commonappdata() / strBuild / strPlatform / strConfiguration / strAppId;

}


::file::path dir_context::commonappdata_locale_schema(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
{

   sync_lock sl(mutex());

   string strLocale(pszLocale);

   if (strLocale.is_empty())
   {

      auto psession = Session;

      strLocale = psession->m_strLocale;

   }

   string strSchema(pszSchema);

   if (strSchema.is_empty())
   {

      auto psession = Session;

      strSchema = psession->m_strSchema;

   }

   return commonappdata(pszAppId, pszBuild, pszPlatform, pszConfiguration) / strLocale / strSchema;

}


::file::path dir_context::trash_that_is_not_trash(const ::file::path & psz)
{

   UNREFERENCED_PARAMETER(psz);

   __throw(interface_only_exception("this is an interface"));

}


::file::path dir_context::appdata()
{

   //__throw(interface_only_exception("this is an interface"));

   return System.m_pdirsystem->m_pathAppData;

}

::file::path dir_context::cache()
{

   return ::dir::ca2roaming() / "cache";

}


::file::path dir_context::commonappdata_root()
{

   return "/payload/lib";

}


::file::path dir_context::commonappdata()
{

   return element_commonappdata(install());

}

::file::path dir_context::element_commonappdata(const string & strElement)
{

   string strRelative;

   strRelative = strElement;

   index iFind = strRelative.find(':');

   if (iFind >= 0)
   {

      strsize iFind1 = strRelative.reverse_find("\\", iFind);

      strsize iFind2 = strRelative.reverse_find("/", iFind);

      strsize iStart = max(iFind1 + 1, iFind2 + 1);

      strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);

   }

   return commonappdata_root() / strRelative;

}


//::file::path dir_context::usersystemappdata(const string & pcszPrefix)

//{
//   UNREFERENCED_PARAMETER(pobject);
//   UNREFERENCED_PARAMETER(pcszPrefix);

//   __throw(interface_only_exception("this is an interface"));
//}


//::file::path dir_context::userappdata(::layered * pobjectContext)
//{

//   UNREFERENCED_PARAMETER(pobject);

//   __throw(interface_only_exception("this is an interface"));

//}


//::file::path dir_context::userdata(::layered * pobjectContext)
//{

//   UNREFERENCED_PARAMETER(pobject);

//   __throw(interface_only_exception("this is an interface"));

//}


//::file::path dir_context::default_os_user_path_prefix(::layered * pobjectContext)
//{

//   UNREFERENCED_PARAMETER(pobject);

//   __throw(interface_only_exception("this is an interface"));

//}


//::file::path dir_context::default_userappdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   UNREFERENCED_PARAMETER(pobject);
//   UNREFERENCED_PARAMETER(pcszPrefix);

//   UNREFERENCED_PARAMETER(pcszLogin);

//   __throw(interface_only_exception("this is an interface"));
//}

//::file::path dir_context::default_userdata(const string & pcszPrefix, const string & lpcszLogin)

//{
//   UNREFERENCED_PARAMETER(pobject);
//   UNREFERENCED_PARAMETER(pcszPrefix);

//   UNREFERENCED_PARAMETER(pcszLogin);

//   __throw(interface_only_exception("this is an interface"));
//}

//::file::path dir_context::default_userfolder(const string & pcszPrefix, const string & lpcszLogin)

//{
//   UNREFERENCED_PARAMETER(pobject);
//   UNREFERENCED_PARAMETER(pcszPrefix);

//   UNREFERENCED_PARAMETER(pcszLogin);

//   __throw(interface_only_exception("this is an interface"));
//}

::file::path dir_context::userquicklaunch()
{
   __throw(interface_only_exception("this is an interface"));
}

::file::path dir_context::userprograms()
{
   __throw(interface_only_exception("this is an interface"));
}

::file::path dir_context::commonprograms()
{
   __throw(interface_only_exception("this is an interface"));
}

bool dir_context::is_inside_time(const ::file::path & pszPath)
{
   UNREFERENCED_PARAMETER(pszPath);
   __throw(interface_only_exception("this is an interface"));
}

bool dir_context::is_inside(const ::file::path & pszDir, const ::file::path & pszPath)
{
   UNREFERENCED_PARAMETER(pszDir);
   UNREFERENCED_PARAMETER(pszPath);
   __throw(interface_only_exception("this is an interface"));
}


::file::watcher & dir_context::watcher()
{

   return *System.m_pdirsystem->m_pfilewatcher;

}


::file::path dir_context::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
{

   ::file::patha stra;

   stra.add_tokens(pszEnv, ":", false);

   string strCandidate;

   for (i32 i = 0; i < stra.get_count(); i++)
   {

      strCandidate = stra[i] / pszTopic;

      if (Context.file().exists(strCandidate))
      {
         return strCandidate;
      }

   }

   return "";

}

//      ::file::path dir_context::get_api_cc()
//      {
//
//         if(m_strApiCc.has_char())
//            return m_strApiCc;
//
//         sync_lock sl(&m_mutex);
//
//
//
//         return m_strApiCc;
//
//      }




::file::path dir_context::bookmark()
{

   return ::dir::bookmark();

}


//::file::path dir_context::home()
//{

//   return ::dir::home();

//}

::file::path dir_context::desktop()
{

   return home() / "Desktop";

}


::file::path dir_context::document()
{

   return home() / "Document";

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

   ::file::path pathJson = Context.file().dropbox_info_json();

   if (!Context.file().exists(pathJson))
   {

      ::file::path pathTxt = Context.dir().home() / "dropbox.txt";

      string strPath = Context.file().as_string(pathTxt);

      strPath.trim();

      return strPath;

   }


   string strJson = Context.file().as_string(pathJson);

   ::property_set set;

   set.parse_json(strJson);

   return set["personal"]["path"];

}


::file::path dir_context::onedrive()
{
   ::file::path pathIni = Context.file().onedrive_cid_ini();

   string strIni = Context.file().as_string(pathIni);

   ::property_set set;

   set.parse_ini(strIni);

   string strLibrary = set["library"];

   ::str::tokenizer token(strLibrary);

   token.skip_word(7);

   string strWork = token.get_word();

   strWork.trim("\"");

   return strWork;

}

::file::path dir_context::standalone()
{


   return ::dir::roaming() / System.m_strStandalone;

}


//string_array dir_context::locale_schema_matter(string & strLocale, const string & strStyle)
//{

//   return System.m_spdir->locale_schema_matter(get_context_application(), strLocale, strStyle);

//}


//string_array dir_context::locale_schema_matter(string & strLocale, const string & strStyle, const string & pathRoot, const ::file::path & pathDomain)
//{

//   return System.m_spdir->locale_schema_matter(get_context_application(), strLocale, strStyle, pathRoot, pathDomain);

//}

//
//string dir_context::matter(const ::file::patha & patha, bool bDir)
//{
//
//   return System.m_spdir->matter(get_context_application(), patha, bDir);
//
//}


//string dir_context::matter(const ::file::path & path, bool bDir)
//{
//
//   return System.m_spdir->matter(get_context_application(), path, bDir);
//
//}
////
//
//void dir_context::matter_ls(const ::file::path & str, ::file::patha & stra)
//{
//   System.m_spdir->matter_ls(get_context_application(), str, stra);
//}
//
//void dir_context::matter_ls_file(const ::file::path & str, ::file::patha & stra)
//{
//   System.m_spdir->matter_ls_file(get_context_application(), str, stra);
//}


//::file::path dir_context::matter_file(const ::file::path & pcsz, bool bDir)
//
//{
//
//   string strPath = System.m_spdir->matter(get_context_application(), pcsz, bDir);
//
//
//   return strPath;
//
//}


//::file::path dir_context::userquicklaunch()
//{
//
//   return System.m_spdir->userquicklaunch(get_object());
//
//}

//
//::file::path dir_context::userprograms()
//{
//
//   return System.m_spdir->userprograms(get_object());
//
//}


//::file::listing & dir_context::ls(listing & listing)
//{
//
//   return System.m_spdir.m_p->ls(get_context_application(), listing);
//
//}

//::file::listing & dir_context::ls_relative_name(listing & listing)
//{
//
//   return System.m_spdir.m_p->ls_relative_name(get_context_application(), listing);
//
//}
//

//bool dir_context::has_subdir(const ::file::path & pcsz)
//
//{
//
//   return System.m_spdir.m_p->has_subdir(get_context_application(), pcsz);
//
//
//}
//

//bool dir_context::is(const ::file::path & pcsz)
//
//{
//
//   return System.m_spdir.m_p->is(pcsz, get_context_application());
//
//
//}
//

//bool dir_context::is_inside(const ::file::path & pcszDir, const ::file::path & lpcszPath)
//
//{
//
//   return System.m_spdir.m_p->is_inside(pcszDir, lpcszPath, get_context_application());
//
//
//}
//

//bool dir_context::is_inside_time(const ::file::path & pcsz)
//
//{
//   return System.m_spdir.m_p->is_inside_time(pcsz, get_context_application());
//
//}


//::file::listing & dir_context::root_ones(::file::listing & listing)
//{
//   return System.m_spdir.m_p->root_ones(listing, get_context_application());
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
//   return System.m_spdir.m_p->mk(path, get_context_application());
//
//}


//bool dir_context::rm(const ::file::path & path, bool bRecursive)
//{
//
//   return System.m_spdir.m_p->rm(get_context_application(), path, bRecursive);
//
//}


//::file::path dir_context::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
//{
//
//   return System.m_spdir->pathfind(pszEnv, pszTopic, pszMode, get_context_application());
//
//}


//::file::path dir_context::dropbox()
//{
//
//   return System.m_spdir->dropbox(get_context_application());
//
//}


//::file::path dir_context::onedrive()
//{
//
//   return System.m_spdir->onedrive(get_context_application());
//
//}


//
//
//} // namespace file
//
//


