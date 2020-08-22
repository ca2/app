#pragma once



namespace user
{


   class CLASS_DECL_AURA form_window :
      virtual public ::user::form_control,
      virtual public ::user::form_callback
   {
   public:



      form_window();
      virtual ~form_window();

      virtual string get_path() override;
      virtual bool open_document(const var & varFile) override;


      using ::user::control::_001IsPointInside;
      virtual bool _001IsPointInside(control * pcontrol, point64 point) override;
      virtual void control_get_window_rect(control * pcontrol, RECT * prect) override;

      virtual void control_get_client_rect(control * pcontrol, RECT * prect) override;

      using form_callback::call_update;
      using form_control::call_update;
      using form_callback::update;
      using form_control::update;

      virtual bool _001Initialize() override;

      virtual void _017OnAppLanguage() override;
      virtual void _001OnButtonAction(control * pcontrol) override;
      virtual void _001OnInitializeForm() override;
      virtual void _001OnInitializeControl(control * pcontrol) override;
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(control * pcontrol) override;
      virtual void _001RemoveControls() override;
      virtual bool _001Validate(control * pcontrol, var & var);
      virtual bool _001SaveEdit(control * pcontrol);
      virtual void on_command(::user::command * pcommand) override;
      DECL_GEN_SIGNAL(_001OnNotify);
      DECL_GEN_SIGNAL(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key, ::database::selection & selection) override;
      virtual void Update(bool bSave);
      virtual bool _001SetData(id uiId, bool bData);
      virtual bool _001GetData(id uiId, bool & bData);
      virtual index _001AddControl(control_descriptor * pdescriptor);
      virtual void _001FillCombo(control * pcontrol);

      virtual void WfiOnClose() override;

      DECL_GEN_SIGNAL(_000OnPosCreate);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData() override;
      virtual void update(::update * pupdate)  override;
      virtual void _001Update(control * pcontrol) override;
      virtual void _001UpdateCheckBox(control * pcontrol) override;
      virtual void _001UpdateComboBox(control * pcontrol) override;
      virtual void _001UpdateEdit(control * pcontrol) override;
      virtual void _001UpdateSimpleList(control * pcontrol) override;

      virtual void _001UpdateDbFlags(control * pcontrol) override;
      virtual void _001UpdateDbFlagsCheckBox(control * pcontrol) override;

      DECL_GEN_SIGNAL(_001OnAppLanguage);

      bool OnCommand(WPARAM wparam, LPARAM lparam);

      bool OnCommandButton(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);

      bool OnCommandCheckBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);

      bool OnCommandComboBox(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);

      bool OnCommandEdit(control * pcontrol, UINT uiNotificationCode, LPARAM lparam);



      virtual void data_on_after_change(::database::client* pclient, const ::database::key& key, const var& var, ::update* pupdate = nullptr) override;


      virtual bool create_control(class control_descriptor * pdescriptor, index iIndex) override;
      virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor) override;

      bool operator == (const control & control) const;

      void on_control_event(::user::control_event * pevent) override;
      void _001SetControlFactory();


      
      //virtual ::form_property_set * get_form_property_set() override;
      

   };


} // namespace user










