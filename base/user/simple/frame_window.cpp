#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/simple/_simple.h"
#endif
#include "aura/message.h"
#include "aura/update.h"
#include "aqua/xml.h"


#ifdef WINDOWS_DESKTOP
#include <dde.h>
#endif


#define TEST 0


namespace base
{


   ::type user::get_simple_frame_window_type_info()
   {

      return __type(::simple_frame_window);

   }


} // namespace base


simple_frame_window::simple_frame_window()
{

   m_bFramePayloadFlags = false;

   m_bProdevianFrame = true;

   m_etranslucencyFrame = ::user::translucency_present;

   m_bDefaultCreateToolbar = true;

   m_bShowTask = true;

   m_bDefaultNotifyIcon = false;

#if defined(_UWP)

   m_bTransparentFrameEnable = false;

#else

   m_bTransparentFrameEnable = true;

#endif

   //m_bblur_Background = false;

   m_bCustomFrameBefore = true;

   m_bFirstShow = true;

   m_bSaveWindowRect = true;

   m_bEnableSaveWindowRect2 = true;

   m_bFullScreenOnMaximize = false;

//#if defined(APPLE_IOS) || defined(ANDROID)

   m_bWindowFrame = false;

//#else

  // m_bWindowFrame = true;

//#endif

   m_bLayered = true;

   m_pdocumenttemplate = nullptr;

}


simple_frame_window::~simple_frame_window()
{

   //m_phelpertask->m_pframe = nullptr;

   //m_phelpertask->m_bRun = false;

}


::estatus simple_frame_window::initialize(::layered * pobjectContext)
{

   auto estatus = ::experience::frame_window::initialize(pobjectContext);

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


::user::e_translucency simple_frame_window::get_translucency(::user::style* pstyle) const
{

   if (m_etranslucencyFrame != ::user::translucency_undefined)
   {

      return m_etranslucencyFrame;

   }

   return ::experience::frame_window::get_translucency(pstyle);

}


void simple_frame_window::install_message_routing(::channel * pchannel)
{

   ::experience::frame_window::install_message_routing(pchannel);

   IGUI_MSG_LINK(WM_CREATE, pchannel, this, &simple_frame_window::_001OnCreate);
#ifdef WINDOWS_DESKTOP
   IGUI_MSG_LINK(WM_DDE_INITIATE, pchannel, this, &simple_frame_window::_001OnDdeInitiate);
#endif
   IGUI_MSG_LINK(WM_DESTROY, pchannel, this, &simple_frame_window::_001OnDestroy);
   IGUI_MSG_LINK(WM_CLOSE, pchannel, this, &simple_frame_window::_001OnClose);
   IGUI_MSG_LINK(WM_SIZE, pchannel, this, &simple_frame_window::_001OnSize);
   IGUI_MSG_LINK(WM_MOVE, pchannel, this, &simple_frame_window::_001OnMove);
   IGUI_MSG_LINK(WM_GETMINMAXINFO, pchannel, this, &simple_frame_window::_001OnGetMinMaxInfo);
   IGUI_MSG_LINK(WM_MOUSEMOVE, pchannel, this, &simple_frame_window::_001OnMouseMove);
   IGUI_MSG_LINK(WM_DISPLAYCHANGE, pchannel, this, &simple_frame_window::_001OnDisplayChange);
   IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &simple_frame_window::_001OnShowWindow);
   IGUI_MSG_LINK(WM_MOUSEACTIVATE, pchannel, this, &simple_frame_window::_001OnMouseActivate);
   IGUI_MSG_LINK(WM_NCHITTEST, pchannel, this, &simple_frame_window::_001OnNcHitTest);

   IGUI_MSG_LINK(WM_KEYDOWN, pchannel, this, &simple_frame_window::_001OnKey);
   IGUI_MSG_LINK(WM_SYSKEYDOWN, pchannel, this, &simple_frame_window::_001OnKey);
   IGUI_MSG_LINK(WM_KEYUP, pchannel, this, &simple_frame_window::_001OnKey);
   IGUI_MSG_LINK(WM_SYSKEYUP, pchannel, this, &simple_frame_window::_001OnKey);

   connect_command_probe("transparent_frame", &simple_frame_window::_001OnUpdateToggleTransparentFrame);
   connect_command("transparent_frame", &simple_frame_window::_001OnToggleTransparentFrame);

   connect_command_probe("impact_full_screen", &simple_frame_window::_001OnUpdateViewFullScreen);
   connect_command("impact_full_screen", &simple_frame_window::_001OnViewFullScreen);

   connect_command("notify_icon_topic", &simple_frame_window::_001OnNotifyIconTopic);
   connect_command("app_exit", &simple_frame_window::_001OnAppExit);

   IGUI_MSG_LINK(WM_APPEXIT, pchannel, this, &simple_frame_window::_001OnAppExit);
   IGUI_MSG_LINK(WM_ACTIVATEAPP, pchannel, this, &simple_frame_window::_001OnActivateApp);
   IGUI_MSG_LINK(WM_ACTIVATE, pchannel, this, &simple_frame_window::_001OnActivate);
   IGUI_MSG_LINK(message_update_notify_icon, pchannel, this, &simple_frame_window::_001OnUpdateNotifyIcon);

#ifdef WINDOWS_DESKTOP

   IGUI_MSG_LINK(System.m_uiWindowsTaskbarCreatedMessage, pchannel, this, &simple_frame_window::_001OnTaskbarCreated);

#endif

}


void simple_frame_window::defer_save_window_placement()
{

   sync_lock sl(mutex());

   if (!should_save_window_rect())
   {

      return;

   }

   m_bPendingSaveWindowRect = true;

   m_tickLastSaveWindowRectRequest.Now();

   defer_fork("save_window_rect", [this]()
   {

         while (::thread_get_run()
            && (m_ewindowflag & window_flag_is_window)
            && m_pimpl
               && !m_pimpl->m_bDestroying)
         {

            if (m_tickLastSaveWindowRectRequest.elapsed() < 200_ms)
            {
            }
            else if (m_bPendingSaveWindowRect)
            {

               try
               {

                  _thread_save_window_placement();

                  m_tickLastSaveWindowRect.Now();

               }
               catch (...)
               {

               }

            }
            else if (m_tickLastSaveWindowRect.elapsed() > 10000)
            {

               break;

            }
            else
            {

               Sleep(1_s);

            }

         }

      }
   );

}


