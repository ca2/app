// From acme/filesystem/file/_.cpp by camilo on 2021-08-09 
// From acme_windows/acme_file.cpp
// 04:38 BRT <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "acme_file.h"
#include <stdio.h>


void copy_character_per_character(char * pszTarget, const char * pszSource)
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


string url_dir_name_for_relative(const char * pszPath)
{
   
   string strDir(pszPath);

   if (::str().ends(strDir, "/"))
   {

      return strDir;

   }

   ::str().ends_eat(strDir, "/");

   strsize iFind = strDir.reverse_find("/");

   if (iFind < 0)
      return "/";

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



CLASS_DECL_ACME bool solve_relative_inplace(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount)
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

   int & iSlashCount = *piSlashCount;

   iSlashCount = 0;

   iaSlash[0] = 0;

   strsize iPos = 0;

   if (iLen >= 2)
   {

      if (psz[0] == '\\' && psz[1] == '\\')
      {

#ifndef WINDOWS

         bOnlyNativeFileSep = false;

#endif

         iaSlash[0] = 1;

         iPos = 2;

         iSlashCount = 1;

      }

   }

   while (psz[iPos])
   {

      if (psz[iPos] == '/' || psz[iPos] == '\\')
      {

         CHECK_NATIVE_FILE_SEP(psz[iPos]);

         iaSlash[iSlashCount] = iPos;

         iSlashCount++;

         iPos++;

         if (iPos >= iLen)
         {

            // the end of string has been reached

            if (iPos > 2)
            {

               iSlashCount--;

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

               if (iSlashCount >= 2)
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

                  iPos = iaSlash[maximum(0, iSlashCount - 2)]; // go back to position of previous slash

                  iSlashCount -= 2;

                  if (iSlashCount <= 0)
                  {

                     iSlashCount = 1;

                  }

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

                  iSlashCount -= 2;

                  if (iSlashCount <= 0)
                  {

                     iNewPosition = iaSlash[0];

                     iSlashCount = 1;

                  }
                  else
                  {

                     iNewPosition = iaSlash[iSlashCount];

                  }

                  strcpy(&psz[iNewPosition], &psz[iPos]);

                  iLen -= iPos - iNewPosition;

                  iPos = iNewPosition;

               }
               else
               {

                  iPos += ch_uni_len(psz[iPos]);

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

               iSlashCount--;

               if (iSlashCount <= 0)
               {

                  iNewPosition = iaSlash[0];

                  iSlashCount = 1;

               }
               else
               {

                  iNewPosition = iaSlash[iSlashCount];

               }

               auto pszNewPosition = psz + iNewPosition;

               auto pszPos = psz + iPos;

               copy_character_per_character(pszNewPosition, pszPos);

               iLen -= iPos - iNewPosition;

               iPos = iNewPosition;

            }
            else
            {

               iPos += ch_uni_len(psz[iPos]);

               if (iPos >= iLen)
               {

                  goto ret;

               }

            }

         }
         else if (psz[iPos] == '/' || psz[iPos] == '\\')
         {

            CHECK_NATIVE_FILE_SEP(psz[iPos]);

            iaSlash[iSlashCount] = iPos;

            iSlashCount++;

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

            iPos += ch_uni_len(psz[iPos]);

            if (iPos >= iLen)
            {

               goto ret;

            }

         }

      }
      else
      {

         iPos += ch_uni_len(psz[iPos]);

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

   strsize iaSlash[512];

   int iSlashCount = 512;

   solve_relative_inplace(str, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

   if (pbUrl)
   {

      *pbUrl = bUrl;

   }

   return str;

}


CLASS_DECL_ACME string defer_solve_relative(const char * pszRelative, const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if (strRelative.is_empty())
      return "";
   if (strAbsolute.is_empty())
      return solve_relative(strRelative);
   if (::str().begins_ci(strRelative, "http://"))
      return solve_relative(strRelative);
   if (::str().begins_ci(strRelative, "https://"))
      return solve_relative(strRelative);
   if (::str().begins_ci(strRelative, "ftp://"))
      return solve_relative(strRelative);
   if (::str().begins_ci(strRelative, "ext://"))
      return solve_relative(strRelative);
   if (::str().begins(strRelative, "/"))
      return solve_relative(strRelative);
   if (::str().begins(strRelative, "\\\\"))
      return solve_relative(strRelative);

   index iFind = strRelative.find(":\\");

   if (iFind >= 0)
   {
      index i = 0;
      for (; i < iFind; i++)
      {
         if (!ansi_char_is_alphabetic(strRelative[i]) && !ansi_char_is_digit(strRelative[i]))
            break;
      }

      if (i == iFind)
         return solve_relative(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if (!::str().ends(strAbsolute, "/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return solve_relative(strRelative);

}




//CLASS_DECL_ACME bool read_resource_as_file(const char * pszFile,HINSTANCE hinst,::u32 nID,LPCTSTR pcszType);


string file_path_folder(const char * path1)
{

   const char * psz = path1 + strlen(path1) - 1;
   while (psz >= path1)
   {
      if (*psz != '\\' && *psz != '/' && *psz != ':')
         break;
      psz--;
   }
   while (psz >= path1)
   {
      if (*psz == '\\' || *psz == '/' || *psz == ':')
         break;
      psz--;
   }
   if (psz >= path1) // strChar == "\\" || strChar == "/"
   {
      const char * pszEnd = psz;
      /*while(psz >= path1)
       {
       if(*psz != '\\' && *psz != '/' && *psz != ':')
       break;
       psz--;
       }*/
      return string(path1, pszEnd - path1);
   }
   else
   {
      return "";
   }
}


//string file_path_name(const char * path)
//{
//
//   const char * pszName2 = ansi_find_char_reverse(path, '\\');
//   
//   const char * pszName1 = ansi_find_char_reverse(path, '/');
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
//   strsize iPos1 = str.reverse_find('\\');
//   strsize iPos2 = str.reverse_find('/');
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


bool file_path_is_relative(const char * psz)
{

   return !file_path_is_absolute(psz);

   //string strPath(psz);
   //if (strPath.find(':') != -1 && strPath.find(':') < 10)
   //   return false;
   //if (strPath.find('/') == 0 || strPath.find('\\') == 0)
   //   return false;
   //return true;

}


bool file_path_is_absolute(const char * psz)
{

   if (is_null(psz))
   {

      return false;

   }

   if (*psz == '/' || *psz == '\\')
   {

      return true;

   }

   if (!ansi_char_is_alphabetic(*psz))
   {

      return false;

   }

   psz++;

   if (*psz == ':')
   {

      return true;

   }
      
   while (*psz
      && (ansi_char_is_alphabetic(*psz)
      || ansi_char_is_digit(*psz)
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


bool file_path_is_dots(const char * psz)
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


bool file_path_is_equal(const char * psz1, const char * psz2)
{

   auto path1 = file_path_normalize(psz1);

   auto path2 = file_path_normalize(psz2);

   return path1.compare_ci(path2) == 0;

}


enum_path file_path_get_type(const ::string & str, enum_path epathForce)
{

   if (epathForce != e_path_none)
   {

      return epathForce;

   }
   else if (str.begins_ci("data:"))
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

   bool bUrl;

   bool bOnlyNativeFileSep;

   strsize iaSlash[512];

   int iSlashCount;

   if (epath == e_path_data)
   {

      return true;

   }

#ifdef WINDOWS

   if (strPath.get_length() > 3
      && strPath[2] == ':'
      && ::str().begins_eat(strPath, "/"))
   {

      //strPath = strPath.Mid(1);

   }

#endif

   bool bCertainlySyntathicallyDir = solve_relative_inplace(strPath, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

   if (bUrl && strPath.begins_ci("file:///"))
   {

      bUrl = false;

      //strPath = ::file::path(get_system()->url().url_decode(strPath.Mid(7)));
      strPath = ::file::path(url_decode(strPath.Mid(7)));

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

            for (int i = 0; i < iSlashCount; i++)
            {

               psz[iaSlash[i]] = chSep;

            }

            strPath.release_string_buffer();

         }

   }

   return bCertainlySyntathicallyDir;

}



