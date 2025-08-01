#include "framework.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


//int_bool file_exists_raw(const ::file::path & path1)
//{
//
//#ifdef WINDOWS
//
//   unsigned int dwFileAttributes = GetFileAttributesA(path1);
//
//   if (dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
//      return false;
//
//   return true;
//
//#else
//
//
//   // dedicaverse stat -> Sir And Arthur - Cesar Serenato
//
//   struct stat st;
//
//   if(stat(path1, &st))
//      return false;
//
//   if((st.st_mode & S_IFDIR))
//      return false;
//
//   return true;
//
//#endif
//
//}

void file_put_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path, "wb");

   if (f == nullptr)
      return;

   ::collection::count iSize = strlen(scopedstr);

   ::collection::count iRead = fwrite(scopedstr, 1, (size_t)iSize, f);

   fclose(f);

}

void file_add_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path, "ab");

   if (f == nullptr)
      return;

   ::collection::count iSize = strlen(scopedstr);

   ::collection::count iRead = fwrite(scopedstr, 1, (size_t)iSize, f);

   fclose(f);

}


void file_beg_contents_raw(const ::file::path & path, const ::scoped_string & scopedstr)
{

   FILE * f = fopen(path, "rb+");

   long lLen;

   lLen = (long) ( strlen(scopedstr));

   fseek(f, lLen, SEEK_END);

   long lEnd = ftell(f);

   long lSize = 1024 * 1024;

   char * buf = (char *) malloc(lSize);

   long lRemain = lEnd - lLen;

   while (lRemain > 0)
   {

      fseek(f, lEnd - lRemain - lLen, SEEK_SET);

      fread(buf, 1, minimum(lRemain, lSize), f);

      fseek(f, lEnd - lRemain, SEEK_SET);

      fwrite(buf, 1, minimum(lRemain, lSize), f);

      lRemain -= minimum(lRemain, lSize);

   }

   free(buf);

   fseek(f, 0, SEEK_SET);

   auto lRead = fwrite(scopedstr, 1, lLen, f);

   if (lRead != lLen)
   {

      informationf("file_beg_contents_raw: error writing to file.");

   }

   fclose(f);

}


unsigned long long file_length_raw(const ::file::path & path)
{

#ifdef WINDOWS
   struct _stat st;
   ::_stat(path, &st);
   return st.st_size;

#else
   struct stat st;
   ::stat(path, &st);
   return st.st_size;

#endif

}




string file_system()->line(const ::file::path & path, ::collection::index iLine)
{

   string str;

   FILE * file = FILE_open(path, "r", _SH_DENYNO);

   if (file == nullptr)
   {

      unsigned int dw = ::get_last_error();

      return "";

   }

   int iChar;

   string strLine;

   int iLastChar = -1;

   while (iLine >= 0)
   {

      iChar = fgetc(file);

      if (iChar == EOF)
      {

         break;

      }

      if (iChar == '\r')
      {

         iLine--;

      }
      else if (iChar == '\n')
      {

         if (iLastChar != '\r')
         {

            iLine--;

         }

      }
      else if (iLine == 0)
      {

         str += (char)iChar;

      }

      iLastChar = iChar;

   }

   return str;

}


bool file_set_line_dup(const ::file::path & path, ::collection::index iLine, const ::scoped_string & scopedstrLine)
{

   if (iLine < 0)
   {

      return false;

   }

   string str;

   ::file::path path(scopedstrPath);

            auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(path.folder());

   FILE * file = FILE_open(path, "a+", _SH_DENYWR);

   if (file == nullptr)
   {

      unsigned int dw = ::get_last_error();

      return false;

   }

   int iChar;

   string strLine;

   int iLastChar = -1;

   ::collection::index iPosStart = -1;

   ::collection::index iPosEnd = -1;

   while (iLine >= 0)
   {

      iChar = fgetc(file);

      if (iChar == EOF)
      {

         break;

      }

      if (iChar == '\r')
      {

         iLine--;

      }
      else if (iChar == '\n')
      {

         if (iLastChar != '\r')
         {

            iLine--;

         }

      }
      else if (iLine == 0)
      {

         if (iPosStart <= 0)
         {

            iPosStart = ftell(file);

         }

      }

      iLastChar = iChar;

   }

   if (iLine > 0)
   {

      fwrite("\n", 1, (size_t)iLine, file);

      fwrite(scopedstrLine, 1, strlen(scopedstrLine), file);

      fclose(file);

   }
   else
   {

      iPosEnd = ftell(file);

      ::file::path pathTime = path;

      pathTime += ".time";

      FILE * file2 = FILE_open(pathTime, "w", _SH_DENYWR);

      if (iPosStart > 0)
      {

         memory m;

         fseek(file, 0, SEEK_SET);

         m.set_size(iPosStart);

         fread(m.get_data(), 1, (size_t)iPosStart, file);

         fwrite(m.get_data(), 1, (size_t)iPosStart, file2);

      }

      fwrite(scopedstrLine, 1, strlen(scopedstrLine), file2);

      ::collection::index iEnd = fseek(file, 0, SEEK_END);

      if (iEnd - iPosEnd > 0)
      {

         memory m;

         fseek(file, (long) iPosEnd, SEEK_SET);

         m.set_size(iEnd - iPosEnd);

         fread(m.get_data(), 1, (size_t)m.get_size(), file);

         fwrite(m.get_data(), 1, (size_t)m.get_size(), file2);

      }

      fclose(file2);

      fclose(file);

#if defined(WINDOWS) || defined(APPLE_IOS)

      if (!file_copy_dup(path, pathTime.c_str(), true))
      {

         return false;

      }

      file_delete(pathTime);

#else

      ::system("mv -f \"" + string(pathTime) + "\" \"" + string(path) + "\"");

#endif

   }

   return true;

}
