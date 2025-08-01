#include "framework.h"
//#include "acme/operating_system/_.h"
#include "acme/operating_system/_os.h"
#include <dlfcn.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <sys/types.h> // for jl_raise_debugger
#elif !defined(_OS_WINDOWS_)
#include <link.h>
#endif

void * __node_library_touch(const ::file::path & path, string & strMessage)
{

   for (int i = _dyld_image_count(); i >= 0 ; i--)
   {

      const char *image_name = _dyld_get_image_name(i);

      if(::file::path(image_name).title().case_insensitive_order(::file::path(scopedstrPath).title()) == 0)
      {

         goto found;

      }

      if(::file::path(image_name).title().case_insensitive_order(("lib" + ::file::path(scopedstrPath).title())) == 0)
      {

         goto found;

      }

   }

   return nullptr;
found:
   return __node_library_open(scopedstrPath, strMessage);

}


void * __node_library_open(const ::file::path & path, string & strMessage)
{

   strMessage.empty();

   string strPath(scopedstrPath);

   string strError;

   ::file::path path;

   if(!ansi_ends(strPath, ".dylib"))
   {

      strPath += ".dylib";

   }

   if(strPath.find('/') < 0 && !ansi_begins(strPath, "lib"))
   {

      strPath = "lib" + strPath;

   }

   informationf("\n\nGoing to dlopen: \"" + strPath + "\"");

   path = ::file::path(::get_exe_path()).folder() / strPath;

   informationf("\nFirst path to try: \"" + path + "\"");

   void * plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(1) dlopen: " + path + " with the error: \"" + strError + "\"";

   path = strPath;

   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(2) dlopen: " + path + " with the error: \"" + strError + "\"";

   path = ::file::path(::dir::ca2_module()) / strPath;

   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(3) dlopen: " + path + " with the error: \"" + strError + "\"";

   if(strPath.find('/') >= 0)
   {

      path = ::file::path(strPath).name();

      plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

      if(plibrary != nullptr)
      {

         goto finished;

      }

      strError = dlerror();

      strMessage += "\n(4) dlopen: " + path + " with the error: \"" + strError + "\"";

   }

finished:

   if(plibrary != nullptr)
   {

      strMessage = "__node_library_open (1) Succeeded " + path;

   }
   else
   {

      strMessage = "__node_library_open : Failed with : " + strMessage;

   }

   informationf("\n" + strMessage + "\n\n");

   return plibrary;

}


bool __node_library_close(void * plibrary)
{

   if(plibrary != nullptr)
   {

      dlclose(plibrary);

   }

   return true;

}


void * __node_library_raw_get(void * plibrary, const ::scoped_string & scopedstrElement)
{

   return dlsym(plibrary, pszElement);

}






void * __node_library_open_ca2(const ::file::path & path, string & strMessage)
{

   string strPath(scopedstrPath);
   
   if(!strPath.case_insensitive_begins("lib"))
   {
      
      strPath = "lib" + strPath;
      
   }

   if(!strPath.case_insensitive_ends(".dylib"))
   {
      
      strPath += ".dylib";
      
   }

   void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      strMessage = "__node_library_open_ca2 Succeeded " + strPath;

   }
   else
   {

      string strError;

      strError = dlerror();

      strMessage = "__node_library_open_ca2 : " + strPath + " with the error: \"" + strError + "\"";

   }

   informationf("\n\n" + strMessage + "\n\n");

   return plibrary;

}


