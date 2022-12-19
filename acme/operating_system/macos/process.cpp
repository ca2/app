//
//  process.cpp
//  acme
//
//  Created by Camilo Sasuke on 2021-05-13 18:25 BRT <3ThomasBorregaardSørensen_!!
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <spawn.h>
#include <unistd.h>
#include <mach-o/dyld.h>


::file::path macos_app_path(::acme_directory * pacmedirectory, string strApp)
{

   ::file::path path = pacmedirectory->home() / "Library/papp Support/ca2/mypath" / (strApp + ".txt");

   return pacmedirectory->m_pacmefile->as_string(path);

}

extern char ** environ;

string_array get_c_args_for_c(const scoped_string & str);

string transform_to_c_arg(const scoped_string & str);

int create_process2(const char * _cmd_line, int * pprocessId);





//string apple_app_module_path()
//{
//
//   string str;
//
//   char * psz = str.get_string_buffer(1024);
//
//
//   u32 size = 1024;
//
//   if(_NSGetExecutablePath(psz, &size) == 0)
//
//   {
//
//      str.release_string_buffer();
//
//   }
//   else
//   {
//
//      psz = str.get_string_buffer(size);
//
//
//      if(_NSGetExecutablePath(psz, &size) == 0)
//
//      {
//
//         str.release_string_buffer();
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

CLASS_DECL_ACME bool is_shared_library_busy(u32 processid, const string_array & stra)
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

CLASS_DECL_ACME ::file::path core_app_path(::acme_directory * pacmedirectory, string strApp)
{

   ::file::path path = getenv("HOME");

   path /= "Library/papp Support/ca2/mypath" / strApp;

   path += ".txt";

   return pacmedirectory->m_pacmefile->as_string(path);

}





