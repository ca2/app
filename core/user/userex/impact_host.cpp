//
//  userex_view_container.cpp
//  app_veriwell_musical_player
//
//  Created by Camilo Sasuke Tsumanuma on 14/07/18.
//  Copyright © 2018 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "core/user/userex/_userex.h"
#include "aura/message.h"
#include "aura/update.h"
#include "core/user/userex/_userex.h"
#include "apex/message/simple_command.h"


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


   void impact_host::assert_valid() const
   {

      ::user::impact::assert_valid();

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

      m_idaHandledCommands.add(m_idaHandledViews);

   }


   void impact_host::on_command(::message::command * pcommand)
   {

      if (m_idaHandledViews.contains(pcommand->m_id))
      {

         toggle_view(pcommand->m_id);

      }

      return ::user::impact::on_command(pcommand);

   }





   void impact_host::_001DefaultLayoutView(::id idView)
   {

      if (m_mapframe[idView] == nullptr)
      {

         return;

      }

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      auto pframewindow = m_mapframe[idView];

      pframewindow->order_front();

      pframewindow->set_dim(rectangle.width() / 4, 0, rectangle.width() / 2, rectangle.height() / 5);

      pframewindow->display();

      pframewindow->set_need_redraw();

   }


   __pointer(::simple_frame_window) impact_host::_001GetFrame(::id idView)
   {

      __pointer(::user::impact) pimpact = _001GetView(idView);

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


   __pointer(::user::impact) impact_host::_001GetView(::id idView)
   {

      __pointer(::user::document) pdocument = get_doc(idView);

      if (pdocument.is_null())
      {

         return nullptr;

      }

      return pdocument->get_view();

   }


   void impact_host::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::user::impact::on_subject(psubject, pcontext);

   }


   bool impact_host::OnUpDownTargetAttach(::user::interaction * pupdown)
   {

      if (!tabfy(pupdown))
      {

         return false;

      }

      return true;

   }


   __pointer(::userex::pane_tab_view) impact_host::get_pane_tab_view()
   {

      if (m_ptemplateTab == nullptr)
      {

         m_ptemplateTab = new user::single_document_template(
            "main",
            __type(::user::document),
            __type(simple_child_frame),
            __type(::userex::pane_tab_view));

      }

      __pointer(::user::document) pdocTab = m_ptemplateTab->get_document();

      if (pdocTab == nullptr)
      {

         pdocTab = m_ptemplateTab->open_document_file(get_application(), ::e_type_null, __visible(false).is_true(), this);

      }

      return pdocTab->get_typed_view < ::userex::pane_tab_view >();

   }


   bool impact_host::tabfy(::user::interaction * pupdown)
   {


      INFO("-------------------------------------------------------------------");
      INFO("");
      INFO("");
      INFO("impact_host::tabfy (1)");
      INFO("");
      INFO("");



      post_routine(__routine([pupdown, this]
      {

         __pointer(::simple_frame_window) pframewindow = pupdown;

         auto ptabview = get_pane_tab_view();

         {

            if (ptabview->is_hosting(pframewindow))
            {

               return;

            }

            __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

            ::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

            pframewindow->m_bSizeEnable = false;

            pframewindow->m_bMoveEnable = false;

            ::id id = pupdown->m_id;

            auto strTitle = pframewindow->get_window_text();

            strTitle.is_empty(id);


            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("impact_host::tabfy (2)");
            INFO("");
            INFO("");

            //::user::impact_data* pimpactdata = ptabview->host_impact(id, strTitle, pframewindow, pframewindow->get_active_document());
            ptabview->host_impact(id, strTitle, pframewindow, pframewindow->get_active_document());


            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("impact_host::tabfy (3)");
            INFO("");
            INFO("");

            if (pframewindow->m_ewindowflag & e_window_flag_window_created)
            {


               INFO("-------------------------------------------------------------------");
               INFO("");
               INFO("");
               INFO("impact_host::tabfy (3.1)");
               INFO("");
               INFO("");


               ptabview->set_current_tab_by_id(id);

               pframewindow->set_need_layout();

               pframewindow->WindowDataSaveWindowRect();

            }

         }


         INFO("-------------------------------------------------------------------");
         INFO("");
         INFO("");
         INFO("impact_host::tabfy (4)");
         INFO("");
         INFO("");


         if (pframewindow->m_ewindowflag & e_window_flag_window_created)
         {


            INFO("-------------------------------------------------------------------");
            INFO("");
            INFO("");
            INFO("impact_host::tabfy (4.1)");
            INFO("");
            INFO("");

            ptabview->get_parent_frame()->display();

            set_need_layout();

            set_need_redraw();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      }));

      return true;

   }


   bool impact_host::OnUpDownTargetDetach(::user::interaction * pupdown)
   {

      INFO("-------------------------------------------------------------------");
      INFO("");
      INFO("");
      INFO("impact_host::OnUpDownTargetDetach (1)");

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

                  __pointer(::userex::pane_tab_view) ptabview = pdocument->get_typed_view < ::userex::pane_tab_view >();

                  pframewindowTab = ptabview->get_parent_frame();


               }

            }

            {

               ::user::lock_sketch_to_design lockSketchToDesign(pframewindow);

               __keep_on(&pframewindow->m_uiUserInteractionFlags, ::user::interaction_wfi_up_down_loading);

               pframewindow->set_parent(nullptr);

               pframewindow->on_frame_position();

               if (m_ptemplateTab != nullptr)
               {

                  string strId = pframewindow->m_id;

                  __pointer(::user::document) pdocument = m_ptemplateTab->get_document(0);

                  if (pdocument.is_set())
                  {

                     __pointer(::userex::pane_tab_view) ptabview = pdocument->get_typed_view < ::userex::pane_tab_view >();

                     ptabview->erase_tab_by_id(pframewindow->m_id);

                     if (ptabview.is_set() && ptabview->get_tab_count() <= 0)
                     {

                        ptabview->get_parent_frame()->hide();

                        ptabview->get_parent_frame()->set_need_redraw();

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

         ::rectangle_i32 rectTab;

         __pointer(::user::document) pdocument = m_ptemplateTab->get_document();

         if (pdocument != nullptr)
         {

            __pointer(::userex::pane_tab_view) ptabview = pdocument->get_typed_view < ::userex::pane_tab_view >();

            if (ptabview != nullptr)
            {

               auto pframewindowTab = ptabview->GetTypedParent < simple_frame_window >();

               bool bShow = ptabview->get_tab_count() >= 1;

               if(!bShow)
               {

                  if (pframewindowTab->is_this_visible())
                  {
                     INFO("-------------------------------------------------------------------");
                     INFO("");
                     INFO("");
                     INFO("pframewindowTab HIDE HIDE HIDE");
                     INFO("");
                     INFO("");
                     pframewindowTab->hide();

                  }

               }
               else
               {
                  

                  INFO("-------------------------------------------------------------------");
                  INFO("");
                  INFO("");
                  INFO("pframewindowTab VISIBLE VISIBLE VISIBLE");
                  INFO("");
                  INFO("");
                  auto rectRequest = rectangle_i32_dimension(20, 20, 800, 300);

                  //if (!pframewindowTab->is_this_visible() || rectRequest != pframewindowTab->window_request_rect())
                  {

                     pframewindowTab->order_top();

                     pframewindowTab->place(rectRequest);

                     pframewindowTab->display();

                     pframewindowTab->set_need_redraw();

                  }

               }

            }

         }

      }

   }


   __pointer(::user::document) impact_host::get_doc(::id idView)
   {

      return m_mapdoc[idView];

   }


   __pointer(::user::impact) impact_host::get_view(::id idView)
   {

      __pointer(::user::document) pdocument = get_doc(idView);

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


   bool impact_host::_001AttachView(::id idView)
   {

      if(_001IsCompactMode())
      {

         return true;

      }

      __pointer(::userex::font_view) pview = _001GetView(idView);

      if(pview.is_null())
      {

         return false;

      }

      m_mapframe[idView] = dynamic_cast < simple_frame_window * > (pview->get_parent_frame());

      m_mapframe[idView]->display(e_display_none);

      _001DefaultLayoutView(idView);

      return true;

   }


   __pointer(::user::impact) impact_host::_001DetachView(::id idView)
   {

      __pointer(::user::impact) pview = _001GetView(idView);

      if (m_mapframe[idView] == nullptr)
      {

         return nullptr;

      }

      ASSERT(m_mapframe[idView] != nullptr);

      m_mapframe[idView] = nullptr;

      return pview;

   }


   bool impact_host::defer_create_view(::id idView, ::create * pcreate)
   {

      __pointer(::user::document) pdocument = get_doc(idView);

      auto papplication = get_application();

      if (pdocument.is_set())
      {

         return false;

      }

      ::id id = idView;

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      ::user::impact_system * pimpactsystem = puser->m_mapimpactsystem[idView];

      if (pimpactsystem != nullptr)
      {

         if (pcreate != nullptr)
         {

            pcreate->m_id = id;

            pimpactsystem->do_request(pcreate);

            pdocument = ::user::__document(pcreate);

         }
         else
         {

            pdocument = pimpactsystem->open_document_file(get_application(), e_type_empty, __visible(true).is_true(), this, m_bWfiUpDownTarget ? e_window_flag_updown : e_window_flag_none, id);

         }

         if (pdocument.is_null())
         {

            return false;

         }

      }
      else
      {

         pdocument = papplication->defer_create_view(idView, this, m_bWfiUpDownTarget ? e_window_flag_updown : e_window_flag_none, id);

      }

      m_mapdoc[idView] = pdocument;

      ASSERT(pdocument->m_pviewTopic != nullptr);

      pdocument->m_pviewTopic->set_notify_user_interaction(this);

      return true;

   }


   void impact_host::_001OnView(::id idView)
   {

      toggle_view(idView);

      //defer_create_view(idView);

      //__pointer(::simple_frame_window) pframewindow = _001GetFrame(idView);

      //if (pframewindow.is_set())
      //{

      //   pframewindow->post_predicate([pframewindow]()
      //   {

      //      pframewindow->InitialFramePosition();

      //   });

      //}

   }


   void impact_host::show_view(::id idView)
   {

      bool bShow = true;

      auto papplication = get_application();

      papplication->data_set("frame::" + idView.to_string() + ".visible", bShow);

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->will_use_view_hint(idView);

      if (!defer_create_view(idView))
      {

         __pointer(::simple_frame_window) pframewindow = _001GetFrame(idView);

         if (pframewindow.is_set())
         {

            pframewindow->WindowDataLoadWindowRect();

            pframewindow->set_need_redraw();

            pframewindow->post_redraw();

         }

      }

   }


   void impact_host::hide_view(::id idView)
   {

      bool bShow = false;

      auto papplication = get_application();

      papplication->data_set("frame::" + idView + ".visible", bShow);

      __pointer(::simple_frame_window) pframewindow = _001GetFrame(idView);

      if(pframewindow.is_null())
      {

         return;

      }

      pframewindow->hide();

      pframewindow->set_need_redraw();

      pframewindow->post_redraw();

   }


   void impact_host::toggle_view(::id idView)
   {

      //post_routine(__routine([this, idView]()
         //{

            bool bShow = false;

            auto papplication = get_application();

            papplication->data_get("frame::" + idView + ".visible", bShow);

            bShow = !bShow;

            if (bShow)
            {

               show_view(idView);

            }
            else
            {

               hide_view(idView);

            }

         //}
         //));

   }


   void impact_host::defer_show_view(::id idView)
   {

      bool bShow = false;

      auto papplication = get_application();

      papplication->data_get("frame::" + idView + ".visible", bShow);

      if (!bShow)
      {

         return;

      }

      show_view(idView);

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
         
         for (auto & id : m_idaHandledViews)
         {
            
            defer_show_view(id);
            
         }
         
      }
      
   }
   
} // namespace userex



