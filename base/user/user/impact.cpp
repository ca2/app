#include "framework.h"
#include "impact.h"
#include "document.h"
#include "frame_window.h"
#include "impact_system.h"
#include "toolbar.h"
#include "impact_data.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "acme/platform/system.h"
#include "aura/message/user.h"
#include "aura/user/user/system.h"
#include "aura/user/user/interaction_array.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/windowing/window.h"
#include "base/platform/session.h"
#include "base/user/user/place_holder.h"
#include "base/user/user/user.h"


namespace user
{


   impact::impact()
   {

      m_bToolbar = false;

      m_bEmptyAreaIsClientArea = false;

      //m_bExtendOnParent = true;


   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::box::install_message_routing(pchannel);

      //MESSAGE_LINK(WM_VIEW, pchannel, this, &impact::_001OnImpact);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &impact::on_message_left_button_down);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &impact::on_message_left_button_up);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &impact::on_message_mouse_move);
      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &impact::on_message_destroy);
      //      MESSAGE_LINK(e_message_left_button_down    , pchannel, this, &impact::on_message_right_button_down);
      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &impact::on_message_middle_button_down);
      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &impact::on_message_right_button_down);


      MESSAGE_LINK(e_message_mouse_activate, pchannel, this, &impact::_001OnMouseActivate);
      //      MESSAGE_LINK(e_message_destroy        , pchannel, this, &impact::on_message_destroy);
      //    MESSAGE_LINK(e_message_create        , pchannel, this, &impact::on_message_create);

      // Standard commands for split pane
      //  //      add_command_handler(ID_WINDOW_SPLIT , &impact::_001OnSplitCmd);
      //    connect_command_probe(ID_WINDOW_SPLIT ,  &impact::_001OnUpdateSplitCmd);

      // Standard commands for next pane
      //  connect_command_probe(ID_NEXT_PANE    , &impact::_001OnUpdateNextPaneMenu);
      //add_command_handler(ID_NEXT_PANE   , &impact::_001OnNextPaneCmd);
      //      connect_command_probe(ID_PREV_PANE    , &impact::_001OnUpdateNextPaneMenu);
      //    add_command_handler(ID_PREV_PANE    , &impact::_001OnNextPaneCmd);

      //}}__MSG_MAP
      // special command for Initial Update


      /* ON_e_message_mouse_activate()

      // Standard commands for split pane
      ON_COMMAND_EX(ID_WINDOW_SPLIT, &impact::OnSplitCmd)
      ON_UPDATE_::message::command(ID_WINDOW_SPLIT, &impact::OnUpdateSplitCmd)

      // Standard commands for next pane
      ON_UPDATE_::message::command(ID_NEXT_PANE, &impact::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_NEXT_PANE, &impact::OnNextPaneCmd)
      ON_UPDATE_::message::command(ID_PREV_PANE, &impact::OnUpdateNextPaneMenu)
      ON_COMMAND_EX(ID_PREV_PANE, &impact::OnNextPaneCmd)
      //}}__MSG_MAP
      // special command for Initial Update
      ON_MESSAGE_VOID(WM_INITIALUPDATE, impact::OnInitialUpdate) */

   }


   ////////////////////////////////////////////////////////////////////////////
   //
   // ::user::impact second phase construction - bind to ::user::document

   bool impact::pre_create_window(::user::system * pusersystem)
   {

      //ASSERT(pusersystem->m_createstruct.style & WS_CHILD);


//#ifdef WINDOWS_DESKTOP
//
//      if (pusersystem->m_createstruct.style & WS_BORDER)
//      {
//
//         pusersystem->m_createstruct.dwExStyle |= WS_EX_CLIENTEDGE;
//
//         pusersystem->m_createstruct.style &= ~WS_BORDER;
//
//      }
//
//
//#endif


      return true;

   }


   void impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pmessagecreate(pmessage);

      if (get_parent()->is_frame_window() ||
         get_parent()->is_place_holder())
      {

         m_bExtendOnParentHostingArea = true;

      }

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         ASSERT(::user::impact::get_document() == nullptr);

         auto pusersystem = m_pusersystem;

         if (pusersystem && pusersystem->m_pdocumentCurrent != nullptr)
         {

            ::pointer<::user::document>pdocument = pusersystem->m_pdocumentCurrent;

            pdocument->add_impact(this);

         }

         if(::user::impact::get_document() == nullptr)
         {

            warning()(e_trace_category_appmsg) << "Warning: Creating a pane with no ::user::document.";

         }

         auto pframe = get_typed_parent < ::user::frame_window >();

         if (pframe != nullptr && pframe->m_pviewMain == nullptr)
         {

            pframe->m_pviewMain = this;

         }

      }

      if(pmessagecreate->previous())
      {

         return;

      }

      {

         auto ptopic = create_topic(::id_on_create_impact);

         ptopic->m_puserelement              = this;

         ptopic->m_actioncontext.m_pmessage    = pmessage;

         ptopic->m_actioncontext.add(e_source_initialize);

         route(ptopic);

      }

      pmessagecreate->m_lresult = 0;

   }


   void impact::on_message_destroy(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto pframe = parent_frame();

      if (pframe != nullptr && pframe->get_active_impact() == this)
      {

         pframe->set_active_impact(nullptr, false);    // deactivate during death

      }

      if (m_pdocument != nullptr)
      {

         m_pdocument->erase_impact(this);

      }

   }


   void impact::destroy()
   {

      ::user::interaction::destroy();

   }


   void impact::initialize_impact(::user::document * pdocument)
   {

      //auto estatus = 
      
      ::user::box::initialize(pdocument);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pdocument =  pdocument;

      if (!m_pdocument && pdocument)
      {

         throw ::exception(error_wrong_type);

      }

//      _set_data(0, pdocument->get_data(0));



      //return estatus;

   }


   //void impact::CalcWindowRect(::int_rectangle * pClientRect, unsigned int nAdjustType)

   //{
   //   /* trans   ENSURE_ARG(pClientRect != nullptr);

   //   if (nAdjustType != 0)
   //   {
   //   // allow for special client-edge style
   //   ::AdjustWindowRectEx(pClientRect, 0, false, GetExStyle());


   //   // default behavior for in-place editing handles scrollbars
   //   unsigned int uStyle = GetStyle();
   //   if (uStyle & WS_VSCROLL)
   //   {
   //   int nAdjust = ::windows_definition::Data.cxVScroll;
   //   if (uStyle & WS_BORDER)
   //   nAdjust -= CX_BORDER;
   //   pClientRect->right() += nAdjust;

   //   }
   //   if (uStyle & WS_HSCROLL)
   //   {
   //   int nAdjust = ::windows_definition::Data.cyHScroll;
   //   if (uStyle & WS_BORDER)
   //   nAdjust -= CY_BORDER;
   //   pClientRect->bottom() += nAdjust;

   //   }
   //   return;
   //   }*/

   //   // call default to place borders outside of client int_rectangle
   //   ::user::interaction::CalcWindowRect(pClientRect, nAdjustType);

   //}

   /////////////////////////////////////////////////////////////////////////////
   // Command routing

   void impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      if(pcommand->is_handled(this))
      {

         return;

      }

      pcommand->handle(this);

      ::user::interaction_base::route_command(pcommand);

      if(pcommand->m_bRet)
      {

         return;

      }

      auto pdocument = get_document();

      if (pdocument)
      {

         pdocument->command_handler(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

      ::pointer<::user::interaction>puserinteractionParent = get_parent();

      if (puserinteractionParent)
      {

         puserinteractionParent->route_command(pcommand, false);

      }
      else
      {

         ::pointer<::channel> pchannel = application();

         if (pchannel)
         {

            pchannel->route_command(pcommand);

         }

      }

   }


   void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::box::handle(ptopic, phandlercontext);

      if (ptopic)
      {

         if (ptopic->id() == id_initial_update)
         {

            if (get_document()->is_opened())
            {

               update_impact();

            }

         }

      }

   //   //call_update(id_initial_update);        // initial update

   }


   //void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   ::user::box::handle(ptopic, phandlercontext);

   //   //if (pHint != nullptr)
   //   //{
   //   //   if (base_class < ::update > ::bases(pHint))
   //   //   {
   //   //      ::update * pupdate = dynamic_cast < ::update * > (pHint);
   //   //      OnImpactUpdateHint(pSender, lHint, pupdate);
   //   //   }
   //   //}

   //   //if(ptopic->id() == id_set_edit_file)
   //   //{

   //   //   post_simple_command(e_simple_command_set_edit_file, pparticle);

   //   //}

   //   //if (lHint> update_begin && lHint < update_end)
   //   //{
   //   //   on_simple_impact_update_hint(pSender, (e_hint)lHint, pHint);
   //   //}
   //   //ASSERT(pimpact != this);
   //   //UNUSED(pSender);     // unused in release builds

   //   // invalidate the entire pane, erase background too
   //   //Invalidate(true);

   //   //papp->on_update_impact(this,pSender,lHint,pHint);

   //}

   //void impact::on_simple_impact_update_hint(::pointer<::user::impact>pviewSender, e_hint ehint, object * pupdate)
   //{

   //   switch (ehint)
   //   {
   //      break;
   //   default:
   //      break;
   //   };

   //}

   //void impact::OnImpactUpdateHint(::pointer<::user::impact>pSender, LPARAM lHint, ::update * pHint)
   //{
   //   __UNREFERENCED_PARAMETER(pimpact);
   //   __UNREFERENCED_PARAMETER(eupdate);
   //   __UNREFERENCED_PARAMETER(pHint);
   //}


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact selection support

   bool impact::IsSelected(const object* pDocItem) const
   {
      ASSERT_VALID(pDocItem);
      //  UNUSED(pDocItem);    // unused in release builds

      return false;   // not implemented, so not selected
   }


   bool impact::has_toolbar()
   {

      return m_bToolbar;

   }


   ::atom impact::get_toolbar_id()
   {

      return get_document()->m_pimpactsystem->id() + "/" + class_title();

   }


   toolbar * impact::get_toolbar(::user::frame_interaction * pframewindow, bool bCreate)
   {

      if (!has_toolbar())
      {

         throw ::exception(error_wrong_state);

      }

      auto toolbartransport = pframewindow->m_puserframewindow->get_toolbar(get_toolbar_id(), bCreate);

      if (!toolbartransport)
      {

         return toolbartransport;

      }

      return toolbartransport;

   }


   void impact::OnActivateImpact(bool bActivate, ::pointer<::user::impact>pActivateImpact, ::pointer<::user::impact>pDeactivateImpact)
   {

      auto pdocument = get_document();
      
      auto pframewindow = parent_frame();

      if (bActivate)
      {

         // take the focus if this frame/::user::impact/pane is now active
         if (IsTopParentActive())
         {

            set_keyboard_focus();

         }
         
         if(pframewindow)
         {
            
            if (pdocument && pdocument->has_toolbar())
            {
               
               auto ptoolbar = pdocument->get_toolbar(pframewindow, true);
               
               pframewindow->show_control_bar(ptoolbar);
               
            }
            
            if (has_toolbar())
            {
               
               auto ptoolbar = get_toolbar(pframewindow, true);
               
               pframewindow->show_control_bar(ptoolbar);
               
            }
            
         }

      }
      else
      {

         auto pframewindow = parent_frame();
         
         if(pframewindow)
         {
            
            if (pdocument && pdocument->has_toolbar())
            {
               
               auto ptoolbar = pdocument->get_toolbar(pframewindow, false);
               
               if(::is_set(ptoolbar))
               {
                  
                  pframewindow->hide_control_bar(ptoolbar);
                  
               }
               
            }
            
            if (has_toolbar())
            {
               
               auto ptoolbar = get_toolbar(pframewindow, false);
               
               if (::is_set(ptoolbar))
               {
                  
                  pframewindow->hide_control_bar(ptoolbar);
                  
               }
               
            }
            
         }

      }

   }


   void impact::OnActivateFrame(enum_activate eactivate, ::pointer<::user::frame_window>/*pFrameWnd*/)
   {

   }


   /* trans
   int impact::OnMouseActivate(::windowing::window * pDesktopWnd, unsigned int nHitTest, const ::atom & atom)
   {
   int nResult = ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
   if (nResult == MA_NOACTIVATE || nResult == MA_NOACTIVATEANDEAT)
   return nResult;   // frame does not want to activate

   ::pointer<::user::frame_window>pParentFrame = get_parent_frame();
   if (pParentFrame != nullptr)
   {
   // eat it if this will cause activation
   ASSERT(pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame));

   // either re-activate the current ::user::impact, or set this ::user::impact to be active
   ::pointer<::user::impact>pimpact = pParentFrame->get_active_impact();
   oswindow oswindow_Focus = ::GetFocus();
   if (pimpact == this &&
   get_handle() != oswindow_Focus && !::IsChild(get_handle(), oswindow_Focus))
   {
   // re-activate this ::user::impact
   OnActivateImpact(true, this, this);
   }
   else
   {
   // activate this ::user::impact
   pParentFrame->set_active_impact(this);
   }
   }
   return nResult;
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact scrolling support

   bool impact::OnScroll(unsigned int /*nScrollCode*/, unsigned int /*nPos*/, bool /*bDoScroll*/)
   {
      return false;
   }

   //bool impact::OnScrollBy(size /*sizeScroll*/, bool /*bDoScroll*/)
   //{
   //   return false;
   //}

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact drag/drop support

   ///*DROPEFFECT impact::OnDragScroll(unsigned int /*dwKeyState*/, int_point /*int_point*/)
   //{
   //#ifndef ___NO_OLE_SUPPORT
   // return DROPEFFECT_SCROLL; // this means do the default
   //#else
   // return 0;
   //#endif
   //}

   //DROPEFFECT impact::OnDragEnter(COleDataObject* /*pDataObject*/,
   // unsigned int /*dwKeyState*/, int_point /*int_point*/)
   //{
   // return 0;   // DROPEFFECT_NONE
   //}

   //DROPEFFECT impact::OnDragOver(COleDataObject* /*pDataObject*/,
   //unsigned int /*dwKeyState*/, int_point /*int_point*/)
   //{
   //return 0;   // DROPEFFECT_NONE
   //}

   //bool impact::OnDrop(COleDataObject* /*pDataObject*/,
   //DROPEFFECT /*dropEffect*/, int_point /*int_point*/)
   //{
   // return false;
   //}

   //DROPEFFECT impact::OnDropEx(COleDataObject* /*pDataObject*/,
   // DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, int_point /*int_point*/)
   //{
   // return (DROPEFFECT)-1;  // not implemented
   //}

   //void impact::OnDragLeave()
   //{
   //}

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact splitting commands


   /*   CScrollBar* impact::GetScrollBarCtrl(int nBar) const
      {

         ///ASSERT(nBar == SB_HORZ || nBar == SB_VERT);
         // trans   if (GetStyle() & ((nBar == SB_HORZ) ? WS_HSCROLL : WS_VSCROLL))
         //   {
         // it has a regular windows style scrollbar (no control)
         //      return nullptr;
         //   }


         return nullptr;
      }*/


   void impact::set_impact_title(const ::scoped_string & scopedstrImpactTitle)
   {

      m_strImpactTitle = scopedstrImpactTitle;

   }


   string impact::get_impact_title() const
   {

      return m_strImpactTitle;

   }


   enum_window_type impact::get_window_type()
   {

      return e_window_type_impact;

   }



   void impact::OnUpdateSplitCmd(::message::command* pCmdUI)
   {
      __UNREFERENCED_PARAMETER(pCmdUI);
      /*ENSURE_ARG(pCmdUI != nullptr);
      CSplitterWnd* pSplitter = GetParentSplitter(this, false);
      pCmdUI->enable(pSplitter != nullptr && !pSplitter->IsTracking());*/
   }

   bool impact::OnSplitCmd(unsigned int)
   {
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, false);
      if (pSplitter == nullptr)
      return false;

      ASSERT(!pSplitter->IsTracking());
      pSplitter->DoKeyboardSplit();*/
      return true;    // attempted at least
   }

   void impact::OnUpdateNextPaneMenu(::message::command* pCmdUI)
   {
      __UNREFERENCED_PARAMETER(pCmdUI);
      /*ASSERT(pCmdUI->m_nID == ID_NEXT_PANE ||
      pCmdUI->m_nID == ID_PREV_PANE);
      CSplitterWnd* pSplitter = GetParentSplitter(this, false);
      pCmdUI->enable(pSplitter != nullptr &&
      pSplitter->CanActivateNext(pCmdUI->m_nID == ID_PREV_PANE));*/
   }

   bool impact::OnNextPaneCmd(unsigned int nID)
   {
      __UNREFERENCED_PARAMETER(nID);
      /*   CSplitterWnd* pSplitter = GetParentSplitter(this, false);
      if (pSplitter == nullptr)
      return false;

      ASSERT(nID == ID_NEXT_PANE || nID == ID_PREV_PANE);
      pSplitter->ActivateNext(nID == ID_PREV_PANE);*/
      return true;
   }

   ///////////////////////////////////////////////////////////////////////////////
   //// Printing support virtual functions (others in viewpr.cpp)

   //void impact::OnPrepareDC(::draw2d::graphics_pointer & pgraphics, CPrintInfo* pInfo)
   //{
   //   __UNREFERENCED_PARAMETER(pInfo);
   //   ASSERT_VALID(pgraphics);
   //   UNUSED(pgraphics); // unused in release builds

   //   // Default to one page printing if doc length not known
   //}




