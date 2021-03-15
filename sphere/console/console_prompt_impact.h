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


      prompt_impact(::context_object * pcontextobject);
      virtual ~prompt_impact();


      virtual void install_message_routing(::channel * pchannel);


      virtual int getch();
      virtual int ungetch(int c);
      virtual void clear();

      void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);
      virtual bool keyboard_focus_is_focusable();

      DECL_GEN_SIGNAL(on_message_create);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual void interpret_command();

   };


} // namespace console








































