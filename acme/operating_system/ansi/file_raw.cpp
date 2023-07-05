#include "framework.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


#if !defined(WINDOWS)


int_bool file_path_is_link(const ::file::path & path)
{

   struct stat stat;

   zero(stat);

   if(lstat(path.c_str(), &stat) != 0)
   {

      return false;

   }

   if(S_ISLNK(stat.st_mode))
   {

      return true;

   }

   return false;

}


#endif


void file_put_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path.c_str(), "wb");

   if (f == nullptr)
      return;

   ::count iSize = ansi_len(path.c_str());

   ::count iRead = fwrite(path.c_str(), 1, (size_t)iSize, f);

   fclose(f);

}

void file_add_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path.c_str(), "ab");

   if (f == nullptr)
      return;

   ::count iSize = scopedstr.size();

   ::count iRead = fwrite(scopedstr.c_str(), 1, (size_t)iSize, f);

   fclose(f);

}


void file_beg_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path.c_str(), "rb+");

   long lLen;

   lLen = (long) scopedstr.size();

   fseek(f, lLen, SEEK_END);

   long lEnd = ftell(f);

   long lSize = 1024 * 1024;

   char * buf = (char *) malloc(lSize);

   long lRemain = lEnd - lLen;

   while (lRemain > 0)
   {

      fseek(f, lEnd - lRemain - lLen, SEEK_SET);

      auto iToReadCount = minimum(lRemain, lSize);

      auto iReadCount = fread(buf, 1, iToReadCount, f);

      if(iReadCount < iToReadCount)
      {

         int iFileError = ferror(f);

         if(iFileError != 0)
         {



         }

         int iFileEOF = feof(f);



      }

      fseek(f, lEnd - lRemain, SEEK_SET);

      fwrite(buf, 1, minimum(lRemain, lSize), f);

      lRemain -= minimum(lRemain, lSize);

   }

   free(buf);

   fseek(f, 0, SEEK_SET);

   auto lRead = fwrite(scopedstr.c_str(), 1, lLen, f);

   if (lRead != lLen)
   {

      information("file_beg_contents_raw: error writing to file.");

   }

   fclose(f);

}


u64 file_length_raw(const ::file::path & path)
{

#ifdef WINDOWS
   struct _stat st;
   ::_stat(path, &st);
   return st.st_size;

#else
   struct stat st;
   ::stat(path.c_str(), &st);
   return st.st_size;

#endif

}




//string acmefile()->line(const ::file::path & path, index iLine)
//{
//
//   string str;
//
//   auto pfile = fopen(path, "r", _SH_DENYNO);
//
//   if (pfile == nullptr)
//   {
//
//      ::e_status estatus = ::get_last_status();
//
//      return "";
//
//   }
//
//   int iChar;
//
//   string strLine;
//
//   int iLastChar = -1;
//
//   while (iLine >= 0)
//   {
//
//      iChar = fgetc(pfile);
//
//      if (iChar == EOF)
//      {
//
//         break;
//
//      }
//
//      if (iChar == '\r')
//      {
//
//         iLine--;
//
//      }
//      else if (iChar == '\n')
//      {
//
//         if (iLastChar != '\r')
//         {
//
//            iLine--;
//
//         }
//
//      }
//      else if (iLine == 0)
//      {
//
//         str += (char)iChar;
//
//      }
//
//      iLastChar = iChar;
//
//   }
//
//   return str;
//
//}


