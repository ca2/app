#pragma once



namespace console
{


   class CLASS_DECL_SPHERE prompt_impact :
      virtual public ::user::impact
   {
   public:


      
      millis                 m_millisCaretStart;

      millis                 m_millisCaretPeriod;

      strsize              m_iCursor;

      ::size_i32               m_sizeChar;

      string               m_strCommand;

      event                m_evNewChar;

      strsize              m_iNewChar;

      millis m_millisLastError;

      bool                 m_bOk;


      prompt_impact(::object * pobject);
      virtual ~prompt_impact();


      virtual void install_message_routing(::channel * pchannel);


      virtual int getch();
      virtual int ungetch(int c);
      virtual void clear();

      void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);
      virtual bool keyboard_focus_is_focusable();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnKeyDown);
      DECLARE_MESSAGE_HANDLER(_001OnKeyUp);
      DECLARE_MESSAGE_HANDLER(_001OnShowWindow);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual void interpret_command();

   };


} // namespace console








































