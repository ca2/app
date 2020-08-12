#pragma once



namespace console
{


   class CLASS_DECL_SPHERE prompt_impact :
      virtual public ::user::impact
   {
   public:


      
      tick                 m_tickCaretStart;

      tick                 m_tickCaretPeriod;

      strsize              m_iCursor;

      ::size               m_sizeChar;

      string               m_strCommand;

      event                m_evNewChar;

      strsize              m_iNewChar;

      tick m_tickLastError;

      bool                 m_bOk;


      prompt_impact(::object * pobject);
      virtual ~prompt_impact();


      virtual void install_message_routing(::channel * pchannel);


      virtual int getch();
      virtual int ungetch(int c);
      virtual void clear();

      void simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics);
      virtual bool keyboard_focus_is_focusable();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      virtual void interpret_command();

   };


} // namespace console








































