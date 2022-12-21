#include "framework.h"
#include "acme/platform/library.h"
#include "acme/platform/system.h"
//#include "acme/filesystem/filesystem/path.h"
#include <dlfcn.h>
#include <link.h>

struct query_loaded_library
{

string m_strPathIn;
string m_strPathOut;


};

namespace acme
{
   int
   __node_library_is_loaded_callback(struct dl_phdr_info *info, size_t size, void *data)
   {
      query_loaded_library *q = (query_loaded_library *) data;

      if (::file::path(info->dlpi_name).name() == q->m_strPathIn)
      {


         q->m_strPathOut = info->dlpi_name;

         return 1;

      }
      return 0;
   }


   string __node_library_is_loaded(const char *pszPath)
   {


      query_loaded_library q;

      q.m_strPathIn = pszPath;

      if (!q.m_strPathIn.case_insensitive_ends(".so"))
      {

         q.m_strPathIn += ".so";

      }

      if (!q.m_strPathIn.case_insensitive_begins("/") && !q.m_strPathIn.case_insensitive_begins("lib"))
      {

         q.m_strPathIn = "lib" + q.m_strPathIn;

      }

      dl_iterate_phdr(__node_library_is_loaded_callback, &q);

      return q.m_strPathOut;

   }


   void * system::operating_system_library_touch(const ::file::path & path, string &strMessage)
   {

      string strPath = __node_library_is_loaded(path);

      if (strPath.has_char())
      {

         return operating_system_library_open(path, strMessage);

      }

      return nullptr;

   }


   void *system::operating_system_library_open(const ::file::path & path, string &strMessage)
   {

      string strPath(path);

      if (strPath == "os")
      {

         strPath = "ca2os";

      } else if (strPath == "app_sphere")
      {

         strPath = "basesphere";

      }

      if (ansi_find_string(strPath, ".") == nullptr)
      {

         strPath += ".so";

      }

      if (strstr((const char *) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
      {

         strPath = "lib" + strPath;

      }

      void *plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);
      //void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_NODELETE);

      if (plibrary == nullptr)
      {

         // pubs.opengroup.org contribution

         int iError = errno;

         const char *psz = strerror(iError);

         if (psz != nullptr)
         {

            strMessage += psz;

         }

         char *errstr;

         errstr = dlerror();

         if (errstr != nullptr)
         {

            strMessage += errstr;

         }

      }
      else
      {

         strMessage += "Successfully loaded library ";

         strMessage += path;

      }

      return plibrary;

   }


   void * system::operating_system_library_open_ca2(const ::file::path & path, string &strMessage)
   {

      string strPath(path);

      if (!strPath.case_insensitive_ends(".so"))
      {

         strPath += ".so";

      }

      if (!strPath.case_insensitive_begins("lib"))
      {

         strPath = "lib" + strPath;

      }

      void *plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

      if (plibrary != nullptr)
      {

         return plibrary;

      }

      int iError = errno;

      const char *psz = strerror(iError);

      if (psz != nullptr)
      {

         strMessage += psz;

      }

      const char *psz2 = dlerror();

      if (psz2 != nullptr)
      {

         strMessage += psz2;

      }

      return plibrary;

   }


   bool system::operating_system_library_close(void *plibrary)
   {

      if (plibrary == nullptr)
         return false;

      return dlclose(plibrary) == 0;

   }


   void *system::operating_system_library_raw_get(void *plibrary, const ::scoped_string & scopedstrEntryName)
   {

      return dlsym(plibrary, scopedstrEntryName.c_str());

   }


} // namespace acme



