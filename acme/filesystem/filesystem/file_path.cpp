// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme_file.h"
//#include "acme/networking/as_string.h"
//#include "acme/primitive/collection/numeric_array.h"



void copy_character_per_character(char * pszTarget, const scoped_string & strSource)
{

   while(*pszSource)
   {

      *pszTarget = *pszSource;

      pszTarget++;

      pszSource++;

   }

}

const char * file_path_name(const char * path)
{

   auto name1 = strrchr(path, '\\');

   auto name2 = strrchr(path, '/');

   if (!name1)
   {

      if (!name2)
      {

         return path;

      }
      else
      {

         return name2 + 1;

      }

   }
   else
   {
   
      if (name1 > name2) // || !name2 not needed
      {

         return name1 + 1;

      }
      else 
      {

         return name2 + 1;

      }

   }

}


const char * file_path_final_extension(const char * path)
{

   auto name = file_path_name(path);

   auto final_extension = strrchr(name, '.');

   if (!final_extension)
   {

      return nullptr;

   }

   return final_extension + 1;

}


const char * file_path_all_extensions(const char * path)
{

   auto name = file_path_name(path);

   auto final_extension = strchr(name, '.');

   if (!final_extension)
   {

      return nullptr;

   }

   return final_extension + 1;

}


string url_dir_name_for_relative(const scoped_string & strPath)
{
   
   string strDir(pszPath);

   if (strDir.ends("/"))
   {

      return strDir;

   }

   strDir.ends_eat("/");

   strsize iFind = strDir.rear_find("/");

   if (iFind < 0)
   {

      return "/";

   }

   return strDir.substr(0, iFind + 1);

}


#ifdef WINDOWS

#define CHECK_NATIVE_FILE_SEP(ch) \
   \
   if (bOnlyNativeFileSep && psz[iPos] == '/') \
   { \
   \
      bOnlyNativeFileSep = false; \
   \
   }

#else

