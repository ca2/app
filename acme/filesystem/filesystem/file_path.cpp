// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme_file.h"
//#include "acme/networking/as_string.h"
//#include "acme/primitive/collection/numeric_array.h"


void copy_character_per_character(char * pszTarget, const char * pszSource)
{

   while(*pszSource)
   {

      *pszTarget = *pszSource;

      pszTarget++;

      pszSource++;

   }

}


::string file_path_name(const ::scoped_string & scopedstrPath)
{

   auto p = scopedstrPath.rear_find_first_character_in("\\/");

   if(::is_null(p))
   {

      return scopedstrPath;

   }

   return {p + 1, scopedstrPath.end() };

}


::string file_path_final_extension(const ::scoped_string & scopedstrPath)
{

   auto scopedstrName = file_path_name(scopedstrPath);

   auto last_dot = scopedstrName.rear_find('.');

   if (!last_dot)
   {

      return {};

   }

   return {last_dot + 1, scopedstrName.end()};

}


::string file_path_all_extensions(const ::scoped_string & scopedstrPath)
{

   auto scopedstrName = file_path_name(scopedstrPath);

   auto name_first_dot = scopedstrName.find('.');

   if (!name_first_dot)
   {

      return {};

   }

   return {name_first_dot + 1, scopedstrName.end()};

}


::string url_dir_name_for_relative(const ::file::path & path)
{

   ASSERT(!path.ends("/"));
   ASSERT(!path.ends("\\"));

   auto p = path.rear_find('/');

   if (::is_null(p))
   {

      return "/";

   }

   return { path.begin(), p };

}


#ifdef WINDOWS

#define CHECK_NATIVE_FILE_SEP(ch) \
   \
   if (bOnlyNativeFileSep && (ch) == '/') \
   { \
   \
      bOnlyNativeFileSep = false; \
   \
   }

#else

#define CHECK_NATIVE_FILE_SEP(ch) \
   \
   if (bOnlyNativeFileSep && (ch) == '/') \
   { \
   \
      bOnlyNativeFileSep = false; \
   \
   }

#endif


