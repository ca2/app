﻿#include "framework.h"
#include "_windows_runtime.h"
//#include "apex/node/universal_windows/_windows_runtime.h"
//#include "apex/os/windows_common/draw2d_direct2d_global.h"


CLASS_DECL_APEX int g_iMouse = -1;


//CLASS_DECL_APEX int_bool GetCursorPos(POINT_I32 * lppoint);

//
//CLASS_DECL_APEX int_bool ui_get_cursor_pos(POINT_I32 * ppt)
//{
//
//   if (ppt == nullptr)
//      return false;
//
//   int_bool iRet = false;
//
//   ::point_i32 pointCursor;
//
//   ::wait(::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([=, &pointCursor, &iRet]()
//   {
//
//      try
//      {
//
//         iRet = ::GetCursorPos(&pointCursor);
//
//      }
//      catch (...)
//      {
//
//      }
//
//   })));
//
//   if (iRet != false)
//   {
//
//      *ppt = pointCursor;
//
//   }
//
//   return iRet;
//
//}
//

//int g_iMouseX = 0;
//int g_iMouseY = 0;
//

//CLASS_DECL_APEX int_bool GetCursorPos(POINT_I32 * lppoint)
//{
//
//   lppoint->x = g_iMouseX;
//
//   lppoint->y = g_iMouseY;
//
//   if (g_iMouse < 0)
//      return false;
//
//   ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
//          ref new ::winrt::Windows::UI::Core::DispatchedHandler([]()
//   {
//
//      ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Devices::Input::PointerDevice ^ > ^ deva = ::winrt::Windows::Devices::Input::PointerDevice::GetPointerDevices();
//
//      for (unsigned int u = 0; u < deva->Size; u++)
//      {
//
//         ::winrt::Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(u);
//
//         if (dev->PointerDeviceType == ::winrt::Windows::Devices::Input::PointerDeviceType::Mouse)
//         {
//
//            ::winrt::Windows::UI::Input::PointerPoint ^ pointerPoint = ::winrt::Windows::UI::Input::PointerPoint::GetCurrentPoint(g_iMouse);
//
//            g_iMouseX = (::i32)pointerPoint->RawPosition.X;
//
//            g_iMouseY = (::i32)pointerPoint->RawPosition.Y;
//
//         }
//
//      }
//
//   }));
//
//   return true;
//
//}




CLASS_DECL_APEX void defer_dock_application(int_bool bDock)
{

   __UNREFERENCED_PARAMETER(bDock);

}

