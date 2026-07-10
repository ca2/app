//
//  userex_impact_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/07/18.
//  Copyright (c) 2018 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "impact_host.h"
#include "impact_host_host.h"
#include "pane_tab_impact.h"
#include "font_impact.h"
#include "acme/constant/user_message.h"
#include "acme/constant/simple_command.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/atom.h"
#include "apex/database/_binary_stream.h"
#include "apex/message/simple_command.h"
#include "acme/handler/request.h"
#include "berg/user/user/tab_pane.h"
#include "berg/user/user/document.h"
#include "berg/user/user/single_document_template.h"
#include "berg/user/simple/child_frame.h"
#include "core/user/user/user.h"
#include "core/platform/application.h"
#include "core/platform/session.h"


namespace userex
{


   impact_host::impact_host()
   {

      m_bExtendOnParentHostingArea = false;

      m_sizeTabbedFrame.cx = 800;
      m_sizeTabbedFrame.cy = 300;
      // m_ptemplateTab = nullptr;
   }


   impact_host::~impact_host() {}


   // void impact_host::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   // void impact_host::dump(dump_context & dumpcontext) const
   //{

   //   ::user::impact::dump(dumpcontext);

   //}


   // ::core::application* impact_host::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* impact_host::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* impact_host::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   void impact_host::install_message_routing(::channel *pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &impact_host::on_message_create);
   }


   void impact_host::on_message_create(::message::message *pmessage)
   {

      m_pimpacthosthost = get_parent();

      m_atomaHandledCommands.append(m_pimpacthosthost->m_idaHandledImpacts);

      ::cast<::berg::application> pbergapplication = m_papplication;

      if (pbergapplication->impact_system("main") != nullptr)
      {

         ::i32_rectangle rectangleTab;

         ::pointer<::user::document> pdocument = pbergapplication->impact_system("main")->get_document();

         if (pdocument != nullptr)
         {

            ::pointer<::userex::pane_tab_impact> ptabimpact = pdocument->get_typed_impact<::userex::pane_tab_impact>();

            if (ptabimpact != nullptr)
            {

               auto pframewindowTab = ptabimpact->get_typed_parent<simple_frame_window>();

               bool bShow = ptabimpact->get_tab_count() >= 1;

               if (!bShow)
               {

                  if (pframewindowTab->is_this_visible())
                  {
                     information() << "-------------------------------------------------------------------";
                     information() << "";
                     information() << "";
                     information() << "pframewindowTab HIDE HIDE HIDE";
                     information() << "";
                     information() << "";
                     pframewindowTab->display(e_display_hide, {});
                  }
               }
               else
               {


                  information() << "-------------------------------------------------------------------";
                  information() << "";
                  information() << "";
                  information() << "pframewindowTab VISIBLE VISIBLE VISIBLE";
                  information() << "";
                  information() << "";
                  auto rectangleRequest = i32_rectangle_dimension(20, 20, 800, 300);

                  // if (!pframewindowTab->is_this_visible() || rectangleRequest !=
                  // pframewindowTab->window_request_rect())
                  {

                     pframewindowTab->order_top();

                     pframewindowTab->place(rectangleRequest);

                     pframewindowTab->display();

                     pframewindowTab->set_need_redraw();
                  }
               }
            }
         }
      }
   }


   void impact_host::on_command(::message::command *pcommand)
   {

      if (m_pimpacthosthost->m_idaHandledImpacts.contains(pcommand->command_id()))
      {

         toggle_impact(pcommand->command_id());
      }

      return ::user::impact::on_command(pcommand);
   }


   void impact_host::_001DefaultLayoutImpact(const ::atom &atomImpactId)
   {

      if (impact_item_frame_window(atomImpactId) == nullptr)
      {

         return;
      }

      ::i32_rectangle rectangle;

      rectangle = this->rectangle();

      auto pframewindow = impact_item_frame_window(atomImpactId);

      pframewindow->order_front();

      pframewindow->place(
         ::i32_rectangle_dimension(rectangle.width() / 4, 0, rectangle.width() / 2, rectangle.height() / 5));

      pframewindow->display();

      pframewindow->set_need_redraw();
   }


   ::pointer<::simple_frame_window> impact_host::_001GetFrame(const ::atom &atomImpactId)
   {

      ::pointer<::user::impact> pimpact = _001GetImpact(atomImpactId);

      if (pimpact.is_null())
      {

         return nullptr;
      }

      auto pframewindow = pimpact->parent_frame();

      if (::is_null(pframewindow))
      {

         return nullptr;
      }

      return pframewindow;
   }


   ::pointer<::user::impact> impact_host::_001GetImpact(const ::atom &atomImpactId)
   {

      ::pointer<::user::document> pdocument = impact_item_document(atomImpactId);

      if (pdocument.is_null())
      {

         return nullptr;
      }

      return pdocument->get_impact();
   }


   void impact_host::handle(::topic *ptopic, ::handler_context *phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);
   }


   bool impact_host::OnUpDownTargetAttach(::user::interaction *pupdown)
   {

      if (m_pimpacthosthost->OnUpDownTargetAttach(pupdown))
      {

         return true;
      }


      if (!tabfy(pupdown))
      {

         return false;
      }

      return true;
   }


   bool impact_host::OnUpDownTargetDetach(::user::interaction *pupdown)
   {

      if (m_pimpacthosthost->OnUpDownTargetDetach(pupdown))
      {

         return true;
      }

      information() << "-------------------------------------------------------------------";
      information() << "";
      information() << "";
      information() << "impact_host::OnUpDownTargetDetach (1)";

      ::pointer<::simple_frame_window> pframewindow = pupdown;

      if (pframewindow.is_set())
      {

         if (!(pframewindow->m_ewindowflag & e_window_flag_window_created))
         {

            pframewindow->m_puserinteractionParent = nullptr;

            return true;
         }

         pframewindow->enable_size();

         pframewindow->enable_move();

         fork(
            [pframewindow, this]()
            {
               ::pointer<simple_frame_window> pframewindowTab;

               ::cast<::berg::application> pbergapplication = m_papplication;

               if (pbergapplication->impact_system("main") != nullptr)
               {

                  ::pointer<::user::document> pdocument = pbergapplication->impact_system("main")->get_document(0);

                  if (pdocument.is_set())
                  {

                     ::pointer<::userex::pane_tab_impact> ptabimpact =
                        pdocument->get_typed_impact<::userex::pane_tab_impact>();

                     pframewindowTab = ptabimpact->parent_frame();
                  }
               }

               {

                  //::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

                  __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

                  pframewindow->set_parent(nullptr);

                  pframewindow->on_frame_position();

                  ::cast<::berg::application> pbergapplication = m_papplication;

                  if (pbergapplication->impact_system("main") != nullptr)
                  {

                     string strId = pframewindow->id();

                     ::pointer<::user::document> pdocument = pbergapplication->impact_system("main")->get_document(0);

                     if (pdocument.is_set())
                     {

                        ::pointer<::userex::pane_tab_impact> ptabimpact =
                           pdocument->get_typed_impact<::userex::pane_tab_impact>();

                        ptabimpact->erase_tab_by_id(pframewindow->id());

                        if (ptabimpact.is_set() && ptabimpact->get_tab_count() <= 0)
                        {

                           ptabimpact->parent_frame()->display(e_display_hide, {});

                           ptabimpact->parent_frame()->set_need_redraw();
                        }
                     }
                  }
               }

               pframewindow->set_need_redraw();

               pframewindow->post_redraw();
            });

         return true;
      }

      return false;
   }


   bool impact_host::is_user_impact_visible(const ::atom &atomImpactId)
   {

      auto p = m_mapImpactItem.find(atomImpactId);

      if (p.is_null())
      {

         return false;
      }

      auto &pimpactitem = p->m_element2;

      if (::is_null(pimpactitem))
      {

         return false;
      }

      return pimpactitem->m_bVisible;
   }


   ::pointer<::userex::pane_tab_impact> impact_host::get_pane_tab_impact()
   {

      ::cast<::berg::application> pbergapplication = m_papplication;

      // if (!pbergapplication->impact_system("main"))
      //{

      //   //m_ptemplateTab = ;;
      //   pbergapplication->add_impact_system(
      //      "main", __initialize_new user::single_document_template(
      //      "main",
      //      ::type<::user::document>(),
      //      ::type<simple_child_frame>(),
      //      ::type<::userex::pane_tab_impact>()));

      //   //user()->initialize(this);

      //}

      ::pointer<::user::document> pdocTab = pbergapplication->impact_system("main")->get_document();

      if (pdocTab == nullptr)
      {

         pdocTab = pbergapplication->impact_system("main")->open_document_file(get_app(), ::e_type_null,
                                                                               __visible(false).is_true(), this);
      }

      return pdocTab->get_typed_impact<::userex::pane_tab_impact>();
   }


   bool impact_host::tabfy(::user::interaction *pupdown)
   {


      information() << "-------------------------------------------------------------------";
      information() << "";
      information() << "";
      information() << "impact_host::tabfy (1)";
      information() << "";
      information() << "";

      // post_procedure([pupdown, this]
      {

         ::pointer<::simple_frame_window> pframewindow = pupdown;

         auto ptabimpact = get_pane_tab_impact();

         {

            if (ptabimpact->is_hosting(pframewindow))
            {

               return true;
            }

            __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

            //::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

            pframewindow->m_bSizeEnable = false;

            pframewindow->m_bMoveEnable = false;

            ::atom atom = pupdown->id();

            ::string strTitle = pframewindow->get_window_text();

            strTitle.set_if_empty(atom.as_string());


            information() << "-------------------------------------------------------------------";
            information() << "";
            information() << "";
            information() << "impact_host::tabfy (2)";
            information() << "";
            information() << "";

            //::user::impact_data* pimpactdata = ptabimpact->host_impact(atom, strTitle, pframewindow,
            //:pframewindow->get_active_document());
            ptabimpact->host_impact(atom, pframewindow, pframewindow->get_active_document());

            ptabimpact->get_tab_by_id(atom)->set_title(strTitle);

            information() << "-------------------------------------------------------------------";
            information() << "";
            information() << "";
            information() << "impact_host::tabfy (3)";
            information() << "";
            information() << "";

            if (pframewindow->m_ewindowflag & e_window_flag_window_created)
            {


               information() << "-------------------------------------------------------------------";
               information() << "";
               information() << "";
               information() << "impact_host::tabfy (3.1)";
               information() << "";
               information() << "";


               ptabimpact->set_current_tab_by_id(atom);

               pframewindow->set_need_layout();

               pframewindow->WindowDataSaveWindowRectangle();
            }
         }


         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "impact_host::tabfy (4)";
         information() << "";
         information() << "";


         if (pframewindow->m_ewindowflag & e_window_flag_window_created)
         {


            information() << "-------------------------------------------------------------------";
            information() << "";
            information() << "";
            information() << "impact_host::tabfy (4.1)";
            information() << "";
            information() << "";

            ptabimpact->parent_frame()->display();

            set_need_layout();

            set_need_redraw();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();
         }
      }

      return true;
   }


   void impact_host::on_layout(::draw2d::graphics_pointer &pgraphics) { ::user::impact::on_layout(pgraphics); }


   ::pointer<::user::document> impact_host::impact_item_document(const ::atom &atomImpactId)
   {
      
      auto p = m_mapImpactItem.find(atomImpactId);

      if (p.is_null())
      {

         return nullptr;
      }

      auto &pimpactitem = p->m_element2;

      if (::is_null(pimpactitem))
      {

         return nullptr;
      }

      return pimpactitem->m_pdocument;

   }


      ::pointer<::simple_frame_window> impact_host::impact_item_frame_window(const ::atom &atomImpactId)
   {

      auto p = m_mapImpactItem.find(atomImpactId);

      if (p.is_null())
      {

         return nullptr;
      }

      auto &pimpactitem = p->m_element2;

      if (::is_null(pimpactitem))
      {

         return nullptr;
      }

      return pimpactitem->m_pframewindow;

   }


   ::pointer<::user::impact>impact_host::get_hosted_impact(const ::atom & atomImpactId)
   {

      ::pointer<::user::document>pdocument = impact_item_document(atomImpactId);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->m_pimpactTopic;

   }


   bool impact_host::_001IsCompactMode()
   {

      if (!m_pimpacthosthost)
      {

         return false;

      }

      return m_pimpacthosthost->_001IsCompactMode();


   }


   void impact_host::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {
   
      ::user::place_holder::_001OnDraw(pgraphics);

   }


   bool impact_host::_001AttachImpact(const ::atom & atomImpactId)
   {

      if(_001IsCompactMode())
      {

         return true;

      }

      ::pointer<::userex::font_impact>pimpact = _001GetImpact(atomImpactId);

      if(pimpact.is_null())
      {

         return false;

      }

      defer_construct_newø(m_mapImpactItem[atomImpactId]);
      
      auto pframewindow = dynamic_cast<simple_frame_window *>(pimpact->parent_frame());

      m_mapImpactItem[atomImpactId]->m_pframewindow = pframewindow;

      pframewindow->display(e_display_none);

      _001DefaultLayoutImpact(atomImpactId);

      return true;

   }


   ::pointer<::user::impact>impact_host::_001DetachImpact(const ::atom & atomImpactId)
   {

      ::pointer<::user::impact>pimpact = _001GetImpact(atomImpactId);

      if (impact_item_frame_window(atomImpactId) == nullptr)
      {

         return nullptr;

      }

      ASSERT(impact_item_frame_window(atomImpactId) != nullptr);

      m_mapImpactItem[atomImpactId] = nullptr;

      return pimpact;

   }


   ::user::interaction * impact_host::wfi_up_down_target_get_hosting_parent(const ::atom &atomImpactId)
   {

      if (!get_parent()->wfi_is_up_down_target())
      {

         throw ::exception(error_wrong_state);

      }

      return m_pimpacthosthost->wfi_up_down_target_get_hosting_parent(atomImpactId);

   }



   bool impact_host::defer_create_impact(const ::atom & atomImpactId, ::request * prequest)
   {

      ::pointer<::user::document>pdocument = impact_item_document(atomImpactId);

      auto papp = get_app();

      if (pdocument.is_set())
      {

         return false;

      }

      ::atom atom = atomImpactId;

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession;
      
      auto puser = psession->m_puser;

      ::cast<::berg::application> pbergapplication = m_papplication;

      ::user::impact_system * pimpactsystem = pbergapplication->impact_system(atomImpactId);

      if (pimpactsystem != nullptr)
      {

         if (prequest != nullptr)
         {

            prequest->id() = atom;

            pimpactsystem->request(prequest);

            pdocument = ::user::__document(prequest);

         }
         else
         {

            pdocument = pimpactsystem->open_document_file(
               get_app(),
               e_type_empty,
               __visible(true).is_true(), 
               this, 
               m_pimpacthosthost->wfi_is_up_down_target() ? e_window_flag_updown : e_window_flag_none, atom);

         }

         if (pdocument.is_null())
         {

            return false;

         }

      }
      else
      {

         pdocument = papp->defer_create_impact(
            atomImpactId,
            this, m_pimpacthosthost->wfi_is_up_down_target() ? e_window_flag_updown : e_window_flag_none,
            atom);

      }

      defer_construct_newø(m_mapImpactItem[atomImpactId]);

      m_mapImpactItem[atomImpactId]->m_pdocument = pdocument;

      ASSERT(pdocument->m_pimpactTopic != nullptr);

      pdocument->m_pimpactTopic->set_notify_user_interaction(this);

      m_pimpacthosthost->on_user_impact_created(atomImpactId);

      return true;

   }


   void impact_host::_001OnImpact(const ::atom & atomImpactId)
   {

      toggle_impact(atomImpactId);

      //defer_create_impact(atomImpactId);

      //::pointer<::simple_frame_window>pframewindow = _001GetFrame(atomImpactId);

      //if (pframewindow.is_set())
      //{

      //   pframewindow->post_predicate([pframewindow]()
      //   {

      //      pframewindow->InitialFramePosition();

      //   });

      //}

   }


   void impact_host::show_impact(const ::atom &atomImpactId)
   {

      bool bShow = true;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->set("frame::" + atomImpactId + ".visible", bShow);

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession;
      
      auto puser = psession->m_puser;

      puser->will_use_impact_hint(atomImpactId);

      if (!defer_create_impact(atomImpactId))
      {

         ::pointer<::simple_frame_window> pframewindow = _001GetFrame(atomImpactId);

         if (pframewindow.is_set())
         {

            //pframewindow->WindowDataLoadWindowRectangle();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      }

      auto &pimpactitem = m_mapImpactItem[atomImpactId];

      defer_construct_newø(pimpactitem);

      pimpactitem->m_bVisible = true;
          

   }


   void impact_host::hide_impact(const ::atom &atomImpactId)
   {

      bool bShow = false;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->set("frame::" + atomImpactId + ".visible", bShow);

      ::pointer<::simple_frame_window> pframewindow = _001GetFrame(atomImpactId);

      if(pframewindow.is_null())
      {

         return;

      }

      pframewindow->display(e_display_hide, {});

      pframewindow->set_need_redraw();

      pframewindow->post_redraw();

            auto &pimpactitem = m_mapImpactItem[atomImpactId];

      defer_construct_newø(pimpactitem);

      pimpactitem->m_bVisible = false;


   }


   void impact_host::toggle_impact(const ::atom &atomImpactId)
   {

      //post_procedure(__routine([this, atomImpactId]()
         //{

            bool bVisible = is_user_impact_visible(atomImpactId);

            //::cast < ::database::client > pdatabaseclient = application();

            //pdatabaseclient->datastream()->get("frame::" + atomImpactId + ".visible", bShow);

            //bShow = !bShow;

            if (!bVisible)
            {

               show_impact(atomImpactId);

            }
            else
            {

               hide_impact(atomImpactId);

            }

         //}
         //));

   }


   void impact_host::defer_show_impact(const ::atom & atomImpactId)
   {

      bool bShow = false;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->get("frame::" + atomImpactId + ".visible", bShow);

      if (!bShow)
      {

         return;

      }

      show_impact(atomImpactId);

   }


   //::update::update()
   //{

   //   m_etype = type_none;

   //}


   //::update::~::update()
   //{


   //}

   
   
   void impact_host::on_simple_command(::message::simple_command * psimplecommand)
   {
      
      if (psimplecommand->command() == e_simple_command_defer_initialize_handled_impacts)
      {
         
         for (auto &atom: m_pimpacthosthost->m_idaHandledImpacts)
         {
            
            defer_show_impact(atom);
            
         }
         
      }
      
   }


   void impact_host::route_command(::message::command *pcommand, bool bRouteToKeyDescendant)
   {

      return ::user::place_holder::route_command(pcommand, bRouteToKeyDescendant);

      // if (pcommand->m_bRet)
      //   return;

      //// then pump through parent
      //::pointer<::user::interaction> puiParent = get_parent();

      // if (puiParent != nullptr)
      //{

      //   puiParent->route_command(pcommand);

      //   if (pcommand->m_bRet)
      //   {

      //      return;
      //   }
      //}
   }

   
} // namespace userex



