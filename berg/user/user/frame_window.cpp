#include "framework.h"
#include "frame_window.h"
#include "document.h"
#include "impact.h"
#include "impact_host.h"
#include "impact_system.h"
#include "toolbar.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"
#include "acme/constant/user_key.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/task_flag.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/user/user/_text_stream.h"
#include "acme/user/user/activation_token.h"
#include "apex/message/simple_command.h"
#include "apex/platform/savings.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/message/user.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/user/user/copydesk.h"
#include "aura/user/user/style.h"
#include "aura/user/user/system.h"
#include "berg/user/user/place_holder.h"
#include "berg/platform/application.h"
#include "berg/platform/session.h"


namespace user
{


   frame_window::frame_window()
   {

      m_puserframewindow = this;

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_einteraction -= ::user::e_interaction_system_context_menu;

      m_pviewMain = nullptr;
      //m_bAutoWindowFrame = true;
      //m_bWindowFrame = true;
      m_nWindow = -1;                 // unknown interaction_impl ID
      m_bAutoMenuEnable = true;       // auto enable on by default
      //m_lpfnCloseProc = nullptr;
//#ifdef WINDOWS_DESKTOP
//      m_hMenuDefault = nullptr;
//      m_hAccelTable = nullptr;
//#endif
      //m_nIDHelp = 0;
      m_nIDTracking = 0;
      m_nIDLastMessage = 0;

      m_cModalStack = 0;              // initialize modality support

#ifdef WINDOWS_DESKTOP

      //m_hMenuAlt = nullptr;

#endif

      m_nIdleFlags = 0;               // no idle work at start
      m_rectangleBorder.Null();

      m_bHelpMode = 0;    // not in Shift+F1 help mode
      m_dwPromptContext = 0;

      m_pNextFrameWnd = nullptr;         // not in list_base yet

      m_bInRecalcLayout = false;
      m_nShowDelay = -1;              // no delay pending

      m_bFrameMoveEnable = true;

      m_pviewActive = nullptr;

      AddFrameWnd();

   }


   frame_window::~frame_window()
   {
      
      RemoveFrameWnd();

   }


   bool frame_window::_001IsFrameWnd()
   {

      return true;

   }


   void frame_window::GetBorderRectangle(::int_rectangle * prectangle)
   {

      __UNREFERENCED_PARAMETER(prectangle);

   }


   void frame_window::SetBorderRect(const ::int_rectangle & rectangle)
   {

      __UNREFERENCED_PARAMETER(rectangle);

   }


   //void frame_window::NotifyFloatingWindows(unsigned int dwFlags)
   //{

   //   __UNREFERENCED_PARAMETER(dwFlags);

   //}


   string frame_window::get_window_default_matter()
   {

      return "frame";

   }


   void frame_window::on_simple_command(::message::simple_command * psimplecommand)
   {

      switch (psimplecommand->command())
      {
      case e_simple_command_update_frame_title:

         on_update_frame_title(psimplecommand->m_lparam != false);

         psimplecommand->m_bRet = true;

         break;

      default:

         break;
      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::interaction::on_simple_command(psimplecommand);

   }


   void frame_window::on_command(::message::command * pcommand)
   {

      ::user::interaction::on_command(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      ::user::interaction::on_command(pcommand);

   }


   bool frame_window::handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken)
   {

      auto pcommand = __initialize_new::message::command(atom, puseractivationtoken);

      route_command(pcommand);

      return pcommand->m_bRet;

   }


   void frame_window::install_message_routing(::channel * pchannel)
   {

      ::user::main_window::install_message_routing(pchannel);

      MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &frame_window::on_message_destroy);
      MESSAGE_LINK(::user::e_message_create, pchannel, this, &frame_window::on_message_create);
      MESSAGE_LINK(::user::e_message_size, pchannel, this, &frame_window::on_message_size);
      MESSAGE_LINK(::user::e_message_set_focus, pchannel, this, &frame_window::on_message_set_focus);
      MESSAGE_LINK(::user::e_message_activate, pchannel, this, &frame_window::_001OnActivate);
      MESSAGE_LINK(::user::e_message_non_client_activate, pchannel, this, &frame_window::_001OnNcActivate);
#ifdef WINDOWS_DESKTOP
      //MESSAGE_LINK(WM_SYSCOMMAND, pchannel, this, &frame_window::_001OnSysCommand);
      //MESSAGE_LINK(WM_QUERYENDSESSION, pchannel, this, &frame_window::_001OnQueryEndSession);
#endif

   }


   void frame_window::update_active_document(::topic * ptopic)
   {

      auto pdocument = get_active_document();

      if (::is_null(pdocument))
      {

         return;

      }

      pdocument->update_all_impacts(ptopic);

   }


   void frame_window::update_active_document(const ::atom & atom)
   {

      auto pdocument = get_active_document();

      if (::is_null(pdocument))
      {

         return;

      }

      pdocument->id_update_all_impacts(atom);

   }


   ::atom frame_window::get_topic_impact_id()
   {

      auto pdocument = get_active_document();

      if (::is_null(pdocument))
      {

         return nullptr;

      }

      return pdocument->get_topic_impact_id();

   }


   bool frame_window::set_topic_impact_by_id(const ::atom & atom)
   {

      auto pdocument = get_active_document();

      if (::is_null(pdocument))
      {

         return false;

      }

      return pdocument->set_topic_impact_by_id(atom);

   }


   //void frame_window::defer_synch_layered()
   //{

   //   //bool bCalcLayered = calc_layered();

   //   //if (is_different(GetExStyle() & WS_EX_LAYERED, bCalcLayered))
   //   //{

   //   //   if (bCalcLayered)
   //   //   {

   //   //      ModifyStyleEx(0, WS_EX_LAYERED);

   //   //   }
   //   //   else
   //   //   {

   //   //      ModifyStyleEx(WS_EX_LAYERED, 0);

   //   //   }

   //   //}

   //}


   //bool frame_window::calc_layered()
   //{

   //   return true;

   //}


   bool frame_window::on_set_parent(::user::interaction_base * puiParent)
   {

      if (!::user::interaction::on_set_parent(puiParent))
      {

         return false;

      }

      return true;

   }


//   void frame_window::assert_ok() const
//   {
//
//      try
//      {
//
//         ::user::interaction::assert_ok();
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//
//   void frame_window::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::interaction::dump(dumpcontext);
//
//////#ifdef WINDOWS_DESKTOP
//////      dumpcontext << "m_hAccelTable = " << (uptr)m_hAccelTable;
//////#endif
////      dumpcontext << "\nm_nWindow = " << m_nWindow;
////      dumpcontext << "\nm_nIDHelp = " << m_strMatterHelp;
////      dumpcontext << "\nm_nIDTracking = " << m_nIDTracking;
////      dumpcontext << "\nm_nIDLastMessage = " << m_nIDLastMessage;
////      if (m_pviewActive != nullptr)
////         dumpcontext << "\nwith active ::user::impact: " << ::hex::lower_from((::iptr)m_pviewActive);
////      else
////         dumpcontext << "\nno active ::user::impact";
////
////      dumpcontext << "\n";
//
//   }


//   lresult frame_window::send_create_message()
//   {
//      
//      auto pcreate = øcreate_new < ::message::create >();
//      
//      pcreate->id() = ::user::e_message_create;
//      
//      pcreate->m_pusersystem = m_pusersystem;
//      
//      return send_message(pcreate);
//   
//   }


   bool frame_window::create_bars()
   {

      return false;

   }

   /////////////////////////////////////////////////////////////////////////////
   // frame_window

