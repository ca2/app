#pragma once


namespace filehandler
{


   class CLASS_DECL_CORE library :
      virtual public ::aura::library
   {
   public:


      library();
      virtual ~library();


      virtual bool handles_extension(const char * pszExtension);
      virtual bool handles_mime_type(const char * pszMimeType);

      virtual void get_extension_app(string_array & straAppId, const char * pszExtension);
      virtual void get_mime_type_app(string_array & straAppId, const char * pszMimeType);


      // impl
      virtual void get_extension_list(string_array & stra);
      virtual void get_mime_type_list(string_array & stra);


   };


} // namespace filehandler





