//
//  c_os_file.cpp
//  c
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 1/14/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"



CLASS_DECL_APEX void dll_processes(unsigned_int_array & dwa, string_array & straProcesses, const ::scoped_string & scopedstrDll)
{



}


//::file::path dir::home()
//{
//
//   return getenv("HOME");
//
//}

//::file::path dir::ca2_user()
//{
//
//    return ::file::path(getenv("HOME")) / "Library/ca2";
//
//}
//
//::file::path dir::sys_temp()
//{
//
//   return ca2roaming() / "time";
//
//}



//
//CLASS_DECL_APEX bool _os_resolve_alias(::particle * pparticle, ::file::path & path, const ::scoped_string & scopedstr, ::user::interaction_base * pinteraction, bool bNoUI, bool bNoMount)
//{
//
//   return _os_resolve_alias(path, psz, pinteraction, bNoUI, bNoMount);
//
//}


CLASS_DECL_APEX bool _os_may_have_alias(const ::scoped_string & scopedstr)
{

   return true;

}

//
//bool os_is_folder_alias(const ::scoped_string & scopedstr, bool bNoUI, bool bNoMount)
//{
//
//   char * pszTarget = ns_resolve_alias(psz, bNoUI, bNoMount);
//
//   if(::is_null(pszTarget))
//   {
//
//      return false;
//
//   }
//
//   ::file::path path = ::string_from_strdup(pszTarget);
//
//   return is_dir(path);
//
//}


#ifndef __APPLE__


bool os_is_alias(const ::file::path & path);


bool context::os_is_alias(const ::file::path & path)
{

   return ::os_is_alias(path);
   
}


#endif



