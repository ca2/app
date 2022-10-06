#include "framework.h"
#include "frame_window.h"
////#include "base/user/simple/_component.h"
#include "aura/message.h"
#include "aqua/xml/document.h"
#include "acme/id.h"
#include "aura/user/user/window_util.h"
#include "acme/parallelization/pool.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/fastblur.h"
#include "aura/windowing/icon.h"
#include "aura/user/user/alpha_source.h"
#include "base/user/user/user.h"
#include "aura/user/user/primitive_impl.h"
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


   ::type user::get_simple_frame_window_type_info()
   {

      return __type(::simple_frame_window);

   }


} // namespace base


simple_frame_window::simple_frame_window()
{

   m_bEnableDragClient = false;

   m_bClickDefaultMouseHandling = false;

   m_bHoverDefaultMouseHandling = false;

   m_bFramePayloadFlags = false;

   m_bProdevianFrame = true;

   m_bToolbar = false;

   m_etranslucencyFrame = ::user::e_translucency_present;

   //m_bDefaultCreateToolbar = true;

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

   //m_bWindowFrame = true;

//#if defined(APPLE_IOS) || defined(ANDROID)

//   m_bWindowFrame = false;

//#else

  // m_bWindowFrame = true;

//#endif

   m_bLayered = true;

   m_ewindowflag |= e_window_flag_composite;

   m_pdocumenttemplate = nullptr;

}


simple_frame_window::~simple_frame_window()
{

}


void simple_frame_window::initialize(::object * pobject)
{

   //auto estatus = 
   
   ::experience::frame_window::initialize(pobject);

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


::user::enum_translucency simple_frame_window::get_translucency(::user::style* pstyle) const
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
   MESSAGE_LINK(e_message_move, pchannel, this, &simple_frame_window::on_message_move);

#ifdef WINDOWS_DESKTOP

   MESSAGE_LINK(e_message_get_min_max_info, pchannel, this, &simple_frame_window::_001OnGetMinMaxInfo);

#endif

   MESSAGE_LINK(e_message_mouse_move, pchannel, this, &simple_frame_window::on_message_mouse_move);
   MESSAGE_LINK(e_message_display_change, pchannel, this, &simple_frame_window::on_message_display_change);
   MESSAGE_LINK(e_message_show_window, pchannel, this, &simple_frame_window::on_message_show_window);
   MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &simple_frame_window::_001OnMouseActivate);
   MESSAGE_LINK(e_message_non_client_hittest, pchannel, this, &simple_frame_window::_001OnNcHitTest);

   MESSAGE_LINK(e_message_key_down, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_sys_key_down, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_key_up, pchannel, this, &simple_frame_window::_001OnKey);
   MESSAGE_LINK(e_message_sys_key_up, pchannel, this, &simple_frame_window::_001OnKey);

   add_command_prober("transparent_frame", this, &simple_frame_window::_001OnUpdateToggleTransparentFrame);
   add_command_handler("transparent_frame", this, &simple_frame_window::_001OnToggleTransparentFrame);

   add_command_prober("view_full_screen", this, &simple_frame_window::_001OnUpdateImpactFullScreen);
   add_command_handler("view_full_screen", this, &simple_frame_window::_001OnImpactFullScreen);

   add_command_handler("notify_icon_topic", this, &simple_frame_window::_001OnNotifyIconTopic);
   add_command_handler("app_exit", this, &simple_frame_window::on_message_app_exit);

#ifdef WINDOWS_DESKTOP


   MESSAGE_LINK(WM_APPEXIT, pchannel, this, &simple_frame_window::on_message_app_exit);
   MESSAGE_LINK(e_message_activate_app, pchannel, this, &simple_frame_window::_001OnActivateApp);

#endif

   MESSAGE_LINK(e_message_activate, pchannel, this, &simple_frame_window::_001OnActivate);
   MESSAGE_LINK(e_message_update_notify_icon, pchannel, this, &simple_frame_window::_001OnUpdateNotifyIcon);

}


void simple_frame_window::task_save_window_placement()
{

   ::output_debug_string("_task_save_window_rect start\n");

   auto ptask = ::get_task();

   while (ptask->task_get_run())
   {

      bool bIsWindow = (m_ewindowflag & e_window_flag_is_window);

      if (!bIsWindow)
      {

         break;

      }

      if (!m_pprimitiveimpl)
      {

         break;

      }

      bool bDestroying = m_pprimitiveimpl->is_destroying();

      if (bDestroying)
      {

         break;

      }

      if (m_durationLastSaveWindowRectRequest.elapsed() < 150_ms)
      {

         preempt(150_ms);

      }
      else if (m_bPendingSaveWindowRect)
      {

         task_intensive_save_window_placement();

         m_durationLastSaveWindowRect.Now();

      }
      else if (m_durationLastSaveWindowRect.elapsed() > 10_s)
      {

         break;

      }
      else
      {

         preempt(150_ms);

      }

   }

   ::output_debug_string("_task_save_window_rect end\n");

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

      if (m_durationLastSaveWindowRect.elapsed() < 300_ms)
      {

         continue;

      }

      try
      {

         m_bSizeMove = false;

         m_bPendingSaveWindowRect = false;

         WindowDataSaveWindowRect();

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

   synchronous_lock synchronouslock(mutex());

   if (!should_save_window_rect())
   {

      return;

   }

   m_bPendingSaveWindowRect = true;

   m_durationLastSaveWindowRectRequest.Now();

   __defer_branch(task_save_window_placement);

}


bool simple_frame_window::WindowDataLoadWindowRect()
{

   if (wfi_has_up_down())
   {

      if (!(m_uiUserInteractionFlags & ::user::e_interaction_wfi_up_down_loading))
      {

         __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading);

         bool bWfiDown = true;

         auto papp = get_app();

         papp->data_get("wfi_down", bWfiDown);

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
         INFORMATION("-------------------------------------------------------------------");
         INFORMATION("");
         INFORMATION("");
         INFORMATION("interaction_child::WindowDataLoadWindowRect (3)");
         INFORMATION("");
         INFORMATION("");

         return false;

      }

   }

   INFORMATION("-------------------------------------------------------------------");
   INFORMATION("");
   INFORMATION("");
   INFORMATION("interaction_child::WindowDataLoadWindowRect (4)");
   INFORMATION("");
   INFORMATION("");

   return ::experience::frame_window::WindowDataLoadWindowRect();

}


