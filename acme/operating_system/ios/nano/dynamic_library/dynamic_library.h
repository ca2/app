// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/dynamic_library.h"


namespace ios
{


namespace operating_system
{


//namespace dynamic_library
//{


class CLASS_DECL_ACME dynamic_library :
virtual public ::operating_system::dynamic_library
{
public:
   
   
   inline static const_char_pointer represented_component_name()
   {
      
      return "nano_dynamic_library";
      
   }
   
   
   dynamic_library();
   
   ~dynamic_library() override;
   
   
   ::file::path module_path(library_t * plibrary) override;
   
   
//   virtual ::file::path module_path_by_name(const ::scoped_string & scopedtrName);
   
   
   library_t * module_by_name(const ::scoped_string & scopedstrsName) override;
   
   
   library_t * module_by_path(const ::file::path & path) override;
   
   
   //library_t * touch(const ::file::path & path, string & strMessage) override;
   
   
   library_t * open(const ::file::path & path, string & strMessage) override;
   
   
   library_t * open_on_context(const ::file::path & path, string & strMessage) override;
   
   
   bool close(library_t * plibrary) override;
   
   
   void *raw_get(library_t * plibrary, const ::scoped_string & scopedstrEntryName) override;
   
   
};


} // namespace operating_system


//} // nano


} // namespace ios
