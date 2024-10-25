#include "framework.h"
#include "file.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/operating_system/shared_posix/time.h"
#include "acme/_operating_system.h"
#include "acme/operating_system/console.h"
//#include "acme/prototype/collection/map_interface.h"
//#if defined( FREEBSD)
//#define __XSI_VISIBLE 1
//#endif
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#include <fcntl.h>


namespace unistd
{

   file::file()
   {
      m_iFile = -1;
   }
   file::file(const file & file):
m_iFile(file.m_iFile)
   {
   }
   file::file(int iFile):
m_iFile(iFile)
   {
   }
   file::~file()
   {

close();

   }

   int file::close()
   {
      int res = 0;
      if(m_iFile >= 0)
      {

         res = ::close(m_iFile);

         m_iFile = -1;

      }
      return res;
   }



   memsize file::read(void * p, memsize s)
   {

      return ::read(m_iFile, p, s);

   }


   long file::write(const void * p, memsize s)
   {

      return ::write(m_iFile, p, s);

   }



      int file::set_cloexec_or_close()
      {
         long flags;

         if (m_iFile == -1)
            return -1;

         flags = fcntl(m_iFile, F_GETFD);
         if (flags == -1)
            goto err;

         if (fcntl(m_iFile, F_SETFD, flags | FD_CLOEXEC) == -1)
            goto err;

         return m_iFile;

         err:
         close();
      return -1;
      }


      int file::create_tmpfile_cloexec(char * tmpname)
      {

#ifdef HAVE_MKOSTEMP
         m_iFile = mkostemp(tmpname, O_CLOEXEC);
         if (m_iFile >= 0)
            unlink(tmpname);
#else
         m_iFile = mkstemp(tmpname);
         if (m_iFile >= 0)
         {
            m_iFile = set_cloexec_or_close();
            unlink(tmpname);
         }
#endif

         return m_iFile;
      }

      /*
       * Create a ___new, unique, anonymous file of the given size, and
       * return the file descriptor for it. The file descriptor is set
       * CLOEXEC. The file is immediately suitable for mmap()'ing
       * the given size at offset zero.
       *
       * The file should not have a permanent backing store like a disk,
       * but may have if XDG_RUNTIME_DIR is not properly implemented in OS.
       *
       * The file name is deleted from the file system.
       *
       * The file is suitable for buffer sharing between processes by
       * transmitting the file descriptor over Unix sockets using the
       * SCM_RIGHTS methods.
       */
      int    file::create_anonymous_file(memsize size)
      {
         static const char pszTemplate[] = "/weston-shared-XXXXXX";
         const char * path;
         char * name;

         path = getenv("XDG_RUNTIME_DIR");
         if (!path)
         {
            errno = ENOENT;
            return -1;
         }

         ::file::path filepath;

         filepath = path;
         filepath /= pszTemplate;

         ::string strPath = filepath;

         m_iFile = create_tmpfile_cloexec(strPath.get_buffer(strPath.length()));

         strPath.release_buffer();

         if (m_iFile < 0)
            return -1;

         if (ftruncate(m_iFile, size) < 0)
         {
            close();
            return -1;
         }

         return m_iFile;
      }



}//namespace unistd

char * malloc_get_current_dir_name()
{
   
   auto size = pathconf(".", _PC_PATH_MAX);
   
   if(size <= 0)
   {
      
      size = PATH_MAX;
      
   }
   
   char * buf = (char *) malloc(size + 1);
   
   if(buf == nullptr)
   {
    
      return nullptr;
      
   }
   
   auto ptr = getcwd(buf, (size_t)(size + 1));
   
   return ptr;

}


::string current_working_directory()
{
	auto p = malloc_get_current_dir_name();
	::string str(p);
	::free(p);
	
	return str;


}

