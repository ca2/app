#include "framework.h"
#include "aura/os/_c.h"
#include "aura/os/_.h"
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


int_bool ensure_file_size_fd(i32 fd, size_t iSize)
{

   if (ftruncate(fd, iSize) == -1)
      return false;

   return true;

}


size_t get_file_size(i32 fd)
{

   struct stat st;

   if (fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}



int_bool file_set_length(const ::string & lpszName, size_t iSize)
{

   i32 fd = ::open(lpszName, O_RDONLY);

   int_bool bSet = ::ensure_file_size_fd(fd, iSize) != -1;

   ::close(fd);

   return bSet;

}


int_bool m_psystem->m_pacmefile->exists(const ::string & path1)
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


int_bool m_psystem->m_pacmepath->is_file_or_dir(const ::string & path1, ::file::enum_type * petype)
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


int_bool m_psystem->m_pacmefile->put_contents(const ::string & path, const ::string & contents, ::count len)
{

   bool bOk = false;

            auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->create(::file_path_folder(path));

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

      size_t dwWritten = ::fwrite(contents, 1, (u32)dwWrite, file);

      bOk = dwWritten == dwWrite;

   }
   catch (...)
   {


   }

   ::fclose(file);

   return bOk;

}




string m_psystem->m_pacmefile->as_string(const ::string & path, strsize iReadAtMostByteCount)
{

   string str;


   FILE * f = fopen(path, "rb");

   if (f == nullptr)
      return "";

   ::count iSize = FILE_get_size(f);

   iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);

   char * psz = str.get_string_buffer(iReadAtMostByteCount);


   ::count iRead = fread(psz, 1, iReadAtMostByteCount, f);

   psz[iRead] = '\0';

   str.release_string_buffer(iRead);

   ::str().begins_eat_ci(str, "\xef\xbb\xbf");

   fclose(f);

   return str;

}


memory file_as_memory(const ::string & path, strsize iReadAtMostByteCount)
{

   memory mem;

   file_as_memory(mem, path, iReadAtMostByteCount);

   return mem;

}


bool file_as_memory(memory_base & memory, const ::string & path, strsize iReadAtMostByteCount)
{

   FILE * f = fopen(path, "rb");
   if (f == nullptr)
      return false;
   strsize iSize = FILE_get_size(f);

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


memsize file_as_memory(const ::string & path, void * p, memsize s)
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






filesize file_length_dup(const ::string & path)
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


   if (!GetModuleFileNameW(nullptr, pszModuleFilePath, (::u32)pszModuleFilePath.count()))

      return "";

   return string(pszModuleFilePath);


#elif defined(APPLEOS)

   return apple_app_module_path();

#endif

}





int_bool file_copy_dup(const ::string & pszNew, const ::string & pszSrc, int_bool bOverwrite)
{

   i32 input, output;
   size_t filesize;
   void * source, * target;


   i32 flags = O_RDWR | O_CREAT | O_TRUNC;
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

   memcpy_dup(target, source, filesize);

   msync(target, filesize, MS_SYNC);

   munmap(source, filesize);
   munmap(target, filesize);

   fsync(output);

   close(input);
   close(output);

   return true;

}





int_bool file_is_equal_path_dup(const ::string & psz1, const ::string & psz2)
{
   if (ansi_compare_ci(psz1, psz2) == 0)
      return true;

   //throw ::exception(::exception(" // TODO: it should follow links "));

   return false;

}


CLASS_DECL_CORE string file_get_mozilla_firefox_plugin_container_path()
{
   throw ::exception(::exception(" todo "));

   return "";

}



int_bool file_delete(const ::string & pszFileName)

{


   if (::unlink(pszFileName) == -1)

   {

      return false;

   }

   return true;


}





int_bool file_path_is_equal(const ::string & psz1, const ::string & psz2)
{

   const i32 iBufSize = MAX_PATH * 8;
   wstring pwsz1 = utf8_to_unicode(psz1);
   wstring pwsz2 = utf8_to_unicode(psz2);
   //   unichar * pwszFile1;
      // unichar * pwszFile2;
   widechar * pwszPath1 = new widechar[iBufSize];
   widechar * pwszPath2 = new widechar[iBufSize];
   i32 iCmp = -1;
   //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
      // {
      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
      //{
   string path1 = unicode_to_utf8(pwszPath1);
   string path2 = unicode_to_utf8(pwszPath2);
   iCmp = ansi_compare_ci(path1, path2);
   //}
   //}
   delete[] pwszPath1;
   delete[] pwszPath2;
   return iCmp == 0;

}










i32 ansi_open(const ::string & psz, i32 i)
{

   return open(psz, i);

}

void ansi_get_errno(i32 * perrno)
{
   *perrno = errno;
}

FILE * ansi_fopen(const ::string & psz, const ::string & pszMode)
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


void ansi_unlink(const ::string & psz)
{

   unlink(psz);

}


int_bool is_dir(const ::string & path1)
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




