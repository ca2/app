#pragma once


namespace app_message_box
{


   class CLASS_DECL_APP_MESSAGE_BOX main_window :
      virtual public ::app_app::main_window
   {
   public:


      __pointer(::user::button)     m_pbuttonShowMessageBox;


      main_window();
      ~main_window() override;


      virtual void on_create_user_interaction() override;

      //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem) override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void show_message_box();


   };


} // namespace app_message_box












