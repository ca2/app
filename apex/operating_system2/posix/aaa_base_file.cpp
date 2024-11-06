#include "framework.h"
#include "apex/operating_system/_c.h"
//#include "apex/operating_system/_.h"
#ifdef WINDOWS
#include <io.h>
#include <stdio.h>
#else

#include <sys/stat.h>
//Copy file using mmap()
#include <sys/mman.h>
#include <unistd.h>
#endif

#include <fcntl.h>

//
//#define PACKAGE "mmap"
//#include <wchar.h>
//#include <fcntl.h>
//#include <sys/stat.h>


//void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);


int_bool ensure_file_size_fd(int fd, size_t iSize)
{

   if (ftruncate(fd, iSize) == -1)
      return false;

   return true;

}


size_t get_file_size(int fd)
{

   struct stat st;

   if (fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}



int_bool file_set_length(const char * lpszName, size_t iSize)
{

   int fd = ::open(lpszName, O_RDONLY);

   int_bool bSet = ::ensure_file_size_fd(fd, iSize) != -1;

   ::close(fd);

   return bSet;

}


int_bool file_system()->exists(const ::file::path & path1)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if (stat(path1, &st))
   {

      return false;

   }

   if ((st.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


int_bool path_system()->is_file_or_dir(const ::file::path & path1, ::file::enum_type * petype)
{

   struct stat st;

   if (stat(path1, &st))
   {

      if (is_set(petype))
      {

         *petype = ::file::e_type_none;

      }

      return false;

   }

   if (is_set(petype))
   {

      if ((st.st_mode & S_IFDIR))
      {

         *petype = ::file::e_type_folder;

      }
      else
      {

         *petype = ::file::e_type_file;

      }

   }

   return true;

}


int_bool file_system()->put_contents(const ::file::path & path, const char * contents, ::collection::count len)
{

   bool bOk = false;

            auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->create(::file_path_folder(path));

   wstring wstr(path);

   FILE * file = FILE_open(path, "w+", _SH_DENYWR);

   if (file == nullptr)
   {

      return false;

   }

   try
   {

      size_t dwWrite;

      if (len < 0)
      {

         dwWrite = ansi_length(contents);

      }
      else
      {

         dwWrite = len;

      }

      size_t dwWritten = ::fwrite(contents, 1, (unsigned int)dwWrite, file);

      bOk = dwWritten == dwWrite;

   }
   catch (...)
   {


   }

   ::fclose(file);

   return bOk;

}




string file_system()->as_string(const ::file::path & path, character_count iReadAtMostByteCount)
{

   string str;


   FILE * f = fopen(path, "rb");

   if (f == nullptr)
      return "";

   ::collection::count iSize = FILE_get_size(f);

   iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);

   char * psz = str.get_buffer(iReadAtMostByteCount);


   ::collection::count iRead = fread(psz, 1, iReadAtMostByteCount, f);

   psz[iRead] = '\0';

   str.release_buffer(iRead);

   str.case_insensitive_begins_eat("\xef\xbb\xbf");

   fclose(f);

   return str;

}


memory file_as_memory(const ::file::path & path, character_count iReadAtMostByteCount)
{

   memory mem;

   file_as_memory(mem, path, iReadAtMostByteCount);

   return mem;

}


bool file_as_memory(memory_base & memory, const ::file::path & path, character_count iReadAtMostByteCount)
{

   FILE * f = fopen(path, "rb");
   if (f == nullptr)
      return false;
   character_count iSize = FILE_get_size(f);

   if (iSize < 0)
   {

      ::memory mem;

      mem.set_size(1024 * 16);

      int iRead;

      if (iReadAtMostByteCount >= 0)
      {

         while ((iRead = (int)fread(mem.get_data(), 1, minimum(iReadAtMostByteCount - memory.get_size(), mem.get_size()), f)) > 0)
         {

            memory.append(mem.get_data(), iRead);

         }

      }
      else
      {

         while ((iRead = (int)fread(mem.get_data(), 1, mem.get_size(), f)) > 0)
         {

            memory.append(mem.get_data(), iRead);

         }

      }


   }
   else
   {

      iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);

      memory.set_size(iReadAtMostByteCount);

      fread(memory.get_data(), memory.get_size(), 1, f);

   }

   fclose(f);

   return true;

}


memsize file_as_memory(const ::file::path & path, void * p, memsize s)
{

   FILE * f = fopen(path, "rb");

   if (f == nullptr)
   {

      return 0;

   }

   memsize sRead = 0;

   try
   {

      sRead = fread(p, 1, s, f);

   }
   catch (...)
   {

   }

   fclose(f);

   return sRead;

}






filesize file_length_dup(const ::file::path & path)
{

   struct stat st;
   stat(path, &st);
   return st.st_size;

}



::file::path file::app_module()
{

#if defined(ANDROID) || defined(LINUX)

   ::file::path path;

   char * pszModule = nullptr;

   if((pszModule = br_find_exe(nullptr)) == nullptr)
   {

      if (!br_init_lib(nullptr))
      {

         char path[PATH_MAX * 4];

         char dest[PATH_MAX * 4];

         pid_t pid = getpid();

         sprintf(path, "/proc/%d/exe", pid);

         auto iSize = readlink(path, dest, PATH_MAX);

         if (iSize > 0)
         {

            dest[iSize] = '\0';

            pszModule = strdup(dest);


         }

      }

   }

   path = pszModule;

   ::free(pszModule);

   return path;

#elif defined(WINDOWS)

   wstring pszModuleFolder(MAX_PATH * 8);


   wstring pszModuleFilePath(MAX_PATH * 8);


   if (!GetModuleFileNameW(nullptr, pszModuleFilePath, (unsigned int)pszModuleFilePath.count()))

      return "";

   return string(pszModuleFilePath);


#elif defined(__APPLE__)

   return apple_app_module_path();

#endif

}





int_bool file_copy_dup(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrSrc, int_bool bOverwrite)
{

   int input, output;
   size_t filesize;
   void * source, * target;


   int flags = O_RDWR | O_CREAT | O_TRUNC;
   if (!bOverwrite)
      flags |= O_EXCL;
   if ((output = open(pszNew, flags, 0666)) == -1)
   {
      fprintf(stderr, "Error: opening file: %s\n", pszNew);
      return false;
   }


   if ((input = open(pszSrc, O_RDONLY)) == -1)
   {
      fprintf(stderr, "Error: opening file: %s\n", pszSrc);
      return false;
   }


   filesize = lseek(input, 0, SEEK_END);
   ftruncate(output, filesize);

   if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input, 0)) == (void *)-1)
   {
      fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
      return false;
   }


   if ((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *)-1)
   {
      fprintf(stderr, "Error mapping ouput file: %s\n", pszNew);
      return false;
   }

   memory_copy(target, source, filesize);

   msync(target, filesize, MS_SYNC);

   munmap(source, filesize);
   munmap(target, filesize);

   fsync(output);

   close(input);
   close(output);

   return true;

}





