#pragma once


#include "aura/platform/application.h"


namespace app_shader
{


   class CLASS_DECL_APP_SHADER application :
      virtual public ::aura::application
   {
   public:


      __composite(::app_shader::main_window)                    m_pmainwindow;


      application();
      ~application() override;

 
      virtual void init_instance() override;
      virtual void term_application() override;


      virtual void on_request(::create * pcreate) override;


#ifdef _DEBUG


      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      virtual string get_next_shader_path(const string& strPath);

      virtual void get_shader_listing(::file::listing& listing);


   };


} // namespace app_shader



