#pragma once





namespace simple_ui
{


   class CLASS_DECL_CORE edit_box :
      virtual public ::user::plain_edit
   {
   public:


      iptr         m_iPos;


      edit_box();
      virtual ~edit_box();


      virtual void install_message_routing(::channel * pchannel);

      
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);

      virtual bool keyboard_focus_is_focusable();


   };



} // namespace simple_ui



