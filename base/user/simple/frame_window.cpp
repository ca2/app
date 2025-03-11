#include "framework.h"
#include "frame_window.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/constant/id.h"
#include "acme/parallelization/pool.h"
#include "acme/platform/keep.h"
#include "acme/handler/request.h"
#include "acme/platform/system.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/user/user/_text_stream.h"
#include "apex/handler/signal.h"
#include "apex/database/_binary_stream.h"
#include "apex/database/change_event.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/node.h"
#include "apex/platform/savings.h"
#include "apex/platform/system.h"
#include "acme/platform/application_menu.h"
#include "acme/user/user/activation_token.h"
#include "aqua/xml/document.h"
#include "aura/user/user/interaction_array.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/user/menu/track_popup.h"
#include "aura/user/user/alpha_source.h"
#include "aura/windowing/display.h"
#include "aura/windowing/icon.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "base/user/user/user.h"
#include "base/platform/application.h"
#include "aura/user/user/notify_icon.h"
#include "base/platform/session.h"
#include "base/user/experience/frame.h"
#include "aura/message/user.h"
#include "aura/user/user/system.h"
#include "base/user/user/impact_system.h"
#include "base/user/experience/control_box.h"
#include "base/user/user/document.h"
#include "base/user/user/toolbar.h"
#include "base/user/user/place_holder.h"
#include "base/user/user/impact_host.h"
#include "aura/user/user/style.h"


#define TEST 0
//#define VERBOSE_LOG


namespace base
{


   ::type_atom user::get_simple_frame_window_type_info()
   {

      return ::type < ::simple_frame_window >();

   }


} // namespace base


simple_frame_window::simple_frame_window()
{

   m_bEnableDragClient = false;

   m_bDefaultClickHandling = false;

   //m_bDefaultMouseHoverHandling = false;

   m_bHideOnCloseMessage = false;

   m_bFramePayloadFlags = false;

   m_bProdevianFrame = true;

   m_bToolbar = false;

   m_etranslucencyFrame = ::user::e_translucency_present;

   //m_bDefaultCreateToolbar = true;

   m_bShowTask = true;

   //m_bDefaultNotifyIcon = false;

#if defined(UNIVERSAL_WINDOWS)

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

   //m_bWindowFrame = true;

//#if defined(APPLE_IOS) || defined(ANDROID)

//   m_bWindowFrame = false;

//#else

  // m_bWindowFrame = true;

//#endif

   m_bLayered = true;

   m_ewindowflag |= e_window_flag_composite;

   m_pimpactsystem = nullptr;

}


simple_frame_window::~simple_frame_window()
{

}


void simple_frame_window::initialize(::particle * pparticle)
{

   //auto estatus = 

   ::experience::frame_window::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


::user::notify_icon * simple_frame_window::notify_icon()
{

   return m_pnotifyicon;

}


bool simple_frame_window::has_notify_icon()
{

#if defined(HAS_GTK4)

   return false;

#else

   return m_bDefaultNotifyIcon2;

#endif

}


void simple_frame_window::on_system_command(const ::e_system_command & esystemcommand)
{

   if (has_notify_icon() && esystemcommand == e_system_command_minimize)
   {

      hide();

      set_need_redraw();

      post_redraw();

      return;

   }

   ::experience::frame_window::on_system_command(esystemcommand);

}



void simple_frame_window::enable_default_notification_icon(bool bEnableDefaultNotificationIcon)
{

   m_bDefaultNotifyIcon2 = bEnableDefaultNotificationIcon;

}


void simple_frame_window::on_update_notify_icon_menu(::collection::index & iNotifyIconItem)
{

   on_update_notify_icon_menu_header(iNotifyIconItem);

   on_update_notify_icon_menu_top(iNotifyIconItem);

   on_update_notify_icon_menu_main(iNotifyIconItem);

   on_update_notify_icon_menu_bottom(iNotifyIconItem);

   on_update_notify_icon_menu_footer(iNotifyIconItem);


}


void simple_frame_window::on_update_notify_icon_menu_header(::collection::index & iNotifyIconItem)
{

   auto papp = application();

   //auto puser = papp->get_session()->user();

   auto strAppTitle = papp->application_title();

   auto pmenu = m_pnotifyicon->menu();

   pmenu->stock_item_at(iNotifyIconItem, strAppTitle, "notify_icon_topic");

   if (papp->application_menu()->has_element())
   {

      ::collection::index iIndexSource;

      if (papp->application_menu()->first()->m_strName == strAppTitle)
      {

         if (papp->application_menu()->first()->is_popup())
         {

            auto ppopupApp = papp->application_menu()->first();

            pmenu->separator_at(iNotifyIconItem);
            
            for (::collection::index iIndexPopup = 0; iIndexPopup < ppopupApp->count(); iIndexPopup++)
            {

               if (iIndexPopup + 1 < ppopupApp->count())
               {

                  if (ppopupApp->element_at(iIndexPopup)->is_separator()
                     && ppopupApp->element_at(iIndexPopup + 1)->m_atomMenu == "try_close_application")
                  {

                     if (iIndexPopup + 1 == ppopupApp->upper_bound())
                     {

                        break;

                     }
                     else if (ppopupApp->element_at(iIndexPopup + 2)->is_separator())
                     {

                        iIndexPopup += 2;

                     }

                  }

               }

               auto pitem = ppopupApp->element_at(iIndexPopup);

               if (pitem->m_atomMenu == "try_close_application")
               {

                  continue;

               }

               pmenu->insert_at(iNotifyIconItem++, pitem);

            }

            pmenu->separator_at(iNotifyIconItem);

         }

         iIndexSource = 1;

      }
      else
      {

         iIndexSource = 0;

      }

      for (; iIndexSource < papp->application_menu()->count(); iIndexSource++)
      {

         auto papplicationmenu = papp->application_menu()->element_at(iIndexSource);

         pmenu->insert_at(iNotifyIconItem++, papplicationmenu);

      }

   }
   else
   {

   }


}


void simple_frame_window::on_update_notify_icon_menu_top(::collection::index & iNotifyIconItem)
{

   //auto papp = auraapplication();

   //auto c = papp->application_menu()->get_count();

   //auto papplicationmenu = papp->application_menu();

   //for (auto i = 0; i < c; i++)
   //{

   //      auto pitem = papp->main_menu()->element_at(i);

     // m_pnotifyicon->menu()->insert_at(0, papplicationmenu); // notify_icon_insert_item(false, iNotifyIconItem, pitem->m_strName, pitem->m_strId);

//   }

}


void simple_frame_window::on_update_notify_icon_menu_main(::collection::index & iNotifyIconItem)
{



}


void simple_frame_window::on_update_notify_icon_menu_bottom(::collection::index & iNotifyIconItem)
{

   if (m_pframe != nullptr
      && m_pframe->get_control_box() != nullptr
      && m_pframe->get_control_box()->has_button(::experience::e_button_transparent_frame))
   {

//      m_pnotifyicon->menu()->separator_at(iNotifyIconItem);

      //m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, _("Transparent Frame"), "transparent_frame");
//      m_pnotifyicon->menu()->stock_item_at(iNotifyIconItem, "Transparent Frame", "transparent_frame");

      if (m_bWindowFrame)
      {

//         auto papplicationmenu = application()->application_menu();

         {

            auto pmenu = m_pnotifyicon->menu();

            auto ppopupView = pmenu->popup_at(iNotifyIconItem, "View");

            //ppopupView->add(pmenuView);

            ppopupView->item("Transparent Frame", "transparent_frame", "", "");

         }

         application()->application_menu_update();

      }


   }

}


void simple_frame_window::on_update_notify_icon_menu_footer(::collection::index & iNotifyIconItem)
{

   m_pnotifyicon->menu()->separator_at(iNotifyIconItem);

   //m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, _("Exit"), "app_exit");
   m_pnotifyicon->menu()->stock_item_at(iNotifyIconItem, "Exit", "try_close_application");

}


::user::enum_translucency simple_frame_window::get_translucency(::user::style * pstyle)
{

   if (m_etranslucencyFrame != ::user::e_translucency_undefined)
   {

      return m_etranslucencyFrame;

   }

   return ::experience::frame_window::get_translucency(pstyle);

}


void simple_frame_window::install_message_routing(::channel * pchannel)
{

   ::experience::frame_window::install_message_routing(pchannel);

   MESSAGE_LINK(e_message_create, pchannel, this, &simple_frame_window::on_message_create);
   //#ifdef WINDOWS_DESKTOP
      //MESSAGE_LINK(WM_DDE_INITIATE, pchannel, this, &simple_frame_window::_001OnDdeInitiate);
   //#endif
   MESSAGE_LINK(e_message_destroy, pchannel, this, &simple_frame_window::on_message_destroy);
   MESSAGE_LINK(e_message_close, pchannel, this, &simple_frame_window::on_message_close);
   MESSAGE_LINK(e_message_size, pchannel, this, &simple_frame_window::on_message_size);
   MESSAGE_LINK(e_message_reposition, pchannel, this, &simple_frame_window::on_message_move);

#ifdef WINDOWS_DESKTOP

   MESSAGE_LINK(e_message_get_min_max_info, pchannel, this, &simple_frame_window::_001OnGetMinMaxInfo);

#endif

   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_frame_window::on_message_mouse_move);
   MESSAGE_LINK(e_message_display_change, pchannel, this, &simple_frame_window::on_message_display_change);
   MESSAGE_LINK(e_message_show_window, pchannel, this, &simple_frame_window::on_message_show_window);
   MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &simple_frame_window::_001OnMouseActivate);
   MESSAGE_LINK(e_message_non_client_hit_test, pchannel, this, &simple_frame_window::_001OnNcHitTest);

   MESSAGE_LINK(e_message_key_down, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_sys_key_down, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_key_up, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_sys_key_up, pchannel, this, &simple_frame_window::_001OnKey);

   add_command_prober("transparent_frame", { this,  &simple_frame_window::_001OnUpdateToggleTransparentFrame });
   add_command_handler("transparent_frame", { this,  &simple_frame_window::_001OnToggleTransparentFrame });

   add_command_prober("view_full_screen", { this,  &simple_frame_window::_001OnUpdateImpactFullScreen });
   add_command_handler("view_full_screen", { this,  &simple_frame_window::_001OnImpactFullScreen });

   add_command_handler("notify_icon_topic", { this,  &simple_frame_window::_001OnNotifyIconTopic });
   add_command_handler("try_close_application", { this,  &simple_frame_window::on_message_app_exit });

