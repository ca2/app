//
//  file.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 02/10/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "platform.h"
#include "acme/operating_system/shared_posix/c_errno.h"
#include "acme/operating_system/file.h"
#if defined(__APPLE__)
#include <unistd.h>
#endif


::file::path get_current_directory_path()
{
   
#if defined(__GLIBC__)
   
   char * pszCurrentDirectory = ::get_current_dir_name();
   
   if (::is_null(pszCurrentDirectory))
   {

      auto cerrno = c_errno();

      auto estatus = cerrno.failed_estatus();

      throw ::exception(estatus, "get_current_directory_path: get_current_dir_name returned nullptr");

   }

   ::string strCurrentDirectory = ::string_from_strdup(pszCurrentDirectory);
   
   return strCurrentDirectory;
   
#else
   
   char szCurrentDirectory[PATH_MAX * 2];
   
   if (::getcwd(szCurrentDirectory, sizeof(szCurrentDirectory)) == nullptr)
   {

      auto cerrno = c_errno();

      auto estatus = cerrno.failed_estatus();

      throw ::exception(estatus, "get_current_directory_path: get_cwd returned nullptr");

   }
   
   return szCurrentDirectory;
   
#endif
   
}



