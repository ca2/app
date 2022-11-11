#include "framework.h"


namespace android
{


   namespace axis
   {


      dir::dir(::particle * pparticle) :
         ::object(pparticle),
         ::file::system_dir(pparticle),
         ::file::dir::axis::system(pparticle),
         ::android::dir(pparticle),
         ::file_watcher::file_watcher(pparticle)
      {


      }

      //path::path(::particle * pparticle) :
      //   ::object(pparticle)
      //{
      //}


      //inline bool myspace(char ch)
      //{
      //   return ch == ' ' ||
      //          ch == '\t' ||
      //          ch == '\r' ||
      //          ch == '\n';
      //}



      //string dir::path(const ::string & pszFolder, strsize iLenFolder, const ::string & pszRelative, strsize iLenRelative, const ::string & psz2, strsize iLen2, bool bUrl)
      //{

      //   bool bEmptyRelative = iLenRelative == 0 || pszRelative == nullptr || *pszRelative == '\0';
      //   bool bEmpty2 = iLen2 == 0 || psz2 == nullptr || *psz2 == '\0';

      //   if(bEmptyRelative && bEmpty2)
      //      return pszFolder;

      //   string strPath;
      //   char * lpsz;

      //   if(bEmptyRelative)
      //   {
      //      pszRelative = psz2;
      //      iLenRelative = iLen2;
      //   }

      //   while((pszFolder[iLenFolder - 1] == '\\' || pszFolder[iLenFolder - 1] == '/') && iLenFolder > 0)
      //   {
      //      if(bUrl)
      //      {
      //         if((iLenFolder - 2) >= 0 && (pszFolder[iLenFolder - 2] == '\\' || pszFolder[iLenFolder - 2] == '/' || pszFolder[iLenFolder - 2] == ':'))
      //         {
      //            if(pszFolder[iLenFolder - 2] == ':')
      //            {
      //               break;
      //            }
      //            else
      //            {
      //               if((iLenFolder - 3) >= 0 && (pszFolder[iLenFolder - 3] == ':'))
      //               {
      //                  iLenFolder--;
      //                  break;
      //               }
      //            }
      //         }
      //         else
      //         {
      //            iLenFolder--;
      //         }
      //      }
      //      else
      //      {
      //         iLenFolder--;
      //      }
      //   }

      //   while(*pszRelative != '\0' && (*pszRelative == '\\' || *pszRelative == '/') && iLenRelative > 0)
      //   {
      //      pszRelative++;
      //      iLenRelative--;
      //   }

      //   if(bEmptyRelative || bEmpty2)
      //   {
      //      lpsz = strPath.get_string_buffer(iLenFolder + 1 + iLenRelative);
      //      strncpy(lpsz, pszFolder, iLenFolder);
      //      if(strnicmp(&lpsz[iLenFolder - 5], ".zip:", 5) == 0)
      //      {
      //         iLenFolder--;
      //      }
      //      else
      //      {
      //         lpsz[iLenFolder] = '/';
      //      }
      //      strncpy(&lpsz[iLenFolder + 1], pszRelative, iLenRelative);
      //      lpsz[iLenFolder + 1 + iLenRelative] = '\0';
      //      {
      //         if(bUrl)
      //         {
      //            while(*lpsz++ != '\0')
      //               if(*lpsz == '\\') *lpsz = '/';
      //         }
      //         else
      //         {
      //            while(*lpsz++ != '\0')
      //               if(*lpsz == '/') *lpsz = '\\';
      //         }
      //      }
      //      strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative);
      //      return strPath;
      //   }

      //   while((pszRelative[iLenRelative - 1] == '\\' || pszRelative[iLenRelative - 1] == '/') && iLenRelative > 0)
      //   {
      //      iLenRelative--;
      //   }

      //   while(*psz2 != '\0' && (*psz2 == '\\' || *psz2 == '/') && iLen2 > 0)
      //   {
      //      psz2++;
      //      iLen2--;
      //   }

      //   lpsz = strPath.get_string_buffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);
      //   strncpy(lpsz, pszFolder, iLenFolder);
      //   lpsz[iLenFolder] = '/';
      //   strncpy(&lpsz[iLenFolder + 1], pszRelative, iLenRelative);
      //   lpsz[iLenFolder + 1 + iLenRelative] = '/';
      //   strncpy(&lpsz[iLenFolder + 1 + iLenRelative + 1], psz2, iLen2);
      //   lpsz[iLenFolder + 1 + iLenRelative + 1 + iLen2] = '\0';
      //   {
      //      if(bUrl)
      //      {
      //         while(*lpsz++ != '\0')
      //            if(*lpsz == '\\') *lpsz = '/';
      //      }
      //      else
      //      {
      //         while(*lpsz++ != '\0')
      //            if(*lpsz == '/') *lpsz = '\\';
      //      }
      //   }
      //   strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);
      //   return strPath;
      //}



