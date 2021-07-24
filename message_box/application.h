#pragma once



namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX_APP application :
      virtual public ::aura::application
   {
   public:


      __composite(window)                             m_pwindow;


      application();
      virtual ~application();

      virtual ::e_status init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJECT_REF_DEBUG_PARAMS) override;
      virtual int64_t dec_ref(OBJECT_REF_DEBUG_PARAMS) override;
#endif


   };


} // namespace app_message_box



