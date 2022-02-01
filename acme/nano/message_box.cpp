//
// Created by camilo on 2021-01-21 14:57 <3ThomasBorregaardSørensen
// Generalization by camilo on 31/01/2022 14:53 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"
#include "_nano.h"


nano_message_box::nano_message_box()
{

   m_bStartCentered = true;

}


nano_message_box::~nano_message_box()
{


}


void nano_message_box::on_draw(nano_device * pnanodevice)
{

   rectangle_i32 rectangleText;

   get_client_rectangle(rectangleText);

   rectangleText.bottom = rectangleText.top + rectangleText.height() * 3 / 4;

   rectangleText.deflate(25);

   pnanodevice->draw_text(m_strMessage, rectangleText, e_align_top_left, m_pbrushWindow, m_pbrushText, m_pfont);

}


//void nano_message_box::on_mouse_down(int x, int y)
//{
//   SetCapture(m_hwnd);
//   m_edialogresultMouseDown = hit_test(x, y);

//}
//void nano_message_box::on_mouse_up(int x, int y)
//{
//   ReleaseCapture();
//   m_edialogresultMouseUp = hit_test(x, y);
//}

//   enum_dialog_result nano_message_box::get_result()
//   {
//
//      if (m_edialogresultMouseUp == m_edialogresultMouseDown)
//      {
//
//         return m_edialogresultMouseUp;
//
//      }
//
//      return e_dialog_result_none;
//   }
//};

//LRESULT CALLBACK nano_message_box::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//   if (msg == WM_NCCREATE)
//   {
//
//      CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
//      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pcreatestruct->lpCreateParams);
//
//   }
//   nano_message_box * pbox = (nano_message_box *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//
//   if (!pbox)
//   {
//      return DefWindowProc(hwnd, msg, wParam, lParam);
//   }
//   return pbox->window_procedure(msg, wParam, lParam);
//
//LRESULT nano_message_box::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
//{
//   switch (message)
//   {
//   case WM_CLOSE:
//      DestroyWindow(hwnd);
//      break;
//   case WM_DESTROY:
//      PostQuitMessage(0);
//      break;
//   case WM_CREATE:
//   {
//      m_hwnd = hwnd;
//
//      update_drawing_objects();
//   }
//   break;
//   case WM_LBUTTONDOWN:
//      on_mouse_down(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//      break;
//   case WM_LBUTTONUP:
//   {
//      on_mouse_up(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//      if (get_result() != e_dialog_result_none)
//      {
//
//         ::DestroyWindow(hwnd);
//
//      }
//   }
//
//   break;
//   case WM_PAINT:
//   {
//      PAINTSTRUCT paintstruct{};
//      HDC hdc = BeginPaint(hwnd, &paintstruct);
//      draw(hdc);
//      EndPaint(hwnd, &paintstruct);
//   }
//   break;
//   default:
//      return DefWindowProc(hwnd, msg, wParam, lParam);
//   }
//   return 0;
//}
//
//
//HINSTANCE nano_message_box_hinstance()
//{
//
//   HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");
//
//   if (hinstanceWndProc == nullptr)
//   {
//
//      hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);
//
//   }
//
//   return hinstanceWndProc;
//
//}
//
//void register_nano_message_box_window_class()
//{
//
//   if (g_bNanoMessageBoxRegistered)
//   {
//
//      return;
//
//   }
//
//   auto hinstanceWndProc = nano_message_box_hinstance();
//
//   WNDCLASSEX wndclassex;
//
//   //Step 1: Registering the Window Class
//   wndclassex.cbSize = sizeof(WNDCLASSEX);
//   wndclassex.style = 0;
//   wndclassex.lpfnWndProc = &message_box_window_procedure;
//   wndclassex.cbClsExtra = 0;
//   wndclassex.cbWndExtra = 0;
//   wndclassex.hInstance = hinstanceWndProc;
//   wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//   wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
//   wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//   wndclassex.lpszMenuName = NULL;
//   wndclassex.lpszClassName = _T(NANO_MESSAGE_BOX_WINDOW_CLASS);
//   wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//   if (!RegisterClassEx(&wndclassex))
//   {
//
//      throw_status(error_failed, "Failed to register nano message box window class.");
//
//   }
//
//   g_bNanoMessageBoxRegistered = true;
//
//}