//#ifdef WINDOWS
//#include <io.h>
//#include <stdio.h>
//#else
//
//#include <sys/stat.h>
////Copy file using mmap()
//#include <sys/mman.h>
//#include <unistd.h>
//#endif
//
//#include <fcntl.h>
//
////
////#define PACKAGE "mmap"
////#include <wchar.h>
////#include <fcntl.h>
//#include <sys/stat.h>
//
//
////void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);
//
//
//int_bool set_file_size_fd(i32 fd, size_t iSize)
//{
//
//   if (ftruncate(fd, iSize) == -1)
//      return false;
//
//   return true;
//
//}
//
//
//::i64 get_file_size(i32 fd)
//{
//
//   struct stat st;
//
//   if (fstat(fd, &st) == -1)
//   {
//
//      ::close(fd);
//
//      return -1;
//
//   }
//
//   return pst->st_size;
//
//}
//
//
//
//int_bool set_file_size(const char * lpszName, size_t iSize)
//{
//
//   i32 fd = ::open(lpszName, O_RDONLY);
//
//   int_bool bSet = ::ensure_file_size_fd(fd, iSize) != -1;
//
//   ::close(fd);
//
//   return bSet;
//
//}
//
//
//int_bool file_system()->exists(const ::file::path & path1)
//{
//
//   // dedicaverse stat -> Sir And Arthur - Cesar Serenato
//
//   struct stat st;
//
//   if (stat(path1, &st))
//   {
//
//      return false;
//
//   }
//
//   if ((pst->st_mode & S_IFDIR))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//int_bool path_system()->is_file_or_dir(const ::file::path & path1, ::file::enum_type * petype)
//{
//
//   struct stat st;
//
//   if (stat(path1, &st))
//   {
//
//      if (is_set(petype))
//      {
//
//         *petype = ::file::e_type_none;
//
//      }
//
//      return false;
//
//   }
//
//   if (is_set(petype))
//   {
//
//      if ((pst->st_mode & S_IFDIR))
//      {
//
//         *petype = ::file::e_type_folder;
//
//      }
//      else
//      {
//
//         *petype = ::file::e_type_file;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//int_bool file_system()->put_contents(const ::file::path & path, const char * contents, ::collection::count len)
//{
//
//   bool bOk = false;
//
//            auto psystem = system();
//
//         auto pacmedirectory = psystem->m_pdirectorysystem;
//
//pacmedirectory->create(::file_path_folder(path));
//
//   wstring wstr(path);
//
//   FILE * file = FILE_open(path, "w+", _SH_DENYWR);
//
//   if (file == nullptr)
//   {
//
//      return false;
//
//   }
//
//   try
//   {
//
//      size_t dwWrite;
//
//      if (len < 0)
//      {
//
//         dwWrite = ansi_length(contents);
//
//      }
//      else
//      {
//
//         dwWrite = len;
//
//      }
//
//      size_t dwWritten = ::fwrite(contents, 1, (u32)dwWrite, file);
//
//      bOk = dwWritten == dwWrite;
//
//   }
//   catch (...)
//   {
//
//
//   }
//
//   ::fclose(file);
//
//   return bOk;
//
//}
//
//
//
//
//string file_system()->as_string(const ::file::path & path, strsize iReadAtMostByteCount)
//{
//
//   string str;
//
//
//   FILE * f = fopen(path, "rb");
//
//   if (f == nullptr)
//      return "";
//
//   ::collection::count iSize = FILE_get_size(f);
//
//   iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);
//
//   char * psz = str.get_buffer(iReadAtMostByteCount);
//
//
//   ::collection::count iRead = fread(psz, 1, iReadAtMostByteCount, f);
//
//   psz[iRead] = '\0';
//
//   str.release_buffer(iRead);
//
//   str.case_insensitive_begins_eat("\xef\xbb\xbf");
//
//   fclose(f);
//
//   return str;
//
//}
//
//string_array file_as_lines(const ::file::path & path, strsize iReadAtMostByteCount)
//{
//
//   string str = file_system()->as_string(path, iReadAtMostByteCount);
//
//   string_array stra;
//
//   stra.add_lines(str);
//
//   return stra;
//
//}
//
//memory file_as_memory(const ::file::path & path, strsize iReadAtMostByteCount)
//{
//
//   memory mem;
//
//   file_as_memory(mem, path, iReadAtMostByteCount);
//
//   return mem;
//
//}
//
//
//bool file_as_memory(memory_base & memory, const ::file::path & path, strsize iReadAtMostByteCount)
//{
//
//   FILE * f = fopen(path, "rb");
//   if (f == nullptr)
//      return false;
//   strsize iSize = FILE_get_size(f);
//
//   if (iSize < 0)
//   {
//
//      ::memory mem;
//
//      mem.set_size(1024 * 16);
//
//      int iRead;
//
//      if (iReadAtMostByteCount >= 0)
//      {
//
//         while ((iRead = (int)fread(mem.get_data(), 1, minimum(iReadAtMostByteCount - memory.get_size(), mem.get_size()), f)) > 0)
//         {
//
//            memory.append(mem.get_data(), iRead);
//
//         }
//
//      }
//      else
//      {
//
//         while ((iRead = (int)fread(mem.get_data(), 1, mem.get_size(), f)) > 0)
//         {
//
//            memory.append(mem.get_data(), iRead);
//
//         }
//
//      }
//
//
//   }
//   else
//   {
//
//      iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);
//
//      memory.set_size(iReadAtMostByteCount);
//
//      fread(memory.get_data(), memory.get_size(), 1, f);
//
//   }
//
//   fclose(f);
//
//   return true;
//
//}
//
//
//memsize file_as_memory(const ::file::path & path, void * p, memsize s)
//{
//
//   FILE * f = fopen(path, "rb");
//
//   if (f == nullptr)
//   {
//
//      return 0;
//
//   }
//
//   memsize sRead = 0;
//
//   try
//   {
//
//      sRead = fread(p, 1, s, f);
//
//   }
//   catch (...)
//   {
//
//   }
//
//   fclose(f);
//
//   return sRead;
//
//}
//
//
//
//
//
//
//filesize file_length_dup(const ::file::path & path)
//{
//
//   struct stat st;
//   stat(path, &st);
//   return pst->st_size;
//
//}
//
//
//
////::file::path file::app_module()
////{
////
////#if defined(ANDROID) || defined(LINUX)
////
////   ::file::path path;
////
////   char * pszModule = nullptr;
////
////   if((pszModule = br_find_exe(nullptr)) == nullptr)
////   {
////
////      if (!br_init_lib(nullptr))
////      {
////
////         char path[PATH_MAX * 4];
////
////         char dest[PATH_MAX * 4];
////
////         pid_t pid = getpid();
////
////         sprintf(path, "/proc/%d/exe", pid);
////
////         auto iSize = readlink(path, dest, PATH_MAX);
////
////         if (iSize > 0)
////         {
////
////            dest[iSize] = '\0';
////
////            pszModule = strdup(dest);
////
////
////         }
////
////      }
////
////   }
////
////   path = pszModule;
////
////   ::free(pszModule);
////
////   return path;
////
////#elif defined(WINDOWS)
////
////   wstring pszModuleFolder(MAX_PATH * 8);
////
////
////   wstring pszModuleFilePath(MAX_PATH * 8);
////
////
////   if (!GetModuleFileNameW(nullptr, pszModuleFilePath, (::u32)pszModuleFilePath.count()))
////
////      return "";
////
////   return string(pszModuleFilePath);
////
////
////#elif defined(__APPLE__)
////
////   return apple_app_module_path();
////
////#endif
////
////}
//
//
//
//
//
//int_bool file_copy_dup(const ::scoped_string & scopedstrNew, const ::scoped_string & scopedstrSrc, int_bool bOverwrite)
//{
//
//   i32 input, output;
//   size_t filesize;
//   void * source, * target;
//
//
//   i32 flags = O_RDWR | O_CREAT | O_TRUNC;
//   if (!bOverwrite)
//      flags |= O_EXCL;
//   if ((output = open(pszNew, flags, 0666)) == -1)
//   {
//      fprintf(stderr, "Error: opening file: %s\n", pszNew);
//      return false;
//   }
//
//
//   if ((input = open(pszSrc, O_RDONLY)) == -1)
//   {
//      fprintf(stderr, "Error: opening file: %s\n", pszSrc);
//      return false;
//   }
//
//
//   filesize = lseek(input, 0, SEEK_END);
//   ftruncate(output, filesize);
//
//   if ((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input, 0)) == (void *)-1)
//   {
//      fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
//      return false;
//   }
//
//
//   if ((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *)-1)
//   {
//      fprintf(stderr, "Error mapping ouput file: %s\n", pszNew);
//      return false;
//   }
//
//   memory_copy(target, source, filesize);
//
//   msync(target, filesize, MS_SYNC);
//
//   munmap(source, filesize);
//   munmap(target, filesize);
//
//   fsync(output);
//
//   close(input);
//   close(output);
//
//   return true;
//
//}
//
//
//
//
//
//int_bool file_is_equal_path_dup(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//   if (case_insensitive_ansi_compare(psz1, psz2) == 0)
//      return true;
//
//   //throw ::exception(::exception(" // TODO: it should follow links "));
//
//   return false;
//
//}
//
//
//CLASS_DECL_ACME string file_get_mozilla_firefox_plugin_container_path()
//{
//   throw ::exception(::exception(" todo "));
//
//   return "";
//
//}
//
//
//
//int_bool file_delete(const ::file::path & path)
//
//{
//
//
//   if (::unlink(pszFileName) == -1)
//
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//
//}
//
//
//
//
//
//int_bool file_path_is_equal(const ::scoped_string & scopedstr1, const ::scoped_string & scopedstr2)
//{
//
//   const i32 iBufSize = MAX_PATH * 8;
//   wstring pwsz1 = utf8_to_unicode(psz1);
//   wstring pwsz2 = utf8_to_unicode(psz2);
//   //   unichar * pwszFile1;
//      // unichar * pwszFile2;
//   ::wide_character * pwszPath1 = ___new ::wide_character[iBufSize];
//   ::wide_character * pwszPath2 = ___new ::wide_character[iBufSize];
//   i32 iCmp = -1;
//   //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
//      // {
//      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
//      //{
//   string path1 = unicode_to_utf8(pwszPath1);
//   string path2 = unicode_to_utf8(pwszPath2);
//   iCmp = case_insensitive_ansi_compare(path1, path2);
//   //}
//   //}
//   delete[] pwszPath1;
//   delete[] pwszPath2;
//   return iCmp == 0;
//
//}
//
//
//
//
//
//
//
//
//
//
//i32 ansi_open(const ::scoped_string & scopedstr, i32 i)
//{
//
//   return open(psz, i);
//
//}
//
//void ansi_get_errno(i32 * perrno)
//{
//   *perrno = errno;
//}
//
//FILE * ansi_fopen(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrMode)
//{
//
//   return fopen(psz, pszMode);
//
//}
//
//
//int ansi_file_flag(int iFlag)
//{
//
//   int i = 0;
//
//   if (iFlag & ::file::e_open_binary)
//   {
//
//      i |= O_BINARY;
//
//   }
//
//   if (iFlag & ::file::e_open_read)
//   {
//
//      if (iFlag & ::file::e_open_write)
//      {
//
//         i |= O_RDWR;
//
//      }
//      else
//      {
//
//         i |= O_RDONLY;
//
//      }
//
//   }
//   else if (iFlag & ::file::e_open_write)
//   {
//
//      i |= O_WRONLY;
//
//   }
//
//   return i;
//
//}
//
//
//void ansi_unlink(const ::scoped_string & scopedstr)
//{
//
//   unlink(psz);
//
//}
//
//
//int_bool is_dir(const ::file::path & path1)
//{
//
//   struct stat st;
//
//   if (stat(path1, &st))
//   {
//
//      return false;
//
//   }
//
//   if (!(pst->st_mode & S_IFDIR))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//
//
//
//
//
//
//
//#ifdef __cplusplus
//
//string file_first_line_dup(const ::string & strPath)
//{
//
//   string line;
//
//   FILE * file = FILE_open(strPath, "r", _SH_DENYNO);
//
//   if (file == nullptr)
//   {
//
//      return "";
//
//   }
//
//   try
//   {
//
//      int c;
//
//      do
//      {
//
//         c = fgetc(file);
//
//         if (c == '\n') break;
//
//         if (c == '\r') break;
//
//         line += (char)c;
//
//      } while (c != EOF);
//
//   }
//   catch (...)
//   {
//
//   }
//
//   fclose(file);
//
//   return line;
//
//}
//
//
//#endif
//
//
//
//


