#include "framework.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "aura/os/uwp/_winrt.h"
#include "aura/node/uwp/_uwp.h"
#include "aura/node/uwp/buffer.h"
#include "_uwp.h"


extern int g_iMouse;


#undef System
#undef Platform


using namespace Platform;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::System;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;



namespace uwp
{


   directx_framework_view::directx_framework_view(::aura::system * psystem, ::String ^ strId)
   {

      draw2d_direct2d::defer_direct2d_initialize();

      m_puisettings = ref new ::Windows::UI::ViewManagement::UISettings;

      create_factory < ::uwp::buffer, ::graphics::graphics >();

      m_dwMouseMoveThrottle = 10;

      m_pimpl = nullptr;

      m_pointLastCursor.X = 0;
      m_pointLastCursor.Y = 0;

      m_bLeftButton = false;
      m_bMiddleButton = false;
      m_bRightButton = false;

      m_strId = strId;

      if (!main_initialize())
      {

         __throw(::exception::exception("Failed to run main_initialize at directx_framework_view constructor."));

      }

      m_psystem = psystem;

      //      psystem->get_context_session()->m_frameworkview = this;

      m_pdxi = psystem->m_papplicationStartup->__create_new < directx_interaction>();

   }


   directx_framework_view::~directx_framework_view()
   {

      ::draw2d_direct2d::direct2d_finalize();

   }


   void directx_framework_view::initialize_directx_application()
   {

      int nReturnCode = 0;

      if (!m_psystem->m_hthread)
      {

         if (!m_psystem->begin_synch())
         {

            __throw(::exception::exception("failed to begin_synch the system"));

         }

      }

      auto estatus = m_pdxi->initialize(m_psystem);

      if (!estatus)
      {

         __throw(resource_exception());

      }

      //m_psystem->get_context_session()->m_pframeworkview = this;

      m_psystem->get_context_session()->m_puiHost = m_pdxi;

      m_directx->defer_init();

      ::user::os_calc_dark_mode();

      auto pcs = __new(::user::create_struct);

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      auto routine = [this]()
      {

         manual_reset_event ev;

         m_window->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler(
            [this, &ev]()
            {

               //m_directx->m_windowBounds = m_window->Bounds;

               //auto pchanged = ref new Windows::UI::Core::WindowSizeChangedEventArgs();

               ::size size((LONG) m_window->Bounds.Width, (LONG) m_window->Bounds.Height);

               //pchanged->Size.Height = m_window->Bounds.Height;

               on_window_size_changed(m_window.Get(), size);

               ev.set_event();

            }));

         ev.wait(15_s);

         auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

         auto puserinteraction = m_pdxi;

         //puserinteraction->display(e_display_normal);

         //puserinteraction->set_need_layout();

         //puserinteraction->set_need_redraw();

         //puserinteraction->post_redraw();


      };

      pcs->m_routineSuccess = __routine(routine);

      m_pimpl = __create < ::user::interaction_impl >();

      m_pimpl->m_rect.left = (LONG) m_window->Bounds.X;
      m_pimpl->m_rect.top = (LONG) m_window->Bounds.Y;
      m_pimpl->m_rect.right = (LONG) (m_window->Bounds.X + m_window->Bounds.Width);
      m_pimpl->m_rect.top = (LONG) (m_window->Bounds.Y + m_window->Bounds.Height);

      m_pimpl->m_window = m_window;

      m_directx->m_pimpl = m_pimpl;

      m_pimpl->m_pframeworkview = this;

      pcs->m_pimpl = m_pimpl;

      get_context_system()->m_paurasystem->m_pimplMain = m_pimpl;

      //m_pimpl->m_bNotifyLayoutCompletedPending = true;

