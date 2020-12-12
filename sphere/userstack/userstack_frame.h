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
      millis m_millisLastHover;
      bool                       m_bTimerOn;

      bool                       m_bMouseOver;

      __pointer(view)                     m_pview;
      __pointer(pane_view)                m_ppaneview;


      frame(::layered * pobjectContext);
      virtual void install_message_routing(::channel * pchannel);

      DECL_GEN_SIGNAL(_001OnApp1);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      virtual void _000OnMouse(::message::mouse * pmouse);

      void OnHoverAction();

      virtual bool pre_create_window(::user::create_struct * pcreatestruct);

      void ShowControlBars(bool bShow);

      virtual ~frame();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void pre_translate_message(::message::message * pmessage);

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(_001OnApp2000);


      virtual void message_handler(::message::base * pbase);


      virtual void message_queue_message_handler(::message::message * pmessage);


   };


} // namespace userstack


