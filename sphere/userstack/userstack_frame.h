#pragma once


namespace userstack
{


   class CLASS_DECL_SPHERE frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:


      
      ::user::message_queue_pointer   m_spqueue;


      image_list  *              m_pimagelist;
      __pointer(::user::document)                 m_pdocument;
      bool                       m_bHoverMouse;
      ::duration m_durationLastHover;
      bool                       m_bTimerOn;

      bool                       m_bMouseOver;

      __pointer(impact)                     m_pimpact;
      __pointer(pane_view)                m_ppaneview;


      frame(::object * pobject);
      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(_001OnApp1);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      virtual void _000OnMouse(::message::mouse * pmouse);

      void OnHoverAction();

      virtual bool pre_create_window(::user::system * pusersystem);

      void ShowControlBars(bool bShow);

      virtual ~frame();

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual void pre_translate_message(::message::message * pmessage);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer);
      DECLARE_MESSAGE_HANDLER(_001OnApp2000);


      virtual void message_handler(::user::message * pusermessage);


      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace userstack