   // // 
   //{{__MSG_MAP(frame_window)
   /* xxx   ON_WM_INITMENU()
   ON_WM_INITMENUPOPUP()
   ON_WM_MENUSELECT()
   ON_MESSAGE(WM_POPMESSAGESTRING, &frame_window::OnPopMessageString)
   ON_MESSAGE(WM_SETMESSAGESTRING, &frame_window::OnSetMessageString)
   ON_MESSAGE(WM_HELPPROMPTADDR, &frame_window::OnHelpPromptAddr)
   ON_MESSAGE_VOID(::user::e_message_idle_update_command_user_interface, frame_window::OnIdleUpdateCmdUI)
   ON_WM_ENTERIDLE()
   ON_e_message_hscroll()
   ON_e_message_vscroll()
   ON_WM_SETFOCUS()

   ON_WM_DESTROY()
   ON_WM_CLOSE()
   ON_WM_SIZE()
   ON_WM_ERASEBKGND()
   ON_WM_ACTIVATE()
   ON_e_message_non_client_activate()
   ON_WM_DROPFILES()
   ON_WM_QUERYENDSESSION()
   ON_WM_ENDSESSION()
   ON_WM_SETCURSOR()
   ON_WM_ENABLE()
   // OLE palette support
   ON_WM_QUERYNEWPALETTE()
   ON_WM_PALETTECHANGED()
   ON_MESSAGE(WM_COMMANDHELP, &frame_window::OnCommandHelp)
   ON_MESSAGE(::user::e_message_help_hit_test, &frame_window::OnHelpHitTest)
   ON_MESSAGE(WM_ACTIVATETOPLEVEL, &frame_window::OnActivateTopLevel)
   // turning on and off standard frame gadgetry
   ON_UPDATE_::message::command(ID_VIEW_STATUS_BAR, &frame_window::OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_STATUS_BAR, &frame_window::OnBarCheck)
   ON_UPDATE_::message::command(ID_VIEW_TOOLBAR, &frame_window::OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_TOOLBAR, &frame_window::OnBarCheck)
   ON_UPDATE_::message::command(ID_VIEW_REBAR, &frame_window::OnUpdateControlBarMenu)
   ON_COMMAND_EX(ID_VIEW_REBAR, &frame_window::OnBarCheck)
   // turning on and off standard mode indicators
   ON_UPDATE_::message::command(ID_INDICATOR_CAPS, &frame_window::OnUpdateKeyIndicator)
   ON_UPDATE_::message::command(ID_INDICATOR_NUM, &frame_window::OnUpdateKeyIndicator)
   ON_UPDATE_::message::command(ID_INDICATOR_SCRL, &frame_window::OnUpdateKeyIndicator)
   ON_UPDATE_::message::command(ID_INDICATOR_KANA, &frame_window::OnUpdateKeyIndicator)
   // standard help handling
   ON_UPDATE_::message::command(ID_CONTEXT_HELP, &frame_window::OnUpdateContextHelp)
   // toolbar "tooltip" notification
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, &frame_window::OnToolTipText)
   ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, &frame_window::OnToolTipText)
   ON_NOTIFY_EX_RANGE(RBN_CHEVRONPUSHED, 0, 0xFFFF, &frame_window::OnChevronPushed)
   //}}__MSG_MAP
   // message handling for standard DDE commands
   ON_MESSAGE(WM_DDE_INITIATE, &frame_window::OnDDEInitiate)
   ON_MESSAGE(WM_DDE_EXECUTE, &frame_window::OnDDEExecute)
   ON_MESSAGE(WM_DDE_TERMINATE, &frame_window::OnDDETerminate)
   ON_REGISTERED_MESSAGE(gen_MsgMouseWheel, &frame_window::OnRegisteredMouseWheel) */
   // // 

   /////////////////////////////////////////////////////////////////////////////
   // frame_window construction/destruction



   void frame_window::AddFrameWnd()
   {

   }


   void frame_window::RemoveFrameWnd()
   {

   }


   /////////////////////////////////////////////////////////////////////////////
   // Special processing etc