      //string dir::relpath(const ::string & lpcszSource, const ::string & lpcszRelative, const ::string & psz2)
      //{
      //   const char * pszRequest;
      //   if(::url::is_url(lpcszSource, &pszRequest))
      //   {
      //      if(string_begins(lpcszRelative, "/"))
      //      {
      //         return path((const ::string &) string(lpcszSource, pszRequest - lpcszSource), lpcszRelative);
      //      }
      //      else if(*pszRequest == '\0' || string_ends(lpcszSource, "/"))
      //      {
      //         return path(lpcszSource, lpcszRelative, psz2);
      //      }
      //      else
      //      {
      //         return path((const ::string &) name(lpcszSource), lpcszRelative, psz2);
      //      }
      //   }
      //   else
      //   {
      //      if(string_ends(lpcszSource, "\\") || string_ends(lpcszSource, "/"))
      //      {
      //         return path(lpcszSource, lpcszRelative, psz2);
      //      }
      //      else
      //      {
      //         return path((const ::string &) name(lpcszSource), lpcszRelative, psz2);
      //      }
      //   }
      //}

      //bool path::is_equal(const ::string & lpszPath1, const ::string & lpszPath2)
      //{
      //   // use case insensitive compare as a starter
      //   if (lstrcmpi(lpszPath1, lpszPath2) != 0)
      //   return false;

      //   // on non-DBCS systems, we are done
      //   if (!GetSystemMetrics(SM_DBCSENABLED))
      //   return true;

      //   // on DBCS systems, the file name may not actually be the same
      //   // in particular, the file system is case sensitive with respect to
      //   // "full width" roman characters.
      //   // (ie. fullwidth-R is different from fullwidth-r).
      //   i32 nLen = lstrlen(lpszPath1);
      //   if (nLen != lstrlen(lpszPath2))
      //   return false;
      //   ASSERT(nLen < _MAX_PATH);

      //   // need to get both CT_CTYPE1 and CT_CTYPE3 for each filename
      //   LCID lcid = GetThreadLocale();
      //   ::u16 aCharType11[_MAX_PATH];
      //   VERIFY(GetStringTypeEx(lcid, CT_CTYPE1, lpszPath1, -1, aCharType11));
      //   ::u16 aCharType13[_MAX_PATH];
      //   VERIFY(GetStringTypeEx(lcid, CT_CTYPE3, lpszPath1, -1, aCharType13));
      //   ::u16 aCharType21[_MAX_PATH];
      //   VERIFY(GetStringTypeEx(lcid, CT_CTYPE1, lpszPath2, -1, aCharType21));
      //   #ifdef _DEBUG
      //   ::u16 aCharType23[_MAX_PATH];
      //   VERIFY(GetStringTypeEx(lcid, CT_CTYPE3, lpszPath2, -1, aCharType23));
      //   #endif

      //   // for every C3_FULLWIDTH character, make sure it has same C1 value
      //   i32 i = 0;
      //   for (const ::string & lpsz = lpszPath1; *lpsz != 0; lpsz = _tcsinc(lpsz))
      //   {
      //   // check for C3_FULLWIDTH characters only
      //   if (aCharType13[i] & C3_FULLWIDTH)
      //   {
      //   #ifdef _DEBUG
      //   ASSERT(aCharType23[i] & C3_FULLWIDTH); // should always match!
      //   #endif

      //   // if CT_CTYPE1 is different then file system considers these
      //   // file names different.
      //   if (aCharType11[i] != aCharType21[i])
      //   return false;
      //   }
      //   ++i; // look at next character type
      //   }
      //   return true; // otherwise file name is truly the same
      //}

      //void dir::root_ones(string_array & straPath, string_array & straTitle, ::aura::application * papp)
      //{
      //   ::u32 dwSize = ::GetLogicalDriveStrings(0, nullptr);
      //   char * lpszAlloc = (char *) malloc(dwSize + 1);
      //   char * lpsz = lpszAlloc;
      //   dwSize = ::GetLogicalDriveStrings(dwSize + 1, lpsz);

      //   string str;
      //   while(*lpsz)
      //   {
      //      str.Empty();
      //      while(*lpsz)
      //      {
      //         str += *lpsz;
      //         lpsz++;
      //      }
      //      straPath.add(str);
      //      str.trim(":/\\");
      //      straTitle.add("Drive " + str);
      //      lpsz++;
      //   }

      //   free(lpszAlloc);
      //}



      ::file::listing & dir::ls(::particle * pparticle, ::file::listing & listing)
      {


         if (::file::dir::axis::system::ls(papp, listing))
         {

            return listing;

         }

         return ::android::dir::ls(papp, listing);

      }


