#include "framework.h"
#include "acid/filesystem/filesystem/ace_directory.h"
#include "acid/platform/system.h"
#include <dlfcn.h>


//CLASS_DECL_ACID ::acid::system * system();

namespace platform
{
//void * __node_library_open(const ::file::path & path, string & strMessage);


   void * platform::operating_system_library_touch(const ::file::path & path, string & strMessage)
   {

      return operating_system_library_open(path, strMessage);

   }


   void * platform::operating_system_library_open(const ::file::path & pathParam, string & strMessage)
   {
      
      auto psystem = system();

      string strPath(pathParam);

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

      //::acid::get()->platform()->informationf("\n\nGoing to dlopen : \"" + strPath + "\"");

      ::file::path path;

      path = acedirectory()->module() / strPath;

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
      
      path = ::file::path(psystem->m_pacedirectory->module()).folder() / strPath;

      plibrary = dlopen(path, RTLD_LOCAL | RTLD_LAZY);

      if(plibrary != nullptr)
      {

         goto finished;

      }

      strError = dlerror();

      strMessage += "\n(3) node_library_open Failed " + path + " with the error: \""+strError+"\"";

      if(strPath.find('/') != nullptr)
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

      ::acid::get()->platform()->informationf("\n"+strMessage+"\n\n");

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


   void * platform::operating_system_library_raw_get(void * plibrary, const ::scoped_string & scopedstrElement)
   {

      return dlsym(plibrary, scopedstrElement);

   }


   void * platform::operating_system_library_open_ca2(const ::file::path & pathParam, string & strMessage)
   {

      strMessage.empty();

      string strError;

      ::file::path path(pathParam);

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

      ::acid::get()->platform()->informationf("\n"+strMessage+"\n\n");

      return plibrary;

   }


} // namespace acid


