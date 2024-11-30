// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"


namespace operating_system
{


   dynamic_library::dynamic_library()
   {

   }


   dynamic_library::~dynamic_library()
   {


   }


   ::file::path dynamic_library::module_path(library_t* plibrary)
   {

      throw ::interface_only();

      return {};

   }


   ::file::path dynamic_library::module_path_by_name(const ::scoped_string& scopedstrName)
   {

      auto plibrary = module_by_name(scopedstrName);

      if (::is_null(plibrary))
      {

         return nullptr;

      }

      auto path = module_path(plibrary);

      return path;

   }


   library_t* dynamic_library::module_by_name(const ::scoped_string& scopedstrName)
   {

      throw ::interface_only();

      return {};

   }


   library_t* dynamic_library::module_by_path(const ::file::path& path)
   {

      throw ::interface_only();

      return {};

   }


   library_t* dynamic_library::touch(const ::file::path& path, string& strMessage)
   {

      auto plibrary = module_by_path(path);

      if (plibrary)
      {

         return plibrary;

      }

      plibrary = module_by_name(path);

      if (plibrary)
      {

         return plibrary;

      }

      return nullptr;

   }


   library_t* dynamic_library::open(const ::file::path& path, string& strMessage)
   {

      throw ::interface_only();

      return nullptr;

   }


   library_t* dynamic_library::open_on_context(const ::file::path& path, string& strMessage)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool dynamic_library::close(library_t* plibrary)
   {

      //throw ::interface_only();
      return false;

   }


   void* dynamic_library::raw_get(library_t* plibrary, const ::scoped_string& scopedstrEntryName)
   {

      throw ::interface_only();

      return nullptr;


   }


} // namespace operating_system