      if (!puiHost->create_window_ex(pcs))
      {

         __throw(resource_exception("Couldn't create Main Window"));

         return;

      }



   }


   void directx_framework_view::Initialize(CoreApplicationView ^ applicationView)
   {

      impact::Initialize(applicationView);

      applicationView->Activated += ref new TypedEventHandler<CoreApplicationView ^, IActivatedEventArgs ^>(this, &directx_framework_view::OnActivated);

      CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs ^>(this, &directx_framework_view::OnSuspending);

      CoreApplication::Resuming += ref new EventHandler<Object ^>(this, &directx_framework_view::OnResuming);

   }


   void directx_framework_view::install_directx_application_message_routing()
   {

      m_puisettings->ColorValuesChanged += ref new TypedEventHandler<Windows::UI::ViewManagement::UISettings ^, Platform::Object ^>(this, &directx_framework_view::OnUISettingsColorValuesChange);

      CoreWindow ^ window = m_window.Get();

      window->VisibilityChanged += ref new TypedEventHandler<CoreWindow ^, VisibilityChangedEventArgs ^>(this, &directx_framework_view::OnWindowVisibilityChanged);

      window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

      window->SizeChanged += ref new TypedEventHandler<CoreWindow ^, WindowSizeChangedEventArgs ^>(this, &directx_framework_view::OnWindowSizeChanged);

      window->PointerMoved += ref new TypedEventHandler < CoreWindow ^, PointerEventArgs ^>(this, &directx_framework_view::OnPointerMoved);

      window->CharacterReceived += ref new TypedEventHandler<CoreWindow ^, CharacterReceivedEventArgs ^>(this, &directx_framework_view::OnCharacterReceived);

      window->KeyDown += ref new TypedEventHandler < CoreWindow ^, KeyEventArgs ^>(this, &directx_framework_view::OnKeyDown);

      window->KeyUp += ref new TypedEventHandler < CoreWindow ^, KeyEventArgs ^>(this, &directx_framework_view::OnKeyUp);

      window->PointerPressed += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &directx_framework_view::OnPointerPressed);

      window->PointerReleased += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &directx_framework_view::OnPointerReleased);

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      displayinformation->DpiChanged += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DpiChanged);

      displayinformation->DisplayContentsInvalidated += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DisplayContentsInvalidated);

   }


   void directx_framework_view::SetWindow(CoreWindow ^ window)
   {

      impact::SetWindow(window);

      m_directx = ref new directx_base();

      m_directx->m_psystem = m_psystem;

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      m_directx->Initialize(window, displayinformation->LogicalDpi);

      install_directx_application_message_routing();

      initialize_directx_application();

   }


   void directx_framework_view::Load(String ^ entryPoint)
   {

   }


   void directx_framework_view::Run()
   {

      m_window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);

   }


   void directx_framework_view::Uninitialize()
   {

   }


   void directx_framework_view::OnUISettingsColorValuesChange(Windows::UI::ViewManagement::UISettings ^ uisettings, Platform::Object ^)
   {

      ::user::os_calc_dark_mode();

   }


   void directx_framework_view::OnWindowSizeChanged(CoreWindow ^ sender, WindowSizeChangedEventArgs ^ args)
   {

      ::size size((LONG) args->Size.Width, (LONG) args->Size.Height);

      on_window_size_changed(sender, size);

   }


   void directx_framework_view::on_window_size_changed(CoreWindow ^ sender, const ::size & size)
   {

      m_directx->m_size = size;

      m_rectLastWindowRect.Width = (float)m_directx->m_size.cx;

      m_rectLastWindowRect.Height = (float)m_directx->m_size.cy;

      m_directx->OnWindowSizeChange();

   }

 
   void directx_framework_view::DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      m_rectLastWindowRect = m_window->Bounds;

      m_directx->OnChangeDpi(sender->LogicalDpi);


   }


   void directx_framework_view::DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      // Ensure the D3D Device is available for rendering.

      m_directx->ValidateDevice();

   }


   void directx_framework_view::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
   {

      m_window->Activate();

      if (args != nullptr)
      {

         if (args->Kind == ActivationKind::Protocol)
         {

            ProtocolActivatedEventArgs ^ eventArgs = (ProtocolActivatedEventArgs ^)args;

            string str = eventArgs->Uri->AbsoluteUri;

            auto pcreate = m_psystem->__create_new < ::create >();

            pcreate->m_ecommand = ::command_protocol;

            pcreate->m_varFile = str;

            //m_psystem->add_create(pcreate);

            //auto papp = m_psystem->m_papplicationStartup;

            //if (papp == nullptr)
            //{

            //   papp = m_psystem->get_context_session()->m_pappCurrent;

            //}

            m_psystem->post_object(e_message_system, e_system_message_create, pcreate);

         }

      }


   }


   void directx_framework_view::OnSuspending(Object ^ sender, SuspendingEventArgs ^ args)
   {

   }


   void directx_framework_view::OnResuming(Object ^ sender, Object ^ args)
   {

   }


   void directx_framework_view::OnCharacterReceived(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::CharacterReceivedEventArgs ^ args)
   {

      if(m_psystem->get_context_session() == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
         return;

      if (puiHost->m_pimpl == nullptr)
         return;

      __pointer(::message::base) pbase;

      auto pkey  = __new(::message::key);

      pbase = pkey;

      pkey->m_id = e_message_char;
      pkey->m_playeredUserPrimitive = puiHost;
      pkey->m_nChar = keycode_to_char(args->KeyCode);

      puiHost->m_pimpl->queue_message_handler(pbase);

   }


   void directx_framework_view::OnKeyDown(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {
      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = true;
      }

      if(m_psystem == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
         return;

      if (puiHost->m_pimpl == nullptr)
         return;

      __pointer(::message::base) pbase;

      auto pkey  = __new(::message::key);

      pbase = pkey;

      bool bTextFocus = m_puserinteraction->get_keyboard_focus() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if(bSpecialKey || !bTextFocus || m_psystem->get_context_session()->is_key_pressed(::user::key_control)
         || m_psystem->get_context_session()->is_key_pressed(::user::key_alt))
      {

         pkey->m_id                 = e_message_key_down;
         pkey->m_playeredUserPrimitive       = m_psystem->get_context_session()->m_puiHost;
         pkey->m_nChar              = virtualkey_to_char(args->VirtualKey);
         pkey->m_ekey               = ekey;
         pkey->m_wparam             = pkey->m_nChar;
         pkey->m_nFlags             = virtualkey_to_code(args->VirtualKey);
         pkey->m_lparam             = pkey->m_nFlags << 16;
         //pkey->m_strText            = m_strNewText;
         //if (pkey->m_strText.has_char())
         //{
           // pkey->m_ekey = ::user::key_refer_to_text_member;
         //}
   //      pkey->m_key = args;


         puiHost->m_pimpl->queue_message_handler(pbase);

      }

   }

   void directx_framework_view::OnKeyUp(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
         return;

      if (puiHost->m_pimpl == nullptr)
         return;

      __pointer(::message::base) pbase;

      ::message::key * pkey = new  ::message::key;

      pbase = pkey;


      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = false;
      }
      
      bool bTextFocus = m_puserinteraction->get_keyboard_focus() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if (bSpecialKey || !bTextFocus)
      {

         pkey->m_id = e_message_key_up;
         pkey->m_playeredUserPrimitive = m_psystem->get_context_session()->m_puiHost;
         pkey->m_nChar = virtualkey_to_char(args->VirtualKey);
         pkey->m_ekey = ekey;
         pkey->m_wparam = pkey->m_nChar;


         //      pkey->m_key = args;

               //if (m_psystem->m_psimpleui != nullptr && m_psystem->m_psimpleui->is_window_visible())
               //{
               //   string str;
               //   str = (char)pkey->m_nChar;
               //   if (m_bFontopusShift)
               //   {
               //      if (pkey->m_nChar == 0xbe)
               //      {
               //         str = ">";
               //      }
               //      else if (str == "2")
               //      {
               //         str = "@";
               //      }
               //      else
               //      {
               //         str.make_upper();
               //      }
               //   }
               //   else
               //   {
               //      if (pkey->m_nChar == 0xbe)
               //      {
               //         str = ".";
               //      }
               //   }
               //   m_psystem->m_psimpleui->on_char(virtualkey_to_userkey(args->VirtualKey), str);
               //}
               //else
               //{
         puiHost->m_pimpl->queue_message_handler(pbase);
         //}

      }



   }


   void directx_framework_view::OnWindowClosed(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::CoreWindowEventArgs ^ args)
   {

   }


   void directx_framework_view::OnWindowVisibilityChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^ args)
   {

      if (args->Visible)
      {

         if (m_directx->m_bCoreWindowVisible.is_empty())
         {

            m_directx->m_bCoreWindowVisible = true;

         }
         else if (m_directx->m_bCoreWindowVisible.isFalse())
         {

            m_directx->m_bCoreWindowVisible = true;

            CoreWindow ^ window = m_window.Get();

            if (window)
            {

               m_directx->HandleDeviceLost();

            }

         }

      }
      else
      {

         if (m_directx->m_bCoreWindowVisible)
         {

            m_directx->m_bCoreWindowVisible = false;

            m_directx->DestroyWindowSizeDependentResources();

         }

      }

   }

   void directx_framework_view::OnPointerMoved(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      //if (m_dwMouseMoveThrottle && m_millisLastMouseMove.elapsed() < m_dwMouseMoveThrottle)
      //{

        // return;

      //}

      if(m_psystem == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
         return;

      if (puiHost->m_pimpl == nullptr)
         return;

      __pointer(::message::base) pbase;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::message::mouse * pmouse = new ::message::mouse;

      pbase = pmouse;

      pmouse->m_point.x       = (::i32) pointerPoint->RawPosition.X;
      pmouse->m_point.y       = (::i32) pointerPoint->RawPosition.Y;
      pmouse->m_id            = e_message_mouse_move;
      pmouse->m_playeredUserPrimitive  = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      auto pimpl = __uwp_user_interaction_impl(puiHost->m_pimpl);

      pimpl->m_pointCursor.set(
         (LONG) pointerPoint->RawPosition.X, 
         (LONG) pointerPoint->RawPosition.Y);

      puiHost->m_pimpl->queue_message_handler(pbase);

      m_millisLastMouseMove= ::millis::now();

   }


   void directx_framework_view::OnPointerPressed(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
      {

         return;

      }

      if (puiHost->m_pimpl == nullptr)
      {

         return;

      }

      __pointer(::message::base) pbase;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::message::mouse * pmouse = new  ::message::mouse;

      pbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(args->CurrentPoint->Properties->IsLeftButtonPressed && !m_bLeftButton)
      {

         pmouse->m_id     = e_message_left_button_down;

         m_bLeftButton           = true;
         m_bMiddleButton         = false;
         m_bRightButton          = false;

      }
      else if(args->CurrentPoint->Properties->IsRightButtonPressed && !m_bRightButton)
      {

         pmouse->m_id     = e_message_right_button_down;

         m_bLeftButton           = false;
         m_bMiddleButton         = false;
         m_bRightButton          = true;

      }
      else if(args->CurrentPoint->Properties->IsMiddleButtonPressed && !m_bMiddleButton)
      {

         pmouse->m_id     = e_message_middle_button_down;

         m_bLeftButton           = false;
         m_bMiddleButton         = true;
         m_bRightButton          = false;

      }

      pmouse->m_playeredUserPrimitive = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puiHost->m_pimpl->queue_message_handler(pbase);

   }


   void directx_framework_view::OnPointerReleased(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost == nullptr)
         return;

      if (puiHost->m_pimpl == nullptr)
         return;

      __pointer(::message::base) pbase;

      ::message::mouse * pmouse = new  ::message::mouse;

      pbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(m_bLeftButton && !args->CurrentPoint->Properties->IsLeftButtonPressed)
      {

         pmouse->m_id     = e_message_left_button_up;
         m_bLeftButton           = false;

      }
      else if(m_bRightButton && !args->CurrentPoint->Properties->IsRightButtonPressed)
      {

         pmouse->m_id     = e_message_right_button_up;
         m_bRightButton          = false;

      }
      else if(m_bMiddleButton && !args->CurrentPoint->Properties->IsMiddleButtonPressed)
      {

         pmouse->m_id     = e_message_middle_button_up;
         m_bMiddleButton         = false;

      }

      pmouse->m_playeredUserPrimitive = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puiHost->m_pimpl->queue_message_handler(pbase);

   }


   directx_application_source::directx_application_source(::aura::system * paxissystem, const string & strId)
   {

      m_psystem     = paxissystem;

      m_strId           = strId;

   }


   Windows::ApplicationModel::Core::IFrameworkView^ directx_application_source::CreateView()
   {

      return ref new directx_framework_view(m_psystem,m_strId);

   }


   directx_application_source ^ new_directx_application_source(::aura::system * papexsystem, const string & strId)
   {

      string str = strId;

      //str += " client_only";

      //str += " full_screen";

      return ref new directx_application_source(papexsystem, str);

   }

   
   Windows::Foundation::Rect directx_framework_view::get_input_content_rect()
   {

      Windows::Foundation::Rect rect;
      
      auto pfocusui = m_puserinteraction->get_keyboard_focus();

      auto puserinteraction = __user_interaction(pfocusui);

      if (puserinteraction)
      {

         ::rect r = puserinteraction->get_window_rect();

         m_rectInputContentRect.X = (float) r.left;
         m_rectInputContentRect.Y = (float)r.top;
         m_rectInputContentRect.Width = (float)r.width();
         m_rectInputContentRect.Height = (float)r.height();

      }

      rect = m_rectInputContentRect;

      return rect;

   }


   Windows::Foundation::Rect directx_framework_view::get_input_selection_rect()
   {

      Windows::Foundation::Rect rect = m_rectInputSelectionRect;

      return rect;

   }

   
   widestring directx_framework_view::get_input_text()
   {

      widestring wstrText;

      auto pfocusui = m_puserinteraction->get_keyboard_focus();

      auto puserinteraction = __user_interaction(pfocusui);

      if (puserinteraction)
      {

         string strText;

         puserinteraction->_001GetText(strText);

         wstrText = strText;

      }

      return wstrText;

   }


   bool directx_framework_view::set_input_text(const widestring & wstr)
   {

      auto pfocusui = m_puserinteraction->get_keyboard_focus();

      auto puserinteraction = __user_interaction(pfocusui);

      if (puserinteraction)
      {

         string strText;

         strText = wstr;

         puserinteraction->_001SetText(strText, e_source_user);

      }

      //return wstrText;
      return true;

   }


   //void directx_framework_view::get_input_text(const widestring & wstr)
   //{


   //}


   Windows::Foundation::Rect directx_framework_view::get_window_rect()
   {

      Windows::Foundation::Rect rect = m_rectLastWindowRect;

      /*      rect.X = 0;
            rect.Y = 0;
            rect.Width = 600;
            rect.Height = 480;

            if(m_window == nullptr)
               return rect;

            ::wait(m_window->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler ([=, &rect]()
            {
               try
               {
                  rect = m_window->Bounds;
               }
               catch(...)
               {
               }
            })));*/

      return rect;

   }

   Windows::Foundation::Point directx_framework_view::get_cursor_pos()
   {

      single_lock sl(&m_mutex, true);

      Windows::Foundation::Point p = m_pointLastCursor;

      /*      if(m_window == nullptr)
               return p;

            if(g_iMouse < 0)
               return p;

            ::wait(m_window->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler ([=, &p]()
            {
               try
               {

                  Windows::Foundation::Collections::IVectorView < Windows::Devices::Input::PointerDevice ^ > ^ deva = ::Windows::Devices::Input::PointerDevice::GetPointerDevices();

                  for(unsigned int u = 0; u < deva->Size; u++)
                  {

                     Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(u);

                     if(dev->PointerDeviceType == ::Windows::Devices::Input::PointerDeviceType::Mouse)
                     {

                        Windows::UI::Input::PointerPoint ^ pointerPoint = Windows::UI::Input::PointerPoint::GetCurrentPoint(g_iMouse);

                        p = pointerPoint->RawPosition;

                        break;

                     }

                  }

               }
               catch(...)
               {
               }
            })), 5); // wait for up to 5 milliseconds

            m_pointLastCursor = p;*/

      return p;

   }


} // namespace uwp




