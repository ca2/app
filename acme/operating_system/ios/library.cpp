#include "framework.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include <dlfcn.h>


//CLASS_DECL_ACME ::acme::system * acmesystem();


void * __node_library_open(const ::file::path & path, string & strMessage);

void * __node_library_touch(const ::file::path & path, string & strMessage)
{

   return __node_library_open(pszPath, strMessage);

}

void * __node_library_open(const ::file::path & path, string & strMessage)
{
   
   auto psystem = acmesystem();

   string strPath(pszPath);

   strMessage.empty();

   string strError;

   if(strPath == "os")
   {

      strPath = "ca2os";

   }
   else if(strPath == "os2")
   {

      strPath = "ca2os2";

   }

   if(!ansi_ends(strPath, ".dylib"))
   {

      strPath += ".dylib";

   }

   if(!string_begins_ci(strPath, "/") && !ansi_begins(strPath, "lib"))
   {

      strPath = "lib" + strPath;

   }

   //::output_debug_string("\n\nGoing to dlopen : \"" + strPath + "\"");

   ::file::path path;

   path = ::file::path(::get_exe_path()).folder() / strPath;

   void * plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(1) node_library_open Failed " + path + " with the error: \""+strError+"\"";

   path = strPath;

   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(2) node_library_open Failed " + path + " with the error: \""+strError+"\"";
   
   path = ::file::path(psystem->m_pacmedirectory->module()).folder() / strPath;

   plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n(3) node_library_open Failed " + path + " with the error: \""+strError+"\"";

   if(strPath.find('/') >= 0)
   {

      path = ::file::path(strPath).name();

      plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

      if(plibrary != nullptr)
      {

         goto finished;

      }

      strError = dlerror();

      strMessage += "\n(4) node_library_open Failed " + path + " with the error: \""+strError+"\"";

   }

finished:

   if(plibrary != nullptr)
   {

      strMessage = "node_library_open Succeeded " + path;

   }
   else
   {

      strMessage = "node_library_open FAILED " + path + strMessage;

   }

   ::output_debug_string("\n"+strMessage+"\n\n");

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

   strMessage.empty();

   string strError;

   ::file::path path(pszPath);

   void * plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

   if(plibrary != nullptr)
   {

      goto finished;

   }

   strError = dlerror();

   strMessage += "\n node_library_open_ca2 Failed " + path + " with the error: \""+strError+"\"";


finished:

   if(plibrary != nullptr)
   {

      strMessage = "node_library_open_ca2 Succeeded " + path;

   }
   else
   {

      strMessage = "node_library_open_ca2 FAILED " + path + strMessage;

   }

   ::output_debug_string("\n"+strMessage+"\n\n");

   return plibrary;

}