void simple_frame_window::WindowDataSaveWindowRect()
{

   if(wfi_has_up_down())
   {

      bool bDown;

      bDown = m_eupdown != e_updown_up;

      auto papp = get_app();

      papp->data_set("wfi_down", bDown);

   }

   return ::experience::frame_window::WindowDataSaveWindowRect();

}


bool simple_frame_window::_001OnBeforeAppearance()
{

   edisplay edisplay = const_layout().sketch().display();

   if (edisplay == ::e_display_up || edisplay == ::e_display_down)
   {


      initialize_frame_window_experience();

      //if (!initialize_frame_window_experience())
      //{

      //   return false;

      //}

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


void simple_frame_window::assert_ok() const
{

   ::user::frame_window::assert_ok();

}


void simple_frame_window::dump(dump_context & dumpcontext) const
{

   ::user::frame_window::dump(dumpcontext);

}


__pointer(::user::interaction) simple_frame_window::WindowDataGetWnd()
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

      synchronous_lock synchronouslock(mutex());

      try
      {

         auto psystem = m_psystem;

         auto pnode = psystem->node();

         pnode->node_send([this]()
         {

            if (m_pnotifyicon)
            {

               m_pnotifyicon->destroy_notify_icon();

               m_pnotifyicon.release();

            }

         });
         
      }
      catch (...)
      {

      }

   }

}


::experience::frame * simple_frame_window::frame_experience()
{

   auto psession = get_session();

   auto puser = psession->user();

   if(!puser || puser->experience() == nullptr)
   {

      return nullptr;

   }

   auto papp = get_app();

   if(papp->m_puserinteractionMain != nullptr)
   {

      __pointer(::simple_frame_window) pframe = papp->m_puserinteractionMain.get();

      if(pframe.is_set())
      {

         auto pschemaRef = pframe->m_pframe;

         if(pschemaRef.is_set())
         {

            auto pframe = ::experience::frame_window::frame_experience(pschemaRef->m_strExperience, pschemaRef->m_strFrameSchema);

            if(::is_set(pframe))
            {

               auto psignal = get_signal(id_user_style_change);

               psignal->add_handler(pframe);

               return pframe;

            }

         }

      }

   }

   auto pframe = ::experience::frame_window::frame_experience(m_varFrame["experience"], m_varFrame["schema"]);

   string strStyle;
   
   strStyle = m_varFrame["style"];

   auto psignal = get_signal(id_user_style_change);

   psignal->add_handler(pframe);

   if (strStyle.has_char())
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

      //return true;

      return;

   }

   __pointer(::experience::frame) pexperienceframe;

   try
   {

      pexperienceframe = ::move_transfer(frame_experience());

   }
   catch (const ::exception &)
   {

   }
   catch (...)
   {

      //return error_failed;

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

#if defined(_UWP) || defined(ANDROID) || defined(APPLE_IOS)

   return false;

#else

   return m_bDefaultNotifyIcon;

#endif

}


void simple_frame_window::on_message_create(::message::message * pmessage)
{

   if (pmessage->previous())
   {

      return;

   }

   __pointer(::message::create) pcreate(pmessage);

   auto pcreateContext = (::create *) pcreate->get_create();

   if (::is_set(pcreateContext))
   {

      __pointer(::user::system) pusersystem = pcreateContext->m_pmatterUserPayload;

      if (pusersystem)
      {

         if (pusersystem->m_bWindowFrame.is_set())
         {

            m_bWindowFrame = pusersystem->m_bWindowFrame;

         }

         //if (m_psystem->m_papexsystem->m_bPreferNoFrameWindow)
         //{

         //   m_bWindowFrame = false;

         //}

      }

   }
   //else
   //{

   //   m_bWindowFrame = m_psystem->m_papexsystem->m_bExperienceMainFrame;

   //}

   //__pointer(::user::place_holder) pplaceholder = get_parent();

   //if (pplaceholder != nullptr)
   //{

   //   __pointer(::user::place_holder_container) pcontainer = pplaceholder->get_parent();

   //   if (pcontainer != nullptr)
   //   {

   //      pcontainer->on_place_hold(this, pplaceholder);

   //   }

   //}

   auto papp = get_app();

   if (m_bWindowFrame.is_none())
   {

      auto& bApplicationExperienceMainFrame = papp->m_bExperienceMainFrame;

      if(bApplicationExperienceMainFrame.is_set())
      {

         if (get_parent() == nullptr)
         {

            m_bWindowFrame = bApplicationExperienceMainFrame;

         }
         else
         {

            m_bWindowFrame = false;

         }

      }
      else
      {

#if defined(_UWP) || defined(APPLE_IOS) || defined(ANDROID)

         m_bWindowFrame = false;

#else

         m_bWindowFrame = get_parent() == nullptr || wfi_has_up_down();

#endif

      }

   }

   //if (m_psystem->m_papexsystem->m_bPreferNoFrameWindow)
   //{

   //   m_bWindowFrame = false;

   //}

   //if (m_bWindowFrame || m_bFramePayloadFlags)
   {

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

//#if !defined(APPLE_IOS) && !defined(ANDROID)

         if (m_pdocumenttemplate->m_atom.has_char())
         {

            ::file::path pathFrameJson = "matter://" + m_pdocumenttemplate->m_atom + "/frame.network_payload";

            auto pcontext = get_context();

            m_varFrame = pcontext->m_papexcontext->file().safe_get_network_payload(pathFrameJson);

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

   on_select_user_style();

   if (get_parent() == nullptr)
   {

      if (m_ebuttonaHide.contains(::experience::e_button_transparent_frame))
      {

         erase_appearance(e_appearance_transparent_frame);

      }

   }

   //if (m_bWindowFrame)
   //{
      
      initialize_frame_window_experience();

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

      m_pprimitiveimpl->show_task(m_bShowTask);

   }

   auto textAppTitle = papp->m_textAppTitle;

   string strAppTitle;

   if (textAppTitle.get_text().has_char())
   {

      strAppTitle = textAppTitle.get_text();

   }
   else
   {

      string_array stra;

      stra.explode("/", papp->m_strAppId);

      strAppTitle = stra.slice(1).implode(" ");

      strAppTitle.replace_with(" ", "_");

      strAppTitle.replace_with(" ", "-");

      strAppTitle.replace_with(" ", ".");

   }

#if !defined(_UWP) && !defined(ANDROID) && !defined(APPLE_IOS)

   if (!(m_ewindowflag & e_window_flag_window_created))
   {

      if (m_bDefaultNotifyIcon)
      {

         //auto psystem = m_psystem->m_papexsystem;

         //auto estatus = 
         
         __defer_construct(m_pnotifyicon);

         //if (estatus.succeeded())
         {

            //m_pnotifyicon->m_puserinteraction = this;

            index iNotifyIconItem = 0;

            m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, strAppTitle, "notify_icon_topic");

            auto c = papp->applicationmenu().get_count();

            for (auto i = 0; i < c; i++)
            {

               auto & item = papp->applicationmenu()[i];

               m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, item.m_strName, item.m_strId);

            }

            if (m_pframe != nullptr
               && m_pframe->get_control_box() != nullptr
               && m_pframe->get_control_box()->has_button(::experience::e_button_transparent_frame))
            {

               m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, "separator");

               m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, _("Transparent Frame"), "transparent_frame");

            }

            m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, "separator");

            m_pnotifyicon->notify_icon_insert_item(iNotifyIconItem, _("Exit"), "app_exit");

            post_message(e_message_update_notify_icon);

         }

      }

   }

