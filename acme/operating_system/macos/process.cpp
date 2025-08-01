//
//  process.cpp
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 18:25 BRT <3ThomasBorregaardSorensen_!!
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <unistd.h>
#include <mach-o/dyld.h>


::file::path macos_app_path(::directory_system * pdirectorysystem, string strApp)
{

   ::file::path path = pdirectorysystem->home() / "Library/papp Support/ca2/mypath" / (strApp + ".txt");

   return pdirectorysystem->m_pfilesystem->as_string(path);

}

extern char ** environ;

string_array get_c_args_for_c(const ::scoped_string & scopedstr);

string transform_to_c_arg(const ::scoped_string & scopedstr);

int create_process2(const_char_pointer  _cmd_line, int * pprocessId);





//string apple_app_module_path()
//{
//
//   string str;
//
//   char * psz = str.get_buffer(1024);
//
//
//   unsigned int size = 1024;
//
//   if(_NSGetExecutablePath(scopedstr, &size) == 0)
//
//   {
//
//      str.release_buffer();
//
//   }
//   else
//   {
//
//      psz = str.get_buffer(size);
//
//
//      if(_NSGetExecutablePath(scopedstr, &size) == 0)
//
//      {
//
//         str.release_buffer();
//
//      }
//      else
//      {
//
//         return "";
//
//      }
//
//   }
//
//
//   return str;
//
//}

CLASS_DECL_ACME bool is_shared_library_busy(unsigned int processid, const string_array & stra)
{

   return false;

}


CLASS_DECL_ACME bool is_shared_library_busy(const string_array & stra)
{

   return false;

}

//void os_term_application()
//{
////
////   ns_app_terminate();
////
//}
//

CLASS_DECL_ACME ::file::path core_app_path(::directory_system * pdirectorysystem, string strApp)
{

   ::file::path path = getenv("HOME");

   path /= "Library/papp Support/ca2/mypath" / strApp;

   path += ".txt";

   return pdirectorysystem->m_pfilesystem->as_string(path);

}