#ifdef WINDOWS_DESKTOP


   MESSAGE_LINK(e_message_application_exit, pchannel, this, &simple_frame_window::on_message_app_exit);
   MESSAGE_LINK(e_message_activate_app, pchannel, this, &simple_frame_window::_001OnActivateApp);

#endif

   MESSAGE_LINK(e_message_activate, pchannel, this, &simple_frame_window::_001OnActivate);
   MESSAGE_LINK(e_message_update_notify_icon, pchannel, this, &simple_frame_window::_001OnUpdateNotifyIcon);

}


void simple_frame_window::task_save_window_placement()
{

   informationf("_task_save_window_rect start\n");

   auto ptask = ::get_task();

   while (ptask->task_get_run())
   {

      bool bIsWindow = (m_ewindowflag & e_window_flag_is_window);

      if (!bIsWindow)
      {

         break;

      }

      //if (!m_pprimitiveimpl)
      //{

      //   break;

      //}

      bool bDestroying = has_destroying_flag();

      if (bDestroying)
      {

         break;

      }

      if (m_timeLastSaveWindowRectRequest.elapsed() < 150_ms)
      {

         preempt(150_ms);

      }
      else if (m_bPendingSaveWindowRect)
      {

         task_intensive_save_window_placement();

         m_timeLastSaveWindowRect.Now();

      }
      else if (m_timeLastSaveWindowRect.elapsed() > 10_s)
      {

         break;

      }
      else
      {

         preempt(150_ms);

      }

   }

   informationf("_task_save_window_rect end\n");

}


void simple_frame_window::task_intensive_save_window_placement()
{

   while (::task_get_run())
   {

      preempt(300_ms);

      if (layout().m_eflag)
      {

         continue;

      }

      if (m_timeLastSaveWindowRect.elapsed() < 300_ms)
      {

         continue;

      }

      try
      {

         m_bSizeMove = false;

         m_bPendingSaveWindowRect = false;

         user_post([this]()
                                     {

                                        WindowDataSaveWindowRectangle();

                                     });

         break;

      }
      catch (...)
      {

      }

      m_bPendingSaveWindowRect = true;

   }

}


void simple_frame_window::defer_save_window_placement()
{

   if (has_destroying_flag() ||
      has_finishing_flag())
   {

      return;

   }

   synchronous_lock synchronouslock(this->synchronization());

   if (!should_save_window_rectangle())
   {

      return;

   }

   m_bPendingSaveWindowRect = true;

   m_timeLastSaveWindowRectRequest.Now();

   __defer_branch(task_save_window_placement);

}


bool simple_frame_window::WindowDataLoadWindowRectangle()
{

   if (wfi_has_up_down())
   {

      if (!(m_uiUserInteractionFlags & ::user::e_interaction_wfi_up_down_loading2))
      {

         __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

         bool bWfiDown = true;

         auto papp = get_app();

         ::cast < ::database::client > pdatabaseclient = papp;

         pdatabaseclient->datastream()->get("wfi_down", bWfiDown);

         if (bWfiDown)
         {

            design_down();

            //return true;

         }
         else
         {

            design_up();

            if (m_ewindowflag & e_window_flag_window_created)
            {

               return true;

            }

         }

      }
      else if (wfi_is_down())
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction_child::WindowDataLoadWindowRectangle (3)";
         information() << "";
         information() << "";

         return false;

      }

   }

   information() << "-------------------------------------------------------------------";
   information() << "";
   information() << "";
   information() << "interaction_child::WindowDataLoadWindowRectangle (4)";
   information() << "";
   information() << "";

   return ::experience::frame_window::WindowDataLoadWindowRectangle();

}


void simple_frame_window::WindowDataSaveWindowRectangle()
{

   if (wfi_has_up_down())
   {

      bool bDown;

      bDown = m_eupdown != e_updown_up;

      auto papp = get_app();

      ::cast < ::database::client > pdatabaseclient = papp;

      pdatabaseclient->datastream()->set("wfi_down", bDown);

   }

   return ::experience::frame_window::WindowDataSaveWindowRectangle();

}


bool simple_frame_window::_001OnBeforeEnterAppearance()
{

   ::e_display edisplayRequest = const_layout().sketch().display();

   if (edisplayRequest == ::e_display_up || edisplayRequest == ::e_display_down)
   {

      initialize_frame_window_experience();

   }

   if (!::experience::frame_window::_001OnBeforeEnterAppearance())
   {

      return false;

   }

   return true;

}


::pointer<::user::interaction>simple_frame_window::WindowDataGetWnd()
{

   return this;

}


void simple_frame_window::on_message_destroy(::message::message * pmessage)
{

   pmessage->previous();

   if (m_ptaskpool)
   {

      m_ptaskpool->destroy();

      m_ptaskpool.release();

   }

   {

      //_synchronous_lock synchronouslock(this->synchronization());

      try
      {

         //user_send([this]()
           // {

               if (m_pnotifyicon)
               {

                  m_pnotifyicon->destroy_notify_icon();

                  m_pnotifyicon.release();

               }

            //});

      }
      catch (...)
      {

      }

   }

}


::pointer < ::experience::frame > simple_frame_window::frame_experience()
{

   auto puser = user();

   if (!puser || puser->experience() == nullptr)
   {

      return nullptr;

   }

   auto papp = get_app();

   if (papp->m_pacmeuserinteractionMain != nullptr)
   {

      ::pointer<::simple_frame_window>pframe = papp->m_pacmeuserinteractionMain.get();

      if (pframe.is_set())
      {

         auto pschemaRef = pframe->m_pframe;

         if (pschemaRef.is_set())
         {

            auto pframe = ::experience::frame_window::frame_experience(pschemaRef->m_strExperience, pschemaRef->m_strFrameSchema);

            if (::is_set(pframe))
            {

               auto psignal = signal(id_user_style_change);

               psignal->add_handler(pframe);

               return pframe;

            }

         }

      }

   }

   auto pframe = ::experience::frame_window::frame_experience(m_varFrame["experience"], m_varFrame["schema"]);

   string strStyle;

   strStyle = m_varFrame["style"];

   auto psignal = signal(id_user_style_change);

   psignal->add_handler(pframe);

   if (strStyle.has_character())
   {

      set_user_style(strStyle);

   }
   else
   {

      set_user_style(pframe->get_default_user_style());

   }

   return pframe;

}


void simple_frame_window::initialize_frame_window_experience()
{

   if (m_pframe.is_set())
   {

      return;

   }

   ::pointer<::experience::frame>pexperienceframe;

   try
   {

      pexperienceframe = ::transfer(frame_experience());

   }
   catch (const ::exception &)
   {

   }
   catch (...)
   {

   }

   if (pexperienceframe == nullptr)
   {


      throw ::exception(error_null_pointer);

   }

   set_frame(pexperienceframe);

   ::experience::frame_window::initialize_frame_window_experience();

   //if (!::experience::frame_window::initialize_frame_window_experience())
   //{

   //   return false;

   //}

#if defined(LINUX) || defined(__APPLE__)

   SetActiveFlag(true);

#endif

   //return true;

}


bool simple_frame_window::would_display_notify_icon()
{

#if defined(UNIVERSAL_WINDOWS) || defined(ANDROID) || defined(APPLE_IOS) || defined(OPENBSD)

   return false;

#else

   return has_notify_icon();

#endif

}


void simple_frame_window::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

//   if (m_pusersystem
//       && m_pusersystem->m_bWindowFrame)
//   {
//
//            m_bWindowFrame = pusersystem->m_bWindowFrame;
//
//         }
//
//         //if (system()->m_bPreferNoFrameWindow)
//         //{
//
//         //   m_bWindowFrame = false;
//
//         //}
//
//      }
//
//   }
//   //else
//   //{
//
//   //   m_bWindowFrame = system()->m_bExperienceMainFrame;
//
//   //}
//
//   //::pointer<::user::place_holder>pplaceholder = get_parent();
//
//   //if (pplaceholder != nullptr)
//   //{
//
//   //   ::pointer<::user::place_holder_container>pcontainer = pplaceholder->get_parent();
//
//   //   if (pcontainer != nullptr)
//   //   {
//
//   //      pcontainer->on_place_hold(this, pplaceholder);
//
//   //   }
//
//   //}

   auto papp = get_app();

//   if (m_bWindowFrame.undefined())
//   {
//
//      auto & bApplicationExperienceMainFrame = papp->m_bExperienceMainFrame;
//
//      if (bApplicationExperienceMainFrame.is_set())
//      {
//
//         if (get_parent() == nullptr)
//         {
//
//            m_bWindowFrame = bApplicationExperienceMainFrame;
//
//         }
//         else
//         {
//
//            m_bWindowFrame = false;
//
//         }
//
//      }
//      else
//      {
//
//#if defined(UNIVERSAL_WINDOWS) || defined(APPLE_IOS) || defined(ANDROID)
//
//         m_bWindowFrame = false;
//
//#else
//
//         m_bWindowFrame = get_parent() == nullptr || wfi_has_up_down();
//
//#endif
//
//      }
//
//   }

   //if (system()->m_bPreferNoFrameWindow)
   //{

   //   m_bWindowFrame = false;

   //}

   //if (m_bWindowFrame || m_bFramePayloadFlags)
   {

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         //#if !defined(APPLE_IOS) && !defined(ANDROID)

         if (m_pimpactsystem->id().has_character())
         {

            ::file::path pathFrameJson = "matter://" + m_pimpactsystem->id() + "/frame.network_payload";

            //// auto pcontext = get_context();

            m_varFrame = file()->safe_get_network_payload(pathFrameJson);

         }

         //#endif
         if (m_varFrame["experience"].is_empty())
         {

            string strPreferredExperience = get_app()->preferred_experience();

            m_varFrame["experience"] = strPreferredExperience;

         }

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

               m_ebuttonaHide.add(::experience::e_button_transparent_frame);

            }

            if (m_varFrame["control_box"]["dock_button"]["visible"].is_set_false())
            {

               m_ebuttonaHide.add(::experience::e_button_dock);

            }

         }

      }

   }


   //if (m_bWindowFrame)
   //{

   initialize_frame_window_experience();


   on_select_user_style();

   if (get_parent() == nullptr)
   {

      if (m_ebuttonaHide.contains(::experience::e_button_transparent_frame))
      {

         erase_appearance(e_appearance_transparent_frame);

      }

   }

   //if (!initialize_frame_window_experience())
   //{

   //   pcreate->m_lresult = -1;

   //   pcreate->m_bRet = true;

   //   return;

   //}

