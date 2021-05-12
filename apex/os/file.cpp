//
//  c_os_file.cpp
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 1/14/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"



CLASS_DECL_APEX void dll_processes(u32_array & dwa, string_array & straProcesses, const char * pszDll)
{



}


::file::path dir::home()
{

   return getenv("HOME");

}

//::file::path dir::ca2_user()
//{
//
//    return ::file::path(getenv("HOME")) / "Library/ca2";
//
//}

::file::path dir::sys_temp()
{

   return ca2roaming() / "time";

}


char * ns_resolve_alias(const char * psz, bool bNoUI, bool bNoMount);


#ifndef __APPLE__

bool context::_os_resolve_alias(::file::path & path, const char * psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
{

   char * pszTarget = ns_resolve_alias(psz, bNoUI, bNoMount);

   if(::is_null(pszTarget))
   {

      return false;

   }

   path = ::str::from_strdup(pszTarget);

   return true;

}

#endif

//
//CLASS_DECL_APEX bool _os_resolve_alias(::object * pobject, ::file::path & path, const char * psz, ::user::primitive * pinteraction, bool bNoUI, bool bNoMount)
//{
//
//   return _os_resolve_alias(path, psz, pinteraction, bNoUI, bNoMount);
//
//}


CLASS_DECL_APEX bool _os_may_have_alias(const char * psz)
{

   return true;

}


bool os_is_folder_alias(const char * psz, bool bNoUI, bool bNoMount)
{

   char * pszTarget = ns_resolve_alias(psz, bNoUI, bNoMount);

   if(::is_null(pszTarget))
   {

      return false;

   }

   ::file::path path = ::str::from_strdup(pszTarget);

   return is_dir(path);

}


#ifndef __APPLE__


bool os_is_alias(const char * path);


bool context::os_is_alias(const char * path)
{

   return ::os_is_alias(path);
   
}


#endif



