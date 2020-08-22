#pragma once


namespace aura
{


   class CLASS_DECL_AURA library:
      virtual public ::aura::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library();


      // impl
      virtual void get_app_list(string_array & stra);
      virtual void get_extension_list(string_array & stra);
      virtual void get_extension_app(string_array & straApp,const char * pszExtension);


      //virtual __pointer(::aura::application) get_new_application(const char * pszAppId);


   };


} // namespace aura