//}

   if (get_parent() == nullptr && m_strFrameTitle.is_empty())
   {

      m_strFrameTitle = papp->get_app_user_friendly_task_bar_name();

   }

   //#if !defined(WINDOWS)

      //defer_set_icon();

   //#endif

      //defer_synch_layered();

   if (!m_bShowTask)
   {

      show_task(m_bShowTask);

   }

   //#if !defined(UNIVERSAL_WINDOWS) && !defined(ANDROID) && !defined(APPLE_IOS)

   //if (!(m_ewindowflag & e_window_flag_window_created))
   //{

      if (would_display_notify_icon())
      {

         information() << "simple_frame_window::on_message_create m_bDefaultNotifyIcon";

         user_send([this]()
                        {

                          //auto papp = get_app();
                     //auto psystem = system();

                     //auto estatus =

                          information() << "simple_frame_window::on_message_create default notify icon starting user thread";

                          try
                           {


                              __defer_construct(m_pnotifyicon);

                           }
                           catch(::exception &)
                           {

                              information() << "simple_frame_window::on_message_create Failed to create notify icon (1)!";

                              enable_default_notification_icon(false);

                              m_pnotifyicon.release();

                           }
                           catch(...)
                           {

                              information() << "simple_frame_window::on_message_create Failed to create notify icon!";

                              enable_default_notification_icon(false);

                              m_pnotifyicon.release();

                           }

                          //if (estatus.succeeded())
                          if(m_pnotifyicon)
                          {

                             //m_pnotifyicon->m_puserinteraction = this;

                             ::collection::index iNotifyIconItem = 0;

                             on_update_notify_icon_menu(iNotifyIconItem);

                             post_message(e_message_update_notify_icon);

                          }

                        });

   }

   //}

   //#endif

   set_window_text(get_frame_title());

}


void simple_frame_window::_on_show_window()
{

   ::experience::frame_window::_on_show_window();

   if (m_bFirstShow)
   {

      m_bFirstShow = false;

      if (get_active_impact())
      {

         get_active_impact()->post_message(e_message_simple_command, e_simple_command_defer_initialize_handled_impacts);

      }

   }

}


void simple_frame_window::on_message_show_window(::message::message * pmessage)
{

   ::pointer<::message::show_window>pshow(pmessage);

   if (pshow->m_bShow)
   {

      //informationf("simple_frame_window::on_message_show_window true : " + ::type(this).name());

      //defer_set_icon();

   }
   else
   {

      //informationf("simple_frame_window::on_message_show_window false :" + ::type(this).name());

   }

   if (would_display_notify_icon())
   {

      if (m_pnotifyicon != nullptr)
      {

         m_pnotifyicon->notify_icon_step();

      }

      OnUpdateToolWindow(pshow->m_bShow);

   }

}



void simple_frame_window::on_message_display_change(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   if (is_top_level())
   {

      ::e_display edisplay = const_layout().sketch().display();

      display(edisplay, { ::user::e_activation_display_change });

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }
   else
   {

      post_simple_command(e_simple_command_load_window_rect, (lparam)false);

   }

   pmessage->m_bRet = true;

   pusermessage->m_lresult = 0;

}


void simple_frame_window::_001OnUpdateNotifyIcon(::message::message * pmessage)
{

   defer_create_notification_icon();

}


void simple_frame_window::on_message_size(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   //m_timeLastVisualChange.Now();

   //if (get_parent() == nullptr)
   //{

   //   defer_save_window_placement();

   //}

}


void simple_frame_window::on_message_move(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   m_timeLastVisualChange.Now();


}


bool simple_frame_window::on_create_client(::user::system * pusersystem)
{

   return ::user::frame_window::on_create_client(pusersystem);

}


bool simple_frame_window::pre_create_window(::user::system * pusersystem)
{

   if (!::user::frame_window::pre_create_window(pusersystem))
   {

      return false;

   }

   //#ifdef WINDOWS_DESKTOP
   //
   //   //pusersystem->m_createstruct.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
   //   //pusersystem->m_createstruct.style |= WS_OVERLAPPEDWINDOW;
   //   //pusersystem->m_createstruct.style |= WS_THICKFRAME;
   //   pusersystem->m_createstruct.style |= WS_POPUP;
   //   //pusersystem->m_createstruct.style &= ~WS_VISIBLE;
   //   pusersystem->m_createstruct.style |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
   //
   //#endif

   ::request * prequest = pusersystem->m_prequest;

   if (prequest && would_display_notify_icon())
   {

      ::pointer<::user::system>pusersystem = prequest->m_pmatterUserPayload;

      ::pointer<::user::document>pdocument = pusersystem->m_pdocumentCurrent;

      if (pdocument->get_document_template()->m_bHiddenOnNotifyIcon)
      {

         //display(::e_display_hide);

         //set_need_redraw();

         //post_redraw();

         prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

         //pusersystem->m_createstruct.style &= ~WS_VISIBLE;

      }

   }
   else if(prequest)
   {
      
      if(prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
      {
         
         display();
         
      }

      
   }

   return true;

}


void simple_frame_window::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   if (::type(this).name().case_insensitive_contains("child_frame"))
   {

      information() << "child_frame";

   }

   //auto papp = get_app();

   //if (!papp->m_bExperienceMainFrame && get_parent() == nullptr)
   //{

   //   auto rectangle = get_host_user_interaction()->rectangle();

   //   place(rectangle);

   //}

   if (is_frame_experience_enabled())
   {

      ::experience::frame_window::on_layout(pgraphics);

   }
   else
   {

      ::user::frame_window::on_layout(pgraphics);

   }

   m_timeLastVisualChange.Now();


}


void simple_frame_window::on_reposition()
{

   //if (m_bWindowFrame)
   //{

   //   on_layout(pgraphics);

   //}

   ::user::frame_window::on_reposition();

   m_timeLastVisualChange.Now();


}