      //   bool dir::rls(::particle * pparticle, const ::string & lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, enum_extract eextract)
      //   {
      //
      //      if(::file::dir::axis::system::rls(papp,lpcsz,pstraPath,pstraTitle,pstraRelative,eextract))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::rls(papp,lpcsz,pstraPath,pstraTitle,pstraRelative,eextract);
      //
      //   }
      //
      //
      //   bool dir::rls_pattern(::particle * pparticle, const ::string & lpcsz, const ::string & lpszPattern, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative, bool_array * pbaIsDir, i64_array * piaSize, enum_extract eextract)
      //   {
      //
      //      if(::file::dir::axis::system::rls_pattern(papp,lpcsz,lpszPattern,pstraPath,pstraTitle,pstraRelative,pbaIsDir,piaSize,eextract))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::rls_pattern(papp,lpcsz,lpszPattern,pstraPath,pstraTitle,pstraRelative,pbaIsDir,piaSize,eextract);
      //
      //   }


      //   bool dir::rls_dir(::particle * pparticle, const ::string & lpcsz, string_array * pstraPath, string_array * pstraTitle, string_array * pstraRelative)
      //   {
      //
      //      if(::file::dir::axis::system::rls_dir(papp,lpcsz,pstraPath,pstraTitle,pstraRelative))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::rls_dir(papp,lpcsz,pstraPath,pstraTitle,pstraRelative);
      //
      //   }
      //
      //
      //   bool dir::ls_dir(::particle * pparticle, const ::string & lpcsz, string_array * pstraPath, string_array * pstraTitle)
      //   {
      //
      //      if(::file::dir::axis::system::ls_dir(papp,lpcsz,pstraPath,pstraTitle))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::ls_dir(papp,lpcsz,pstraPath,pstraTitle);
      //
      //   }
      //
      //
      //   bool dir::ls_file(::particle * pparticle, const ::string & lpcsz, string_array * pstraPath, string_array * pstraTitle)
      //   {
      //
      //      if(::file::dir::axis::system::ls_file(papp,lpcsz,pstraPath,pstraTitle))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::ls_file(papp,lpcsz,pstraPath,pstraTitle);
      //
      //   }
      //
      //
      //   bool dir::ls(::particle * pparticle, const ::string & lpcsz, string_array * pstraPath, string_array * pstraTitle, bool_array * pbaIsDir, i64_array * piaSize)
      //   {
      //
      //      if(::file::dir::axis::system::ls(papp,lpcsz,pstraPath,pstraTitle,pbaIsDir,piaSize))
      //      {
      //
      //         return true;
      //
      //      }
      //
      //      return ::linux::dir::ls(papp,lpcsz,pstraPath,pstraTitle,pbaIsDir,piaSize);
      //
      //   }


      bool          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(const ::file::path & lpcszPath, ::aura::application * papp)
      {

         if (::androidpacmedir->is(lpcszPath, papp))
            return true;

         if (::file::dir::axis::system::is(lpcszPath, papp))
            return true;

         return false;

      }

      //   bool          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(const ::string & strPath, ::aura::application * papp)
      //   {
      //
      //      if(::linuxpacmedir->is(strPath,papp))
      //         return true;
      //
      //      if(::file::dir::axis::system::is(strPath,papp))
      //         return true;
      //
      //      return false;
      //
      //   }

      bool dir::name_is(const ::file::path & str, ::aura::application * papp)
      {
         //output_debug_string(str);
         strsize iLast = str.get_length() - 1;
         while (iLast >= 0)
         {
            if (str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               break;
            iLast--;
         }
         while (iLast >= 0)
         {
            if (str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
               break;
            iLast--;
         }
         if (iLast >= 0)
         {
            while (iLast >= 0)
            {
               if (str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
               {
                  iLast++;
                  break;
               }
               iLast--;
            }
         }
         else
         {
            return true; // assume empty string is root_ones directory
         }

         if (thread_zip_is_dir && iLast >= 3 && !ansi_count_compare_ci(&((const ::string &)str)[iLast - 3], ".zip", 4))
         {

            return true;

         }

         strsize iFind = ::str().find_ci(".zip:", str);

         if (thread_set(e_task_flag_compress_is_dir) && iFind >= 0 && iFind < iLast)
         {

            bool bHasSubFolder = m_pziputil->has_sub_folder(papp, str);

            return bHasSubFolder;

         }

         bool bIsDir =          auto psystem = acmesystem();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->is(str.Left(iLast));

         return bIsDir;

      }


      bool dir::initialize()
      {

         if (!::android::dir::initialize())
         {

            return false;

         }

         return true;

      }


   } // namespace axis


} // namespace android



