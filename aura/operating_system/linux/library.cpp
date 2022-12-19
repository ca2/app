#include "framework.h"
#include "acme/platform/library.h"
#include "acme/primitive/string/string.h"
#include "acme/filesystem/filesystem/path.h"
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

string __node_library_is_loaded(const ::string & pszPath)
{


   query_loaded_library q;

   q.m_strPathIn = pszPath;

   if(!q.m_strPathIn.case_insensitive_ends(".so"))
   {

      q.m_strPathIn += ".so";

   }

   if(!q.m_strPathIn.begins("/") && !q.m_strPathIn.case_insensitive_begins("lib"))
   {

      q.m_strPathIn = "lib" + q.m_strPathIn;

   }

   dl_iterate_phdr(__node_library_is_loaded_callback, &q);

   return q.m_strPathOut;

}


CLASS_DECL_AURA void * __node_library_touch(const ::string & pszPath, string & strMessage)
{

   string strPath = __node_library_is_loaded(pszPath);

   if(strPath.has_char())
   {

      return __node_library_open(strPath, strMessage);

   }

   return nullptr;

}

CLASS_DECL_AURA void * __node_library_open(const ::string & pszPath, string & strMessage)
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

   if(strstr((const ::string &) strPath, "/") == nullptr && !ansi_begins(strPath, "lib"))
      strPath = "lib" + strPath;

   void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

   if(plibrary == nullptr)
   {

      // pubs.opengroup.org contribution

      int iError = errno;


      char *errstr;

      errstr = dlerror();

      if (errstr != nullptr)
      {

         strMessage += errstr;

      }

      const scoped_string & str = strerror(iError);

      if(psz != nullptr)
      {

         strMessage += psz;

      }


   }
   else
   {

      strMessage += "Successfully loaded library ";

      strMessage += pszPath;

   }

   return plibrary;

}


CLASS_DECL_AURA void * __node_library_open_ca2(const ::string & pszPath, string & strMessage)
{

   string strPath(pszPath);

   if(!strPath.case_insensitive_ends(".so"))
   {

      strPath += ".so";

   }

   if(!strPath.case_insensitive_begins("lib"))
   {

      strPath = "lib" + strPath;

   }

   void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

   if(plibrary != nullptr)
   {

      return plibrary;

   }

   int iError = errno;

   const scoped_string & str = strerror(iError);

   if(psz != nullptr)
   {

      strMessage += psz;

   }

   const scoped_string & str2 = dlerror();

   if(psz2 != nullptr)
   {

      strMessage += psz2;

   }

   return plibrary;

}


CLASS_DECL_AURA bool __node_library_close(void * plibrary)
{

   if(plibrary == nullptr)
      return false;

   return dlclose(plibrary) == 0;

}


CLASS_DECL_AURA void * __node_library_raw_get(void * plibrary, const ::string & pszEntryName)
{

   return dlsym(plibrary, pszEntryName);

}




























