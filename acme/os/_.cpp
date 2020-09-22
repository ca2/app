//
//  _.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/09/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"

string g_strCommandLine;

CLASS_DECL_ACME string & get_command_line_string()
{

   return g_strCommandLine;

}


CLASS_DECL_ACME string get_command_line_dup()
{

   return get_command_line_string();

}





CLASS_DECL_ACME void set_command_line_dup(const char * psz)
{

   get_command_line_string() = psz;

   ::file::path pathFolder = ::dir::program_data();

   string strAppId = get_command_line_param(psz, "app");

   if (strAppId.has_char())
   {

      pathFolder /= strAppId;

      ::file::path path = pathFolder / "last_command_line.txt";

      file_put_contents_dup(path, get_command_line_string());

      ::file::path pathExecutable = consume_param(psz, nullptr);

      string strAppTitle = executable_title_from_appid(strAppId);

      path = pathFolder / "last_executable.txt";

      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
      {

         file_put_contents_dup(path, pathExecutable);

      }

   }

}


CLASS_DECL_ACME void get_command_line_dup(char * psz, int iBuffer)
{

   strncpy(psz, get_command_line_dup(), iBuffer);

}