CLASS_DECL_ACME bool solve_relative_inplace(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize_array & iaSlash)
{

   bOnlyNativeFileSep = true;

   bool bCertainlySyntathicallyDir = false;

   bUrl = false;

   //bool bDup = false;

   strsize iLen = str.length();

   char * psz = str.get_buffer(iLen);

   //string strAbsolute(strParam);

   char * pend = psz + iLen;

   strsize iNewPosition;

   bool bDynIa = false;

   //strsize * iaSlash = *iaSlash;

   iaSlash.set_size(0);

   auto p = psz;

   if (iLen >= 2)
   {

      if (psz[0] == '\\' && psz[1] == '\\')
      {

#ifndef WINDOWS

         bOnlyNativeFileSep = false;

#endif

         iaSlash.add(1);

         p += 2;

      }

   }

   while (p < pend)
   {

      if (*p == '/' || *p == '\\')
      {

         CHECK_NATIVE_FILE_SEP(*p);

         iaSlash.add(p - psz);

         p++;

         if (p >= pend)
         {

            // the end of string has been reached

            if (p > psz + 2)
            {

               iaSlash.erase_at(iaSlash.get_upper_bound());

               p--; // erase trailing slash

               iLen--;

            }

            bCertainlySyntathicallyDir = true;

            goto ret;

         }
         else if (*p == '.')
         {

            p++;

            if (p >= pend)
            {

               // the end of string has been reached

               if (iaSlash.size() >= 2)
               {

                  p -= 2; // erase the dot and and trailing slash

               }
               else
               {

                  p--;// erase the dot

               }

               bCertainlySyntathicallyDir = true;

               goto ret;

            }
            else if (*p == '.')
            {

               p++;

               if (p >= pend)
               {

                  // the end of string has been reached

                  p = psz + iaSlash[maximum(0, iaSlash.size() - 2)]; // go back to position of previous slash

                  iaSlash.set_size(maximum(1, iaSlash.size() - 2));

                  if (p > psz + 2)
                  {

                     p--;

                  }

                  bCertainlySyntathicallyDir = true;

                  goto ret;

               }
               else if (*p == '/' || *p == '\\')
               {

                  CHECK_NATIVE_FILE_SEP(*p);

//                  if (!bDup)
//                  {
//
//                     psz = str.get_buffer();
//
//                     bDup = true;
//
//                  }

                  auto iSlashCount = iaSlash.size() - 2;

                  if (iSlashCount <= 0)
                  {

                     iNewPosition = iaSlash[0];

                     iaSlash.set_size(1);

                  }
                  else
                  {

                     iNewPosition = iaSlash[iSlashCount];

                     iaSlash.set_size(iSlashCount);

                  }

                  ansi_cpy(&psz[iNewPosition], p);

                  iLen -= p - &psz[iNewPosition];

                  p = &psz[iNewPosition];

               }
               else
               {

                  p += utf8_unicode_length(*p);

                  if (p >= pend)
                  {

                     p = pend - 1;

                     goto ret;

                  }

               }

            }
            else if (*p == '/' || *p == '\\')
            {

               CHECK_NATIVE_FILE_SEP(*p);

//               if (!bDup)
//               {
//
//                  psz = str.get_buffer();
//
//                  bDup = true;
//
//               }

               auto iSlashCount = iaSlash.size() - 1;

               if (iSlashCount <= 0)
               {

                  iNewPosition = iaSlash[0];

                  iaSlash.set_size(1);

               }
               else
               {

                  iNewPosition = iaSlash[iSlashCount];

                  iaSlash.set_size(iSlashCount);

               }

               auto pszNewPosition = psz + iNewPosition;

               auto pszPos = p;

               copy_character_per_character(pszNewPosition, pszPos);

               iLen -= p - pszNewPosition;

               p = pszNewPosition;

            }
            else
            {

               p += utf8_unicode_length(*p);

            }

         }
         else if (*p == '/' || *p == '\\')
         {

            CHECK_NATIVE_FILE_SEP(*p);

            iaSlash.add(p - psz);

            p++;

            if (p > psz + 3 && *(p - 3) == ':')
            {

               bUrl = true;

            }

            if (p >= pend)
            {

               // the end of string has been reached


               bCertainlySyntathicallyDir = true;

               goto ret;

            }

         }
         else
         {

            p += utf8_unicode_length(*p);

         }

      }
      else
      {

         p += utf8_unicode_length(*p);

      }

   }

ret:

   //if (bDup)
   //{

      //str.release_buffer(p - psz);

      auto iLenDebug = p - psz;

   str.release_buffer(iLen);

  // }
//   else if (p < pend)
//   {
//
//      str.truncate(p);
//
//   }

   return bCertainlySyntathicallyDir;

}



CLASS_DECL_ACME string solve_relative(const ::string & strParam, bool * pbUrl)
{

   string str(strParam);

   bool bUrl;

   bool bOnlyNativeFileSep;

   strsize_array iaSlash;

   solve_relative_inplace(str, bUrl, bOnlyNativeFileSep, iaSlash);

   if (pbUrl)
   {

      *pbUrl = bUrl;

   }

   return str;

}


