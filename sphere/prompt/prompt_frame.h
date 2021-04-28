#pragma once


namespace prompt
{


   class CLASS_DECL_SPHERE frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:


      
      ::user::message_queue_pointer   m_spqueue;

      bool                       m_bAutoHideOnOutClick;
      i32                 m_iAnimateStep;
      __pointer(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      enum_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

      frame(::object * pobject);
      virtual ~frame();

      virtual void install_message_routing(::channel * pchannel);

      void ShowControlBars(bool bShow);


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      bool m_bHoverMouse;
      millis m_millisLastHover;

      void OnHoverAction(bool bShowWinActionArea);

      void ToFront();

      virtual void on_command(::message::command * pcommand);
      virtual void on_command_probe(::message::command * pcommand);



      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer);

      DECLARE_MESSAGE_HANDLER(_001OnClose);
      DECLARE_MESSAGE_HANDLER(_001OnMove);
      DECLARE_MESSAGE_HANDLER(_001OnShowWindow);
      DECLARE_MESSAGE_HANDLER(_001OnApp2000);


      virtual void message_queue_message_handler(::message::message * pmessage);
   };


} // namespace prompt


