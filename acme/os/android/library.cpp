#include "framework.h"
#include <dlfcn.h>


CLASS_DECL_ACME void * __node_library_touch(const char * pszPath, string & strMessage)
{

   return __node_library_open(pszPath, strMessage);

}


CLASS_DECL_ACME void * __node_library_open(const char * pszPath, string & strMessage)
{

   strMessage.Empty();

   string strPath(pszPath);

   if(strPath == "os")
   {

      strPath = "ca2os";

   }
   else if(strPath == "app_sphere")
   {

      strPath = "basesphere";

   }

   if (ansi_find_string(strPath, ".") == nullptr)
   {

      strPath += ".so";

   }

   if (strstr((const char *)strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
   {

      strPath = "lib" + strPath;

   }

   //void * plibrary = dlopen(strPath,RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
   void * plibrary = dlopen(strPath,RTLD_LOCAL | RTLD_NOW);

   if (plibrary != nullptr)
   {

      strMessage += "Successfully loaded library : \"" + strPath +"\"!!";

   }
   else
   {

      int iError = errno;

      const char * psz = strerror(iError);

      const char * psz2 = dlerror();

      strMessage += "Failed to load library : \"" + strPath + "\"!";

      if (psz != nullptr)
      {

         strMessage += "strerror("+__str(iError) +") = " + string(psz);

      }

      if (psz2 != nullptr)
      {

         strMessage += "dlerror = " + string(psz2);

      }

   }

   return plibrary;

}


CLASS_DECL_ACME void * __node_library_open_ca2(const char * pszPath, string & strMessage)
{

   strMessage.Empty();

   //void * plibrary = dlopen(pszPath,RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
   void * plibrary = dlopen(pszPath,RTLD_LOCAL | RTLD_NOW);

   int iError = errno;

   const char * psz = strerror(iError);

   if(psz != nullptr)
   {

      strMessage += psz;

   }

   const char * psz2 = dlerror();

   if(psz2 != nullptr)
   {

      strMessage += psz2;

   }

   return plibrary;

}


CLASS_DECL_ACME bool __node_library_close(void * plibrary)
{

   if(plibrary == nullptr)
      return false;

   return dlclose(plibrary) == 0;

}


CLASS_DECL_ACME void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return dlsym(plibrary,pszEntryName);

}




























