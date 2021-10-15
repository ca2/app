#include "framework.h"
#include "aura/os/windows_common/draw2d_direct2d_global.h"
#include "aura/os/universal_windows/_winrt.h"
#include "aura/node/universal_windows/_uwp.h"
#include "aura/node/universal_windows/buffer.h"
#include "_uwp.h"


extern int g_iMouse;


#undef ::aura::get_system()
#undef Platform


using namespace Platform;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::ApplicationModel;
using namespace ::winrt::Windows::ApplicationModel::Core;
using namespace ::winrt::Windows::ApplicationModel::Activation;
using namespace ::winrt::Windows::::aura::get_system();
using namespace ::winrt::Windows::Graphics::Display;
using namespace ::winrt::Windows::::aura::get_system()::Threading;



namespace universal_windows
{


   directx_framework_view::directx_framework_view(::aura::system * psystem, ::String ^ strId)
   {

      draw2d_direct2d::defer_direct2d_initialize();

      m_puisettings = ref new ::winrt::Windows::UI::ViewManagement::UISettings;

      create_factory < ::universal_windows::buffer, ::graphics::graphics >();

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

         __throw(::exception("Failed to run main_initialize at directx_framework_view constructor."));

      }

      m_psystem = psystem;

      //      psystem->get_session()->m_frameworkview = this;

