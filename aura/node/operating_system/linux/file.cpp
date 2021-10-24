#include "framework.h"
#include "_linux.h"



string get_sys_temp_path()
{

   return ::file::path(getenv("HOME")) / ".ca2" / "time";

}



bool __node_further_file_is_equal(const ::file::path &,  const ::file::path &)
{

   return false;

}



//bool context::_os_resolve_alias(::file::path & path, const ::string & psz, ::user::primitive * pprimitive, bool bNoUI, bool bNoMount)
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


// CLASS_DECL_AURA bool context::os_resolve_alias(::file::path & path, const ::string & psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
// {

//    return _os_resolve_alias(path, psz, bNoUI, bNoMount);

// }



CLASS_DECL_AURA bool _os_may_have_alias(const ::string & psz)
{

   return true;

}


//CLASS_DECL_AURA bool context::os_is_alias(const ::string & path)
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
