#include "framework.h"
//#include "apex/platform/app_core.h"




//CLASS_DECL_APEX string get_command_line()
//{
//
//   return get_command_line_string();
//
//}


//
//
//
//CLASS_DECL_APEX void set_command_line_dup(const ::scoped_string & scopedstr)
//{
//
//   get_command_line_string() = psz;
//
//   ::file::path pathFolder = ::dir::program_data();
//
//   string strAppId = get_command_line_parameter(psz, "app");
//
//   if (strAppId.has_character())
//   {
//
//      pathFolder /= strAppId;
//
//      ::file::path path = pathFolder / "last_command_line.txt";
//
//      file_system()->put_contents(path, get_command_line_string());
//
//      ::file::path pathExecutable = consume_command_line_parameter(psz, nullptr);
//
//      string strAppTitle = executable_title_from_appid(strAppId);
//
//      path = pathFolder / "last_executable.txt";
//
//      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
//      {
//
//         file_system()->put_contents(path, pathExecutable);
//
//      }
//
//   }
//
//}

//
//CLASS_DECL_APEX void get_command_line(char * psz, int iBuffer)
//{
//
//   strncpy(psz, get_command_line(), iBuffer);
//
//}








