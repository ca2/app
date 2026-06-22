//
// Created by camilo on 06/02/2022 12:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
//#include "details_window.h"
//#include "button.h"
//#include "acme/user/user/mouse.h"
//#include "acme/windowing/window.h"
//#include "acme/platform/system.h"
//#include "acme/windowing/display.h"
//#include "acme/windowing/windowing.h"
//
//
//namespace micro
//{
//
//
//   details_window::details_window()
//   {
//
//      m_efont = e_font_monospace;
//
//      m_strLabelDetails = "Dump to file";
//
//   }
//
//
//   details_window::~details_window()
//   {
//
//
//   }
//
//
//   void details_window::calculate_size()
//   {
//
//
//#if !defined(UNIVERSAL_WINDOWS) && !defined(__ANDROID__)
//
//      //::i32 wScreen = 1280;
//      //::i32 hScreen = 768;
//
//      auto sizeScreen = system()->acme_windowing()->acme_display()->get_main_screen_size();
//
//      //operating_system_get_main_screen_size(wScreen, hScreen);
//
//      auto wScreen = sizeScreen.cx;
//
//      auto hScreen = sizeScreen.cy;
//
//      ::i32 w = wScreen / 2;
//      ::i32 h = (w / 8) * 5;
//      ::i32 x = (wScreen - w) / 2;
//      ::i32 y = (hScreen - h) / 2;
//
//      m_rectangle.set_dimension(x, y, w, h);
//
//#endif
//
//   }
//
//
//   void details_window::on_click(const ::payload & payload, ::user::mouse * pmouse)
//   {
//
//      if (payload == "details")
//      {
//
//         //string m_strDetails;
//
//         ::cast < ::message_box_payload > pmessageboxpayload = m_pdialog;
//
//         display_temporary_file_with_text(pmessageboxpayload->m_strDetails);
//
//         //pdetailswindow->display_synchronously(m_strDetails, m_strTitle + " : Details", ::user::e_message_box_ok, m_strDetails);
//
//         //m_atomResult.clear();
//
//         pmouse->m_bRet = true;
//
//         return;
//
//      }
//
//      ::micro::message_box::on_click(payload, pmouse);
//
////      return false;
//      
//   }
//
//
//
//} // namespace micro
//
//
