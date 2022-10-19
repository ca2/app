#pragma once


#include "control.h"
#include "aura/user/user/form_callback.h"


namespace user
{


   class CLASS_DECL_AXIS form_window :
      virtual public ::user::form_control,
      virtual public ::user::form_callback
   {
   public:



      form_window();
      ~form_window() override;


      string get_path() override;
      bool open_document(const ::payload & payloadFile) override;


      //using ::user::interaction::_001IsPointInside;
      bool _001IsPointInside(interaction * pinteraction, const point_i64 & point) override;
      void control_get_window_rect(interaction * pinteraction, RECTANGLE_I32 & rectangle) override;

      void control_get_client_rect(interaction * pinteraction, RECTANGLE_I32 & rectangle) override;

      //using form_callback::update;
      //using form_control::update;

      bool _001Initialize() override;

      void _017OnAppLanguage() override;
      void _001OnButtonAction(interaction * pinteraction) override;
      void _001OnInitializeForm() override;
      void _001OnInitializeControl(interaction * pinteraction) override;
      void _001UpdateFunctionStatic();
      bool _001OnBeforeSave(interaction * pinteraction) override;
      //virtual void _001RemoveControls() override;
      virtual bool _001Validate(interaction * pinteraction, ::payload & payload);
      virtual bool _001SaveEdit(interaction * pinteraction);
      void on_command(::message::command * pcommand) override;
      DECLARE_MESSAGE_HANDLER(_001OnNotify);
      DECLARE_MESSAGE_HANDLER(_001OnMessageNotify);
      void _001GetSelection(::database::key & key, ::database::selection & selection) override;
      virtual void Update(bool bSave);
      virtual bool _001SetData(const ::atom & atom, bool bData);
      virtual bool _001GetData(const ::atom & atom, bool & bData);
      virtual void _001FillCombo(interaction * pinteraction);

      void WfiOnClose() override;

      DECLARE_MESSAGE_HANDLER(_000OnPosCreate);
      DECLARE_MESSAGE_HANDLER(on_message_create);

      void install_message_routing(::channel * pchannel) override;
      void _001InitializeFormPreData() override;
      void handle(::topic * ptopic, ::context * pcontext)  override;
      void _001Update(interaction * pinteraction) override;
      void _001UpdateCheckBox(interaction * pinteraction) override;
      void _001UpdateComboBox(interaction * pinteraction) override;
      void _001UpdateEdit(interaction * pinteraction) override;
      void _001UpdateSimpleList(interaction * pinteraction) override;

      void _001UpdateDbFlags(interaction * pinteraction) override;
      void _001UpdateDbFlagsCheckBox(interaction * pinteraction) override;

      DECLARE_MESSAGE_HANDLER(_001OnAppLanguage);

      bool OnCommand(wparam wparam, lparam lparam);

      bool OnCommandButton(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandCheckBox(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandComboBox(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);

      bool OnCommandEdit(interaction * pinteraction, ::u32 uNotificationCode, lparam lparam);



      void data_on_after_change(::database::client* pclient, const ::database::key& key, const ::payload & payload, ::topic * ptopic = nullptr) override;


      //virtual bool create_interaction(::user::interaction * pinteractionParent, const ::atom & atom) override;
      //virtual bool normalize_control_descriptor_typeinfo(class ::user::control_descriptor * pdescriptor) override;

      bool operator == (const interaction & interaction) const;

      //void handle(::topic * ptopic, ::context * pcontext) override;
      void _001SetControlFactory();


      
      //virtual ::form_property_set * get_form_property_set() override;
      

   };


} // namespace user










