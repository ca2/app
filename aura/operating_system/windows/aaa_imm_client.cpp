#include "framework.h"
//#include "base/user/user/_component.h"
//#include "imm_client.h"
#include "aura/os/windows/imm_context.h"


#ifdef WINDOWS_DESKTOP


imm_client::imm_client()
{

   m_bImeCancelling = false;
   m_bImeCandidateOpened = false;

}


imm_client::~imm_client()
{


}


void imm_client::install_message_routing(::channel * pchannel)
{

   MESSAGE_LINK(e_message_set_focus, pchannel, this, &::imm_client::on_message_set_focus);
   MESSAGE_LINK(e_message_kill_focus, pchannel, this, &::imm_client::on_message_kill_focus);
   MESSAGE_LINK(WM_IME_SETCONTEXT, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_STARTCOMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_COMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_ENDCOMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_NOTIFY, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_KEYDOWN, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_KEYUP, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_IME_SELECT, pchannel, this, &::imm_client::_001OnIme);
   MESSAGE_LINK(WM_INPUTLANGCHANGE, pchannel, this, &::imm_client::_001OnIme);

   MESSAGE_LINK(e_message_char, pchannel, this, &::imm_client::_011OnChar);
   MESSAGE_LINK(WM_IME_CHAR, pchannel, this, &::imm_client::_011OnChar);

   MESSAGE_LINK(e_message_key_down, pchannel, this, &::imm_client::on_message_key_down);


}





void imm_client::on_message_set_focus(::message::message * pmessage)
{

}


void imm_client::on_message_kill_focus(::message::message * pmessage)
{

   m_bImeCandidateOpened = false;

}


void imm_client::_011OnChar(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   if (pusermessage->m_atom == e_message_char)
   {

      auto psession = get_session();

      if (psession->is_key_pressed(::user::e_key_control)
         || psession->is_key_pressed(::user::e_key_alt))
      {

         return;

      }

      if (pusermessage->m_wparam == '\b')
      {

         return;

      }

      if (pusermessage->m_wparam == '\t')
      {

         return;

      }

      wchar_t wsz[2];
      wsz[0] = (wchar_t) pusermessage->m_wparam;
      wsz[1] = '\0';

      string strChar;

      strChar = wsz;

      //if (!::str().begins_eat_ci(m_strImeComposition, strChar))
      //{

      insert_text(strChar, false, e_source_user);

      //}

   }

}


void imm_client::insert_text(string str, bool bForceNewStep, const ::action_context & context)
{


}


