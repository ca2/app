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
      ::pointer<::user::document>                m_pdocument;
      bool                       m_bHoverMouse;
      class ::time m_timeLastHover;
      bool                       m_bTimerOn;

      bool                       m_bMouseOver;

      ::pointer<impact>                    m_pimpact;
      ::pointer<pane_impact>               m_ppaneimpact;


      frame(::particle * pparticle);
      void install_message_routing(::channel * pchannel) override;

      DECLARE_MESSAGE_HANDLER(_001OnApp1);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      virtual void _000OnMouse(::message::mouse * pmouse);

      void OnHoverAction();

      virtual bool pre_create_window(::user::system * pusersystem);

      void ShowControlBars(bool bShow);

      virtual ~frame();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      virtual void pre_translate_message(::message::message * pmessage);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer);
      DECLARE_MESSAGE_HANDLER(_001OnApp2000);


      virtual void message_handler(::user::message * pusermessage);


      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace userstack


