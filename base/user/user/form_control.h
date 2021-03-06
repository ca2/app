#pragma once


namespace user
{


   class CLASS_DECL_BASE form_control:
      virtual public ::user::form
   {
   public:


      string                     m_strPath;
      bool                       m_bOnEditUpdate;
      bool                       m_bOnLanguageChange;
      ::u32                       m_uiId;
      //control_descriptor_set     m_controldescriptorset;
      bool                       m_bInitialized;
      ::file::path               m_pathDefaultDocument;


      //__pointer(form_control)    m_pformChild;


      form_control();
      virtual ~form_control();



      inline ::base::application* get_application() const;
      inline ::base::session* get_session() const;
      inline ::base::system* get_system() const { return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }

      //ref_array < CTransparentStatic > m_staticpa;


      virtual string get_path();
      virtual ::e_status open_document(const ::payload & varFile) override;
      //::type controltype_to_typeinfo(::user::enum_control_type econtroltype);

      virtual ::e_status open_html(const ::string & str) override;


      //using ::user::interaction::_001IsPointInside;
      virtual bool _001IsPointInside(::user::interaction * pinteraction,point_i64 point);
      virtual void control_get_window_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle);

      virtual void control_get_client_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle);

      
      virtual ::user::form * get_form() override;
      virtual void soft_reload() override;


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(::user::interaction * pinteraction);
      virtual void _001OnInitializeForm(::user::interaction * pinteraction);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(::user::interaction * pinteraction);
      //virtual void _001RemoveControls();
      bool _001Validate(::user::interaction * pinteraction,::payload & payload);
      bool _001SaveEdit(::user::interaction * pinteraction);
      virtual void on_command(::message::command * pcommand) override;
      DECLARE_MESSAGE_HANDLER(_001OnNotify);
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key,::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uId,bool bData);
      bool _001GetData(id uId,bool & bData);
      bool _001AddControl(::user::interaction * pinteraction) override;
      //__pointer(class control_descriptor) new_form_control() override;
      void _001FillCombo(::user::interaction * pinteraction);

      virtual void WfiOnClose() override;

      DECLARE_MESSAGE_HANDLER(_000OnPosCreate);
      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData();
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool update_data(bool bSaveAndValidate) override;
      virtual void _001Update(::user::interaction * pinteraction);
      virtual void _001UpdateCheckBox(::user::interaction * pinteraction);
      virtual void _001UpdateComboBox(::user::interaction * pinteraction);
      virtual void _001UpdateEdit(::user::interaction * pinteraction);
      virtual void _001UpdateSimpleList(::user::interaction * pinteraction);

      virtual void _001UpdateDbFlags(::user::interaction * pinteraction);
      virtual void _001UpdateDbFlagsCheckBox(::user::interaction * pinteraction);

      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);

      bool OnCommand(wparam wparam,lparam lparam);

      bool OnCommandButton(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam);

      bool OnCommandCheckBox(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam);

      bool OnCommandComboBox(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam);

      bool OnCommandEdit(::user::interaction * pinteraction,::u32 uNotificationCode,lparam lparam);



      virtual void data_on_after_change(::database::client* pclient, const ::database::key& key, const ::payload & payload, ::subject::subject * psubject = nullptr);


      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id) override;
      //virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor);

      void on_control_event(::user::control_event * pevent) override;
      void _001SetControlFactory();


      virtual bool _001OnControlSetFocus(::user::interaction * pinteraction);
      virtual bool _001OnControlKillFocus(::user::interaction * pinteraction);


      //        ::user::form_window(::object * pobject);
      //    virtual ~::user::form_window();

      //virtual void install_message_routing(::channel * pchannel);

      //      DECLARE_MESSAGE_HANDLER(on_message_create);


      //      ::user::form_window(::object * pobject);

      //virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      //      virtual void on_control_event(::user::control_event * pevent);
      //      DECLARE_MESSAGE_HANDLER(on_message_create);
      virtual void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(_001OnUser123);
      //      virtual void install_message_routing(::channel * pchannel);


//      virtual void soft_reload();

      //virtual ::form_property_set * get_form_property_set() override;

//      virtual bool _001IsPointInside(::user::interaction * pinteraction,point_i64 point);

      //    virtual void control_get_window_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle);

      //  virtual void control_get_client_rect(::user::interaction * pinteraction,RECTANGLE_I32 * prectangle);



      //virtual bool open_document(const ::payload & varFile) override;


   };


} // namespace user


