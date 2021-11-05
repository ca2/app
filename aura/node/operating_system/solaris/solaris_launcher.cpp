#include "framework.h"

#undef USE_MISC



bool launcher::start()
{

   if(!ensure_executable())
      return false;

   vsstring strPath(get_executable_path());
   vsstring strDir(::file_path_folder(strPath));


    /*vsstring strPath

   SHELLEXECUTEINFOA infoa;

   __memset(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.lpFile         = strPath;
   infoa.lpDirectory    = strDir;*/

    execlp(strPath, strPath, (char *) 0);

   return true;

}
