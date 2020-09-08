#include "framework.h"
#include "acme/app_core.h"
#include "acme/compress/zip/_.h"
#include "acme/const/id.h"


#ifdef WINDOWS

#define DIR_SEPARATOR "\\"

#else

#define DIR_SEPARATOR "/"

#endif


namespace file
{


   
      system_dir * system_dir::g_pthis = nullptr;


      system_dir::system_dir()
      {

         if(::file::system_dir::g_pthis == nullptr)
         {

            ::file::system_dir::g_pthis = this;

            add_ref(OBJ_REF_DBG_ARGS);

         }

         m_pziputil = nullptr;

//         m_isdirmap.m_tickTimeout = 180000;

         m_pathInstall = ::dir::install();

      }


      system_dir::~system_dir()
      {

         ::acme::del(m_pziputil);

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

      //::file::path system_dir::simple_path(const string & strFolder, const string & strRelative)
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
      //      #if defined(LINUX) || defined(APPLEOS)
      //      psz[iFolderEnd - iFolderBeg + 1] = '/';
      //      #else
      //      psz[iFolderEnd - iFolderBeg + 1] = '\\';
      //      #endif
      //      ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
      //      strPath.ReleaseBuffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
      //   }


      //   return strPath;
      //}

      //::file::path system_dir::simple_path(const string & strFolder, const string & strRelative, const string & str2)
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
      //         #if defined(LINUX) || defined(APPLEOS)
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
      //      #if defined(LINUX) || defined(APPLEOS)
      //      string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
      //      #else
      //      string_STRCAT2_beg_char_end(strPath, '/', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
      //      #endif
      //      return strPath;
      //   }

      //   string strPath;

      //   string & psz = strPath.get_string_buffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
      //   ansi_count_copy(psz, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
      //   #if defined(LINUX) || defined(APPLEOS)
      //   psz[iFolderEnd - iFolderBeg + 1] = '/';
      //   #else
      //   psz[iFolderEnd - iFolderBeg + 1] = '\\';
      //   #endif
      //   ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
      //   #if defined(LINUX) || defined(APPLEOS)
      //   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '/';
      //   #else
      //   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '\\';
      //   #endif
      //   ansi_count_copy(&psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1 + 1], &((const string &)str2)[iBeg2], iEnd2 - iBeg2 + 1);
      //   strPath.ReleaseBuffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);

      //   return strPath;

      //}


      //::file::path system_dir::relpath(const string & pcszSource,const string & lpcszRelative)

      //{
      //   UNREFERENCED_PARAMETER(pcszSource);

      //   UNREFERENCED_PARAMETER(pcszRelative);

      //   __throw(interface_only_exception("this is an interface"));
      //}


      //::file::path system_dir::relpath(const string & pcszSource, const string & lpcszRelative, const string & psz2)

      //{
      //   UNREFERENCED_PARAMETER(pcszSource);

      //   UNREFERENCED_PARAMETER(pcszRelative);

      //   UNREFERENCED_PARAMETER(psz2);
      //   __throw(interface_only_exception("this is an interface"));
      //}


      ::file::listing & system_dir::root_ones(::file::listing & listing, ::generic * pobject)
      {

         UNREFERENCED_PARAMETER(listing);

         __throw(interface_only_exception("this is an interface"));

      }


      ::file::listing & system_dir::ls(::generic * pobject, listing & l)
      {

         ::file::path path = Context.defer_process_path(l.m_pathUser, pobject);

         if (path.begins_ci("matter://"))
         {

            ::str::begins_eat_ci(path, "matter://");

            matter_ls(pobject, path, l);

            return l;

         }

         if (l.m_bRecursive)
         {

            if (l.m_eextract != extract_none && thread_is_set(id_thread_zip_is_dir) && (icmp(path.ext(), ".zip") == 0 || path.find_ci("zip:") >= 0))
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

            if (::str::begins_ci(path, "http://") || ::str::begins_ci(path, "https://"))
            {

               property_set set;

               string str = Sess(pobject).http().get(path, set);

               l.add_tokens(str, "\n", false);

            }
            else if (thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(path, ".zip") || ::str::find_file_extension("zip:", path) >= 0))
            {

               m_pziputil->ls(pobject, l);

            }
            else
            {

               l = ::error_failed;

            }

         }

         return l;

      }

      ::file::listing & system_dir::ls_relative_name(::generic * pobject, listing & l)
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

               string str = Sess(pobject).http().get(l.m_pathUser, set);

