#pragma once


namespace console
{


   class CLASS_DECL_SPHERE prompt_frame :
      virtual public simple_frame_window,
      virtual public ::user::message_queue_listener
   {
   public:


      

      bool                       m_bAutoHideOnOutClick;
      int                 m_iAnimateStep;
      ::image::image_list_pointer          m_pimagelist;
      bool                    m_bTimerHide;
      bool                    m_bTimerOn;
      enum_position              m_eposition;
      bool                    m_bMoveDrag;
      bool                    m_bLControl;

      prompt_frame(::particle * pparticle);
      virtual ~prompt_frame();

      void install_message_routing(::channel * pchannel) override;

      void ShowControlBars(bool bShow);


      bool show_mini();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      bool m_bHoverMouse;
      class ::time m_timeLastHover;

      void OnHoverAction(bool bShowWinActionArea);

      void ToFront();

      virtual void on_command(::message::command * pcommand) override;
      virtual void on_command_probe(::message::command * pcommand) override;


      ::user::enum_translucency get_translucency(::user::style * pstyle) override;


      DECLARE_MESSAGE_HANDLER(on_message_create);
      void on_timer(::timer * ptimer) override;

      DECLARE_MESSAGE_HANDLER(on_message_close);
      DECLARE_MESSAGE_HANDLER(on_message_move);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(_001OnApp2000);


      virtual void message_queue_message_handler(::message::message * pmessage) override;

      ::experience::frame * frame_experience() override;
      
      
   };


} // namespace prompt


