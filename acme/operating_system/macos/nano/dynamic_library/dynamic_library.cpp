// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/platform/system.h"
#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <mach-o/nlist.h>
#include <sys/types.h> // for jl_raise_debugger
//#include <link.h>


string apple_app_module_folder();


namespace macos
{



   namespace operating_system
   {


      dynamic_library::dynamic_library()
      {
         
      }


      dynamic_library::~dynamic_library()
      {
         
         
      }

      ::file::path dynamic_library::module_path(library_t * plibrary)
      {
         
         for (int i = _dyld_image_count(); i >= 0 ; i--)
         {
            
            ::string strMessage;
            
            const_char_pointer image_name = _dyld_get_image_name(i);
            
            auto p = open(image_name, strMessage);
            
            close(p);
            
            if(p == plibrary)
            {
             
               return image_name;
               
            }

         }
         
         return nullptr;
         
      }


      library_t * dynamic_library::module_by_name(const ::scoped_string & scopedstr)
      {
         
         ::file::path path;
         
         ::string strTitle = ::file::path(scopedstr).title();
         
         strTitle.case_insensitive_begins_eat("lib");
         
         ::string strLibTitle = strTitle;
         
         strLibTitle = "lib" + strLibTitle;
         
         for (int i = _dyld_image_count(); i >= 0 ; i--)
         {
            
            path = _dyld_get_image_name(i);
            
            ::string strPathTitle = path.title();
            
            if(strPathTitle.case_insensitive_equals(strTitle))
            {
               
               goto found;
               
            }
            
            if(strPathTitle.case_insensitive_equals(strLibTitle))
            {
               
               goto found;
               
            }
            
         }
         
         return nullptr;
         
      found:
         
         ::string strMessage;
         
         auto p = open(path, strMessage);
         
         close(p);
         
         return p;
         
      }


      library_t * dynamic_library::module_by_path(const ::file::path & path)
      {
         
         ::file::path pathInProcess;
         
         for (int i = _dyld_image_count(); i >= 0 ; i--)
         {
            
            pathInProcess = _dyld_get_image_name(i);
            
            if(path_system()->real_path_is_same(pathInProcess, path))
            {
               
               goto found;
               
            }
            
         }
         
         return nullptr;
         
      found:
         
         ::string strMessage;
         
         auto p = open(pathInProcess, strMessage);
         
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
         
         //informationf("\n\nGoing to dlopen: \"" + strPath + "\"");
         
         auto pathModuleFolder = ::apple_app_module_folder();
         
         path = pathModuleFolder / strPath;
         
         //informationf("\nFirst path to try: \"" + path + "\"");
         
         auto plibrary = (library_t *) dlopen(path, RTLD_LOCAL | RTLD_LAZY);
         
         if(plibrary != nullptr)
         {
            
            goto finished;
            
         }
         
         strError = dlerror();
         
         strMessage += "\n(1) dlopen: " + path + " with the error: \"" + strError + "\"";
         
         path = strPath;
         
         plibrary = (library_t *) dlopen(path, RTLD_LOCAL | RTLD_LAZY);
         
         if(plibrary != nullptr)
         {
            
            goto finished;
            
         }
         
         strError = dlerror();
         
         strMessage += "\n(2) dlopen: " + path + " with the error: \"" + strError + "\"";
         
         path = ::file::path(directory_system()->module()) / strPath;
         
         plibrary = (library_t *) dlopen(path, RTLD_LOCAL | RTLD_LAZY);
         
         if(plibrary != nullptr)
         {
            
            goto finished;
            
         }
         
         strError = dlerror();
         
         strMessage += "\n(3) dlopen: " + path + " with the error: \"" + strError + "\"";
         
         if(strPath.contains('/'))
         {
            
            path = ::file::path(strPath).name();
            
            plibrary = (library_t *)  dlopen(path, RTLD_LOCAL | RTLD_LAZY);
            
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
               
               informationf("\n" + strMessage + "\n\n");
               
            }
            
         }
         else
         {
            
            strMessage = "__node_library_open : Failed with : " + strMessage;
            
            informationf("\n" + strMessage + "\n\n");
            
         }
         
         return plibrary;
         
      }


      bool dynamic_library::close(library_t * plibrary)
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
               
               informationf("\n\n" + strMessage + "\n\n");
               
            }
            
         }
         else
         {
            
            string strError;
            
            strError = dlerror();
            
            strMessage = "__node_library_open_ca2 : " + strPath + " with the error: \"" + strError + "\"";
            
            informationf("\n\n" + strMessage + "\n\n");
            
         }
         
         return plibrary;
         
      }


   } // namespace operating_system



} // namespace macos

namespace operating_system
{

CLASS_DECL_ACME::operating_system::dynamic_library* new_dynamic_library()
{
   
   return __raw_new ::macos::operating_system::dynamic_library();
   
}


}
