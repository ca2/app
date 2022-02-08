#include "framework.h"
#include "_winrt.h"
#include "aura/node/universal_windows/_uwp.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"


CLASS_DECL_CORE int g_iMouse = -1;


CLASS_DECL_CORE int_bool GetCursorPos(POINT_I32 * lppoint);


CLASS_DECL_CORE int_bool ui_get_cursor_pos(POINT_I32 * ppt)
{

   if (ppt == nullptr)
      return false;

   int_bool iRet = false;

   ::point_i32 pointCursor;

   ::wait(::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([=, &pointCursor, &iRet]()
   {

      try
      {

         iRet = ::GetCursorPos(&pointCursor);

      }
      catch (...)
      {

      }

   })));

   if (iRet != false)
   {

      *ppt = pointCursor;

   }

   return iRet;

}


int g_iMouseX = 0;
int g_iMouseY = 0;


CLASS_DECL_CORE int_bool GetCursorPos(POINT_I32 * lppoint)
{

   lppoint->x = g_iMouseX;

   lppoint->y = g_iMouseY;

   if (g_iMouse < 0)
      return false;

   ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
          ref new ::winrt::Windows::UI::Core::DispatchedHandler([]()
   {

      ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Devices::Input::PointerDevice ^ > ^ deva = ::winrt::Windows::Devices::Input::PointerDevice::GetPointerDevices();

      for (unsigned int u = 0; u < deva->Size; u++)
      {

         ::winrt::Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(u);

         if (dev->PointerDeviceType == ::winrt::Windows::Devices::Input::PointerDeviceType::Mouse)
         {

            ::winrt::Windows::UI::Input::PointerPoint ^ pointerPoint = ::winrt::Windows::UI::Input::PointerPoint::GetCurrentPoint(g_iMouse);

            g_iMouseX = (::i32)pointerPoint->RawPosition.X;

            g_iMouseY = (::i32)pointerPoint->RawPosition.Y;

         }

      }

   }));

   return true;

}




CLASS_DECL_CORE void defer_dock_application(int_bool bDock)
{

   __UNREFERENCED_PARAMETER(bDock);

}

//CLASS_DECL_CORE void main_branch(::matter* pobjectTask, enum_priority epriority)
//{
//
//   ::wait(
//      ::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler([pobjectTask]()
//   {
//
//            pobjectTask->call();
//
//   })));
//
//}

#undef papplication

::winrt::Windows::UI::Xaml::papplication^ get_xaml_app();









#undef System
#undef Platform

using namespace Platform;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::ApplicationModel;
using namespace ::winrt::Windows::ApplicationModel::Core;
using namespace ::winrt::Windows::ApplicationModel::Activation;
using namespace ::winrt::Windows::System;
using namespace ::winrt::Windows::Graphics::Display;
using namespace ::winrt::Windows::System::Threading;

uptr keycode_to_char(uptr n)
{
   return n;
}


