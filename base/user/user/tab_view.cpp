#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   tab_view::tab_view()
   {

      m_flagNonClient.remove(non_client_background);
      m_flagNonClient.remove(non_client_focus_rect);

      get_data()->m_pcallback       = this;
      m_pimpactdata                   = nullptr;
      m_pimpactdataOld                = nullptr;
      m_bCloseDocumentIfNoTabs      = false;

   }


   tab_view::~tab_view()
   {

   }


   void tab_view::assert_valid() const
   {

      impact::assert_valid();

   }


   void tab_view::dump(dump_context & dumpcontext) const
   {

      impact::dump(dumpcontext);

   }


   void tab_view::_001OnCreate(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

   }


   void tab_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      tab::on_subject(psubject, pcontext);

      impact::on_subject(psubject, pcontext);

   }


   void tab_view::_001OnSetFocus(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      if(get_view_uie() != nullptr)
      {
         get_view_uie()->SetFocus();
      }

   }


   void tab_view::OnActivateView(bool bActivate, __pointer(impact) pActivateView, __pointer(impact) pDeactiveView)
   {

      __pointer(::user::interaction) pinteraction = get_view_uie();

      __pointer(::user::impact) pview = pinteraction;

      if (pview.is_null() && pinteraction.is_set())
      {

         if (pinteraction->is_place_holder())
         {

            auto puiptraChild = m_puiptraChild;
            pview = puiptraChild->first_interaction();

         }
         else
         {

            __pointer(::user::frame_window) pframe = pinteraction;

            if (pframe.is_set())
            {

               pview = pframe->GetActiveView();

            }

         }

      }

      if (pview.is_set())
      {

         pview->OnActivateView(bActivate, pActivateView, pDeactiveView);

      }
      else
      {

         ::user::impact::OnActivateView(bActivate, pActivateView, pDeactiveView);

      }

   }


   bool tab_view::pre_create_window(::user::create_struct * pcreatestruct)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return impact::pre_create_window(pcreatestruct);

   }


   void tab_view::rotate()
   {
      index iSel = _001GetSel();

      if(iSel < 0)
         iSel = 0;
      else
         iSel++;

      if(iSel >= _001GetPaneCount())
         iSel = 0;

      if(iSel >= _001GetPaneCount())
         return;

      _001SetSel(iSel);

   }

   void tab_view::_001OnMenuMessage(::message::message * pmessage)
   {
      SCAST_PTR(::message::base, pbase, pmessage);
      if(pbase->m_wparam == 0 && pbase->m_lparam == 0)
      {
         set_cur_tab_by_id(m_pimpactdataOld->m_id);
      }
   }

   void tab_view::install_message_routing(::channel * pchannel)
   {
      impact::install_message_routing(pchannel);
      ::user::tab::install_message_routing(pchannel);
      MESSAGE_LINK(e_message_create, pchannel, this, &tab_view::_001OnCreate);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &tab_view::_001OnMenuMessage);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_view::_001OnSetFocus);
   }


   void tab_view::_001OnTabClick(index iTab)
   {

      ::user::tab::_001OnTabClick(iTab);

   }


   void tab_view::_001OnRemoveTab(class tab_pane * ptab)
   {

      sync_lock sl(mutex());

      ::user::tab::_001OnRemoveTab(ptab);

      if (ptab->m_pplaceholder.is_set())
      {

         __pointer(::user::interaction) puiChild;

         ptab->m_pplaceholder->get_child(puiChild);

         if (puiChild.is_set())
         {

            puiChild->display(e_display_none);

            //puiChild->post_pred([puiChild]()
            //{

            //   puiChild->SetParent(nullptr);

            //});

         }

      }

      m_placeholdera.remove(ptab->m_pplaceholder);

      id idTab = ptab->m_id;

      ::user::impact_data * pimpactdata = m_impactdatamap[idTab];

      if (m_pimpactdata == pimpactdata)
      {

         m_pimpactdata = nullptr;

      }

      if (m_pimpactdataOld == pimpactdata)
      {

         m_pimpactdataOld = nullptr;

      }

      m_impactdatamap.remove_key(idTab);



   }


   void tab_view::_001OnDropTab(index iTab, enum_position eposition)
   {

      if (eposition != e_element_icon)
      {

         id id1 = ::user::tab::tab_id(::user::tab::_001GetSel());

         id id2 = ::user::tab::tab_id(iTab);

         id id3 = payload(id1).get_string() + "->:<-" + payload(id2).get_string();

         ::user::tab_pane * ppane1 = get_pane_by_id(id1);

         ::user::tab_pane * ppane2 = get_pane_by_id(id2);

         string strName1 = ppane1->get_title();

         string strName2 = ppane2->get_title();

         auto pimpactdata = allocate_impact_data(id3);

         add_tab(strName1 + "->:<-" + strName2, id3, true, false, pimpactdata->m_pplaceholder);

         __pointer(::user::split_view) psplitview = impact::create_view < ::user::split_view >(pimpactdata);

         pimpactdata->m_puserinteraction = psplitview;

         if (eposition == position_top || eposition == position_bottom)
         {

            psplitview->SetSplitOrientation(orientation_horizontal);

         }
         else
         {

            psplitview->SetSplitOrientation(orientation_vertical);

         }

         psplitview->SetPaneCount(2);

         psplitview->set_position_rate(0, 0.5);

         psplitview->initialize_split_layout();

         __pointer(::user::interaction) pwnd1;

         __pointer(::user::interaction) pwnd2;

         ppane1->m_pplaceholder->get_child(pwnd1);

         ppane2->m_pplaceholder->get_child(pwnd2);

         if (eposition == position_top || eposition == position_left)
         {

            psplitview->SetPane(0, pwnd2, false);

            psplitview->SetPane(1, pwnd1, false);

         }
         else
         {

            psplitview->SetPane(0, pwnd1, false);

            psplitview->SetPane(1, pwnd2, false);

         }

         on_create_impact(pimpactdata);

         remove_tab_by_id(id1);

         remove_tab_by_id(id2);

         set_cur_tab_by_id(id3);

      }

      get_data()->m_iClickTab = -1;

      get_data()->m_bDrag = false;

      m_estate = state_initial;

   }


   ::user::interaction * tab_view::_001GetTabWnd(index iTab)
   {

      if (m_pviewcreator == nullptr)
      {

         return nullptr;

      }

      if(get_impact_data(::user::tab::tab_id(iTab)) != nullptr)
      {

         return get_impact_data(::user::tab::tab_id(iTab))->m_puserinteraction;

      }
      else
      {

         return nullptr;

      }

   }


   void tab_view::_001DropTargetWindowInitialize(::user::tab * pchannel)
   {

      create_tab_by_id(::user::tab::tab_id(pchannel->get_data()->m_iClickTab));

      m_pdroptargetwindow = __new(tab_drop_target_window(this, (i32) pchannel->get_data()->m_iClickTab));

      ::rect rect;

      rect = pchannel->get_data()->m_rectTabClient;

      pchannel->_001ClientToScreen(&rect);

      auto pcreatestruct = __new(::user::create_struct (WS_EX_LAYERED, nullptr, nullptr, 0, rect));

      m_pdroptargetwindow->create_window_ex(pcreatestruct);

      m_pdroptargetwindow->order(zorder_top_most);

      m_pdroptargetwindow->place(rect);

      m_pdroptargetwindow->display(e_display_normal);

      m_pdroptargetwindow->SetCapture();

   }


   void tab_view::_001DropTargetWindowRelay(::user::tab * pchannel)
   {

      UNREFERENCED_PARAMETER(pchannel);

      set_need_redraw();

   }


   void tab_view::_001DropTargetWindowFinalize(::user::tab * pchannel)
   {
      UNREFERENCED_PARAMETER(pchannel);
      if(m_pdroptargetwindow != nullptr)
      {
         //System.remove_frame(m_pdroptargetwindow);
         //m_pdroptargetwindow->DestroyWindow();
         //m_pdroptargetwindow = nullptr;
      }
   }


   void tab_view::_001OnShowTab(tab * ptab)
   {

      if(ptab == this)
      {

         on_change_cur_sel();

         on_change_cur_sel();

      }

   }


   void tab_view::on_change_cur_sel()
   {

      id id = tab_id(_001GetSel());

      ::id idSplit;

      ::rect rectTabClient = get_data()->m_rectTabClient;

      ::user::impact_data * pimpactdata = get_impact_data(id, rectTabClient);

      if (pimpactdata == nullptr)
      {

         return;

      }

      index iPane = ::user::tab::id_pane(id);

      if(iPane >= 0)
      {

         get_data()->m_panea[iPane]->m_pimpactdata = pimpactdata;

         if(pimpactdata->m_pplaceholder != nullptr)
         {

            get_data()->m_panea[iPane]->m_pplaceholder = pimpactdata->m_pplaceholder;

         }
         else if(pimpactdata->m_puserinteraction != nullptr)
         {

            if(pane_holder(iPane) == nullptr)
            {

               get_data()->m_panea[iPane]->m_pplaceholder = place_hold(pimpactdata->m_puserinteraction,get_data()->m_rectTabClient);

            }
            else
            {

               //sync_lock sl(mutex_children());

               get_data()->m_panea[iPane]->m_pplaceholder->m_puiptraChild.release();

               get_data()->m_panea[iPane]->m_pplaceholder->place_hold(pimpactdata->m_puserinteraction);

            }

         }
         else
         {

            get_data()->m_panea[iPane]->m_pplaceholder = get_new_place_holder(get_data()->m_rectTabClient);

         }

      }

      {

         sync_lock sl(mutex());

         if (pimpactdata->m_idTitle.has_char())
         {

            index iPane = tab_pane(_001GetSel());

            if (iPane >= 0 && get_data()->m_panea[iPane]->m_id == pimpactdata->m_id)
            {

               get_data()->m_panea[iPane]->set_title(pimpactdata->m_idTitle);

            }

         }

      }

      idSplit = pimpactdata->m_idSplit;

      if(pimpactdata != m_pimpactdata)
      {

         m_pimpactdataOld = m_pimpactdata;

         m_pimpactdata = pimpactdata;

      }

      if (m_pimpactdata == nullptr || m_pimpactdata->m_pplaceholder == nullptr)
      {

         return;

      }

      if (m_pimpactdata->m_puserinteraction == nullptr)
      {

//         sync_lock sl(mutex_children());



         auto puiptraChild = m_pimpactdata->m_pplaceholder->m_puiptraChild;

         if (puiptraChild && puiptraChild->has_interaction())
         {

            m_pimpactdata->m_puserinteraction = puiptraChild->first_interaction();

         }

      }

      if (m_pimpactdataOld
         && m_pimpactdataOld->m_eflag & ::user::e_flag_hide_on_kill_focus)
      {

         output_debug_string("::user::e_flag_hide_on_kill_focus");
         m_pimpactdataOld->m_pplaceholder->hide();

      }

      if (m_pimpactdata != nullptr)
      {

         if (m_pimpactdata->m_eflag & ::user::e_flag_hide_all_others_on_show
            || m_pimpactdata->m_eflag & ::user::e_flag_hide_topic_on_show)
         {

            ::user::tab_pane_array & panea = get_data()->m_panea;

            for (i32 iTab = 0; iTab < panea.get_count(); iTab++)
            {

               auto pimpactdataPane = panea[iTab]->m_pimpactdata;

               if (pimpactdataPane.is_null() || pimpactdataPane == m_pimpactdata)
               {

                  continue;

               }

               else if (m_pimpactdata->m_eflag & ::user::e_flag_hide_topic_on_show)
               {

                  if ((m_pimpactdata->m_eflag & ::user::e_flag_modifier_impact)
                     || (m_pimpactdata->m_eflag & ::user::e_flag_tool_impact))
                  {

                     if (!(pimpactdataPane->m_eflag & ::user::e_flag_modifier_impact)
                        && !(pimpactdataPane->m_eflag & ::user::e_flag_tool_impact))
                     {

                        continue;

                     }

                  }

               }

               pimpactdataPane->m_pplaceholder->hide();

            }

         }

      }


      ::rect rectClient;

      m_pimpactdata->m_pplaceholder->get_client_rect(rectClient);

      if (!rectTabClient.is_empty())
      {

         m_pimpactdata->m_pplaceholder->order(zorder_top);

         m_pimpactdata->m_pplaceholder->place(rectTabClient);

         m_pimpactdata->m_pplaceholder->display();

         m_pimpactdata->m_pplaceholder->set_need_redraw();

         m_pimpactdata->m_pplaceholder->set_need_layout();

         m_pimpactdata->m_pplaceholder->post_redraw();

      }

      ::user::impact * pview = nullptr;

      if (m_pimpactdata->m_puserinteraction)
      {

         pview = m_pimpactdata->m_puserinteraction.cast < ::user::impact >();

      }

      if (pview == nullptr)
      {

         pview = this;

      }

      auto pframe = GetParentFrame();

      if (::is_set(pframe))
      {

         pframe->SetActiveView(pview);

      }

      Application.on_change_cur_sel(this);

   }


   ::index tab_view::create_tab_by_id(id id)
   {

      if (get_impact_data(id, get_data()->m_rectTabClient) == nullptr)
      {

         return -1;

      }

      index iTab = id_tab(id);

      if (iTab < 0)
      {

         return -1;

      }

      return iTab;

   }


   void tab_view::on_change_pane_count(::array < ::user::tab_pane * > array)
   {

      ::user::tab::on_change_pane_count(array);

      if (m_bCloseDocumentIfNoTabs && get_pane_count() <= 0)
      {

         if (get_document() != nullptr)
         {

            get_document()->close_document();

         }

      }

   }


   void tab_view::on_remove_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_remove_child(pinteraction);

      ::user::tab::on_remove_child(pinteraction);

   }


   void tab_view::on_remove_place_holder_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_remove_place_holder_child(pinteraction);

      ::user::tab::on_remove_place_holder_child(pinteraction);

   }



   void tab_view::on_hide_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_hide_child(pinteraction);

      ::user::tab::on_hide_child(pinteraction);

   }


   void tab_view::on_hide_place_holder_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_hide_place_holder_child(pinteraction);

      ::user::tab::on_hide_place_holder_child(pinteraction);

   }


   //::user::impact_data * tab_view::create_impact(id id, const ::rect & rectCreate, ::user::frame_window * pframewindow)

   //{

   //   if (m_pviewcreator == nullptr)
   //      return nullptr;

   //   ::user::impact_data * pimpactdata = m_pviewcreator->::user::impact_creator::create_impact(id, rectCreate);


   //   if (pimpactdata != nullptr)
   //   {

   //      if (id_pane(id) == -1)
   //      {

   //         ::user::tab::add_tab("", id);

   //      }

   //      ::user::tab_pane * ppane = get_pane_by_id(id);

   //      if (ppane != nullptr)
   //      {

   //         {

   //            sync_lock sl(mutex());

   //            if (pimpactdata->m_strCreatorDataTitle.has_char() && ppane->m_id == pimpactdata->m_id)
   //            {

   //               ppane->set_title(pimpactdata->m_strCreatorDataTitle);

   //            }

   //         }

   //         if (ppane != nullptr)
   //         {

   //            ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

   //         }

   //      }

   //      on_change_pane_count();

   //   }

   //   return pimpactdata;

   //}

   id tab_view::get_view_id()
   {

      if (m_pimpactdata == nullptr)
      {

         return ::id();

      }

      return m_pimpactdata->m_id;

   }


   ::user::impact_data * tab_view::get_view_creator_data()
   {

      return m_pimpactdata;

   }


   ::user::interaction * tab_view::get_view_uie()
   {

      ::user::impact_data * pimpactdata = get_view_creator_data();

      if (pimpactdata == nullptr)
      {

         return nullptr;

      }

      if (pimpactdata->m_puserinteraction != nullptr)
      {

         return pimpactdata->m_puserinteraction;

      }

      auto puiptraChild = pimpactdata->m_pplaceholder->m_puiptraChild;

      if (pimpactdata->m_pplaceholder != nullptr && puiptraChild->interaction_count() == 1)
      {

         return puiptraChild->first_interaction();

      }

      return nullptr;

   }


   ::user::document * tab_view::get_view_document()
   {

      if(m_pimpactdata == nullptr)
      {

         return nullptr;

      }

      return m_pimpactdata->m_pdocument.cast < ::user::document > ();

   }


   void tab_view::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      bool bUpdateBuffer = false;

      bool bUpdateWindow = false;

      sketch_to_design(pgraphics, bUpdateBuffer, bUpdateWindow);

      if (!is_this_visible())
      {

         return;

      }

      if (m_bDrawTabAtBackground)
      {

         _001DrawThis(pgraphics);

         _001DrawChildren(pgraphics);

      }
      else
      {

         _001DrawChildren(pgraphics);

         {

            millis t1 = millis::now();

            _001DrawThis(pgraphics);

            millis d1 = t1.elapsed();

            if(d1 > 50)
            {

               string strType = type_name();

               CINFO(prodevian)("(more than 50ms) "+strType+"::_000DrawThis took " + __str(d1) + ".\n");

            }

         }

      }

   }


   bool tab_view::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      //if (!add_tab(pimpactdata->m_id, pimpactdata->m_idTitle))
      //{

      //   return false;

      //}

      ::user::tab_pane* ppane = get_pane_by_id(pimpactdata->m_id);

      if (ppane != nullptr)
      {

         if (!pimpactdata->m_pplaceholder)
         {

            auto pplaceholder = get_new_place_holder(get_data()->m_rectTabClient);

            pimpactdata->m_pplaceholder = pplaceholder;

         }

         ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

         ppane->m_pimpactdata = pimpactdata;

      }

      on_change_pane_count();

      return true;

   }


   void tab_view::on_after_host_impact(::user::impact_data * pimpactdata)
   {

      ::user::impact_host::on_after_host_impact(pimpactdata);

      __throw(todo("experience"));

      //__pointer(::user::frame) pframewindow = pimpactdata->m_puserinteraction;

      //if(pframewindow.is_set())
      //{

      //   pframewindow->m_bWindowFrame = true;

      //   pframewindow->enable_frame_experience();

      //   pframewindow->initialize_frame_window_experience();

      //}

   }


   void tab_view::route_command_message(::user::command * pcommand)
   {

      if (!handle(pcommand))
      {

         return;

      }

      //if (get_view_uie() != nullptr)
      //{

      //   get_view_uie()->route_command_message(pcommand);

      //   if (pcommand->m_bRet)
      //   {

      //      return;

      //   }

      //}

      impact::route_command_message(pcommand);

   }

   //void tab_view::set_impact_creator(::user::impact_creator * pviewcreator)
   //{

   //   m_pviewcreator = pviewcreator;

   //   if(m_pviewcreator != nullptr)
   //   {
   //      m_pviewcreator->m_pimpacthost = this;
   //   }

   //}

   //::user::impact_creator * tab_view::get_view_creator()
   //{
   //   return m_pviewcreator;
   //}


   tab_drop_target_window::tab_drop_target_window(::user::tab * ptab, index iTab) :
      ::object(ptab->get_context_application())
   {

      m_positiona.add(position_top);

      m_positiona.add(position_right);

      m_positiona.add(position_bottom);

      m_positiona.add(position_left);

      m_ptab         = ptab;

      m_iTab         = iTab;

   }


   tab_drop_target_window::~tab_drop_target_window()
   {

   }


   void tab_drop_target_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tab_drop_target_window::_001OnLButtonUp);

   }


   void tab_drop_target_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      color32_t crBorderNormal = ARGB(80, 127, 127, 80);

      color32_t crBorderSelect = ARGB(100, 40, 40, 20);

      color32_t crBorder;

      color32_t crBkNormal = ARGB(160, 150, 200, 255);

      color32_t crBkSelect = ARGB(180, 255, 230, 155);

      color32_t crBk;

      auto psession = Session;

      auto pointCursor=      psession->get_cursor_pos();

      _001ScreenToClient(&pointCursor);

      enum_position epositionDrag = m_ptab->DragHitTest(pointCursor);

      for (auto eposition : m_positiona)
      {

         ::rect rect;

         m_ptab->GetDragRect(rect, eposition);

         if (eposition == epositionDrag)
         {

            crBk = crBkSelect;

            crBorder = crBorderSelect;

         }
         else
         {

            crBk = crBkNormal;

            crBorder = crBorderNormal;

         }

         pgraphics->fill_rect(rect, crBk);

         pgraphics->draw_rect(rect, crBorder);

      }

   }


   //bool tab_drop_target_window::get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::interaction * pinteraction)
   //{

   //   etranslucency = e_translucency_present;

   //   return true;

   //}

   void tab_drop_target_window::_001OnLButtonUp(::message::message * pmessage)
   {

      SCAST_PTR(::message::mouse, pmouse, pmessage);

      ReleaseCapture();

      auto point(pmouse->m_point);

      _001ScreenToClient(point);

      enum_position eposition = m_ptab->DragHitTest(point);

      m_ptab->_001OnDropTab(m_iTab, eposition);

      display(e_display_none);

      DestroyWindow();

      pmessage->m_bRet = true;

   }


   bool tab_drop_target_window::has_pending_graphical_update()
   {

      return true;

   }


} // namespace user