//   /////////////////////////////////////////////////////////////////////////////
//   // ::user::impact diagnostics
//
//   void impact::dump(dump_context & dumpcontext) const
//   {
//      ::user::interaction::dump(dumpcontext);
//
//      //if (((impact *) this)->::user::impact::get_document() != nullptr)
//      //   dumpcontext << "with ::user::document: ";
//      //else
//      //   dumpcontext << "with no ::user::document\n";
//   }
//
//
//   void impact::assert_ok() const
//   {
//
//      ::user::interaction::assert_ok();
//
//   }


   // ::base::application* impact::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::base::session* impact::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::base::system* impact::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::base::user* impact::user()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }


   void impact::set_notify_user_interaction(::user::interaction* puserinteractionNotify)
   {

      m_puserinteractionImpactNotify = puserinteractionNotify;

      if (!m_puserinteractionImpactNotify && puserinteractionNotify)
      {

         throw ::exception(error_wrong_type);

      }

      //return ::success;

   }

   //void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   //if (pusermessage->m_wparam == ::user::impact_message_update)
   //   //{

   //   //   ::user::document::update * pupdate = (::user::document::update *) pusermessage->m_lparam.m_lparam;

   //   //   on_update(pupdate->m_pSender, pupdate->m_lHint, pupdate->m_pHint);

   //   //}
   //   if (pusermessage->m_wparam == ::user::impact_message_close_document)
   //   {

   //      get_document()->close_document();

   //   }

   //}


   ::pointer<::user::interaction>impact::create_impact(::user::interaction * pimpactAlloc, ::user::impact_data * pimpactdata, ::user::interaction * pviewLast)
   {

      ::pointer<::request>pcreate(e_create, this);

      auto pusersystem = __allocate ::user::system();

      m_pusersystem = pusersystem;

      pusersystem->m_puserprimitiveNew = pimpactAlloc;

      pusersystem->m_puserprimitiveLastImpact = pviewLast;

      pusersystem->m_pdocumentCurrent = get_document();

      auto pinteraction = pusersystem->create_impact(pimpactdata->m_pplaceholder, pimpactdata->id());

      return pinteraction;

   }


   ::pointer<::user::interaction>impact::create_impact(const ::type_atom & typeatom, ::user::document * pdocument, ::user::interaction * puserinteractionParent, const ::atom & atom, ::user::interaction * pviewLast, ::user::impact_data * pimpactdata)
   {

      ::pointer<::request>prequest;

      ::pointer < ::user::system > pusersystem = m_pusersystem;

      __check_refdbg
      
      if(!pusersystem)
      {

         __check_refdbg

         pusersystem = __create_new < ::user::system >();

         __check_refdbg
         
      }

      __check_refdbg

      if (pusersystem->m_prequest)
      {

         prequest= pusersystem->m_prequest;

      }
      else
      {

         __check_refdbg

         __construct_new(pusersystem->m_prequest);

         __check_refdbg

         prequest = pusersystem->m_prequest;

         prequest->m_pmatterUserPayload = pusersystem;

      }

      if (::is_set(pimpactdata))
      {

         pusersystem->m_pimpactdata = pimpactdata;

      }

      pusersystem->m_typeatomNewImpact = typeatom;

      pusersystem->m_puserprimitiveLastImpact = pviewLast;

      __check_refdbg

      if (pdocument == nullptr)
      {

         pusersystem->m_pdocumentCurrent = get_document();

      }
      else
      {

         pusersystem->m_pdocumentCurrent = pdocument;

      }

      if (puserinteractionParent == nullptr)
      {

         puserinteractionParent = this;

      }

      ::atom idCreate(atom);

      if (idCreate.is_empty())
      {

         idCreate = (const ::atom &) pusersystem->m_typeatomNewImpact.name();

      }

      __check_refdbg

      auto pinteraction = pusersystem->create_impact(puserinteractionParent, idCreate);

      __check_refdbg

      return pinteraction;

   }


   ::pointer<::user::interaction>create_impact(const ::type_atom & typeatom, ::user::document * pdocument, ::user::interaction * puserinteractionParent, const ::atom & atom, ::user::interaction * pviewLast)
   {

      ::pointer<::request>pcreate(e_create_new, pdocument);

      auto pusersystem= __allocate ::user::system();

      pusersystem->m_typeatomNewImpact = typeatom;

      pusersystem->m_puserprimitiveLastImpact = pviewLast;

      pusersystem->m_pdocumentCurrent = pdocument;

      auto pinteraction = pusersystem->create_impact(puserinteractionParent, atom);

      return pinteraction;

   }


   void impact::on_message_left_button_down(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      pmessage->previous();

      //if (pmessage->m_bRet)
      //{

      //   return;

      //}

      if (parent_frame() != nullptr)
      {

         parent_frame()->set_active_impact(this);

      }

   }


   void impact::on_message_left_button_up(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      //auto pmouse = pmessage->m_union.m_pmouse;

   }


   void impact::on_message_mouse_move(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);
      //   auto pmouse = pmessage->m_union.m_pmouse;

   }


   bool impact::is_impact()
   {

      return true;

   }


   void impact::call_handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if (ptopic->id() == id_initial_update)
      {

         if (!get_document())
         {

            return;

         }

         if (!get_document()->is_opened())
         {

            return;

         }

      }

      ::user::box::call_handle(ptopic, phandlercontext);

   }


   ::user::document * impact::get_document() const
   {

      ASSERT(::is_set(this));
      return ((::user::impact *) this)->m_pdocument;

   }


   ::data::data * impact::_get_data(const ::atom & atom)
   {

      return m_pdocument->get_data(atom);

   }


   //void impact::collaborate(::job * pjob)
   //{
   //   {
   //      ::user::job * puserjob = (dynamic_cast < ::user::job * > (pjob));
   //      if (puserjob != nullptr)
   //      {
   //         puserjob->m_puserinteraction = this;
   //      }
   //   }
   //}


   int impact::get_total_page_count(::handler_context * pcontext)
   {

      return 1;

   }


   //void impact::on_draw_impact_nc(::image::image *pimage)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);

   //}

   //void impact::on_draw_impact(::draw2d::graphics_pointer & pgraphics, pointer_array < ::data::data > spadata)
   //{

   //   __UNREFERENCED_PARAMETER(pgraphics);
   //   __UNREFERENCED_PARAMETER(spadata);

   //}

   //void impact::defer_draw_impact(::image::image *pimage)
   //{

   //   if (get_document() == nullptr)
   //      return;

   //   pointer_array < ::data::data > spadata = get_document()->m_dataa;

   //   //spadata.add(get_document()->m_spdata);

   //   object_spa synchronization;

   //   for (::collection::index i = 0; i < spadata.get_count(); i++)
   //   {

   //      synchronization.add(spadata[i].data_mutex());

   //   }

   //   retry_multi_lock synchronouslock(synchronization, ::time(1), ::time(1));

   //   try
   //   {
   //      on_draw_impact(pgraphics, spadata);
   //   }
   //   catch (...)
   //   {
   //   }

   //}

   //void impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   on_draw_impact_nc(pgraphics);

   //   int iTry = 0;

   //   bool bOk;

   //retry:

   //   bOk = true;

   //   try
   //   {
   //      defer_draw_impact(pgraphics);
   //   }
   //   catch (...)
   //   {
   //      bOk = false;
   //   }

   //   iTry++;
   //   if (!bOk && iTry < 9)
   //      goto retry;

   //}


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact second phase construction - bind to document

   //const char _vfxWndFrameOrImpact[] = __WNDFRAMEORVIEW;




   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact drawing support


   /*void impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {
   call_update(id_initial_update);        // initial update
   }*/

   /*   void impact::on_update(::user::impact * pSender, LPARAM lHint, object * pHint)
   {
   ::user::impact::handle(ptopic, phandlercontext);
   }
   */
   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact selection support

   /*   bool impact::IsSelected(const object* pDocItem) const
   {
   ASSERT_VALID(pDocItem);
   //      UNUSED(pDocItem);    // unused in release builds

   return false;   // not implemented, so not selected
   }*/


   void impact::_001OnMouseActivate(::message::message * pmessage)
   {
      ::pointer<::message::mouse_activate>pmouseactivate(pmessage);
      pmessage->previous();
      //int nResult = pmouseactivate->get_lresult();

      if (pmouseactivate->get_message() == e_mouse_activate
            || pmouseactivate->get_message() == e_mouse_activate_no_activate_and_eat)
      {

         pmouseactivate->m_lresult = pmouseactivate->get_message(); // frame does not want to activate

         pmouseactivate->m_bRet = true;

      }

      auto pParentFrame = parent_frame();

      if (pParentFrame != nullptr)
      {

         // eat it if this will cause activation
         ASSERT(pParentFrame == pmouseactivate->get_desktop_window()
                || pmouseactivate->get_desktop_window()->is_child(pParentFrame));

         // either re-activate the current ::user::impact, or set this ::user::impact to be active
         ::pointer<::user::impact>pimpact = pParentFrame->get_active_impact();

         auto puser = user();

         if(puser)
         {

            ::pointer<::user::interaction>puserinteractionFocus = puser->get_keyboard_focus(window()->m_puserthread);

            if (pimpact == this
            && this != puserinteractionFocus
            && !is_child(puserinteractionFocus))
            {

               // re-activate this ::user::impact
               OnActivateImpact(true, this, this);

            }
            else
            {

               // activate this ::user::impact
               pParentFrame->set_active_impact(this);

            }

         }

      }

      pmouseactivate->m_lresult = pmouseactivate->get_message();

      pmouseactivate->m_bRet = true;

   }


   void impact::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      return ::user::box::_001CallOnDraw(pgraphics);
      //on_context_offset(pgraphics);

      //synchronous_lock slImpact(synchronization());

      ////synchronous_lock slDocument(get_document()->synchronization());.

      //{

      //   draw_select ds(this, pgraphics);

      //   _001OnDraw(pgraphics);

      //}

   }


   void impact::on_select()
   {
      
      auto pParentFrame = parent_frame();

      if (pParentFrame != nullptr)
      {
         // eat it if this will cause activation
         /*      ASSERT(pParentFrame == pmouseactivate->get_desktop_window()
         || pmouseactivate->get_desktop_window()->IsChild(pParentFrame));*/

         // either re-activate the current ::user::impact, or set this ::user::impact to be active
         ::pointer<::user::impact>pimpact = pParentFrame->get_active_impact();

         auto puser = user();

         ::pointer<::user::interaction>puserinteractionFocus = puser->get_keyboard_focus(window()->m_puserthread);

         if (pimpact == this
         && this != puserinteractionFocus
         && !is_child(puserinteractionFocus))
         {

            // re-activate this ::user::impact
            OnActivateImpact(true, this, this);

         }
         else
         {

            // activate this ::user::impact
            pParentFrame->set_active_impact(this);

         }

      }

   }


