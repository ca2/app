#pragma once



namespace console
{


   class CLASS_DECL_SPHERE prompt_impact :
      virtual public ::user::impact
   {
   public:


      
      class ::time                 m_timeCaretStart;

      class ::time                 m_timeCaretPeriod;

      strsize              m_iCursor;

      ::size_i32               m_sizeChar;

      string               m_strCommand;

      event                m_evNewChar;

      strsize              m_iNewChar;

      class ::time m_timeLastError;

      bool                 m_bOk;


      prompt_impact(::particle * pparticle);
      virtual ~prompt_impact();


      void install_message_routing(::channel * pchannel) override;


      virtual int getch();
      virtual int ungetch(int c);
      virtual void clear();

      void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);
      virtual bool keyboard_focus_is_focusable();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual void interpret_command();

   };


} // namespace console








































