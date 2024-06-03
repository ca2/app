// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"


namespace nano
{


   namespace dynamic_library
   {


      dynamic_library::dynamic_library()
      {

      }


      dynamic_library::~dynamic_library()
      {


      }


      ::string dynamic_library::get_module_path(library_t * plibrary)
      {

         throw ::interface_only();

         return {};

      }


      ::string dynamic_library::get_module_path_by_name(const char *pszName)
      {

         auto plibrary = get_module_by_name(pszName);

         if (::is_null(plibrary))
         {

            return nullptr;

         }

         ::string strPath = get_module_path(plibrary);

         return strPath;

      }


      library_t * dynamic_library::get_module_by_name(const char * pszName)
      {

         throw ::interface_only();

         return {};

      }


      library_t * dynamic_library::touch(const ::file::path & path, string &strMessage)
      {

         throw ::interface_only();

         return nullptr;

      }


      library_t *dynamic_library::open(const ::file::path & path, string &strMessage)
      {

         throw ::interface_only();

         return nullptr;

      }


      library_t * dynamic_library::open_on_context(const ::file::path & path, string &strMessage)
      {

         throw ::interface_only();

         return nullptr;

      }


      bool dynamic_library::close(library_t *plibrary)
      {

         throw ::interface_only();
         return false;

      }


      void *dynamic_library::raw_get(library_t *plibrary, const ::scoped_string & scopedstrEntryName)
      {

         throw ::interface_only();

         return nullptr;


      }


   } // namespace dynamic_library


} // namespace nano



