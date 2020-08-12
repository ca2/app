#ifdef WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

char* g_pszDirSystem = NULL;

#ifdef _WIN32
__declspec(dllexport)
#endif
void winpr_set_dir_system(char* psystem)
{

   g_pszDirSystem = psystem;

}

#ifdef WIN32
__declspec(dllexport)
#endif
char* winpr_dir_system()
{

   return g_pszDirSystem;

}