//CLASS_DECL_APEX void main_branch(::matter* pobjectTask, enum_priority epriority)
//{
//
//   ::wait(
//      ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([pobjectTask]()
//   {
//
//      pobjectTask->operator()();
//
//   })));
//
//}
//
//#undef papplication
//
//::winrt::Windows::UI::Xaml::papplication^ get_xaml_app();
//
//
//
//
//
//
//
//
//
//#undef ::apex::get_system()
//#undef Platform
//
//using namespace Platform;
//using namespace Microsoft::WRL;
//using namespace ::winrt::Windows::Foundation;
//using namespace ::winrt::Windows::UI::Core;
//using namespace ::winrt::Windows::ApplicationModel;
//using namespace ::winrt::Windows::ApplicationModel::Core;
//using namespace ::winrt::Windows::ApplicationModel::Activation;
//using namespace ::winrt::Windows::::apex::get_system();
//using namespace ::winrt::Windows::Graphics::Display;
//using namespace ::winrt::Windows::::apex::get_system()::Threading;
//
//uptr keycode_to_char(uptr n)
//{
//   return n;
//}
//
//
//uptr virtualkey_to_char(::winrt::Windows::::apex::get_system()::VirtualKey e)
//{
//   switch (e)
//   {
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number0:
//      return '0';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number1:
//      return '1';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number2:
//      return '2';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number3:
//      return '3';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number4:
//      return '4';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number5:
//      return '5';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number6:
//      return '6';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number7:
//      return '7';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number8:
//      return '8';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number9:
//      return '9';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::A:
//      return 'a';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::B:
//      return 'b';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::C:
//      return 'c';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::D:
//      return 'd';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::E:
//      return 'e';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::F:
//      return 'f';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::G:
//      return 'g';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::H:
//      return 'h';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::I:
//      return 'i';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::J:
//      return 'j';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::K:
//      return 'k';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::L:
//      return 'l';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::M:
//      return 'm';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::N:
//      return 'n';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::O:
//      return 'o';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::P:
//      return 'p';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Q:
//      return 'q';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::R:
//      return 'r';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::S:
//      return 's';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::T:
//      return 't';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::U:
//      return 'u';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::V:
//      return 'v';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::W:
//      return 'w';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::X:
//      return 'x';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Y:
//      return 'y';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Z:
//      return 'z';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Shift:
//      return VK_SHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftShift:
//      return VK_LSHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightShift:
//      return VK_RSHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Control:
//      return VK_CONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftControl:
//      return VK_LCONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightControl:
//      return VK_RCONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Menu:
//      return VK_MENU;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftMenu:
//      return VK_LMENU;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightMenu:
//      return VK_RMENU;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Tab:
//      return VK_TAB;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Enter:
//      return VK_RETURN;
//   default:
//      ;
//   }
//   return (int)e;
//}
//
//
//::user::enum_key virtualkey_to_userkey(::winrt::Windows::::apex::get_system()::VirtualKey e, bool& bSpecialKey)
//{
//   bSpecialKey = false;
//   switch (e)
//   {
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number0:
//      return ::user::e_key_0;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number1:
//      return ::user::e_key_1;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number2:
//      return ::user::e_key_2;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number3:
//      return ::user::e_key_3;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number4:
//      return ::user::e_key_4;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number5:
//      return ::user::e_key_5;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number6:
//      return ::user::e_key_6;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number7:
//      return ::user::e_key_7;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number8:
//      return ::user::e_key_8;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number9:
//      return ::user::e_key_9;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::A:
//      return ::user::e_key_a;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::B:
//      return ::user::e_key_b;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::C:
//      return ::user::e_key_c;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::D:
//      return ::user::e_key_d;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::E:
//      return ::user::e_key_e;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::F:
//      return ::user::e_key_f;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::G:
//      return ::user::e_key_g;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::H:
//      return ::user::e_key_h;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::I:
//      return ::user::e_key_i;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::J:
//      return ::user::e_key_j;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::K:
//      return ::user::e_key_k;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::L:
//      return ::user::e_key_l;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::M:
//      return ::user::e_key_m;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::N:
//      return ::user::e_key_n;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::O:
//      return ::user::e_key_o;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::P:
//      return ::user::e_key_p;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Q:
//      return ::user::e_key_q;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::R:
//      return ::user::e_key_r;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::S:
//      return ::user::e_key_s;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::T:
//      return ::user::e_key_t;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::U:
//      return ::user::e_key_u;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::V:
//      return ::user::e_key_v;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::W:
//      return ::user::e_key_w;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::X:
//      return ::user::e_key_x;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Y:
//      return ::user::e_key_y;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Z:
//      return ::user::e_key_z;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Shift:
//      bSpecialKey = true;
//      return ::user::e_key_shift;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftShift:
//      bSpecialKey = true;
//      return ::user::e_key_left_shift;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightShift:
//      bSpecialKey = true;
//      return ::user::e_key_right_shift;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Control:
//      bSpecialKey = true;
//      return ::user::e_key_control;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftControl:
//      bSpecialKey = true;
//      return ::user::e_key_left_control;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightControl:
//      bSpecialKey = true;
//      return ::user::e_key_right_control;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Menu:
//      bSpecialKey = true;
//      return ::user::e_key_alt;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftMenu:
//      bSpecialKey = true;
//      return ::user::e_key_left_alt;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightMenu:
//      bSpecialKey = true;
//      return ::user::e_key_right_alt;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Tab:
//      bSpecialKey = true;
//      return ::user::e_key_tab;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Enter:
//      bSpecialKey = true;
//      return ::user::e_key_return;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Delete:
//      bSpecialKey = true;
//      return ::user::e_key_delete;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Back:
//      bSpecialKey = true;
//      return ::user::e_key_back;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Left:
//      bSpecialKey = true;
//      return ::user::e_key_left;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Right:
//      bSpecialKey = true;
//      return ::user::e_key_right;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Up:
//      bSpecialKey = true;
//      return ::user::e_key_up;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Down:
//      bSpecialKey = true;
//      return ::user::e_key_down;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::PageUp:
//      bSpecialKey = true;
//      return ::user::e_key_up;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::PageDown:
//      bSpecialKey = true;
//      return ::user::e_key_down;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Home:
//      bSpecialKey = true;
//      return ::user::e_key_home;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::End:
//      bSpecialKey = true;
//      return ::user::e_key_end;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Escape:
//      bSpecialKey = true;
//      return ::user::e_key_escape;
//   case 186:
//      return ::user::e_key_semicolon;
//   case 187:
//      return ::user::e_key_equal;
//   case 188:
//      return ::user::e_key_comma;
//   case 189:
//      return ::user::e_key_hyphen;
//   case 190:
//      return ::user::e_key_dot;
//   case 191:
//      return ::user::e_key_semicolon2;
//   case 193:
//      return ::user::e_key_slash2;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Space:
//      return ::user::e_key_space;
//   default:
//      ;
//      {
//         int iKey = (int)e;
//         debug_break();
//      }
//   }
//
//   return (::user::enum_key) e;
//
//}
//
//
//uptr virtualkey_to_code(::winrt::Windows::::apex::get_system()::VirtualKey e)
//{
//   switch (e)
//   {
//   case 190:
//      return '.';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number0:
//      return 1;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number1:
//      return 2;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number2:
//      return 3;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number3:
//      return 4;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number4:
//      return 5;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number5:
//      return 6;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number6:
//      return 7;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number7:
//      return 8;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number8:
//      return 9;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Number9:
//      return 10;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::A:
//      return 'a';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::B:
//      return 'b';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::C:
//      return 'ca';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::D:
//      return 'd';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::E:
//      return 'e';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::F:
//      return 'f';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::G:
//      return 'g';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::H:
//      return 'h';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::I:
//      return 'i';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::J:
//      return 'j';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::K:
//      return 'k';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::L:
//      return 'l';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::M:
//      return 'm';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::N:
//      return 'n';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::O:
//      return 'o';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::P:
//      return 'p';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Q:
//      return 'q';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::R:
//      return 'r';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::S:
//      return 's';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::T:
//      return 't';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::U:
//      return 'u';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::V:
//      return 'v';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::W:
//      return 'w';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Y:
//      return 'y';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Z:
//      return 'z';
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Shift:
//      return VK_SHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftShift:
//      return VK_LSHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightShift:
//      return VK_RSHIFT;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Control:
//      return VK_CONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftControl:
//      return VK_LCONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightControl:
//      return VK_RCONTROL;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::Menu:
//      return VK_MENU;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::LeftMenu:
//      return VK_LMENU;
//   case ::winrt::Windows::::apex::get_system()::VirtualKey::RightMenu:
//      return VK_RMENU;
//   default:
//      ;
//   }
//   return (int)e;
//}
//
//
////::u32 system_main(::apex::system * psystem)
////{
////
////   try
////   {
////
////      psystem->m_bReady = true;
////
////      psystem->on_run();
////
////      if(psystem->m_error.get_exit_code() != 0)
////      {
////
////         ::output_debug_string(L"application::main on_run termination failure");
////
////      }
////
////      //if(psystem->is_system())
////      //{
////
////      //   m_psystem->set_finish();
////
////      //}
////
////      try
////      {
////
////         psystem->term_thread();
////
////      }
////      catch(...)
////      {
////
////         psystem->m_error.set_if_not_set(-1);
////
////      }
////
////   }
////   catch(::exit_exception &)
////   {
////
////      //m_psystem->set_finish();
////
////   }
////
////   return 0;
////
////}
//
//
//// namespace user
//// {
//
////    /*::color::color g_colorSystemAppBackground;
//
////    CLASS_DECL_APEX color32_t set_system_app_background_color()
//
////    CLASS_DECL_APEX color32_t get_system_app_background_color()
////    {
//
////       auto color = ::apex::get_system()->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);
//
////       auto r = color.R;
//
////       auto g = color.G;
//
////       auto b = color.B;
//
////       return argb(255, r, g, b);
//
////    }*/
//
////    //CLASS_DECL_APEX double get_system_app_luminance()
////    //{
//
////    //   auto color = ::apex::get_system()->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);
//
////    //   double r = color.R;
//
////    //   double g = color.G;
//
////    //   double b = color.B;
//
////    //   return (r + g + b) / (255.0 * 3.0);
//
////    //}
//
//
////    //CLASS_DECL_APEX void os_update_colors()
////    //{
//
////    //   // App Background Color
////    //   {
//
//
////    //      auto color = ::apex::get_system()->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);
//
////    //      auto r = color.R;
//
////    //      auto g = color.G;
//
////    //      auto b = color.B;
//
////    //      set_system_app_background_color(::color::color(r, g, b));
//
////    //   }
//
//
////    //   // Luminance
////    //   {
//
//
////    //      auto color = ::apex::get_system()->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);
//
////    //      double r = color.R;
//
////    //      double g = color.G;
//
////    //      double b = color.B;
//
////    //      set_system_app_luminance((r + g + b) / (255.0 * 3.0));
//
////    //   }
//
////    //}
//
////    CLASS_DECL_APEX void os_update_dark_mode()
////    {
//
////       double dLuminance = get_system_app_luminance();
//
////       bool bDarkMode = dLuminance < 0.5;
//
////       set_system_dark_mode(bDarkMode);
//
////       set_app_dark_mode(bDarkMode);
//
////    }
//
//
//// } // namespace user
//
//
//
