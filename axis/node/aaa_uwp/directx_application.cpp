#include "framework.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "aura/os/uwp/_winrt.h"
#include "_uwp.h"
#include "buffer.h"


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

bool g_bCoreWindowOnceVisible = false;


namespace uwp
{


   directx_framework_view::directx_framework_view(::aura::system * psystem, ::String ^ strId)
   {

      draw2d_direct2d::direct2d_initialize();

      m_puisettings = ref new ::Windows::UI::ViewManagement::UISettings;
         
      create_factory < ::uwp::buffer, ::graphics::graphics >();

      m_dwMouseMoveThrottle = 10;

      m_pimpl = nullptr;

      m_pointLastCursor.X = 0;
      m_pointLastCursor.Y = 0;

      m_bLeftButton        = false;
      m_bMiddleButton      = false;
      m_bRightButton       = false;

      m_strId = strId;

      if (!main_initialize())
      {

         __throw(::exception::exception("Failed to run main_initialize at directx_framework_view constructor."));

      }

      m_psystem = psystem;

//      psystem->get_context_session()->m_frameworkview = this;

      m_pdxi = __new(directx_interaction);

   }


   directx_framework_view::~directx_framework_view()
   {

      ::draw2d_direct2d::direct2d_finalize();

   }


   void directx_framework_view::initialize_directx_application()
   {

      int nReturnCode = 0;

      if (!m_psystem->begin_synch())
      {

         __throw(::exception::exception("failed to begin_synch the system"));

      }

      auto estatus = m_pdxi->initialize(m_psystem);

      if (!estatus)
      {

         __throw(resource_exception());

      }

      m_psystem->get_context_session()->m_frameworkview = this;

      m_psystem->get_context_session()->m_puiHost = m_pdxi;

      m_directx->defer_init();

      ::user::os_update_dark_mode();

      ::user::create_struct cs;

      if (!m_psystem->get_context_session()->m_puiHost->create_window_ex(cs))
      {

         __throw(resource_exception("Couldn't create Main Window"));

         return;

      }

      auto puserinteraction = m_pdxi;

      auto pimpl = m_psystem->get_context_session()->m_puiHost->m_pimpl;

      auto puwpui = pimpl->cast < ::uwp::interaction_impl >();

      puwpui->m_frameworkview = this;

      puwpui->m_window = m_window;

      m_pimpl = puwpui;

      m_directx->m_pimpl = puwpui;



      puserinteraction->display(display_normal);

      puserinteraction->set_need_layout();

      puserinteraction->set_need_redraw();

      puserinteraction->post_redraw();


   }


   void directx_framework_view::Initialize(CoreApplicationView ^ applicationView)
   {

      impact::Initialize(applicationView);

      applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &directx_framework_view::OnActivated);

      CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &directx_framework_view::OnSuspending);

      CoreApplication::Resuming += ref new EventHandler<Object^>(this, &directx_framework_view::OnResuming);

   }


   void directx_framework_view::install_directx_application_message_routing()
   {
      
      m_puisettings->ColorValuesChanged += ref new TypedEventHandler<Windows::UI::ViewManagement::UISettings^, Platform::Object^> (this, &directx_framework_view::OnUISettingsColorValuesChange);

      CoreWindow ^ window = m_window.Get();

      window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &directx_framework_view::OnWindowVisibilityChanged);

      window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

      window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &directx_framework_view::OnWindowSizeChanged);

      window->PointerMoved += ref new TypedEventHandler < CoreWindow^, PointerEventArgs^>(this, &directx_framework_view::OnPointerMoved);

      window->CharacterReceived += ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &directx_framework_view::OnCharacterReceived);

      window->KeyDown += ref new TypedEventHandler < CoreWindow^, KeyEventArgs^>(this, &directx_framework_view::OnKeyDown);

      window->KeyUp += ref new TypedEventHandler < CoreWindow^, KeyEventArgs^>( this, &directx_framework_view::OnKeyUp);

      window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_framework_view::OnPointerPressed);

      window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_framework_view::OnPointerReleased);

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      displayinformation->DpiChanged += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DpiChanged);

      displayinformation->DisplayContentsInvalidated += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DisplayContentsInvalidated);

   }


   void directx_framework_view::SetWindow(CoreWindow^ window)
   {

      impact::SetWindow(window);

      m_directx = ref new directx_base();

      m_directx->m_psystem = m_psystem;

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      m_directx->Initialize(window, displayinformation->LogicalDpi);

      install_directx_application_message_routing();

      initialize_directx_application();

      m_rectLastWindowRect = m_window->Bounds;

   }


   void directx_framework_view::Load(String^ entryPoint)
   {

   }


   void directx_framework_view::Run()
   {

      m_window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);

   }


   void directx_framework_view::Uninitialize()
   {

   }


   void directx_framework_view::OnUISettingsColorValuesChange(Windows::UI::ViewManagement::UISettings^ uisettings, Platform::Object^)
   {

      ::user::os_update_dark_mode();

   }


   void directx_framework_view::OnWindowSizeChanged(CoreWindow ^ sender, WindowSizeChangedEventArgs ^ args)
   {

      m_directx->m_size.set_size((i32) args->Size.Width, (i32)args->Size.Height);

      m_rectLastWindowRect.Width = (float) m_directx->m_size.cx;

      m_rectLastWindowRect.Height = (float) m_directx->m_size.cy;

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

            auto pcreate = __new(::create(m_psystem));

            pcreate->m_ecommand = ::command_protocol;

            pcreate->m_varFile = str;

            //m_psystem->add_create(pcreate);

            //auto papp = m_psystem->m_papplicationStartup;

            //if (papp == nullptr)
            //{

            //   papp = m_psystem->get_context_session()->m_pappCurrent;

            //}

            m_psystem->post_object(e_message_system, system_message_create, pcreate);

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

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
         return;

      pointer < ::message::base > spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      pkey->m_id = e_message_char;
      pkey->m_puserinteraction = m_psystem->get_context_session()->m_puiHost;
      pkey->m_nChar = keycode_to_char(args->KeyCode);

      m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_framework_view::OnKeyDown(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {
      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = true;
      }

      if(m_psystem == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
         return;

      pointer < ::message::base > spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      bool bTextFocus = m_psystem->get_context_session()->get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if(bSpecialKey || !bTextFocus || m_psystem->get_context_session()->is_key_pressed(::user::key_control)
         || m_psystem->get_context_session()->is_key_pressed(::user::key_alt))
      {

         pkey->m_id                 = e_message_key_down;
         pkey->m_puserinteraction       = m_psystem->get_context_session()->m_puiHost;
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


         m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);

      }

   }

   void directx_framework_view::OnKeyUp(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
         return;

      pointer < ::message::base > spbase;

      ::message::key * pkey = new  ::message::key;

      spbase = pkey;


      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = false;
      }
      
      bool bTextFocus = m_psystem->get_context_session()->get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if (bSpecialKey || !bTextFocus)
      {

         pkey->m_id = e_message_key_up;
         pkey->m_puserinteraction = m_psystem->get_context_session()->m_puiHost;
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
         m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);
         //}

      }



   }

   void directx_framework_view::OnWindowVisibilityChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^ args)
   {

      if (args->Visible)
      {

         if (!g_bCoreWindowOnceVisible)
         {

            g_bCoreWindowOnceVisible = true;

         }

      }

   }

   void directx_framework_view::OnPointerMoved(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_dwMouseMoveThrottle && m_tickLastMouseMove.elapsed() < m_dwMouseMoveThrottle)
      {

         return;

      }

      if(m_psystem == nullptr)
         return;

      if(m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      if(m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
         return;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x       = (::i32) pointerPoint->RawPosition.X;
      pmouse->m_point.y       = (::i32) pointerPoint->RawPosition.Y;
      pmouse->m_id            = e_message_mouse_move;
      pmouse->m_puserinteraction  = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);

      m_tickLastMouseMove = ::get_tick();

   }


   void directx_framework_view::OnPointerPressed(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      if(m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      if(m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
         return;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(args->CurrentPoint->Properties->IsLeftButtonPressed && !m_bLeftButton)
      {

         pmouse->m_id     = e_message_lbutton_down;

         m_bLeftButton           = true;
         m_bMiddleButton         = false;
         m_bRightButton          = false;

      }
      else if(args->CurrentPoint->Properties->IsRightButtonPressed && !m_bRightButton)
      {

         pmouse->m_id     = e_message_rbutton_down;

         m_bLeftButton           = false;
         m_bMiddleButton         = false;
         m_bRightButton          = true;

      }
      else if(args->CurrentPoint->Properties->IsMiddleButtonPressed && !m_bMiddleButton)
      {

         pmouse->m_id     = WM_MBUTTONDOWN;

         m_bLeftButton           = false;
         m_bMiddleButton         = true;
         m_bRightButton          = false;

      }

      pmouse->m_puserinteraction = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_framework_view::OnPointerReleased(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(m_bLeftButton && !args->CurrentPoint->Properties->IsLeftButtonPressed)
      {

         pmouse->m_id     = e_message_lbutton_up;
         m_bLeftButton           = false;

      }
      else if(m_bRightButton && !args->CurrentPoint->Properties->IsRightButtonPressed)
      {

         pmouse->m_id     = e_message_rbutton_up;
         m_bRightButton          = false;

      }
      else if(m_bMiddleButton && !args->CurrentPoint->Properties->IsMiddleButtonPressed)
      {

         pmouse->m_id     = WM_MBUTTONUP;
         m_bMiddleButton         = false;

      }

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
      {

         return;

      }

      if (m_psystem->get_context_session()->m_puiHost->m_pimpl == nullptr)
      {

         return;

      }

      pmouse->m_puserinteraction = m_psystem->get_context_session()->m_puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      m_psystem->get_context_session()->m_puiHost->m_pimpl->queue_message_handler(spbase);

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


   directx_application_source ^ new_directx_application_source(::aura::system * paurasystem, const string & strId)
   {

      string str = strId;

      //str += " client_only";

      //str += " full_screen";

      return ref new directx_application_source(paurasystem, str);

   }

   
   Windows::Foundation::Rect directx_framework_view::get_input_content_rect()
   {

      Windows::Foundation::Rect rect = m_rectInputContentRect;

      return rect;

   }


   Windows::Foundation::Rect directx_framework_view::get_input_selection_rect()
   {

      Windows::Foundation::Rect rect = m_rectInputSelectionRect;

      return rect;

   }


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