int_bool file_is_equal_path_dup(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
{
   if (case_insensitive_ansi_compare(psz1, psz2) == 0)
      return true;

   //throw ::exception(::exception(" // TODO: it should follow links "));

   return false;

}


CLASS_DECL_APEX string file_get_mozilla_firefox_plugin_container_path()
{
   throw ::exception(::exception(" todo "));

   return "";

}



int_bool file_delete(const ::file::path & path)

{


   if (::unlink(pszFileName) == -1)

   {

      return false;

   }

   return true;


}





int_bool file_path_is_equal(const ::file::path & pathParam1, const ::file::path & pathParam2)
{

   const int iBufSize = MAX_PATH * 8;
   wstring pwsz1 = utf8_to_unicode(psz1);
   wstring pwsz2 = utf8_to_unicode(psz2);
   //   unichar * pwszFile1;
      // unichar * pwszFile2;
   ::wide_character * pwszPath1 = aaa_primitive_new ::wide_character[iBufSize];
   ::wide_character * pwszPath2 = aaa_primitive_new ::wide_character[iBufSize];
   int iCmp = -1;
   //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
      // {
      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
      //{
   string path1 = unicode_to_utf8(pwszPath1);
   string path2 = unicode_to_utf8(pwszPath2);
   iCmp = case_insensitive_ansi_compare(path1, path2);
   //}
   //}
   delete[] pwszPath1;
   delete[] pwszPath2;
   return iCmp == 0;

}










int ansi_open(const ::scoped_string & scopedstr, int i)
{

   return open(psz, i);

}

void ansi_get_errno(int * perrno)
{
   *perrno = errno;
}

FILE * ansi_fopen(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrMode)
{

   return fopen(psz, pszMode);

}


int ansi_file_flag(int iFlag)
{

   int i = 0;

   if (iFlag & ::file::e_open_binary)
   {

      i |= O_BINARY;

   }

   if (iFlag & ::file::e_open_read)
   {

      if (iFlag & ::file::e_open_write)
      {

         i |= O_RDWR;

      }
      else
      {

         i |= O_RDONLY;

      }

   }
   else if (iFlag & ::file::e_open_write)
   {

      i |= O_WRONLY;

   }

   return i;

}


void ansi_unlink(const ::scoped_string & scopedstr)
{

   unlink(psz);

}


int_bool is_dir(const ::file::path & path1)
{

   struct stat st;

   if (stat(path1, &st))
   {

      return false;

   }

   if (!(st.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}









#ifdef __cplusplus

string file_first_line_dup(const ::string & strPath)
{

   string line;

   FILE * file = FILE_open(strPath, "r", _SH_DENYNO);

   if (file == nullptr)
   {

      return "";

   }

   try
   {

      int c;

      do
      {

         c = fgetc(file);

         if (c == '\n') break;

         if (c == '\r') break;

         line += (char)c;

      } while (c != EOF);

   }
   catch (...)
   {

   }

   fclose(file);

   return line;

}


#endif