#define CHECK_NATIVE_FILE_SEP(ch) \
   \
   if (bOnlyNativeFileSep && psz[iPos] == '/') \
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

   bool bDup = false;

   strsize iLen = str.get_length();

   char * psz = str.get_string_buffer(iLen);

   //string strAbsolute(strParam);

   strsize iNewPosition;

   bool bDynIa = false;

   //strsize * iaSlash = *iaSlash;

   iaSlash.set_size(0);

   strsize iPos = 0;

   if (iLen >= 2)
   {

      if (psz[0] == '\\' && psz[1] == '\\')
      {

#ifndef WINDOWS

         bOnlyNativeFileSep = false;

#endif

         iaSlash.add(1);

         iPos = 2;

      }

   }

   while (psz[iPos])
   {

      if (psz[iPos] == '/' || psz[iPos] == '\\')
      {

         CHECK_NATIVE_FILE_SEP(psz[iPos]);

         iaSlash.add(iPos);

         iPos++;

         if (iPos >= iLen)
         {

            // the end of string has been reached

            if (iPos > 2)
            {

               iaSlash.erase_at(iaSlash.get_upper_bound());

               iPos--; // erase trailing slash

            }

            bCertainlySyntathicallyDir = true;

            goto ret;

         }
         else if (psz[iPos] == '.')
         {

            iPos++;

            if (iPos >= iLen)
            {

               // the end of string has been reached

               if (iaSlash.size() >= 2)
               {

                  iPos -= 2; // erase the dot and and trailing slash

               }
               else
               {

                  iPos--;// erase the dot

               }

               bCertainlySyntathicallyDir = true;

               goto ret;

            }
            else if (psz[iPos] == '.')
            {

               iPos++;

               if (iPos >= iLen)
               {

                  // the end of string has been reached

                  iPos = iaSlash[maximum(0, iaSlash.size() - 2)]; // go back to position of previous slash

                  iaSlash.set_size(maximum(1, iaSlash.size() - 2));

                  if (iPos > 2)
                  {

                     iPos--;

                  }

                  bCertainlySyntathicallyDir = true;

                  goto ret;

               }
               else if (psz[iPos] == '/' || psz[iPos] == '\\')
               {

                  CHECK_NATIVE_FILE_SEP(psz[iPos]);

                  if (!bDup)
                  {

                     psz = str.get_string_buffer();

                     bDup = true;

                  }

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

                  strcpy(&psz[iNewPosition], &psz[iPos]);

                  iLen -= iPos - iNewPosition;

                  iPos = iNewPosition;

               }
               else
               {

                  iPos += utf8_unicode_length(psz[iPos]);

                  if (iPos >= iLen)
                  {

                     iPos = iLen - 1;

                     goto ret;

                  }

               }

            }
            else if (psz[iPos] == '/' || psz[iPos] == '\\')
            {

               CHECK_NATIVE_FILE_SEP(psz[iPos]);

               if (!bDup)
               {

                  psz = str.get_string_buffer();

                  bDup = true;

               }

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

               auto pszPos = psz + iPos;

               copy_character_per_character(pszNewPosition, pszPos);

               iLen -= iPos - iNewPosition;

               iPos = iNewPosition;

            }
            else
            {

               iPos += utf8_unicode_length(psz[iPos]);

               if (iPos >= iLen)
               {

                  goto ret;

               }

            }

         }
         else if (psz[iPos] == '/' || psz[iPos] == '\\')
         {

            CHECK_NATIVE_FILE_SEP(psz[iPos]);

            iaSlash.add(iPos);

            iPos++;

            if (iPos > 3 && psz[iPos - 3] == ':')
            {

               bUrl = true;

            }

            if (iPos >= iLen)
            {

               // the end of string has been reached


               bCertainlySyntathicallyDir = true;

               goto ret;

            }

         }
         else
         {

            iPos += utf8_unicode_length(psz[iPos]);

            if (iPos >= iLen)
            {

               goto ret;

            }

         }

      }
      else
      {

         iPos += utf8_unicode_length(psz[iPos]);

         if (iPos >= iLen)
         {

            goto ret;

         }

      }

   }

ret:

   if (bDup)
   {

      str.release_string_buffer(iPos);

   }
   else if (iPos < iLen)
   {

      str.truncate(iPos);

   }

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