void imm_client::_001OnIme(::message::message * pmessage)
{

   synchronous_lock synchronouslock(mutex());

#ifdef WINDOWS_DESKTOP

   ::pointer<::user::message>pusermessage(pmessage);

   if (pmessage->m_atom == WM_INPUTLANGCHANGE)
   {

      ::output_debug_string("WM_INPUTLANGCHANGE");

      //get_wnd()->pred([this]()
      //   {

      //      imm_context imm(this);

      //      if (!ImmGetOpenStatus(imm))
      //      {

      //         ImmSetOpenStatus(imm, true);

      //      }
      //
      //      //SendMessage(ImmGetDefaultIMEWnd(get_handle()), WM_IME_CONTROL, IMC_OPENSTATUSWINDOW, 0);

      //      //   output_debug_string("window already open");

      //      //}

      //      //


      //   });

   }
   else if (pmessage->m_atom == WM_IME_SELECT)
   {

      //SetInputLanguage();

   }
   else if (pmessage->m_atom == WM_IME_SETCONTEXT)
   {

      //EnableIME();

   }
   else if (pmessage->m_atom == WM_IME_COMPOSITION)
   {

      if (pmessage->m_lparam == 0)
      {

         ::output_debug_string("\nWM_IME_COMPOSITION Cancellation...");

         if (m_strImeComposition.has_char())
         {

            edit_undo();

            m_strImeComposition.Empty();

         }

      }
      else
      {

         ::output_debug_string("\nWM_IME_COMPOSITION " + __string((::i64) pusermessage->m_lparam.m_lparam));

         if ((pmessage->m_lparam & GCS_RESULTSTR) != 0)
         {

            ::output_debug_string("\nWM_IME_COMPOSITION Result String... ");

            imm_context imm(this);

            string strComposition;

            strComposition = imm.get_string(GCS_RESULTSTR);

            if (strComposition.is_empty())
            {

               strComposition = imm.get_string(GCS_RESULTREADSTR);

            }

            ::output_debug_string("\nWM_IME_COMPOSITION Compositè String Length = " + __string(strComposition.get_length()));

            on_text_composition(strComposition);

            on_text_composition_done();

         }

         if ((pmessage->m_lparam & GCS_COMPSTR) != 0)
         {

            ::output_debug_string("\nWM_IME_COMPOSITION Compositing... ");

            imm_context imm(this);

            string strComposition;

            strComposition = imm.get_string(GCS_COMPSTR);

            ::output_debug_string("\nGCS_COMPSTR \"" + strComposition + "\"");

            wstring wstrComposition;

            wstrComposition = strComposition;

            if (strComposition.is_empty())
            {

               strComposition = imm.get_string(GCS_COMPREADSTR);

               ::output_debug_string("\nGCS_COMPREADSTR \"" + strComposition + "\"");

            }

            on_text_composition(strComposition);

         }

      }

      pusermessage->m_bRet = true;

   }
   else if (pmessage->m_atom == WM_IME_KEYDOWN)
   {

      INFORMATION("WM_IME_KEYDOWN");

   }
   else if (pmessage->m_atom == WM_IME_ENDCOMPOSITION)
   {

      INFORMATION("WM_IME_ENDCOMPOSITION");

   }
   else if (pmessage->m_atom == WM_IME_STARTCOMPOSITION)
   {

      INFORMATION("WM_IME_STARTCOMPOSITION");

      m_bImeCancelling = false;

      on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION);

      pusermessage->m_bRet = true;

   }
   else if (pmessage->m_atom == WM_IME_NOTIFY)
   {

      if (pusermessage->m_wparam == IMN_SETCANDIDATEPOS)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCANDIDATEPOS");

      }
      else if (pusermessage->m_wparam == IMN_SETCOMPOSITIONFONT)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCOMPOSITIONFONT");

      }
      else if (pusermessage->m_wparam == IMN_SETCOMPOSITIONWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCOMPOSITIONWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_SETSTATUSWINDOWPOS)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETSTATUSWINDOWPOS");

      }
      else if (pusermessage->m_wparam == IMN_OPENCANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_OPENCANDIDATE");

         m_bImeCandidateOpened = true;

      }
      else if (pusermessage->m_wparam == IMN_CHANGECANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CHANGECANDIDATE");

         m_bImeCandidateOpened = true;

      }
      else if (pusermessage->m_wparam == IMN_CLOSECANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CLOSECANDIDATE");

         m_bImeCandidateOpened = false;

      }
      else if (pusermessage->m_wparam == IMN_OPENSTATUSWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_OPENSTATUSWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_CLOSESTATUSWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CLOSESTATUSWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_SETSTATUSWINDOWPOS)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETSTATUSWINDOWPOS");

      }
      else if (pusermessage->m_wparam == IMN_SETCONVERSIONMODE)
      {

         imm_context imm(this);

         DWORD dwConversion = 0;

         DWORD dwSentence = 0;

         ImmGetConversionStatus(imm, &dwConversion, &dwSentence);

         string str;

         str.format("\n" "WM_IME_NOTIFY" " > " "IMN_SETCONVERSIONMODE conversion=%d sentence=%d", dwConversion, dwSentence);

         str += "\n";

         if (dwConversion == IME_CMODE_ALPHANUMERIC)
         {

            str += "alphanumeric mode; ";

         }
         else
         {
            if (dwConversion & IME_CMODE_NATIVE)
            {

               str += "native mode; ";

            }

            if (dwConversion & IME_CMODE_KATAKANA)
            {

               str += "katakana mode; ";

            }
            if (dwConversion & IME_CMODE_LANGUAGE)
            {

               str += "language mode; ";

            }

            if (dwConversion & IME_CMODE_FULLSHAPE)
            {

               str += "full shape mode; ";

            }
            if (dwConversion & IME_CMODE_ROMAN)
            {

               str += "roman mode; ";

            }
            if (dwConversion & IME_CMODE_CHARCODE)
            {

               str += "char code mode; ";

            }
            if (dwConversion & IME_CMODE_HANJACONVERT)
            {

               str += "hanja mode; ";

            }
            if (dwConversion & IME_CMODE_NATIVESYMBOL)
            {

               str += "native symbol mode; ";

            }

         }

         output_debug_string(str);

      }
      else
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " + __string((::i64)pusermessage->m_wparam) + "    ");

      }

   }

