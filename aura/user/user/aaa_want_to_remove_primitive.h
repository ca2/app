#pragma once


namespace user
{


   class interaction;


   class CLASS_DECL_AURA primitive:
      virtual public channel,
      virtual public ::aura::drawable,
      virtual public ::user::check,
      virtual public ::user::text
   {
   public:


      interaction *     m_puiThis;


      primitive();
      virtual ~primitive();

      inline oswindow get_safe_handle() const;

#ifdef WINDOWS_DESKTOP

      virtual bool GetWindowPlacement(WINDOWPLACEMENT* pwndpl);


      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* pwndpl);


#endif

      virtual bool SetPlacement(const ::rect & rect,UINT nFlags = SWP_SHOWWINDOW);

      virtual i32 get_total_page_count(::job * pjob);

      virtual void _001OnTimer(::timer * ptimer);

      virtual bool enable_window(bool bEnable = true);

      // Text Edit
      virtual void _001GetSel(strsize& iBeg, strsize& iEnd) const;
      virtual index SelToColumn(strsize iSel);
      virtual index SelToColumnX(strsize iSel, i32& x);
      virtual index SelToLine(strsize iSel);
      virtual index SelToLineX(strsize iSel, i32& x);
      virtual strsize LineColumnToSel(index iLine, index iColumn);
      virtual strsize LineXToSel(index iLine, i32 x);
      virtual index CharToLine(strsize iSel);


      virtual void set_window_text(const char * pszString);

      //virtual void _001SetCheck(enum_check echeck, const ::action_context & action_context);
      //virtual void _001SetText(const string & strText, const ::action_context & action_context);

      virtual ::user::primitive * first_child_user_primitive();
      virtual ::user::primitive * top_user_primitive();
      virtual ::user::primitive * under_user_primitive();
      virtual ::user::primitive * above_user_primitive();
      virtual ::user::primitive * next_user_primitive();
      virtual ::user::primitive * previous_user_primitive();

   };


} // namespace user