void nano_message_box::add_button(const char * pszText, enum_dialog_result edialogresult)
{

   auto pbutton = __new(nano_button);

   pbutton->m_strText = pszText;
   pbutton->m_id = edialogresult;

   add_child(pbutton);

}


void nano_message_box::display_synchronously(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
{

   auto sizeScreen = operating_system_get_main_screen_size();

   int wScreen = sizeScreen.cx;
   int hScreen = sizeScreen.cy;

   int w = wScreen / 2;
   int h = (w / 16) * 5;
   int x = (wScreen - w) / 2;
   int y = (hScreen - h) / 2;

   m_rectangle.set_dim(x, y, w, h);

   m_strMessage = strMessage;

   m_strTitle = strTitle;

   auto emessageboxType = emessagebox & e_message_box_type_mask;

   switch (emessageboxType)
   {
      case e_message_box_ok_cancel:
         add_button("OK", e_dialog_result_ok);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_abort_retry_ignore:
         add_button("Abort", e_dialog_result_abort);
         add_button("Retry", e_dialog_result_retry);
         add_button("Ignore", e_dialog_result_ignore);
         break;
      case e_message_box_yes_no_cancel:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_yes_no:
         add_button("Yes", e_dialog_result_yes);
         add_button("No", e_dialog_result_no);
         break;
      case e_message_box_retry_cancel:
         add_button("Retry", e_dialog_result_retry);
         add_button("Cancel", e_dialog_result_cancel);
         break;
      case e_message_box_cancel_try_continue:
         add_button("Cancel", e_dialog_result_cancel);
         add_button("Try", e_dialog_result_retry);
         add_button("Continue", e_dialog_result_continue);
         break;
      default:
         add_button("OK", e_dialog_result_ok);
         break;
   }

   if (emessagebox & e_message_box_default_button_mask)
   {

      int iDefaultButton = ((int)(emessagebox & e_message_box_default_button_mask) >> 4) & 7;

      if (emessagebox & e_message_box_default_button_1)
      {

         m_childa[iDefaultButton]->set_focus();

      }

   }

   int wButton = 150;

   int hButton = 50;

   int iRight = m_rectangle.width() - 25;

   int iBottom = m_rectangle.height() - 25;

   int wSpacing = 25;

   for (index iChild = m_childa.get_upper_bound(); iChild >= 0; iChild--)
   {

      auto pchild = m_childa[iChild];

      pchild->m_rectangle.bottom = iBottom;
      pchild->m_rectangle.top = pchild->m_rectangle.bottom - hButton;
      pchild->m_rectangle.right = iRight;
      pchild->m_rectangle.left = pchild->m_rectangle.right - wButton;

      iRight = pchild->m_rectangle.left - wSpacing;

   }

   create();

   nano_window::display_synchronously();

}





//__pointer(::sequence < ::conversation >) nano_message_box::display(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
//{
//
//   auto psequence = __new(::sequence <::conversation >());
//
//   psequence->m_p = this;
//
//   fork([strMessage, strTitle, emessagebox, psequence]()
//      {
//
//         psequence->m_p->display_synchronously(strMessage, strTitle, emessagebox);
//
//         psequence->on_sequence();
//
//      });
//
//   return psequence;
//
//}


//LRESULT nano_message_box::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
//{
//
//   return ::DefWindowProc(m_hwnd, message, wparam, lparam);
//
//}




CLASS_DECL_ACME ::id os_message_box(::object * pobject, const char * pszMessage, const char * pszTitle, enum_message_box emessagebox)
{

   initialize_nano();

   auto pmessagebox = pobject->__create_new < nano_message_box >();

   pmessagebox->display_synchronously(pszMessage, pszTitle, emessagebox);

   auto idResult = pmessagebox->get_result();

   return idResult;

}