   bool frame_window::LoadAccelTable(const ::scoped_string & scopedstrResourceName)
   {


      //ASSERT(m_hAccelTable == nullptr);  // only do once
      //ASSERT(scopedstrResourceName != nullptr);

      /*   HINSTANCE hInst = ::aura::FindResourceHandle(scopedstrResourceName, RT_ACCELERATOR);

      m_hAccelTable = ::LoadAccelerators(hInst, pszResourceName);*/
//#ifdef WINDOWS_DESKTOP
//      return (m_hAccelTable != nullptr);
//#endif

      return false;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   HACCEL frame_window::GetDefaultAccelerator()
//   {
//      // use ::user::document specific accelerator table over m_hAccelTable
//      HACCEL hAccelTable = m_hAccelTable;
//      HACCEL hAccel;
//      ::pointer<::user::document>pDoc = get_active_document();
//      if (pDoc != nullptr && (hAccel = pDoc->GetDefaultAccelerator()) != nullptr)
//         hAccelTable = hAccel;
//
//      return hAccelTable;
//   }
//
//
//   #endif


   void frame_window::pre_translate_message(::message::message * pmessage)
   {

      ENSURE_ARG(pmessage != nullptr);
      // check for special cancel modes for combo interactiones
      //if (pMsg->message == ::user::e_message_left_button_down || pMsg->message == ::user::e_message_non_client_left_button_down)
      //   __cancel_modes(pMsg->oswindow);    // filter clicks

      ::pointer<::message::key>pkey = pmessage;

      if (pkey.is_set())
      {

         if (session()->is_key_pressed(::user::e_key_alt) && session()->is_key_pressed(::user::e_key_control))
         {

            if (pkey->m_ekey == ::user::e_key_p)
            {

               ::pointer<::windowing::window>pimpl = window();

               if (pimpl.is_set())
               {

                  //synchronous_lock synchronouslock(pimpl->m_spgraphics->synchronization());

                  ::image::image_pointer pimage1;

                  ::int_rectangle rectangle;

                  window_rectangle(rectangle);

                  pimage1 = image()->create_image(rectangle.size());

                  //auto pparticleSynchronization = pimpl->m_pgraphics->get_draw_lock();

                  auto pbufferitem = pimpl->m_pgraphicsgraphics->on_begin_draw(e_graphics_draw);

                  synchronous_lock synchronouslock(pbufferitem->m_pmutex);

                  auto rectangleTarget = ::double_rectangle(rectangle.size());

                  auto pgraphics = pbufferitem->g();

                  ::image::image_source imagesource(pgraphics);

                  ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

                  ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                  pimage1->get_graphics()->draw(imagedrawing);

                  auto pcopydesk = copydesk();

                  pcopydesk->image_to_desk(pimage1);

                  image()->save_image(directory_system()->userconfig() / "control_alt_p.png", pimage1);

                  ::image::image_pointer pimage2;

                  //auto estatus = 
                  
                  øconstruct(pimage2);

                  //if (!estatus)
                  //{

                  //   return;

                  //}

                  //estatus = 
                  
                  pimage2->create({ 300, rectangle.size().cy() * 300 / rectangle.size().cx() });

                  //if (!estatus)
                  //{

                  //   return;

                  //}

                  pimage2->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

                  double_rectangle rectangleSource(rectangle.size());

                  {

                     ::image::image_source imagesource(pimage1, rectangleSource);

                     double_rectangle rectangleTarget(pimage2->size());

                     ::image::image_drawing_options imagedrawingoptions(rectangleTarget);

                     ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

                     pimage2->get_graphics()->draw(imagedrawing);

                  }

                  image()->save_image(directory_system()->userconfig() / "control_alt_p_w300.png", pimage2);

                  pkey->m_bRet = true;

                  pkey->m_lresult = 1;

               }

               return;

            }

         }

      }

      // allow tooltip messages to be filtered
      ::user::interaction::pre_translate_message(pmessage);
      if (pmessage->m_bRet)
         return;




      /* trans if (pMsg->message >= ::user::e_message_key_first && pMsg->message <= ::user::e_message_key_last)
      {
      // finally, translate the message
      HACCEL hAccel = GetDefaultAccelerator();
      return hAccel != nullptr &&  ::TranslateAccelerator(get_handle(), hAccel, pMsg);
      }*/
   }


   void frame_window::destroy()
   {
      ::user::interaction::destroy();
      // default for frame windows is to allocate them on the heap
      //  the default post-cleanup is to 'delete this'.
      // never explicitly call 'delete' on a frame_window, use DestroyWindow instead
      //release();
   }


   void frame_window::OnPaletteChanged(::pointer<::user::interaction>pFocusWnd)
   {
      __UNREFERENCED_PARAMETER(pFocusWnd);
      // trans user::frame_window::OnPaletteChanged(pFocusWnd);
   }

   bool frame_window::OnQueryNewPalette()
   {
      // trans    return user::frame_window::OnQueryNewPalette();
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // frame_window support for context sensitive help.

   void frame_window::ExitHelpMode()
   {
      /* trans
      // if not in help mode currently, this is a no-op
      if (!m_bHelpMode)
      return;

      // only post ___new WM_EXITHELPMODE message if one doesn't already exist
      //  in the queue.
      MESSAGE msg;
      if (!::PeekMessage(&msg, get_handle(), WM_EXITHELPMODE, WM_EXITHELPMODE,
      PM_REMOVE|PM_NOYIELD))
      {
      VERIFY(::PostMessage(get_handle(), WM_EXITHELPMODE, 0, 0));
      }

      // release capture if this interaction_impl has it
      if (psession->GetCapture() == get_handle())
         

         auto puser = user();

         auto pwindowing = system()->windowing();

         pwindowing->release_mouse_capture();

      ::pointer<::user::frame_window>pFrameWnd = top_level_frame();
      ENSURE_VALID(pFrameWnd);
      pFrameWnd->m_bHelpMode = m_bHelpMode = HELP_INACTIVE;
      PostMessage(::user::e_message_kick_idle);   // trigger idle update
      */
   }

   bool frame_window::OnSetCursor(::pointer<::user::interaction>pwindow, unsigned int nHitTest, const ::atom & atom)
   {
      
      __UNREFERENCED_PARAMETER(pwindow);
      __UNREFERENCED_PARAMETER(nHitTest);
      __UNREFERENCED_PARAMETER(atom);
      
      ::pointer<::user::frame_window>pFrameWnd = top_level_frame();

      ENSURE_VALID(pFrameWnd);
      if (pFrameWnd->m_bHelpMode)
      {

         return true;

      }
      // trans   return user::frame_window::OnSetCursor(pwindow, nHitTest, message);

      return true;

   }

   /*LRESULT frame_window::OnCommandHelp(WPARAM, LPARAM lParam)
   {
   if (lParam == 0)
   {
   if (IsTracking())
   lParam = HID_BASE_COMMAND+m_nIDTracking;
   else
   lParam = HID_BASE_RESOURCE+m_nIDHelp;
   }
   if (lParam != 0)
   {
   application* pApp = System;
   if (pApp != nullptr)
   pApp->WinHelpInternal(lParam);
   return true;
   }
   return false;
   }*/

   /*LRESULT frame_window::OnHelpHitTest(WPARAM, LPARAM)
   {
   if (m_nIDHelp != 0)
   return HID_BASE_RESOURCE+m_nIDHelp;
   else
   return 0;
   }*/

   //bool frame_window::OnCommand(WPARAM wParam, LPARAM lParam)
   //   // return true if command invocation was attempted
   //{
   //   //   ::oswindow oswindow_Ctrl = (::oswindow) lParam;
   //   //   unsigned int nID = LOWORD(wParam);

   //   ::pointer<::user::frame_window>pFrameWnd = top_level_frame();
   //   ENSURE_VALID(pFrameWnd);
   //   /*   if (pFrameWnd->m_bHelpMode && oswindow_Ctrl == nullptr &&
   //   nID != ID_HELP && nID != ID_DEFAULT_HELP && nID != ID_CONTEXT_HELP)
   //   {
   //   // route as help
   //   if (!SendMessage(WM_COMMANDHELP, 0, HID_BASE_COMMAND+nID))
   //   SendMessage(::user::e_message_command, ID_DEFAULT_HELP);
   //   return true;
   //   }
   //   */
   //   // route as normal command
   //   // trans   return user::frame_window::OnCommand(wParam, lParam);
   //   return false;
   //}




   void frame_window::BeginModalState()
   {
      //   ASSERT(get_handle() != nullptr);
      ASSERT(is_window());

      // allow stacking, but don't do anything
      if (++m_cModalStack > 1)
         return;

      // determine top-level parent, since that is the true parent of any
      //  modeless windows anyway...
      //auto pparent = top_level();

      m_puiptraDisable->erase_all();

      /*
      // disable all windows connected to this frame (and add them to the list_base)
      ::pointer<::user::interaction>oswindow = psystem->get_desktop_window()->GetWindow(GW_CHILD);

      while (oswindow != nullptr)
      {

         if (oswindow->is_window_enabled() && ::user::is_descendant(pParent, oswindow) && oswindow->send_message(WM_DISABLEMODAL) == 0)
         {

            oswindow->enable_window(false);

            m_uiptraDisable.add(oswindow);

         }

         oswindow = oswindow->GetWindow(GW_HWNDNEXT);

      }
      */


   }

   void frame_window::EndModalState()
   {
      // pop one off the stack (don't undo modalness unless stack is down to zero)
      if (m_cModalStack == 0 || --m_cModalStack > 0)
         return;

      for (::collection::index nIndex = 0; nIndex < m_puiptraDisable->get_count(); nIndex++)
      {

         ASSERT(m_puiptraDisable->element_at(nIndex) != nullptr);

         if (m_puiptraDisable->element_at(nIndex)->is_window())
            m_puiptraDisable->element_at(nIndex)->enable_window(true);

      }

      m_puiptraDisable->erase_all();

   }


   void frame_window::ShowOwnedWindows(bool bShow)
   {
      __UNREFERENCED_PARAMETER(bShow);
      // walk through all top-level windows
      throw ::interface_only();
      /*   oswindow oswindow = ::GetWindow(::get_desktop_window(), GW_CHILD);
      while (oswindow != nullptr)
      {
      ::windowing::window * pwindow = interaction_impl::FromHandlePermanent(oswindow);
      if (pwindow != nullptr && get_handle() != oswindow && __is_descendant(this, pwindow))
      {
      unsigned int uStyle = ::GetWindowLong(oswindow, GWL_STYLE);
      if (!bShow && (uStyle & (WS_VISIBLE|WS_DISABLED)) == WS_VISIBLE)
      {
      ::display(oswindow, e_display_none);
      pwindow->m_nFlags |= WF_TEMPHIDE;
      }
      // don't show temporarily hidden windows if we're in print thumbnail mode
      else if (bShow && (uStyle & (WS_VISIBLE|WS_DISABLED)) == 0 &&
      (pwindow->m_nFlags & WF_TEMPHIDE) && !m_lpfnCloseProc)
      {
      ::display(oswindow, SW_SHOWNOACTIVATE);
      pwindow->m_nFlags &= ~WF_TEMPHIDE;
      }
      }
      oswindow = ::GetWindow(oswindow, GW_HWNDNEXT);
      }*/
   }

   void frame_window::OnEnable(bool bEnable)
   {

      //      if (bEnable && (m_nFlags & WF_STAYDISABLED))
      //      {
      //
      //         // Work around for MAPI support. This makes sure the main interaction_impl
      //         // remains disabled even when the mail system is booting.
      //
      //         enable_window(false);
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //         ::XXXSetFocus(nullptr);
      //#else
      //
      //         throw ::exception(todo);
      //
      //#endif
      //
      //         return;
      //
      //      }


      // this causes modal dialogs to be "truly modal"
      //if (!bEnable && !InModalState())
      //{
      //   ASSERT((m_nFlags & WF_MODALDISABLE) == 0);
      //   m_nFlags |= WF_MODALDISABLE;
      //   BeginModalState();
      //}
      //else if (bEnable && (m_nFlags & WF_MODALDISABLE))
      //{
      //   m_nFlags &= ~WF_MODALDISABLE;
      //   EndModalState();

      //   // cause normal focus logic to kick in
      //   if (psystem->get_active_ui() == this)
      //      send_message(::user::e_message_activate, WA_ACTIVE);
      //}

      //// force ::user::e_message_non_client_activate because Windows may think it is unecessary
      //if (bEnable && (m_nFlags & WF_STAYACTIVE))
      //   send_message(::user::e_message_non_client_activate, true);
      //// force ::user::e_message_non_client_activate for floating windows too
   }


   bool frame_window::pre_create_window(::user::system * pusersystem)
   {

      if (m_bAddToTitle)
      {

         m_bPrefixTitle = true;

      }

      //if(pusersystem->m_createstruct.hwndParent != nullptr)
      //{

      //   pusersystem->m_createstruct.style |= WS_CHILD;

      //}

      //pusersystem->m_createstruct.style &= ~WS_VISIBLE;

//#ifdef WINDOWS_DESKTOP
//
//      pusersystem->m_createstruct.style &= ~WS_CAPTION;
//
//#endif

      return true;

   }


   //bool frame_window::create_interaction(const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction * puiParent, const ::scoped_string & scopedstrMenuName, unsigned int dwExStyle, ::request * prequest)
   //{

   //   __UNREFERENCED_PARAMETER(scopedstrMenuName);

   //   m_strFrameTitle = pszWindowName;    // save title for later

   //   auto pusersystem = øallocate ::user::system(dwExStyle, pszClassName, pszWindowName, uStyle, rectangle, pcreate);

   //   if (!::user::interaction::create_window_ex(pusersystem, puiParent, pcreate->id()))
   //   {

   //      information(trace_category_appmsg, e_trace_level_warning, "Warning: failed to create frame_window.\n");

   //      return false;

   //   }

   //   return true;

   //}


   bool frame_window::on_create_client(::user::system * pusersystem)
   {

      if (pusersystem != nullptr)
      {

         if (pusersystem->m_typeatomNewImpact || pusersystem->m_puserprimitiveNew != nullptr)
         {

            auto pinteraction = pusersystem->create_impact(this, FIRST_PANE);

            if(!pinteraction)
            {

               warning() <<"the impact wasn't created: " << pusersystem->m_typeatomNewImpact.as_string();

            }

         }

      }

      return true;

   }


   void frame_window::on_message_create(::message::message * pmessage)
   {

      if (!m_papplication->m_pacmeuserinteractionMain)
      {

         m_papplication->m_pacmeuserinteractionMain = this;

      }

      if (pmessage->previous())
      {
         
         return;
         
      }

      //m_strDataKey = "frame::" + m_pimpactsystem->id();

//#ifdef MACOS

      if(get_parent() == nullptr)
      {
         
         auto pwindowing = windowing();
         
         pwindowing->defer_create_main_menu(
                                       
                                       m_straMenuParent,
                                       m_straMenuName,
                                       m_straMenuId
                                       );

      }

//#endif

      ::pointer<::message::create>pcreatemessage(pmessage);

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         pcreatemessage->m_lresult = OnCreateHelper(m_pusersystem);

         pcreatemessage->m_bRet = pcreatemessage->m_lresult == -1;

         if(pcreatemessage->m_bRet)
         {

            return;

         }

      }

//      defer_synch_layered();


   }


   int frame_window::OnCreateHelper(::user::system * pusersystem)
   {

      if (!on_create_client(pusersystem))
      {

         error()(e_trace_category_appmsg) << "Failed to create client pane/::user::impact for frame.";

         return -1;

      }

      return 0;

   }


   void frame_window::enable_frame_experience(bool bEnable)
   {


   }


   void frame_window::OnInitialFrameUpdate(bool bMakeVisible)
   {

      // if (bMakeVisible)
      // {

      //    if (get_parent() == nullptr || !get_parent()->is_place_holder())
      //    {

      //       _001FancyInitialFramePlacement();

      //    }

      // }

   }


   ::string frame_window::calculate_data_key()
   {

      string strDataKey;

      strDataKey = id() + "::" + m_pimpactsystem->id();

      return strDataKey;

   }


   bool frame_window::LoadFrame(const ::scoped_string & scopedstrMatter, unsigned int dwDefaultStyle, ::user::interaction * puiParent, ::user::system * pusersystem)
   {

      __UNREFERENCED_PARAMETER(puiParent);

      // only do this once
      //   ASSERT_VALID_IDR(nIDResource);
      //   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

      m_strMatterHelp = scopedstrMatter;    // ID for help context (+HID_BASE_RESOURCE)

      //   string strFullString;
      //   if (strFullString.load_string(nIDResource))
      //      __extract_sub_string(m_strTitle, strFullString, 0);    // first sub-string

      //dwDefaultStyle &= ~WS_VISIBLE;

      ::int_rectangle rectangleFrame;

      ::pointer<::user::place_holder>pholder;

      if (puiParent != nullptr && (pholder = puiParent).is_set())
      {

         rectangleFrame = pholder->rectangle();

      }
      else
      {

         rectangleFrame = {};

      }

//      if(pusersystem)
//      {
//
//         if(pusersystem->m_prequest)
//         {
//
//            add(pusersystem->m_prequest);
//
//         }
//
//      }

      //m_bLockSketchToDesign = true;

      ///set_display(e_display_none);

      //informationf("\nm_bLayoutEnable false");

      //auto pusersystem = øallocate ::user::system(0L, nullptr, m_strFrameTitle, dwDefaultStyle, rectangleFrame, pcreate);

      //if (!create_window_ex(pusersystem, puiParent, pcreate->id()))
      //{

      //   return false;   // will self destruct on failure normally

      //}


   if (pusersystem->id().is_set())
   {

      ::string strAtom = pusersystem->id().as_string();

      if (strAtom.has_character())
      {

         id() = strAtom;

      }

   }

   m_strMatterHelp = scopedstrMatter;    // ID for help context (+HID_BASE_RESOURCE)

   auto papp = get_app();

   if (puiParent == nullptr)
   {

      puiParent = papp->get_request_parent_ui(this, pusersystem);

   }

   //::int_rectangle rectangleFrame;

   //::pointer<::user::place_holder>pholder;

//   if (puiParent != nullptr && (pholder = puiParent).is_set())
//   {
//
//      rectangleFrame = pholder->rectangle();
//
//   }

   //m_bLockSketchToDesign = true;

   if (puiParent == nullptr || wfi_has_up_down())
   {

      if (wfi_has_up_down() && ::is_set(puiParent) && puiParent->m_bWfiUpDownTarget)
      {

         m_pupdowntarget = puiParent;

      }
      
      if(windowing()->is_sandboxed())
      {
         
         display_zoomed();
         
      }
      else if (should_save_window_rectangle())
      {

         //bool bForceRestore = false;

         //bool bInitialFramePosition = true;

         //m_puserinteractionParent = puiParent;

         //WindowDataLoadWindowRectangle(bForceRestore, bInitialFramePosition);

         //_001FancyInitialFramePlacement();

         initial_frame_placement();

         rectangleFrame = const_layout().state(::user::e_layout_sketch).parent_raw_rectangle();

         information() << "LoadFrame rectangleFrame : " << rectangleFrame;
         information() << "LoadFrame edisplay : " << const_layout().sketch().display();

         if (wfi_has_up_down())
         {

            if (m_eupdown == e_updown_up)
            {

               puiParent = nullptr;

            }
            else if (m_eupdown == e_updown_down)
            {

               ::pointer<::user::document>pdocument = pusersystem->m_pdocumentCurrent;

               ::pointer<::user::impact_host>pimpacthost;

               if (pimpacthost.is_set())
               {

                  puiParent = pimpacthost->updown_target_get_place_holder(this, pdocument);

               }

            }

         }

      }

      if (is_top_level())
      {

         if (m_ewindowflag & e_window_flag_main_frame)
         {

            display(e_display_zoomed);

            //  psession->get_main_workspace(rectangleFrame);

         }

      }

      rectangleFrame = const_layout().state(::user::e_layout_sketch).parent_raw_rectangle();

      //pusersystem->set_rect(rectangleFrame);

      information() << "LoadFrame (2) rectangleFrame : " << rectangleFrame;
      information() << "LoadFrame (2) sketch.edisplay : " << const_layout().sketch().display();


   }

//   if (puiParent != nullptr)
//   {
//
//      //pusersystem->m_createstruct.style |= WS_CHILD;
//
//   }

   m_bEnableSaveWindowRect2 = false;

   bool bLoadImplRect = m_ewindowflag & e_window_flag_load_window_rect_on_impl;

   m_ewindowflag -= e_window_flag_load_window_rect_on_impl;

   //bool bCreated = create_window_ex(pusersystem, puiParent, id());

   //bool bCreated;

   m_pusersystem = pusersystem;

   //bCreated =

//   if (pusersystem->m_prequest && !(pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen))
//   {
//
//      hide();
//
//   }

   if (bLoadImplRect)
   {

      m_ewindowflag += e_window_flag_load_window_rect_on_impl;

   }

//   if (::is_set(get_parent()))
//   {
//
//      if (pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
//      {
//
//         display();
//
//      }
//
//   }
//   else
//   {
//
//      if (pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
//      {
//
//         initial_frame_display();
//
//         //if(pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
//         {
//
//            if (!const_layout().sketch().is_screen_visible())
//            {
//
//               information() << "LoadFrame sketch !is_screen_visible going to display_normal (1)";
//
//               display_normal(e_display_normal, ::user::e_activation_set_foreground);
//
//            }
//
//         }
//
//      }
//
//   }

   m_bNeedPerformLayout = true;

   set_need_layout();

   if (puiParent)
   {

      create_child(puiParent);

      //if (!create_child(puiParent))
      //{

      //   return false;

      //}

   }
   else
   {

      //create_host(e_parallelization_asynchronous);

      create_window();

      //if (!create_host())
      //{

      //   return false;

      //}


   }

   if (pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
   {

      set_need_redraw();

      post_redraw();

   }

      /* trans   // save the default menu handle
      ASSERT(get_handle() != nullptr);
      m_hMenuDefault = ::GetMenu(get_handle()); */

      // load accelerator resource
      //   LoadAccelTable(MAKEINTRESOURCE(nIDResource));


      return true;

//      return false;

      // only do this once
      //   ASSERT_VALID_IDR(nIDResource);
      //   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

      /*m_nIDHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

      string strFullString;
      if (strFullString.load_string(nIDResource))
      __extract_sub_string(m_strTitle, strFullString, 0);    // first sub-string

      VERIFY(__defer_register_class(__WNDFRAMEORVIEW_REG));

      // attempt to create the interaction_impl
      const_char_pointer lpszClass = GetIconWndClass(dwDefaultStyle, nIDResource);

      string strTitle = m_strTitle;
      if (!create_window_ex(0, lpszClass, strTitle, dwDefaultStyle, rectangleDefault,

      puiParent, nIDResource, (LPVOID) pContext))
      {
      return false;   // will self destruct on failure normally
      }

      // save the default menu handle
      //ASSERT(get_handle() != nullptr);
      // trans m_hMenuDefault = ::GetMenu(get_handle());
      m_hMenuDefault = nullptr; // trans

      // load accelerator resource
      LoadAccelTable(MAKEINTRESOURCE(nIDResource));

      if (pContext == nullptr)   // send initial update
      send_message_to_descendants(WM_INITIALUPDATE, 0, 0, true, true);

      return true;*/
   }


//#ifdef WINDOWS_DESKTOP
//
//
//   void frame_window::OnUpdateFrameMenu(HMENU hMenuAlt)
//   {
//      if (hMenuAlt == nullptr)
//      {
//         // attempt to get default menu from ::user::document
//         ::pointer<::user::document>pDoc = get_active_document();
//         if (pDoc != nullptr)
//            hMenuAlt = pDoc->GetDefaultMenu();
//         // use default menu stored in frame if none from ::user::document
//         if (hMenuAlt == nullptr)
//            hMenuAlt = m_hMenuDefault;
//      }
//      // finally, set the menu
//      // trans ::SetMenu(get_handle(), hMenuAlt);
//   }
//
//
//#endif


   void frame_window::prepare_frame(::user::document * pdocument, bool bMakeVisible)
   {

      // if the frame does not have an active ::user::impact, set to first pane
      ::pointer<::user::impact>pimpact;

      if (get_active_impact() == nullptr)
      {

         ::pointer<::user::interaction>pwindow = get_child_by_id(FIRST_PANE);

         if (pwindow != nullptr && base_class < ::user::impact > ::bases(pwindow))
         {

            pimpact = pwindow;

            //set_active_impact(pimpact, false);

         }

      }

      //   oswindow oswindow = get_handle();
      //   unsigned int uStyle = ::GetWindowLong(oswindow, GWL_STYLE);
      //   bool bChild =  uStyle & WS_CHILD;

      OnInitialFrameUpdate(bMakeVisible);

      if (bMakeVisible)
      {

         //m_bLockSketchToDesign = false;

         // send initial update to all views (and other controls) in the frame
         send_message_to_descendants(::user::e_message_system_update, id_initial_update, (lparam)0, true, true);

         m_bNeedPerformLayout = true;

         set_need_layout();

         set_need_redraw();

         post_redraw();

         // give ::user::impact a chance to save the focus (CFormImpact needs this)
         if (pimpact != nullptr)
         {

            pimpact->OnActivateFrame(e_activate_inactive, this);

         }

         // finally, activate the frame
         // (send the default show command unless the main desktop interaction_impl)
         //ActivateFrame(e_display_default);
         // Don't activate frame when preparing it, initial frame display should
         // had handled activation.

         if (pimpact != nullptr)
         {

            pimpact->OnActivateImpact(true, pimpact, pimpact);

         }

      }

      //m_bLockSketchToDesign = false;

      // update frame counts and frame title (may already have been visible)
      if (pdocument != nullptr)
      {

         pdocument->update_frame_counts();

      }

      on_update_frame_title(true);

      //if (get_parent() != nullptr
      //      && get_parent()->is_place_holder()
      //      && !is_true("should_not_be_automatically_holded_on_initial_update_frame"))
      //{
      //   get_parent()->place_hold(this);
      //   //get_parent()->on_layout(pgraphics);
      //}

   }


   //bool frame_window::_001FancyInitialFramePlacement(bool bForceRestore)
   //{

   //   __UNREFERENCED_PARAMETER(bForceRestore);

   //   if (m_bFrameMoveEnable)
   //   {

   //      display(e_display_restore);

   //   }

   //   ActivateTopParent();

   //   ActivateFrame();

   //   set_reposition();

   //   set_need_layout();

   //   set_need_redraw();

   //   post_redraw();

   //   return true;

   //}


   void frame_window::OnClose()
   {

      throw ::interface_only();
      /*if (m_lpfnCloseProc != nullptr)
      (*m_lpfnCloseProc)(this);

      // Note: only queries the active ::user::document
      ::pointer<::user::document>pdocument = get_active_document();
      if (pdocument != nullptr && !pdocument->can_close_frame(this))
      {
      // ::user::document can't close right now -- don't close it
      return;
      }
      application* pApp = System;
      if (pApp != nullptr && pApp->m_puiMain == this)
      {
      // attempt to save all documents
      if (pdocument == nullptr && !pApp->save_all_modified())
      return;     // don't close it

      // hide the application's windows before closing all the documents
      pApp->HideApplication();

      // close all documents first
      pApp->close_all_documents(false);


      // there are cases where destroying the documents may destroy the
      //  main interaction_impl of the application.
      if (!::windows_definition::ContextIsDLL && pApp->m_puiMain == nullptr)
      {
      __post_quit_message(0);
      return;
      }
      }

      // detect the case that this is the last frame on the ::user::document and
      // shut down with on_close_document instead.
      if (pdocument != nullptr && pdocument->m_bAutoDelete)
      {
      bool bOtherFrame = false;
      POSITION pos = pdocument->get_impact_count();
      while (pos != nullptr)
      {
      ::pointer<::user::impact>pimpact = pdocument->get_impact(pos);
      ENSURE_VALID(pimpact);
      if (pimpact->get_parent_frame() != this)
      {
      bOtherFrame = true;
      break;
      }
      }
      if (!bOtherFrame)
      {
      pdocument->on_close_document();
      return;
      }

      // allow the ::user::document to cleanup before the interaction_impl is destroyed
      pdocument->pre_close_frame(this);
      }

      // then destroy the interaction_impl
      DestroyWindow();*/
   }

   void frame_window::on_message_destroy(::message::message * pmessage)
   {

      pmessage->previous();


   }


   //void frame_window::on_command(::message::command* pcommand)
   //{

   //   ::user::frame_interaction::on_command(pcommand);

   //}


   void frame_window::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      if (bRouteToKeyDescendant)
      {

         ::pointer<::user::impact>pimpact = get_active_impact();

         if (pimpact != nullptr)
         {

            pimpact->route_command(pcommand, false);

            if (pcommand->m_bRet)
            {

               return;

            }

         }

      }

      ::user::box::route_command(pcommand, false);

   }


   /*
   // Delegate scroll messages to active ::user::impact as well
   void frame_window::OnHScroll(unsigned int, unsigned int, CScrollBar*)
   {
      ::pointer<::user::interaction>pActiveImpact = get_active_impact();
      if (pActiveImpact != nullptr)
      {
         // trans const MESSAGE* pMsg = GetCurrentMessage();
         // trans pActiveImpact->SendMessage(::user::e_message_scroll_x, pMsg->wParam, pMsg->lParam);
      }
   }

   void frame_window::OnVScroll(unsigned int, unsigned int, CScrollBar*)
   {
      ::pointer<::user::interaction>pActiveImpact = get_active_impact();
      if (pActiveImpact != nullptr)
      {
         // trans      const MESSAGE* pMsg = GetCurrentMessage();
         // trans      pActiveImpact->SendMessage(::user::e_message_scroll_y, pMsg->wParam, pMsg->lParam);
      }
   }
   */

   //LRESULT frame_window::OnActivateTopLevel(WPARAM wParam, LPARAM lParam)
   //{
   //   __UNREFERENCED_PARAMETER(wParam);
   //   __UNREFERENCED_PARAMETER(lParam);
   //   // trans   user::frame_window::OnActivateTopLevel(wParam, lParam);

   //   // exit Shift+F1 help mode on activation changes
   //   ExitHelpMode();


   //   // deactivate current active ::user::impact
   //   //thread *pThread = get_task();
   //   //ASSERT(pThread);
   //   
   //   ::pointer<::user::impact>pActiveImpact = get_active_impact();

   //   if (pActiveImpact == nullptr)
   //   {

   //      pActiveImpact = GetActiveFrame()->get_active_impact();

   //   }

   //   if (pActiveImpact != nullptr)
   //   {

   //      pActiveImpact->OnActivateImpact(false, pActiveImpact, pActiveImpact);

   //   }

   //   return 0;

   //}

   void frame_window::_001OnActivate(::message::message * pmessage)
   {
      ::pointer<::message::activate>pactivate(pmessage);

      ::pointer<::user::interaction>pActive = (pactivate->m_eactivate == e_activate_inactive ? pactivate->m_pWndOther : this);

      pmessage->previous();

      // get top level frame unless this is a child interaction_impl
      // determine if interaction_impl should be active or not
      //::pointer<::user::frame_window>pTopLevel = (GetStyle() & WS_CHILD) ? this : top_level_frame();

      //if (pTopLevel == nullptr)
      //{

      //   pTopLevel = this;

      //}

      {

         auto ptopic = create_topic(id_on_activate);

         ptopic->payload("eactivate") = (int)pactivate->m_eactivate;

         route(ptopic);

      }


      //bool bStayActive =
      //(pTopLevel == pActive ||
      // (pActive && pTopLevel == pActive->top_level_frame() &&
      //  (pActive == pTopLevel ||
      //   (pActive && pActive->send_message(WM_FLOATSTATUS, FS_SYNCACTIVE) != 0))));
      ////pTopLevel->m_nFlags &= ~WF_STAYACTIVE;
      ////if (bStayActive)
      ////   pTopLevel->m_nFlags |= WF_STAYACTIVE;

      //// synchronization floating windows to the ___new state
      //NotifyFloatingWindows(bStayActive ? FS_ACTIVATE : FS_DEACTIVATE);

      // get active ::user::impact (use active frame if no active ::user::impact)
      
      ::pointer<::user::impact>pActiveImpact = get_active_impact();

      if (pActiveImpact == nullptr)
      {

         pActiveImpact = GetActiveFrame()->get_active_impact();

      }

      // when frame gets activated, re-activate current ::user::impact
      if (pActiveImpact != nullptr)
      {
         if (pactivate->m_eactivate != e_activate_inactive && !pactivate->m_bMinimized)
            pActiveImpact->OnActivateImpact(true, pActiveImpact, pActiveImpact);

         // always notify the ::user::impact of frame activations
         pActiveImpact->OnActivateFrame(pactivate->m_eactivate, this);
      }

      set_need_redraw();

   }


   void frame_window::_001OnNcActivate(::message::message * pmessage)
   {

      //::pointer<::message::nc_activate>pncactivate(pmessage);

//#ifdef WINDOWS_DESKTOP
//
//      if (::IsIconic(get_handle()))
//      {
//
//         pncactivate->m_bRet = false;
//
//      }
//      else
//      {
//
//         pncactivate->m_lresult = false;
//
//         pncactivate->m_bRet = true;
//
//
//      }
//
//#else
//
//      pncactivate->m_lresult = true;
//
//      pncactivate->m_bRet = true;
//
//#endif

   }


   //void frame_window::OnSysCommand(unsigned int nID, LPARAM lParam)
   //{
   //   
   //   __UNREFERENCED_PARAMETER(lParam);

   //   ::pointer<::user::frame_window>pFrameWnd = top_level_frame();

   //   ENSURE_VALID(pFrameWnd);

   //   // set status bar as appropriate
   //   //   unsigned int nItemID = (nID & 0xFFF0);

   //   // don't interfere with system commands if not in help mode
   //   if (pFrameWnd->m_bHelpMode)
   //   {
   //      /*switch (nItemID)
   //      {
   //      case SC_SIZE:
   //      case SC_MOVE:
   //      case SC_MINIMIZE:
   //      case SC_MAXIMIZE:
   //      case SC_NEXTWINDOW:
   //      case SC_PREVWINDOW:
   //      case SC_CLOSE:
   //      case SC_RESTORE:
   //      case SC_TASKLIST:
   //      if (!SendMessage(WM_COMMANDHELP, 0,
   //      HID_BASE_COMMAND+ID_COMMAND_FROM_SC(nItemID)))
   //      SendMessage(::user::e_message_command, ID_DEFAULT_HELP);
   //      return;
   //      }*/
   //   }

   //   // call default functionality
   //   // trans   user::frame_window::OnSysCommand(nID, lParam);
   //}


#ifdef WINDOWS_DESKTOP


   ///////////////////////////////////////////////////////////////////////////////
   //// default frame processing

   //// default drop processing will attempt to open the file
   //void frame_window::OnDropFiles(HDROP hDropInfo)
   //{

   //   __UNREFERENCED_PARAMETER(hDropInfo);

   //}

#endif

   // query end session for main frame will attempt to close it all down
   bool frame_window::OnQueryEndSession()
   {

      return true;
   }

   // when Windows session ends, close all documents
   void frame_window::OnEndSession(bool bEnding)
   {
      __UNREFERENCED_PARAMETER(bEnding);
   }


   void frame_window::show_control_bar(::user::control_bar * pcontrolbar)
   {

      if(!is_child(pcontrolbar))
      {

         pcontrolbar->set_parent(this);

      }

      pcontrolbar->display();

      pcontrolbar->set_need_layout();

      pcontrolbar->set_need_redraw();

      pcontrolbar->post_redraw();

      // m_bNeedRepositionBars = true;

      set_need_perform_layout();

      set_need_layout();

      set_need_redraw();

      post_redraw();

//      return ::success;

   }


   void frame_window::hide_control_bar(::user::control_bar * pcontrolbar)
   {

      if(!is_child(pcontrolbar))
      {

         pcontrolbar->set_parent(this);

      }

      pcontrolbar->hide();

      set_need_layout();

      //m_bNeedRepositionBars = true;


      //throw ::interface_only();

   }


   ::pointer<toolbar>frame_window::get_toolbar(const ::atom & idToolbar, bool bCreate, const ::scoped_string & scopedstrToolbarParam, unsigned int dwCtrlStyle, unsigned int uStyle, const ::type_atom & typeatom)
   {

      try
      {

         auto & ptoolbartransport = m_mapToolbar[idToolbar];

         if (bCreate && !ptoolbartransport)
         {

            ptoolbartransport = create_toolbar(idToolbar, scopedstrToolbarParam, dwCtrlStyle, uStyle, "simple_toolbar");

            add_control_bar(ptoolbartransport);

         }

         return ptoolbartransport;

      }
      catch (const ::exception & exception)
      {

#ifdef _DEBUG

         auto pmessagebox = __initialize_new ::message_box(exception, "Failed to create toolbar \"" + idToolbar.as_string() + "\"");

         pmessagebox->async();

#endif

      }
      catch (...)
      {

#ifdef _DEBUG

         ::exception exception(error_catch_all_exception);

         auto pmessagebox = __initialize_new ::message_box(exception, "Failed to create toolbar \"" + idToolbar.as_string() + "\"");

         pmessagebox->async();

#endif

      }

//      catch (::exception & exception)
//      {
//
//#ifdef _DEBUG
//
//         throw ::exception(error_catch_all_exception, "Failed to create toolbar \"" + idToolbar.as_string() + "\"");
//
//#endif
//
//      }
//      catch (...)
//      {
//
//#ifdef _DEBUG
//
//         throw ::exception(error_catch_all_exception, "Failed to create toolbar \"" + idToolbar.as_string() + "\"");
//
//#endif
//
//      }

      //auto pmessagebox = message_box("Failed to create toolbar \"" + idToolbar.as_string() + "\"");

      //pmessagebox->async();

      return nullptr;

   }


   ::pointer<toolbar>frame_window::create_toolbar(const ::atom & idToolbar, const ::scoped_string & scopedstrToolbarParam, unsigned int dwCtrlStyle, unsigned int uStyle, const ::type_atom & typeatom)
   {

      ::pointer < toolbar> ptoolbar = øid_create (typeatom);

      ptoolbar->m_dwStyle = uStyle;

      ptoolbar->m_dwCtrlStyle = dwCtrlStyle;

      //auto estatus = 
      
      ptoolbar->create_child(this);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //// auto pcontext = get_context();

      string strToolbar(scopedstrToolbarParam);

      if(strToolbar.is_empty())
      {

         strToolbar = idToolbar + ".toolbar";

      }

      string strMatter = directory()->matter(strToolbar);
//
//      string strXml = file()->safe_get_string(strMatter);

      ptoolbar->load_xml_toolbar(strMatter);

      //if(!toolbartransport->load_xml_toolbar(strXml))
      //{

      //   return error_failed;

      //}

      return ptoolbar;

   }


   ::user::interaction * frame_window::get_active_impact()
   {

      ASSERT(m_pviewActive == nullptr || base_class < ::user::impact >::bases(m_pviewActive));

      return m_pviewActive;

   }


   void frame_window::set_active_impact(::user::impact * pviewNew, bool bNotify)
   {

      auto pviewOld = m_pviewActive;

      //auto pframewindow = parent_frame();

      //if (pframewindow)
      //{

      //   pframewindow->set_active_impact(pviewNew, bNotify);

      //}

      if (pviewNew == pviewOld)
      {

         return;     // do not re-activate if set_active_impact called more than once

      }

      m_pviewActive = nullptr;   // no active for the following processing

      // deactivate the old one
      if (pviewOld != nullptr && bNotify)
      {

         pviewOld->OnActivateImpact(false, pviewNew, pviewOld);

      }

      // if the OnActivateImpact moves the active interaction_impl,
      //    that will veto this machine
      if (m_pviewActive != nullptr)
      {

         return;     // already set

      }

      m_pviewActive = pviewNew;

      // activate
      if (pviewNew != nullptr)
      {

         if (bNotify)
         {

            pviewNew->OnActivateImpact(true, pviewNew, pviewOld);

         }

      }

   }



   /////////////////////////////////////////////////////////////////////////////
   // Special ::user::impact swapping/activation

   void frame_window::OnSetFocus(::pointer<::user::interaction>pOldWnd)
   {
      __UNREFERENCED_PARAMETER(pOldWnd);
      if (m_pviewActive != nullptr)
         m_pviewActive->set_keyboard_focus();
      /*trans else
      user::frame_window::OnSetFocus(pOldWnd);
      */
   }

   
   ::user::document * frame_window::get_active_document()
   {

      ASSERT_OK(this);

      ::pointer<::user::impact>pimpact = get_active_impact();

      if (pimpact != nullptr)
      {

         return pimpact->get_document();

      }

      return nullptr;

   }


   /////////////////////////////////////////////////////////////////////////////
   // Command prompts


   void frame_window::GetMessageString(unsigned int nID, string & rMessage) const
   {
      __UNREFERENCED_PARAMETER(nID);
      __UNREFERENCED_PARAMETER(rMessage);
      // load appropriate string
      throw ::interface_only();
      /*   char * psz = rMessage.GetBuffer(255);

      if (::aura::LoadString(nID, psz) != 0)

      {
      // first newline terminates actual string
      psz = _tcschr(scopedstr, '\n');

      if (scopedstr != nullptr)

      *psz = '\0';

      }
      else
      {
      // not found
      information(trace_category_appmsg, 0, "Warning: no message line prompt for ID 0x%04X.\n", nID);
      }
      rMessage.ReleaseBuffer();*/
   }


   //LRESULT frame_window::OnPopMessageString(WPARAM wParam, LPARAM lParam)
   //{

   //   //if (m_nFlags & WF_NOPOPMSG)
   //   //   return 0;

   //   return send_message(WM_SETMESSAGESTRING, wParam, lParam);

   //}


   //LRESULT frame_window::OnSetMessageString(WPARAM wParam, LPARAM lParam)
   //{

   //   unsigned int nIDLast = m_nIDLastMessage;

   //   //      m_nFlags &= ~WF_NOPOPMSG;

   //   ::pointer<::user::interaction>pMessageBar = GetMessageBar();

   //   if (pMessageBar != nullptr)
   //   {

   //      const ::scoped_string & scopedstr = nullptr;


   //      string strMessage;

   //      // set the message bar text

   //      if (lParam != 0)
   //      {

   //         ASSERT(wParam == 0);    // can't have both an ID and a string

   //         psz = (const ::string &)lParam; // set an explicit string


   //      }
   //      else if (wParam != 0)
   //      {

   //         // map_base SC_CLOSE to PREVIEW_CLOSE when in print thumbnail mode
   //         /*         if (wParam == __IDS_SCCLOSE && m_lpfnCloseProc != nullptr)
   //         wParam = __IDS_PREVIEW_CLOSE;*/

   //         // get message associated with the ID indicated by wParam
   //         //NT64: Assume IDs are still 32-bit

   //         GetMessageString((unsigned int)wParam, strMessage);

   //         psz = strMessage;


   //      }

   //      pMessageBar->set_window_text(scopedstr);


   //      // update owner of the bar in terms of last message selected
   //      ::pointer<::user::frame_window>pFrameWnd = pMessageBar->get_parent_frame();

   //      if (pFrameWnd != nullptr)
   //      {

   //         pFrameWnd->m_nIDLastMessage = (unsigned int)wParam;

   //         pFrameWnd->m_nIDTracking = (unsigned int)wParam;

   //      }

   //   }

   //   m_nIDLastMessage = (unsigned int)wParam;    // ___new ID(or 0)

   //   m_nIDTracking = (unsigned int)wParam;       // so F1 on toolbar buttons work

   //   return nIDLast;

   //}


   //LRESULT frame_window::OnHelpPromptAddr(WPARAM, LPARAM)
   //{
   //   return (LRESULT)&m_dwPromptContext;
   //}

   ::pointer<::user::interaction>frame_window::GetMessageBar()
   {
      return get_child_by_id("status_bar");
   }

//   void frame_window::OnEnterIdle(unsigned int nWhy, ::pointer<::user::interaction>pWho)
//   {
//      __UNREFERENCED_PARAMETER(pWho);
//      // trans user::frame_window::OnEnterIdle(nWhy, pWho);
//#ifdef WINDOWS
//      if (nWhy != MSGF_MENU || m_nIDTracking == m_nIDLastMessage)
//         return;
//#else
//      if (m_nIDTracking == m_nIDLastMessage)
//         return;
//#endif
//
//      SetMessageText(m_nIDTracking);
//      ASSERT(m_nIDTracking == m_nIDLastMessage);
//   }

   //void frame_window::SetMessageText(const ::scoped_string & scopedstrText)

   //{
   //   send_message(WM_SETMESSAGESTRING, 0, (lparam)pszText);

   //}

   //void frame_window::SetMessageText(unsigned int nID)
   //{
   //   send_message(WM_SETMESSAGESTRING, (WPARAM)nID);
   //}



   /////////////////////////////////////////////////////////////////////////////
   // Setting title of frame interaction_impl - UISG standard

   void frame_window::on_update_frame_title(bool bAddToTitle)
   {
      //if ((GetStyle() & FWS_ADDTOTITLE) == 0)
        // return;     // leave it alone!

      if (!m_bAddToTitle)
      {

         return;

      }


      ::pointer<::user::document>pdocument = get_active_document();
      if (bAddToTitle && pdocument != nullptr)
         UpdateFrameTitleForDocument(pdocument->get_title());
      else
         UpdateFrameTitleForDocument(nullptr);
   }


   void frame_window::UpdateFrameTitleForDocument(const ::scoped_string & scopedstrDocName)

   {

      string WindowText;

      //if (GetStyle() & FWS_PREFIXTITLE)
      if(m_bPrefixTitle)
      {
         // get name of currently active ::user::impact
         if (scopedstrDocName.has_character())

         {
            WindowText += scopedstrDocName;


            // add current interaction_impl # if needed
            if (m_nWindow > 0)
            {

               string strText;

               // :%d will produce a maximum of 11 TCHARs
               strText.formatf(":%d", m_nWindow);

               WindowText += strText;

            }

            WindowText += " - ";

         }
         WindowText += m_strFrameTitle;
      }
      else
      {
         // get name of currently active ::user::impact
         WindowText += m_strFrameTitle;
         if (scopedstrDocName.has_character())

         {
            WindowText += " - ";
            WindowText += scopedstrDocName;


            // add current interaction_impl # if needed
            if (m_nWindow > 0)
            {

               string strText;

               // :%d will produce a maximum of 11 TCHARs
               strText.formatf(":%d", m_nWindow);

               WindowText += strText;

            }
         }
      }

      // set title if changed, but don't erase completely
      // Note: will be excessive for MDI Frame with maximized child
      set_window_text(WindowText);
   }

   /////////////////////////////////////////////////////////////////////////////

   /*   void frame_window::OnSetThumbnailMode(bool bThumbnail, CPrintThumbnailState* pState)
      {
         ENSURE_ARG(pState != nullptr);
         // default implementation changes control bars, menu and main pane interaction_impl


         // set visibility of standard ControlBars (only the first 32)
         //   unsigned int dwOldStates = 0;

         if (bThumbnail)
         {
            // Entering Print Thumbnail


            // show any modeless dialogs, popup windows, float tools, etc
            ShowOwnedWindows(false);

            // Hide the main pane
         }
         else
         {
            // Leaving Thumbnail
            m_lpfnCloseProc = nullptr;

            // shift original FIRST_PANE back to its rightful ID
                  ::pointer<::user::interaction>oswindow = get_child_by_id(__IDW_PANE_SAVE);
            if (oswindow != nullptr)
            {
            ::pointer<::user::interaction>oswindow_Temp = get_child_by_id(FIRST_PANE);
            if (oswindow_Temp != nullptr)
            __set_dialog_control_id_(oswindow_Temp, __IDW_PANE_SAVE);
            __set_dialog_control_id_(oswindow, FIRST_PANE);
            }

            on_layout(pgraphics);


            // show any modeless dialogs, popup windows, float tools, etc
            ShowOwnedWindows(true);
         }
      }
      */


//#ifdef WINDOWS_DESKTOP
//
//
//   void frame_window::DelayUpdateFrameMenu(HMENU hMenuAlt)
//   {
//
//      m_hMenuAlt = hMenuAlt;
//
//      m_nIdleFlags |= idleMenu;
//
//   }
//
//
//#endif


   ::pointer<::user::frame_window>frame_window::GetActiveFrame()
   {
      // by default, the active frame is the frame itself (MDI is different)
      return this;
   }


   void frame_window::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::main_window::on_perform_top_down_layout(pgraphics);

      m_rectangleHosting = this->raw_rectangle(e_layout_layout);

      __task_guard(m_bInRecalcLayout);

      // clear idle flags for recalc on_layout if called elsewhere
      //   if (m_nIdleFlags & idleNotify)
      //   bNotify = true;
      m_nIdleFlags &= ~(idleLayout | idleNotify);
      {

         //         unsigned int dwTime2= ::time::now();

         //informationf("message_handler call time0= %d ms",dwTime2 - t_time1.operator DWORD_PTR());
         //informationf("userframewindow call time1= %d ms",dwTime2 - t_time1.operator DWORD_PTR());

      }

      ::string strType(::type(this).name());
      // reposition all the child windows (regardless of ID)
      //if (GetStyle() & FWS_SNAPTOBARS)
      if(m_bSnapToBars)
      {

         ::int_rectangle rectangle(0, 0, 32767, 32767);

         RepositionBars(0, 0xffff, FIRST_PANE, reposQuery, &rectangle, rectangle, false);

         RepositionBars(0, 0xffff, FIRST_PANE, reposExtra, &m_rectangleBorder, rectangle, true);

         //CalcWindowRect(&rectangle);

         set_size(rectangle.size());

         display(e_display_normal, { ::user::e_activation_no_activate });

      }
      else
      {

         RepositionBars(0, 0xffff, FIRST_PANE, reposExtra, &m_rectangleBorder);

      }

   }