      m_pdxi = psystem->m_papplicationStartup->__create_new < directx_interaction>();

   }


   directx_framework_view::~directx_framework_view()
   {

      ::draw2d_direct2d::direct2d_finalize();

   }


   void directx_framework_view::initialize_directx_application()
   {

      int nReturnCode = 0;

      if (!m_psystem->m_htask)
      {

         if (!m_psystem->begin_synch())
         {

            __throw(::exception("failed to begin_synch the system"));

         }

      }

      auto estatus = m_pdxi->initialize(m_psystem);

      if (!estatus)
      {

         __throw(error_resource);

      }

      //m_psystem->get_session()->m_pframeworkview = this;

      m_psystem->get_session()->m_puserinteractionHost = m_pdxi;

      m_directx->defer_init();

      ::user::os_calc_dark_mode();

      auto pcs = __new(::user::system);

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      auto routine = [this]()
      {

         manual_reset_event ev;

         m_window->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler(
            [this, &ev]()
            {

               //m_directx->m_windowBounds = m_window->Bounds;

               //auto pchanged = ref new ::winrt::Windows::UI::Core::WindowSizeChangedEventArgs();

               ::size_i32 size((LONG) m_window->Bounds.Width, (LONG) m_window->Bounds.Height);

               //pchanged->Size.Height = m_window->Bounds.Height;

               on_window_size_changed(m_window.Get(), size);

               subject.set_event();

            }));

         subject.wait(15_s);

         auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

         auto puserinteraction = m_pdxi;

         //puserinteraction->display(e_display_normal);

         //puserinteraction->set_need_layout();

         //puserinteraction->set_need_redraw();

         //puserinteraction->post_redraw();


      };

      pcs->m_routineSuccess = __routine(routine);

      m_pimpl = __create < ::user::interaction_impl >();

      m_pimpl->m_rectangle.left = (LONG) m_window->Bounds.X;
      m_pimpl->m_rectangle.top = (LONG) m_window->Bounds.Y;
      m_pimpl->m_rectangle.right = (LONG) (m_window->Bounds.X + m_window->Bounds.Width);
      m_pimpl->m_rectangle.top = (LONG) (m_window->Bounds.Y + m_window->Bounds.Height);

      m_pimpl->m_window = m_window;

      m_directx->m_pimpl = m_pimpl;

      m_pimpl->m_pframeworkview = this;

      pcs->m_pimpl = m_pimpl;

      get_context_system()->m_paurasystem->m_pimplMain = m_pimpl;

      //m_pimpl->m_bNotifyLayoutCompletedPending = true;

      if (!puserinteractionHost->create_window_ex(pcs))
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

      m_puisettings->ColorValuesChanged += ref new TypedEventHandler<::winrt::Windows::UI::ViewManagement::UISettings ^, Platform::Object ^>(this, &directx_framework_view::OnUISettingsColorValuesChange);

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

      ::winrt::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

      displayinformation->DpiChanged += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DpiChanged);

      displayinformation->DisplayContentsInvalidated += ref new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_view::DisplayContentsInvalidated);

   }


   void directx_framework_view::SetWindow(CoreWindow ^ window)
   {

      impact::SetWindow(window);

      m_directx = ref new directx_base();

      m_directx->m_psystem = m_psystem;

      ::winrt::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();

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


   void directx_framework_view::OnUISettingsColorValuesChange(::winrt::Windows::UI::ViewManagement::UISettings ^ uisettings, Platform::Object ^)
   {

      ::user::os_calc_dark_mode();

   }


   void directx_framework_view::OnWindowSizeChanged(CoreWindow ^ sender, WindowSizeChangedEventArgs ^ args)
   {

      ::size_i32 size((LONG) args->Size.Width, (LONG) args->Size.Height);

      on_window_size_changed(sender, size);

   }


   void directx_framework_view::on_window_size_changed(CoreWindow ^ sender, const ::size_i32 & size)
   {

      m_directx->m_size = size;

      m_rectangleLastWindowRect.Width = (float)m_directx->m_size.cx;

      m_rectangleLastWindowRect.Height = (float)m_directx->m_size.cy;

      m_directx->OnWindowSizeChange();

   }

 
   void directx_framework_view::DpiChanged(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      m_rectangleLastWindowRect = m_window->Bounds;

      m_directx->OnChangeDpi(sender->LogicalDpi);


   }


   void directx_framework_view::DisplayContentsInvalidated(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
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

            //   papp = m_psystem->get_session()->m_papplicationCurrent;

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


   void directx_framework_view::OnCharacterReceived(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::CharacterReceivedEventArgs ^ args)
   {

      if(m_psystem->get_session() == nullptr)
         return;

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
         return;

      if (puserinteractionHost->m_pimpl == nullptr)
         return;

      __pointer(::user::message) pusermessage;

      auto pkey  = __new(::message::key);

      pusermessage = pkey;

      pkey->m_id = e_message_char;
      pkey->m_playeredUserPrimitive = puserinteractionHost;
      pkey->m_nChar = keycode_to_char(args->KeyCode);

      puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);

   }


   void directx_framework_view::OnKeyDown(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::KeyEventArgs ^ args)
   {
      if (args->VirtualKey == ::winrt::Windows::::aura::get_system()::VirtualKey::Shift)
      {
         m_bFontopusShift = true;
      }

      if(m_psystem == nullptr)
         return;

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
         return;

      if (puserinteractionHost->m_pimpl == nullptr)
         return;

      __pointer(::user::message) pusermessage;

      auto pkey  = __new(::message::key);

      pusermessage = pkey;

      bool bTextFocus = m_puserinteraction->get_keyboard_focus() != nullptr;

      bool bSpecialKey = false;

      ::user::enum_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if(bSpecialKey || !bTextFocus || m_psystem->get_session()->is_key_pressed(::user::e_key_control)
         || m_psystem->get_session()->is_key_pressed(::user::e_key_alt))
      {

         pkey->m_id                 = e_message_key_down;
         pkey->m_playeredUserPrimitive       = m_psystem->get_session()->m_puserinteractionHost;
         pkey->m_nChar              = virtualkey_to_char(args->VirtualKey);
         pkey->m_ekey               = ekey;
         pkey->m_wparam             = pkey->m_nChar;
         pkey->m_nFlags             = virtualkey_to_code(args->VirtualKey);
         pkey->m_lparam             = pkey->m_nFlags << 16;
         //pkey->m_strText            = m_strNewText;
         //if (pkey->m_strText.has_char())
         //{
           // pkey->m_ekey = ::user::e_key_refer_to_text_member;
         //}
   //      pkey->m_key = args;


         puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);

      }

   }

   void directx_framework_view::OnKeyUp(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::KeyEventArgs ^ args)
   {

      if(m_psystem == nullptr)
         return;

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
         return;

      if (puserinteractionHost->m_pimpl == nullptr)
         return;

      __pointer(::user::message) pusermessage;

      ::message::key * pkey = new  ::message::key;

      pusermessage = pkey;


      if (args->VirtualKey == ::winrt::Windows::::aura::get_system()::VirtualKey::Shift)
      {
         m_bFontopusShift = false;
      }
      
      bool bTextFocus = m_puserinteraction->get_keyboard_focus() != nullptr;

      bool bSpecialKey = false;

      ::user::enum_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if (bSpecialKey || !bTextFocus)
      {

         pkey->m_id = e_message_key_up;
         pkey->m_playeredUserPrimitive = m_psystem->get_session()->m_puserinteractionHost;
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
         puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);
         //}

      }



   }


   void directx_framework_view::OnWindowClosed(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::CoreWindowEventArgs ^ args)
   {

   }


   void directx_framework_view::OnWindowVisibilityChanged(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::VisibilityChangedEventArgs^ args)
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

   void directx_framework_view::OnPointerMoved(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      //if (m_dwMouseMoveThrottle && m_durationLastMouseMove.elapsed() < m_dwMouseMoveThrottle)
      //{

        // return;

      //}

      if(m_psystem == nullptr)
         return;

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
         return;

      if (puserinteractionHost->m_pimpl == nullptr)
         return;

      __pointer(::user::message) pusermessage;

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::message::mouse * pmouse = new ::message::mouse;

      pusermessage = pmouse;

      pmouse->m_point.x       = (::i32) pointerPoint->RawPosition.X;
      pmouse->m_point.y       = (::i32) pointerPoint->RawPosition.Y;
      pmouse->m_id            = e_message_mouse_move;
      pmouse->m_playeredUserPrimitive  = m_psystem->get_session()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      auto pimpl = __uwp_user_interaction_impl(puserinteractionHost->m_pimpl);

      pimpl->m_pointCursor.set(
         (LONG) pointerPoint->RawPosition.X, 
         (LONG) pointerPoint->RawPosition.Y);

      puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);

      m_durationLastMouseMove= ::duration::now();

   }


   void directx_framework_view::OnPointerPressed(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
      {

         return;

      }

      if (puserinteractionHost->m_pimpl == nullptr)
      {

         return;

      }

      __pointer(::user::message) pusermessage;

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::message::mouse * pmouse = new  ::message::mouse;

      pusermessage = pmouse;

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

      pmouse->m_playeredUserPrimitive = m_psystem->get_session()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);

   }


   void directx_framework_view::OnPointerReleased(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_psystem == nullptr)
      {

         return;

      }

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      auto puserinteractionHost = __user_interaction(m_psystem->get_session()->m_puserinteractionHost);

      if (puserinteractionHost == nullptr)
         return;

      if (puserinteractionHost->m_pimpl == nullptr)
         return;

      __pointer(::user::message) pusermessage;

      ::message::mouse * pmouse = new  ::message::mouse;

      pusermessage = pmouse;

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

      pmouse->m_playeredUserPrimitive = m_psystem->get_session()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      puserinteractionHost->m_pimpl->queue_message_handler(pusermessage);

   }


   directx_application_source::directx_application_source(::aura::system * paxissystem, const ::string & strId)
   {

      m_psystem     = paxissystem;

      m_strId           = strId;

   }


   ::winrt::Windows::ApplicationModel::Core::IFrameworkView^ directx_application_source::CreateView()
   {

      return ref new directx_framework_view(m_psystem,m_strId);

   }


   directx_application_source ^ new_directx_application_source(::aura::system * papexsystem, const ::string & strId)
   {

      string str = strId;

      //str += " client_only";

      //str += " full_screen";

      return ref new directx_application_source(papexsystem, str);

   }

   
   ::winrt::Windows::Foundation::Rect directx_framework_view::get_input_content_rect()
   {

      ::winrt::Windows::Foundation::Rect rectangle_i32;
      
      auto pfocusui = m_puserinteraction->get_keyboard_focus();

      auto puserinteraction = __user_interaction(pfocusui);

      if (puserinteraction)
      {

         ::rectangle_i32 r = puserinteraction->get_window_rect();

         m_rectangleInputContentRect.X = (float) r.left;
         m_rectangleInputContentRect.Y = (float)r.top;
         m_rectangleInputContentRect.Width = (float)r.width();
         m_rectangleInputContentRect.Height = (float)r.height();

      }

      rectangle = m_rectangleInputContentRect;

      return rectangle;

   }


   ::winrt::Windows::Foundation::Rect directx_framework_view::get_input_selection_rect()
   {

      ::winrt::Windows::Foundation::Rect rectangle = m_rectangleInputSelectionRect;

      return rectangle;

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


   ::winrt::Windows::Foundation::Rect directx_framework_view::get_window_rect()
   {

      ::winrt::Windows::Foundation::Rect rectangle = m_rectangleLastWindowRect;

      /*      rectangle.X = 0;
            rectangle.Y = 0;
            rectangle.Width = 600;
            rectangle.Height = 480;

            if(m_window == nullptr)
               return rectangle;

            ::wait(m_window->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler ([=, &rectangle]()
            {
               try
               {
                  rectangle = m_window->Bounds;
               }
               catch(...)
               {
               }
            })));*/

      return rectangle;

   }

   ::winrt::Windows::Foundation::Point directx_framework_view::get_cursor_position()
   {

      single_lock synchronouslock(&m_mutex, true);

      ::winrt::Windows::Foundation::Point p = m_pointLastCursor;

      /*      if(m_window == nullptr)
               return p;

            if(g_iMouse < 0)
               return p;

            ::wait(m_window->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref new ::winrt::Windows::UI::Core::DispatchedHandler ([=, &p]()
            {
               try
               {

                  ::winrt::Windows::Foundation::Collections::IVectorView < ::winrt::Windows::Devices::Input::PointerDevice ^ > ^ deva = ::winrt::Windows::Devices::Input::PointerDevice::GetPointerDevices();

                  for(unsigned int u = 0; u < deva->Size; u++)
                  {

                     ::winrt::Windows::Devices::Input::PointerDevice ^ dev = deva->GetAt(u);

                     if(dev->PointerDeviceType == ::winrt::Windows::Devices::Input::PointerDeviceType::Mouse)
                     {

                        ::winrt::Windows::UI::Input::PointerPoint ^ pointerPoint = ::winrt::Windows::UI::Input::PointerPoint::GetCurrentPoint(g_iMouse);

                        p = pointerPoint->RawPosition;

                        break;

                     }

                  }

               }
               catch(...)
               {
               }
            })), 5); // wait for up to 5 ::durations

            m_pointLastCursor = p;*/

      return p;

   }


} // namespace universal_windows




