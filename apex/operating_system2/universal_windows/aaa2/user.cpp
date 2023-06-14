#include "framework.h"
#include "_winrt.h"
#include "apex/operating_system/universal_windows/_uwp.h"
//#include "apex/os/windows_common/draw2d_direct2d_global.h"


CLASS_DECL_APEX int g_iMouse = -1;


//CLASS_DECL_APEX int_bool GetCursorPos(::point_i32 * lppoint);

//
//CLASS_DECL_APEX int_bool ui_get_cursor_pos(::point_i32 * ppt)
//{
//
//   if (ppt == nullptr)
//      return false;
//
//   int_bool iRet = false;
//
//   ::point_i32 pointCursor;
//
//   ::wait(::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler([=, &pointCursor, &iRet]()
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

//CLASS_DECL_APEX int_bool GetCursorPos(::point_i32 * lppoint)
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
//          ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler([]()
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

   UNREFERENCED_PARAMETER(bDock);

}



#undef papp

::winrt::Windows::UI::Xaml::papp^ get_xaml_app();









#undef ::apexacmesystem()
#undef Platform

using namespace Platform;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::ApplicationModel;
using namespace ::winrt::Windows::ApplicationModel::Core;
using namespace ::winrt::Windows::ApplicationModel::Activation;
using namespace ::winrt::Windows::apexacmesystem();
using namespace ::winrt::Windows::Graphics::Display;
using namespace ::winrt::Windows::apexacmesystem()::Threading;