   // frame_window implementation of OLE border space negotiation
   bool frame_window::NegotiateBorderSpace(unsigned int nBorderCmd, ::int_rectangle * pRectBorder)
   {

      ::int_rectangle border, request;

      switch (nBorderCmd)
      {
      case borderGet:
         ASSERT(pRectBorder != nullptr);

         RepositionBars(0, 0xffff, FIRST_PANE, reposQuery,
                        pRectBorder);

         break;

      case borderRequest:
         return true;

      case borderSet:
         if (pRectBorder == nullptr)

         {
            if (!m_rectangleBorder.is_null())
            {
               // releasing all border space -- recalc needed
               m_rectangleBorder.Null();
               return true;
            }
            // original int_rectangle is is_empty & pRectBorder is nullptr, no recalc needed

            return false;

         }

         if (m_rectangleBorder != *pRectBorder)
         {

            // the rects are different -- recalc needed
            m_rectangleBorder = *pRectBorder;

            return true;

         }

         return false;   // no recalc needed

      default:
         ASSERT(false);  // invalid frame_window::BorderCmd
      }

      return true;

   }


   void frame_window::OnSize(unsigned int nType, int cx, int cy)
   {

   }


   bool frame_window::OnEraseBkgnd(::image::image *pimage)
   {

      __UNREFERENCED_PARAMETER(pimage);

      if (m_pviewActive != nullptr)
      {

         return true;        // active ::user::impact will erase/paint itself

      }

      // for ::user::impact-less frame just use the default background fill
      return true;
      //   return user::frame_window::OnEraseBkgnd(pgraphics);

   }

//   LRESULT frame_window::OnRegisteredMouseWheel(WPARAM wParam, LPARAM lParam)
//   {
//
//      LRESULT lResult = 0;
//
//      // convert from MSH_MOUSEWHEEL to ::user::e_message_mouse_wheel
//
//#ifdef WINDOWS_DESKTOP
//
//      unsigned short keyState = 0;
//
//      
//
//      keyState |= psession->is_key_pressed(::user::e_key_control) ? MK_CONTROL : 0;
//      keyState |= psession->is_key_pressed(::user::e_key_shift) ? MK_SHIFT : 0;
//
//      oswindow hwFocus = ::GetFocus();
//      const oswindow hwDesktop = ::get_desktop_window();
//
//      if (hwFocus == nullptr)
//         lResult = send_message(::user::e_message_mouse_wheel, (wParam << 16) | keyState, lParam);
//      else
//      {
//         do
//         {
//            lResult = ::SendMessage(hwFocus, ::user::e_message_mouse_wheel,
//                                    (wParam << 16) | keyState, lParam);
//            hwFocus = ::GetParent(hwFocus);
//         }
//         while (lResult == 0 && hwFocus != nullptr && hwFocus != hwDesktop);
//      }
//
//#else
//
//      throw ::interface_only();
//
//#endif
//
//      return lResult;
//
//   }


