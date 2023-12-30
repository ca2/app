#pragma once



namespace app_net
{


   class CLASS_DECL_APP_APP_APP application :
      virtual public ::aura::application
   {
   public:


      ::pointer<window>                            m_pwindow;


      application();
      ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();


      virtual void init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::request * prequest) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count() override;
      virtual int64_t decrement_reference_count() override;
#endif

   };


} // namespace app_net



