#include "framework.h"
#include "library.h"


//#include "acme/prototype/collection/string_array.h"


namespace filehandler
{


   library::library()
   {

   }


   library::~library()
   {

   }


   bool library::handles_extension(const ::scoped_string & scopedstrExtension)
   {

      string_array stra;

      get_extension_list(stra);

      if(!stra.case_insensitive_contains(scopedstrExtension))
         return false;

      return true;

   }


   bool library::handles_mime_type(const ::scoped_string & scopedstrMimeType)
   {

      string_array stra;

      get_mime_type_list(stra);

      if(!stra.case_insensitive_contains(scopedstrMimeType))
         return false;

      return true;

   }


   void library::get_extension_app(string_array & straAppId, const ::scoped_string & scopedstrExtension)
   {

      if(!handles_extension(scopedstrExtension))
         return;

      string_array stra;

      throw todo;

      //get_app_list(stra);

      //if(stra.get_count() == 1)
      //{
      //   straAppId.add(m_strRoot + "/" + stra[0]);
      //}

   }

   void library::get_mime_type_app(string_array & straAppId, const ::scoped_string & scopedstrMimeType)
   {

      if(!handles_mime_type(scopedstrMimeType))
         return;

      string_array stra;

      throw todo;

      //get_app_list(stra);

      //if(stra.get_count() == 1)
      //{
      //   straAppId.add(m_strRoot + "/" + stra[0]);
      //}

   }


   void library::get_extension_list(string_array & stra)
   {

      __UNREFERENCED_PARAMETER(stra);

   }


   void library::get_mime_type_list(string_array & stra)
   {
      __UNREFERENCED_PARAMETER(stra);
   }




} // namespace filehandler




