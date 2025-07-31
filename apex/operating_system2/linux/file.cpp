#include "framework.h"
#include "acme/filesystem/filesystem/path.h"



string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}



bool __node_further_file_is_equal(const ::file::path &,  const ::file::path &)
{

   return false;

}



//bool context::_os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pprimitive, bool bNoUI, bool bNoMount)
//{
//
//    if(::is_null(scopedstr))
//    {
//
//        return false;
//
//    }
//
//
//
//
//   char * pszRealPath = ::realpath(scopedstr, NULL);
//
//   if(scopedstrRealPath == NULL)
//   {
//
//      return false;
//
//   }
//
//   if(strcmp(scopedstr, pszRealPath) == 0)
//   {
//
//    ::free(scopedstrRealPath);
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
//   ::free(scopedstrRealPath);
//
//   return true;
//
//}
//


// CLASS_DECL_APEX bool context::os_resolve_alias(::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



CLASS_DECL_APEX bool _os_may_have_alias(const ::scoped_string & scopedstr)
{

   return true;

}


//CLASS_DECL_APEX bool context::os_is_alias(const ::file::path & path)
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
