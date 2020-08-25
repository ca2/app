#include "framework.h"
#undef USE_MISC



bool launcher::start()
{

   if(!ensure_executable())
      return false;

   string strPath(get_executable_path());
   string strDir(dir::name(strPath));
    

    /*vsstring strPath

   SHELLEXECUTEINFOA infoa;

   __memset(&infoa, 0, sizeof(infoa));

   infoa.cbSize         = sizeof(infoa);
   infoa.pFile         = strPath;

   infoa.pDirectory    = strDir;*/


    execlp(strPath, strPath, (char *) 0);

   return true;

}