::file::enum_type safe_get_file_system_item_type(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return ::file::e_type_doesnt_exist;

      }

      //fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), iErrNo);

      //throw ::exception(estatus);

      return ::file::e_type_doesnt_exist;

   }

   if (stat.st_mode & S_IFDIR)
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_existent_file;

}



::file::enum_type get_file_system_item_type(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return ::file::e_type_doesnt_exist;

      }

      fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), cerrornumber.m_iErrorNumber);

      throw ::exception(estatus);

      return ::file::e_type_doesnt_exist;

   }

   if (!(stat.st_mode & S_IFDIR))
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_existent_file;

}



bool safe_is_directory(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return false;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return false;

      }

      ///fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), iErrNo);

      //throw ::exception(estatus);

      return false;

   }

   if (!(stat.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


bool is_directory(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return false;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return false;

      }

      fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), cerrornumber.m_iErrorNumber);

      throw ::exception(estatus);

   }

   if (!(stat.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


::file::e_type safe_file_type(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return ::file::e_type_doesnt_exist;

      }

      return ::file::e_type_doesnt_exist;

   }

   if (stat.st_mode & S_IFDIR)
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_existent_file;

}


::file::e_type file_type(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      auto cerrornumber = c_error_number();

      if(cerrornumber.m_iErrorNumber == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return ::file::e_type_doesnt_exist;

      }

      fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), cerrornumber.m_iErrorNumber);

      throw ::file::exception(estatus, cerrornumber, path, ::file::e_open_none, "file_type");

   }

   if (stat.st_mode & S_IFDIR)
   {

      return ::file::e_type_existent_folder;

   }

   return ::file::e_type_existent_file;

}


