#pragma once


namespace base
{


   class CLASS_DECL_BASE application :
      virtual public ::aura::application,
      virtual public ::user::form_callback,
      virtual public ::user::impact_creator
   {
   public:





      // bool                                            m_bBaseProcessInitialize;
      // bool                                            m_bBaseProcessInitializeResult;

      // bool                                            m_bBaseInitializeInstance;
      // bool                                            m_bBaseInitializeInstanceResult;

      // bool                                            m_bBaseInitialize1;
      // bool                                            m_bBaseInitialize1Result;

      // bool                                            m_bBaseInitialize;
      // bool                                            m_bBaseInitializeResult;



      application();
      virtual ~application();


      virtual ::estatus     initialize(::object * pobjectContext) override;


      //virtual void install_message_routing(::channel * pchannel) override;

      //virtual void update(::update * pupdate) override;

      virtual ::estatus process_init() override;

      virtual ::estatus init_instance() override;

      virtual ::estatus     create_impact_system();

      virtual ::type user_default_controltype_to_typeinfo(::user::e_control_type econtroltype) override;
      virtual ::type control_type_from_id(const ::id & id, ::user::e_control_type & econtroltype) override;


      virtual void on_create_impact(::user::impact_data * pimpactdata) override;
      void process_message_filter(i32 code,::message::message * pmessage) override;



      //virtual __pointer(::user::user) create_user();

      virtual bool on_thread_on_idle(::thread_impl * pimpl,LONG lCount);



      virtual bool process_message() override;

      i32 hotplugin_host_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,::hotplugin::host * phost,::hotplugin::plugin * pplugin) override;


      //virtual ::form_property_set * get_form_property_set() override;
      


      using ::aura::application::on_control_event;
      using ::user::form_callback::on_control_event;


      virtual void remove_document_template(::user::impact_system * pimpactsystem);

      virtual void term_application() override;

      virtual void SetCurrentHandles() override;

      virtual ::draw2d::icon * set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon) override;

      virtual ::draw2d::icon * get_icon(object * pobject, bool bBigIcon) const override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual ::user::interaction * create_menu_interaction();

      virtual __pointer(::user::document) defer_create_view(string strView, ::user::interaction * puiParent, ewindowflag ewindowflag = window_flag_none, const ::id & id = nullptr) override;


   };


} // namespace base






