#include "framework.h"
#include "acme/platform/system.h"
#include <dlfcn.h>
#include <link.h>

struct query_loaded_library
{

   string m_strPathIn;
   string m_strPathOut;


};


//CLASS_DECL_ACME void *__node_library_open(const ::file::path &path, string &strMessage);


static int
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


namespace acme
{


   string system::operating_system_library_is_loaded(const ::file::path &path)
   {


      query_loaded_library q;

      q.m_strPathIn = path;

      if (!string_ends_ci(q.m_strPathIn, ".so"))
      {

         q.m_strPathIn += ".so";

      }

      if (!string_begins_ci(q.m_strPathIn, "/") && !string_begins_ci(q.m_strPathIn, "lib"))
      {

         q.m_strPathIn = "lib" + q.m_strPathIn;

      }

      dl_iterate_phdr(__node_library_is_loaded_callback, &q);

      return q.m_strPathOut;
   }


   void *system::operating_system_library_touch(const ::file::path &path, string &strMessage)
   {

      string strPath = operating_system_library_is_loaded(path);

      if (strPath.has_char())
      {

         return operating_system_library_open(strPath, strMessage);

      }

      return nullptr;

   }


   void *system::operating_system_library_open(const ::file::path &path, string &strMessage)
   {

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

      if (strstr((const char *) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
      {

         strPath = "lib" + strPath;

      }

      void *plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

      if (plibrary == nullptr)
      {

         // pubs.opengroup.org contribution

         int iError = errno;

         auto pszError = strerror(iError);

         if (pszError != nullptr)
         {

            strMessage += pszError;

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


   void *system::operating_system_library_open_ca2(const ::file::path &path, string &strMessage)
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

      auto pszError = strerror(iError);

      if (pszError != nullptr)
      {

         strMessage += pszError;

      }

      auto pszDlError = dlerror();

      if (pszDlError != nullptr)
      {

         strMessage += pszDlError;

      }

      return plibrary;

   }


   bool system::operating_system_library_close(void *plibrary)
   {

      if (plibrary == nullptr)
         return false;

      return dlclose(plibrary) == 0;

   }


   void *system::operating_system_library_raw_get(void *plibrary, const ::scoped_string &scopedstrEntryName)
   {

      return dlsym(plibrary, scopedstrEntryName);

   }


} // namespace acme


