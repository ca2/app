// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// From acme/nano/dynamic_library on 2024-06-02 18:06 by camilo <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library_dl.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/_operating_system.h"
#include <dlfcn.h>
#include <link.h>
#include <errno.h>
#include <string.h>


class modules_query :
   virtual public ::particle
{
public:
   string m_strName;
   ::file::path m_path;
   ::library_t* m_plibrary;


   modules_query() :
      m_plibrary(nullptr)
   {


   }


   void query_by_address(library_t* plibrary)
   {

      m_plibrary = plibrary;

      iterate();

   }


   void query_by_name(const ::scoped_string& scopedstrName)
   {

      m_strName = scopedstrName;

      if (!m_strName.case_insensitive_ends(".so"))
      {

         m_strName += ".so";

      }

      if (!m_strName.case_insensitive_begins("/") && !m_strName.case_insensitive_begins("lib"))
      {

         m_strName = "lib" + m_strName;

      }

      iterate();

   }


   void query_by_path(const ::file::path& path)
   {

      m_path = path;

      iterate();

   }


   void iterate()
   {

      dl_iterate_phdr(&s_callback, this);

   }


   static int s_callback(::dl_phdr_info* info, size_t size, void* data)
   {

      auto pcallback = (modules_query*)data;

      return pcallback->callback(info, size);

   }


   int callback(::dl_phdr_info* info, size_t size)
   {

      if (m_plibrary && m_plibrary == (::library_t*)info->dlpi_addr)
      {

         m_path = info->dlpi_name;

         m_strName = m_path.name();

         return 1;

      }
      else
      {

         auto path = ::file::path(info->dlpi_name);

         auto strName = path.name();

         if ((m_strName.has_character() && strName == m_strName)
            || (m_path.has_character() && path_system()->real_path_is_same(path, m_path)))
         {

            m_path = info->dlpi_name;

            m_strName = m_path.name();

            m_plibrary = (::library_t*)info->dlpi_addr;

            return 1;

         }

         return 0;

      }

   }

};


namespace dl
{


   dynamic_library::dynamic_library()
   {

   }


   dynamic_library::~dynamic_library()
   {


   }


   ::file::path dynamic_library::module_path(library_t* plibrary)
   {

      auto pquery = __create_new<modules_query>();

      pquery->query_by_address(plibrary);

      return pquery->m_path;

   }


   ::library_t* dynamic_library::module_by_name(const ::scoped_string& scopedstrName)
   {

      auto pquery = __create_new<modules_query>();

      pquery->query_by_name(scopedstrName);

      return pquery->m_plibrary;

   }


   ::library_t* dynamic_library::module_by_path(const ::file::path& path)
   {

      auto pquery = __create_new<modules_query>();

      pquery->query_by_path(path);

      return pquery->m_plibrary;

   }


   //         library_t * dynamic_library::touch(const ::file::path & path, string & strMessage)
   //         {
   //
   //            auto plibrary = this->get_module_by_name(path);
   //
   //            plibrary;
   //
   //         }


   library_t* dynamic_library::open(const ::file::path& path, string& strMessage)
   {

      string strPath(path);

      string strOs("os");

      if (strPath == strOs)
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

      if (!strPath.contains('/') && !ansi_begins(strPath, "lib"))
      {

         strPath = "lib" + strPath;

      }

      auto plibrary = (library_t*)dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);
      //void * plibrary = dlopen(strPath, RTLD_GLOBAL | RTLD_NODELETE);

      if (plibrary == nullptr)
      {

         // pubs.opengroup.org contribution

         int iError = errno;

         const_char_pointer psz = strerror(iError);

         if (scopedstr != nullptr)
         {

            strMessage += psz;

         }

         char* errstr;

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


   library_t* dynamic_library::open_on_context(const ::file::path& path, string& strMessage)
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

      auto plibrary = (library_t*)dlopen(strPath, RTLD_GLOBAL | RTLD_LAZY | RTLD_NODELETE);

      if (plibrary != nullptr)
      {

         return plibrary;

      }

      int iError = errno;

      const_char_pointer psz = strerror(iError);

      if (scopedstr != nullptr)
      {

         strMessage += psz;

      }

      const_char_pointer psz2 = dlerror();

      if (scopedstr2 != nullptr)
      {

         strMessage += psz2;

      }

      return plibrary;

   }


   bool dynamic_library::close(library_t* plibrary)
   {

      if (plibrary == nullptr)
         return false;

      return dlclose(plibrary) == 0;

   }


   void* dynamic_library::raw_get(library_t* plibrary, const ::scoped_string& scopedstrEntryName)
   {

      return dlsym(plibrary, scopedstrEntryName.c_str());

   }


} // namespace dl


namespace operating_system
{


   CLASS_DECL_ACME::operating_system::dynamic_library* new_dynamic_library()
   {

      return __raw_new ::dl::dynamic_library();

   }


} // namespace operating_system
