#include "framework.h"
#include <dlfcn.h>


   base_library::base_library(__pointer(::axis::application) papp) :
      ::object(pobject)
   {

      m_plibrary = nullptr;

      m_bAutoClose = false;

   }


   base_library::base_library(__pointer(::axis::application) papp, const char * pszOpen) :
      ::object(pobject)
   {

      m_plibrary = nullptr;

      m_bAutoClose = false;

      open(pszOpen);

   }


   base_library::~base_library()
   {

      if(m_bAutoClose)
      {

         close();

      }

   }


   bool base_library::open(const char * pszPath, bool bAutoClose)
   {

      if(m_bAutoClose)
      {

         close();

      }

      m_bAutoClose = bAutoClose;

      string strPath(pszPath);

      if(strPath == "os")
      {
         strPath = "ca2os";
      }
      else if(strPath == "os2")
      {
         strPath = "ca2os2";
      }

      if(!ansi_ends(strPath, ".dylib"))
         strPath += ".dylib";

      if(!ansi_begins(strPath, "lib"))
         strPath = "lib" + strPath;

      m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);

      return true;

   }


   bool base_library::close()
   {

      if(m_plibrary != nullptr)
      {

         dlclose(m_plibrary);

      }

      return true;

   }


   void * base_library::raw_get(const char * pszElement)
   {

      return dlsym(m_plibrary, pszElement);

   }


   bool base_library::is_opened()
   {

      return m_plibrary != nullptr;

   }


   bool base_library::is_closed()
   {

      return m_plibrary == nullptr;

   }


   ca2_library::ca2_library(__pointer(::axis::application) papp) :
      ::object(pobject),
      base_library(pobject)
   {

   }


   ca2_library::ca2_library(__pointer(::axis::application) papp, const char * pszOpen) :
      ::object(pobject),
      base_library(papp, pszOpen)
   {

   }


   ca2_library::~ca2_library()
   {

   }


   bool ca2_library::open(const char * pszPath, bool bAutoClose)
   {

      return base_library::open(pszPath, bAutoClose);

   }


