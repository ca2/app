#include "framework.h"
////#include "aura/os/_.h"
//#include "aura/os/_os.h"
//#include <dlfcn.h>
//#ifdef __APPLE__
//#include <mach-o/dyld.h>
//#include <mach-o/nlist.h>
//#include <sys/types.h> // for jl_raise_debugger
//#elif !defined(_OS_WINDOWS_)
//#include <link.h>
//#endif
//
//void * __node_library_touch(const ::string & pszPath, string & strMessage)
//{
//
//   for (i32 i = _dyld_image_count(); i >= 0 ; i--)
//   {
//
//      const char *image_name = _dyld_get_image_name(i);
//
//      if(::file::path(image_name).title().case_insensitive_order(::file::path(pszPath).title()) == 0)
//      {
//
//         goto found;
//
//      }
//
//      if(::file::path(image_name).title().case_insensitive_order(("lib" + ::file::path(pszPath).title())) == 0)
//      {
//
//         goto found;
//
//      }
//
//   }
//
//   return nullptr;
//found:
//   return __node_library_open(pszPath, strMessage);
//
//}
//
//
//void * __node_library_open(const ::string & pszPath, string & strMessage)
//{
//
//   strMessage.empty();
//
//   string strPath(pszPath);
//
//   string strError;
//
//   ::file::path path;
//
//   if(!ansi_ends(strPath, ".dylib"))
//   {
//
//      strPath += ".dylib";
//
//   }
//
//   if(strPath.find('/') < 0 && !ansi_begins(strPath, "lib"))
//   {
//
//      strPath = "lib" + strPath;
//
//   }
//
//   ::output_debug_string("\n\nGoing to dlopen: \"" + strPath + "\"");
//
//   path = ::file::path(::get_exe_path()).folder() / strPath;
//
//   ::output_debug_string("\nFirst path to try: \"" + path + "\"");
//
//   void * plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
//
//   if(plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   strError = dlerror();
//
//   strMessage += "\n(1) dlopen: " + path + " with the error: \"" + strError + "\"";
//
//   path = strPath;
//
//   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
//
//   if(plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   strError = dlerror();
//
//   strMessage += "\n(2) dlopen: " + path + " with the error: \"" + strError + "\"";
//
//   path = ::file::path(::dir::ca2_module()) / strPath;
//
//   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
//
//   if(plibrary != nullptr)
//   {
//
//      goto finished;
//
//   }
//
//   strError = dlerror();
//
//   strMessage += "\n(3) dlopen: " + path + " with the error: \"" + strError + "\"";
//
//   if(strPath.find('/') >= 0)
//   {
//
//      path = ::file::path(strPath).name();
//
//      plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);
//
//      if(plibrary != nullptr)
//      {
//
//         goto finished;
//
//      }
//
//      strError = dlerror();
//
//      strMessage += "\n(4) dlopen: " + path + " with the error: \"" + strError + "\"";
//
//   }
//
//finished:
//
//   if(plibrary != nullptr)
//   {
//
//      strMessage = "__node_library_open (1) Succeeded " + path;
//
//   }
//   else
//   {
//
//      strMessage = "__node_library_open : Failed with : " + strMessage;
//
//   }
//
//   ::output_debug_string("\n" + strMessage + "\n\n");
//
//   return plibrary;
//
//}
//
//
//bool __node_library_close(void * plibrary)
//{
//
//   if(plibrary != nullptr)
//   {
//
//      dlclose(plibrary);
//
//   }
//
//   return true;
//
//}
//
//
//void * __node_library_raw_get(void * plibrary, const ::string & pszElement)
//{
//
//   return dlsym(plibrary, pszElement);
//
//}
//
//
//
//
//
//
//void * __node_library_open_ca2(const ::string & pszPath, string & strMessage)
//{
//
//   string strPath(pszPath);
//   
//   if(!strPath.case_insensitive_begins("lib"))
//   {
//      
//      strPath = "lib" + strPath;
//      
//   }
//
//   if(!strPath.case_insensitive_ends(".dylib"))
//   {
//      
//      strPath += ".dylib";
//      
//   }
//
//   void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
//
//   if(plibrary != nullptr)
//   {
//
//      strMessage = "__node_library_open_ca2 Succeeded " + strPath;
//
//   }
//   else
//   {
//
//      string strError;
//
//      strError = dlerror();
//
//      strMessage = "__node_library_open_ca2 : " + strPath + " with the error: \"" + strError + "\"";
//
//   }
//
//   ::output_debug_string("\n\n" + strMessage + "\n\n");
//
//   return plibrary;
//
//}
//
//
