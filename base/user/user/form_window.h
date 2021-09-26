#pragma once



namespace user
{


   class CLASS_DECL_BASE form_window :
      virtual public ::user::form_control,
      virtual public ::user::form_callback
   {
   public:



      form_window();
      virtual ~form_window();

      virtual string get_path() override;
      virtual ::e_status open_document(const ::payload & varFile) override;


      //using ::user::interaction::_001IsPointInside;
      virtual bool _001IsPointInside(interaction * pinteraction, point_i64 point) override;
      virtual void control_get_window_rect(interaction * pinteraction, RECTANGLE_I32 * prectangle) override;

      virtual void control_get_client_rect(interaction * pinteraction, RECTANGLE_I32 * prectangle) override;

      //using form_callback::update;
      //using form_control::update;

      virtual bool _001Initialize() override;

      virtual void _017OnAppLanguage() override;
      virtual void _001OnButtonAction(interaction * pinteraction) override;
      virtual void _001OnInitializeForm() override;
      virtual void _001OnInitializeControl(interaction * pinteraction) override;
      void _001UpdateFunctionStatic();
      virtual bool _001OnBeforeSave(interaction * pinteraction) override;
      //virtual void _001RemoveControls() override;
      virtual bool _001Validate(interaction * pinteraction, ::payload & payload);
      virtual bool _001SaveEdit(interaction * pinteraction);
      virtual void on_command(::message::command * pcommand) override;
      DECLARE_MESSAGE_HANDLER(_001OnNotify);
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);
      virtual void _001GetSelection(::database::key & key, ::database::selection & selection) override;
      virtual void Update(bool bSave);
      virtual bool _001SetData(const ::id & id, bool bData);
      virtual bool _001GetData(const ::id & id, bool & bData);
      virtual void _001FillCombo(interaction * pinteraction);

      virtual void WfiOnClose() override;

      DECLARE_MESSAGE_HANDLER(_000OnPosCreate);
      DECLARE_MESSAGE_HANDLER(on_message_create);

      virtual void install_message_routing(::channel * pchannel) override;
      virtual void _001InitializeFormPreData() override;
      virtual void handle(::subject * psubject, ::context * pcontext)  override;
      virtual void _001Update(interaction * pinteraction) override;
      virtual void _001UpdateCheckBox(interaction * pinteraction) override;
      virtual void _001UpdateComboBox(interaction * pinteraction) override;
      virtual void _001UpdateEdit(interaction * pinteraction) override;
      virtual void _001UpdateSimpleList(interaction * pinteraction) override;

      virtual void _001UpdateDbFlags(interaction * pinteraction) override;
      virtual void _001UpdateDbFlagsCheckBox(interaction * pinteraction) override;

      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);

      bool OnCommand(wparam wparam, lparam lparam);

      bool OnCommandButton(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandCheckBox(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandComboBox(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandEdit(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);



      virtual void data_on_after_change(::database::client* pclient, const ::database::key& key, const ::payload & payload, ::subject * psubject = nullptr) override;


      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::id & id) override;
      //virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor) override;

      bool operator == (const interaction & interaction) const;

      //void handle(::subject * psubject, ::context * pcontext) override;
      void _001SetControlFactory();


      
      //virtual ::form_property_set * get_form_property_set() override;
      

   };


} // namespace user










