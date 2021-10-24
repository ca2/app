#include "framework.h"


bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());
   
   string strDir(::file_path_folder(strPath));

   string strParams = get_params();



   call_async(strPath, strParams, strDir, e_display_none, m_bPrivileged);

   return true;

}