#endif

}


void imm_client::on_message_key_down(::message::message * pmessage)
{

#ifdef WINDOWS_DESKTOP

   auto pkey = pmessage->m_union.m_pkey;

   if (pkey->m_ekey == ::user::e_key_escape)
   {

      if (m_bImeCandidateOpened)
      {

         imm_context imm(this);

         imm.close_candidate();

      }

      if (m_strImeComposition.has_char())
      {

         m_bImeCancelling = true;

         imm_context imm(this);

         ::ImmNotifyIME(imm, NI_COMPOSITIONSTR, CPS_CANCEL, 0);

         edit_undo();

         m_strImeComposition.Empty();

         pkey->m_bRet = true;

         return;

      }

   }

#endif

}


void imm_client::on_text_composition(string str)
{

}



void imm_client::on_text_composition_done()
{

   m_bImeCandidateOpened = false;

}


bool imm_client::is_text_composition_active() const
{

   return m_bImeCandidateOpened;

}


int imm_client::on_text_composition_message(int iMessage)
{

#ifdef WINDOWS_DESKTOP

   if (iMessage == TEXT_COMPOSITION_MESSAGE_UPDATE_CARET)
   {

      //strsize iBeg;
      //strsize iEnd;

      //_001GetSel(iBeg, iEnd);

      //i32 x;
      //i32 iLine = SelToLineX(iEnd, x);




      //int y = (iLine)* m_iLineHeight - get_context_offset().y;
      //int y2 = y + m_iLineHeight;
      // ::point_i32 point(x, y);
      //::rectangle_i32 r;
      //get_client_rect(rectangle);
      //rectangle.left = x;
      //rectangle.top = y;
      //rectangle.bottom = y2;
      //client_to_screen(rectangle);
      //get_wnd()->screen_to_client(rectangle);


      //SetCaretPos(rectangle.left, rectangle.top);
      //ShowCaret(get_handle());
   }
   else if (iMessage == TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION)
   {

      imm_context imm(this);

      if (!imm)
      {

         return 0;

      }

      ::rectangle_i32 rectangle;

      get_text_composition_area(rectangle);

      COMPOSITIONFORM com = {};

      com.dwStyle = CFS_FORCE_POSITION;
      com.ptCurrentPos = rectangle.top_left();
      com.ptCurrentPos.y -= 100;
      ::rectangle_i32 rect2(rectangle);
      rect2.offset_y(-100);
      com.dwStyle = CFS_RECT;
      com.rcArea = rect2;

      //ShowCaret(get_handle());

      //auto pstyle = get_style(pgraphics);

      //auto pfont = get_font(pstyle);

      //if (pfont)
      //{

      //   LOGFONTW lf = {};

      //   if (pfont->GetLogFont(&lf))
      //   {

      //      if (ImmSetCompositionFontW(imm, &lf))
      //      {

      //         output_debug_string("set ime composition font (Unicode) pos");

      //      }



      //   }

      //}

      if (::ImmSetCompositionWindow(imm, &com))
      {
         output_debug_string("set ime composition window pos");
      }

      CANDIDATEFORM can = {};

      can.dwStyle = CFS_CANDIDATEPOS;

      can.ptCurrentPos = rectangle.bottom_left();

      if (::ImmSetCandidateWindow(imm, &can))
      {

         output_debug_string("set ime candidate window pos");

      }

      return 1;

   }

#endif

   return 0;

}



#endif



