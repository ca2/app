#include "framework.h"
#include "acme/operating_system/android/_android.h"
#include "_android.h"

#include <sys/file.h>


// gone to ansios_file.cpp/.h
/*

//#include <sys/stat.h>


void fd_set_size(int fd, long long iSize)
{

   if(ftruncate(fd, iSize) == -1)
      throw ::exception(::exception("fd_set_size exception"));

}


long long fd_get_file_size(int fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}

*/




//CLASS_DECL_ACME void dll_processes(unsigned_int_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrDll)
//{
//
//
//
//}



//::file::path dir::sys_temp()
//{
//
//   return ::file::path(getenv("HOME")) /  ".acme" / "time";
//
//}
//
//
//
//::file::path dir::home()
//{
//
//   //return getenv("HOME");
//   return "/data/home";
//
//}
//
//
//// ::file::path dir::bookmark()
//// {
//
////    return          auto psystem = system();
//
//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->localconfig() / "favorites";
//
//// }


bool __node_further_file_is_equal(const ::file::path &, const ::file::path &)
{

   return false;

}





// The lockf() function is not available on Android; we translate to flock().
//#define F_LOCK LOCK_EX
//#define F_ULOCK LOCK_UN
int lockf(int fd, int cmd, off_t ignored_len) 
{
   
   return ::flock(fd, cmd);

}


 CLASS_DECL_ACME bool _os_may_have_alias(const ::scoped_string & scopedstr)
 {

    return true;

 }



//
//extern "C"
//void android_set_cache_dir(const ::scoped_string & scopedstrDir)
//{
//
//   ::acmeacmesystem()->m_pathCacheDir = pszDir;
//
//}
//
//extern "C"
//const_char_pointer android_get_cache_dir()
//{
//
//   return ::acmeacmesystem()->m_pathCacheDir;
//
//}





CLASS_DECL_ACME ::file::path get_home_config_folder_path()
{

   auto pathHomeConfigFolder = ::system()->m_pathCacheDirectory / ".config";

   return pathHomeConfigFolder;

}