bool simple_frame_window::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
{

   if (wfi_is_up_down())
   {

      if (!(m_uiUserInteractionFlags & ::user::interaction_wfi_up_down_loading))
      {

         __keep_on(&m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

         bool bWfiDown = true;

         Application.data_get("wfi_down", bWfiDown);

         if (bWfiDown)
         {

            design_down();

            return true;

         }
         else
         {

            design_up();

            if (m_ewindowflag & window_flag_window_created)
            {

               return true;

            }

         }

      }
      else if (wfi_is_down())
      {
         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("interaction_child::WindowDataLoadWindowRect (3)");
         INFO("");
         INFO("");

         return false;

      }

   }

   INFO("-------------------------------------------------------------------");
   INFO("");
   INFO("");
   INFO("interaction_child::WindowDataLoadWindowRect (4)");
   INFO("");
   INFO("");

   return ::experience::frame_window::WindowDataLoadWindowRect(bForceRestore, bInitialFramePosition);

}


bool simple_frame_window::WindowDataSaveWindowRect()
{

   if(wfi_is_up_down())
   {

      bool bDown;

      bDown = m_eupdown != updown_up;

      Application.data_set("wfi_down", bDown);

   }

   return ::experience::frame_window::WindowDataSaveWindowRect();

}


bool simple_frame_window::_001OnBeforeAppearance()
{

   edisplay edisplay = layout().sketch().display();

   if (edisplay == ::display_up || edisplay == ::display_down)
   {

      if (!initialize_frame_window_experience())
      {

         return false;

      }

   }

   if (!::experience::frame_window::_001OnBeforeAppearance())
   {

      return false;

   }

   if (!::user::frame_window::_001OnBeforeAppearance())
   {

      return false;

   }

   return true;

}


void simple_frame_window::_thread_save_window_placement()
{

   while (::thread_get_run())
   {

      if (!thread_sleep(300))
      {

         break;

      }

      if (layout().m_eflag)
      {

         continue;

      }

      if (m_tickLastSaveWindowRect.elapsed() < 300)
      {

         continue;

      }

      try
      {

         m_bSizeMove = false;

         m_bPendingSaveWindowRect = false;

         if (WindowDataSaveWindowRect())
         {

            break;

         }

         m_bPendingSaveWindowRect = true;

      }
      catch (...)
      {

      }

   }

}


void simple_frame_window::assert_valid() const
{

   ::user::frame_window::assert_valid();

}


void simple_frame_window::dump(dump_context & dumpcontext) const
{

   ::user::frame_window::dump(dumpcontext);

}


__pointer(::user::interaction) simple_frame_window::WindowDataGetWnd()
{

   return this;

}


void simple_frame_window::_001OnDestroy(::message::message * pmessage)
{

   pmessage->previous();

   {

      sync_lock sl(mutex());

      try
      {

         if (m_pnotifyicon)
         {

            m_pnotifyicon->DestroyWindow();

            m_pnotifyicon.release();

         }

      }
      catch (...)
      {

      }

   }

}


::experience::frame * simple_frame_window::experience_get_frame()
{

   if(User.experience() == nullptr)
   {

      return nullptr;

   }

   if(Application.m_puiMain1 != nullptr)
   {

      __pointer(::simple_frame_window) pframe = Application.m_puiMain1;

      if(pframe.is_set())
      {

         auto pschemaRef = pframe->m_pframe;

         if(pschemaRef.is_set())
         {

            auto pframe = get_frame_experience(pschemaRef->m_strLibrary, pschemaRef->m_strName);

            if(::is_set(pframe))
            {

               if(GetExStyle() & WS_EX_TOOLWINDOW)
               {

                  //pschema->m_bHollow = false;

               }

               pframe->set_style(pschemaRef->m_strStyle);

               return pframe;

            }

         }

      }

   }

   auto pframe = get_frame_experience(m_varFrame["experience"], m_varFrame["schema"]);

   pframe->set_style(m_varFrame["style"]);

   return pframe;

}


//bool simple_frame_window::WfiOnBeforeUpDown()
//{
//
//
//
//
//}


bool simple_frame_window::initialize_frame_window_experience()
{

   if (m_pframe.is_set())
   {

      return true;

   }

   __pointer(::experience::frame) pexperienceframe;

   try
   {

      pexperienceframe = experience_get_frame();

   }
   catch (::exception::exception_pointer e)
   {

   }
   catch (...)
   {

      return false;

   }

   if (pexperienceframe == nullptr)
   {


      return false;

   }

   set_frame(pexperienceframe);

   if (!::experience::frame_window::initialize_frame_window_experience())
   {

      return false;

   }

#if defined(LINUX) || defined(APPLEOS)

   SetActiveFlag(TRUE);

#endif

   return true;

}


bool simple_frame_window::would_display_notify_icon()
{

#if defined(_UWP) || defined(ANDROID) || defined(APPLE_IOS)

   return false;

#else

   return m_bDefaultNotifyIcon;

#endif

}


void simple_frame_window::_001OnCreate(::message::message * pmessage)
{

   SCAST_PTR(::message::create, pcreate, pmessage);

   ::create * pcreateContext = (::create *) pcreate->m_lpcreatestruct->CREATE_STRUCT_P_CREATE_PARAMS;

   if (::is_set(pcreateContext))
   {

      auto pusercreate = pcreateContext->m_pusercreate;

      if (::is_set(pusercreate))
      {

         m_bAutoWindowFrame = __user_create(pusercreate)->m_bAutoWindowFrame;

         m_bWindowFrame = __user_create(pusercreate)->m_bWindowFrame;

      }

   }

   //auto pinteractionParent = GetParent();


   __pointer(::user::place_holder) pplaceholder = GetParent();

   if (pplaceholder != nullptr)
   {

      __pointer(::user::place_holder_container) pcontainer = pplaceholder->GetParent();

      if (pcontainer != nullptr)
      {

         pcontainer->on_place_hold(this, pplaceholder);

      }

   }

   if (m_bAutoWindowFrame)
   {

      if(Application.is_true("client_only"))
      {

         m_bWindowFrame = false;

      }
      else
      {

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

         m_bWindowFrame = false;

#else

         m_bWindowFrame = GetParent() == nullptr || wfi_is_up_down();

#endif

      }

   }

   if (m_bWindowFrame || m_bFramePayloadFlags)
   {

      if (!(m_ewindowflag & window_flag_window_created))
      {

//#if !defined(APPLE_IOS) && !defined(ANDROID)

         ::file::path pathFrameJson = "matter://" + m_pdocumenttemplate->m_strMatter + "/frame.json";

         if (m_pdocumenttemplate->m_strMatter.has_char())
         {

            m_varFrame = Context.file().as_json(pathFrameJson);

         }

//#endif

         if (m_varFrame["schema"].is_empty())
         {

            m_varFrame["schema"] = "005";

         }

         if (m_varFrame["style"].is_empty())
         {

            m_varFrame["style"] = "DarkWarmBlue";

         }

         if (m_bWindowFrame)
         {

            if (m_varFrame["control_box"]["transparent_button"]["visible"].is_set_false()
               || !m_bTransparentFrameEnable)
            {

               m_ebuttonaHide.add(::experience::button_transparent_frame);

            }

            if (m_varFrame["control_box"]["dock_button"]["visible"].is_set_false())
            {

               m_ebuttonaHide.add(::experience::button_dock);

            }

         }

      }

   }

   on_select_user_style();

   if (GetParent() == nullptr)
   {

      if (m_ebuttonaHide.contains(::experience::button_transparent_frame))
      {

         layout().remove_appearance(appearance_transparent_frame);

      }

   }

   if (m_bWindowFrame)
   {

      if (!initialize_frame_window_experience())
      {

         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

   }

   if (GetParent() == nullptr && m_strFrameTitle.is_empty())
   {

      m_strFrameTitle = Application.get_app_user_friendly_task_bar_name();

   }

   defer_set_icon();

   defer_synch_layered();

   if (!m_bShowTask)
   {

      m_pimpl->show_task(m_bShowTask);

   }

   string strAppTitle = Application.m_strAppTitle;

   if (strAppTitle.is_empty())
   {

      string_array stra;

      stra.explode("/", Application.m_strAppId);

      strAppTitle = stra.slice(1).implode(" ");

      strAppTitle.replace("_", " ");

      strAppTitle.replace("-", " ");

      strAppTitle.replace(".", " ");

   }

   if (!(m_ewindowflag & window_flag_window_created))
   {

      if (m_bDefaultNotifyIcon)
      {

         index iNotifyIconItem = 0;

         notify_icon_insert_item(iNotifyIconItem, strAppTitle, "notify_icon_topic");

         auto c = Application.applicationmenu().get_count();

         for (auto i = 0; i < c; i++)
         {
            auto& item = Application.applicationmenu()[i];

            notify_icon_insert_item(iNotifyIconItem, item.m_strName, item.m_strId);

         }

         if (m_pframe != nullptr
            && m_pframe->get_control_box() != nullptr
            && m_pframe->get_control_box()->has_button(::experience::button_transparent_frame))
         {

            notify_icon_insert_item(iNotifyIconItem, "separator");

            notify_icon_insert_item(iNotifyIconItem, _("Transparent Frame"), "transparent_frame");

         }

         notify_icon_insert_item(iNotifyIconItem, "separator");

         notify_icon_insert_item(iNotifyIconItem, _("Exit"), "app_exit");

         post_message(message_update_notify_icon);

      }

      create_bars();

   }

   if (pmessage->previous())
   {

      return;

   }

   set_window_text(get_frame_title());

}


void simple_frame_window::_on_show_window()
{

   ::experience::frame_window::_on_show_window();

   if (m_bFirstShow)
   {

      m_bFirstShow = false;

      if (GetActiveView())
      {

         GetActiveView()->post_message(message_simple_command, simple_command_defer_initialize_handled_views);

      }

   }

}


void simple_frame_window::_001OnShowWindow(::message::message * pmessage)
{

   SCAST_PTR(::message::show_window, pshow, pmessage);

   if(pshow->m_bShow)
   {

      output_debug_string("\nsimple_frame_window::_001OnShowWindow TRUE " + string(typeid(*this).name()));

      defer_set_icon();

   }
   else
   {

      output_debug_string("\nsimple_frame_window::_001OnShowWindow FALSE " + string(typeid(*this).name()));

   }

   if(would_display_notify_icon())
   {

      if(m_pnotifyicon != nullptr)
      {

         m_pnotifyicon->step();

      }

      OnUpdateToolWindow(pshow->m_bShow);

   }

}


void simple_frame_window::_001OnDisplayChange(::message::message * pmessage)
{

   SCAST_PTR(::message::base, pbase, pmessage);

   if (is_host_top_level())
   {

      ::edisplay edisplay = layout().sketch().display();

      display(edisplay, activation_display_change);

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }
   else
   {

      post_simple_command(simple_command_load_window_rect, (LPARAM)FALSE);

   }

   pmessage->m_bRet = true;

   pbase->m_lresult = 0;

}


void simple_frame_window::_001OnTaskbarCreated(::message::message * pmessage)
{

   defer_create_notification_icon();

}


void simple_frame_window::_001OnUpdateNotifyIcon(::message::message * pmessage)
{

   defer_create_notification_icon();

}


void simple_frame_window::_001OnSize(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   //m_tickLastVisualChange.Now();

   //if (GetParent() == nullptr)
   //{

   //   defer_save_window_placement();

   //}

}


void simple_frame_window::_001OnMove(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   m_tickLastVisualChange.Now();


}


bool simple_frame_window::on_create_client(::user::create_struct * pcs, ::create * pcreate)

{

   return ::user::frame_window::on_create_client(pcs, pcreate);


}


bool simple_frame_window::pre_create_window(::user::create_struct& cs)
{

   if (!::user::frame_window::pre_create_window(cs))
   {

      return false;

   }

   //cs.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
   //cs.style |= WS_OVERLAPPEDWINDOW;
   //cs.style |= WS_THICKFRAME;
   cs.style |= WS_POPUP;
   //cs.style &= ~WS_VISIBLE;
   cs.style |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

   ::create* pcreateContext = (::create*) cs.CREATE_STRUCT_P_CREATE_PARAMS;

   if(pcreateContext && would_display_notify_icon())
   {

      __pointer(::user::document) pdocument = __user_create(pcreateContext->m_pusercreate)->m_pdocumentCurrent;

      if (pdocument->get_document_template()->m_bHiddenOnNotifyIcon)
      {

         //display(::display_hide);

         //set_need_redraw();

         //post_redraw();

         pcreateContext->m_bMakeVisible = false;

         cs.style &= ~WS_VISIBLE;

      }

   }

   return true;

}


void simple_frame_window::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   if (string(type_name()).contains_ci("child_frame"))
   {

      output_debug_string("%child_frame%\n");

   }

   if (is_frame_experience_enabled())
   {

      ::experience::frame_window::on_layout(pgraphics);

   }
   else
   {

      ::user::frame_window::on_layout(pgraphics);

   }

   m_tickLastVisualChange.Now();


}


void simple_frame_window::on_reposition()
{

   //if (m_bWindowFrame)
   //{

   //   on_layout(::draw2d::graphics_pointer & pgraphics);

   //}

   ::user::frame_window::on_reposition();

   m_tickLastVisualChange.Now();


}


void simple_frame_window::ViewOnActivateFrame(__pointer(::user::impact) pview, UINT user, __pointer(::user::interaction) pframe)
{
   UNREFERENCED_PARAMETER(pview);
   UNREFERENCED_PARAMETER(user);
   UNREFERENCED_PARAMETER(pframe);
   //   if(pview != nullptr)
   //      pview->OnActivateFrame(WA_INACTIVE, (__pointer(::user::simple_frame_window)) pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(::message::message * pmessage)
{
#ifdef WINDOWS_DESKTOP
   SCAST_PTR(::message::base, pbase, pmessage);
   MINMAXINFO FAR * pMMI = (MINMAXINFO FAR*) pbase->m_lparam.m_lparam;

   if (layout().is_full_screen())
   {
      pMMI->ptMaxSize.y = m_FullScreenWindowRect.height();

      pMMI->ptMaxTrackSize.y = pMMI->ptMaxSize.y;

      pMMI->ptMaxSize.x = m_FullScreenWindowRect.width();

      pMMI->ptMaxTrackSize.x = pMMI->ptMaxSize.x;

   }
#else
   __throw(todo());
#endif
}


void simple_frame_window::ShowControlBars(bool bShow, bool bLeaveFullScreenBarsOnHide)
{

   UINT nShow;

   if (bShow)
   {

      nShow = display_normal;

   }
   else
   {

      nShow = display_none;

   }

   for(auto & pbar : m_toolbarmap.values())
   {

      try
      {

         if(pbar != nullptr && (bShow || (!pbar->m_bFullScreenBar || !bLeaveFullScreenBarsOnHide)))
         {

            pbar->display(nShow);

         }

      }
      catch (...)
      {

      }

   }

   set_need_layout();

}


void simple_frame_window::WfiOnFullScreen()
{

   ShowControlBars(false, true);

   sketch_prepare_window_full_screen();

}


//bool simple_frame_window::display(display_transparent_frame)
//{
//
//   if (m_ebuttonaHide.contains(::experience::button_transparent_frame))
//   {
//
//      m_eshow -= ::show_transparent_frame;
//
//      return false;
//
//   }
//
//   m_eshow.toggle(::show_transparent_frame);
//
//   set_need_layout();
//
//   set_need_redraw();
//
//   defer_save_window_placement();
//
//   return true;
//
//}


bool simple_frame_window::frame_is_transparent()
{
   
   if(!m_bTransparentFrameEnable)
   {
      
      return false;
      
   }
   
   auto eappearance = layout().design().appearance();

   if(eappearance & ::appearance_transparent_frame)
   {
      
      return true;
      
   }
   
   return false;

}


void simple_frame_window::_001OnExitFullScreen()
{

   ShowControlBars(true);

   ::experience::frame_window::_001OnExitFullScreen();

}


void simple_frame_window::_001OnViewFullScreen(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   ToggleFullScreen();

}


void simple_frame_window::_001OnMouseMove(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

}


void simple_frame_window::_001OnNcHitTest(::message::message * pmessage)
{

   SCAST_PTR(::message::base, pbase, pmessage);

   //int x = GET_X_LPARAM(pmessage->m_lparam.m_lparam);

   //int y = GET_Y_LPARAM(pmessage->m_lparam.m_lparam);

   pbase->m_lresult = HTCLIENT;

   pbase->m_bRet = true;

}


void simple_frame_window::_001OnMouseActivate(::message::message * pmessage)
{

   SCAST_PTR(::message::mouse_activate, pmouseactivate, pmessage);

   pmouseactivate->m_lresult = MA_ACTIVATE;

   pmouseactivate->m_bRet = true;

}


void simple_frame_window::_001OnUpdateViewFullScreen(::message::message * pmessage)
{
   SCAST_PTR(::user::command, pcommand, pmessage);
   pcommand->Enable();
   pcommand->_001SetCheck(layout().is_full_screen());
   pcommand->m_bRet = true;
}


void simple_frame_window::ToggleFullScreen()
{

   if (layout().is_full_screen())
   {

      display(display_normal);

   }
   else
   {

      display(display_full_screen);

   }

}


bool simple_frame_window::_001CanEnterScreenSaver()
{

   return true;

}




void simple_frame_window::_001OnToggleCustomFrame(::message::message * pmessage)
{
   UNREFERENCED_PARAMETER(pmessage);
   SetCustomFrame(!GetCustomFrame());
}

void simple_frame_window::_001OnUpdateToggleCustomFrame(::message::message * pmessage)
{
   SCAST_PTR(::user::command, pcommand, pmessage);
   pcommand->Enable();
   pcommand->_001SetCheck(m_bWindowFrame);
}


void simple_frame_window::_001OnToggleTransparentFrame(::message::message * pmessage)
{

   layout().toggle_appearance(appearance_transparent_frame);

   display();

   set_reposition();

   set_need_layout();

   set_need_redraw();

   post_redraw();

   pmessage->m_bRet = true;

}


void simple_frame_window::_001OnUpdateToggleTransparentFrame(::message::message * pmessage)
{

   SCAST_PTR(::user::command, pcommand, pmessage);

   pcommand->Enable();

   //if (GetTopLevelFrame()->frame_is_transparent())
   //{

   //   MessageBox(nullptr, "ft", "", MB_OK);

   //}
   //else
   //{

   //   MessageBox(nullptr, "fnt", "", MB_OK);

   //}

   pcommand->_001SetCheck(frame_is_transparent());

}


void simple_frame_window::ActivateFrame(edisplay edisplay)
{

   ::user::frame_window::ActivateFrame(edisplay);

}


void simple_frame_window::GetBorderRect(RECT * prect)

{
   *prect = m_rectBorder;

}

void simple_frame_window::SetBorderRect(const ::rect & rect)
{
   m_rectBorder = rect;
}


void simple_frame_window::SetCustomFrame(bool bCustom)
{

   m_bWindowFrame = bCustom;

   enable_frame_experience(bCustom);

   set_need_layout();

   set_need_redraw();

}


bool simple_frame_window::GetCustomFrame()
{

   return m_bWindowFrame;

}


::color simple_frame_window::get_border_main_body_color()
{

   if (!m_pframe)
   {

      return ::experience::frame_window::get_border_main_body_color();

   }

   return m_pframe->get_border_main_body_color();

}


void simple_frame_window::_001OnAppExit(::message::message * pmessage)
{

   if (GetParent() != nullptr)
   {

      pmessage->m_bRet = false;

      return;

   }

   Application.request({::command_france_exit});

   if (pmessage != nullptr)
   {

      pmessage->m_bRet = true;

   }


}


void simple_frame_window::_001OnClose(::message::message * pmessage)
{

   if (wfi_is_up_down())
   {

      string strView = m_id;

      bool bShow = false;

      if (::str::ends_eat_ci(strView, "::frame"))
      {

         Application.data_set("frame::" + strView + ".visible", bShow);

      }

      hide();

      set_need_redraw();

      post_redraw();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      return;

   }

   if ((bool)m_varFrame["hide_on_close"])
   {

      display(display_none);

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      return;

   }

   if(would_display_notify_icon())
   {

      if(pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

#ifdef LINUX
      //if(is_window_visible())
      if(::user::get_edesktop() == ::user::desktop_unity_gnome
            || ::user::get_edesktop() == ::user::desktop_ubuntu_gnome)
      {

         display(display_none);

      }
      else
      {

         display(display_iconic);

      }
#else

      if(is_window_visible())
      {

         hide();

         set_need_redraw();

         post_redraw();

      }

#endif // LINUX

      ModifyStyleEx(0, WS_EX_TOOLWINDOW);

      return;

   }

   if (m_bModal)
   {

      EndModalLoop(IDOK);

      pmessage->m_bRet = true;

      return;

   }
   else if (GetTopLevelFrame() != nullptr && GetTopLevelFrame()->m_bModal)
   {

      GetTopLevelFrame()->EndModalLoop(IDOK);

      pmessage->m_bRet = true;

      return;

   }

   if (::is_set(pmessage))
   {

      pmessage->m_bRet = true;

   }

   bool bHideWindow = false;

   {

      {

         // Note: only queries the active document
         ::user::document * pdocument = GetActiveDocument();

         if (pdocument != nullptr && !pdocument->can_close_frame(this))
         {

            // document can't close right now -- don't close it
            return;

         }

      }

      //::aura::application * papp = &Application;

      if (GetParent() != nullptr)
      {

         bHideWindow = true;

      }
      //else if (papp->is_system() || papp->is_session())
      //{

      //   // TODO: instead of closing all applications in process System.m_apptra, should close application that make part of
      //   // cube, bergedge, session or system.

      //   auto applicationa = System.get_applicationa();

      //   for (auto & papp : applicationa)
      //   {

      //      if (!App(papp.m_p)._001CloseApplicationByUser(this))
      //      {

      //         return;

      //      }

      //   }

      //}
      else if(Application.on_close_frame_window(this))
      {

         return;

      }
      else
      {

         bHideWindow = true;

      }

   }

   if(bHideWindow)
   {

      display(display_none);

   }

}


//#ifdef WINDOWS_DESKTOP
//
//void simple_frame_window::OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* pncsp)
//
//{
//   UNREFERENCED_PARAMETER(bCalcValidRects);
//   if(is_frame_experience_enabled() && m_pframe != nullptr)
//   {
//      OnNcCalcSize(&pncsp->rgrc[0]);
//
//   }
//   else
//   {
//      // trans      ::user::frame_window::OnNcCalcSize(bCalcValidRects, pncsp);
//
//   }
//
//}
//
//#endif

void simple_frame_window::_001OnActivateApp(::message::message * pmessage)
{

   SCAST_PTR(::message::base, pbase, pmessage);

   pbase->previous();

   //bool bActive = pbase->m_wparam != FALSE;

   if (GetParent() == nullptr && GetExStyle() & WS_EX_LAYERED)
   {

      //if (bActive)
      //{

      //   if (layout().is_iconic())
      //   {

      //      display(display_normal);

      //   }
      //   SetActiveWindow();
      //}

      pbase->m_bRet = true;

      pbase->m_lresult = 0;

   }
}



void simple_frame_window::_000OnMouseLeave(::message::message * pmessage)
{

   if (!layout().is_moving() && !layout().is_sizing() && !layout().is_docking())
   {

      ::experience::frame_window::_000OnMouseLeave(pmessage);

   }

}


void simple_frame_window::_001OnActivate(::message::message * pmessage)
{

   SCAST_PTR(::message::activate, pactivate, pmessage);

   pactivate->previous();

   int iActive = LOWORD(pactivate->m_wparam);

   if (iActive)
   {

      if (pactivate->m_bMinimized)
      {

      }
      else
      {

         display(display_default, activation_set_foreground);

         set_need_redraw();

         if (GetExStyle() & WS_EX_LAYERED)
         {

            if (iActive == WA_CLICKACTIVE)
            {

               //   if (bMinimized || layout().is_iconic())
               //   {

               //      display(display_normal);

               //   }
               //   else
               //   {

               //      display(display_iconic);

               //   }

               //}
               //else if (bMinimized)
               //{



               //   display(display_normal);


            }

            pactivate->m_bRet = true;

            pactivate->m_lresult = 0;

         }

      }

   }
   else
   {

      //if (GetExStyle() & WS_EX_LAYERED)
      //{

      //   if (pactivate->m_lparam == 0)
      //   {

      //      if (!layout().is_iconic())
      //      {

      //         display(display_iconic | display_no_activate);

      //      }

      //   }

      pactivate->m_bRet = true;

      pactivate->m_lresult = 0;


      //

//         if (!bMinimized && !layout().is_iconic())
//         {
//
////            display(display_iconic);
//
//         }


      //}

   }

}


bool simple_frame_window::LoadFrame(const char * pszMatter, u32 dwDefaultStyle, ::user::interaction * puiParent, ::create * pcreate)
{

   if (m_pdescriptor.is_null())
   {

      m_pdescriptor.create(this);

   }

   m_id = pcreate->m_id.to_string() + "::frame";

   UNREFERENCED_PARAMETER(puiParent);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   if (puiParent == nullptr)
   {

      puiParent = Application.get_request_parent_ui(this, pcreate);

   }

   dwDefaultStyle &= ~WS_VISIBLE;

   ::rect rectFrame;

   __pointer(::user::place_holder) pholder;

   if(puiParent != nullptr && (pholder = puiParent).is_set())
   {

      pholder->get_client_rect(rectFrame);

   }

   if(puiParent == nullptr)
   {

      m_bLayoutEnable = false;

      INFO("simple_frame_window::LoadFrame m_bLayoutEnable FALSE");

   }

   ::user::create_struct createstruct(0L, nullptr, m_strFrameTitle, dwDefaultStyle, rectFrame, pcreate);

   if (!pre_create_window(createstruct))
   {

      return false;

   }

   if(puiParent == nullptr || wfi_is_up_down())
   {

      if (wfi_is_up_down() && ::is_set(puiParent) && puiParent->m_bWfiUpDownTarget)
      {

         m_pupdowntarget = puiParent;

      }

      if(should_save_window_rect())
      {

         bool bForceRestore = false;

         bool bInitialFramePosition = true;

         m_pdescriptor->m_puserinteractionParent = puiParent;

         WindowDataLoadWindowRect(bForceRestore, bInitialFramePosition);

         rectFrame = layout().sketch().screen_rect();

         INFO("simple_frame_window::LoadFrame rectFrame (l=%d, t=%d) (w=%d, h=%d)", rectFrame.left, rectFrame.top, rectFrame.width(), rectFrame.height());
         INFO("simple_frame_window::LoadFrame edisplay=%s", __cstr(layout().sketch().display().eflag()));

         if (wfi_is_up_down())
         {

            if (m_eupdown == updown_up)
            {

               puiParent = nullptr;

            }
            else if (m_eupdown == updown_down)
            {

               __pointer(::user::document) pdocument = __user_create(pcreate->m_pusercreate)->m_pdocumentCurrent;

               //__pointer(::userex::impact_host) peximpacthost = puiParent;

               __pointer(::user::impact_host) pimpacthost;

          /*     if (peximpacthost)
               {

                  pimpacthost = peximpacthost->get_pane_tab_view();

               }*/

               if (pimpacthost.is_set())
               {

                  puiParent = pimpacthost->updown_target_get_place_holder(this, pdocument);

               }

            }

         }

      }

      if(is_host_top_level())
      {

         if(m_ewindowflag & window_flag_main_frame)
         {

            display(display_zoomed);

          //  Session.get_main_wkspace(rectFrame);

         }

      }

      rectFrame = layout().sketch().screen_rect();

      createstruct.set_rect(rectFrame);

      INFO("(2) simple_frame_window::LoadFrame rectFrame (l=%d, t=%d) (w=%d, h=%d)", rectFrame.left, rectFrame.top, rectFrame.width(), rectFrame.height());
      INFO("(2) simple_frame_window::LoadFrame edisplay=%s", __cstr(layout().sketch().display().eflag()));

      if (pcreate->m_bMakeVisible)
      {

         layout().sketch() = activation_set_foreground;

         dwDefaultStyle |= WS_VISIBLE;

      }
      else
      {

         set_need_layout();

         layout().sketch() = display_none;

         INFO("simple_frame_window::LoadFrame DISPLAY_NONE");

      }

      design_display();

   }

   if (puiParent != nullptr)
   {

      createstruct.style |= WS_CHILD;

   }

   m_bEnableSaveWindowRect2 = false;

   bool bLoadImplRect = m_ewindowflag & window_flag_load_window_rect_on_impl;

   m_ewindowflag -= window_flag_load_window_rect_on_impl;

   bool bCreated = create_window_ex(createstruct, puiParent, m_id);

   if (bLoadImplRect)
   {

      m_ewindowflag += window_flag_load_window_rect_on_impl;

   }

   if (!bCreated)
   {

      return false;   // will self destruct on failure normally

   }

   if (pcreate == nullptr)   // send initial update
   {

      send_message_to_descendants(message_update, INITIAL_UPDATE, (LPARAM)0, TRUE, TRUE);

   }

   return true;

}


void simple_frame_window::_001OnDdeInitiate(::message::message * pmessage)
{

   //SCAST_PTR(::message::base, pbase, pmessage);

   //pbase->set_lresult(default_window_procedure((u32)pbase->m_wparam, pbase->m_lparam, pbase->get_lresult()));

}


void simple_frame_window::_001OnKey(::message::message * pmessage)
{


}


void simple_frame_window::pre_translate_message(::message::message * pmessage)
{

   if(pmessage->m_id == message_display_change)
   {

      display();

   }
   else if (pmessage->m_id == WM_MOUSEMOVE)
   {

   }

   return ::experience::frame_window::pre_translate_message(pmessage);

}


void simple_frame_window::on_frame_position()
{

   display(display_default, activation_set_active);

   order_top();

   if (is_frame_experience_enabled())
   {

      if (layout().design().display() == ::display_iconic)
      {

         display(display_normal);

      }

   }

   if (m_palphasource != nullptr)
   {

      m_palphasource->on_alpha_target_initial_frame_position();

   }

   set_need_redraw();

   post_redraw();

}


void simple_frame_window::InitialFramePosition(bool bForceRestore)
{

   try
   {

      if(m_bFrameMoveEnable)
      {

         bool bHostTopLevel = is_host_top_level();

         if(Application.has_property("wfi_maximize") && is_top_level_window())
         {

            display(display_zoomed);

         }
         else if(bHostTopLevel
            || Application.has_property("client_only")
            || Application.has_property("full_screen"))
         {

            if(is_frame_experience_enabled())
            {

               display(display_full_screen);

            }
            else
            {

               //best_monitor(nullptr,nullptr,true);

               display(display_zoomed);

            }

         }
         else
         {

            m_bInitialFramePosition = true;

            WindowDataLoadWindowRect(bForceRestore,true);

         }

      }

      m_bInitialFramePosition = true;

      get_context_application()->on_initial_frame_position(this);

      //on_frame_position();

   }
   catch(...)
   {

   }

   m_bLayoutEnable = true;

   //set_need_redraw();

   output_debug_string("\nm_bLayoutEnable TRUE");

   if (GetParent() == nullptr || is_host_top_level())
   {

      set_need_layout();

      set_need_redraw();

      set_layout_ready();

      post_redraw();

      output_debug_string("\nframe_window::POST_READRAW\n");

   }

}




void simple_frame_window::on_after_graphical_update()
{

   ::user::frame_window::on_after_graphical_update();

   if (m_bInitialFramePosition)
   {

      m_bInitialFramePosition = false;

      m_bEnableSaveWindowRect2 = true;

   }

}


void simple_frame_window::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
{

   if(get_context_application() == nullptr
         || get_context_application()->get_context_session() == nullptr
         || Session.m_psavings == nullptr)
   {

      return;

   }


   if (Session.savings().is_trying_to_save(::e_resource_processing)
         || Session.savings().is_trying_to_save(::e_resource_translucent_background))
   {

      ::rect rectClient;

      get_client_rect(rectClient);

      pgraphics->fill_rect(rectClient, RGB(0, 0, 0));

   }
   else
   {

      ::user::frame_window::_001OnDeferPaintLayeredWindowBackground(pgraphics);

   }

}


void simple_frame_window::_000OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
{

   if (!is_frame_experience_enabled())
   {

      ::user::frame_window::_000OnDraw(pgraphicsParam);

      return;

   }

   {

      sync_lock sl(mutex());

      if (m_pimpl->m_puserinteraction == nullptr)
      {

         return;

      }

      if (!_000OnBeforeDraw(pgraphicsParam))
      {

         return;

      }

   }

   auto pstyle = get_style(pgraphicsParam);

   windowing_output_debug_string("\nsimple_frame_window::_001OnDraw B");

   ::rect rectClient;

   get_window_rect(rectClient);

   rectClient -= rectClient.top_left();

   bool bDib = false;

   double dAlpha = get_alpha();

   ::draw2d::graphics_pointer & pgraphics = pgraphicsParam;

   if(dAlpha == 0.0)
   {

      windowing_output_debug_string("Alpha is Zero\n");

   }

   if(rectClient.area() > 0 && dAlpha > 0.0 && dAlpha < 1.0 && GetExStyle() & WS_EX_LAYERED)
   {

      auto estatus = __defer_construct(m_pimageAlpha);

      if (estatus)
      {

         estatus = m_pimageAlpha->create(rectClient.size());

         if (estatus)
         {

            m_pimageAlpha->fill(0, 0, 0, 0);

            pgraphics = m_pimageAlpha->get_graphics();

            pgraphics->SetViewportOrg(pgraphics->GetViewportOrg());

            bDib = true;

         }

      }

   }

   //::user::style_context style(this);

   {

      tick t1 = tick::now();

      //pinteraction->_001OnDraw(pgraphics);
      if(dAlpha > 0.0)
      {

         bool bBlurBackground = get_draw_flags(pstyle) & ::user::flag_blur_background;

         int iDrawingOrder = DRAWING_ORDER_CLIENT_OVER;

         if (!bBlurBackground)
         {

            iDrawingOrder = get_int(pstyle, ::user::int_top_level_drawing_order);

            if(pstyle)
            {

               pstyle->_001OnDrawMainFrameBackground(pgraphics, this);

               //if (pstyle->_001OnDrawMainFrameBackground(pgraphics, this))
               //{

               //   break;

               //}

               //style.next();

            }

         }

#if TEST

         pgraphics->fill_solid_rect_dim(0, 0, 100, 100, ARGB(128, 255, 0, 0));

#endif

         tick d1 = t1.elapsed();

         string strType = type_name();

         if(d1 > 50)
         {

            CINFO(prodevian)("(more than 50ms) "+strType+"::_001OnDraw took " + __str(d1) + "millis.\n");

         }

         if (iDrawingOrder == DRAWING_ORDER_CLIENT_OVER)
         {

            _001DrawThis(pgraphics);

            _001DrawChildren(pgraphics);

         }
         else
         {

            tick t1 = tick::now();

            draw_frame_and_control_box_over(pgraphics);

            tick d1 = t1.elapsed();

            if(d1 > 50)
            {

               CINFO(prodevian)("(more than 50ms) draw_frame_and_control_box_over took " + __str(d1) + "millis.\n");

            }

         }

      }

      _008CallOnDraw(pgraphics);

#if TEST

      pgraphics->fill_solid_rect_dim(0, 100, 100, 100, ARGB(128, 0, 0, 255));

#endif

   }

   if(bDib)
   {

      pgraphicsParam->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphicsParam->alpha_blend(nullptr,rectClient.size(),pgraphics,nullptr,dAlpha);

   }

}


void simple_frame_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   // glxxx

   //return;

   auto pstyle = get_style(pgraphics);

   bool bBlurBackground = get_draw_flags(pstyle) & ::user::flag_blur_background;

   if(bBlurBackground)
   {

      //printf("simplefrmwnd : " + string(type_name()) + " : blur_background");

      class imaging & imaging = System.imaging();

      ::rect rectClient;

      get_client_rect(rectClient);

      //rectClient.offset(rectClient.top_left());

      if(Session.savings().is_trying_to_save(::e_resource_translucent_background))
      {

         //pgraphics->fill_rect(rectClient, RGB(150, 220, 140));

      }
      else if(Session.savings().is_trying_to_save(::e_resource_processing)
              || Session.savings().is_trying_to_save(::e_resource_blur_background))
      {

         imaging.color_blend(pgraphics,rectClient,RGB(150,180,140),150);

      }
      else
      {

#ifndef LINUX

         //printf("simplefrmwnd : " + string(type_name()) + " : ifndef LINUX");

         if(rectClient.size() != m_pimageBk->size())
         {
            m_pimageBk->create(rectClient.size());
            m_pimageBk->fill(0,200,200,190);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::draw2d::fastblur *( *pfnNew )(__pointer(::aura::application)) = (::draw2d::fastblur *(*)(__pointer(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");
            //m_pimageBlur->create(this);
            //m_fastblur.initialize(rectClient.size(),2);

            m_pimageBlur->create(rectClient.size());

         }

         if(m_pimageBlur->is_ok())
         {

            m_pimageBlur->g()->BitBlt(0,0,rectClient.width(),rectClient.height(),pgraphics,0,0,SRCCOPY);
            m_blur.blur(m_pimageBlur, 2);
            imaging.bitmap_blend(
            m_pimageBlur->g(),
            nullptr,
            rectClient.size(),
            m_pimageBk->g(),
            nullptr,
            49);
            pgraphics->from(rectClient.size(),
                            m_pimageBlur->g(),
                            nullptr,
                            SRCCOPY);

         }

#endif

      }

   }

   //printf("simplefrmwnd : " + string(type_name()) + " : draw_frame");

   draw_frame(pgraphics);


}


bool simple_frame_window::on_before_set_parent(__pointer(::user::interaction) pinteraction)
{

   WindowDataSaveWindowRect();

   if (!::user::box::on_before_set_parent(pinteraction))
   {

      return false;

   }

   return true;

}


bool simple_frame_window::on_set_parent(::user::interaction * puiParent)
{

   if (!::user::frame_window::on_set_parent(puiParent))
   {

      return false;

   }

   return true;

}


void simple_frame_window::on_after_set_parent()
{

   auto puiParent = GetParent();


   if (puiParent == nullptr)
   {

      if (m_bLayered)
      {

         ModifyStyleEx(0, WS_EX_LAYERED);

      }

   }

   set_reposition();

   set_need_layout();

   set_need_redraw();

}


bool simple_frame_window::get_client_rect(RECT * prect)
{

   if (m_bWindowFrame && m_pframe != nullptr && !layout().is_full_screen() && !frame_is_transparent())
   {

      return m_pframe->get_window_client_rect(prect);

   }
   else
   {

      ::user::interaction::get_client_rect(prect);

   }

   return true;

}


bool simple_frame_window::is_application_main_window()
{

   return Application.m_puiMain1 == this;

}


bool simple_frame_window::LoadToolBar(::type type, id idToolBar, const char * pszToolBar, u32 dwCtrlStyle, u32 uStyle)
{

   __composite(::user::toolbar) & ptoolbar = m_toolbarmap[idToolBar];

   if(!ptoolbar)
   {

      auto estatus = __id_compose(ptoolbar, type);

      if(!estatus)
      {

         return false;

      }

      if (ptoolbar == nullptr)
      {

         return false;

      }

      if (!ptoolbar->create_toolbar(this, dwCtrlStyle, uStyle))
      {

         return false;

      }

   }

   if (ptoolbar.is_null())
   {

      return false;

   }

   string strMatter = Context.dir().matter(pszToolBar);

   if (ptoolbar->value("matter_annotation") == strMatter)
   {

      return true;

   }

   string strXml = Context.file().as_string(strMatter);

   if(!ptoolbar->LoadXmlToolBar(strXml))
   {

      return false;

   }

   m_toolbarmap.set_at(idToolBar,ptoolbar);

   AddControlBar(ptoolbar);

   ptoolbar->set_need_layout();

   ptoolbar->value("matter_annotation") = strMatter;

   set_need_layout();

   return true;

}


void simple_frame_window::defer_create_notification_icon()
{

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   if (m_pnotifyicon)
   {

      m_pnotifyicon->DestroyWindow();

   }

   if (m_piconNotify.is_null())
   {

      auto estatus = __construct_new(m_piconNotify);

      if(estatus)
      {

         const char * pszAppName = Application.m_strAppName;

         m_piconNotify->load_app_tray_icon(pszAppName);

      }

   }

   __construct_new(m_pnotifyicon);

   if (!m_pnotifyicon->create_notify_icon(1, this, m_piconNotify))
   {

      m_pnotifyicon.release();

      return;

   }

   m_setMinimizeToTray.defer(set_true);

}


// persistent frame implemenation using updowntarget
bool simple_frame_window::updown_get_up_enable()
{

   return m_pupdowntarget != nullptr && wfi_is_up_down() && wfi_is_down();

}


bool simple_frame_window::updown_get_down_enable()
{

   return m_pupdowntarget != nullptr && wfi_is_up_down() && wfi_is_up();

}


void simple_frame_window::design_down()
{

   m_eupdown = updown_down;

   if (m_pframe)
   {

      m_pframe->get_control_box()->set_need_layout();

   }

   __keep_on(&m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

   frame_Attach();

}


void simple_frame_window::WfiToggleShow()
{

   if (is_window_visible())
   {

      hide();

   }
   else
   {

      WindowDataLoadWindowRect();

   }

   set_need_redraw();

   post_redraw();

}


//void simple_frame_window::WfiOnAfterDown()
//{
//
//   data_set("wfi_down", true);
//
//}


//void simple_frame_window::WfiOnAfterUp()
//{
//
//   data_set("wfi_down", false);
//
//}


void simple_frame_window::design_up()
{

   m_eupdown = updown_up;

   if (m_pframe)
   {

      m_pframe->get_control_box()->set_need_layout();

   }

   __keep_on(&m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

   frame_Detach();

   if (m_pupdowntarget->m_uiUserInteractionFlags & ::user::interaction_wfi_up_tool_window)
   {

      ModifyStyle(0, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);

   }

}





bool simple_frame_window::create_window(const char * pszClassName, const char * pszWindowName, u32 uStyle, const ::rect & rect, ::user::interaction * puiParent, const char * pszMenuName, u32 dwExStyle, ::create * pcreate)
{

   return ::user::frame_window::create_window(pszClassName, pszWindowName, uStyle, rect, puiParent, pszMenuName, dwExStyle, pcreate);

}


void simple_frame_window::route_command_message(::user::command * pcommand)
{

   ::experience::frame_window::route_command_message(pcommand);

}


#ifdef WINDOWS_DESKTOP



void simple_frame_window::OnDropFiles(HDROP hDropInfo)
{

   SetActiveWindow();      // activate us first !
   UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, nullptr, 0);

   ::file::patha patha;

   natural_wstring pwszFileName(char_count, _MAX_PATH);

   for (UINT iFile = 0; iFile < nFiles; iFile++)
   {

      if (::DragQueryFileW(hDropInfo, iFile, pwszFileName, _MAX_PATH))
      {

         patha.add(__str(pwszFileName));

      }

   }

   ::DragFinish(hDropInfo);

   User.on_frame_window_drop_files(this, patha);

}


// query end session for main frame will attempt to close it all down
bool simple_frame_window::OnQueryEndSession()
{

   ::aura::application* pApp = &Application;

   if (pApp != nullptr && pApp->m_puiMain1 == this)
   {

      return App(pApp).save_all_modified();

   }

   return true;

}


void simple_frame_window::OnEndSession(bool bEnding)
{

   if(!bEnding)
      return;

   Application.close(::apex::e_end_system);

}


#else

//void simple_frame_window::OnDropFiles(HDROP hDropInfo)
//{
//
//   UNREFERENCED_PARAMETER(hDropInfo);
//
//}
//


#endif






LRESULT simple_frame_window::OnDDEInitiate(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWS_DESKTOP

   ::aura::application* pApp = &Application;
   if (pApp != nullptr &&
         LOWORD(lParam) != 0 && HIWORD(lParam) != 0 &&
         (ATOM)LOWORD(lParam) == pApp->m_atomApp &&
         (ATOM)HIWORD(lParam) == pApp->m_atomSystemTopic)
   {
      // make duplicates of the incoming atoms (really adding a context_object)
      wchar_t szAtomName[_MAX_PATH];
      GlobalGetAtomNameW(pApp->m_atomApp, szAtomName, _MAX_PATH - 1);
      GlobalAddAtomW(szAtomName);
      GlobalGetAtomNameW(pApp->m_atomSystemTopic, szAtomName, _MAX_PATH - 1);
      GlobalAddAtomW(szAtomName);

      // send the WM_DDE_ACK (caller will delete duplicate atoms)
      ::SendMessageW((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
                    MAKELPARAM(pApp->m_atomApp, pApp->m_atomSystemTopic));
   }

#else

   ::exception::throw_not_implemented();

#endif

   return 0L;
}


// always ACK the execute command - even if we do nothing
LRESULT simple_frame_window::OnDDEExecute(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWS_DESKTOP

   // unpack the DDE message
   uptr unused;
   HGLOBAL hData;
   //IA64: Assume DDE LPARAMs are still 32-bit
   VERIFY(UnpackDDElParam(WM_DDE_EXECUTE, lParam, &unused, (uptr*)&hData));

   // get the command string
   const char * psz = (const char *)GlobalLock(hData);

   wstring strCommand;
   try
   {
      strCommand = psz;

      GlobalUnlock(hData);
   }
   catch (memory_exception * pe)
   {
      GlobalUnlock(hData);
      ::exception_pointer esp(pe);
   }


   // acknowledge now - before attempting to execute
   ::PostMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
                 //IA64: Assume DDE LPARAMs are still 32-bit
                 ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
                                (UINT)0x8000, (uptr)hData));

   // don't execute the command when the ui is disabled
   if (!is_window_enabled())
   {
      TRACE(trace_category_appmsg, trace_level_warning, "Warning: DDE command '%s' ignored because ui is disabled.\n",
            string(strCommand).c_str());
      return 0;
   }

   // execute the command
   //LPWSTR pszCommand = strCommand.alloc(strCommand.get_length());

   //if (!System.OnDDECommand(pszCommand))

   //   TRACE(trace_category_appmsg, trace_level_warning, "Error: failed to execute DDE command '%s'.\n", pszCommand);

   //strCommand.release_string_buffer();

#else

   ::exception::throw_not_implemented();

#endif

   return 0L;

}

LRESULT simple_frame_window::OnDDETerminate(WPARAM wParam, LPARAM lParam)
{

#ifdef WINDOWS_DESKTOP

   ::PostMessage((oswindow)wParam, WM_DDE_TERMINATE, (WPARAM)get_handle(), lParam);

#else

   ::exception::throw_not_implemented();

#endif

   return 0L;

}


void simple_frame_window::NotifyFloatingWindows(u32 dwFlags)
{
   ASSERT_VALID(this);
   // trans   ASSERT(get_handle() != nullptr);

   // get top level parent frame ui first unless this is a child ui
   __pointer(::user::frame_window) pParent = (GetStyle() & WS_CHILD) ? this : GetTopLevelFrame();
   ASSERT(pParent != nullptr);
   //if (dwFlags & (FS_DEACTIVATE | FS_ACTIVATE))
   //{
   //   // update parent ui activation state
   //   bool bActivate = !(dwFlags & FS_DEACTIVATE);
   //   bool bEnabled = pParent->is_window_enabled();

   //   if (bActivate && bEnabled && pParent != this)
   //   {
   //      // Excel will try to Activate itself when it receives a
   //      // WM_NCACTIVATE so we need to keep it from doing that here.
   //      //m_nFlags |= WF_KEEPMINIACTIVE;
   //      pParent->send_message(WM_NCACTIVATE, TRUE);
   //      //m_nFlags &= ~WF_KEEPMINIACTIVE;
   //   }
   //   else
   //   {
   //      pParent->send_message(WM_NCACTIVATE, FALSE);
   //   }
   //}

   // then update the state of all floating windows owned by the parent
#ifdef WINDOWS_DESKTOP

   __pointer(::user::interaction) oswindowDesktop = Application.get_desktop_window();

   if (oswindowDesktop.is_null())
      return;

   __pointer(::user::interaction) oswindow = oswindowDesktop->get_wnd(GW_CHILD);

   while (oswindow != nullptr)
   {

      if (::user::is_descendant(pParent, oswindow))
         oswindow->send_message(WM_FLOATSTATUS, dwFlags);

      oswindow = oswindow->get_wnd(GW_HWNDNEXT);

   }

#else
   __throw(todo());
#endif
}



// query end session for main frame will attempt to close it all down
void simple_frame_window::_001OnQueryEndSession(::message::message * pmessage)
{

   SCAST_PTR(::message::base, pbase, pmessage);

   if (::is_set_ref(Application) && Application.m_puiMain1 == this)
   {

      pbase->m_lresult = Application.save_all_modified();

      pbase->m_bRet = true;

      return;

   }

   pbase->m_lresult = TRUE;

   return;

}


void simple_frame_window::on_control_event(::user::control_event * pevent)
{

   ::experience::frame_window::on_control_event(pevent);

   if(pevent->m_bRet)
   {

      return;

   }

   return ::user::frame_window::on_control_event(pevent);

}


string simple_frame_window::get_window_default_matter()
{

   if (m_pdocumenttemplate == nullptr)
   {

      return frame_window::get_window_default_matter();

   }

   return m_pdocumenttemplate->m_strMatter;

}


//void simple_frame_window::guserbaseOnInitialUpdate(::message::message * pmessage)
//{
//   SCAST_PTR(::message::base, pbase, pmessage);
//   ::user::FrameInitialUpdate * pfiu = (::user::FrameInitialUpdate *)pbase->m_lparam.m_lparam;
//   if (pfiu != nullptr)
//   {
//      __pointer(::user::frame_window) pframe = (this);
//      // if the frame does not have an active ::user::impact, set to first pane
//      __pointer(::user::impact) pview;
//      if (pframe->GetActiveView() == nullptr)
//      {
//         __pointer(::user::interaction) pwindow = pframe->get_child_by_id("pane_first");
//         if (pwindow != nullptr && base_class < ::user::impact >::bases(pwindow))
//         {
//            pview = (pwindow.m_p);
//            pframe->SetActiveView(pview, FALSE);
//         }
//      }
//
//      if (pfiu->m_bMakeVisible)
//      {
//         // send initial update to all views (and other controls) in the frame
//         pframe->send_message_to_descendants(WM_INITIALUPDATE, 0, (LPARAM)0, TRUE, TRUE);
//
//         // give ::user::impact a chance to save the focus (CFormView needs this)
//         if (pview != nullptr)
//            pview->OnActivateFrame(WA_INACTIVE, pframe);
//
//         // finally, activate the frame
//         // (send the default show command unless the main desktop ui)
//         edisplay edisplay = display_default;      // default
//         ::aura::application* pApp = &System;
//         if (pApp != nullptr && pApp->m_puiMain == pframe)
//         {
//            edisplay = System.m_edisplay; // use the parameter from WinMain
//            System.m_edisplay = display_undefined; // set to default after first time
//         }
//         bool bFullScreen;
//         data_get("FullScreen", bFullScreen);
//         if (bFullScreen)
//         {
//            display(display_full_screen);
//         }
//         else
//         {
//            pframe->ActivateFrame(edisplay);
//         }
//         if (pview != nullptr)
//            pview->OnActivateView(TRUE, pview, pview);
//
//      }
//
//      __pointer(::user::document) pdocument = pfiu->m_pdocument;
//      // update frame counts and frame title (may already have been visible)
//      if (pdocument != nullptr)
//         pdocument->update_frame_counts();
//      pframe->on_update_frame_title(TRUE);
//
//      set_need_redraw();
//   }
//   pbase->set_lresult(0);
//}


void simple_frame_window::_001OnClip(::draw2d::graphics_pointer & pgraphics)
{

   ::user::interaction::_001OnClip(pgraphics);

}


void simple_frame_window::draw_frame_and_control_box_over(::draw2d::graphics_pointer & pgraphics)
{

   if (!is_this_visible())
   {

      return;

   }

   ::user::interaction_array uia;

   {

      sync_lock sl(mutex());

      uia = m_uiptraChild;

   }

   {

      ::draw2d::savedc k(pgraphics);

      //on_viewport_offset(pgraphics);
      //if (0)
      {
         try
         {

            for (auto & pinteraction : uia.interactiona())
            {

               auto pcontrolbox = pinteraction->cast < ::experience::control_box >();

               if (!pcontrolbox)
               {

                  {

                     tick t1 = tick::now();

                     pinteraction->_000CallOnDraw(pgraphics);

                     tick d1 = t1.elapsed();

                     if(d1 > 50)
                     {

                        string strType = pinteraction->type_name();

                        //if(strType.contains("pane_view"))
                        //{

                          // output_debug_string("paneview\n");

                        //}

                        CINFO(prodevian)("(more than 50ms) " + strType + "::_001OnDraw took " + __str(d1) + "millis.\n");

                     }

                  }

               }

            }

         }
         catch (...)
         {

         }

      }

   }

   {

      tick t1 = tick::now();

      _001DrawThis(pgraphics);

      tick d1 = t1.elapsed();

      if(d1 > 50)
      {

         CINFO(prodevian)("(more than 50ms) simple_frame_windows::_001DrawThis took " + __str(d1) + "millis.\n");

      }

   }

   tick tx = tick::now();

   bool bTransparentFrame = frame_is_transparent();

   bool bActive = is_active();

   tick taxw = tick::now();

   tick daxw = taxw.elapsed();

   if(daxw > 50)
   {

      output_debug_string("what???axxw\n");

   }

   tick txx = tick::now();

   if (m_bWindowFrame && (!bTransparentFrame || bActive))
   {

      ::draw2d::savedc k(pgraphics);

      //on_viewport_offset(pgraphics);

      try
      {

         for (auto & pinteraction : uia.interactiona())
         {

            if (base_class < ::experience::control_box > ::bases(pinteraction))
            {

               string str;

               pinteraction->get_window_text(str);

               if (str == "r")
               {

                  //TRACE0("x button");

               }

               //if (pinteraction->is_this_visible())
               {

                  if (str == "r")
                  {

                     //TRACE0("x button visible");

                  }

                  {

                     tick t1 = tick::now();

                     pinteraction->_000CallOnDraw(pgraphics);

                     tick d1 = t1.elapsed();

                     if(d1 > 50)
                     {

                        CINFO(prodevian)("(more than 50ms) simple_frame_windows::_001DrawThis took " + __str(d1) + ".\n");

                     }

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

   }

   auto dxx = txx.elapsed();
   if(dxx > 50)
   {

      output_debug_string("what???xx");

   }

   auto dx = tx.elapsed();
   if(dx > 50)
   {

      output_debug_string("what???");

   }

   {

      tick t1 = tick::now();

      _008CallOnDraw(pgraphics);

      tick d1 = t1.elapsed();

      if(d1 > 50)
      {

         CINFO(prodevian)("(more than 50ms) simple_frame_windows::_001DrawThis took " + __str(d1) + ".\n");

      }

   }

   //pgraphics->fill_solid_rect_dim(200, 200, 1600, 800, ARGB(128, 200, 240, 150));

}


void simple_frame_window::draw_frame(::draw2d::graphics_pointer & pgraphics)
{

   if (m_bWindowFrame && !Session.savings().is_trying_to_save(::e_resource_display_bandwidth))
   {

      ::experience::frame_window::_001OnDraw(pgraphics);

   }

}





//void simple_frame_window::WfiOnClose()
//{
//
//   post_message(WM_CLOSE);
//
//}
//

//void simple_frame_window::WfiOnMaximize()
//{
//
//   if (m_bFullScreenOnMaximize)
//   {
//
//      display(display_full_screen);
//
//   }
//   else
//   {
//
//      _001WindowMaximize();
//
//   }
//
//}


//void simple_frame_window::WfiOnMinimize(bool bNoActivate)
//{
//
//   _001WindowMinimize(bNoActivate);
//
//}


//void simple_frame_window::WfiOnRestore()
//{
//
//   _001WindowRestore();
//
//}


//void simple_frame_window::WfiOnDock(edisplay edisplay)
//{
//
//   _001WindowDock(edisplay);
//
//}


//bool simple_frame_window::DeferFullScreen(bool bFullScreen, bool bRestore)
//{
//   if (bFullScreen)
//   {
//      __pointer(::user::interaction) pwndParentFrame = GetParentFrame();
//      if (pwndParentFrame == nullptr)
//      {
//         if (!layout().is_full_screen())
//         {
//            display(display_full_screen);
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
//      if (pframe == nullptr)
//      {
//         if (!layout().is_full_screen())
//         {
//            display(display_full_screen);
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//
//      if (pframe->DeferFullScreen(bFullScreen, bRestore))
//         return true;
//
//      if (!layout().is_full_screen())
//      {
//         display(display_full_screen);
//         return true;
//      }
//      else
//      {
//         return false;
//      }
//   }
//   else
//   {
//      if (layout().is_full_screen())
//      {
//         display(display_normal);
//         return true;
//      }
//      __pointer(::user::interaction) pwndParentFrame = GetParentFrame();
//      if (pwndParentFrame == nullptr)
//      {
//         return false;
//      }
//      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
//      if (pframe == nullptr)
//      {
//         return false;
//      }
//      return pframe->DeferFullScreen(bFullScreen, bRestore);
//   }
//}


bool simple_frame_window::calc_layered()
{

   ::draw2d::graphics_pointer pgraphics = ::draw2d::create_memory_graphics();

   auto pstyle = get_style(pgraphics);

   if (m_bLayered && get_translucency(pstyle) != ::user::translucency_none)
   {
      return !Session.savings().is_trying_to_save(::e_resource_processing)
             && !Session.savings().is_trying_to_save(::e_resource_display_bandwidth);
   }
   else
   {

      return false;

   }

}


void simple_frame_window::data_on_after_change(::message::message * pmessage)
{

   //box::data_on_after_change(pmessage);

   SCAST_PTR(database::change_event, pupdate, pmessage);

   if (pupdate->m_datakey == "ca2.savings")
   {

      defer_synch_layered();

   }

}




void simple_frame_window::on_simple_command(::message::simple_command * psimplecommand)
{

   ::user::frame_window::on_simple_command(psimplecommand);

}


class ::mini_dock_frame_window* simple_frame_window::CreateFloatingFrame(u32 uStyle)
{

   UNREFERENCED_PARAMETER(uStyle);

   return nullptr;

}


















//bool simple_frame_window::display(edisplay edisplay)
//{
//
//   bool bOk1 = ::user::frame_window::display(edisplay);
//
//   if (edisplay == ::display_up)
//   {
//
//      m_eupdown = updown_up;
//
//   }
//   else if (edisplay == ::display_down)
//   {
//
//      m_eupdown = updown_down;
//
//   }
//
//   //display(edisplay);
//
//   if(edisplay == ::display_full_screen)
//   {
//
//      WfiOnAfterFullScreen();
//
//   }
//
//   return bOk1;
//
//}


bool simple_frame_window::keyboard_focus_is_focusable()
{

   return false;

}

bool simple_frame_window::create_bars()
{

   if (!on_create_bars())
   {

      return false;

   }

   //set_need_layout();

   return true;

}


bool simple_frame_window::on_create_bars()
{

   if(!m_bDefaultCreateToolbar)
   {

      return true;

   }

   __pointer(::user::document) pdocument = GetActiveDocument();

   if (pdocument.is_null())
   {

      __pointer(::user::interaction) pinteraction = get_child_by_id("pane_first");

      __pointer(::user::impact) pview = pinteraction;

      if (pview.is_set())
      {

         pdocument = pview->get_document();

      }

   }

   if (pdocument.is_set())
   {

      pdocument->on_create_bars(this);

   }

   return true;

}


void simple_frame_window::InitialUpdateFrame(::user::document * pDoc,bool bMakeVisible)
{

   ::user::frame_window::InitialUpdateFrame(pDoc,bMakeVisible);

}


void simple_frame_window::_001OnTimer(::timer * ptimer)
{

   ::user::frame_window::_001OnTimer(ptimer);

   ::experience::frame_window::_001OnTimer(ptimer);

}


void simple_frame_window::OnNotifyIconContextMenu(UINT uiNotifyIcon)
{

   auto point = Session.get_cursor_pos();

   string strXml = notification_area_get_xml_menu();

   User.track_popup_xml_menu(this, strXml, 0, point);

}


void simple_frame_window::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
{

   UNREFERENCED_PARAMETER(uiNotifyIcon);

}


void simple_frame_window::OnNotifyIconLButtonDown(UINT uiNotifyIcon)
{

   default_notify_icon_topic();

   UNREFERENCED_PARAMETER(uiNotifyIcon);

}


void simple_frame_window::_001OnNotifyIconTopic(::message::message * pmessage)
{

   if(m_bDefaultNotifyIcon)
   {

      default_notify_icon_topic();

   }

   pmessage->m_bRet = true;

}


void simple_frame_window::default_notify_icon_topic()
{

   toggle_restore();

}


void simple_frame_window::OnInitialFrameUpdate(bool bMakeVisible)
{

   if(!m_bDefaultNotifyIcon)
   {

      ::user::frame_window::OnInitialFrameUpdate(bMakeVisible);

      return;

   }

   if(bMakeVisible)
   {

      //OnUpdateToolWindow(bMakeVisible);

      InitialFramePosition();

   }

}


void simple_frame_window::OnUpdateToolWindow(bool bVisible)
{

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   if (m_pimpl == nullptr)
   {

      return;

   }

#ifdef LINUX


   m_pimpl->show_task(bVisible && m_bShowTask);

#else

   m_pimpl->show_task(bVisible && m_bShowTask
                      && !layout().is_iconic());

#endif

}


void simple_frame_window::show_task(bool bShow)
{

   if (m_pimpl == nullptr)
   {

      return;

   }

   m_pimpl->show_task(bShow);

}


//::user::front_end_schema * simple_frame_window::get_user_front_end_schema()
//{
//
//   if (m_pframe == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   return m_pframe->get_user_front_end_schema();
//
//}


bool simple_frame_window::window_is_notify_icon_enabled()
{

   return m_bDefaultNotifyIcon;

}


//bool simple_frame_window::get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pinteraction)
//{
//
//   if (m_pframe != nullptr)
//   {
//
//
//      if (m_pframe->get_color(cr, ecolor, pinteraction))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return ::user::frame_window::get_color(cr, ecolor, pinteraction);
//
//}
//
//


void simple_frame_window::on_select_user_style()
{

   if (m_puserstyle.is_null())
   {

      string strSchema = m_varFrame["experience"];

      if (strSchema.has_char() || is_top_level_window())
      {

         auto pstyle = User.get_user_style(strSchema, get_context_application());

         __refer(m_puserstyle, pstyle);

         //if (!estatus)
         //{


         //}

      }

   }

   //::user::frame_window::on_select_user_style();

}



void simple_frame_window::call_notification_area_action(const char * pszId)
{

   string strId(pszId);

   post_pred([this, strId]()
   {

      notification_area_action(strId);

   });

}


void simple_frame_window::notification_area_action(const char * pszId)
{

   __pointer(::user::interaction) pinteraction = this;

   ::user::command command((::id) pszId);

   pinteraction->_001SendCommand(&command);

}


string simple_frame_window::notification_area_get_xml_menu()
{

   auto pdocument = __new(::xml::document);

   pdocument->create_root("menu");

   for (auto & pitem : m_notifyiconitema)
   {

      if (pitem->m_strId == "separator")
      {

         pdocument->root()->add_child("separator");

      }
      else
      {

         pdocument->root()->add_child("item", { "id", pitem->m_strId }, pitem->m_strName);

      }

   }

   return pdocument->get_xml();

}


void simple_frame_window::on_visual_applied()
{

   ::experience::frame_window::on_visual_applied();

   if (GetParent() == nullptr)
   {

      if (m_ewindowflag & window_flag_auto_store_window_rect)
      {

         if (m_ewindowflag & window_flag_pending_save_window_rect)
         {

            defer_save_window_placement();

         }

      }

      m_ewindowflag -= window_flag_loading_window_rect;

   }

}


void simple_frame_window::_001OnAfterAppearance()
{

   ::experience::frame_window::_001OnAfterAppearance();

}




