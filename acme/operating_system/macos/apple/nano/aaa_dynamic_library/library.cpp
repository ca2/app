#include "framework.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/system.h"
#include <dlfcn.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <sys/types.h> // for jl_raise_debugger
#elif !defined(_OS_WINDOWS_)
#include <link.h>
#endif


string apple_app_module_folder();
::file::path get_module_folder();

namespace platform
{

//void * __node_library_open(const ::file::path & path, string & strMessage);


void * platform::operating_system_library_touch(const ::file::path & path, string & strMessage)
{
   
   auto strTitle = path.title();
   
   auto strLibTitle = "lib" + strTitle;

   for (int i = _dyld_image_count(); i >= 0 ; i--)
   {

      const char *image_name = _dyld_get_image_name(i);

      if(::file_path_title(image_name).case_insensitive_equals(strTitle))
      {

         goto found;

      }

      if(::file_path_title(image_name).case_insensitive_equals(strLibTitle))
      {

         goto found;

      }

   }

   return nullptr;
   
found:
   
   return operating_system_library_open(path, strMessage);

}


void * platform::operating_system_library_open(const ::file::path & pathParam, string & strMessage)
{

   strMessage.empty();

   string strPath(pathParam);

   string strError;

   ::file::path path;

   if(!ansi_ends(strPath, ".dylib"))
   {

      strPath += ".dylib";

   }

   if(!strPath.contains('/') && !strPath.case_insensitive_begins("lib"))
   {

      strPath = "lib" + strPath;

   }

   //informationf("---->  Going to dlopen: \"" + strPath + "\"");
   
   auto pathModuleFolder = ::get_module_folder();

   path = pathModuleFolder / strPath;

   //informationf("----> First path to try: \"" + path + "\"");

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

   path = ::file::path(apple_app_module_folder()) / strPath;

   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(3) dlopen: " + path + " with the error: \"" + strError + "\"";

   if(strPath.contains('/'))
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

      strMessage = "__node_library_open Succeeded " + pathParam;
      
      if(has_verbose_flag())
      {
         
         informationf("----> " + strMessage + "\n\n");
         
      }

   }
   else
   {

      strMessage = "__node_library_open : Failed with : " + strMessage;
      
      informationf("----> " + strMessage + "\n\n");

   }

   return plibrary;

}


bool platform::operating_system_library_close(void * plibrary)
{

   if(plibrary != nullptr)
   {

      dlclose(plibrary);

   }

   return true;

}


void * platform::operating_system_library_raw_get(void * plibrary, const ::scoped_string & scopedstrSymbol)
{

   return dlsym(plibrary, scopedstrSymbol);

}


void * platform::operating_system_library_open_ca2(const ::file::path & pathParam, string & strMessage)
{

   string strPath(pathParam);
   
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

      if(has_verbose_flag())
      {
         
         informationf("---->  " + strMessage + "\n\n");
         
      }
      
   }
   else
   {

      string strError;

      strError = dlerror();

      strMessage = "__node_library_open_ca2 : " + strPath + " with the error: \"" + strError + "\"";

      informationf("---->  " + strMessage + "\n\n");

   }

   return plibrary;

}


} // namespace acme