bool safe_file_exists(const ::file::path & path)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat stat = {};

   if (::stat(path, &stat))
   {

      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return false;

      }
      else if(estatus == error_not_a_directory)
      {

         return false;

      }

      //auto error_code = cerrornumber.error_code();

      //throw ::file::exception(estatus, errorcode, path, ::file::e_open_none, "stat");

      return false;

   }

   if ((stat.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


bool file_exists(const ::file::path & path)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat stat = {};

   if (::stat(path, &stat))
   {

      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.estatus();

      if(estatus == error_file_not_found)
      {

         return false;

      }
      else if(estatus == error_not_a_directory)
      {

         return false;

      }

      auto error_code = cerrornumber.error_code();

      throw ::file::exception(estatus, error_code, path, ::file::e_open_none, "stat");

   }

   if ((stat.st_mode & S_IFDIR))
   {

      return false;

   }

   if ((stat.st_mode & S_IFMT))
   {

      return true;

   }

   return false;

}


//void create_directory_path(const ::file::path & pathParam)
//{
//
//   if (is_directory(pathParam))
//   {
//
//      return ::success_none;
//
//   }
//
//   string strName;
//
//   ::file::path pathDir;
//
//   strsize iLastPos = -1;
//
//   ::file::path_array stra;
//
//   ::file::path path(pathParam);
//
//   path.ascendants_path(stra);
//
//   ::collection::index i = stra.get_upper_bound();
//
//   for (; i >= 0; i--)
//   {
//
//      string strDir = stra[i];
//
//      auto estatus = is_directory(strDir);
//
//      if(estatus)
//      {
//
//         break;
//
//      }
//
//   }
//
//   if (i < 0)
//   {
//
//      return true;
//
//   }
//
//   for (; i < stra.get_count(); i++)
//   {
//
//      string strDir = stra[i];
//
//      auto estatus = create_directory(strDir);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//   }
//
//   return ::success;
//
//}
//
//

void create_directory(const ::file::path & path)
{
   
   auto pszPath = path.c_str();

   if (::mkdir(pszPath, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
   {
      
      auto cerrornumber = c_error_number();

      auto estatus = cerrornumber.estatus();
      
      if(estatus == error_already_exists)
      {
         
//#ifdef DEBUG
//         
//         throw exception(error_already_exists, "Why the program is creating directory if it is alredy a directory");
//         
//#endif
         
         return;
         
      }

      throw ::exception(estatus);

   }

}


void erase_directory(const ::file::path & path)
{


   if (::rmdir(path) != 0)
   {

      auto cerrornumber = c_error_number();

      auto estatus =  cerrornumber.estatus();

      throw ::exception(estatus);

   }

}


void file_delete(const ::file::path & path)
{


   if (::unlink(path) == -1)
   {

      auto cerrornumber = c_error_number();

      auto estatus =  cerrornumber.estatus();

      throw ::exception(estatus);

   }

}


[[noreturn]] CLASS_DECL_ACME void throw_file_errno_exception(const ::file::path & path, ::file::e_open eopen, const ::scoped_string & scopedstr, c_error_number cerrornumber)
{

   if(cerrornumber.m_iErrorNumber == 0)
   {

      cerrornumber.m_iErrorNumber = errno;

   }

   auto estatus =  cerrornumber.estatus();

   auto errorcode = cerrornumber.error_code();

   throw ::file::exception(estatus, errorcode, path, eopen, scopedstr);

}


void copy(::file::file_status * pstatus, const struct stat * pst)
{
    
    pstatus->m_filesize = pst->st_size;

    pstatus->m_attribute = 0;


#if defined(ANDROID) || defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

    ::copy(&pstatus->m_timeModification, &pst->st_mtim);
    ::copy(&pstatus->m_timeAccess, &pst->st_atim);
    ::copy(&pstatus->m_timeCreation, &pst->st_ctim);

#else

    ::copy(&pstatus->m_timeModification, &pst->st_mtimespec);
    ::copy(&pstatus->m_timeAccess, &pst->st_atimespec);
    ::copy(&pstatus->m_timeCreation, &pst->st_ctimespec);

#endif

    if (pstatus->m_timeCreation <= 0_s)
    {
       
       pstatus->m_timeCreation = pstatus->m_timeModification;
       
    }

    if (pstatus->m_timeAccess <= 0_s)
    {
       
       pstatus->m_timeAccess = pstatus->m_timeModification;
       
    }

}


void copy(struct status * pst, const ::file::file_status * pstatus)
{
    
    
}


void std_out_buffer::write(const void * pdata, memsize nCount)
{

//#ifdef WINDOWS
//
//   DWORD dw;
//
//   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (::u32)nCount, &dw, nullptr);
//
//#else

   fwrite(pdata, nCount, 1, stdout);


//#endif

}


::file::path home_folder_path()
{
   
   return getenv("HOME");
   
}



   bool is_directory_accessible(const ::file::path & path)
   {

      return ::access(path, X_OK) == 0;

   }



::file::e_type operating_system_executable_type(const ::file::path & path)
{

      struct stat buff;

      if (stat(path.c_str(), &buff))
      {

         return ::file::e_type_doesnt_exist;

      }

      if(access(path.c_str(), X_OK))
      {

         return ::file::e_type_non_executable;

      }

      return S_ISREG(buff.st_mode) ? ::file::e_type_executable : ::file::e_type_folder2;


}


void operating_system_determine_executable(::file::path & path)
{

   path.m_etype = path.m_etype & (::file::e_type_executable | ::file::e_type_non_executable);

   path.m_etype |= operating_system_executable_type(path);

}



