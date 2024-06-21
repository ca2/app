// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/platform/system.h"
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <sys/types.h>

namespace ios
{


namespace nano
{


namespace dynamic_library
{


dynamic_library::dynamic_library()
{
   
}


dynamic_library::~dynamic_library()
{
   
   
}


library_t *__dl_______touch(const      char  ** image_name)




{
   
   
   
}

::file::path dynamic_library::module_path(library_t * plibrary)
{
   
   for (i32 i = _dyld_image_count(); i >= 0 ; i--)
   {
      ::string strMessage;
      
      ::string strMessage;
      
      const char *image_name = _dyld_get_image_name(i);
      auto p = open(image_name, strMessage);
      if(::is_set(p))
      {
         close(p);
         if(p ==     plibrary)
         {
            
            return image_name;
            
         }
         
      }
      
   }
   
   return {};
   
}


library_t * dynamic_library::module_by_name(const ::file::path & path, string & strMessage)
{
   
   auto strTitle = path.title();
   
   auto strLibTitle = "lib" + strTitle;
   
   for (i32 i = _dyld_image_count(); i >= 0 ; i--)
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
   
   auto p = open(path, strMessage);
   
   close(p);
   
   return p;
   
}


library_t * dynamic_library::module_by_path(const ::file::path & path, string & strMessage)
{
   
   
   for (i32 i = _dyld_image_count(); i >= 0 ; i--)
   {
      
      const char *image_name = _dyld_get_image_name(i);
      
      if(acmepath()->real_path_is_equal(image_name, path))
      {
         
         goto found;
         
      }
      
   }
   
   return nullptr;
   
found:
   
   auto p = open(path, strMessage);
   
   close(p);
   
   return p;
   
}


library_t * dynamic_library::open(const ::file::path & pathParam, string & strMessage)
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
   
   //::acme::get()->platform()->informationf("\n\nGoing to dlopen: \"" + strPath + "\"");
   
   auto pathModuleFolder = ::get_module_folder();
   
   path = pathModuleFolder / strPath;
   
   //::acme::get()->platform()->informationf("\nFirst path to try: \"" + path + "\"");
   
   auto plibrary = (library_t *) dlopen(path, RTLD_LOCAL | RTLD_LAZY);
   
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
         
         ::acme::get()->platform()->informationf("\n" + strMessage + "\n\n");
         
      }
      
   }
   else
   {
      
      strMessage = "__node_library_open : Failed with : " + strMessage;
      
      ::acme::get()->platform()->informationf("\n" + strMessage + "\n\n");
      
   }
   
   return plibrary;
   
}


bool dynamic_library::::operating_system_library_close(library_t * plibrary)
{
   
   if(plibrary != nullptr)
   {
      
      dlclose(plibrary);
      
   }
   
   return true;
   
}


void * dynamic_library::raw_get(library_t * plibrary, const ::scoped_string & scopedstrSymbol)
{
   
   return dlsym(plibrary, scopedstrSymbol);
   
}


library_t * dynamic_library::open_on_context(const ::file::path & pathParam, string & strMessage)
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
   
   auto plibrary = (library_t *) dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
   
   if(plibrary != nullptr)
   {
      
      strMessage = "__node_library_open_ca2 Succeeded " + strPath;
      
      if(has_verbose_flag())
      {
         
         ::acme::get()->platform()->informationf("\n\n" + strMessage + "\n\n");
         
      }
      
   }
   else
   {
      
      string strError;
      
      strError = dlerror();
      
      strMessage = "__node_library_open_ca2 : " + strPath + " with the error: \"" + strError + "\"";
      
      ::acme::get()->platform()->informationf("\n\n" + strMessage + "\n\n");
      
   }
   
   return plibrary;
   
}



} // namespace dynamic_library


} // namespace nano



} // namespace ios