uptr virtualkey_to_char(::winrt::Windows::System::VirtualKey e)
{
   switch (e)
   {
   case ::winrt::Windows::System::VirtualKey::Number0:
      return '0';
   case ::winrt::Windows::System::VirtualKey::Number1:
      return '1';
   case ::winrt::Windows::System::VirtualKey::Number2:
      return '2';
   case ::winrt::Windows::System::VirtualKey::Number3:
      return '3';
   case ::winrt::Windows::System::VirtualKey::Number4:
      return '4';
   case ::winrt::Windows::System::VirtualKey::Number5:
      return '5';
   case ::winrt::Windows::System::VirtualKey::Number6:
      return '6';
   case ::winrt::Windows::System::VirtualKey::Number7:
      return '7';
   case ::winrt::Windows::System::VirtualKey::Number8:
      return '8';
   case ::winrt::Windows::System::VirtualKey::Number9:
      return '9';
   case ::winrt::Windows::System::VirtualKey::A:
      return 'a';
   case ::winrt::Windows::System::VirtualKey::B:
      return 'b';
   case ::winrt::Windows::System::VirtualKey::C:
      return 'c';
   case ::winrt::Windows::System::VirtualKey::D:
      return 'd';
   case ::winrt::Windows::System::VirtualKey::E:
      return 'e';
   case ::winrt::Windows::System::VirtualKey::F:
      return 'f';
   case ::winrt::Windows::System::VirtualKey::G:
      return 'g';
   case ::winrt::Windows::System::VirtualKey::H:
      return 'h';
   case ::winrt::Windows::System::VirtualKey::I:
      return 'i';
   case ::winrt::Windows::System::VirtualKey::J:
      return 'j';
   case ::winrt::Windows::System::VirtualKey::K:
      return 'k';
   case ::winrt::Windows::System::VirtualKey::L:
      return 'l';
   case ::winrt::Windows::System::VirtualKey::M:
      return 'm';
   case ::winrt::Windows::System::VirtualKey::N:
      return 'n';
   case ::winrt::Windows::System::VirtualKey::O:
      return 'o';
   case ::winrt::Windows::System::VirtualKey::P:
      return 'p';
   case ::winrt::Windows::System::VirtualKey::Q:
      return 'q';
   case ::winrt::Windows::System::VirtualKey::R:
      return 'r';
   case ::winrt::Windows::System::VirtualKey::S:
      return 's';
   case ::winrt::Windows::System::VirtualKey::T:
      return 't';
   case ::winrt::Windows::System::VirtualKey::U:
      return 'u';
   case ::winrt::Windows::System::VirtualKey::V:
      return 'v';
   case ::winrt::Windows::System::VirtualKey::W:
      return 'w';
   case ::winrt::Windows::System::VirtualKey::X:
      return 'x';
   case ::winrt::Windows::System::VirtualKey::Y:
      return 'y';
   case ::winrt::Windows::System::VirtualKey::Z:
      return 'z';
   case ::winrt::Windows::System::VirtualKey::Shift:
      return VK_SHIFT;
   case ::winrt::Windows::System::VirtualKey::LeftShift:
      return VK_LSHIFT;
   case ::winrt::Windows::System::VirtualKey::RightShift:
      return VK_RSHIFT;
   case ::winrt::Windows::System::VirtualKey::Control:
      return VK_CONTROL;
   case ::winrt::Windows::System::VirtualKey::LeftControl:
      return VK_LCONTROL;
   case ::winrt::Windows::System::VirtualKey::RightControl:
      return VK_RCONTROL;
   case ::winrt::Windows::System::VirtualKey::Menu:
      return VK_MENU;
   case ::winrt::Windows::System::VirtualKey::LeftMenu:
      return VK_LMENU;
   case ::winrt::Windows::System::VirtualKey::RightMenu:
      return VK_RMENU;
   case ::winrt::Windows::System::VirtualKey::Tab:
      return VK_TAB;
   case ::winrt::Windows::System::VirtualKey::Enter:
      return VK_RETURN;
   default:
      ;
   }
   return (int)e;
}