               l.add_tokens(str, "\n", false);

            }
            else if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(l.m_pathUser, ".zip") || ::str::find_file_extension("zip:", l.m_pathUser) >= 0))
            {

               m_pziputil->ls(pobject, l);

            }
            else
            {

               l = ::error_failed;

            }

         }

         return l;

      }


      bool system_dir::has_subdir(::generic * pobject, const ::file::path & pathFolder)
      {

         ::file::listing ls(::get_context_application(pobject));

         ls.ls_dir(pathFolder);

         return ls.get_count() > 0;

      }


      bool system_dir::is_cached(bool & bIs, const ::file::path & path, ::generic * pobject)
      {

         bIs = false;

#ifdef WINDOWS_DESKTOP
#ifdef WINDOWS_DESKTOP
         if(::str::ends_ci(path, ".lnk"))
         {
#endif

            ::file::path pathTarget;

            if(Context.file().resolve_link(get_context_application(), pathTarget, path))
            {

               bIs = is(pathTarget, pobject);

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

            bHasSubFolder = m_pziputil->has_sub_folder(pobject, path);

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


      bool system_dir::is(const ::file::path & pathParam,::generic * pobject)
      {

         ::file::path path;

         if (pathParam.begins_ci("appmatter://"))
         {

            path = m_pathLocalAppMatterFolder / path.Mid(12);

         }
         else
         {

            path = pathParam;

         }

         bool bIs;

         if (!(pathParam & ::file::flag_bypass_cache) && is_cached(bIs, path, pobject))
         {

            return bIs;

         }

         return is_impl(path, pobject);

      }


      bool system_dir::is_impl(const ::file::path & path, ::generic * pobject)
      {

         if (path.ends_ci("://") || path.ends_ci(":/") || path.ends_ci(":"))
         {

            return true;

         }

         if (::str::begins_ci(path, "http://") || ::str::begins_ci(path, "https://"))
         {

            property_set set;

            if (path & ::file::flag_bypass_cache)
            {

               set["nocache"] = true;

            }

            return Sess(pobject).http().exists(path, set);

         }

         if (::thread_is_set(id_thread_zip_is_dir) && (::str::ends_ci(path, ".zip")))
         {

            //m_isdirmap.set(path, true, 0);

            return true;

         }

         if (::thread_is_set(id_thread_zip_is_dir) && (::str::find_file_extension("zip:", path) >= 0))
         {

            bool bHasSubFolder;

            bHasSubFolder = m_pziputil->has_sub_folder(pobject, path);

//            m_isdirmap.set(path, bHasSubFolder, get_last_error());

            return bHasSubFolder;

         }

         return false;

      }


      bool system_dir::name_is(const ::file::path & strPath,::generic * pobject)
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
//            u32 dwLastError;
            //if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
            //   return bHasSubFolder;
            bHasSubFolder = m_pziputil->has_sub_folder(pobject, strPath);
            //m_isdirmap.set(strPath, bHasSubFolder, get_last_error());
            return bHasSubFolder;
         }
         return false;


      }


//      system_dir::is_dir_map::is_dir_map()
//      {
//
//      }
//
//
//      bool system_dir::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, u32 & dwLastError)
//      {
//
//         return lookup(path, bIsDir, dwLastError, (i32) path.length());
//
//      }
//
//
//      bool system_dir::is_dir_map::lookup(const ::file::path & path, bool &bIsDir, u32 &dwLastError, i32 iLastChar)
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
//      bool system_dir::is_dir_map::lookup_dynamic(const ::file::path & path, bool &bIsDir, u32 & dwLastError, i32 iLastChar)
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
//         if (::get_fast_tick_count() > pdir->m_tickLastCheck + m_tickTimeout)
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
//      bool system_dir::is_dir_map::lookup_small(const ::file::path & path,bool &bIsDir,u32 &dwLastError, i32 iLastChar)
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
//         if (::get_fast_tick_count() > pdir->m_tickLastCheck + m_tickTimeout)
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
//      void system_dir::is_dir_map::set(const ::file::path & path,bool bIsDir,u32 dwLastError)
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
//                  pfind->m_tickLastCheck = ::get_fast_tick_count();
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
//            pdir->m_tickLastCheck = ::get_fast_tick_count();
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

      ::file::path system_dir::time()
      {
         __throw(interface_only_exception("this is an interface"));
      }

      ::file::path system_dir::stage()
      {
         __throw(interface_only_exception("this is an interface"));
      }


      ::file::path system_dir::stageapp()
      {

         __throw(interface_only_exception("this is an interface"));

      }


      ::file::path system_dir::netseed()
      {

         __throw(interface_only_exception("this is an interface"));

      }


      ::file::path system_dir::install()
      {

         sync_lock sl(mutex());

         return m_pathInstall;

      }


      ::file::path system_dir::config()
      {

         sync_lock sl(mutex());

         return m_pathCa2Config;

      }


      ::file::path system_dir::home()
      {

         sync_lock sl(mutex());

         return m_pathHome;

      }

      //::file::path system_dir::userfolder(::generic * pobject)
      //{

      //   UNREFERENCED_PARAMETER(pobject);

      //   sync_lock sl(mutex());

      //   return m_pathUser;

      //}


      ::file::path system_dir::module()
      {

         sync_lock sl(mutex());

         return m_pathModule;

      }


      ::file::path system_dir::ca2module()
      {

         sync_lock sl(mutex());

         return m_pathCa2Module;

      }


      ::file::path system_dir::time_square(::generic * pobject)
      {

         UNREFERENCED_PARAMETER(pobject);

         return time() / "time";

      }


      ::file::path system_dir::time_log(const string & pszId)
      {

         UNREFERENCED_PARAMETER(pszId);
         __throw(interface_only_exception("this is an interface"));

      }


      bool system_dir::mk(const ::file::path & path,::generic * pobject)
      {

         UNREFERENCED_PARAMETER(path);
         __throw(interface_only_exception("this is an interface"));

      }


      bool system_dir::rm(::generic * pobject,const ::file::path & path,bool bRecursive)
      {

         UNREFERENCED_PARAMETER(path);
         UNREFERENCED_PARAMETER(bRecursive);
         __throw(interface_only_exception("this is an interface"));

      }


      string system_dir::locale_schema_matter(::generic * pobject, const string & strLocale, const string & strSchema, const ::file::path & pathRoot, const ::file::path & pathDomain)
      {

         string strHint = pathRoot / "appmatter" / pathDomain / ::get_context_application(pobject)->get_locale_schema_dir(strLocale, strSchema);

         return strHint;

      }


      string system_dir::matter(const ::file::path & path, bool bDir, const ::file::path & pathRoot, const ::file::path & pathDomain)
      {

         string strMatter = ::file::path("appmatter://") / pathRoot / "appmatter" / pathDomain / "_std/_std" / path;

         return strMatter;

      }



      void system_dir::matter_ls(::generic * pobject, const ::file::path & path, ::file::patha & stra)
      {

         sync_lock sl(System.m_spmutexMatter);

         string strDir = matter(pobject, path, true);

         if (m_bMatterFromHttpCache)
         {

            string strMatter = strDir;

            if(::str::begins_eat_ci(strMatter, "appmatter://"))
            {

               strMatter = "/matter/" + strMatter;

            }
            else
            {

               strsize iFind1 = strMatter.find_ci("/matter/");

               strsize iFind2 = strMatter.find_ci("\\matter\\");

               strsize iFind = min_non_neg(iFind1, iFind2);

               if(iFind > 0)
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

               strLs = Sess(pobject).http().get(strUrl, set);

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

            strDir = System.get_matter_cache_path(strDir);

            stra = listing(::get_context_application(pobject)).ls(strDir);

         }

      }


      void system_dir::matter_ls_file(::generic * pobject,const ::file::path & str,::file::patha & stra)
      {

         ::file::path strDir = matter(pobject, str, true);

         if(m_bMatterFromHttpCache)
         {

            property_set set;

            set["raw_http"] = true;

            string strFile = Context.dir().cache() / strDir/ "list_dir.list_dir";

            strsize iFind = strFile.find(DIR_SEPARATOR);

            if (iFind > 0)
            {

               strFile.replace(":", "_", iFind + 1);

            }

            strFile.replace("////", "//");
            strFile.replace("\\\\","\\", 1);

            string strLs;

            if(Context.file().exists(strFile))
            {

               strLs = Context.file().as_string(strFile);

            }


            ::file::patha straLs;

            string_array straSep;

            straSep.add("\r");
            straSep.add("\n");
            straSep.add("\r\n");

            straLs.add_smallest_tokens(strLs,straSep,false);

            for(index i = 0; i < straLs.get_count(); i++)
            {

               if(!::str::ends(straLs[i],"/"))
               {
                  ::file::path strPath  = strDir / straLs[i];
                  stra.add(strPath);
               }

            }

         }
         else
         {

            stra = listing(::get_context_application(pobject)).ls(strDir);

         }

      }


      string system_dir::matter_from_locator(::generic * pobject, const ::file::patha & patha, const string_array & straMatterLocator, bool bDir)
      {

         if (patha.is_empty())
         {

            return "";

         }

         if (straMatterLocator.is_empty())
         {

            return "";

         }

         ::acme::application * papp = ::get_context_application(pobject);

         ::file::path pathLs0 = straMatterLocator.first();

         pathLs0 /= papp->get_locale_schema_dir();

         ::file::path pathCache = m_pathLocalAppMatterFolder / pathLs0 / patha[0] + ".map_question";

         TRACE("cache map path: %s", pathCache.c_str());

         string strPath = Context.file().as_string(pathCache);

         if (::str::begins_eat_ci(strPath, "itdoesntexist."))
         {

            tick t = ansi_to_i64(strPath);

            auto elapsed = t.elapsed();

            if (elapsed < 5 * 60 * 1000)
            {

               if (false)
               {

                  return "itdoesntexist";

               }

            }

            strPath.Empty();

         }

         if (!(patha[0] & ::file::flag_bypass_cache) && strPath.has_char())
         {

            string strFinal(strPath);

            if(strFinal.begins_ci("appmatter://"))
            {

               strFinal = m_pathLocalAppMatterFolder / strFinal.Mid(12);

            }

            if (::is_file_or_dir_dup(strFinal, nullptr))
            {

               TRACE("!!Cache Hit: %s", strFinal.c_str());

               return strPath;

            }

            TRACE("...Cache Miss: %s", strFinal.c_str());

         }

         string strLocale;

         string strSchema;

         string_array straLs;

         papp->locale_schema_matter(straLs, straMatterLocator, strLocale, strSchema);

         ::acme::str_context * pcontext = Sess(pobject).str_context();

         if (m_bMatterFromHttpCache)
         {

            string_array stra;

            string strMatter;

            for (auto & strLs : straLs)
            {

               for (auto & path : patha)
               {

                  strMatter = strLs / path;

                  strPath = ::dir::ca2roaming() / "appmatter" / strMatter;

//                  if (::is_file_or_dir_dup(strPath, nullptr))
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

            if (patha[0] & ::file::flag_required)
            {

               set["required"] = true;

            }

            if (patha[0] & ::file::flag_bypass_cache)
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

            strMatter = Sess(pobject).http().get(strUrl, set);

            TRACE("");
            TRACE("");
            TRACE("matter = ::: %s", strMatter.c_str());
            TRACE("");
            TRACE("");

            strMatter.trim();

            if(strMatter.has_char() && ::str::begins_eat_ci(strMatter, "https://server.ca2.cc/matter/"))
            {

               strPath = "appmatter://" + strMatter;

               if(bDir)
               {

                  ::dir::mk(m_pathLocalAppMatterFolder / strMatter);

               }

               goto ret;

            }

         }
         else
         {

            string strMatter;

            for (auto & strLs : straLs)
            {

               for (auto & path : patha)
               {

                  strMatter = strLs / path;

                  strPath = m_pathLocalAppMatterFolder / strMatter;

                  if (::is_file_or_dir_dup(strPath, nullptr))
                  {

                     goto ret;

                  }

               }

            }

         }

         strPath = "itdoesntexist." + __str(tick::now().m_i);

ret:

         if (m_bMatterFromHttpCache)
         {

            Context.file().put_contents(pathCache, strPath);

         }

         return strPath;

      }


      string system_dir::matter_from_locator(::generic * pobject, ::file::path path, const string_array & straMatterLocator, bool bDir)
      {

         ::file::patha patha;

         ::str::begins_eat_ci(path, "matter://");

         patha.add(path);

         return matter_from_locator(pobject, patha, straMatterLocator, bDir);

      }


      string system_dir::matter(::generic * pobject, const ::file::patha & patha, bool bDir)
      {

         ::acme::application * papp = ::get_context_application(pobject);

         string_array straMatterLocator;
         {

            sync_lock sl(mutex());

            straMatterLocator = papp->m_straMatterLocator;

         }

         return matter_from_locator(pobject, patha, straMatterLocator, bDir);

      }


      string system_dir::matter(::generic * pobject, ::file::path path, bool bDir)
      {

         ::acme::application * papp = ::get_context_application(pobject);

         string_array straMatterLocator;

         {

            sync_lock sl(mutex());

            straMatterLocator = papp->m_straMatterLocator;

         }

         return matter_from_locator(pobject, path, straMatterLocator, bDir);

      }


      ::file::path system_dir::appmatter(string strApp, ::file::path pathRel)
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

               strRepo = "app-acme";

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
                          ::file::path(strRepo) / "appmatter" / strApp / "_std" / "_std" / pathRel);

         return point;

      }


      ::estatus system_dir::initialize(::generic * pobjectContext)
      {

         auto estatus = ::generic::initialize(pobjectContext);

         if (!estatus)
         {
            
            return estatus;

         }

#ifdef __APPLE__
         if(::dir::is(System.side_get_matter_path("app/_matter/main")))
         {

            m_pathLocalAppMatterFolder = System.side_get_matter_path("");

         }
         else
#endif
         {

            m_pathLocalAppMatterFolder = System.local_get_matter_cache_path();

         }

         m_pfilewatcher.create();

         ::dir::mk(::dir::bookmark());

         if(!update_module_path())
         {

            return false;

         }

         if (m_pziputil == nullptr)
         {

            m_pziputil = new ::zip::util();

         }

         string strRelative = ::dir::app_relative();

         m_pathDefaultAppData = ::dir::home() / "application";

         string strAppFolder;

         if (System.m_plibrary)
         {

            if (System.m_plibrary->get_ca2_library())
            {

               strAppFolder = System.m_plibrary->get_ca2_library()->m_strFolder;

               if (strAppFolder.is_empty())
               {

                  strAppFolder = System.m_plibrary->get_ca2_library()->m_strName;

               }

            }

         }

         if (strAppFolder.is_empty())
         {

            strAppFolder = _002Underscore(System.m_strAppId);

         }

         m_pathDefaultAppData /= strAppFolder;

         //m_strCa2DefaultAppData /= System.get_system_platform();

         //m_strCa2DefaultAppData /= System.get_system_configuration();

         ::file::path pathAppData = System.m_varTopicQuery["app_folder"];

         if (pathAppData.has_char())
         {

            m_pathAppData = pathAppData;

         }
         else
         {

            m_pathAppData = m_pathDefaultAppData;
         }


         return true;

      }


      ::file::path system_dir::commonappdata(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration)
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


      ::file::path system_dir::commonappdata_locale_schema(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
      {

         sync_lock sl(mutex());

         string strLocale(pszLocale);

         if (strLocale.is_empty())
         {

            strLocale = Session.m_strLocale;

         }

         string strSchema(pszSchema);

         if (strSchema.is_empty())
         {

            strSchema = Session.m_strSchema;

         }

         return commonappdata(pszAppId, pszBuild, pszPlatform, pszConfiguration) / strLocale / strSchema;

      }


      ::file::path system_dir::trash_that_is_not_trash(const ::file::path & psz)
      {

         UNREFERENCED_PARAMETER(psz);

         __throw(interface_only_exception("this is an interface"));

      }


      ::file::path system_dir::appdata()
      {

         //__throw(interface_only_exception("this is an interface"));

         return m_pathAppData;

      }

      ::file::path system_dir::cache()
      {

         return ::dir::ca2roaming() / "cache";

      }


      ::file::path system_dir::commonappdata_root()
      {

         return "/var/lib";

      }


      ::file::path system_dir::commonappdata()
      {

         return element_commonappdata(install());

      }

      ::file::path system_dir::element_commonappdata(const string & strElement)
      {

         string strRelative;

         strRelative = strElement;

         index iFind = strRelative.find(':');

         if(iFind >= 0)
         {

            strsize iFind1 = strRelative.reverse_find("\\",iFind);

            strsize iFind2 = strRelative.reverse_find("/",iFind);

            strsize iStart = MAX(iFind1 + 1,iFind2 + 1);

            strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);

         }

         return commonappdata_root()/ strRelative;

      }


      //::file::path system_dir::usersystemappdata(::generic * pobject, const string & pcszPrefix)

      //{
      //   UNREFERENCED_PARAMETER(pobject);
      //   UNREFERENCED_PARAMETER(pcszPrefix);

      //   __throw(interface_only_exception("this is an interface"));
      //}


      //::file::path system_dir::userappdata(::generic * pobject)
      //{

      //   UNREFERENCED_PARAMETER(pobject);

      //   __throw(interface_only_exception("this is an interface"));

      //}


      //::file::path system_dir::userdata(::generic * pobject)
      //{

      //   UNREFERENCED_PARAMETER(pobject);

      //   __throw(interface_only_exception("this is an interface"));

      //}


      //::file::path system_dir::default_os_user_path_prefix(::generic * pobject)
      //{

      //   UNREFERENCED_PARAMETER(pobject);

      //   __throw(interface_only_exception("this is an interface"));

      //}


      //::file::path system_dir::default_userappdata(::generic * pobject, const string & pcszPrefix, const string & lpcszLogin)

      //{
      //   UNREFERENCED_PARAMETER(pobject);
      //   UNREFERENCED_PARAMETER(pcszPrefix);

      //   UNREFERENCED_PARAMETER(pcszLogin);

      //   __throw(interface_only_exception("this is an interface"));
      //}

      //::file::path system_dir::default_userdata(::generic * pobject, const string & pcszPrefix, const string & lpcszLogin)

      //{
      //   UNREFERENCED_PARAMETER(pobject);
      //   UNREFERENCED_PARAMETER(pcszPrefix);

      //   UNREFERENCED_PARAMETER(pcszLogin);

      //   __throw(interface_only_exception("this is an interface"));
      //}

      //::file::path system_dir::default_userfolder(::generic * pobject, const string & pcszPrefix, const string & lpcszLogin)

      //{
      //   UNREFERENCED_PARAMETER(pobject);
      //   UNREFERENCED_PARAMETER(pcszPrefix);

      //   UNREFERENCED_PARAMETER(pcszLogin);

      //   __throw(interface_only_exception("this is an interface"));
      //}

      ::file::path system_dir::userquicklaunch(::generic * pobjectContext)
      {
         UNREFERENCED_PARAMETER(pobjectContext);
         __throw(interface_only_exception("this is an interface"));
      }

      ::file::path system_dir::userprograms(::generic * pobjectContext)
      {
         UNREFERENCED_PARAMETER(pobjectContext);
         __throw(interface_only_exception("this is an interface"));
      }

      ::file::path system_dir::commonprograms()
      {
         __throw(interface_only_exception("this is an interface"));
      }

      bool system_dir::is_inside_time(const ::file::path & pszPath,::generic * pobject)
      {
         UNREFERENCED_PARAMETER(pszPath);
         __throw(interface_only_exception("this is an interface"));
      }

      bool system_dir::is_inside(const ::file::path & pszDir,const ::file::path & pszPath,::generic * pobject)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         __throw(interface_only_exception("this is an interface"));
      }


      ::file::watcher & system_dir::watcher()
      {

         return *m_pfilewatcher;

      }


      ::file::path system_dir::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode, ::generic * pobject)
      {

         ::acme::application * papp = ::get_context_application(pobject);

         ::file::patha stra;

         stra.add_tokens(pszEnv, ":", false);

         string strCandidate;

         for(i32 i = 0; i < stra.get_count(); i++)
         {

            strCandidate = stra[i] / pszTopic;

            if(Sess(papp).file().exists(strCandidate))
            {
               return strCandidate;
            }

         }

         return "";

      }

