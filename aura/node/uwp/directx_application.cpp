#include "framework.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "aura/os/uwp/_winrt.h"
#include "aura/user/_.h"
#include "_uwp.h"
#include "buffer.h"


CLASS_DECL_ACME void set_core_window_once_visible();

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


   directx_application::directx_application()
   {

   }
      
    
   ::estatus directx_application::initialize_directx_application(::aura::system * psystem, String ^ strId)
   {

      draw2d_direct2d::defer_direct2d_initialize();

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

         ::output_debug_string("Failed to run main_initialize at directx_application constructor.");

         //__throw(::exception::exception("Failed to run main_initialize at directx_application constructor.")

         return ::error_failed;

      }

      m_psystem = psystem;

//      psystem->get_context_session()->m_directxapplication = this;

      auto estatus = __construct_new(m_pdxinteraction);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   directx_application::~directx_application()
   {

      ::draw2d_direct2d::direct2d_finalize();

   }


   void directx_application::initialize_directx_application()
   {

      int nReturnCode = 0;

      if (!m_psystem->begin_synch())
      {

         __throw(::exception::exception("failed to begin_synch the system"));

      }

      auto estatus = m_pdxinteraction->initialize(m_psystem);

      if (!estatus)
      {

         __throw(resource_exception());

      }

      auto psession = m_psystem->get_context_session()->m_paurasession;

      psession->m_paurasession->m_directxapplication = this;

      psession->m_puiHost = m_pdxinteraction;

      m_directx->defer_init();

      //::user::calc_update_dark_mode();

      ::user::create_struct cs;

      auto puiHost = __user_interaction(psession->m_puiHost);

      if (!puiHost->create_window_ex(cs))
      {

         __throw(resource_exception("Couldn't create Main Window"));

         return;

      }

      auto puserinteraction = m_pdxinteraction;

      auto pimpl = puiHost->m_pimpl;

      auto puwpui = pimpl->cast < ::uwp::interaction_impl >();

      puwpui->m_directxapplication = this;

      puwpui->m_window = m_window;

      m_pimpl = puwpui;

      m_directx->m_pimpl = puwpui;

      //puserinteraction->display(display_normal);

      //puserinteraction->set_need_layout();

      //puserinteraction->set_need_redraw();

      //puserinteraction->post_redraw();


   }


   void directx_application::Initialize(CoreApplicationView ^ applicationView)
   {

      impact::Initialize(applicationView);

      applicationView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &directx_application::OnActivated);

      CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs^>(this, &directx_application::OnSuspending);

      CoreApplication::Resuming += ref new EventHandler<Object^>(this, &directx_application::OnResuming);

   }


   void directx_application::install_directx_application_message_routing()
   {
      
      m_puisettings->ColorValuesChanged += ref new TypedEventHandler<Windows::UI::ViewManagement::UISettings^, Platform::Object^> (this, &directx_application::OnUISettingsColorValuesChange);

      CoreWindow ^ window = m_window.Get();

      window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &directx_application::OnWindowVisibilityChanged);

      window->PointerCursor = ref new CoreCursor(CoreCursorType::Arrow, 0);

      window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &directx_application::OnWindowSizeChanged);

      window->PointerMoved += ref new TypedEventHandler < CoreWindow^, PointerEventArgs^>(this, &directx_application::OnPointerMoved);

      window->CharacterReceived += ref new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &directx_application::OnCharacterReceived);

      window->KeyDown += ref new TypedEventHandler < CoreWindow^, KeyEventArgs^>(this, &directx_application::OnKeyDown);

      window->KeyUp += ref new TypedEventHandler < CoreWindow^, KeyEventArgs^>( this, &directx_application::OnKeyUp);

      window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_application::OnPointerPressed);

      window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_application::OnPointerReleased);

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      displayinformation->DpiChanged += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_application::DpiChanged);

      displayinformation->DisplayContentsInvalidated += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_application::DisplayContentsInvalidated);

   }


   void directx_application::SetWindow(CoreWindow^ window)
   {

      impact::SetWindow(window);

      m_directx = ref new directx_base();

      m_directx->m_psystem = m_psystem;

      ::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      m_directx->Initialize(window, displayinformation->LogicalDpi);

      install_directx_application_message_routing();

      initialize_directx_application();

      m_rectLastWindowRect = m_window->Bounds;

      auto psystem = ::get_context_system();

      auto psession = psystem->get_context_session();

      auto phost = psession->m_puiHost;

      auto puiHost = __user_interaction(phost);

      puiHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectWindowScreen.left = 0;
      puiHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectWindowScreen.top = 0;
      puiHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectWindowScreen.right = (LONG) m_window->Bounds.Width;
      puiHost->m_pimpl->cast < ::user::interaction_impl >()->m_rectWindowScreen.bottom = (LONG) m_window->Bounds.Height;

      m_directx->m_bCreated = true;

      ::set_core_window_once_visible();

      on_size({ (LONG)window->Bounds.Width, (LONG)window->Bounds.Height });

   }


   void directx_application::Load(String^ entryPoint)
   {

   }


   void directx_application::Run()
   {

      m_window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);

   }


   void directx_application::Uninitialize()
   {

   }


   void directx_application::OnUISettingsColorValuesChange(Windows::UI::ViewManagement::UISettings^ uisettings, Platform::Object^)
   {

      ::user::defer_calc_os_dark_mode();

   }


   void directx_application::on_size(const ::size& size)
   {

      m_directx->m_size = size;

      m_rectLastWindowRect.Width = (float)m_directx->m_size.cx;

      m_rectLastWindowRect.Height = (float)m_directx->m_size.cy;

      m_directx->OnWindowSizeChange();

   }


   void directx_application::OnWindowSizeChanged(CoreWindow ^ sender, WindowSizeChangedEventArgs ^ args)
   {

      on_size({ (LONG) args->Size.Width, (LONG) args->Size.Height });

   }


   void directx_application::DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      m_rectLastWindowRect = m_window->Bounds;

      m_directx->OnChangeDpi(sender->LogicalDpi);


   }


   void directx_application::DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      // Ensure the D3D Device is available for rendering.

      m_directx->ValidateDevice();

   }


   void directx_application::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
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

            m_psystem->post_object(SYSTEM_MESSAGE, system_message_create, pcreate);

         }

      }

      //{

      //   auto puiHost = Sess(m_psystem).host();

      //   puiHost->set_need_layout();

      //   puiHost->set_need_redraw();

      //   puiHost->post_redraw();

      //}

   }


   void directx_application::OnSuspending(Object ^ sender, SuspendingEventArgs ^ args)
   {

   }


   void directx_application::OnResuming(Object ^ sender, Object ^ args)
   {

   }


   void directx_application::OnCharacterReceived(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::CharacterReceivedEventArgs ^ args)
   {

      if(m_psystem->get_context_session() == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
      {

         return;

      }

      ___pointer < ::message::base > spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      pkey->m_id = WM_CHAR;
      pkey->m_playeredUserPrimitive = puiHost;
      pkey->m_nChar = keycode_to_char(args->KeyCode);

      puiHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_application::OnKeyDown(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {
      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = true;
      }

      if(m_psystem == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
         return;

      ___pointer < ::message::base > spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      bool bTextFocus = Session.get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if(bSpecialKey || !bTextFocus || Session.is_key_pressed(::user::key_control)
         || Session.is_key_pressed(::user::key_alt))
      {

         pkey->m_id                 = WM_KEYDOWN;
         pkey->m_playeredUserPrimitive = puiHost;
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


         puiHost->m_pimpl->queue_message_handler(spbase);

      }

   }


   void directx_application::OnKeyUp(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::KeyEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      if (m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
         return;

      ___pointer < ::message::base > spbase;

      ::message::key * pkey = new  ::message::key;

      spbase = pkey;


      if (args->VirtualKey == ::Windows::System::VirtualKey::Shift)
      {
         m_bFontopusShift = false;
      }
      
      bool bTextFocus = Session.get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::e_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if (bSpecialKey || !bTextFocus)
      {

         pkey->m_id = WM_KEYUP;
         pkey->m_playeredUserPrimitive = puiHost;
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
         puiHost->m_pimpl->queue_message_handler(spbase);
         //}

      }



   }

   void directx_application::OnWindowVisibilityChanged(Windows::UI::Core::CoreWindow^, Windows::UI::Core::VisibilityChangedEventArgs^ args)
   {

      if (args->Visible)
      {

         if (!g_bCoreWindowOnceVisible)
         {

            g_bCoreWindowOnceVisible = true;

         }

         //{

         //   __pointer(::user::interaction) pframe;

         //   auto& app = App(m_psystem);
         //   
         //   //app.get_frame(pframe);

         //   //pframe->set_need_layout();

         //   //pframe->set_need_redraw();

         //   //pframe->post_redraw();

         //}

      }

   }

   void directx_application::OnPointerMoved(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_dwMouseMoveThrottle && m_tickLastMouseMove.elapsed() < m_dwMouseMoveThrottle)
      {

         return;

      }

      if(m_psystem == nullptr)
         return;

      auto pcontextsession = m_psystem->get_context_session();

      if (::is_null(pcontextsession))
      {

         return;

      }

      if(pcontextsession->m_puiHost == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
         return;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ___pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x             = (LONG) pointerPoint->RawPosition.X;
      pmouse->m_point.y             = (LONG) pointerPoint->RawPosition.Y;
      pmouse->m_id                  = WM_MOUSEMOVE;
      pmouse->m_playeredUserPrimitive = puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puiHost->m_pimpl->queue_message_handler(spbase);

      m_tickLastMouseMove = ::get_tick();

   }


   void directx_application::OnPointerPressed(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      if(m_psystem->get_context_session()->m_puiHost == nullptr)
         return;

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
         return;

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ___pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (LONG) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (LONG) pointerPoint->RawPosition.Y;

      if(args->CurrentPoint->Properties->IsLeftButtonPressed && !m_bLeftButton)
      {

         pmouse->m_id     = WM_LBUTTONDOWN;

         m_bLeftButton           = true;
         m_bMiddleButton         = false;
         m_bRightButton          = false;

      }
      else if(args->CurrentPoint->Properties->IsRightButtonPressed && !m_bRightButton)
      {

         pmouse->m_id     = WM_RBUTTONDOWN;

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

      pmouse->m_playeredUserPrimitive = puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puiHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_application::OnPointerReleased(Windows::UI::Core::CoreWindow ^, Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ___pointer < ::message::base > spbase;

      ::message::mouse * pmouse = new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (LONG) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (LONG) pointerPoint->RawPosition.Y;

      if(m_bLeftButton && !args->CurrentPoint->Properties->IsLeftButtonPressed)
      {

         pmouse->m_id     = WM_LBUTTONUP;
         m_bLeftButton           = false;

      }
      else if(m_bRightButton && !args->CurrentPoint->Properties->IsRightButtonPressed)
      {

         pmouse->m_id     = WM_RBUTTONUP;
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

      auto puiHost = __user_interaction(m_psystem->get_context_session()->m_puiHost);

      if (puiHost->m_pimpl == nullptr)
      {

         return;

      }

      pmouse->m_playeredUserPrimitive = puiHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puiHost->m_pimpl->queue_message_handler(spbase);

   }


   directx_application_source::directx_application_source(::aura::system * paxissystem, const string & strId)
   {

      m_psystem     = paxissystem;

      m_strId           = strId;

   }


   Windows::ApplicationModel::Core::IFrameworkView^ directx_application_source::CreateView()
   {

      auto papp =  ref new directx_application;

      papp->initialize_directx_application(m_psystem, m_strId);

      return papp;

   }


   directx_application_source ^ new_directx_application_source(::aura::system * paurasystem, const string & strId)
   {

      string str = strId;

      //str += " client_only";

      //str += " full_screen";

      return ref new directx_application_source(paurasystem, str);

   }

   
   Windows::Foundation::Rect directx_application::get_input_content_rect()
   {

      Windows::Foundation::Rect rect = m_rectInputContentRect;

      return rect;

   }


   Windows::Foundation::Rect directx_application::get_input_selection_rect()
   {

      Windows::Foundation::Rect rect = m_rectInputSelectionRect;

      return rect;

   }


   Windows::Foundation::Rect directx_application::get_window_rect()
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

   Windows::Foundation::Point directx_application::get_cursor_pos()
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

                  for(unsigned int ui = 0; ui < deva->Size; ui++)
                  {

                     Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(ui);

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