#endif

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

   __pointer(::message::show_window) pshow(pmessage);

   if(pshow->m_bShow)
   {

      output_debug_string("\nsimple_frame_window::on_message_show_window true : " + __type_name(this) + "\n");

      //defer_set_icon();

   }
   else
   {

      output_debug_string("\nsimple_frame_window::on_message_show_window false :" + __type_name(this) + "\n");

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



void simple_frame_window::on_message_display_change(::message::message * pmessage)
{

   __pointer(::user::message) pusermessage(pmessage);

   if (is_top_level())
   {

      ::e_display edisplay = const_layout().sketch().display();

      display(edisplay, e_activation_display_change);

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

   //m_durationLastVisualChange.Now();

   //if (get_parent() == nullptr)
   //{

   //   defer_save_window_placement();

   //}

}


void simple_frame_window::on_message_move(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   m_durationLastVisualChange.Now();


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

   ::create * pcreateContext = pusersystem->m_pcreate;

   if(pcreateContext && would_display_notify_icon())
   {

      __pointer(::user::system) pusersystem = pcreateContext->m_pmatterUserPayload;

      __pointer(::user::document) pdocument = pusersystem->m_pdocumentCurrent;

      if (pdocument->get_document_template()->m_bHiddenOnNotifyIcon)
      {

         //display(::e_display_hide);

         //set_need_redraw();

         //post_redraw();

         pcreateContext->m_bMakeVisible = false;

         //pusersystem->m_createstruct.style &= ~WS_VISIBLE;

      }

   }

   return true;

}


void simple_frame_window::on_layout(::draw2d::graphics_pointer & pgraphics)
{

   if (__type_name(this).contains_ci("child_frame"))
   {

      output_debug_string("%child_frame%\n");

   }

   auto papp = get_app();

   if (papp->m_bExperienceMainFrame.is_false() && get_parent() == nullptr)
   {

      auto rectangle = get_host_window()->get_client_rect();

      place(rectangle);

   }

   if (is_frame_experience_enabled())
   {

      ::experience::frame_window::on_layout(pgraphics);

   }
   else
   {

      ::user::frame_window::on_layout(pgraphics);

   }

   m_durationLastVisualChange.Now();


}


void simple_frame_window::on_reposition()
{

   //if (m_bWindowFrame)
   //{

   //   on_layout(pgraphics);

   //}

   ::user::frame_window::on_reposition();

   m_durationLastVisualChange.Now();


}


void simple_frame_window::ImpactOnActivateFrame(__pointer(::user::impact) pimpact, ::u32 user, __pointer(::user::interaction) pframe)
{
   __UNREFERENCED_PARAMETER(pimpact);
   __UNREFERENCED_PARAMETER(user);
   __UNREFERENCED_PARAMETER(pframe);
   //   if(pimpact != nullptr)
   //      pimpact->OnActivateFrame(WA_INACTIVE, (__pointer(::user::simple_frame_window)) pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(::message::message * pmessage)
{

#ifdef WINDOWS_DESKTOP
   
   //__pointer(::user::message) pusermessage(pmessage);

   //MINMAXINFO * pMMI = (MINMAXINFO *) pusermessage->m_lparam.m_lparam;

   //if (layout().is_full_screen())
   //{

   //   pMMI->ptMaxSize.y = m_FullScreenWindowRect.height();

   //   pMMI->ptMaxTrackSize.y = pMMI->ptMaxSize.y;

   //   pMMI->ptMaxSize.x = m_FullScreenWindowRect.width();

   //   pMMI->ptMaxTrackSize.x = pMMI->ptMaxSize.x;

   //}

#else
   throw ::exception(todo);
#endif
}


void simple_frame_window::show_control_bars(const ::e_display & edisplay, bool bLeaveFullScreenBarsOnHide)
{

   for(auto & toolbartransport : m_mapToolbar.values())
   {

      try
      {

         if(toolbartransport)
         {

            if ((is_screen_visible(edisplay) || (!toolbartransport->m_bFullScreenBar || !bLeaveFullScreenBarsOnHide)))
            {

               enum_activation eactivation = e_activation_default;

               toolbartransport->display(edisplay, eactivation);

            } else
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
   
   if(!m_bTransparentFrameEnable)
   {
      
      return false;
      
   }
   
   auto eappearance = const_layout().design().appearance();

   if(eappearance & ::e_appearance_transparent_frame)
   {
      
      return true;
      
   }
   
   return false;

}


void simple_frame_window::_001OnExitFullScreen()
{

   show_control_bars();

   ::experience::frame_window::_001OnExitFullScreen();

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

   __pointer(::message::nc_hit_test) pnchittest(pmessage);

   pnchittest->set_hit_test(e_hit_test_client);

   pnchittest->m_bRet = true;

}


void simple_frame_window::_001OnMouseActivate(::message::message * pmessage)
{

   __pointer(::message::mouse_activate) pmouseactivate(pmessage);

   pmouseactivate->m_lresult = e_mouse_activate;

   pmouseactivate->m_bRet = true;

}


void simple_frame_window::_001OnUpdateImpactFullScreen(::message::message * pmessage)
{
   
   __pointer(::message::command) pcommand(pmessage);
   
   pcommand->enable();
   
   pcommand->_001SetCheck(layout().is_full_screen());
   
   pcommand->m_bRet = true;

}


void simple_frame_window::ToggleFullScreen()
{

   if (layout().is_full_screen())
   {

      display(e_display_restored);

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
   
   __pointer(::message::command) pcommand(pmessage);
   
   pcommand->enable();
   
   pcommand->_001SetCheck(m_bWindowFrame);

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

   __pointer(::message::command) pcommand(pmessage);

   pcommand->enable();

   //if (top_level_frame()->frame_is_transparent())
   //{

   //   MessageBox(nullptr, "ft", "", e_message_box_ok);

   //}
   //else
   //{

   //   MessageBox(nullptr, "fnt", "", e_message_box_ok);

   //}

   pcommand->_001SetCheck(frame_is_transparent());

}


void simple_frame_window::ActivateFrame(edisplay edisplay)
{

   ::user::frame_window::ActivateFrame(edisplay);

}


void simple_frame_window::GetBorderRect(RECTANGLE_I32 * prectangle)
{

   *prectangle = m_rectangleBorder;

}


void simple_frame_window::SetBorderRect(const ::rectangle_i32 & rectangle)
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

      string strImpact = m_atom;

      bool bShow = false;

      auto papp = get_app();

      if (::str().ends_eat_ci(strImpact, "::frame"))
      {

         papp->data_set("frame::" + strImpact + ".visible", bShow);

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

   if (m_varFrame["hide_on_close"].is_true())
   {

      display(e_display_none);

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

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      if(edesktop == ::user::e_desktop_unity_gnome
            || edesktop == ::user::e_desktop_ubuntu_gnome)
      {

         display(e_display_none);

      }
      else
      {

         display(e_display_iconic);

      }
#else

      if(is_window_visible())
      {

         hide();

         set_need_redraw();

         post_redraw();

      }

#endif // LINUX

      set_tool_window();

      return;

   }

   if (m_bModal)
   {

      EndModalLoop(m_nModalResult);

      pmessage->m_bRet = true;

      return;

   }
   else if (top_level_frame() != nullptr && top_level_frame()->m_bModal)
   {

      top_level_frame()->EndModalLoop(m_nModalResult);

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
      else if(papp->on_close_frame_window(this))
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

   //__pointer(::user::message) pusermessage(pmessage);

   //pusermessage->previous();

   //bool bActive = pusermessage->m_wparam != false;

   //if (get_parent() == nullptr && m_bCompositedFrameWindow)
   //{

   //   //if (bActive)
   //   //{

   //   //   if (layout().is_iconic())
   //   //   {

   //   //      display(e_display_restored);

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

   //__pointer(::message::activate) pactivate(pmessage);

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


bool simple_frame_window::LoadFrame(const ::string & pszMatter, u32 dwDefaultStyle, ::user::interaction * puiParent, ::user::system * pusersystem)
{

   m_atom = pusersystem->m_atom.to_string() + "::frame";

   __UNREFERENCED_PARAMETER(puiParent);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   auto papp = get_app();

   if (puiParent == nullptr)
   {

      puiParent = papp->get_request_parent_ui(this, pusersystem);

   }

   ::rectangle_i32 rectangleFrame;

   __pointer(::user::place_holder) pholder;

   if(puiParent != nullptr && (pholder = puiParent).is_set())
   {

      pholder->get_client_rect(rectangleFrame);

   }

   //m_bLockSketchToDesign = true;

   if(puiParent == nullptr || wfi_has_up_down())
   {

      if (wfi_has_up_down() && ::is_set(puiParent) && puiParent->m_bWfiUpDownTarget)
      {

         m_pupdowntarget = puiParent;

      }

      if(should_save_window_rect())
      {

         //bool bForceRestore = false;

         //bool bInitialFramePosition = true;

         //m_puserinteractionParent = puiParent;

         //WindowDataLoadWindowRect(bForceRestore, bInitialFramePosition);

         //_001FancyInitialFramePlacement();

         initial_frame_placement();

         rectangleFrame = screen_rect();

         FORMATTED_INFORMATION("simple_frame_window::LoadFrame rectangleFrame (l=%d, t=%d) (w=%d, h=%d)", rectangleFrame.left, rectangleFrame.top, rectangleFrame.width(), rectangleFrame.height());
         FORMATTED_INFORMATION("simple_frame_window::LoadFrame edisplay=%s", __c_str(const_layout().sketch().display().eflag()));

         if (wfi_has_up_down())
         {

            if (m_eupdown == e_updown_up)
            {

               puiParent = nullptr;

            }
            else if (m_eupdown == e_updown_down)
            {

               __pointer(::user::document) pdocument = pusersystem->m_pdocumentCurrent;

               __pointer(::user::impact_host) pimpacthost;

               if (pimpacthost.is_set())
               {

                  puiParent = pimpacthost->updown_target_get_place_holder(this, pdocument);

               }

            }

         }

      }

      if(is_top_level())
      {

         if(m_ewindowflag & e_window_flag_main_frame)
         {

            display(e_display_zoomed);

          //  psession->get_main_workspace(rectangleFrame);

         }

      }

      rectangleFrame = screen_rect();

      //pusersystem->set_rect(rectangleFrame);

      FORMATTED_INFORMATION("(2) simple_frame_window::LoadFrame rectangleFrame (l=%d, t=%d) (w=%d, h=%d)", rectangleFrame.left, rectangleFrame.top, rectangleFrame.width(), rectangleFrame.height());
      FORMATTED_INFORMATION("(2) simple_frame_window::LoadFrame edisplay=%s", __c_str(const_layout().sketch().display().eflag()));


   }

   if (puiParent != nullptr)
   {

      //pusersystem->m_createstruct.style |= WS_CHILD;

   }

   m_bEnableSaveWindowRect2 = false;

   bool bLoadImplRect = m_ewindowflag & e_window_flag_load_window_rect_on_impl;

   m_ewindowflag -= e_window_flag_load_window_rect_on_impl;

   //bool bCreated = create_window_ex(pusersystem, puiParent, m_atom);

   //bool bCreated;

   m_pusersystem = pusersystem;

   //bCreated = 
   
   create_interaction(puiParent, atom());

   if (bLoadImplRect)
   {

      m_ewindowflag += e_window_flag_load_window_rect_on_impl;

   }

   //if (!bCreated)
   //{

   //   return false;   // will self destruct on failure normally

   //}

   if (pusersystem == nullptr)   // send initial update
   {

      send_message_to_descendants(e_message_system_update, INITIAL_UPDATE, (lparam)0, true, true);

   }
   
   if (pusersystem->m_pcreate->m_bMakeVisible)
   {

      initial_frame_display();

   }

   return true;

}


void simple_frame_window::_001OnDdeInitiate(::message::message * pmessage)
{

   //__pointer(::user::message) pusermessage(pmessage);

   //pusermessage->set_lresult(default_window_procedure((u32)pusermessage->m_wparam, pusermessage->m_lparam, pusermessage->get_lresult()));

}


void simple_frame_window::_001OnKey(::message::message * pmessage)
{


}


void simple_frame_window::pre_translate_message(::message::message * pmessage)
{

   if(pmessage->m_atom == e_message_display_change)
   {

      display();

   }
   else if (pmessage->m_atom == e_message_mouse_move)
   {

   }

   return ::experience::frame_window::pre_translate_message(pmessage);

}


void simple_frame_window::on_frame_position()
{

   display(e_display_default, e_activation_set_active);

   order_top();

   if (is_frame_experience_enabled())
   {

      if (const_layout().design().display() == ::e_display_iconic)
      {

         display(e_display_restored);

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
//   //if (m_psystem->m_papexsystem->m_bPreferNoFrameWindow)
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
//            WindowDataLoadWindowRect(bForceRestore, true);
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

   auto psession = get_session();

   if(get_app() == nullptr
         || get_app()->get_session() == nullptr
         || psession->m_psavings == nullptr)
   {

      return;

   }

   if (psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing)
         || psession->m_paurasession->savings().is_trying_to_save(::e_resource_translucent_background))
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      pgraphics->fill_rectangle(rectangleClient, rgb(0, 0, 0));

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

      synchronous_lock synchronouslock(mutex());

      if (m_pprimitiveimpl->m_puserinteraction == nullptr)
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

   ::rectangle_i32 rectangleClient;

   get_client_rect(rectangleClient);

   bool bDib = false;

   double dAlpha = get_alpha();

   ::draw2d::graphics_pointer & pgraphics = pgraphicsParam;

   if(dAlpha == 0.0)
   {

      windowing_output_debug_string("Alpha is Zero\n");

   }

   if(rectangleClient.area() > 0 && dAlpha > 0.0 && dAlpha < 1.0 && m_bTransparent)
   {

      //auto estatus = 
      __defer_construct(m_pimageAlpha);

      //if(estatus.succeeded())
      //{

         //estatus = 
      m_pimageAlpha->create(rectangleClient.size());

      //   if(estatus.succeeded())
         {

            m_pimageAlpha->fill(0, 0, 0, 0);

            pgraphics = m_pimageAlpha->get_graphics();

            pgraphics->set_origin(pgraphics->get_origin());

            bDib = true;

         }

      //}

   }

   //::user::style_context style(this);

   {

#ifdef VERBOSE_LOG

      ::duration t1 = ::duration::now();
      
#endif

      //pinteraction->_001OnDraw(pgraphics);
      if(dAlpha > 0.0)
      {

         bool bBlurBackground = get_draw_flags(pstyle).has(::user::e_flag_blur_background);

         int iDrawingOrder = DRAWING_ORDER_CLIENT_OVER;

         if (!bBlurBackground)
         {

            iDrawingOrder = get_int(pstyle, ::user::e_int_top_level_drawing_order);

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

         pgraphics->fill_solid_rect_dim(0, 0, 100, 100, argb(128, 255, 0, 0));

#endif

         string strType = __type_name(this);

#ifdef VERBOSE_LOG

         ::duration d1 = t1.elapsed();

         if(d1 > 50_ms)
         {

            CATEGORY_INFORMATION(prodevian, "(more than 50ms) " << strType << "::_001OnDraw took " << integral_millisecond(d1) << "::duration.\n");

         }

#endif

         if (iDrawingOrder == DRAWING_ORDER_CLIENT_OVER)
         {

            _001DrawThis(pgraphics);

            _001DrawChildren(pgraphics);

         }
         else
         {

#ifdef VERBOSE_LOG

            ::duration t1 = ::duration::now();
            
#endif

            draw_frame_and_control_box_over(pgraphics);

#ifdef VERBOSE_LOG

            auto d1 = t1.elapsed();

            if(d1 > 50_ms)
            {

               CATEGORY_INFORMATION(prodevian, "(more than 50ms) draw_frame_and_control_box_over took " << d1.integral_millisecond() << "::duration.\n");

            }

#endif

         }

      }

      _008CallOnDraw(pgraphics);

#if TEST

      pgraphics->fill_solid_rect_dim(0, 100, 100, 100, argb(128, 0, 0, 255));

#endif

   }

   if(bDib)
   {

      pgraphicsParam->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      image_source imagesource(pgraphics);

      image_drawing_options imagedrawingoptions(rectangleClient.size());

      image_drawing imagedrawing(imagedrawingoptions, imagesource);
      
      imagedrawing.opacity(dAlpha);

      pgraphicsParam->draw(imagedrawing);

   }

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

   auto pstyle = get_style(pgraphics);

   bool bBlurBackground = get_draw_flags(pstyle).has(::user::e_flag_blur_background);

   if(bBlurBackground)
   {

      //printf("simplefrmwnd : " + __type_name(this) + " : blur_background");

      //auto psystem = m_psystem->m_pbasesystem;

//      class imaging & imaging = psystem->imaging();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      //rectangleClient.offset(rectangleClient.top_left());

      auto psession = get_session();

      if(psession->m_paurasession->savings().is_trying_to_save(::e_resource_translucent_background))
      {

         //pgraphics->fill_rectangle(rectangleClient, rgb(150, 220, 140));

      }
      else if(psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing)
              || psession->m_paurasession->savings().is_trying_to_save(::e_resource_blur_background))
      {

         pgraphics->fill_rectangle(rectangleClient, argb(150, 150,180,140));

      }
      else
      {

#ifndef LINUX

         //printf("simplefrmwnd : " + __type_name(this) + " : ifndef LINUX");

         if(rectangleClient.size() != m_pimageBk->size())
         {
            m_pimageBk->create(rectangleClient.size());
            m_pimageBk->fill(0,200,200,190);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::draw2d::fastblur *( *pfnNew )(__pointer(::aura::application)) = (::draw2d::fastblur *(*)(__pointer(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");
            //m_pimageBlur->create(this);
            //m_fastblur.initialize(rectangleClient.size(),2);

            m_pimageBlur->create(rectangleClient.size());

         }

         if(m_pimageBlur->is_ok())
         {

            ::rectangle_f64 rectangleTarget(rectangleClient.size());
            
            {
               
               image_source imagesource(pgraphics);
               
               image_drawing_options imagedrawingoptions(rectangleTarget);
               
               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               m_pimageBlur->g()->draw(imagedrawing);
               
            }

            m_pfastblur->blur(m_pimageBlur, 2);
            
            {
               
               image_source imagesource(m_pimageBk);

               image_drawing_options imagedrawingoptions(rectangleClient.size());
            
               imagedrawingoptions.opacity(49);
               
               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               m_pimageBlur->draw(imagedrawing);
               
            }
            
            {
               
               image_source imagesource(m_pimageBlur);
               
               image_drawing_options imagedrawingoptions(rectangleClient);
               
               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               pgraphics->draw(imagedrawing);
               
            }

         }

#endif

      }

   }

   //printf("simplefrmwnd : " + __type_name(this) + " : draw_frame");

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


bool simple_frame_window::on_set_parent(::user::primitive * puiParent)
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


void simple_frame_window::get_client_rect(RECTANGLE_I32 * prectangle)
{

//   if (m_bWindowFrame && m_pframe != nullptr && !layout().is_full_screen() && !frame_is_transparent())
//   {
//
//      m_pframe->get_window_client_rect(prectangle);
//
//   }
//   else
//   {

      ::experience::frame_window::get_client_rect(prectangle);

//   }

}


bool simple_frame_window::is_application_main_window()
{

   auto papp = get_app();

   return papp->m_puserinteractionMain == this;

}




void simple_frame_window::defer_create_notification_icon()
{

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   windowing_post([this]
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
         
         __construct(m_piconNotify);

         //if(estatus.succeeded())
         {

            //const char * pszAppName = papp->m_strAppName;

            m_piconNotify->load_app_tray_icon(get_app()->m_strAppId);

         }

      }

      __defer_construct(m_pnotifyicon);

      //m_pnotifyicon->m_puserinteraction = this;
      m_pnotifyicon->create_notify_icon("(application_default_notify_icon)", this, m_piconNotify);
      //if (!)
      //{

      //   m_pnotifyicon.release();

      //   return;

      //}

      m_bitMinimizeToTray.defer(e_boolean_true);

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

   __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading);

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


void simple_frame_window::design_up()
{

   m_eupdown = e_updown_up;

   if (m_pframe)
   {

      m_pframe->get_control_box()->set_need_layout();

   }

   __keep_on(&m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading);

   frame_Detach();

   if (m_pupdowntarget->m_uiUserInteractionFlags & ::user::e_interaction_wfi_up_tool_window)
   {

      set_tool_window();

   }

}


//bool simple_frame_window::create_interaction(const ::string & pszClassName, const ::string & pszWindowName, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, const ::string & pszMenuName, u32 dwExStyle, ::create * pcreate)
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
//   SetActiveWindow();      // activate us first !
//   ::u32 nFiles = ::DragQueryFile(hDropInfo, (::u32)-1, nullptr, 0);
//
//   ::file::path_array patha;
//
//   natural_wstring pwszFileName(char_count, _MAX_PATH);
//
//   for (::u32 iFile = 0; iFile < nFiles; iFile++)
//   {
//
//      if (::DragQueryFileW(hDropInfo, iFile, pwszFileName, _MAX_PATH))
//      {
//
//         patha.add(__string(pwszFileName));
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
//   const char * psz = (const ::string &)GlobalLock(hData);
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
//                                (::u32)0x8000, (uptr)hData));
//
//   // don't execute the command when the u is disabled
//   if (!is_window_enabled())
//   {
//      TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: DDE command '%s' ignored because u is disabled.\n",
//            string(strCommand).c_str());
//      return 0;
//   }
//
//   // execute the command
//   //LPWSTR pszCommand = strCommand.alloc(strCommand.get_length());
//
//   //if (!psystem->OnDDECommand(pszCommand))
//
//   //   TRACE(trace_category_appmsg, e_trace_level_warning, "Error: failed to execute DDE command '%s'.\n", pszCommand);
//
//   //strCommand.release_string_buffer();
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
//void simple_frame_window::NotifyFloatingWindows(u32 dwFlags)
//{
//   ASSERT_VALID(this);
//   // trans   ASSERT(get_handle() != nullptr);
//
//   // get top level parent frame u first unless this is a child u
//   __pointer(::user::frame_window) pParent = (GetStyle() & WS_CHILD) ? this : top_level_frame();
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
//   __pointer(::user::interaction) oswindowDesktop = papp->get_desktop_window();
//
//   if (oswindowDesktop.is_null())
//      return;
//
//   __pointer(::user::interaction) oswindow = oswindowDesktop->get_wnd(GW_CHILD);
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

   __pointer(::user::message) pusermessage(pmessage);

   auto papp = get_app();

   if (::is_set(papp) && papp->m_puserinteractionMain == this)
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

   if (ptopic->m_atom == id_task_bar_created)
   {

      defer_create_notification_icon();

   }
   else if(ptopic->user_interaction() == m_pnotifyicon)
   {

      if(ptopic->m_atom == ::id_context_menu)
      {

         //OnNotifyIconContextMenu(ptopic->m_puserelement->m_atom);

         auto pointCursor = get_cursor_position();

         string strXml = notification_area_get_xml_menu();

         auto psession = get_session();

         auto puser = psession->user();

         puser->track_popup_xml_menu(this, strXml, 0, pointCursor, size_i32(), m_pnotifyicon);

      }
      else if(ptopic->m_atom == ::id_left_button_double_click)
      {

         //OnNotifyIconLButtonDblClk(ptopic->m_puserelement->m_atom);

      }
      else if(ptopic->m_atom == ::id_left_button_down)
      {

         //OnNotifyIconLButtonDown(ptopic->m_puserelement->m_atom);

         default_notify_icon_topic();

      }

   }


//#endif

   ::experience::frame_window::handle(ptopic, pcontext);

   if(ptopic->m_bRet)
   {

      return;

   }

   return ::user::frame_window::handle(ptopic, pcontext);

}


string simple_frame_window::get_window_default_matter()
{

   if (m_pdocumenttemplate == nullptr)
   {

      return frame_window::get_window_default_matter();

   }

   return m_pdocumenttemplate->m_atom;

}


//void simple_frame_window::guserbaseOnInitialUpdate(::message::message * pmessage)
//{
//   __pointer(::user::message) pusermessage(pmessage);
//   ::user::FrameInitialUpdate * pfiu = (::user::FrameInitialUpdate *)pusermessage->m_lparam.m_lparam;
//   if (pfiu != nullptr)
//   {
//      __pointer(::user::frame_window) pframe = (this);
//      // if the frame does not have an active ::user::impact, set to first pane
//      __pointer(::user::impact) pimpact;
//      if (pframe->get_active_impact() == nullptr)
//      {
//         __pointer(::user::interaction) pwindow = pframe->get_child_by_id(FIRST_PANE);
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
//         edisplay edisplay = e_display_default;      // default
//         ::aura::application* pApp = System;
//         if (pApp != nullptr && pApp->m_puiMain == pframe)
//         {
//            edisplay = psystem->m_edisplay; // use the parameter from WinMain
//            psystem->m_edisplay = e_display_undefined; // set to default after first time
//         }
//         bool bFullScreen;
//         data_get("FullScreen", bFullScreen);
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
//      __pointer(::user::document) pdocument = pfiu->m_pdocument;
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

   auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //{

   //   synchronous_lock synchronouslock(mutex());

   //   uia = m_uiptraChild;

   //}

   if(puserinteractionpointeraChild)
   {

      ::draw2d::savedc k(pgraphics);

      //on_context_offset(pgraphics);
      //if (0)
      {

         try
         {

            for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
            {

               auto pcontrolbox = pinteraction->cast < ::experience::control_box >();

               if (!pcontrolbox)
               {

                  {

                     ::duration t1 = ::duration::now();

                     pinteraction->_000CallOnDraw(pgraphics);

                     ::duration d1 = t1.elapsed();

                     if(d1 > 50_ms)
                     {

                        string strType = __type_name(pinteraction);

                        //if(strType.contains("pane_impact"))
                        //{

                          // output_debug_string("paneimpact\n");

                        //}

#ifdef VERBOSE_LOG                        

                        CATEGORY_INFORMATION(prodevian, "(more than 50ms) " << strType << "::_001OnDraw took " << integral_millisecond(d1) << "::duration.");

#endif

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

#ifdef VERBOSE_LOG

      ::duration t1 = ::duration::now();

#endif

      _001DrawThis(pgraphics);

      //return; // abcxxx

#ifdef VERBOSE_LOG

      ::duration d1 = t1.elapsed();

      if(d1 > 50_ms)
      {

         CATEGORY_INFORMATION(prodevian, "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << "::duration.\n");

      }

#endif

   }

   ::duration tx = ::duration::now();

   bool bTransparentFrame = frame_is_transparent();

   bool bActive = is_active_window();

   ::duration taxw = ::duration::now();

   ::duration daxw = taxw.elapsed();

   if(daxw > 50_ms)
   {

      output_debug_string("what???axxw\n");

   }

   ::duration txx = ::duration::now();

   if (m_bWindowFrame && (!bTransparentFrame || bActive))
   {

      ::draw2d::savedc k(pgraphics);

      //on_context_offset(pgraphics);

      try
      {

         if (puserinteractionpointeraChild)
         {

            for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
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

#ifdef VERBOSE_LOG

                        ::duration t1 = ::duration::now();
                        
#endif

                        pinteraction->_000CallOnDraw(pgraphics);

#ifdef VERBOSE_LOG

                        ::duration d1 = t1.elapsed();

                        if (d1 > 50_ms)
                        {

                           CATEGORY_INFORMATION(prodevian, "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << ".\n");

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

   auto dxx = txx.elapsed();

   if(dxx > 50_ms)
   {

      //output_debug_string("what???xx");

   }

   auto Δx = tx.elapsed();
   if(Δx > 50_ms)
   {

      //output_debug_string("what???");

   }

   {

#ifdef VERBOSE_LOG

      ::duration t1 = ::duration::now();
      
#endif

      _008CallOnDraw(pgraphics);

#ifdef VERBOSE_LOG

      ::duration d1 = t1.elapsed();

      if(d1 > 50_ms)
      {

         CATEGORY_INFORMATION(prodevian, "(more than 50ms) simple_frame_windows::_001DrawThis took " << integral_millisecond(d1) << ".\n");

      }

#endif

   }

   //pgraphics->fill_solid_rect_dim(200, 200, 1600, 800, argb(128, 200, 240, 150));

}


void simple_frame_window::draw_frame(::draw2d::graphics_pointer & pgraphics)
{

   auto psession = get_session();

   if (m_bWindowFrame && !psession->m_paurasession->savings().is_trying_to_save(::e_resource_display_bandwidth))
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
//      __pointer(::user::interaction) puserinteractionParentFrame = get_parent_frame();
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
//         display(e_display_restored);
//         return true;
//      }
//      __pointer(::user::interaction) puserinteractionParentFrame = get_parent_frame();
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
//   auto psession = get_session();
//
//   if (m_bLayered && get_translucency(pstyle) != ::user::e_translucency_none)
//   {
//      return !psession->m_paurasession->savings().is_trying_to_save(::e_resource_processing)
//             && !psession->m_paurasession->savings().is_trying_to_save(::e_resource_display_bandwidth);
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

   __pointer(database::change_event) pupdate(pmessage);

   if (pupdate->m_datakey == "ca2.savings")
   {

      //defer_synch_layered();

   }

}




void simple_frame_window::on_simple_command(::message::simple_command * psimplecommand)
{

   ::user::frame_window::on_simple_command(psimplecommand);

}


class ::mini_dock_frame_window* simple_frame_window::CreateFloatingFrame(u32 uStyle)
{

   __UNREFERENCED_PARAMETER(uStyle);

   return nullptr;

}


















//bool simple_frame_window::display(edisplay edisplay)
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


bool simple_frame_window::keyboard_focus_is_focusable() const
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

      ::atom atom = m_pdocumenttemplate->m_atom;

      if (atom.has_char())
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


void simple_frame_window::_001OnTimer(::timer * ptimer)
{

   ::user::frame_window::_001OnTimer(ptimer);

   ::experience::frame_window::_001OnTimer(ptimer);

}


//void simple_frame_window::OnNotifyIconContextMenu(::u32 uNotifyIcon)
//{
//
//}



//
//void simple_frame_window::OnNotifyIconLButtonDblClk(::u32 uNotifyIcon)
//{
//
//   __UNREFERENCED_PARAMETER(uNotifyIcon);
//
//}
//
//
//void simple_frame_window::OnNotifyIconLButtonDown(::u32 uNotifyIcon)
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

   if(m_bDefaultNotifyIcon)
   {

      default_notify_icon_topic();

   }

   if(pmessage)
   {

      pmessage->m_bRet = true;

   }

}


void simple_frame_window::default_notify_icon_topic()
{

   frame_toggle_restore();

}


void simple_frame_window::OnInitialFrameUpdate(bool bMakeVisible)
{

   if(!m_bDefaultNotifyIcon)
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

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   if (m_pprimitiveimpl == nullptr)
   {

      return;

   }

#ifdef LINUX


   m_pprimitiveimpl->show_task(bVisible && m_bShowTask);

#else

   m_pprimitiveimpl->show_task(bVisible && m_bShowTask
                      && !layout().is_iconic());

#endif

}


void simple_frame_window::show_task(bool bShow)
{

   if (m_pprimitiveimpl == nullptr)
   {

      return;

   }

   m_pprimitiveimpl->show_task(bShow);

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

   if (m_puserstyle.is_null())
   {

      string strSchema(m_varFrame["experience"].get_string());

      if (strSchema.has_char() || is_top_level_window())
      {

         auto psession = get_session();
         
         auto puser = psession->user();

         auto pstyle = puser->get_user_style(strSchema, get_app());

         __refer(m_puserstyle, pstyle);

      }

   }

}


void simple_frame_window::call_notification_area_action(const ::string & pszId)
{

   ::atom atom(pszId);

   post_procedure([this, atom]()
   {

      handle_command(atom);

   });

}


void simple_frame_window::notification_area_action(const ::string & pszId)
{

   __pointer(::user::interaction) pinteraction = this;

   ::message::command command((::atom) pszId);

   pinteraction->_001SendCommand(&command);

}


string simple_frame_window::notification_area_get_xml_menu()
{

   auto pdocument = __create_new<::xml::document>();

   pdocument->create_root("menu");

   for (auto & pitem : m_pnotifyicon->m_notifyiconitema)
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

   if (get_parent() == nullptr)
   {

      if (m_ewindowflag & e_window_flag_auto_store_window_rect)
      {

         if (m_ewindowflag & e_window_flag_pending_save_window_rect)
         {

            defer_save_window_placement();

         }

      }

      m_ewindowflag -= e_window_flag_loading_window_rect;

   }

}


void simple_frame_window::_001OnAfterAppearance()
{

   ::experience::frame_window::_001OnAfterAppearance();

}




