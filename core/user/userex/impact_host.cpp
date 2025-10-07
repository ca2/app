//
//  userex_impact_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 14/07/18.
//  Copyright (c) 2018 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "impact_host.h"
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

      m_sizeTabbedFrame.cx() = 800;
      m_sizeTabbedFrame.cy() = 300;
      //m_ptemplateTab = nullptr;

   }


   impact_host::~impact_host()
   {


   }


   //void impact_host::assert_ok() const
   //{

   //   ::user::impact::assert_ok();

   //}


   //void impact_host::dump(dump_context & dumpcontext) const
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


   void impact_host::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &impact_host::on_message_create);

   }


   void impact_host::on_message_create(::message::message * pmessage)
   {

      m_atomaHandledCommands.append(m_idaHandledImpacts);

   }


   void impact_host::on_command(::message::command * pcommand)
   {

      if (m_idaHandledImpacts.contains(pcommand->command_id()))
      {

         toggle_impact(pcommand->command_id());

      }

      return ::user::impact::on_command(pcommand);

   }





   void impact_host::_001DefaultLayoutImpact(::atom idImpact)
   {

      if (m_mapframe[idImpact] == nullptr)
      {

         return;

      }

      ::int_rectangle rectangle;

      rectangle = this->rectangle();

      auto pframewindow = m_mapframe[idImpact];

      pframewindow->order_front();

      pframewindow->place(::int_rectangle_dimension(rectangle.width() / 4, 0, rectangle.width() / 2, rectangle.height() / 5));

      pframewindow->display();

      pframewindow->set_need_redraw();

   }


   ::pointer<::simple_frame_window>impact_host::_001GetFrame(::atom idImpact)
   {

      ::pointer<::user::impact>pimpact = _001GetImpact(idImpact);

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


   ::pointer<::user::impact>impact_host::_001GetImpact(::atom idImpact)
   {

      ::pointer<::user::document>pdocument = get_doc(idImpact);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->get_impact();

   }


   void impact_host::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

   }


   bool impact_host::OnUpDownTargetAttach(::user::interaction * pupdown)
   {

      if (!tabfy(pupdown))
      {

         return false;

      }

      return true;

   }


   ::pointer<::userex::pane_tab_impact>impact_host::get_pane_tab_impact()
   {

      if (!user()->impact_system("main"))
      {

         //m_ptemplateTab = ;;
         user()->add_impact_system(
            "main", __initialize_new user::single_document_template(
            "main",
            ::type < ::user::document >(),
            ::type < simple_child_frame >(),
            ::type < ::userex::pane_tab_impact >()));

         //user()->initialize(this);

      }

      ::pointer<::user::document>pdocTab = user()->impact_system("main")->get_document();

      if (pdocTab == nullptr)
      {

         pdocTab = user()->impact_system("main")->open_document_file(get_app(), ::e_type_null, __visible(false).is_true(), this);

      }

      return pdocTab->get_typed_impact < ::userex::pane_tab_impact >();

   }


   bool impact_host::tabfy(::user::interaction * pupdown)
   {


      information() << "-------------------------------------------------------------------";
      information() << "";
      information() << "";
      information() << "impact_host::tabfy (1)";
      information() << "";
      information() << "";

      //post_procedure([pupdown, this]
      {

         ::pointer<::simple_frame_window>pframewindow = pupdown;

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

            //::user::impact_data* pimpactdata = ptabimpact->host_impact(atom, strTitle, pframewindow, pframewindow->get_active_document());
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


   bool impact_host::OnUpDownTargetDetach(::user::interaction * pupdown)
   {

      information() << "-------------------------------------------------------------------";
      information() << "";
      information() << "";
      information() << "impact_host::OnUpDownTargetDetach (1)";

      ::pointer<::simple_frame_window>pframewindow = pupdown;

      if (pframewindow.is_set())
      {

         if (!(pframewindow->m_ewindowflag & e_window_flag_window_created))
         {

            pframewindow->m_puserinteractionParent = nullptr;

            return true;

         }

         pframewindow->enable_size();

         pframewindow->enable_move();

         fork([pframewindow, this]()
         {

            ::pointer<simple_frame_window>pframewindowTab;

            if (user()->impact_system("main") != nullptr)
            {

               ::pointer<::user::document>pdocument = user()->impact_system("main")->get_document(0);

               if (pdocument.is_set())
               {

                  ::pointer<::userex::pane_tab_impact>ptabimpact = pdocument->get_typed_impact < ::userex::pane_tab_impact >();

                  pframewindowTab = ptabimpact->parent_frame();


               }

            }

            {

               //::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

               __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::e_interaction_wfi_up_down_loading2);

               pframewindow->set_parent(nullptr);

               pframewindow->on_frame_position();

               if (user()->impact_system("main") != nullptr)
               {

                  string strId = pframewindow->id();

                  ::pointer<::user::document>pdocument = user()->impact_system("main")->get_document(0);

                  if (pdocument.is_set())
                  {

                     ::pointer<::userex::pane_tab_impact>ptabimpact = pdocument->get_typed_impact < ::userex::pane_tab_impact >();

                     ptabimpact->erase_tab_by_id(pframewindow->id());

                     if (ptabimpact.is_set() && ptabimpact->get_tab_count() <= 0)
                     {

                        ptabimpact->parent_frame()->hide();

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


   void impact_host::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (user()->impact_system("main") != nullptr)
      {

         ::int_rectangle rectangleTab;

         ::pointer<::user::document>pdocument = user()->impact_system("main")->get_document();

         if (pdocument != nullptr)
         {

            ::pointer<::userex::pane_tab_impact>ptabimpact = pdocument->get_typed_impact < ::userex::pane_tab_impact >();

            if (ptabimpact != nullptr)
            {

               auto pframewindowTab = ptabimpact->get_typed_parent < simple_frame_window >();

               bool bShow = ptabimpact->get_tab_count() >= 1;

               if(!bShow)
               {

                  if (pframewindowTab->is_this_visible())
                  {
                     information() << "-------------------------------------------------------------------";
                     information() << "";
                     information() << "";
                     information() << "pframewindowTab HIDE HIDE HIDE";
                     information() << "";
                     information() << "";
                     pframewindowTab->hide();

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
                  auto rectangleRequest = int_rectangle_dimension(20, 20, 800, 300);

                  //if (!pframewindowTab->is_this_visible() || rectangleRequest != pframewindowTab->window_request_rect())
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


   ::pointer<::user::document>impact_host::get_doc(::atom idImpact)
   {

      return m_mapdoc[idImpact];

   }


   ::pointer<::user::impact>impact_host::get_impact(::atom idImpact)
   {

      ::pointer<::user::document>pdocument = get_doc(idImpact);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->m_pimpactTopic;

   }


   bool impact_host::_001IsCompactMode()
   {

      return false;


   }


   bool impact_host::_001AttachImpact(::atom idImpact)
   {

      if(_001IsCompactMode())
      {

         return true;

      }

      ::pointer<::userex::font_impact>pimpact = _001GetImpact(idImpact);

      if(pimpact.is_null())
      {

         return false;

      }

      m_mapframe[idImpact] = dynamic_cast < simple_frame_window * > (pimpact->parent_frame());

      m_mapframe[idImpact]->display(e_display_none);

      _001DefaultLayoutImpact(idImpact);

      return true;

   }


   ::pointer<::user::impact>impact_host::_001DetachImpact(::atom idImpact)
   {

      ::pointer<::user::impact>pimpact = _001GetImpact(idImpact);

      if (m_mapframe[idImpact] == nullptr)
      {

         return nullptr;

      }

      ASSERT(m_mapframe[idImpact] != nullptr);

      m_mapframe[idImpact] = nullptr;

      return pimpact;

   }


   bool impact_host::defer_create_impact(::atom idImpact, ::request * prequest)
   {

      ::pointer<::user::document>pdocument = get_doc(idImpact);

      auto papp = get_app();

      if (pdocument.is_set())
      {

         return false;

      }

      ::atom atom = idImpact;

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession;
      
      auto puser = psession->m_puser;

      ::user::impact_system * pimpactsystem = puser->impact_system(idImpact);

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

            pdocument = pimpactsystem->open_document_file(get_app(), e_type_empty, __visible(true).is_true(), this, m_bWfiUpDownTarget ? e_window_flag_updown : e_window_flag_none, atom);

         }

         if (pdocument.is_null())
         {

            return false;

         }

      }
      else
      {

         pdocument = papp->defer_create_impact(idImpact, this, m_bWfiUpDownTarget ? e_window_flag_updown : e_window_flag_none, atom);

      }

      m_mapdoc[idImpact] = pdocument;

      ASSERT(pdocument->m_pimpactTopic != nullptr);

      pdocument->m_pimpactTopic->set_notify_user_interaction(this);

      return true;

   }


   void impact_host::_001OnImpact(::atom idImpact)
   {

      toggle_impact(idImpact);

      //defer_create_impact(idImpact);

      //::pointer<::simple_frame_window>pframewindow = _001GetFrame(idImpact);

      //if (pframewindow.is_set())
      //{

      //   pframewindow->post_predicate([pframewindow]()
      //   {

      //      pframewindow->InitialFramePosition();

      //   });

      //}

   }


   void impact_host::show_impact(::atom idImpact)
   {

      bool bShow = true;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->set("frame::" + idImpact + ".visible", bShow);

      auto pcontext = m_papplication;
      
      auto psession = pcontext->m_psession;
      
      auto puser = psession->m_puser;

      puser->will_use_impact_hint(idImpact);

      if (!defer_create_impact(idImpact))
      {

         ::pointer<::simple_frame_window>pframewindow = _001GetFrame(idImpact);

         if (pframewindow.is_set())
         {

            pframewindow->WindowDataLoadWindowRectangle();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      }

   }


   void impact_host::hide_impact(::atom idImpact)
   {

      bool bShow = false;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->set("frame::" + idImpact + ".visible", bShow);

      ::pointer<::simple_frame_window>pframewindow = _001GetFrame(idImpact);

      if(pframewindow.is_null())
      {

         return;

      }

      pframewindow->hide();

      pframewindow->set_need_redraw();

      pframewindow->post_redraw();

   }


   void impact_host::toggle_impact(::atom idImpact)
   {

      //post_procedure(__routine([this, idImpact]()
         //{

            bool bShow = false;

            ::cast < ::database::client > pdatabaseclient = application();

            pdatabaseclient->datastream()->get("frame::" + idImpact + ".visible", bShow);

            bShow = !bShow;

            if (bShow)
            {

               show_impact(idImpact);

            }
            else
            {

               hide_impact(idImpact);

            }

         //}
         //));

   }


   void impact_host::defer_show_impact(::atom idImpact)
   {

      bool bShow = false;

      ::cast < ::database::client > pdatabaseclient = application();

      pdatabaseclient->datastream()->get("frame::" + idImpact + ".visible", bShow);

      if (!bShow)
      {

         return;

      }

      show_impact(idImpact);

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
         
         for (auto & atom : m_idaHandledImpacts)
         {
            
            defer_show_impact(atom);
            
         }
         
      }
      
   }
   
} // namespace userex



