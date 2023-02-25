#include "framework.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
#include "_android.h"
#include <dlfcn.h>


namespace acme
{


   void * system::operating_system_library_touch(const ::file::path & path, string & strMessage)
   {

      return operating_system_library_open(path, strMessage);

   }


   void * system::operating_system_library_open(const ::file::path & path, string & strMessage)
   {

      strMessage.empty();

      string strPath(path);

      if (strPath == "os")
      {

         strPath = "ca2os";

      }
      else if (strPath == "app_sphere")
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
      void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW);

      if (plibrary != nullptr)
      {

         strMessage += "Successfully loaded library : \"" + strPath + "\"!!";

      }
      else
      {

         int iError = errno;

         const char * psz = strerror(iError);

         const char * psz2 = dlerror();

         strMessage += "Failed to load library : \"" + strPath + "\"!";

         if (psz != nullptr)
         {

            strMessage += "strerror(" + ::as_string(iError) + ") = " + string(psz);

         }

         if (psz2 != nullptr)
         {

            strMessage += "dlerror = " + string(psz2);

         }

      }

      return plibrary;

   }


   void * system::operating_system_library_open_ca2(const ::file::path & path, string & strMessage)
   {

      strMessage.empty();

      //void * plibrary = dlopen(pszPath,RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
      void * plibrary = dlopen(path, RTLD_LOCAL | RTLD_NOW);

      int iError = errno;

      const char * psz = strerror(iError);

      if (psz != nullptr)
      {

         strMessage += psz;

      }

      const char * psz2 = dlerror();

      if (psz2 != nullptr)
      {

         strMessage += psz2;

      }

      return plibrary;

   }


   bool system::operating_system_library_close(void * plibrary)
   {

      if (plibrary == nullptr)
         return false;

      return dlclose(plibrary) == 0;

   }


   void * system::operating_system_library_raw_get(void * plibrary, const ::scoped_string & scopedstrEntryName)
   {

      return dlsym(plibrary, scopedstrEntryName);

   }


} // namespace acme



