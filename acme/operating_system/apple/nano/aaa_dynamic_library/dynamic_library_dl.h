// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/nano/dynamic_library/dynamic_library.h"


namespace dl
{


   namespace nano
   {


      namespace dynamic_library
      {


         class CLASS_DECL_ACME dynamic_library

                 :
                         virtual public ::nano::dynamic_library::dynamic_library
         {
         public:


            inline static const char * represented_component_name()
            {

               return "nano_dynamic_library";

            }


            dynamic_library();

            ~

            dynamic_library()

            override;


            ::file::path module_path(::library_t * plibrary) override;


            ::library_t * module_by_name(const ::scoped_string & scopedstrName) override;


            ::library_t * module_by_path(const ::file::path & path) override;


            //library_t *touch(const ::file::path &path, string &strMessage) override;


            library_t * open(const ::file::path & path, string & strMessage) override;

            library_t * open_on_context(const ::file::path & path, string & strMessage) override;

            bool close(library_t * plibrary) override;

            void * raw_get(library_t * plibrary, const ::scoped_string & scopedstrEntryName) override;

         };


      } // dynamic_library


   } // nano


} // namespace dl



