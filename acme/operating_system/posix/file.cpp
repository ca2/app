#include "framework.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/file/status.h"


#include "acme/_operating_system.h"


//#ifdef WINDOWS
//#include <io.h>
//#include <stdio.h>
//#else
//
//#include <sys/stat.h>
////Copy file using mmap()
//#include <sys/mman.h>
#include <unistd.h>
//#endif
//
//#include <fcntl.h>
//
////
////#define PACKAGE "mmap"
////#include <wchar.h>
////#include <fcntl.h>
#include <sys/stat.h>
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
//int_bool acmefile()->exists(const ::file::path & path1)
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
//int_bool acmepath()->is_file_or_dir(const ::file::path & path1, ::file::enum_type * petype)
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
//int_bool acmefile()->put_contents(const ::file::path & path, const char * contents, ::count len)
//{
//
//   bool bOk = false;
//
//            auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
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
//string acmefile()->as_string(const ::file::path & path, strsize iReadAtMostByteCount)
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
//   ::count iSize = FILE_get_size(f);
//
//   iReadAtMostByteCount = minimum_non_negative(iSize, iReadAtMostByteCount);
//
//   char * psz = str.get_string_buffer(iReadAtMostByteCount);
//
//
//   ::count iRead = fread(psz, 1, iReadAtMostByteCount, f);
//
//   psz[iRead] = '\0';
//
//   str.release_string_buffer(iRead);
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
//   string str = acmefile()->as_string(path, iReadAtMostByteCount);
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
//   if (ansi_compare_ci(psz1, psz2) == 0)
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
//   ::wide_character * pwszPath1 = memory_new ::wide_character[iBufSize];
//   ::wide_character * pwszPath2 = memory_new ::wide_character[iBufSize];
//   i32 iCmp = -1;
//   //   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
//      // {
//      //  if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
//      //{
//   string path1 = unicode_to_utf8(pwszPath1);
//   string path2 = unicode_to_utf8(pwszPath2);
//   iCmp = ansi_compare_ci(path1, path2);
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

      int iErrNo = errno;

      if(iErrNo == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = errno_status(iErrNo);

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

      return ::file::e_type_folder;

   }

   return ::file::e_type_file;

}



::file::enum_type get_file_system_item_type(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      int iErrNo = errno;

      if(iErrNo == ENOTDIR)
      {

         return ::file::e_type_doesnt_exist;

      }

      auto estatus = errno_status(iErrNo);

      if(estatus == error_file_not_found)
      {

         return ::file::e_type_doesnt_exist;

      }

      fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), iErrNo);

      throw ::exception(estatus);

      return ::file::e_type_doesnt_exist;

   }

   if (!(stat.st_mode & S_IFDIR))
   {

      return ::file::e_type_folder;

   }

   return ::file::e_type_file;

}



bool safe_is_directory(const ::file::path & path)
{

   struct stat stat = {};

   if (::stat(path.c_str(), &stat))
   {

      int iErrNo = errno;

      if(iErrNo == ENOTDIR)
      {

         return false;

      }

      auto estatus = errno_status(iErrNo);

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

      int iErrNo = errno;

      if(iErrNo == ENOTDIR)
      {

         return false;

      }

      auto estatus = errno_status(iErrNo);

      if(estatus == error_file_not_found)
      {

         return false;

      }

      fprintf(stderr, "::is_directory(\"%s\") errno=%d\n", path.c_str(), iErrNo);

      throw ::exception(estatus);

   }

   if (!(stat.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

}


bool safe_file_exists(const ::file::path & path)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat stat = {};

   if (::stat(path, &stat))
   {

      int iErrorNumber = errno;

      auto estatus = errno_status(iErrorNumber);

      if(estatus == error_file_not_found)
      {

         return false;

      }
      else if(estatus == error_not_a_directory)
      {

         return false;

      }

      //auto errorcode = errno_error_code(iErrorNumber);

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

      int iErrorNumber = errno;

      auto estatus = errno_status(iErrorNumber);

      if(estatus == error_file_not_found)
      {

         return false;

      }
      else if(estatus == error_not_a_directory)
      {

         return false;

      }

      auto errorcode = errno_error_code(iErrorNumber);

      throw ::file::exception(estatus, errorcode, path, ::file::e_open_none, "stat");

   }

   if ((stat.st_mode & S_IFDIR))
   {

      return false;

   }

   return true;

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
//   index i = stra.get_upper_bound();
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

   if (::mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
   {
      
      int iErrorNumber = errno;

      auto estatus = errno_status(errno);
      
      if(estatus == error_already_exists)
      {
         
#ifdef DEBUG
         
         throw exception(error_failed, "Why the program is creating directory if it is alredy a directory");
         
#endif
         
         return;
         
      }

      throw ::exception(estatus);

   }

}


void erase_directory(const ::file::path & path)
{


   if (::rmdir(path) != 0)
   {

      auto estatus =  errno_status(errno);

      throw ::exception(estatus);

   }

}


void file_delete(const ::file::path & path)
{


   if (::unlink(path) == -1)
   {

      auto estatus = errno_status(errno);

      throw ::exception(estatus);

   }

}


[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::file::path & path, ::file::e_open eopen, const ::scoped_string & scopedstr, int iErrNo)
{

   if (iErrNo == 0)
   {

      iErrNo = errno;

   } 

   auto estatus = errno_status(iErrNo);

   auto errorcode = errno_error_code(iErrNo);

   throw ::file::exception(estatus, errorcode, path, eopen, scopedstr);

}


void copy(::file::file_status * pstatus, const struct stat * pst)
{
    
    pstatus->m_filesize = pst->st_size;

    pstatus->m_attribute = 0;


#if defined(ANDROID) || defined(LINUX)

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



