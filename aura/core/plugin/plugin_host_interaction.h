#pragma once


namespace plugin
{


   class instance;
   enum enum_check;
   class plugin;


   class CLASS_DECL_AURA host_interaction :
      public ::user::box
   {
   public:


      enum
      {
         message_check = WM_USER + 10,
      };


      ::user::interaction *     m_pframe;
      plugin *                m_pplugin;




      host_interaction(::layered * pobjectContext);
      virtual ~host_interaction();

      void install_message_routing(::channel * pmessage);

      virtual void _000OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual bool defer_check(enum_check echeck);
      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


//      using ::user::box::get_window_rect;
//      virtual bool get_window_rect(RECT64 * prect);
//
//
//
//      using ::user::box::get_client_rect;
//      virtual bool get_client_rect(RECT64 * prect);
//


      virtual bool is_window_visible();

      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnCheck);
      DECL_GEN_SIGNAL(_001OnCreate);

      virtual bool RedrawWindow(const ::rect & rectUpdate, ::draw2d::region * prgnUpdate, UINT flags);

      ::user::interaction * get_os_focus_uie();

      //void _on_start_user_message_handler();
      void _user_message_handler(::message::base * pmessage);

      virtual void _000OnMouse(::message::mouse * pmouse);

      DECL_GEN_SIGNAL(on_ignore_message);
      void _001OnTimer(::timer * ptimer);


      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, lparam lparam);



   };


} // namespace plugin



