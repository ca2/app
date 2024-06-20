// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace ios
{

namespace nano
{


namespace dynamic_library
{


class CLASS_DECL_ACME dynamic_library :
virtual public ::acme::department
{
public:
   
   
   inline static const char *represented_component_name()
   {
      
      return "nano_dynamic_library";
      
   }
   
   
   dynamic_library();
   
   ~dynamic_library() override;
   
   
   virtual ::file::path module_path(library_t * plibrary);
   
   
   virtual ::file::path module_path_by_name(const ::scoped_string & scopedtrName);
   
   
   virtual library_t * module_by_name(const ::scoped_string & scopedstrsName);
   
   
   virtual library_t * module_by_path(const ::file::path & path);
   
   
   virtual library_t * touch(const ::file::path & path, string & strMessage);
   
   
   virtual library_t * open(const ::file::path & path, string & strMessage);
   
   
   virtual library_t * open_on_context(const ::file::path & path, string & strMessage);
   
   
   virtual bool close(library_t * plibrary);
   
   
   virtual void *raw_get(library_t * plibrary, const ::scoped_string & scopedstrEntryName);
   
   
};


} // dynamic_library


} // nano


} // namespace ios
