#include "framework.h"


namespace user
{


   primitive::primitive()
   {

      m_puiThis = nullptr;

   }


   primitive::~primitive()
   {


   }


#ifdef WINDOWS_DESKTOP


   bool primitive::GetWindowPlacement(WINDOWPLACEMENT * pwndpl)

   {

      UNREFERENCED_PARAMETER(pwndpl);


      return false;

   }

   bool primitive::SetWindowPlacement(const WINDOWPLACEMENT * pcwndpl)

   {

      UNREFERENCED_PARAMETER(pcwndpl);


      return false;

   }


#endif // WINDOWS_DESKTOP


   bool primitive::SetPlacement(const ::rect & rect,UINT nFlags)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(nFlags);

      return false;

   }

   i32 primitive::get_total_page_count(::job * pjob)
   {
      UNREFERENCED_PARAMETER(pjob);
      return 1;
   }



   void primitive::_001OnTimer(::timer * ptimer)
   {

      UNREFERENCED_PARAMETER(ptimer);

   }

   //void primitive::add_thread(::thread * pthread)
   //{

   //   sync_lock sl(mutex());

   //   m_threadptra.add(pthread);

   //}


   //void primitive::remove_thread(::thread * pthread)
   //{

   //   sync_lock sl(mutex());

   //   m_threadptra.remove(pthread);

   //}

   bool primitive::enable_window(bool bEnableWindow)
   {

      return true;

   }


   // Text Edit
   void primitive::_001GetSel(strsize& iBeg, strsize& iEnd) const
   {


   }

   
   index primitive::SelToColumn(strsize iSel)
   {

      return -1;

   }


   index primitive::SelToColumnX(strsize iSel, i32& x)
   {

      return -1;

   }


   index primitive::SelToLine(strsize iSel)
   {

      return -1;

   }


   index primitive::SelToLineX(::draw2d::graphics_pointer& pgraphics, strsize iSel, i32& x)
   {

      return -1;

   }


   strsize primitive::LineColumnToSel(index iLine, index iColumn)
   {

      return -1;

   }


   strsize primitive::LineXToSel(index iLine, i32 x)
   {

      return -1;

   }


   index primitive::CharToLine(strsize iSel)
   {

      return -1;

   }


   void primitive::set_window_text(const char * pszString)
   {


   }


   LRESULT primitive::send_message(UINT uiMessage, WPARAM wparam, lparam lparam)

   {

      __throw(interface_only_exception());

      return 0;

   }


   bool primitive::post_message(UINT message, WPARAM wParam, lparam lParam)

   {

      __throw(interface_only_exception());

      return false;

   }


//   void check::_001SetCheck(::enum_check echeck, const ::action_context & context)
//   {
//
//
//   }
//
//
//
//   void set_text::_001SetText(const string & strText, const ::action_context & context)
//   {
//
//   }

   void primitive::message_handler(::message::base * pbase)
   {

   }


   //void primitive::pre_translate_message(::message::base * pbase)
   //{

   //}


} // namespace user
