::user::enum_key virtualkey_to_userkey(::winrt::Windows::System::VirtualKey e, bool& bSpecialKey)
{
   bSpecialKey = false;
   switch (e)
   {
   case ::winrt::Windows::System::VirtualKey::Number0:
      return ::user::e_key_0;
   case ::winrt::Windows::System::VirtualKey::Number1:
      return ::user::e_key_1;
   case ::winrt::Windows::System::VirtualKey::Number2:
      return ::user::e_key_2;
   case ::winrt::Windows::System::VirtualKey::Number3:
      return ::user::e_key_3;
   case ::winrt::Windows::System::VirtualKey::Number4:
      return ::user::e_key_4;
   case ::winrt::Windows::System::VirtualKey::Number5:
      return ::user::e_key_5;
   case ::winrt::Windows::System::VirtualKey::Number6:
      return ::user::e_key_6;
   case ::winrt::Windows::System::VirtualKey::Number7:
      return ::user::e_key_7;
   case ::winrt::Windows::System::VirtualKey::Number8:
      return ::user::e_key_8;
   case ::winrt::Windows::System::VirtualKey::Number9:
      return ::user::e_key_9;
   case ::winrt::Windows::System::VirtualKey::A:
      return ::user::e_key_a;
   case ::winrt::Windows::System::VirtualKey::B:
      return ::user::e_key_b;
   case ::winrt::Windows::System::VirtualKey::C:
      return ::user::e_key_c;
   case ::winrt::Windows::System::VirtualKey::D:
      return ::user::e_key_d;
   case ::winrt::Windows::System::VirtualKey::E:
      return ::user::e_key_e;
   case ::winrt::Windows::System::VirtualKey::F:
      return ::user::e_key_f;
   case ::winrt::Windows::System::VirtualKey::G:
      return ::user::e_key_g;
   case ::winrt::Windows::System::VirtualKey::H:
      return ::user::e_key_h;
   case ::winrt::Windows::System::VirtualKey::I:
      return ::user::e_key_i;
   case ::winrt::Windows::System::VirtualKey::J:
      return ::user::e_key_j;
   case ::winrt::Windows::System::VirtualKey::K:
      return ::user::e_key_k;
   case ::winrt::Windows::System::VirtualKey::L:
      return ::user::e_key_l;
   case ::winrt::Windows::System::VirtualKey::M:
      return ::user::e_key_m;
   case ::winrt::Windows::System::VirtualKey::N:
      return ::user::e_key_n;
   case ::winrt::Windows::System::VirtualKey::O:
      return ::user::e_key_o;
   case ::winrt::Windows::System::VirtualKey::P:
      return ::user::e_key_p;
   case ::winrt::Windows::System::VirtualKey::Q:
      return ::user::e_key_q;
   case ::winrt::Windows::System::VirtualKey::R:
      return ::user::e_key_r;
   case ::winrt::Windows::System::VirtualKey::S:
      return ::user::e_key_s;
   case ::winrt::Windows::System::VirtualKey::T:
      return ::user::e_key_t;
   case ::winrt::Windows::System::VirtualKey::U:
      return ::user::e_key_u;
   case ::winrt::Windows::System::VirtualKey::V:
      return ::user::e_key_v;
   case ::winrt::Windows::System::VirtualKey::W:
      return ::user::e_key_w;
   case ::winrt::Windows::System::VirtualKey::X:
      return ::user::e_key_x;
   case ::winrt::Windows::System::VirtualKey::Y:
      return ::user::e_key_y;
   case ::winrt::Windows::System::VirtualKey::Z:
      return ::user::e_key_z;
   case ::winrt::Windows::System::VirtualKey::Shift:
      bSpecialKey = true;
      return ::user::e_key_shift;
   case ::winrt::Windows::System::VirtualKey::LeftShift:
      bSpecialKey = true;
      return ::user::e_key_left_shift;
   case ::winrt::Windows::System::VirtualKey::RightShift:
      bSpecialKey = true;
      return ::user::e_key_right_shift;
   case ::winrt::Windows::System::VirtualKey::Control:
      bSpecialKey = true;
      return ::user::e_key_control;
   case ::winrt::Windows::System::VirtualKey::LeftControl:
      bSpecialKey = true;
      return ::user::e_key_left_control;
   case ::winrt::Windows::System::VirtualKey::RightControl:
      bSpecialKey = true;
      return ::user::e_key_right_control;
   case ::winrt::Windows::System::VirtualKey::Menu:
      bSpecialKey = true;
      return ::user::e_key_alt;
   case ::winrt::Windows::System::VirtualKey::LeftMenu:
      bSpecialKey = true;
      return ::user::e_key_left_alt;
   case ::winrt::Windows::System::VirtualKey::RightMenu:
      bSpecialKey = true;
      return ::user::e_key_right_alt;
   case ::winrt::Windows::System::VirtualKey::Tab:
      bSpecialKey = true;
      return ::user::e_key_tab;
   case ::winrt::Windows::System::VirtualKey::Enter:
      bSpecialKey = true;
      return ::user::e_key_return;
   case ::winrt::Windows::System::VirtualKey::Delete:
      bSpecialKey = true;
      return ::user::e_key_delete;
   case ::winrt::Windows::System::VirtualKey::Back:
      bSpecialKey = true;
      return ::user::e_key_back;
   case ::winrt::Windows::System::VirtualKey::Left:
      bSpecialKey = true;
      return ::user::e_key_left;
   case ::winrt::Windows::System::VirtualKey::Right:
      bSpecialKey = true;
      return ::user::e_key_right;
   case ::winrt::Windows::System::VirtualKey::Up:
      bSpecialKey = true;
      return ::user::e_key_up;
   case ::winrt::Windows::System::VirtualKey::Down:
      bSpecialKey = true;
      return ::user::e_key_down;
   case ::winrt::Windows::System::VirtualKey::PageUp:
      bSpecialKey = true;
      return ::user::e_key_up;
   case ::winrt::Windows::System::VirtualKey::PageDown:
      bSpecialKey = true;
      return ::user::e_key_down;
   case ::winrt::Windows::System::VirtualKey::Home:
      bSpecialKey = true;
      return ::user::e_key_home;
   case ::winrt::Windows::System::VirtualKey::End:
      bSpecialKey = true;
      return ::user::e_key_end;
   case ::winrt::Windows::System::VirtualKey::Escape:
      bSpecialKey = true;
      return ::user::e_key_escape;
   case 186:
      return ::user::e_key_semicolon;
   case 187:
      return ::user::e_key_equal;
   case 188:
      return ::user::e_key_comma;
   case 189:
      return ::user::e_key_hyphen;
   case 190:
      return ::user::e_key_dot;
   case 191:
      return ::user::e_key_semicolon2;
   case 193:
      return ::user::e_key_slash2;
   case ::winrt::Windows::System::VirtualKey::Space:
      return ::user::e_key_space;
   default:
      ;
      {
         int iKey = (int)e;
         debug_break();
      }
   }

   return (::user::enum_key) e;

}


