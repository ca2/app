#include "framework.h"
//#include "uwp.h"

bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());

   string strDir(dir::name(strPath));

   string strParams = get_params();

#ifdef _UWP

   __throw(::exception::exception("todo"));

#else

   call_async(strPath, strParams, strDir, SW_HIDE);

#endif

   return true;

}