//#ifndef __ANDROID__
//
//   /////////////////////////////////////////////////////////////////////////////
//   // ::user::impact drag/drop support
//
//   DROPEFFECT impact::OnDragScroll(unsigned int /*dwKeyState*/, int_point /*int_point*/)
//   {
//#if !defined(___NO_OLE_SUPPORT) && !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(__ANDROID__) && !defined(SOLARIS)
//      return DROPEFFECT_SCROLL; // this means do the default
//#else
//      return 0;
//#endif
//   }
//
//   DROPEFFECT impact::OnDragEnter(COleDataObject* /*pDataObject*/,
//      unsigned int /*dwKeyState*/, int_point /*int_point*/)
//   {
//      return 0;   // DROPEFFECT_NONE
//   }
//
//   DROPEFFECT impact::OnDragOver(COleDataObject* /*pDataObject*/,
//      unsigned int /*dwKeyState*/, int_point /*int_point*/)
//   {
//      return 0;   // DROPEFFECT_NONE
//   }
//
//   bool impact::OnDrop(COleDataObject* /*pDataObject*/,
//      DROPEFFECT /*dropEffect*/, int_point /*int_point*/)
//   {
//      return false;
//   }
//
//   DROPEFFECT impact::OnDropEx(COleDataObject* /*pDataObject*/,
//      DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, int_point /*int_point*/)
//   {
//      return (DROPEFFECT)-1;  // not implemented
//   }
//
//   void impact::OnDragLeave()
//   {
//   }
//
//
//#endif // __ANDROID__




   void impact::_001OnUpdateSplitCmd(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnSplitCmd(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnUpdateNextPaneMenu(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   void impact::_001OnNextPaneCmd(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }


   // // IMPLEMENT_DYNAMIC for ::user::impact is in wincore.cpp for .OBJ granularity reasons

   //// IMPLEMENT_DYNAMIC(CSplitterWnd, ::user::interaction)   // for __swap tuning
   //// IMPLEMENT_DYNAMIC(CCtrlImpact, ::user::impact)

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact's OnPrintThumbnail.  Here to force linkage

   void impact::_001OnFilePrintThumbnail(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }


   void impact::_001OnFilePrint(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }



   /*
   ::pointer<::user::interaction>impact::CreateImpact(::pointer<::create>Context, unsigned int nID)
   {
   ASSERT(is_window());
   ASSERT(pContext != nullptr);
   ASSERT(pContext->m_typeatomNewImpact != nullptr);

   // Note: can be a ::user::interaction with post_non_client_destroy self cleanup
   ::pointer<::user::interaction>pimpact =  (psystem->alloc(pContext->m_typeatomNewImpact));
   if (pimpact == nullptr)
   {
   TRACE1("Warning: Dynamic create of ::user::impact type %hs failed.\n",
   pContext->m_typeatomNewImpact.name());
   return nullptr;
   }
   ASSERT_KINDOF(::user::interaction, pimpact);

   // views are always created with a border!
   if (!pimpact->create(nullptr, nullptr, __WS_DEFAULT_VIEW,
   int_rectangle(0,0,0,0), this, nID, (::pointer<::create> pContext))
   {
   TRACE0("Warning: could not create ::user::impact for frame.\n");
   return nullptr;        // can't continue without a ::user::impact
   }

   ::pointer<::user::impact>pimpact =  (pimpact);
   pimpact->handle(::topic * ptopic, ::handler_context * phandlercontext);
   if (::windows_definition::Data.bWin4 && (pimpact->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // erase the 3d style from the frame, since the ::user::impact is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   /*   return pimpact;
   }*/


   /*::pointer<::user::interaction>impact::CreateImpact(::pointer<::create>Context, unsigned int nID, ::user::interaction  * puserinteractionParent)
   {
   ASSERT(puserinteractionParent->is_window());
   ASSERT(pContext != nullptr);
   ASSERT(pContext->m_typeatomNewImpact != nullptr);

   // Note: can be a interaction_impl with post_non_client_destroy self cleanup
   ::windowing::window * pimpact = (puserinteractionParent->psystem->alloc(pContext->m_typeatomNewImpact));
   if (pimpact == nullptr)
   {
   TRACE1("Warning: Dynamic create of ::user::impact type %hs failed.\n",
   pContext->m_typeatomNewImpact.name());
   return nullptr;
   }
   ASSERT_KINDOF(interaction_impl, pimpact);

   // views are always created with a border!
   if (!pimpact->create(nullptr, nullptr, __WS_DEFAULT_VIEW,
   int_rectangle(0,0,0,0), puserinteractionParent, nID, (::pointer<::create> pContext))
   {
   TRACE0("Warning: could not create ::user::impact for frame.\n");
   return nullptr;        // can't continue without a ::user::impact
   }

   ( (pimpact))->handle(::topic * ptopic, ::handler_context * phandlercontext);
   if (::windows_definition::Data.bWin4 && (pimpact->GetExStyle() & WS_EX_CLIENTEDGE))
   {
   // erase the 3d style from the frame, since the ::user::impact is
   //  providing it.
   // make sure to recalc the non-client area
   ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
   }*/
   //   return pimpact;
   //}


   void impact::on_message_right_button_down(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //auto pmouse = pmessage->m_union.m_pmouse;

      parent_frame()->set_active_impact(this);
   }

   void impact::on_message_middle_button_down(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //      auto pmouse = pmessage->m_union.m_pmouse;

      parent_frame()->set_active_impact(this);

   }


   bool impact::has_command_handler(::message::command * pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

//      if (get_document() != nullptr)
//      {
//
//         if (get_document()->has_command_handler(pcommand))
//         {
//
//            return true;
//
//         }
//
//      }
//
//      if (get_parent() != nullptr)
//      {
//
//         if (get_parent()->has_command_handler(pcommand))
//         {
//
//            return true;
//
//         }
//
//      }

      return false;

   }


   void impact::walk_pre_translate_tree(::message::message * pmessage,::pointer<::user::interaction>puiStop)
   {


      try
      {

         parent_frame()->pre_translate_message(pmessage);

      }
      catch(...)
      {

      }

      if (pmessage->m_bRet)
      {
       
         return;

      }

      pre_translate_message(pmessage);

   }


   //string impact::calc_parent_data_key()
   //{

   //   return get_document()->calc_data_key();

   //}


   //bool impact::is_local_data()
   //{

   //   if(::user::box::is_local_data())
   //   {

   //      return true;

   //   }

   //   if(get_document() != nullptr && get_document()->is_local_data())
   //   {

   //      return true;

   //   }

   //   return false;

   //}
/*

   ::user::document * get_document(::user::interaction * pinteraction)
   {

      ::pointer<::user::impact>pimpact = pinteraction;

      if (pimpact != nullptr)
      {

         return nullptr;

      }

      return pimpact->get_document();

   }
*/

} // namespace user



