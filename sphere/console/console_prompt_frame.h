#pragma once


namespace console
{


   class CLASS_DECL_SPHERE prompt_frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:


      

      bool                       m_bAutoHideOnOutClick;
      i32                 m_iAnimateStep;
      __pointer(image_list)          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      enum_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

      prompt_frame(::object * pobject);
      virtual ~prompt_frame();

      virtual void install_message_routing(::channel * pchannel) override;

      void ShowControlBars(bool bShow);


      bool show_mini();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      bool m_bHoverMouse;
      millis m_millisLastHover;

      void OnHoverAction(bool bShowWinActionArea);

      void ToFront();

      virtual void on_command(::message::command * pcommand) override;
      virtual void on_command_probe(::message::command * pcommand) override;


      virtual ::user::enum_translucency get_translucency(::user::style * pstyle) const override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer) override;

      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnApp2000);


      virtual void message_queue_message_handler(::message::message * pmessage) override;

      ::experience::frame * experience_get_frame() override;
      
      
   };


} // namespace prompt