   void frame_window::ActivateFrame(::e_display edisplay)
   // nCmdShow is the normal show mode this frame should be in
   {
      // translate default nCmdShow (-1)
      if (edisplay == e_display_default)
      {

         if (!::is_visible(const_layout().sketch().display()))
         {

            edisplay = e_display_normal;

         }
         else if (layout().is_iconic())
         {

            edisplay = e_display_normal;

         }
         else
         {

            edisplay = const_layout().sketch().display();

         }

      }

      if(!const_layout().sketch().zorder().is_change_request() || const_layout().sketch().zorder() != e_zorder_top)
      {

         order_top();

      }

      if (edisplay != e_display_default)
      {

         //lock_sketch_to_design lockSketchToDesign(this);

         display(edisplay);

         set_need_layout();

         set_need_redraw();

      }

      set_reposition();

      set_need_layout();

      set_need_redraw();

      post_redraw();

   }


   bool frame_window::IsTracking() const
   {

      return false;

   }


   void frame_window::_001OnSysCommand(::message::message * pmessage)
   {

   }


   void frame_window::DelayUpdateFrameTitle()
   {

      m_nIdleFlags |= idleTitle;

   }


   void frame_window::DelayRecalcLayout(bool bNotify)
   {

      m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0));

   }


   bool frame_window::InModalState() const
   {

      return m_cModalStack != 0;

   }


