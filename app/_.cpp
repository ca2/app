#include "framework.h"
#include "acme/_library.h"


extern "C" const char * app_app_version()
{

#include "version.txt"

   return pszVersion;

}




