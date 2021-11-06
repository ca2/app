#pragma once



namespace simple_ui
{


   class top :
      virtual public ::user::interaction,
      virtual public ::simple_ui::style
   {
   public:


      bool                       m_bLButtonDown;
      ::point_i32                    m_pointLButtonDown;
      ::size_i32                     m_sizeLButtonDownOffset;

      bool                       m_bDrag;



      top();
      virtual ~top();


      void install_message_routing(::channel * pchannel) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);

      DECLARE_MESSAGE_HANDLER(_001OnActivate);
      DECLARE_MESSAGE_HANDLER(_001OnNcActivate);
      DECLARE_MESSAGE_HANDLER(_001OnSysCommand);

   };


} // namespace simple_ui




