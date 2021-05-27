#pragma once



namespace app_just_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX_APP application :
      virtual public ::aura::application
   {
   public:


      application();
      virtual ~application();


      virtual ::e_status init_instance() override;
      virtual void term_application() override;

      virtual void on_request(::create * pcreate) override;

#ifdef DEBUG
      virtual int64_t add_ref(OBJ_REF_DBG_PARAMS) override;
      virtual int64_t dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif


      virtual void show_message_box();


   };


} // namespace app_just_message_box



