#pragma once


namespace user
{


   class tab_drop_target_window :
      virtual public ::user::interaction
   {
   public:


      array < enum_position >                m_positiona;
      __pointer(::user::tab)                 m_ptab;
      index                                  m_iTab;


      tab_drop_target_window();
      virtual ~tab_drop_target_window();


      virtual ::e_status initialize_tab_drop_target_window(::user::tab* ptab, index iTab);

      //virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, style_context * pcontext) override;


      virtual void install_message_routing(::channel* pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual bool has_pending_graphical_update() override;

   };


} // namespace user



