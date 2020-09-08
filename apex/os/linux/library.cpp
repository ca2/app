#include "framework.h"
#include <dlfcn.h>
#include <link.h>

struct query_loaded_library
{

string m_strPathIn;
string m_strPathOut;


};

static int
__node_library_is_loaded_callback(struct dl_phdr_info *info, size_t size, void *data)
{
    query_loaded_library * q=(query_loaded_library*) data;

   if(::file::path(info->dlpi_name).name() == q->m_strPathIn)
   {


      q->m_strPathOut = info->dlpi_name;

      return 1;

   }
    return 0;
}

string __node_library_is_loaded(const char * pszPath)
{


   query_loaded_library q;

   q.m_strPathIn = pszPath;

   if(!::str::ends_ci(q.m_strPathIn, ".so"))
   {

      q.m_strPathIn += ".so";

   }

   if(!::str::begins_ci(q.m_strPathIn, "/") && !::str::begins_ci(q.m_strPathIn, "lib"))
   {

      q.m_strPathIn = "lib" + q.m_strPathIn;

   }

   dl_iterate_phdr(__node_library_is_loaded_callback, &q);

   return q.m_strPathOut;
}


CLASS_DECL_APEX void * __node_library_touch(const char * pszPath, string & strMessage)
{

   string strPath = __node_library_is_loaded(pszPath);

   if(strPath.has_char())
   {

      return __node_library_open(strPath, strMessage);

   }

   return nullptr;

}

CLASS_DECL_APEX void * __node_library_open(const char * pszPath, string & strMessage)
{

   string strPath(pszPath);

   if(strPath == "os")
   {

      strPath = "ca2os";

   }
   else if(strPath == "app_sphere")
   {

      strPath = "basesphere";

   }

   if(ansi_find_string(strPath, ".") == nullptr)
      strPath += ".so";

   if(strstr((const char *) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
      strPath = "lib" + strPath;

   void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

   if(plibrary == nullptr)
   {

      // pubs.opengroup.org contribution

      int iError = errno;

      const char * psz = strerror(iError);

      if(psz != nullptr)
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

      strMessage += pszPath;

   }

   return plibrary;

}


CLASS_DECL_APEX void * __node_library_open_ca2(const char * pszPath, string & strMessage)
{

   string strPath(pszPath);

   if(!strPath.ends_ci(".so"))
   {

      strPath += ".so";

   }

   if(!strPath.begins_ci("lib"))
   {

      strPath = "lib" + strPath;

   }

   void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

   if(plibrary != nullptr)
   {

      return plibrary;

   }

   int iError = errno;

   const char * psz = strerror(iError);

   if(psz != nullptr)
   {

      strMessage += psz;

   }

   const char * psz2 = dlerror();

   if(psz2 != nullptr)
   {

      strMessage += psz2;

   }

   return plibrary;

}


CLASS_DECL_APEX bool __node_library_close(void * plibrary)
{

   if(plibrary == nullptr)
      return false;

   return dlclose(plibrary) == 0;

}


CLASS_DECL_APEX void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return dlsym(plibrary, pszEntryName);

}




























