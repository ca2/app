#pragma once


#include "acme/platform/library.h"


namespace filehandler
{


   class CLASS_DECL_CORE library :
      virtual public ::acme::library
   {
   public:


      library();
      ~library() override;


      virtual bool handles_extension(const ::scoped_string & scopedstrExtension);
      virtual bool handles_mime_type(const ::scoped_string & scopedstrMimeType);

      virtual void get_extension_app(string_array & straAppId, const ::scoped_string & scopedstrExtension);
      virtual void get_mime_type_app(string_array & straAppId, const ::scoped_string & scopedstrMimeType);


      // impl
      virtual void get_extension_list(string_array & stra);
      virtual void get_mime_type_list(string_array & stra);


   };


} // namespace filehandler