void simple_frame_window::ImpactOnActivateFrame(::pointer<::user::impact>pimpact, unsigned int user, ::pointer<::user::interaction>frame)
{
   __UNREFERENCED_PARAMETER(pimpact);
   __UNREFERENCED_PARAMETER(user);
   //__UNREFERENCED_PARAMETER(pframe);
   //   if(pimpact != nullptr)
   //      pimpact->OnActivateFrame(WA_INACTIVE, (::pointer<::user::simple_frame_window> pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(::message::message * pmessage)
{

#ifdef WINDOWS_DESKTOP

   //::pointer<::user::message>pusermessage(pmessage);

   //MINMAXINFO * pMMI = (MINMAXINFO *) pusermessage->m_lparam.m_lparam;

   //if (layout().is_full_screen())
   //{

   //   pMMI->ptMaxSize.y() = m_FullScreenWindowRect.height();

   //   pMMI->ptMaxTrackSize.y() = pMMI->ptMaxSize.y();

   //   pMMI->ptMaxSize.x() = m_FullScreenWindowRect.width();

   //   pMMI->ptMaxTrackSize.x() = pMMI->ptMaxSize.x();

   //}

#else
   throw ::exception(todo);
#endif
}


void simple_frame_window::show_control_bars(const ::e_display & edisplay, bool bLeaveFullScreenBarsOnHide)
{

   for (auto & toolbartransport : m_mapToolbar.payloads())
   {

      try
      {

         if (toolbartransport)
         {

            if ((is_screen_visible(edisplay) || (!toolbartransport->m_bFullScreenBar || !bLeaveFullScreenBarsOnHide)))
            {

               ::user::activation useractivationDefault;

               toolbartransport->display(edisplay, useractivationDefault);

            }
            else
            {

               toolbartransport->hide();

            }

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

   show_control_bars(e_display_none, true);

   design_window_full_screen();

}


//bool simple_frame_window::display(display_transparent_frame)
//{
//
//   if (m_ebuttonaHide.contains(::experience::e_button_transparent_frame))
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

   if (!m_bTransparentFrameEnable)
   {

      return false;

   }

   auto eappearance = const_layout().sketch().appearance();

   if (eappearance & ::e_appearance_transparent_frame)
   {

      return true;

   }

   return false;

}


void simple_frame_window::_001OnAfterEnterFullScreen()
{

   show_control_bars(e_display_hide);

   ::experience::frame_window::_001OnAfterEnterFullScreen();

}


void simple_frame_window::_001OnAfterExitFullScreen()
{

   ::experience::frame_window::_001OnAfterExitFullScreen();

   show_control_bars();

}


void simple_frame_window::_001OnImpactFullScreen(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   ToggleFullScreen();

}


void simple_frame_window::on_message_mouse_move(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

}


void simple_frame_window::_001OnNcHitTest(::message::message * pmessage)
{

   ::pointer<::message::nc_hit_test>pnchittest(pmessage);

   pnchittest->set_hit_test(e_hit_test_client);

   pnchittest->m_bRet = true;

}


void simple_frame_window::_001OnMouseActivate(::message::message * pmessage)
{

   ::pointer<::message::mouse_activate>pmouseactivate(pmessage);

   pmouseactivate->m_lresult = e_mouse_activate;

   pmouseactivate->m_bRet = true;

}


void simple_frame_window::_001OnUpdateImpactFullScreen(::message::message * pmessage)
{

   ::pointer<::message::command>pcommand(pmessage);

   pcommand->enable();

   pcommand->set_check(layout().is_full_screen(), e_source_sync);

   pcommand->m_bRet = true;

}


void simple_frame_window::ToggleFullScreen()
{

   if (layout().is_full_screen())
   {

      display(e_display_normal);

   }
   else
   {

      display(e_display_full_screen);

   }

}


bool simple_frame_window::_001CanEnterScreenSaver()
{

   return true;

}


void simple_frame_window::_001OnToggleCustomFrame(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   SetCustomFrame(!GetCustomFrame());

}


void simple_frame_window::_001OnUpdateToggleCustomFrame(::message::message * pmessage)
{

   ::pointer<::message::command>pcommand(pmessage);

   pcommand->enable();

   pcommand->set_check(m_bWindowFrame, e_source_sync);

}


void simple_frame_window::_001OnToggleTransparentFrame(::message::message * pmessage)
{

   toggle_appearance(e_appearance_transparent_frame);

   display();

   set_reposition();

   set_need_layout();

   set_need_redraw();

   post_redraw();

   if (pmessage)
   {

      pmessage->m_bRet = true;

   }

}


void simple_frame_window::_001OnUpdateToggleTransparentFrame(::message::message * pmessage)
{

   ::pointer<::message::command>pcommand(pmessage);

   pcommand->enable();

   //if (top_level_frame()->frame_is_transparent())
   //{

   //   MessageBox(nullptr, "ft", "", e_message_box_ok);

   //}
   //else
   //{

   //   MessageBox(nullptr, "fnt", "", e_message_box_ok);

   //}

   pcommand->set_check(frame_is_transparent(), e_source_sync);

}


void simple_frame_window::ActivateFrame(::e_display edisplay)
{

   ::user::frame_window::ActivateFrame(edisplay);

}


void simple_frame_window::GetBorderRectangle(::int_rectangle * prectangle)
{

   *prectangle = m_rectangleBorder;

}


void simple_frame_window::SetBorderRect(const ::int_rectangle & rectangle)
{

   m_rectangleBorder = rectangle;

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


::color::color simple_frame_window::get_border_main_body_color()
{

   if (!m_pframe)
   {

      return ::experience::frame_window::get_border_main_body_color();

   }

   return m_pframe->get_border_main_body_color();

}


void simple_frame_window::on_message_app_exit(::message::message * pmessage)
{

   if (get_parent() != nullptr)
   {

      pmessage->m_bRet = false;

      return;

   }

   auto papp = get_app();

   papp->request_exit_application();

   if (pmessage != nullptr)
   {

      pmessage->m_bRet = true;

   }


}


void simple_frame_window::on_message_close(::message::message * pmessage)
{

   if (wfi_has_up_down())
   {

      string strImpact = id();

      bool bShow = false;

      auto papp = get_app();

      if (strImpact.case_insensitive_ends_eat("::frame"))
      {

         ::cast < ::database::client > pdatabaseclient = papp;

         pdatabaseclient->datastream()->set("frame::" + strImpact + ".visible", bShow);

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

   if (m_bHideOnCloseMessage)
   {

      display(e_display_none);

      set_need_redraw();

      post_redraw();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      return;

   }

   if (would_display_notify_icon())
   {

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

// #ifdef LINUX
//       //if(is_window_visible())
//
//       //auto psystem = system();
//
//       //auto pnode = psystem->node();
//
//       auto edesktop = ::windowing::get_eoperating_ambient();
//
//       if (edesktop == ::windowing::e_operating_ambient_unity
//          || edesktop == ::windowing::e_operating_ambient_xfce)
//       {
//
//          display(e_display_none);
//
//       }
//       else
//       {
//
//          display(e_display_iconic);
//
//       }
//
//       set_need_redraw();
//
//       post_redraw();
//
//
// #else

      if (is_window_visible())
      {

         hide();

         set_need_redraw();

         post_redraw();

      }

//#endif // LINUX

      //set_tool_window();

      return;

   }

   if (m_bModal)
   {
      //throw todo;
      set_dialog_result(m_nModalResult);

      pmessage->m_bRet = true;

      return;

   }
   else if (top_level_frame() != nullptr && top_level_frame()->m_bModal)
   {

      //throw todo;
      //top_level_frame()->EndModalLoop(m_nModalResult);

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
         ::user::document * pdocument = get_active_document();

         if (pdocument != nullptr && !pdocument->can_close_frame(this))
         {

            // document can't close right now -- don't close it
            return;

         }

      }

      auto papp = get_app();

      //::aura::application * papp = &papp;

      if (get_parent() != nullptr)
      {

         bHideWindow = true;

      }
      //else if (papp->is_system() || papp->is_session())
      //{

      //   // TODO: instead of closing all applications in process psystem->m_apptra, should close application that make part of
      //   // cube, bergedge, session or system.

      //   auto applicationa = psystem->get_applicationa();

      //   for (auto & papp : applicationa)
      //   {

      //      if (!App(papp.m_p)._001CloseApplicationByUser(this))
      //      {

      //         return;

      //      }

      //   }

      //}
      else if (papp->on_close_frame_window(this))
      {

         return;

      }
      else
      {

         bHideWindow = true;

      }

   }

   if (bHideWindow)
   {

      display(e_display_none);

   }

}


//#ifdef WINDOWS_DESKTOP
//
//void simple_frame_window::OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS * pncsp)
//
//{
//   __UNREFERENCED_PARAMETER(bCalcValidRects);
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

   //::pointer<::user::message>pusermessage(pmessage);

   //pusermessage->previous();

   //bool bActive = pusermessage->m_wparam != false;

   //if (get_parent() == nullptr && m_bCompositedFrameWindow)
   //{

   //   //if (bActive)
   //   //{

   //   //   if (layout().is_iconic())
   //   //   {

   //   //      display(e_display_normal);

   //   //   }
   //   //   
   //   //   set_active_window();

   //   //}

   //   pusermessage->m_bRet = true;

   //   pusermessage->m_lresult = 0;

   //}

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

   //::pointer<::message::activate>pactivate(pmessage);

   //pactivate->previous();

   //auto eactivate = pactivate->m_eactivate;

   //if (eactivate)
   //{

   //   pactivate->m_bRet = false;

   //   pactivate->m_lresult = 0;

   //}
   //else
   //{

   //   pactivate->m_bRet = false;

   //   pactivate->m_lresult = 0;

   //}

}


bool simple_frame_window::LoadFrame(const ::string & pszMatter, unsigned int dwDefaultStyle, ::user::interaction * puiParent, ::user::system * pusersystem)
{

//   if (pusersystem->id().is_set())
//   {
//
//      ::string strAtom = pusersystem->id().as_string();
//
//      if (strAtom.has_character())
//      {
//
//         id() = strAtom;
//
//      }
//
//   }
//
//   __UNREFERENCED_PARAMETER(puiParent);

//   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)
//
//   auto papp = get_app();

//   if (puiParent == nullptr)
//   {
//
//      puiParent = papp->get_request_parent_ui(this, pusersystem);
//
//   }

//   ::int_rectangle rectangleFrame;
//
//   ::pointer<::user::place_holder>pholder;
//
//   if (puiParent != nullptr && (pholder = puiParent).is_set())
//   {
//
//      rectangleFrame = pholder->rectangle();
//
//   }

   //m_bLockSketchToDesign = true;

//   if (puiParent == nullptr || wfi_has_up_down())
//   {
//
//      if (wfi_has_up_down() && ::is_set(puiParent) && puiParent->m_bWfiUpDownTarget)
//      {
//
//         m_pupdowntarget = puiParent;
//
//      }
//
//      if (should_save_window_rectangle())
//      {
//
//         //bool bForceRestore = false;
//
//         //bool bInitialFramePosition = true;
//
//         //m_puserinteractionParent = puiParent;
//
//         //WindowDataLoadWindowRectangle(bForceRestore, bInitialFramePosition);
//
//         //_001FancyInitialFramePlacement();
//
//         initial_frame_placement();
//
//         rectangleFrame = const_layout().state(::user::e_layout_sketch).parent_raw_rectangle();
//
//         information() << "simple_frame_window::LoadFrame rectangleFrame : " << rectangleFrame;
//         information() << "simple_frame_window::LoadFrame edisplay : " << const_layout().sketch().display();
//
//         if (wfi_has_up_down())
//         {
//
//            if (m_eupdown == e_updown_up)
//            {
//
//               puiParent = nullptr;
//
//            }
//            else if (m_eupdown == e_updown_down)
//            {
//
//               ::pointer<::user::document>pdocument = pusersystem->m_pdocumentCurrent;
//
//               ::pointer<::user::impact_host>pimpacthost;
//
//               if (pimpacthost.is_set())
//               {
//
//                  puiParent = pimpacthost->updown_target_get_place_holder(this, pdocument);
//
//               }
//
//            }
//
//         }
//
//      }
//
//      if (is_top_level())
//      {
//
//         if (m_ewindowflag & e_window_flag_main_frame)
//         {
//
//            display(e_display_zoomed);
//
//            //  psession->get_main_workspace(rectangleFrame);
//
//         }
//
//      }
//
//      rectangleFrame = const_layout().state(::user::e_layout_sketch).parent_raw_rectangle();
//
//      //pusersystem->set_rect(rectangleFrame);
//
//      informationf("(2) simple_frame_window::LoadFrame rectangleFrame (l=%d, t=%d) (w=%d, h=%d)", rectangleFrame.left(), rectangleFrame.top(), rectangleFrame.width(), rectangleFrame.height());
//      informationf("(2) simple_frame_window::LoadFrame edisplay=%s", ::string(::as_string((int)const_layout().sketch().display().eflag())).c_str());
//
//
//   }

//   if (puiParent != nullptr)
//   {
//
//      //pusersystem->m_createstruct.style |= WS_CHILD;
//
//   }
//
//   m_bEnableSaveWindowRect2 = false;
//
//   bool bLoadImplRect = m_ewindowflag & e_window_flag_load_window_rect_on_impl;
//
//   m_ewindowflag -= e_window_flag_load_window_rect_on_impl;

   //bool bCreated = create_window_ex(pusersystem, puiParent, id());

   //bool bCreated;

//   m_pusersystem = pusersystem;

   //bCreated = 

//   if (pusersystem->m_prequest && !(pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen))
//   {
//
//      hide();
//
//   }

//   if (bLoadImplRect)
//   {
//
//      m_ewindowflag += e_window_flag_load_window_rect_on_impl;
//
//   }
//
//   if (pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
//   {
//
//      initial_frame_display();
//
//   }

   if(!::experience::frame_window::LoadFrame(pszMatter, dwDefaultStyle,puiParent,  pusersystem))
   {


      return false;

   }

   //create_interaction(puiParent, atom());


   //if (!bCreated)
   //{

   //   return false;   // will self destruct on failure normally

   //}

   //if (pusersystem == nullptr)   // send initial update
   //{

     // send_message_to_descendants(e_message_system_update, id_initial_update, (lparam)0, true, true);

   //}

//   if (pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
//   {
//
//      initial_frame_display();
//
//   }

   return true;

}


void simple_frame_window::_001OnDdeInitiate(::message::message * pmessage)
{

   //::pointer<::user::message>pusermessage(pmessage);

   //pusermessage->set_lresult(default_window_procedure((unsigned int)pusermessage->m_wparam, pusermessage->m_lparam, pusermessage->get_lresult()));

}


void simple_frame_window::_001OnKey(::message::message * pmessage)
{


}


void simple_frame_window::pre_translate_message(::message::message * pmessage)
{

   if (pmessage->m_emessage == e_message_display_change)
   {

      display();

   }
   else if (pmessage->m_emessage == e_message_mouse_move)
   {

   }

   return ::experience::frame_window::pre_translate_message(pmessage);

}


void simple_frame_window::on_frame_position()
{

   display(e_display_default, { ::user::e_activation_set_active } );

   order_top();

   if (is_frame_experience_enabled())
   {

      if (const_layout().design().display() == ::e_display_iconic)
      {

         display(e_display_normal);

      }

   }

   if (m_palphasource != nullptr)
   {

      m_palphasource->on_alpha_target_initial_frame_position();

   }

   set_need_redraw();

   post_redraw();

}


//bool simple_frame_window::_001FancyInitialFramePlacement(bool bForceRestore)
//{
//
//   //if (system()->m_bPreferNoFrameWindow)
//   //{
//
//   //   set_need_layout();
//
//   //   set_need_redraw();
//
//   //   post_redraw();
//
//   //   return;
//
//   //}
//
//   auto papp = get_app();
//
//   try
//   {
//
//      if(!m_bWindowFrame)
//      {
//
//         display(e_display_full_screen);
//
//      }
//      else if (m_bFrameMoveEnable)
//      {
//
//         bool bHostTopLevel = is_host_top_level();
//
//         if (bHostTopLevel)
//         {
//
//            display(e_display_full_screen);
//
//         }
//         else if (papp->has_property("full_screen"))
//         {
//
//            display(e_display_full_screen);
//
//         }
//         else if (papp->has_property("wfi_maximize") && is_top_level_window())
//         {
//
//            display(e_display_zoomed);
//
//         }
//            //else if(papp->m_bExperienceMainFrame)
//            //{
//
//            //   if(is_frame_experience_enabled())
//            //   {
//
//            //      display(e_display_full_screen);
//
//            //   }
//            //   else
//            //   {
//
//            //      //best_monitor(nullptr,nullptr,true);
//
//            //      display(e_display_zoomed);
//
//            //   }
//
//            //}
//         else
//         {
//
//            m_bInitialFramePosition = true;
//
//            WindowDataLoadWindowRectangle(bForceRestore, true);
//
//         }
//
//      }
//
//      m_bInitialFramePosition = true;
//
//      get_app()->on_initial_frame_position(this);
//
//      //on_frame_position();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   //set_need_layout();
//
//   //set_need_redraw();
//
//   //m_bLockSketchToDesign = false;
//
//   //post_redraw();
//
//   return true;
//
//}




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

   

   if (get_app() == nullptr
      || !session()
      || !session()->savings())
   {

      return;

   }

   if (session()->savings()->is_trying_to_save(::e_resource_processing)
      || session()->savings()->is_trying_to_save(::e_resource_translucent_background))
   {

      auto rectangleX = this->rectangle();

      pgraphics->fill_rectangle(rectangleX, rgb(0, 0, 0));

   }
   else
   {

      ::user::frame_window::_001OnDeferPaintLayeredWindowBackground(pgraphics);

   }

}


void simple_frame_window::_000OnDraw(::draw2d::graphics_pointer & pgraphicsParam)
{

   //if (!is_frame_experience_enabled())
   //{

   //auto pointOffset = pgraphicsParam->origin();

   ::user::frame_window::_000OnDraw(pgraphicsParam);

   return;

   //}

//   ::draw2d::save_context savecontext(pgraphicsParam);
//
//   int_point pointScroll = m_pointScroll;
//
//   if (!pointScroll.is_null())
//   {
//
//      pgraphicsParam->offset_origin(-pointScroll.x(), -pointScroll.y());
//
//   }
//
//   pgraphicsParam->m_dFontFactor = 1.0;
//
//   try
//   {
//
//      auto type = ::type(this);
//
//
//      //if (pgraphics->m_bDraw)
//      //{
//
//#ifdef __DEBUG
//
//      auto timeStart = ::time::now();
//
//#endif //__DEBUG
//
//      //{
//
//      //   auto pinteraction = get_wnd();
//
//      //   if (pinteraction)
//      //   {
//
//         //}
//
//      //}
//
//      _001OnNcClip(pgraphicsParam);
//
//      //auto pstyle = get_style(pgraphics);
//
//      _001OnNcDraw(pgraphicsParam);
//
//
//   }
//   catch (...)
//   {
//
//
//   }
//
//
//   //{
//
//   //   _synchronous_lock synchronouslock(this->synchronization());
//
//   //   if (m_pprimitiveimpl->m_puserinteraction == nullptr)
//   //   {
//
//   //      return;
//
//   //   }
//
//   //   //if (!_000OnBeforeDraw(pgraphicsParam))
//   //   //{
//
//   //     // return;
//
//   //   //}
//
//   //}
//
//   //auto pstyle = get_style(pgraphicsParam);
//
//   windowing_output_debug_string("\nsimple_frame_window::_001OnDraw B");
//
//   ::int_rectangle rectangleX;
//
//   this->rectangle(rectangleX);
//
//   bool bDib = false;
//
//   double dAlpha = get_alpha();
//
//   ::draw2d::graphics_pointer& pgraphics = pgraphicsParam;
//
//   if (dAlpha == 0.0)
//   {
//
//      windowing_output_debug_string("Alpha is Zero\n");
//
//   }
//
//   if (rectangleX.area() > 0 && dAlpha > 0.0 && dAlpha < 1.0 && m_bTransparent)
//   {
//
//      //auto estatus = 
//      __defer_construct(m_pimageAlpha);
//
//      //if(estatus.succeeded())
//      //{
//
//         //estatus = 
//      m_pimageAlpha->create(rectangleX.size());
//
//      //   if(estatus.succeeded())
//      {
//
//         m_pimageAlpha->clear(color::transparent);
//
//         pgraphics = m_pimageAlpha->get_graphics();
//
//         pgraphics->set_origin(pgraphics->get_origin());
//
//         bDib = true;
//
//      }
//
//      //}
//
//   }
//
//   //::user::style_context style(this);
//
//   {
//
//#ifdef VERBOSE_LOG
//
//      ::time t1 = ::time::now();
//
//#endif
//
//      //pinteraction->_001OnDraw(pgraphics);
//      if (dAlpha > 0.0)
//      {
//
//         //bool bBlurBackground = get_draw_flags(pstyle).has(::user::e_flag_blur_background);
//
//         int iDrawingOrder = DRAWING_ORDER_CLIENT_OVER;
//
//         //if (!bBlurBackground)
//         //{
//
//         //   iDrawingOrder = get_int(pstyle, ::user::e_int_top_level_drawing_order);
//
//         //   if (pstyle)
//         //   {
//
//         //      pstyle->_001OnDrawMainFrameBackground(pgraphics, this);
//
//         //      //if (pstyle->_001OnDrawMainFrameBackground(pgraphics, this))
//         //      //{
//
//         //      //   break;
//
//         //      //}
//
//         //      //style.next();
//
//         //   }
//
//         //}
////
////#if TEST
////
////         pgraphics->fill_solid_rect_dim(0, 0, 100, 100, argb(128, 255, 0, 0));
////
////#endif
//
//         string strType = ::type(this).name();
//
//#ifdef VERBOSE_LOG
//
//         ::time d1 = t1.elapsed();
//
//         if (d1 > 50_ms)
//         {
//
//            information()(e_trace_category_prodevian) << "(more than 50ms) " << strType << "::_001OnDraw took " << integral_millisecond(d1) << "::time.\n";
//
//         }
//
//#endif
//
//         if (iDrawingOrder == DRAWING_ORDER_CLIENT_OVER)
//         {
//
//            _001DrawThis(pgraphics);
//
//            _001DrawChildren(pgraphics);
//
//         }
//         else
//         {
//
//#ifdef VERBOSE_LOG
//
//            ::time t1 = ::time::now();
//
//#endif
//
//            draw_frame_and_control_box_over(pgraphics);
//
//#ifdef VERBOSE_LOG
//
//            auto d1 = t1.elapsed();
//
//            if (d1 > 50_ms)
//            {
//
//               information()(e_trace_category_prodevian) << "(more than 50ms) draw_frame_and_control_box_over took " << d1.integral_millisecond() << "::time.\n";
//
//            }
//
//#endif
//
//         }
//
//      }
//
//      if (m_bOverdraw)
//      {
//
//         _008CallOnDraw(pgraphics);
//
//      }
//
//#if TEST
//
//      pgraphics->fill_solid_rect_dim(0, 100, 100, 100, argb(128, 0, 0, 255));
//
//#endif
//
//   }
//
//   if (bDib)
//   {
//
//      pgraphicsParam->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//      ::image::image_source imagesource(pgraphics);
//
//      ::image::image_drawing_options imagedrawingoptions(rectangleX.size());
//
//      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
//
//      imagedrawing.opacity(dAlpha);
//
//      pgraphicsParam->draw(imagedrawing);
//
//   }

}


bool simple_frame_window::_000OnBeforeDraw(::draw2d::graphics_pointer & pgraphicsParam)
{


   return true;

}


void simple_frame_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   // glxxx

   

   //return;

   pgraphics->set_text_rendering_hint(::write_text::e_rendering_anti_alias);

   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //pgraphics->fill_solid_rectangle(::double_rectangle_dimension(10, 10, 200, 200), ::argb(127, 0, 0, 255));

   //return;

   auto pstyle = get_style(pgraphics);

   bool bBlurBackground = get_draw_flags(pstyle).has(::user::e_flag_blur_background);

   if (bBlurBackground)
   {

      //printf("simplefrmwnd : " + ::type(this).name() + " : blur_background");

      //auto psystem = system();

//      class imaging & imaging = psystem->imaging();

      auto rectangleX = this->rectangle();

      //rectangleX.offset(rectangleX.top_left());

      

      if (session()->savings()->is_trying_to_save(::e_resource_translucent_background))
      {

         //pgraphics->fill_rectangle(rectangleX, rgb(150, 220, 140));

      }
      else if (session()->savings()->is_trying_to_save(::e_resource_processing)
         || session()->savings()->is_trying_to_save(::e_resource_blur_background))
      {

         pgraphics->fill_rectangle(rectangleX, argb(150, 150, 180, 140));

      }
      else
      {

#ifndef LINUX

         //printf("simplefrmwnd : " + ::type(this).name() + " : ifndef LINUX");

         if (rectangleX.size() != m_pimageBk->size())
         {
            m_pimageBk->create(rectangleX.size());
            m_pimageBk->clear_argb(0, 200, 200, 190);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::image::fastblur *( *pfnNew )(::pointer<::aura::application> = (::image::fastblur *(*)(::pointer<::aura::application> ::GetProcAddress(hmodule, "new_fastblur");
            //m_pimageBlur->create(this);
            //m_fastblur.initialize(rectangleX.size(),2);

            m_pimageBlur->create(rectangleX.size());

         }

         if (m_pimageBlur->is_ok())
         {

            ::double_rectangle rectangleTarget(rectangleX.size());

            {

               ::image::image_source imagesource(pgraphics);

               ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               m_pimageBlur->g()->draw(imagedrawing);

            }

            m_pfastblur->initialize(m_pimageBlur->size(), 2);

            m_pfastblur->blur(m_pimageBlur);

            {

               ::image::image_source imagesource(m_pimageBk);

               ::image::image_drawing_options imagedrawingoptions(rectangleX.size());

               imagedrawingoptions.opacity(49);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               m_pimageBlur->draw(imagedrawing);

            }

            {

               ::image::image_source imagesource(m_pimageBlur);

               ::image::image_drawing_options imagedrawingoptions(rectangleX);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);

            }

         }

#endif

      }

   }

   //printf("simplefrmwnd : " + ::type(this).name() + " : draw_frame");

//   pgraphics->fill_solid_rectangle(::double_rectangle_dimension(100, 100, 200, 200), ::argb(127, 0, 255, 0));

   //return;

   draw_frame(pgraphics);

}


void simple_frame_window::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
{

   ::experience::frame_window::_001DrawChildren(pgraphics);

}


bool simple_frame_window::on_before_set_parent(::pointer<::user::interaction>pinteraction)
{

   WindowDataSaveWindowRectangle();

   if (!::user::box::on_before_set_parent(pinteraction))
   {

      return false;

   }

   return true;

}


bool simple_frame_window::on_set_parent(::user::interaction_base * puiParent)
{

   if (!::user::frame_window::on_set_parent(puiParent))
   {

      return false;

   }

   return true;

}


void simple_frame_window::on_after_set_parent()
{

   ::experience::frame_window::on_after_set_parent();

   auto puiParent = get_parent();

   if (puiParent == nullptr)
   {

      if (m_bLayered)
      {

         //ModifyStyleEx(0, WS_EX_LAYERED);

      }

   }

   set_reposition();

   set_need_layout();

   set_need_redraw();

}


::int_rectangle simple_frame_window::rectangle(::user::enum_layout elayout)
{

   return ::experience::frame_window::rectangle(elayout);

}


bool simple_frame_window::is_application_main_window()
{

   auto papp = get_app();

   return papp->m_pacmeuserinteractionMain == this;

}




void simple_frame_window::defer_create_notification_icon()
{

   if (!would_display_notify_icon())
   {

      return;

   }

   user_post([this]
      {

         //      if (m_pnotifyicon)
         //      {
         //
         //         m_pnotifyicon->destroy_notify_icon();
         //
         //      }

               //auto papp = get_app();

         if (!m_piconNotify)
         {

            //auto estatus = 

            __øconstruct(m_piconNotify);

            if(m_piconNotify)
            {

               //const ::scoped_string & scopedstrAppName = papp->m_strAppName;

               try
               {



               m_piconNotify->load_app_tray_icon(get_app()->m_strAppId);

               }
               catch(...)
               {

                  informationf("Exception at load_app_tray_icon");

                  m_piconNotify.release();

               }

            }

         }

         if (!m_piconNotify)
         {

            if(would_display_notify_icon())
            {

               enable_default_notification_icon(false);

            }

            informationf("Could not alocate m_piconNotify");

            return;

         }


         __defer_construct(m_pnotifyicon);

         //m_pnotifyicon->m_puserinteraction = this;
         try
         {
         m_pnotifyicon->create_notify_icon("(application_default_notify_icon)", this, m_piconNotify);
         }
         catch(...)
         {

            if(would_display_notify_icon())
            {

               enable_default_notification_icon(false);

            }

            m_pnotifyicon.release();

            m_piconNotify.release();

         }
         //if (!)
         //{

         //   m_pnotifyicon.release();

         //   return;

         //}

         if(m_pnotifyicon)
         {

            m_bitMinimizeToTray.defer(true);

         }

      });

}


// persistent frame implemenation using updowntarget
bool simple_frame_window::updown_get_up_enable()
{

   return m_pupdowntarget != nullptr && wfi_has_up_down() && wfi_is_down();

}


bool simple_frame_window::updown_get_down_enable()
{

   return m_pupdowntarget != nullptr && wfi_has_up_down() && wfi_is_up();

}


void simple_frame_window::design_down()
{

   m_eupdown = e_updown_down;

   if (m_pframe)
   {

      m_pframe->get_control_box()->set_need_layout();

   }

   __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

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

      WindowDataLoadWindowRectangle();

   }

   set_need_redraw();

   post_redraw();

}


void simple_frame_window::design_up()
{

   m_eupdown = e_updown_up;

   if (m_pframe)
   {

      m_pframe->get_control_box()->set_need_layout();

   }

   __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

   frame_Detach();

   if (m_pupdowntarget->m_uiUserInteractionFlags & ::user::e_interaction_wfi_up_tool_window2)
   {

      set_tool_window();

   }

}


//bool simple_frame_window::create_interaction(const ::string & pszClassName, const ::string & pszWindowName, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction * puiParent, const ::string & pszMenuName, unsigned int dwExStyle, ::request * prequest)
//{
//
//   return ::user::frame_window::create_interaction(pszClassName, pszWindowName, uStyle, rectangle, puiParent, pszMenuName, dwExStyle, pcreate);
//
//}


void simple_frame_window::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
{

   ::experience::frame_window::route_command(pcommand, bRouteToKeyDescendant);

}

//
//#ifdef WINDOWS_DESKTOP
//
//
//void simple_frame_window::OnDropFiles(HDROP hDropInfo)
//{
//
//   set_active_window();      // activate us first !
//   unsigned int nFiles = ::DragQueryFile(hDropInfo, (unsigned int)-1, nullptr, 0);
//
//   ::file::path_array patha;
//
//   natural_wstring pwszFileName(char_count, _MAX_PATH);
//
//   for (unsigned int iFile = 0; iFile < nFiles; iFile++)
//   {
//
//      if (::DragQueryFileW(hDropInfo, iFile, pwszFileName, _MAX_PATH))
//      {
//
//         patha.add(as_string(pwszFileName));
//
//      }
//
//   }
//
//   ::DragFinish(hDropInfo);
//
//   auto puser = user();
//
//   puser->on_frame_window_drop_files(this, patha);
//
//}

//void simple_frame_window::OnEndSession(bool bEnding)
//{
//
//   if (!bEnding)
//   {
//
//      return;
//
//   }
//
//   papp->close(::apex::e_end_system);
//
//}
//
//
//#else
//
////void simple_frame_window::OnDropFiles(HDROP hDropInfo)
////{
////
////   __UNREFERENCED_PARAMETER(hDropInfo);
////
////}
////
//
//
//#endif






//LRESULT simple_frame_window::OnDDEInitiate(WPARAM wParam, LPARAM lParam)
//{
//
//
//#ifdef WINDOWS_DESKTOP
//
//   ::aura::application* pApp = &papp;
//   if (pApp != nullptr &&
//         LOWORD(lParam) != 0 && HIWORD(lParam) != 0 &&
//         (ATOM)LOWORD(lParam) == pApp->m_atomApp &&
//         (ATOM)HIWORD(lParam) == pApp->m_atomSystemTopic)
//   {
//      // make duplicates of the incoming atoms (really adding a object)
//      wchar_t szAtomName[_MAX_PATH];
//      GlobalGetAtomNameW(pApp->m_atomApp, szAtomName, _MAX_PATH - 1);
//      GlobalAddAtomW(szAtomName);
//      GlobalGetAtomNameW(pApp->m_atomSystemTopic, szAtomName, _MAX_PATH - 1);
//      GlobalAddAtomW(szAtomName);
//
//      // send the WM_DDE_ACK (caller will delete duplicate atoms)
//      ::SendMessageW((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
//                    MAKELPARAM(pApp->m_atomApp, pApp->m_atomSystemTopic));
//   }
//
//#else
//
//   throw ::interface_only();
//
//#endif
//
//   return 0L;
//}
//
//
//// always ACK the execute command - even if we do nothing
//LRESULT simple_frame_window::OnDDEExecute(WPARAM wParam, LPARAM lParam)
//{
//
//
//#ifdef WINDOWS_DESKTOP
//
//   // unpack the DDE message
//   uptr unused;
//   HGLOBAL hData;
//   //IA64: Assume DDE LPARAMs are still 32-bit
//   VERIFY(UnpackDDElParam(WM_DDE_EXECUTE, lParam, &unused, (uptr*)&hData));
//
//   // get the command string
//   const ::scoped_string & scopedstr = (const ::string &)GlobalLock(hData);
//
//   wstring strCommand;
//   try
//   {
//      strCommand = psz;
//
//      GlobalUnlock(hData);
//   }
//   catch (memory_exception * pe)
//   {
//      GlobalUnlock(hData);
//      ::exception_pointer esp(pe);
//   }
//
//
//   // acknowledge now - before attempting to execute
//   ::PostMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
//                 //IA64: Assume DDE LPARAMs are still 32-bit
//                 ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
//                                (unsigned int)0x8000, (uptr)hData));
//
//   // don't execute the command when the u is disabled
//   if (!is_window_enabled())
//   {
//      information(trace_category_appmsg, e_trace_level_warning, "Warning: DDE command '%s' ignored because u is disabled.\n",
//            string(strCommand).c_str());
//      return 0;
//   }
//
//   // execute the command
//   //LPWSTR pszCommand = strCommand.alloc(strCommand.length());
//
//   //if (!psystem->OnDDECommand(pszCommand))
//
//   //   information(trace_category_appmsg, e_trace_level_warning, "Error: failed to execute DDE command '%s'.\n", pszCommand);
//
//   //strCommand.release_buffer();
//
//#else
//
//   throw ::interface_only();
//
//#endif
//
//   return 0L;
//
//}
//
//LRESULT simple_frame_window::OnDDETerminate(WPARAM wParam, LPARAM lParam)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   ::PostMessage((oswindow)wParam, WM_DDE_TERMINATE, (WPARAM)get_handle(), lParam);
//
//#else
//
//   throw ::interface_only();
//
//#endif
//
//   return 0L;
//
//}
//
//
//void simple_frame_window::NotifyFloatingWindows(unsigned int dwFlags)
//{
//   ASSERT_VALID(this);
//   // trans   ASSERT(get_handle() != nullptr);
//
//   // get top level parent frame u first unless this is a child u
//   ::pointer<::user::frame_window>pParent = (GetStyle() & WS_CHILD) ? this : top_level_frame();
//   ASSERT(pParent != nullptr);
//   //if (dwFlags & (FS_DEACTIVATE | FS_ACTIVATE))
//   //{
//   //   // update parent u activation state
//   //   bool bActivate = !(dwFlags & FS_DEACTIVATE);
//   //   bool bEnabled = pParent->is_window_enabled();
//
//   //   if (bActivate && bEnabled && pParent != this)
//   //   {
//   //      // Excel will try to Activate itself when it receives a
//   //      // e_message_non_client_activate so we need to keep it from doing that here.
//   //      //m_nFlags |= WF_KEEPMINIACTIVE;
//   //      pParent->send_message(e_message_non_client_activate, true);
//   //      //m_nFlags &= ~WF_KEEPMINIACTIVE;
//   //   }
//   //   else
//   //   {
//   //      pParent->send_message(e_message_non_client_activate, false);
//   //   }
//   //}
//
//   // then update the state of all floating windows owned by the parent
//#ifdef WINDOWS_DESKTOP
//
//   ::pointer<::user::interaction>oswindowDesktop = papp->get_desktop_window();
//
//   if (oswindowDesktop.is_null())
//      return;
//
//   ::pointer<::user::interaction>oswindow = oswindowDesktop->get_wnd(GW_CHILD);
//
//   while (oswindow != nullptr)
//   {
//
//      if (::user::is_descendant(pParent, oswindow))
//         oswindow->send_message(WM_FLOATSTATUS, dwFlags);
//
//      oswindow = oswindow->get_wnd(GW_HWNDNEXT);
//
//   }
//
//#else
//   throw ::exception(todo);
//#endif
//}



// query end session for main frame will attempt to close it all down
void simple_frame_window::_001OnQueryEndSession(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   auto papp = get_app();

   if (::is_set(papp) && papp->m_pacmeuserinteractionMain == this)
   {

      pusermessage->m_lresult = papp->save_all_modified();

      pusermessage->m_bRet = true;

      return;

   }

   pusermessage->m_lresult = true;

   return;

}


void simple_frame_window::handle(::topic * ptopic, ::context * pcontext)
{

   if (ptopic->id() == id_task_bar_created)
   {

      //m_pnotifyicon->m_bCreated = false;

      defer_create_notification_icon();

   }
   else if (ptopic->user_interaction() == m_pnotifyicon)
   {

      if (ptopic->id() == ::id_context_menu)
      {

         //OnNotifyIconContextMenu(ptopic->user_interaction_id());

         auto pointCursor = windowing()->display()->get_mouse_cursor_position();
         
         auto squareHint = int_rectangle::square_with_center_and_apothem(pointCursor, 8);

         pointCursor -= squareHint.top_left();

         pointCursor += ::int_size(16, 16);

         auto pmenu = m_pnotifyicon->menu();

         //

         //auto puser = user();
         
         
         auto ptrackpopup  = __allocate  ::menu::track_popup (
                                                           pmenu,
                                                           this,
                                                           m_pnotifyicon,
                                                           pointCursor,
                                                           squareHint//,
            //::menu::e_track_popup_outside_target
                                                           );

         ptrackpopup->track([](){});
         
//         puser->track_popup_menu(this, pmenu, 0, pointCursor, int_size(), m_pnotifyicon);

      }
      else if (ptopic->id() == ::id_left_button_double_click)
      {

         //OnNotifyIconLButtonDblClk(ptopic->user_interaction_id());

      }
      else if (ptopic->id() == ::id_left_button_down)
      {

         //OnNotifyIconLButtonDown(ptopic->user_interaction_id());

         default_notify_icon_topic(ptopic->user_activation_token());

         ptopic->m_bRet = true;

      }

   }

   ::experience::frame_window::handle(ptopic, pcontext);

}


string simple_frame_window::get_window_default_matter()
{

   if (m_pimpactsystem == nullptr)
   {

      return frame_window::get_window_default_matter();

   }

   return m_pimpactsystem->id();

}


//void simple_frame_window::guserbaseOnInitialUpdate(::message::message * pmessage)
//{
//   ::pointer<::user::message>pusermessage(pmessage);
//   ::user::FrameInitialUpdate * pfiu = (::user::FrameInitialUpdate *)pusermessage->m_lparam.m_lparam;
//   if (pfiu != nullptr)
//   {
//      ::pointer<::user::frame_window>pframe = (this);
//      // if the frame does not have an active ::user::impact, set to first pane
//      ::pointer<::user::impact>pimpact;
//      if (pframe->get_active_impact() == nullptr)
//      {
//         ::pointer<::user::interaction>pwindow = pframe->get_child_by_id(FIRST_PANE);
//         if (pwindow != nullptr && base_class < ::user::impact >::bases(pwindow))
//         {
//            pimpact = (pwindow.m_p);
//            pframe->set_active_impact(pimpact, false);
//         }
//      }
//
//      if (pfiu->m_bMakeVisible)
//      {
//         // send initial update to all views (and other controls) in the frame
//         pframe->send_message_to_descendants(WM_INITIALUPDATE, 0, (LPARAM)0, true, true);
//
//         // give ::user::impact a chance to save the focus (CFormImpact needs this)
//         if (pimpact != nullptr)
//            pimpact->OnActivateFrame(WA_INACTIVE, pframe);
//
//         // finally, activate the frame
//         // (send the default show command unless the main desktop u)
//         ::e_display edisplay = e_display_default;      // default
//         ::aura::application* pApp = System;
//         if (pApp != nullptr && pApp->m_puiMain == pframe)
//         {
//            edisplay = psystem->m_edisplay; // use the parameter from WinMain
//            psystem->m_edisplay = e_display_undefined; // set to default after first time
//         }
//         bool bFullScreen;
//         datastream()->get("FullScreen", bFullScreen);
//         if (bFullScreen)
//         {
//            display(e_display_full_screen);
//         }
//         else
//         {
//            pframe->ActivateFrame(edisplay);
//         }
//         if (pimpact != nullptr)
//            pimpact->OnActivateImpact(true, pimpact, pimpact);
//
//      }
//
//      ::pointer<::user::document>pdocument = pfiu->m_pdocument;
//      // update frame counts and frame title (may already have been visible)
//      if (pdocument != nullptr)
//         pdocument->update_frame_counts();
//      pframe->on_update_frame_title(true);
//
//      set_need_redraw();
//   }
//   pusermessage->set_lresult(0);
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

   _synchronous_lock synchronouslock(this->synchronization());

   //auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   uia = m_uiptraChild;

   //}

   //auto children = synchronized_get_children();

   //if (children.has_element())
   {

      ::draw2d::save_context savecontext(pgraphics);

      //on_context_offset(pgraphics);
      //if (0)
      {

         try
         {

            for_user_interaction_children(puserinteraction, this)
            {

               //synchronouslock.unlock();

               ::pointer < ::experience::control_box > pcontrolbox = puserinteraction;

               if (!pcontrolbox)
               {

                  {

                     auto timeStart = ::time::now();

                     puserinteraction->_000CallOnDraw(pgraphics);

                     auto timeEllapsed = timeStart.elapsed();

                     if (timeEllapsed > 50_ms)
                     {

                        string strType = ::type(puserinteraction).name();

                        //if(strType.contains("pane_impact"))
                        //{

                          // informationf("paneimpact\n");

                        //}

#ifdef VERBOSE_LOG                        

                        information()(e_trace_category_prodevian) << "(more than 50ms) " << strType << "::_001OnDraw took " << integral_millisecond(d1) << "::time.";

#endif

                     }

                  }

               }

               //synchronouslock.lock();

            }

         }
         catch (...)
         {

         }

      }

   }

   {

#ifdef VERBOSE_LOG

      ::time t1 = ::time::now();

#endif

      _001DrawThis(pgraphics);

      //return; // abcxxx

#ifdef VERBOSE_LOG

      ::time d1 = t1.elapsed();

      if (d1 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << "::time.\n";

      }

#endif

   }

   bool bTransparentFrame = frame_is_transparent();

   bool bActive = is_active_window();

   if (m_bWindowFrame && (!bTransparentFrame || bActive))
   {

      ::draw2d::save_context savecontext(pgraphics);

      //on_context_offset(pgraphics);

      try
      {

         //if (puserinteractionpointeraChild)
         {

            //auto children = synchronized_get_children();

            //for (auto & pinteraction : children)
            for_user_interaction_children(puserinteraction, this)
            {

               if (base_class < ::experience::control_box > ::bases(puserinteraction))
               {

                  auto strWindowText = puserinteraction->get_window_text();

                  //pinteraction->get_window_text(str);

                  if (strWindowText == "r")
                  {

                     //TRACE0("x button");

                  }

                  //if (pinteraction->is_this_visible())
                  {


                     {

#ifdef VERBOSE_LOG

                        ::time t1 = ::time::now();

#endif

                        puserinteraction->_000CallOnDraw(pgraphics);

#ifdef VERBOSE_LOG

                        ::time d1 = t1.elapsed();

                        if (d1 > 50_ms)
                        {

                           information()(e_trace_category_prodevian) << "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << ".\n";

                  }

#endif

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

   {

#ifdef VERBOSE_LOG

      ::time t1 = ::time::now();

#endif

      _008CallOnDraw(pgraphics);

#ifdef VERBOSE_LOG

      ::time d1 = t1.elapsed();

      if (d1 > 50_ms)
      {

         information()(e_trace_category_prodevian) << "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << ".\n";

}

#endif

      }


   //pgraphics->fill_solid_rect_dim(200, 200, 1600, 800, argb(128, 200, 240, 150));

}


void simple_frame_window::draw_frame(::draw2d::graphics_pointer & pgraphics)
{

   

   if (m_bWindowFrame && !session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
   {

      ::experience::frame_window::_001OnDraw(pgraphics);

   }

}





//void simple_frame_window::WfiOnClose()
//{
//
//   post_message(e_message_close);
//
//}
//

//void simple_frame_window::WfiOnMaximize()
//{
//
//   if (m_bFullScreenOnMaximize)
//   {
//
//      display(e_display_full_screen);
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


//void simple_frame_window::WfiOnDock(::e_display edisplay)
//{
//
//   _001WindowDock(edisplay);
//
//}


//bool simple_frame_window::DeferFullScreen(bool bFullScreen, bool bRestore)
//{
//   if (bFullScreen)
//   {
//      ::pointer<::user::interaction>puserinteractionParentFrame = get_parent_frame();
//      if (puserinteractionParentFrame == nullptr)
//      {
//         if (!layout().is_full_screen())
//         {
//            display(e_display_full_screen);
//            return true;
//         }
//         else
//         {
//            return false;
//         }
//      }
//      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (puserinteractionParentFrame.m_p);
//      if (pframe == nullptr)
//      {
//         if (!layout().is_full_screen())
//         {
//            display(e_display_full_screen);
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
//         display(e_display_full_screen);
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
//         display(e_display_normal);
//         return true;
//      }
//      ::pointer<::user::interaction>puserinteractionParentFrame = get_parent_frame();
//      if (puserinteractionParentFrame == nullptr)
//      {
//         return false;
//      }
//      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (puserinteractionParentFrame.m_p);
//      if (pframe == nullptr)
//      {
//         return false;
//      }
//      return pframe->DeferFullScreen(bFullScreen, bRestore);
//   }
//}


//bool simple_frame_window::calc_layered()
//{
//
//   ::draw2d::graphics_pointer pgraphics = ::draw2d::create_memory_graphics();
//
//   auto pstyle = get_style(pgraphics);
//
//   
//
//   if (m_bLayered && get_translucency(pstyle) != ::user::e_translucency_none)
//   {
//      return !session()->savings()->is_trying_to_save(::e_resource_processing)
//             && !session()->savings()->is_trying_to_save(::e_resource_display_bandwidth);
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}


void simple_frame_window::data_on_after_change(::message::message * pmessage)
{

   //box::data_on_after_change(pmessage);

   ::pointer<database::change_event>pupdate(pmessage);

   if (pupdate->m_strDataKey == "ca2.savings")
   {

      //defer_synch_layered();

   }

}




void simple_frame_window::on_simple_command(::message::simple_command * psimplecommand)
{

   ::user::frame_window::on_simple_command(psimplecommand);

}


class ::mini_dock_frame_window * simple_frame_window::CreateFloatingFrame(unsigned int uStyle)
{

   __UNREFERENCED_PARAMETER(uStyle);

   return nullptr;

}


















//bool simple_frame_window::display(::e_display edisplay)
//{
//
//   bool bOk1 = ::user::frame_window::display(edisplay);
//
//   if (edisplay == ::e_display_up)
//   {
//
//      m_eupdown = e_updown_up;
//
//   }
//   else if (edisplay == ::e_display_down)
//   {
//
//      m_eupdown = e_updown_down;
//
//   }
//
//   //display(edisplay);
//
//   if(edisplay == ::e_display_full_screen)
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

   on_create_bars();

   //if (!on_create_bars())
   //{

   //   return false;

   //}

   show_control_bars();

   //set_need_layout();

   return true;

}


void simple_frame_window::on_create_bars()
{

   //if(!m_bDefaultCreateToolbar)
   //{

   //   //return ::success;
   //   return;

   //}

   if (m_bToolbar)
   {

      ::atom atom = m_pimpactsystem->id();

      if (atom.has_character())
      {

         get_toolbar(atom);

      }

   }

   //return ::success;

}


void simple_frame_window::prepare_frame(::user::document * pdocument, bool bMakeVisible)
{

   ::user::frame_window::prepare_frame(pdocument, bMakeVisible);

   create_bars();

}


void simple_frame_window::on_timer(::timer * ptimer)
{

   ::user::frame_window::on_timer(ptimer);

   ::experience::frame_window::on_timer(ptimer);

}


//void simple_frame_window::OnNotifyIconContextMenu(unsigned int uNotifyIcon)
//{
//
//}



//
//void simple_frame_window::OnNotifyIconLButtonDblClk(unsigned int uNotifyIcon)
//{
//
//   __UNREFERENCED_PARAMETER(uNotifyIcon);
//
//}
//
//
//void simple_frame_window::OnNotifyIconLButtonDown(unsigned int uNotifyIcon)
//{
//
//   default_notify_icon_topic();
//
//   __UNREFERENCED_PARAMETER(uNotifyIcon);
//
//}


//void simple_frame_window::command_handler(const ::atom & atom)
//{
//
//   if(atom == "notify_icon_topic")
//   {
//
//      _001OnNotifyIconTopic(nullptr);
//
//      return ::success;
//
//   }
//   else if (atom == "transparent_frame")
//   {
//
//      _001OnToggleTransparentFrame(nullptr);
//
//      return ::success;
//
//   }
//
//   auto estatus = ::experience::frame_window::command_handler(atom);
//
//   if(estatus)
//   {
//
//      return estatus;
//
//   }
//
//   //::message::command command
//
//   //route_command_message()
//
//   return estatus;
//
//
//}


void simple_frame_window::_001OnNotifyIconTopic(::message::message * pmessage)
{

   if (would_display_notify_icon())
   {

      default_notify_icon_topic(pmessage->user_activation_token());

   }

   if (pmessage)
   {

      pmessage->m_bRet = true;

   }

}


void simple_frame_window::default_notify_icon_topic(::user::activation_token * puseractivationtoken)
{

   frame_toggle_restore(puseractivationtoken);

}


void simple_frame_window::OnInitialFrameUpdate(bool bMakeVisible)
{

   if (!would_display_notify_icon())
   {

      ::user::frame_window::OnInitialFrameUpdate(bMakeVisible);

      return;

   }

   //if(bMakeVisible)
   //{

   //   //OnUpdateToolWindow(bMakeVisible);

   //   _001FancyInitialFramePlacement();

   //}

}


void simple_frame_window::OnUpdateToolWindow(bool bVisible)
{

   if (!would_display_notify_icon())
   {

      return;

   }

   //if (m_pprimitiveimpl == nullptr)
   //{

   //   return;

   //}

#ifdef LINUX


   windowing_window()->show_task(bVisible && m_bShowTask);

#else

   if (!m_bShowTask)
   {

      show_task(false);

   }

#endif

   }


void simple_frame_window::show_task(bool bShow)
{

   //if (m_pprimitiveimpl == nullptr)
   //{

   //   return;

   //}

   window()->show_task(bShow);

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

   return would_display_notify_icon();

}


//bool simple_frame_window::get_color(::color::color & color32, ::user::e_color ecolor, ::user::interaction * pinteraction)
//{
//
//   if (m_pframe != nullptr)
//   {
//
//
//      if (m_pframe->get_color(color32, ecolor, pinteraction))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return ::user::frame_window::get_color(color32, ecolor, pinteraction);
//
//}
//
//


void simple_frame_window::on_select_user_style()
{

   if (!m_puserstyleFrameInteraction)
   {

      string strSchema(m_varFrame["experience"].as_string());

      if (strSchema.has_character() || is_top_level_window())
      {

         auto puser = user();

         auto pstyle = puser->get_user_style(strSchema, application());

         m_puserstyleFrameInteraction = pstyle;

      }

   }

}


void simple_frame_window::call_notification_area_action(const ::atom & atom, ::user::activation_token * puseractivationtoken)
{

   auto puseractivationtokenHold = as_pointer(puseractivationtoken);

   auto atomHold = atom;

   host_post([this, atomHold, puseractivationtokenHold]()
      {

         handle_command(atomHold, puseractivationtokenHold);

      });

}


void simple_frame_window::notification_area_action(const ::atom & atom, ::user::activation_token * puseractivationtoken)
{

   auto pcommand = __initialize_new::message::command(atom, puseractivationtoken);

   route_command(pcommand);

}


//string simple_frame_window::notification_area_get_xml_menu()
//{
//
//   auto pxmldocument = __create_new < ::xml::document >();
//
//   pxmldocument->create_root("menu");
//
//   for (auto & pitem : m_pnotifyicon->m_notifyiconitema)
//   {
//
//      if (pitem->m_strId == "separator")
//      {
//
//         pxmldocument->root()->add_child("separator");
//
//      }
//      else
//      {
//
//         pxmldocument->root()->add_child("item", { "id", pitem->m_strId }, pitem->m_strName);
//
//      }
//
//   }
//
//   return pxmldocument->get_xml();
//
//}


void simple_frame_window::_on_configure_notify_unlocked(const ::int_rectangle & rectangle)
{

   ::experience::frame_window::_on_configure_notify_unlocked(rectangle);

   if (get_parent() == nullptr)
   {

      if (m_bAutomaticallyStoreWindowRectangle)
      {

         if (m_bPendingSaveWindowRectangle)
         {

            post([this]()
                           {

                              defer_save_window_placement();

                           });


         }

      }

      m_bLoadingWindowRectangle = false;

   }

}

//
//void simple_frame_window::_001OnAfterAppearance()
//{
//
//   ::experience::frame_window::_001OnAfterAppearance();
//
//}