//   void frame_window::load_toolbar(const ::atom & idToolbar, const ::scoped_string & scopedstrToolbar, unsigned int dwCtrlStyle, unsigned int uStyle)
//   {
//
//      throw ::interface_only();
//
//      return false;
//
//   }


   // ::berg::application* frame_window::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::berg::session* frame_window::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::berg::system* frame_window::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::berg::user* frame_window::user()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }



   void frame_window::common_construct()
   {

      m_sizeMinimum.cx() = 0;
      m_sizeMinimum.cy() = 0;
      m_nWindow = -1;                 // unknown interaction_impl ID
      m_bAutoMenuEnable = true;       // auto enable on by default
      m_nIDTracking = 0;
      m_nIDLastMessage = 0;

      m_cModalStack = 0;              // initialize modality support
      m_nIdleFlags = 0;               // no idle work at start
      m_rectangleBorder.Null();
      m_dwPromptContext = 0;

      m_pNextFrameWnd = nullptr;         // not in list_base yet

      m_bInRecalcLayout = false;
      m_nShowDelay = -1;              // no delay pending

      AddFrameWnd();

   }


   // query end session for main frame will attempt to close it all down
   void frame_window::_001OnQueryEndSession(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void frame_window::on_message_set_focus(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   void frame_window::OnUpdateControlBarMenu(::message::command * pcommand)
   {

   }


   bool frame_window::OnBarCheck(unsigned int nID)
   {

      __UNREFERENCED_PARAMETER(nID);

      return false;

   }


   void frame_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bWindowFrame && !session()->savings()->is_trying_to_save(::e_resource_display_bandwidth))
      {

      }

   }


   void frame_window::on_message_size(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   ::pointer<::user::interaction>frame_window::WindowDataGetWnd()
   {

      return this;

   }


   void frame_window::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::main_window::handle(ptopic, phandlercontext);

   }


   void frame_window::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pimpactsystem = m_pimpactsystem;

      ::atom atomImpactSystem;

      if (pimpactsystem)
      {

         atomImpactSystem = pimpactsystem->m_atomImpactSystem;

      }

      if (atomImpactSystem.m_eimpact == (enum_impact)FONTSEL_IMPACT)
      {

         information() << "FontSelImpact Frame";

      }

      ::user::main_window::_000OnDraw(pgraphics);

