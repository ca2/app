#include "framework.h"
#include "aqua/message.h"


namespace message
{

   class ::channel * CreateSignal()
   {
      return new class ::channel();
   }





   CLASS_DECL_AQUA bool is_idle_message(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pbase == nullptr)
         return FALSE;

      // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
      if(pbase->is_message() && (pbase->m_id == WM_MOUSEMOVE || pbase->m_id == WM_NCMOUSEMOVE))
      {
         return TRUE;
      }

      // WM_PAINT and WM_SYSTIMER (caret blink)
      return pbase->m_id != WM_PAINT && pbase->m_id != 0x0118;

   }



   CLASS_DECL_AQUA bool is_idle_message(LPMESSAGE pmsg)

   {

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::account::user interface and happen very
      // often are checked for.

      if(pmsg == nullptr)

         return false;

      // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
      if(pmsg->message == WM_MOUSEMOVE || pmsg->message == WM_NCMOUSEMOVE)

      {
         return true;
      }

      // WM_PAINT and WM_SYSTIMER (caret blink)
      return pmsg->message != WM_PAINT && pmsg->message != 0x0118;


   }




} // namespace message












namespace message
{


   UINT translate_to_os_message(UINT uiMessage)
   {

#ifdef WINDOWS

      switch (uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };
#elif defined(LINUX) ||  defined(__APPLE__) || defined(ANDROID)
      switch (uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };

#else
      switch (uiMessage)
      {
      default:
         return uiMessage;
      };
#endif

   }


   e_prototype get_message_prototype(UINT_PTR uiMessage, UINT uiCode)
   {
      switch (uiMessage)
      {
      case WM_SIZE:
         return PrototypeSize;
      case WM_HSCROLL:
      case WM_VSCROLL:
         return PrototypeScroll;
      case WM_CREATE:
      case WM_NCCREATE:
         return PrototypeCreate;
      case WM_MOVE:
         return PrototypeMove;
      case WM_ACTIVATE:
         return PrototypeActivate;
      case WM_MOUSEACTIVATE:
         return PrototypeMouseActivate;
      case WM_MEASUREITEM:
         return PrototypeMeasureItem;
#ifdef WINDOWS
      case WM_NOTIFY:
         return PrototypeNotify;
#endif
      case WM_COMMAND:
         return PrototypeCommand;
         //{
         //switch (uiCode)
         //{
         //case CN_UPDATE_::user::command:
         //    return PrototypeUpdateCommandUserInterface;
         //default:
         //return PrototypeCommand;
         //}
         //}
      case WM_MOUSEMOVE:
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      case WM_LBUTTONDBLCLK:
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
      case WM_RBUTTONDBLCLK:
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
      case WM_MBUTTONDBLCLK:
      case WM_NCMOUSEMOVE:
      case WM_NCLBUTTONDOWN:
      case WM_NCLBUTTONUP:
         return PrototypeMouse;
#ifdef WINDOWS
      case WM_MOUSEWHEEL:
         return PrototypeMouseWheel;
#endif
      case WM_NCACTIVATE:
         return PrototypeNcActivate;
      case WM_TIMER:
         return PrototypeTimer;
      case WM_KEYDOWN:
      case WM_KEYUP:
      case WM_CHAR:
      case WM_DEADCHAR:
      case WM_SYSKEYDOWN:
      case WM_SYSKEYUP:
      case WM_SYSCHAR:
      case WM_SYSDEADCHAR:
#if(_WIN32_WINNT >= 0x0501)
      case WM_UNICHAR:
#endif
         return PrototypeKey;
      case WM_NCHITTEST:
         return PrototypeNcHitTest;
      case WM_SETCURSOR:
         return PrototypeSetCursor;
      case WM_ERASEBKGND:
         return PrototypeEraseBkgnd;
      case WM_SHOWWINDOW:
         return PrototypeShowWindow;
      case WM_INITMENUPOPUP:
         return PrototypeInitMenuPopup;
      case WM_ENABLE:
         return PrototypeEnable;
         /*#ifdef WINDOWS
         case WM_CTLCOLOR:
         if(pba)
         return PrototypeCtlColor;
         case WM_CTLCOLOR + WM_REFLECT_AXIS:
         return PrototypeCtlColorReflect;
         #endif*/
      case WM_KILLFOCUS:
         return PrototypeKillFocus;
      case WM_SETFOCUS:
         return PrototypeSetFocus;
      case WM_WINDOWPOSCHANGING:
      case WM_WINDOWPOSCHANGED:
         return PrototypeWindowPos;
      case WM_NCCALCSIZE:
         return PrototypeNcCalcSize;
      case message_simple_command:
         return PrototypeSimpleCommand;
      case WM_PAINT:
         return PrototypeNone;
      default:
         return PrototypeNone;
      }
   }


} // namespace message

