#include "framework.h"
//#include "universal_windows.h"

bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());

   string strDir(::file_path_folder(strPath));

   string strParams = get_params();

#ifdef _UWP

   throw ::exception(::exception("todo"));

#else

   call_async(strPath, strParams, strDir, SW_HIDE);

#endif

   return true;

}

