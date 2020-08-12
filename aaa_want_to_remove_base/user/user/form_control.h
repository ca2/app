#pragma once


namespace user
{


   class CLASS_DECL_BASE form_control:
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
      form_callback *            m_pcallback;
      ::file::path               m_pathDefaultDocument;


      __pointer(form_control)    m_pformChild;
      form_control *             m_pformParent;


      form_control();
      virtual ~form_control();


      //ref_array < CTransparentStatic > m_staticpa;

      virtual string get_path();
      virtual bool open_document(const var & varFile);
      ::type controltype_to_typeinfo(::user::e_control_type econtroltype);

      virtual ::estatus     open_html(const ::string & str);


      using ::user::control::_001IsPointInside;
      virtual bool _001IsPointInside(__pointer(control) pcontrol,point64 point);
      virtual void control_get_window_rect(__pointer(control) pcontrol,RECT * prect);

      virtual void control_get_client_rect(__pointer(control) pcontrol,RECT * prect);

      
      virtual ::user::form * get_form() override;
      virtual void soft_reload();


      virtual bool _001Initialize();

      virtual void _017OnAppLanguage();
      virtual void _001OnButtonAction(__pointer(control) pcontrol);
      virtual void _001OnInitializeForm(__pointer(control) pcontrol);
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(__pointer(control) pcontrol);
      virtual void _001RemoveControls();
      bool _001Validate(__pointer(control) pcontrol,var & var);
      bool _001SaveEdit(__pointer(control) pcontrol);
      virtual void on_command(::user::command * pcommand) override;
      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key,::database::selection & selection);
      void Update(bool bSave);
      bool _001SetData(id uiId,bool bData);
      bool _001GetData(id uiId,bool & bData);
//      index _001AddControl(class control_descriptor  * pdescriptor) override;
      __pointer(class control_descriptor) new_form_control() override;
      void _001FillCombo(__pointer(control) pcontrol);

      virtual void WfiOnClose() override;

      DECL_GEN_SIGNAL(_000OnPosCreate);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData();
      virtual void update(::update * pupdate) override;
      virtual bool update_data(bool bSaveAndValidate) override;
      virtual void _001Update(__pointer(control) pcontrol);
      virtual void _001UpdateCheckBox(__pointer(control) pcontrol);
      virtual void _001UpdateComboBox(__pointer(control) pcontrol);
      virtual void _001UpdateEdit(__pointer(control) pcontrol);
      virtual void _001UpdateSimpleList(__pointer(control) pcontrol);

      virtual void _001UpdateDbFlags(__pointer(control) pcontrol);
      virtual void _001UpdateDbFlagsCheckBox(__pointer(control) pcontrol);

      DECL_GEN_SIGNAL(_001OnAppLanguage);

      bool OnCommand(WPARAM wparam,LPARAM lparam);

      bool OnCommandButton(__pointer(control) pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandCheckBox(__pointer(control) pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandComboBox(__pointer(control) pcontrol,UINT uiNotificationCode,LPARAM lparam);

      bool OnCommandEdit(__pointer(control) pcontrol,UINT uiNotificationCode,LPARAM lparam);



      DECL_GEN_SIGNAL(data_on_after_change);


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

//      virtual bool _001IsPointInside(__pointer(control) pcontrol,point64 point);

      //    virtual void control_get_window_rect(__pointer(control) pcontrol,RECT * prect);

      //  virtual void control_get_client_rect(__pointer(control) pcontrol,RECT * prect);



      //virtual bool open_document(const var & varFile) override;


   };


} // namespace user


