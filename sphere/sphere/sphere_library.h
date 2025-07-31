#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE library :
      virtual public ::apex::single_application_library < application >,
      virtual public ::filehandler::menu_library
   {
   public:


      library(::particle * pparticle);
      

      virtual void get_app_list(string_array & stra);

      virtual void get_extension_list(string_array & stra);

      virtual void get_extension_app(string_array & straApp, const ::scoped_string & scopedstrExtension);

//      virtual ::pointer<::aura::application>get_new_app(const ::scoped_string & scopedstrAppId);


   };


} // namespace sphere



