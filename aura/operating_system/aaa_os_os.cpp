#include "framework.h"
#include "apex/platform/app_core.h"


extern ::app_core * g_pappcore;


CLASS_DECL_AURA string & get_command_line_string()
{

   return ::g_pappcore->m_strCommandLine;

}


CLASS_DECL_AURA string get_command_line()
{

   return get_command_line_string();

}





CLASS_DECL_AURA void set_command_line_dup(const ::string & psz)
{

   get_command_line_string() = psz;

   ::file::path pathFolder = ::dir::program_data();

   string strAppId = get_command_line_param(psz, "app");

   if (strAppId.has_char())
   {

      pathFolder /= strAppId;

      ::file::path path = pathFolder / "last_command_line.txt";

      m_psystem->m_pacmefile->put_contents(path, get_command_line_string());

      ::file::path pathExecutable = consume_param(psz, nullptr);

      string strAppTitle = executable_title_from_appid(strAppId);

      path = pathFolder / "last_executable.txt";

      if (file_is_equal_path_dup(pathExecutable.title(), strAppTitle))
      {

         m_psystem->m_pacmefile->put_contents(path, pathExecutable);

      }

   }

}


CLASS_DECL_AURA void get_command_line(char * psz, int iBuffer)
{

   strncpy(psz, get_command_line(), iBuffer);

}








