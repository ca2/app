//
//  userex_view_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Tsumanuma on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "aura/message.h"
#include "aura/update.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#include "apex/message/simple_command.h"
#include "base/user/user/tab_pane.h"


namespace userex
{


   impact_host::impact_host()
   {

      m_sizeTabbedFrame.cx = 800;
      m_sizeTabbedFrame.cy = 300;
      m_ptemplateTab = nullptr;

   }


   impact_host::~impact_host()
   {


   }


   void impact_host::assert_ok() const
   {

      ::user::impact::assert_ok();

   }


   void impact_host::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void impact_host::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact_host::on_message_create);

   }


   void impact_host::on_message_create(::message::message * pmessage)
   {

      m_idaHandledCommands.add(m_idaHandledImpacts);

   }


   void impact_host::on_command(::message::command * pcommand)
   {

      if (m_idaHandledImpacts.contains(pcommand->m_atom))
      {

         toggle_view(pcommand->m_atom);

      }

      return ::user::impact::on_command(pcommand);

   }





   void impact_host::_001DefaultLayoutImpact(::atom idImpact)
   {

      if (m_mapframe[idImpact] == nullptr)
      {

         return;

      }

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      auto pframewindow = m_mapframe[idImpact];

      pframewindow->order_front();

      pframewindow->set_dim(rectangle.width() / 4, 0, rectangle.width() / 2, rectangle.height() / 5);

      pframewindow->display();

      pframewindow->set_need_redraw();

   }


   __pointer(::simple_frame_window) impact_host::_001GetFrame(::atom idImpact)
   {

      __pointer(::user::impact) pimpact = _001GetImpact(idImpact);

      if (pimpact.is_null())
      {

         return nullptr;

      }

      __pointer(::simple_frame_window) pframewindow = pimpact->get_parent_frame();

      if (pframewindow.is_null())
      {

         return nullptr;

      }

      return pframewindow;

   }


   __pointer(::user::impact) impact_host::_001GetImpact(::atom idImpact)
   {

      __pointer(::user::document) pdocument = get_doc(idImpact);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->get_view();

   }


   void impact_host::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }


   bool impact_host::OnUpDownTargetAttach(::user::interaction * pupdown)
   {

      if (!tabfy(pupdown))
      {

         return false;

      }

      return true;

   }


   __pointer(::userex::pane_tab_impact) impact_host::get_pane_tab_view()
   {

      if (m_ptemplateTab == nullptr)
      {

         m_ptemplateTab = new user::single_document_template(
            "main",
            __type(::user::document),
            __type(simple_child_frame),
            __type(::userex::pane_tab_impact));

      }

      __pointer(::user::document) pdocTab = m_ptemplateTab->get_document();

      if (pdocTab == nullptr)
      {

         pdocTab = m_ptemplateTab->open_document_file(get_app(), ::e_type_null, __visible(false).is_true(), this);

      }

      return pdocTab->get_type_impact < ::userex::pane_tab_impact >();

   }


   bool impact_host::tabfy(::user::interaction * pupdown)
   {


      INFORMATION("-------------------------------------------------------------------");
      INFORMATION("");
      INFORMATION("");
      INFORMATION("impact_host::tabfy (1)");
      INFORMATION("");
      INFORMATION("");

      post_procedure([pupdown, this]
      {

         __pointer(::simple_frame_window) pframewindow = pupdown;

         auto ptabimpact = get_pane_tab_view();

         {

            if (ptabimpact->is_hosting(pframewindow))
            {

               return;

            }

            __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

            ::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

            pframewindow->m_bSizeEnable = false;

            pframewindow->m_bMoveEnable = false;

            ::atom atom = pupdown->m_atom;

            auto strTitle = pframewindow->get_window_text();

            strTitle.is_empty(atom);


            INFORMATION("-------------------------------------------------------------------");
            INFORMATION("");
            INFORMATION("");
            INFORMATION("impact_host::tabfy (2)");
            INFORMATION("");
            INFORMATION("");

            //::user::impact_data* pimpactdata = ptabimpact->host_impact(atom, strTitle, pframewindow, pframewindow->get_active_document());
            ptabimpact->host_impact(atom, pframewindow, pframewindow->get_active_document());

            ptabimpact->get_tab_by_id(atom)->set_title(strTitle);

            INFORMATION("-------------------------------------------------------------------");
            INFORMATION("");
            INFORMATION("");
            INFORMATION("impact_host::tabfy (3)");
            INFORMATION("");
            INFORMATION("");

            if (pframewindow->m_ewindowflag & e_window_flag_window_created)
            {


               INFORMATION("-------------------------------------------------------------------");
               INFORMATION("");
               INFORMATION("");
               INFORMATION("impact_host::tabfy (3.1)");
               INFORMATION("");
               INFORMATION("");


               ptabimpact->set_current_tab_by_id(atom);

               pframewindow->set_need_layout();

               pframewindow->WindowDataSaveWindowRect();

            }

         }


         INFORMATION("-------------------------------------------------------------------");
         INFORMATION("");
         INFORMATION("");
         INFORMATION("impact_host::tabfy (4)");
         INFORMATION("");
         INFORMATION("");


         if (pframewindow->m_ewindowflag & e_window_flag_window_created)
         {


            INFORMATION("-------------------------------------------------------------------");
            INFORMATION("");
            INFORMATION("");
            INFORMATION("impact_host::tabfy (4.1)");
            INFORMATION("");
            INFORMATION("");

            ptabimpact->get_parent_frame()->display();

            set_need_layout();

            set_need_redraw();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      });

      return true;

   }


   bool impact_host::OnUpDownTargetDetach(::user::interaction * pupdown)
   {

      INFORMATION("-------------------------------------------------------------------");
      INFORMATION("");
      INFORMATION("");
      INFORMATION("impact_host::OnUpDownTargetDetach (1)");

      __pointer(::simple_frame_window) pframewindow = pupdown;

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

            __pointer(simple_frame_window) pframewindowTab;

            if (m_ptemplateTab != nullptr)
            {

               __pointer(::user::document) pdocument = m_ptemplateTab->get_document(0);

               if (pdocument.is_set())
               {

                  __pointer(::userex::pane_tab_impact) ptabimpact = pdocument->get_type_impact < ::userex::pane_tab_impact >();

                  pframewindowTab = ptabimpact->get_parent_frame();


               }

            }

            {

               ::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

               __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

               pframewindow->set_parent(nullptr);

               pframewindow->on_frame_position();

               if (m_ptemplateTab != nullptr)
               {

                  string strId = pframewindow->m_atom;

                  __pointer(::user::document) pdocument = m_ptemplateTab->get_document(0);

                  if (pdocument.is_set())
                  {

                     __pointer(::userex::pane_tab_impact) ptabimpact = pdocument->get_type_impact < ::userex::pane_tab_impact >();

                     ptabimpact->erase_tab_by_id(pframewindow->m_atom);

                     if (ptabimpact.is_set() && ptabimpact->get_tab_count() <= 0)
                     {

                        ptabimpact->get_parent_frame()->hide();

                        ptabimpact->get_parent_frame()->set_need_redraw();

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

      if (m_ptemplateTab != nullptr)
      {

         ::rectangle_i32 rectangleTab;

         __pointer(::user::document) pdocument = m_ptemplateTab->get_document();

         if (pdocument != nullptr)
         {

            __pointer(::userex::pane_tab_impact) ptabimpact = pdocument->get_type_impact < ::userex::pane_tab_impact >();

            if (ptabimpact != nullptr)
            {

               auto pframewindowTab = ptabimpact->GetTypedParent < simple_frame_window >();

               bool bShow = ptabimpact->get_tab_count() >= 1;

               if(!bShow)
               {

                  if (pframewindowTab->is_this_visible())
                  {
                     INFORMATION("-------------------------------------------------------------------");
                     INFORMATION("");
                     INFORMATION("");
                     INFORMATION("pframewindowTab HIDE HIDE HIDE");
                     INFORMATION("");
                     INFORMATION("");
                     pframewindowTab->hide();

                  }

               }
               else
               {
                  

                  INFORMATION("-------------------------------------------------------------------");
                  INFORMATION("");
                  INFORMATION("");
                  INFORMATION("pframewindowTab VISIBLE VISIBLE VISIBLE");
                  INFORMATION("");
                  INFORMATION("");
                  auto rectangleRequest = rectangle_i32_dimension(20, 20, 800, 300);

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


   __pointer(::user::document) impact_host::get_doc(::atom idImpact)
   {

      return m_mapdoc[idImpact];

   }


   __pointer(::user::impact) impact_host::get_view(::atom idImpact)
   {

      __pointer(::user::document) pdocument = get_doc(idImpact);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->m_pviewTopic;

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

      __pointer(::userex::font_view) pimpact = _001GetImpact(idImpact);

      if(pimpact.is_null())
      {

         return false;

      }

      m_mapframe[idImpact] = dynamic_cast < simple_frame_window * > (pimpact->get_parent_frame());

      m_mapframe[idImpact]->display(e_display_none);

      _001DefaultLayoutImpact(idImpact);

      return true;

   }


   __pointer(::user::impact) impact_host::_001DetachImpact(::atom idImpact)
   {

      __pointer(::user::impact) pimpact = _001GetImpact(idImpact);

      if (m_mapframe[idImpact] == nullptr)
      {

         return nullptr;

      }

      ASSERT(m_mapframe[idImpact] != nullptr);

      m_mapframe[idImpact] = nullptr;

      return pimpact;

   }


   bool impact_host::defer_create_view(::atom idImpact, ::create * pcreate)
   {

      __pointer(::user::document) pdocument = get_doc(idImpact);

      auto papp = get_app();

      if (pdocument.is_set())
      {

         return false;

      }

      ::atom atom = idImpact;

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      ::user::impact_system * pimpactsystem = puser->m_mapimpactsystem[idImpact];

      if (pimpactsystem != nullptr)
      {

         if (pcreate != nullptr)
         {

            pcreate->m_atom = atom;

            pimpactsystem->do_request(pcreate);

            pdocument = ::user::__document(pcreate);

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

         pdocument = papp->defer_create_view(idImpact, this, m_bWfiUpDownTarget ? e_window_flag_updown : e_window_flag_none, atom);

      }

      m_mapdoc[idImpact] = pdocument;

      ASSERT(pdocument->m_pviewTopic != nullptr);

      pdocument->m_pviewTopic->set_notify_user_interaction(this);

      return true;

   }


   void impact_host::_001OnImpact(::atom idImpact)
   {

      toggle_view(idImpact);

      //defer_create_view(idImpact);

      //__pointer(::simple_frame_window) pframewindow = _001GetFrame(idImpact);

      //if (pframewindow.is_set())
      //{

      //   pframewindow->post_predicate([pframewindow]()
      //   {

      //      pframewindow->InitialFramePosition();

      //   });

      //}

   }


   void impact_host::show_view(::atom idImpact)
   {

      bool bShow = true;

      auto papp = get_app();

      papp->data_set("frame::" + idImpact.to_string() + ".visible", bShow);

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->will_use_view_hint(idImpact);

      if (!defer_create_view(idImpact))
      {

         __pointer(::simple_frame_window) pframewindow = _001GetFrame(idImpact);

         if (pframewindow.is_set())
         {

            pframewindow->WindowDataLoadWindowRect();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      }

   }


   void impact_host::hide_view(::atom idImpact)
   {

      bool bShow = false;

      auto papp = get_app();

      papp->data_set("frame::" + idImpact + ".visible", bShow);

      __pointer(::simple_frame_window) pframewindow = _001GetFrame(idImpact);

      if(pframewindow.is_null())
      {

         return;

      }

      pframewindow->hide();

      pframewindow->set_need_redraw();

      pframewindow->post_redraw();

   }


   void impact_host::toggle_view(::atom idImpact)
   {

      //post_procedure(__routine([this, idImpact]()
         //{

            bool bShow = false;

            auto papp = get_app();

            papp->data_get("frame::" + idImpact + ".visible", bShow);

            bShow = !bShow;

            if (bShow)
            {

               show_view(idImpact);

            }
            else
            {

               hide_view(idImpact);

            }

         //}
         //));

   }


   void impact_host::defer_show_view(::atom idImpact)
   {

      bool bShow = false;

      auto papp = get_app();

      papp->data_get("frame::" + idImpact + ".visible", bShow);

      if (!bShow)
      {

         return;

      }

      show_view(idImpact);

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
      
      if (psimplecommand->command() == e_simple_command_defer_initialize_handled_views)
      {
         
         for (auto & atom : m_idaHandledImpacts)
         {
            
            defer_show_view(atom);
            
         }
         
      }
      
   }
   
} // namespace userex