CLASS_DECL_ACME string defer_solve_relative(const scoped_string & strRelative, const scoped_string & strAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
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

   index iFind = strRelative.find(":\\");

   if (iFind >= 0)
   {
      index i = 0;
      for (; i < iFind; i++)
      {
         if (!ansi_char_isalpha(strRelative[i]) && !ansi_char_isdigit(strRelative[i]))
            break;
      }

      if (i == iFind)
         return solve_relative(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if (!strAbsolute.ends("/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return solve_relative(strRelative);

}




//CLASS_DECL_ACME bool read_resource_as_file(const scoped_string & strFile,HINSTANCE hinst,::u32 nID,LPCTSTR pcszType);

const char * string_reverse_span_excluding(const scoped_string & str, const scoped_string & strBegin, const scoped_string & strExcluding)
{

   while (psz >= pszBegin)
   {

      auto pszCheck = pszExcluding;

      while(*pszCheck)
      {

         if (*psz == *pszCheck)
         {

            return psz;

         }

         pszCheck++;

      }

      psz--;

   }

   return nullptr;

}


const char * string_reverse_span_including(const scoped_string & str, const scoped_string & strBegin, const scoped_string & strIncluding)
{

   while (psz >= pszBegin)
   {

      auto pszCheck = pszIncluding;

      bool bIncludesAny = false;

      while(*pszCheck)
      {

         if (*psz == *pszCheck)
         {

            bIncludesAny = true;

            break;

         }

         pszCheck++;

      }

      if(!bIncludesAny)
      {

         return psz;

      }

      psz--;

   }

   return nullptr;

}


// 1. /folder/name
// 2. /name
string file_path_folder(const char * path1)
{

   const scoped_string & str = path1 + string_safe_length(path1) - 1;

   auto pszSeparator = string_reverse_span_excluding(psz, path1, "\\/");

// 1. /folder/
// 2. /

   if(!pszSeparator)
   {

      return "";

   }

   auto pszLastFolderCharacter = string_reverse_span_including(pszSeparator, path1, "\\/");

// 1. /folder
// 2. nullptr

   if(pszLastFolderCharacter)
   {

      pszSeparator = pszLastFolderCharacter + 1;

   }

// 1. /folder/
// 2. /

   return string(path1, pszSeparator - path1);

}


//string file_path_name(const char * path)
//{
//
//   const scoped_string & strName2 = ansi_find_char_reverse(path, '\\');
//   
//   const scoped_string & strName1 = ansi_find_char_reverse(path, '/');
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



//string file_path_name(const char * path)
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


string file_path_title(const char * path)
{
   string str = file_path_name(path);
   strsize iPos = str.find('.');
   if (iPos != -1)
   {
      return str.substr(0, iPos);
   }
   else
   {
      return str;
   }
}


bool file_path_is_relative(const scoped_string & str)
{

   return !file_path_is_absolute(psz);

   //string strPath(psz);
   //if (strPath.find(':') != -1 && strPath.find(':') < 10)
   //   return false;
   //if (strPath.find('/') == 0 || strPath.find('\\') == 0)
   //   return false;
   //return true;

}


bool file_path_is_absolute(const scoped_string & str)
{

   if (is_null(psz))
   {

      return false;

   }

   if (*psz == '/' || *psz == '\\')
   {

      return true;

   }

   if (!ansi_char_isalpha(*psz))
   {

      return false;

   }

   psz++;

   if (*psz == ':')
   {

      return true;

   }
      
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


bool file_path_is_dots(const scoped_string & str)
{

   if(is_null(psz))
   {

      return false;

   }

   if (psz[0] == '.')
   {
            
      if (psz[1] == '\0')
      {
               
         return true;
               
      }
      else if(psz[1] == '.')
      {
               
         if (psz[2] == '\0')
         {
                  
            return true;
                  
         }

      }

   }

   return false;

}


bool file_path_is_equal(const scoped_string & str1, const scoped_string & str2)
{

   auto path1 = file_path_normalize(psz1);

   auto path2 = file_path_normalize(psz2);

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

   if (strPath.get_length() > 3
      && strPath[2] == ':'
      && strPath.begins_eat("/"))
   {

      //strPath = strPath.Mid(1);

   }

#endif

   bool bCertainlySyntathicallyDir = solve_relative_inplace(strPath, bUrl, bOnlyNativeFileSep, iaSlash);

   if (bUrl && strPath.case_insensitive_begins("file:///"))
   {

      bUrl = false;

      //strPath = ::file::path(acmesystem()->url().::url::decode(strPath.Mid(7)));
      strPath = ::file::path(::url::decode(strPath.Mid(7)));

      return bCertainlySyntathicallyDir;

   }

   if (bUrl)
   {

      epath = e_path_url;

      strPath.replace_with("/", "\\");

   }
   else
   {

      epath = e_path_file;

   }

#ifdef WINDOWS
   if (!bOnlyNativeFileSep && epath == e_path_file)
#else
   if (!bOnlyNativeFileSep)
#endif
   {

#ifdef WINDOWS
      if (strPath == "\\\\" || strPath == "\\")
      {

      }
      else
#endif
         if (strPath.has_char())
         {

            char * psz = strPath.get_string_buffer();

            char chSep = file_path_separator(epath);

            for (auto & iSlash: iaSlash)
            {

               psz[iSlash] = chSep;

            }

            strPath.release_string_buffer();

         }

   }

   return bCertainlySyntathicallyDir;

}