//      bool bUpdateBuffer;
//
//      bool bUpdateWindow;
//
//      auto type = ::type(this);
//
//      if (type.name().contains("app_veriwell_keyboard") && type.name().contains("main_frame"))
//      {
//
//         //informationf("app_veriwell_keyboard::main_frame");
//
//      }
//      else if(type.name().contains("simple_child_frame"))
//      {
//
//         //informationf("simple_child_frame");
//
//      }
//
//      sketch_to_design(bUpdateBuffer, bUpdateWindow);

//      if (!is_window_visible() || layout().is_iconic())
//      {
//
//         return;
//
//      }

//      if (m_bSketchToDesignLayout)
//      {
//
//         m_bSketchToDesignLayout = false;
//
//         design_layout(pgraphics);
//
//      }

//      auto pstyle = get_style(pgraphics);
//
//      bool bBlurBackground = get_draw_flags(pstyle).has(::user::e_flag_blur_background);
//
//      
//
//      if (bBlurBackground)
//      {
//
//         _001DrawThis(pgraphics);
//
//         _001DrawChildren(pgraphics);
//
//         _008CallOnDraw(pgraphics);
//
//      }
//      else if (!session()->savings()->is_trying_to_save(::e_resource_processing)
//               && !session()->savings()->is_trying_to_save(::e_resource_display_bandwidth)
//               && !session()->savings()->is_trying_to_save(::e_resource_memory))
//      {
//
//#if TEST
//
//         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//         pgraphics->fill_solid_rect_dim(0, 0, 100, 100, argb(128, 255, 0, 0));
//
//#endif
//
//         //return;
//
//         _001DrawThis(pgraphics);
//
//         _001DrawChildren(pgraphics);
//
//         if(m_bOverdraw)
//         {
//
//            _008CallOnDraw(pgraphics);
//
//         }
//
//#if TEST
//
//         pgraphics->fill_solid_rect_dim(0, 100, 100, 100, argb(128, 0, 0, 255));
//
//#endif
//
//      }
//      else
//      {
//
//#if TEST
//
//         pgraphics->fill_rectangle(60, 10, 50, 50, argb(128, 190, 180, 90));
//
//#endif

