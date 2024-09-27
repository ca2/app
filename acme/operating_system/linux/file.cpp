#include "framework.h"
//#include "acme/filesystem/filesystem/path.h"
//#include "_linux.h"
#include "acme/operating_system/ansi/binreloc.h"
#include <unistd.h>


string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}



bool __node_further_file_is_equal(const ::file::path &,  const ::file::path &)
{

   return false;

}



//bool context::_os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::prototype * pprimitive, bool bNoUI, bool bNoMount)
//{
//
//    if(::is_null(psz))
//    {
//
//        return false;
//
//    }
//
//
//
//
//   char * pszRealPath = ::realpath(psz, NULL);
//
//   if(pszRealPath == NULL)
//   {
//
//      return false;
//
//   }
//
//   if(strcmp(psz, pszRealPath) == 0)
//   {
//
//    ::free(pszRealPath);
//
//    return false;
//
//   }
//
//   try
//   {
//
//      path = pszRealPath;
//
//   }
//   catch(...)
//   {
//
//   }
//
//   ::free(pszRealPath);
//
//   return true;
//
//}
//


// CLASS_DECL_ACME bool context::os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::prototype * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



CLASS_DECL_ACME bool _os_may_have_alias(const ::scoped_string & scopedstr)
{

   return true;

}


//CLASS_DECL_ACME bool context::os_is_alias(const ::file::path & path)
//{
//
//    if(is_null(path))
//    {
//
//        return false;
//
//    }
//
//    struct stat st;
//
//    if(lstat(path, &st) == -1)
//    {
//
//        return false;
//
//    }
//
//    if (S_ISLNK(st.st_mode))
//    {
//
//        return true;
//
//    }
//
//    return false;
//
//}


namespace path
{


   ::file::path module()
   {

      char *pszModuleFilePath = nullptr;

#if defined(__APPLE__)

      pszModuleFilePath = ns_get_executable_path();

#else

      pszModuleFilePath = br_find_exe("app");

#endif

      if (pszModuleFilePath == nullptr)
      {

         return "";

      }

      string strModuleFileName(pszModuleFilePath);

      free(pszModuleFilePath);

      return strModuleFileName;

   }


} // namespace path


::file::path get_module_path()
{

   ::file::path path;

   char *pszModule = nullptr;

   if ((pszModule = br_find_exe(nullptr)) == nullptr)
   {

      if (!br_init_lib(nullptr)) {

         char path[PATH_MAX * 4];

         char dest[PATH_MAX * 4];

         pid_t pid = getpid();

         sprintf(path, "/proc/%d/exe", pid);

         auto iSize = readlink(path, dest, PATH_MAX);

         if (iSize > 0) {

            dest[iSize] = '\0';

            pszModule = strdup(dest);

         }

      }

   }

   path = pszModule;

   ::free(pszModule);

   return path;

}



