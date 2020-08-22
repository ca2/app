#pragma once


namespace user
{


   class CLASS_DECL_AURA form_control:
      virtual public ::user::form,
      virtual public ::user::control
   {


   public:


      string                     m_strPath;
      bool                       m_bOnEditUpdate;
      bool                       m_bOnLanguageChange;
      UINT                       m_uiId;
      control_descriptor_set     m_controldescriptorset;
      bool                       m_bInitialized;
      ::file::path               m_pathDefaultDocument;


      __pointer(form_control)    m_pformChild;


      form_control();
      virtual ~form_control();


      //ref_array < CTransparentStatic > m_staticpa;


      virtual string get_path();
      virtual bool open_document(const var & varFile);
      //::type controltype_to_typeinfo(::user::e_control_type econtroltype);

      virtual ::estatus open_html(const ::string & str) override;


      using ::user::control::_001IsPointInside;
      virtual bool _001IsPointInside(::user::control * pcontrol,point64 point);
      virtual void control_get_window_rect(::user::control * pcontrol,RECT * prect);

      virtual void control_get_client_rect(::user::control * pcontrol,RECT * prect);

      
      virtual ::user::form * get_form() override;
      virtual void soft_reload();


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(::user::control * pcontrol);
      virtual void _001OnInitializeForm(::user::control * pcontrol);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(::user::control * pcontrol);
      virtual void _001RemoveControls();
      bool _001Validate(::user::control * pcontrol,var & var);
      bool _001SaveEdit(::user::control * pcontrol);
      virtual void on_command(::user::command * pcommand) override;
      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key,::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uiId,bool bData);
      bool _001GetData(id uiId,bool & bData);
//      index _001AddControl(class control_descriptor  * pdescriptor) override;
      __pointer(class control_descriptor) new_form_control() override;
      void _001FillCombo(::user::control * pcontrol);

      virtual void WfiOnClose() override;

      DECL_GEN_SIGNAL(_000OnPosCreate);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData();
      virtual void update(::update * pupdate) override;
      virtual bool update_data(bool bSaveAndValidate) override;
      virtual void _001Update(::user::control * pcontrol);
      virtual void _001UpdateCheckBox(::user::control * pcontrol);
      virtual void _001UpdateComboBox(::user::control * pcontrol);
      virtual void _001UpdateEdit(::user::control * pcontrol);
      virtual void _001UpdateSimpleList(::user::control * pcontrol);

      virtual void _001UpdateDbFlags(::user::control * pcontrol);
      virtual void _001UpdateDbFlagsCheckBox(::user::control * pcontrol);

      DECL_GEN_SIGNAL(_001OnAppLanguage);

      bool OnCommand(WPARAM wparam,LPARAM lparam);

      bool OnCommandButton(::user::control * pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandCheckBox(::user::control * pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandComboBox(::user::control * pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandEdit(::user::control * pcontrol,UINT uiNotificationCode,LPARAM lparam);



      virtual void data_on_after_change(::database::client* pclient, const ::database::key& key, const var& var, ::update* pupdate = nullptr);


      virtual bool create_control(class control_descriptor * pdescriptor, index iItem) override;
      virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor);

      bool operator == (const control & control) const;

      void on_control_event(::user::control_event * pevent) override;
      void _001SetControlFactory();


      virtual bool _001OnControlSetFocus(::user::interaction * pinteraction);
      virtual bool _001OnControlKillFocus(::user::interaction * pinteraction);


      //        ::user::form_window(::object * pobject);
      //    virtual ~::user::form_window();

      //virtual void install_message_routing(::channel * pchannel);

      //      DECL_GEN_SIGNAL(_001OnCreate);


      //      ::user::form_window(::object * pobject);

      //virtual void update(::update * pupdate) override;
      //      virtual void on_control_event(::user::control_event * pevent);
      //      DECL_GEN_SIGNAL(_001OnCreate);
      virtual void _001OnTimer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnUser123);
      //      virtual void install_message_routing(::channel * pchannel);


      //virtual ::form_property_set * get_form_property_set() override;

//      virtual bool _001IsPointInside(::user::control * pcontrol,point64 point);

      //    virtual void control_get_window_rect(::user::control * pcontrol,RECT * prect);

      //  virtual void control_get_client_rect(::user::control * pcontrol,RECT * prect);



      //virtual bool open_document(const var & varFile) override;


   };


} // namespace user


