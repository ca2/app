#include "framework.h"
#include <stdio.h>


string file_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.find('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}

string file_final_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.rfind('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}





string url_dir_name_for_relative(const char * pszPath)
{
   string strDir(pszPath);

   if(str::ends(strDir,"/"))
      return strDir;

   str::ends_eat(strDir,"/");

   strsize iFind = strDir.reverse_find("/");

   if(iFind < 0)
      return "/";

   return strDir.substr(0,iFind + 1);

}


CLASS_DECL_APEX string solve_relative(const string & strParam, bool * pbUrl)
{

   string str(strParam);

   bool bUrl;

   bool bOnlyNativeFileSep;

   strsize iaSlash[512];

   int iSlashCount = 512;

   solve_relative_inline(str, bUrl, bOnlyNativeFileSep, iaSlash, &iSlashCount);

   if (pbUrl)
   {

      *pbUrl = bUrl;

   }

   return str;

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


CLASS_DECL_APEX bool solve_relative_inline(string & str, bool & bUrl, bool & bOnlyNativeFileSep, strsize * iaSlash, int * piSlashCount)
{

   bOnlyNativeFileSep = true;

   bool bCertainlySyntathicallyDir = false;

   bUrl = false;

   bool bDup = false;

   strsize iLen = str.get_length();

   char * psz = str.get_string_buffer(iLen);

   //string strAbsolute(strParam);

   strsize iNewPos;

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

               iPos--; // remove trailing slash

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

                  iPos -= 2; // remove the dot and and trailing slash

               }
               else
               {

                  iPos--;// remove the dot

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

                  iPos = iaSlash[MAX(0, iSlashCount - 2)]; // go back to position of previous slash

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

                  iSlashCount-=2;

                  if (iSlashCount <= 0)
                  {

                     iNewPos = iaSlash[0];

                     iSlashCount = 1;

                  }
                  else
                  {

                     iNewPos = iaSlash[iSlashCount];

                  }

                  strcpy(&psz[iNewPos], &psz[iPos]);

                  iLen -= iPos - iNewPos;

                  iPos = iNewPos;

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

                  iNewPos = iaSlash[0];

                  iSlashCount = 1;

               }
               else
               {

                  iNewPos = iaSlash[iSlashCount];

               }

               strcpy(&psz[iNewPos], &psz[iPos]);

               iLen -= iPos - iNewPos;

               iPos = iNewPos;

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


CLASS_DECL_APEX string defer_solve_relative(const char * pszRelative,const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if(strRelative.is_empty())
      return "";
   if(strAbsolute.is_empty())
      return solve_relative(strRelative);
   if(str::begins_ci(strRelative,"http://"))
      return solve_relative(strRelative);
   if(str::begins_ci(strRelative,"https://"))
      return solve_relative(strRelative);
   if(str::begins_ci(strRelative,"ftp://"))
      return solve_relative(strRelative);
   if(str::begins_ci(strRelative,"ext://"))
      return solve_relative(strRelative);
   if(str::begins(strRelative,"/"))
      return solve_relative(strRelative);
   if(str::begins(strRelative,"\\\\"))
      return solve_relative(strRelative);

   index iFind = strRelative.find(":\\");

   if(iFind >= 0)
   {
      index i = 0;
      for(; i < iFind; i++)
      {
         if(!ansi_char_is_alphabetic(strRelative[i]) && !ansi_char_is_digit(strRelative[i]))
            break;
      }

      if(i == iFind)
         return solve_relative(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if(!str::ends(strAbsolute,"/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return solve_relative(strRelative);

}




//CLASS_DECL_APEX bool read_resource_as_file(const char * pszFile,HINSTANCE hinst,UINT nID,LPCTSTR pcszType);




string get_temp_file_name_dup(const char * lpszName,const char * pszExtension)
{

#ifdef WINDOWS

   WCHAR pPathBuffer[MAX_PATH * 16];

   DWORD dwRetVal = GetTempPathW(sizeof(pPathBuffer) / sizeof(WCHAR), pPathBuffer);

   if (dwRetVal > sizeof(pPathBuffer) || (dwRetVal == 0))
   {

      debug_print("GetTempPath failed (%d)\n", get_last_error());

      return "";

   }

#else

   char pPathBuffer[MAX_PATH * 16];

   strcpy(pPathBuffer, "/tmp/");

#endif

   ::file::path pathFolder(pPathBuffer);

   for(int i = 0; i < 1000; i++)
   {

      ::file::path path;

      path = pathFolder;

      path /= lpszName;

      path /= __str(i);

      path /= (string(lpszName) + "." + string(pszExtension));

      if(file_exists(path))
      {

         if (::file_delete(path))
         {

            return ::move(path);

         }

      }
      else
      {

         return ::move(path);

      }

   }

   return "";

}




bool write_memory_to_file(FILE * file,const void * pdata,memsize nCount,memsize * puiWritten)

{

#if OSBIT > 32

   memsize pos = 0;

   DWORD dw= 0;

   DWORD dwWrite;

   memsize uiWrittenTotal = 0;

   while(pos < nCount)
   {

      dwWrite = (DWORD)MIN(nCount - uiWrittenTotal,0xffffffffu);

      dw = (DWORD) (fwrite(&((u8 *)pdata)[pos],1, dwWrite, file));


      if(dw != dwWrite)
      {

         uiWrittenTotal += dw;

         if(puiWritten != nullptr)
         {

            *puiWritten = uiWrittenTotal;

         }

         return false;

      }

      uiWrittenTotal += dw;

      if(dw != dwWrite)
         break;

      pos += dw;

   }

   if(puiWritten != nullptr)
   {

      *puiWritten = uiWrittenTotal;

   }

   return uiWrittenTotal == nCount;

#else

   DWORD dw = 0;

   dw = ::fwrite(pdata, 1, (size_t) nCount, file);


   WINBOOL bOk = dw == nCount;

   if(puiWritten != nullptr)
   {

      *puiWritten = dw;

   }

   return bOk;

#endif

}



CLASS_DECL_APEX bool file_append_wait_dup(const string & strFile, const char * psz, strsize s, DWORD tickTimeout)
{

   ::dir::mk(::dir::name(strFile));

   if (!::dir::is(::dir::name(strFile)))
   {

      return false;

   }

   wstring wstr(strFile);

   FILE * pfile = nullptr;
auto tickStart = ::tick::now();



   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
      pfile = fopen(strFile, "ab");
#else
      pfile = _wfopen(wstr, L"ab");
#endif

      if (pfile != nullptr)
      {

         break;

      }

      if (tickStart.elapsed() > tickTimeout)
      {

         return false;

      }

      Sleep(5);

   }

   fwrite(psz, (size_t)s, 1, pfile);

   fclose(pfile);

   return true;

}



bool file_append_wait_dup(const string & strFile, const string & str, DWORD tickTimeout)
{

   return file_append_wait_dup(strFile, str, str.get_length(), tickTimeout);

}

CLASS_DECL_APEX bool file_append_dup(const string & strFile, const char * psz, strsize s)
{

   return file_append_wait_dup(strFile, psz, s, 0);

}

bool file_append_dup(const string & strFile, const string & str)
{

   return file_append_dup(strFile, str, str.get_length());

}







//#ifdef WINDOWS_DESKTOP
//
//
//bool  SHGetSpecialFolderPath(oswindow oswindow, ::file::path & path, i32 csidl, bool fCreate)
//{
//
//   string str;
//
//   if (::SHGetSpecialFolderPathW(oswindow, wtostring(str, MAX_PATH * 8), csidl, fCreate) == FALSE)
//   {
//
//      return false;
//
//   }
//
//   path = str;
//
//   return true;
//
//}
//
//
//#endif


#ifdef WINDOWS


bool __win_file_find_is_dots(WIN32_FIND_DATAW & data)
{

   if (data.cFileName[0] == L'.')
   {

      if (data.cFileName[1] == L'\0' ||
            (data.cFileName[1] == L'.' &&
             data.cFileName[2] == L'\0'))
      {

         return true;

      }

   }

   return false;

}


#endif






void replace_char(char * sz, char ch1, char ch2)
{

   while (*sz)
   {

      if (*sz == ch1)
      {

         *sz = ch2;

      }

      sz++;

   }

}
