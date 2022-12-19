#include "framework.h"
#include "_freebsd.h"
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



//bool context::_os_resolve_alias(::file::path & path, const scoped_string & str, ::user::primitive * pprimitive, bool bNoUI, bool bNoMount)
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


// CLASS_DECL_ACME bool context::os_resolve_alias(::file::path & path, const scoped_string & str, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



CLASS_DECL_ACME bool _os_may_have_alias(const scoped_string & str)
{

   return true;

}


namespace path
{


   ::file::path module()
   {

      // https://arstechnica.com/civis/viewtopic.php?t=433790

      char exepath[PATH_MAX];

      char temp[PATH_MAX];

      ::snprintf(temp, sizeof(temp),"/proc/%d/file", ::getpid());

      ::realpath(temp, exepath);
      // end https://arstechnica.com/civis/viewtopic.php?t=433790

      return exepath;

   }


} // namespace path


char * get_current_dir_name()
{

    return getcwd(nullptr, 0);

}



