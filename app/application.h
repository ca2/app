#pragma once



namespace app_app
{


   class CLASS_DECL_APP_APP_APP application :
      virtual public ::aura::application
   {
   public:


      __reference(window)                             m_pwindow;


      application();
      virtual ~application();

      virtual ::estatus init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif

   };


} // namespace app_app