uptr virtualkey_to_code(::winrt::Windows::System::VirtualKey e)
{
   switch (e)
   {
   case 190:
      return '.';
   case ::winrt::Windows::System::VirtualKey::Number0:
      return 1;
   case ::winrt::Windows::System::VirtualKey::Number1:
      return 2;
   case ::winrt::Windows::System::VirtualKey::Number2:
      return 3;
   case ::winrt::Windows::System::VirtualKey::Number3:
      return 4;
   case ::winrt::Windows::System::VirtualKey::Number4:
      return 5;
   case ::winrt::Windows::System::VirtualKey::Number5:
      return 6;
   case ::winrt::Windows::System::VirtualKey::Number6:
      return 7;
   case ::winrt::Windows::System::VirtualKey::Number7:
      return 8;
   case ::winrt::Windows::System::VirtualKey::Number8:
      return 9;
   case ::winrt::Windows::System::VirtualKey::Number9:
      return 10;
   case ::winrt::Windows::System::VirtualKey::A:
      return 'a';
   case ::winrt::Windows::System::VirtualKey::B:
      return 'b';
   case ::winrt::Windows::System::VirtualKey::C:
      return 'ca';
   case ::winrt::Windows::System::VirtualKey::D:
      return 'd';
   case ::winrt::Windows::System::VirtualKey::E:
      return 'e';
   case ::winrt::Windows::System::VirtualKey::F:
      return 'f';
   case ::winrt::Windows::System::VirtualKey::G:
      return 'g';
   case ::winrt::Windows::System::VirtualKey::H:
      return 'h';
   case ::winrt::Windows::System::VirtualKey::I:
      return 'i';
   case ::winrt::Windows::System::VirtualKey::J:
      return 'j';
   case ::winrt::Windows::System::VirtualKey::K:
      return 'k';
   case ::winrt::Windows::System::VirtualKey::L:
      return 'l';
   case ::winrt::Windows::System::VirtualKey::M:
      return 'm';
   case ::winrt::Windows::System::VirtualKey::N:
      return 'n';
   case ::winrt::Windows::System::VirtualKey::O:
      return 'o';
   case ::winrt::Windows::System::VirtualKey::P:
      return 'p';
   case ::winrt::Windows::System::VirtualKey::Q:
      return 'q';
   case ::winrt::Windows::System::VirtualKey::R:
      return 'r';
   case ::winrt::Windows::System::VirtualKey::S:
      return 's';
   case ::winrt::Windows::System::VirtualKey::T:
      return 't';
   case ::winrt::Windows::System::VirtualKey::U:
      return 'u';
   case ::winrt::Windows::System::VirtualKey::V:
      return 'v';
   case ::winrt::Windows::System::VirtualKey::W:
      return 'w';
   case ::winrt::Windows::System::VirtualKey::Y:
      return 'y';
   case ::winrt::Windows::System::VirtualKey::Z:
      return 'z';
   case ::winrt::Windows::System::VirtualKey::Shift:
      return VK_SHIFT;
   case ::winrt::Windows::System::VirtualKey::LeftShift:
      return VK_LSHIFT;
   case ::winrt::Windows::System::VirtualKey::RightShift:
      return VK_RSHIFT;
   case ::winrt::Windows::System::VirtualKey::Control:
      return VK_CONTROL;
   case ::winrt::Windows::System::VirtualKey::LeftControl:
      return VK_LCONTROL;
   case ::winrt::Windows::System::VirtualKey::RightControl:
      return VK_RCONTROL;
   case ::winrt::Windows::System::VirtualKey::Menu:
      return VK_MENU;
   case ::winrt::Windows::System::VirtualKey::LeftMenu:
      return VK_LMENU;
   case ::winrt::Windows::System::VirtualKey::RightMenu:
      return VK_RMENU;
   default:
      ;
   }
   return (int)e;
}


