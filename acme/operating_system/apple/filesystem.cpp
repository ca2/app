//
//  ns_exe_path.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 8/3/15.
//
//
#include "framework.h"
#include <mach-o/dyld.h>


string apple_app_module_folder();
string apple_app_module_path();


char * ns_get_executable_path();


string get_exe_path()
{
   
   char path[8192];

   u32 size = sizeof(path);

   if (_NSGetExecutablePath(path, &size) == 0)
   {
      
      //printf("executable path is %s\n", path);
      
   }
   else
   {

      //printf("buffer too small; need size_i32 %u\n", size);
      
   }
//                     strPath += ".app/Contents/MacOS/app";

   return path;

}



string apple_app_module_folder()
{

   auto strPath = apple_app_module_path();

   return file_path_folder(strPath);

}


string apple_app_module_path()
{

   return ::string_from_strdup(ns_get_executable_path());

}



