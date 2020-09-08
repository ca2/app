#include "framework.h"

#ifdef WINDOWS
#include <io.h>
#include <stdio.h>
#else
#include <sys/stat.h>
//Copy file using mmap()
#include <sys/mman.h>
#endif

#include <fcntl.h>

//
//#define PACKAGE "mmap"
//#include <wchar.h>
//#include <fcntl.h>
//#include <sys/stat.h>


//void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);


int_bool ensure_file_size_fd(int32_t fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return false;

   return true;

}


size_t get_file_size(int32_t fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}



int_bool file_set_length(const char * pszName, size_t iSize)
{

   int32_t fd = ::open(pszName, O_RDONLY);

   int_bool bSet = ::ensure_file_size_fd(fd, iSize) != -1;

   ::close(fd);

   return bSet;

}




int_bool file_exists(const char * path1)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if((st.st_mode & S_IFDIR))
      return false;

   return true;

}



int_bool file_put_contents_dup(const char * path, const char * contents, ::count len)
{

   bool bOk = false;

   dir::mk(dir::name(path));

   wstring wstr(path);

   FILE * file = fopen_dup(path, "w+");

   if(file == nullptr)
   {

      return false;

   }

   try
   {

      size_t dwWrite;

      if(len < 0)
      {

         dwWrite = strlen_dup(contents);

      }
      else
      {

         dwWrite = len;

      }

      size_t dwWritten = ::fwrite(contents, 1, (uint32_t) dwWrite, file);

      bOk = dwWritten == dwWrite;

   }
   catch(...)
   {


   }

   ::fclose(file);

   return bOk;

}




string file_as_string(const char * path)
{

   string str;


   FILE * f = fopen(path, "rb");

   if(f == nullptr)
      return "";

   ::count iSize = fsize_dup(f);

   LPSTR lpsz = str.GetBufferSetLength(iSize);

   ::count iRead = fread(lpsz, 1,iSize, f);

   lpsz[iRead] = '\0';

   str.ReleaseBuffer(iRead);

   fclose(f);

   return str;

}


memory file_as_memory(const char * path)
{

   memory mem;

   file_as_memory(mem, path);

   return mem;

}


bool file_as_memory(memory_base & memory, const char * path)
{

   FILE * f = fopen(path, "rb");
   if(f == nullptr)
      return false;
   int64_t iSize = fsize_dup(f);

   if(iSize <= 0)
   {

      ::memory mem;

      mem.set_size(1024 * 16);

      int iRead;

      while((iRead = (int) fread(mem.get_data(),1,mem.get_size(),f)) > 0)
      {

         memory.append(mem.get_data(), iRead);

      }

   }
   else
   {

      memory.set_size(iSize);

      fread(memory.get_data(), memory.get_size(), 1, f);

   }

   fclose(f);

   return true;

}

memsize file_as_memory(const char * path, void * p, memsize s)
{
   FILE * f = fopen(path, "rb");
   if (f == nullptr)
      return 0;

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






uint64_t file_length_dup(const char * path)
{

   struct stat st;
   stat(path, &st);
   return st.st_size;

}



string file_module_path_dup()
{

   return "/aqua/stage";

}




extern "C"
int_bool file_copy_dup(const char * pszNew, const char * pszSrc, int_bool bOverwrite)
{

   int32_t input, output;
   size_t filesize;
   void *source, *target;


   int32_t flags = O_RDWR|O_CREAT|O_TRUNC;
   if(!bOverwrite)
      flags |= O_EXCL;
   if((output = open(pszNew, flags, 0666)) == -1)
   {
      fprintf(stderr, "Error: opening file: %s\n", pszNew);
      return false;
   }


   if((input = open(pszSrc, O_RDONLY)) == -1)
   {
      fprintf(stderr, "Error: opening file: %s\n", pszSrc);
      return false;
   }


   filesize = lseek(input, 0, SEEK_END);
   ftruncate(output, filesize);

   if((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input, 0)) == (void *) -1)
   {
      fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
      return false;
   }


   if((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *) -1)
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





int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
{
   if(stricmp_dup(psz1, psz2) == 0)
      return true;

   __throw(::exception::exception(" // TODO: it should follow links "));

   return false;

}


CLASS_DECL_AQUA string file_get_mozilla_firefox_plugin_container_path()
{
   __throw(::exception::exception(" todo "));

   return "";

}



int_bool file_delete(const char * lpszFileName)
{


   if(!::unlink(lpszFileName))
      return FALSE;

   return TRUE;


}





int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   const int32_t iBufSize = MAX_PATH * 8;
   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
//   unichar * pwszFile1;
   // unichar * pwszFile2;
   unichar * pwszPath1 = new unichar[iBufSize];
   unichar * pwszPath2 = new unichar[iBufSize];
   int32_t iCmp = -1;
//   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
   // {
   //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
   //{
   string p1 = ::str::international::unicode_to_utf8(pwszPath1);
   string p2 = ::str::international::unicode_to_utf8(pwszPath2);
   iCmp = stricmp_dup(p1,p2);
   //}
   //}
   delete[] pwszPath1;
   delete[] pwszPath2;
   return iCmp == 0;

}










int32_t ansi_open(const char * psz,int32_t i)
{

   return open(psz,i);

}

void ansi_get_errno(int32_t * perrno)
{
   *perrno = errno;
}

FILE * ansi_fopen(const char * psz,const char * pszMode)
{

   return fopen(psz,pszMode);

}


int ansi_file_flag(int iFlag)
{

   int i = 0;

   if(iFlag & ::file::type_binary)
   {

      i |= O_BINARY;

   }

   if(iFlag & ::file::mode_read)
   {

      if(iFlag & ::file::mode_write)
      {

         i |= O_RDWR;

      }
      else
      {

         i |= O_RDONLY;

      }

   }
   else if(iFlag & ::file::mode_write)
   {

      i |= O_WRONLY;

   }

   return i;

}


void ansi_unlink(const char * psz)
{

   unlink(psz);

}


int_bool is_dir(const char * path1)
{

   struct stat st;

   if(stat(path1, &st))
      return false;

   if(!(st.st_mode & S_IFDIR))
      return false;

   return true;

}









#ifdef __cplusplus

string file_first_line_dup(const string & strPath)
{

   string line;

   FILE * file = fopen_dup(strPath, "r");

   if(file == nullptr)
   {

      return "";

   }

   try
   {

      int c;

      do
      {

         c = fgetc (file);

         if (c == '\n') break;

         if (c == '\r') break;

         line += (char) c;

      }
      while (c != EOF);

   }
   catch(...)
   {

   }

   fclose(file);

   return line;

}


#endif