CLASS_DECL_ACME string defer_solve_relative(const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstrAbsolute)
{
   string strRelative(scopedstrRelative);
   string strAbsolute(scopedstrAbsolute);
   if (strRelative.is_empty())
      return "";
   if (strAbsolute.is_empty())
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("http://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("https://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("ftp://"))
      return solve_relative(strRelative);
   if (strRelative.case_insensitive_begins("ext://"))
      return solve_relative(strRelative);
   if (strRelative.begins("/"))
      return solve_relative(strRelative);
   if (strRelative.begins("\\\\"))
      return solve_relative(strRelative);

   auto pFind = strRelative.find(":\\");

   if (::is_set(pFind))
   {
      auto p = strRelative.begin();
      for (; p < pFind; p++)
      {
         if (!ansi_char_isalpha(*p) && !ansi_char_isdigit(*p))
            break;
      }

      if (p == pFind) {

         return solve_relative(strRelative);

      }

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if (!strAbsolute.ends("/"))
   {

      strAbsolute += "/";

   }

   strRelative = strAbsolute + strRelative;

   return solve_relative(strRelative);

}




//CLASS_DECL_ACME bool read_resource_as_file(const ::scoped_string & scopedstrFile,HINSTANCE hinst,::u32 nID,LPCTSTR pcszType);

//const char * string_reverse_find_first_character_in(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrBegin, const ::scoped_string & scopedstrExcluding)
//{
//
//   while (psz >= pszBegin)
//   {
//
//      auto pszCheck = pszExcluding;
//
//      while(*pszCheck)
//      {
//
//         if (*psz == *pszCheck)
//         {
//
//            return psz;
//
//         }
//
//         pszCheck++;
//
//      }
//
//      psz--;
//
//   }
//
//   return nullptr;
//
//}


//const char * string_reverse_skip_any_character_in(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrBegin, const ::scoped_string & scopedstrIncluding)
//{
//
//   while (psz >= pszBegin)
//   {
//
//      auto pszCheck = pszIncluding;
//
//      bool bIncludesAny = false;
//
//      while(*pszCheck)
//      {
//
//         if (*psz == *pszCheck)
//         {
//
//            bIncludesAny = true;
//
//            break;
//
//         }
//
//         pszCheck++;
//
//      }
//
//      if(!bIncludesAny)
//      {
//
//         return psz;
//
//      }
//
//      psz--;
//
//   }
//
//   return nullptr;
//
//}


::string file_path_folder(const ::scoped_string & scopedstrPath)
{

   auto p = scopedstrPath.rear_find_first_character_in("\\/");

   if(::is_null(p))
   {

      return {};

   }

   auto range = scopedstrPath(0, p);

   auto pFolderLastCharacter = range.rear_skip_any_character_in("\\/");

   if(pFolderLastCharacter)
   {

      p = pFolderLastCharacter + 1;

   }

   return scopedstrPath(0, p);

}


//// 1. /folder/name
//// 2. /name
//const char * find_last_slash(const ::file::path & path1)
//{
//
//    const ::scoped_string & scopedstr = path1 + string_safe_length(path1) - 1;
//
//    auto pszSeparator = string_reverse_find_first_character_in(psz, path1, "\\/");
//
//// 1. /folder/
//// 2. /
//
//    if(!pszSeparator)
//    {
//
//        return "";
//
//    }
//
//    auto pszLastFolderCharacter = string_reverse_skip_any_character_in(pszSeparator, path1, "\\/");
//
//// 1. /folder
//// 2. nullptr
//
//    if(pszLastFolderCharacter)
//    {
//
//        pszSeparator = pszLastFolderCharacter + 1;
//
//    }
//
//// 1. /folder/
//// 2. /
//
//    return string(path1, pszSeparator - path1);
//
//}


//string file_path_name(const ::file::path & path)
//{
//
//   const ::scoped_string & scopedstrName2 = ansi_find_char_reverse(path, '\\');
//   
//   const ::scoped_string & scopedstrName1 = ansi_find_char_reverse(path, '/');
//
//   auto pszName = minimum_non_null(pszName1, pszName2);
//
//   if (pszName == nullptr)
//   {
//
//      return path;
//
//   }
//
//   return pszName + 1;
//
//}



//string file_path_name(const ::file::path & path)
//{
//   string str(path);
//   strsize iPos;
//   strsize iPos1 = str.rear_find('\\');
//   strsize iPos2 = str.rear_find('/');
//   if (iPos1 != -1 && iPos2 != -1)
//   {
//      if (iPos1 > iPos2)
//      {
//         iPos = iPos1 + 1;
//      }
//      else
//      {
//         iPos = iPos2 + 1;
//      }
//   }
//   else if (iPos1 != -1)
//   {
//      iPos = iPos1 + 1;
//   }
//   else if (iPos2 != -1)
//   {
//      iPos = iPos2 + 1;
//   }
//   else
//   {
//      iPos = 0;
//   }
//   return &path[iPos];
//}


::string file_path_title(const ::scoped_string & scopedstrPath)
{

   auto scopedstrName = file_path_name(scopedstrPath);

   auto end = scopedstrName.find('.');

   if (::is_null(end))
   {

      return scopedstrName;

   }

   return scopedstrName(0, end);

}


bool file_path_is_relative(const ::scoped_string & scopedstr)
{

   return !file_path_is_absolute(scopedstr);

   //string strPath(psz);
   //if (strPath.find(':') != -1 && strPath.find(':') < 10)
   //   return false;
   //if (strPath.find('/') == 0 || strPath.find('\\') == 0)
   //   return false;
   //return true;

}


bool file_path_is_absolute(const ::scoped_string & scopedstr)
{

   if (scopedstr.is_empty())
   {

      return false;

   }

   if (*scopedstr.begin() == '/' || *scopedstr.begin() == '\\')
   {

      return true;

   }

   auto psz = scopedstr.begin();

   while (*psz
      && (ansi_char_isalpha(*psz)
      || ansi_char_isdigit(*psz)
      || *psz == '-'
      || *psz == '_'))
   {

      psz++;

   }

   if (*psz == ':')
   {

      return true;

   }

   return false;

}


bool file_path_is_dots(const ::scoped_string & scopedstr)
{

   if(scopedstr.is_empty())
   {

      return false;

   }

   if (scopedstr.begin()[0] == '.')
   {
            
      if (scopedstr.begin()[1] == '\0')
      {
               
         return true;
               
      }
      else if(scopedstr.begin()[1] == '.')
      {
               
         if (scopedstr.begin()[2] == '\0')
         {
                  
            return true;
                  
         }

      }

   }

   return false;

}


bool file_path_is_equal(const ::file::path & pathParam1, const ::file::path & pathParam2)
{

   auto path1 = file_path_normalize(pathParam1);

   auto path2 = file_path_normalize(pathParam2);

   return path1.case_insensitive_order(path2) == 0;

}


enum_path file_path_get_type(const ::string & str, enum_path epathForce)
{

   if (epathForce != e_path_none)
   {

      return epathForce;

   }
   else if (str.case_insensitive_begins("data:"))
   {

      return e_path_data;

   }
   else if (is_url(str))
   {

      return e_path_url;

   }
   else
   {

      return e_path_file;

   }

}


string file_path_normalize(string strPath, enum_path epath)
{

   file_path_normalize_inline(strPath, epath);

   return strPath;

}


bool file_path_normalize_inline(string & strPath, enum_path & epath)
{

   if (epath == e_path_data)
   {

      return true;

   }

   bool bUrl;

   bool bOnlyNativeFileSep;

   strsize_array iaSlash;

#ifdef WINDOWS

   if (strPath.length() > 3
      && strPath[2] == ':'
      && strPath.begins_eat("/"))
   {

      //strPath = strPath.substr(1);

   }

#endif

   bool bCertainlySyntathicallyDir = solve_relative_inplace(strPath, bUrl, bOnlyNativeFileSep, iaSlash);

   if (bUrl && strPath.case_insensitive_begins("file:///"))
   {

      bUrl = false;

      //strPath = ::file::path(acmesystem()->url().::url::decode(strPath.substr(7)));
      strPath = ::file::path(::url::decode(strPath.substr(7)));

      return bCertainlySyntathicallyDir;

   }

   if (bUrl)
   {

      epath = e_path_url;

   }
   else
   {

      epath = e_path_file;

   }

   //strPath.replace_with("\\", "/");

//#ifdef WINDOWS
//   if (!bOnlyNativeFileSep && epath == e_path_file)
//#else
//   if (!bOnlyNativeFileSep)
//#endif
//   {
//
//#ifdef WINDOWS
//      if (strPath == "\\\\" || strPath == "\\")
//      {
//
//      }
//      else
//#endif
         if (strPath.has_char())
         {

            char * psz = strPath.get_buffer();

            char chSep = file_path_separator(epath);

            for (auto & iSlash: iaSlash)
            {

               psz[iSlash] = '/';

            }

            strPath.release_buffer();

         }

   //}

   return bCertainlySyntathicallyDir;

}