//::u32 system_main(::aura::system * psystem)
//{
//
//   try
//   {
//
//      psystem->m_bReady = true;
//
//      psystem->on_run();
//
//      if(psystem->m_error.get_exit_code() != 0)
//      {
//
//         ::output_debug_string(L"application::main on_run termination failure");
//
//      }
//
//      //if(psystem->is_system())
//      //{
//
//      //   m_psystem->set_finish();
//
//      //}
//
//      try
//      {
//
//         psystem->term_thread();
//
//      }
//      catch(...)
//      {
//
//         psystem->m_error.set_if_not_set(-1);
//
//      }
//
//   }
//   catch(::exit_exception &)
//   {
//
//      //m_psystem->set_finish();
//
//   }
//
//   return 0;
//
//}


// namespace user
// {


//    CLASS_DECL_CORE color32_t get_system_app_background_color()
//    {

//       auto color = psystem->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);

//       auto r = color.R;

//       auto g = color.G;

//       auto b = color.B;

//       return argb(255, r, g, b);

//    }

//    CLASS_DECL_CORE double get_system_app_luminance()
//    {

//       auto color = psystem->get_session()->m_frameworkview->m_puisettings->GetColorValue(::winrt::Windows::UI::ViewManagement::UIColorType::Background);

//       double r = color.R;

//       double g = color.G;

//       double b = color.B;

//       return (r + g + b) / (255.0 * 3.0);

//    }


//    CLASS_DECL_CORE void os_update_dark_mode()
//    {

//       double dLuminance = get_system_app_luminance();

//       bool bDarkMode = dLuminance < 0.5;

//       set_system_dark_mode(bDarkMode);

//       set_app_dark_mode(bDarkMode);

//    }


// } // namespace user



