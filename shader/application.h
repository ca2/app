#pragma once


#include "bred/platform/application.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER application :
      virtual public ::bred::application
   {
   public:


      ::pointer<::app_shader::main_window>                   m_pmainwindow;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


 
      virtual void init_instance() override;
      virtual void term_application() override;


      virtual void on_request(::request * prequest) override;


#ifdef _DEBUG


      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;


#endif


      virtual string get_next_shader_path(const ::scoped_string & scopedstrPath);

      virtual void get_shader_listing(::file::listing_base& listing);


   };


} // namespace app_shader



