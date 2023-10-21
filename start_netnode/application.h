#pragma once


namespace app_app
{


   class CLASS_DECL_APP_APP application :
      virtual public ::aura::application
   {
   public:


      ::pointer<::app_app::main_window>      m_pmainwindow;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual int64_t decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif

   };


} // namespace app_app



