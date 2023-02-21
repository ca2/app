#include "framework.h"
#include "acme/operating_system/windows_common/draw2d_direct2d_global.h"
#include "acme/operating_system/universal_windows/_winrt.h"
#include "_uwp.h"
#include "buffer.h"


extern int g_iMouse;


#undef ::acmeacmesystem()
#undef Platform


using namespace Platform;
using namespace Microsoft::WRL;
using namespace ::winrt::Windows::Foundation;
using namespace ::winrt::Windows::UI::Core;
using namespace ::winrt::Windows::ApplicationModel;
using namespace ::winrt::Windows::ApplicationModel::Core;
using namespace ::winrt::Windows::ApplicationModel::Activation;
using namespace ::winrt::Windows::acmeacmesystem();
using namespace ::winrt::Windows::Graphics::Display;
using namespace ::winrt::Windows::acmeacmesystem()::Threading;

bool g_bCoreWindowOnceVisible = false;


namespace universal_windows
{


   directx_framework_impact::directx_framework_impact(::acme::system * psystem, ::String ^ strId)
   {

      draw2d_direct2d::direct2d_initialize();

      m_puisettings = ref memory_new ::winrt::Windows::UI::ViewManagement::UISettings;
         
      add_factory_item < ::universal_windows::buffer, ::graphics::graphics >();

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

         throw ::exception(::exception("Failed to run main_initialize at directx_framework_impact constructor."));

      }

      acmesystem() = psystem;

//      psystem->get_session()->m_frameworkview = this;