//         _001DrawThis(pgraphics);
//
//         _001DrawChildren(pgraphics);
//
//         if(m_bOverdraw)
//         {
//
//            _008CallOnDraw(pgraphics);
//
//         }

//#if TEST
//
//         pgraphics->fill_rectangle(10, 60, 50, 50, argb(128, 190, 180, 90));
//
//#endif
//
//      }


   }


   void frame_window::_001OnNcDraw(::draw2d::graphics_pointer &pgraphics)
   {

      //return;

      //information() << "user::frame_window::_001OnNcDraw graphics offset : " << pgraphics->get_origin();

      auto pstyle = get_style(pgraphics);

      //information() << "user::frame_window::_001OnNcDraw graphics offset (2) : " << pgraphics->get_origin();

//      ::int_rectangle rectangleX;
//
//      this->rectangle(rectangleX);

      if(pstyle)
      {

         ::get_task()->payload("debug") = 123;

         if (pstyle->_001OnDrawMainFrameBackground(pgraphics, this))
         {

            //_001DrawThis(pgraphics);

            //_001DrawChildren(pgraphics);

            //_008CallOnDraw(pgraphics);

            return;

         }

      }

      ::user::main_window::_001OnNcDraw(pgraphics);

   }


   void frame_window::add_control_bar(::user::control_bar *pcontrolbar)
   {

      m_controlbara.add_unique(pcontrolbar);

      //return ::success;

   }


   void frame_window::erase_control_bar(::user::control_bar * pcontrolbar)
   {

      m_controlbara.erase(pcontrolbar);

      //return ::success;

   }


   bool frame_window::has_command_handler(::message::command * pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

      //if (m_pviewActive != nullptr)
      //{

      //   if (m_pviewActive->has_command_handler(pcommand))
      //   {

      //      return true;

      //   }

      //}

      //if (get_parent() != nullptr)
      //{

      //   if (get_parent()->has_command_handler(pcommand))
      //   {

      //      return true;

      //   }

      //}

      return false;

   }


   ::int_rectangle frame_window::hosting_rectangle(::user::enum_layout elayout)
   {
      
      if(m_bWindowFrame)
      {
         
         return m_rectangleHosting;
         
      }
      
      return ::user::main_window::hosting_rectangle(elayout);

   }


} // namespace user