//      ::file::path system_dir::get_api_cc()
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


      bool system_dir::update_module_path()
      {

         if(!Context.file().update_module_path())
         {

            return false;

         }

         m_pathModule = Context.file().module().folder();

         m_pathCa2Module = Context.file().ca2module().folder();

         return true;

      }


      ::file::path system_dir::bookmark()
      {

         return ::dir::bookmark();

      }


      //::file::path system_dir::home()
      //{

      //   return ::dir::home();

      //}

      ::file::path system_dir::desktop()
      {

         return home() / "Desktop";

      }


      ::file::path system_dir::document()
      {

         return home() / "Document";

      }



      ::file::path system_dir::download()
      {

         return home() / "Downloads";

      }


      ::file::path system_dir::music()
      {

         return home() / "Music";

      }


      ::file::path system_dir::video()
      {

         return home() / "Video";

      }


      ::file::path system_dir::image()
      {

         return home() / "Image";

      }


      ::file::path system_dir::dropbox(::generic * pobject)
      {

         ::file::path pathJson = App(pobject).file().dropbox_info_json();

         string strJson = Context.file().as_string(pathJson);

         ::property_set set;

         set.parse_json(strJson);

         return set["personal"]["path"];

      }

      
      ::file::path system_dir::onedrive(::generic * pobject)
      {
         ::file::path pathIni = App(pobject).file().onedrive_cid_ini();
         
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

      ::file::path system_dir::standalone()
      {


         return ::dir::roaming() / System.m_strStandalone;

      }



} // namespace file