      m_pdxi = __new(directx_interaction);

   }


   directx_framework_impact::~directx_framework_impact()
   {

      ::draw2d_direct2d::direct2d_finalize();

   }


   void directx_framework_impact::initialize_directx_application()
   {

      int nReturnCode = 0;

      if (!acmesystem()->begin_synch())
      {

         throw ::exception(::exception("failed to begin_synch the system"));

      }

      auto estatus = m_pdxi->initialize(acmesystem());

      if (!estatus)
      {

         throw ::exception(error_resource);

      }

      acmesession()->m_frameworkview = this;

      acmesession()->m_puserinteractionHost = m_pdxi;

      m_directx->defer_init();

      ::user::os_update_dark_mode();

      ::user::system cs;

      if (!acmesession()->m_puserinteractionHost->create_window_ex(cs))
      {

         throw ::exception(resource_exception("Couldn't create Main Window"));

         return;

      }

      auto puserinteraction = m_pdxi;

      auto pimpl = acmesession()->m_puserinteractionHost->m_pimpl;

      auto puwpui = pimpl->cast < ::universal_windows::interaction_impl >();

      puwpui->m_frameworkview = this;

      puwpui->m_window = m_window;

      m_pimpl = puwpui;

      m_directx->m_pimpl = puwpui;



      puserinteraction->display(e_display_restored);

      puserinteraction->set_need_layout();

      puserinteraction->set_need_redraw();

      puserinteraction->post_redraw();


   }


   void directx_framework_impact::Initialize(CoreApplicationView ^ applicationView)
   {

      impact::Initialize(applicationView);

      applicationView->Activated += ref memory_new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &directx_framework_impact::OnActivated);

      CoreApplication::Suspending += ref memory_new EventHandler<SuspendingEventArgs^>(this, &directx_framework_impact::OnSuspending);

      CoreApplication::Resuming += ref memory_new EventHandler<Object^>(this, &directx_framework_impact::OnResuming);

   }


   void directx_framework_impact::install_directx_application_message_routing()
   {
      
      m_puisettings->ColorValuesChanged += ref memory_new TypedEventHandler<::winrt::Windows::UI::ViewManagement::UISettings^, Platform::Object^> (this, &directx_framework_impact::OnUISettingsColorValuesChange);

      CoreWindow ^ window = m_window.Get();

      window->VisibilityChanged += ref memory_new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &directx_framework_impact::OnWindowVisibilityChanged);

      window->PointerCursor = ref memory_new CoreCursor(CoreCursorType::Arrow, 0);

      window->SizeChanged += ref memory_new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &directx_framework_impact::OnWindowSizeChanged);

      window->PointerMoved += ref memory_new TypedEventHandler < CoreWindow^, PointerEventArgs^>(this, &directx_framework_impact::OnPointerMoved);

      window->CharacterReceived += ref memory_new TypedEventHandler<CoreWindow^, CharacterReceivedEventArgs^>(this, &directx_framework_impact::OnCharacterReceived);

      window->KeyDown += ref memory_new TypedEventHandler < CoreWindow^, KeyEventArgs^>(this, &directx_framework_impact::OnKeyDown);

      window->KeyUp += ref memory_new TypedEventHandler < CoreWindow^, KeyEventArgs^>( this, &directx_framework_impact::OnKeyUp);

      window->PointerPressed += ref memory_new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_framework_impact::OnPointerPressed);

      window->PointerReleased += ref memory_new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &directx_framework_impact::OnPointerReleased);

      ::winrt::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentImpact();

      displayinformation->DpiChanged += ref memory_new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_impact::DpiChanged);

      displayinformation->DisplayContentsInvalidated += ref memory_new TypedEventHandler < DisplayInformation ^, Object ^ >(this, &directx_framework_impact::DisplayContentsInvalidated);

   }


   void directx_framework_impact::SetWindow(CoreWindow^ window)
   {

      impact::SetWindow(window);

      m_directx = ref memory_new directx_base();

      m_directx->acmesystem() = acmesystem();

      ::winrt::Windows::Graphics::Display::DisplayInformation ^ displayinformation = ::winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentImpact();

      m_directx->Initialize(window, displayinformation->LogicalDpi);

      install_directx_application_message_routing();

      initialize_directx_application();

      m_rectangleLastWindowRect = m_window->Bounds;

   }


   void directx_framework_impact::Load(String^ entryPoint)
   {

   }


   void directx_framework_impact::Run()
   {

      m_window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);

   }


   void directx_framework_impact::Uninitialize()
   {

   }


   void directx_framework_impact::OnUISettingsColorValuesChange(::winrt::Windows::UI::ViewManagement::UISettings^ uisettings, Platform::Object^)
   {

      ::user::os_update_dark_mode();

   }


   void directx_framework_impact::OnWindowSizeChanged(CoreWindow ^ sender, WindowSizeChangedEventArgs ^ args)
   {

      m_directx->m_size.set_size((i32) args->Size.Width, (i32)args->Size.Height);

      m_rectangleLastWindowRect.Width = (float) m_directx->m_size.cx;

      m_rectangleLastWindowRect.Height = (float) m_directx->m_size.cy;

      m_directx->OnWindowSizeChange();

   }


   void directx_framework_impact::DpiChanged(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      m_rectangleLastWindowRect = m_window->Bounds;

      m_directx->OnChangeDpi(sender->LogicalDpi);


   }


   void directx_framework_impact::DisplayContentsInvalidated(::winrt::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj)
   {

      // Ensure the D3D Device is available for rendering.

      m_directx->ValidateDevice();

   }


   void directx_framework_impact::OnActivated(CoreApplicationView^ applicationView, IActivatedEventArgs^ args)
   {

      m_window->Activate();

      if (args != nullptr)
      {

         if (args->Kind == ActivationKind::Protocol)
         {

            ProtocolActivatedEventArgs ^ eventArgs = (ProtocolActivatedEventArgs ^)args;

            string str = eventArgs->Uri->AbsoluteUri;

            auto pcreate = __new(::create(acmesystem()));

            pcreate->m_ecommand = ::command_protocol;

            pcreate->m_payloadFile = str;

            //acmesystem()->add_create(pcreate);

            //auto papp = m_pcontext->acmeapplication();

            //if (papp == nullptr)
            //{

            //   papp = acmesession()->m_pappCurrent;

            //}

            acmesystem()->post_object(e_message_system, e_system_message_create, pcreate);

         }

      }


   }


   void directx_framework_impact::OnSuspending(Object ^ sender, SuspendingEventArgs ^ args)
   {

   }


   void directx_framework_impact::OnResuming(Object ^ sender, Object ^ args)
   {

   }


   void directx_framework_impact::OnCharacterReceived(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::CharacterReceivedEventArgs ^ args)
   {

      if(acmesession() == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
         return;

      ::pointer<::user::message>spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      pkey->m_atom = e_message_char;
      pkey->m_puserinteraction = acmesession()->m_puserinteractionHost;
      pkey->m_nChar = keycode_to_char(args->KeyCode);

      acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_framework_impact::OnKeyDown(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::KeyEventArgs ^ args)
   {
      if (args->VirtualKey == ::winrt::Windows::acmeacmesystem()::VirtualKey::Shift)
      {
         m_bFontopusShift = true;
      }

      if(acmesystem() == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
         return;

      ::pointer<::user::message>spbase;

      auto pkey  = __new(::message::key);

      spbase = pkey;

      bool bTextFocus = acmesession()->get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::enum_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if(bSpecialKey || !bTextFocus || acmesession()->is_key_pressed(::user::e_key_control)
         || acmesession()->is_key_pressed(::user::e_key_alt))
      {

         pkey->m_atom                 = e_message_key_down;
         pkey->m_puserinteraction       = acmesession()->m_puserinteractionHost;
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


         acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);

      }

   }

   void directx_framework_impact::OnKeyUp(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::KeyEventArgs ^ args)
   {

      if(acmesystem() == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost == nullptr)
         return;

      if (acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
         return;

      ::pointer<::user::message>spbase;

      ::message::key * pkey = memory_new  ::message::key;

      spbase = pkey;


      if (args->VirtualKey == ::winrt::Windows::acmeacmesystem()::VirtualKey::Shift)
      {
         m_bFontopusShift = false;
      }
      
      bool bTextFocus = acmesession()->get_focus_ui() != nullptr;

      bool bSpecialKey = false;

      ::user::enum_key ekey = virtualkey_to_userkey(args->VirtualKey, bSpecialKey);

      if (bSpecialKey || !bTextFocus)
      {

         pkey->m_atom = e_message_key_up;
         pkey->m_puserinteraction = acmesession()->m_puserinteractionHost;
         pkey->m_nChar = virtualkey_to_char(args->VirtualKey);
         pkey->m_ekey = ekey;
         pkey->m_wparam = pkey->m_nChar;


         //      pkey->m_key = args;

               //if (acmesystem()->m_psimpleui != nullptr && acmesystem()->m_psimpleui->is_window_visible())
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
               //   acmesystem()->m_psimpleui->on_char(virtualkey_to_userkey(args->VirtualKey), str);
               //}
               //else
               //{
         acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);
         //}

      }



   }

   void directx_framework_impact::OnWindowVisibilityChanged(::winrt::Windows::UI::Core::CoreWindow^, ::winrt::Windows::UI::Core::VisibilityChangedEventArgs^ args)
   {

      if (args->Visible)
      {

         if (!g_bCoreWindowOnceVisible)
         {

            g_bCoreWindowOnceVisible = true;

         }

      }

   }

   void directx_framework_impact::OnPointerMoved(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (m_dwMouseMoveThrottle && m_durationLastMouseMove.elapsed() < m_dwMouseMoveThrottle)
      {

         return;

      }

      if(acmesystem() == nullptr)
         return;

      if(acmesession()->m_puserinteractionHost == nullptr)
         return;

      if(acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
         return;

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::pointer<::user::message>spbase;

      ::message::mouse * pmouse = memory_new ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x       = (::i32) pointerPoint->RawPosition.X;
      pmouse->m_point.y       = (::i32) pointerPoint->RawPosition.Y;
      pmouse->m_atom            = e_message_mouse_move;
      pmouse->m_puserinteraction  = acmesession()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);

      m_durationLastMouseMove= ::duration::now();

   }


   void directx_framework_impact::OnPointerPressed(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      if(acmesystem() == nullptr)
         return;

      if(acmesession()->m_puserinteractionHost == nullptr)
         return;

      if(acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
         return;

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::pointer<::user::message>spbase;

      ::message::mouse * pmouse = memory_new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(args->CurrentPoint->Properties->IsLeftButtonPressed && !m_bLeftButton)
      {

         pmouse->m_atom     = e_message_left_button_down;

         m_bLeftButton           = true;
         m_bMiddleButton         = false;
         m_bRightButton          = false;

      }
      else if(args->CurrentPoint->Properties->IsRightButtonPressed && !m_bRightButton)
      {

         pmouse->m_atom     = e_message_right_button_down;

         m_bLeftButton           = false;
         m_bMiddleButton         = false;
         m_bRightButton          = true;

      }
      else if(args->CurrentPoint->Properties->IsMiddleButtonPressed && !m_bMiddleButton)
      {

         pmouse->m_atom     = e_message_middle_button_down;

         m_bLeftButton           = false;
         m_bMiddleButton         = true;
         m_bRightButton          = false;

      }

      pmouse->m_puserinteraction = acmesession()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);

   }


   void directx_framework_impact::OnPointerReleased(::winrt::Windows::UI::Core::CoreWindow ^, ::winrt::Windows::UI::Core::PointerEventArgs ^ args)
   {

      if (acmesystem() == nullptr)
      {

         return;

      }

      ::winrt::Windows::UI::Input::PointerPoint^ pointerPoint = args->CurrentPoint;

      ::g_iMouse = pointerPoint->PointerId;

      ::pointer<::user::message>spbase;

      ::message::mouse * pmouse = memory_new  ::message::mouse;

      spbase = pmouse;

      pmouse->m_point.x = (::i32) pointerPoint->RawPosition.X;

      pmouse->m_point.y = (::i32) pointerPoint->RawPosition.Y;

      if(m_bLeftButton && !args->CurrentPoint->Properties->IsLeftButtonPressed)
      {

         pmouse->m_atom     = e_message_left_button_up;
         m_bLeftButton           = false;

      }
      else if(m_bRightButton && !args->CurrentPoint->Properties->IsRightButtonPressed)
      {

         pmouse->m_atom     = e_message_right_button_up;
         m_bRightButton          = false;

      }
      else if(m_bMiddleButton && !args->CurrentPoint->Properties->IsMiddleButtonPressed)
      {

         pmouse->m_atom     = e_message_middle_button_up;
         m_bMiddleButton         = false;

      }

      if (acmesession()->m_puserinteractionHost == nullptr)
      {

         return;

      }

      if (acmesession()->m_puserinteractionHost->m_pimpl == nullptr)
      {

         return;

      }

      pmouse->m_puserinteraction = acmesession()->m_puserinteractionHost;

      m_pointLastCursor = pointerPoint->RawPosition;

      acmesession()->m_puserinteractionHost->m_pimpl->queue_message_handler(spbase);

   }


   directx_application_source::directx_application_source(::acme::system * paxissystem, const ::string & strId)
   {

      acmesystem()     = paxissystem;

      m_strId           = strId;

   }


   ::winrt::Windows::ApplicationModel::Core::IFrameworkView^ directx_application_source::CreateImpact()
   {

      return ref memory_new directx_framework_impact(acmesystem(),m_strId);

   }


   directx_application_source ^ new_directx_application_source(::acme::system * paurasystem, const ::string & strId)
   {

      string str = strId;

      //str += " client_only";

      //str += " full_screen";

      return ref memory_new directx_application_source(paurasystem, str);

   }

   
   ::winrt::Windows::Foundation::Rect directx_framework_impact::get_input_content_rect()
   {

      ::winrt::Windows::Foundation::Rect rectangle = m_rectangleInputContentRect;

      return rectangle;

   }


   ::winrt::Windows::Foundation::Rect directx_framework_impact::get_input_selection_rect()
   {

      ::winrt::Windows::Foundation::Rect rectangle = m_rectangleInputSelectionRect;

      return rectangle;

   }


   ::winrt::Windows::Foundation::Rect directx_framework_impact::window_rectangle()
   {

      ::winrt::Windows::Foundation::Rect rectangle = m_rectangleLastWindowRect;

      /*      rectangle.X = 0;
            rectangle.Y = 0;
            rectangle.Width = 600;
            rectangle.Height = 480;

            if(m_window == nullptr)
               return rectangle;

            ::wait(m_window->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler ([=, &rectangle]()
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

   ::winrt::Windows::Foundation::Point directx_framework_impact::get_cursor_position()
   {

      single_lock synchronouslock(m_pmutex, true);

      ::winrt::Windows::Foundation::Point p = m_pointLastCursor;

      /*      if(m_window == nullptr)
               return p;

            if(g_iMouse < 0)
               return p;

            ::wait(m_window->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler ([=, &p]()
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




