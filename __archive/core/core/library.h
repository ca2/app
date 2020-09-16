#pragma once


namespace acme
{


   class CLASS_DECL_ACME library:
      virtual public ::acme::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library();


      // impl
      virtual void get_app_list(string_array & stra);
      virtual void get_extension_list(string_array & stra);
      virtual void get_extension_app(string_array & straApp,const char * pszExtension);


      //virtual __pointer(::acme::application) get_new_application(const char * pszAppId);


   };


} // namespace acme


