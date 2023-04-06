#include "framework.h"
#include <dlfcn.h>


namespace ca
{


   library::library()
   {

      m_plibrary = nullptr;

   }


   library::library(const ::string & pszOpen)
   {

      m_plibrary = nullptr;

      open(pszOpen);

   }


   library::~library()
   {

      close();

   }


   bool library::open(const ::string & pszPath)
   {

      vsstring strPath(pszPath);

      if(strPath == "os")
      {

         strPath = "ca2os";

      }
      else if(strPath == "app_sphere")
      {

         strPath = "ca2sphere";

      }

      if(ansi_find_string(strPath, ".") == nullptr)
         strPath += ".so";

      if(strstr((const ::string &) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
         strPath = "lib" + strPath;

      m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
      int iError = errno;

      const ::scoped_string & scopedstr = strerror(iError);

      const ::scoped_string & scopedstr2 = dlerror();

      return m_plibrary != nullptr;

   }


   bool library::close()
   {
      if(m_plibrary != nullptr)
      {
         dlclose(m_plibrary);
      }
   }


   void * library::raw_get(const ::string & pszElement)
   {
      return dlsym(m_plibrary, pszElement);
   }

   ca2_library::ca2_library()
   {
   }

   ca2_library::ca2_library(const ::string & pszOpen) :
      library(pszOpen)
   {

   }

   ca2_library::~ca2_library()
   {

   }

   bool ca2_library::open(const ::string & pszPath)
   {
      return library::open(pszPath);
   }

   bool library::is_opened()
   {

      return m_plibrary != nullptr;

   }

   bool library::is_closed()
   {

      return !is_opened();

   }

} // namespace ca



