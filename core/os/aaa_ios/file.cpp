//
//  c_os_file.cpp
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 1/14/12.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"

char * ns_get_executable_path();

CLASS_DECL_CORE void dll_processes(u32_array & dwa, string_array & straProcesses, const ::string & pszDll)
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
   
   return ::dir::module() / "time";
   
}




string apple_app_module_path()
{
   
   return ::str::from_strdup(ns_get_executable_path());
   
}
