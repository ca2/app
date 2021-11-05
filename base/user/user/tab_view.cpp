#include "framework.h"
#include "base/user/user/_user.h"
#include "tab_pane.h"


namespace user
{


   tab_view::tab_view()
   {

      m_flagNonClient.erase(non_client_background);
      m_flagNonClient.erase(non_client_focus_rect);

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


   void tab_view::on_message_create(::message::message * pmessage)
   {

      auto pdata = get_data();

      pdata->m_pcallback = this;

      if (pmessage->previous())
      {

         return;

      }

   }


   void tab_view::handle(::subject * psubject, ::context * pcontext)
   {

      tab::handle(psubject, pcontext);

      impact::handle(psubject, pcontext);

   }


   void tab_view::_001OnSetFocus(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if(get_view_uie() != nullptr)
      {

         get_view_uie()->set_keyboard_focus();

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

            auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
            pview = puserinteractionpointeraChild->first_interaction();

         }
         else
         {

            __pointer(::user::frame_window) pframe = pinteraction;

            if (pframe.is_set())
            {

               pview = pframe->get_active_view();

            }

         }

      }

      if (pview.is_set() && pview != this)
      {

         pview->OnActivateView(bActivate, pActivateView, pDeactiveView);

      }
      else
      {

         ::user::impact::OnActivateView(bActivate, pActivateView, pDeactiveView);

      }

   }


   bool tab_view::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return impact::pre_create_window(pusersystem);

   }


   void tab_view::rotate()
   {

      index iIndex = get_current_tab_index();

      if (iIndex < 0)
      {

         iIndex = 0;

      }
      else
      {

         iIndex++;

      }

      if (iIndex >= get_tab_count())
      {

         iIndex = 0;

      }

      if (iIndex >= get_tab_count())
      {

         return;

      }

      set_current_tab_by_id(iIndex);

   }


   void tab_view::_001OnMenuMessage(::message::message * pmessage)
   {
      
      __pointer(::user::message) pusermessage(pmessage);

      if(pusermessage->m_wparam == 0 && pusermessage->m_lparam == 0)
      {

         set_current_tab_by_id(m_pimpactdataOld->m_id);

      }

   }


   void tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab::install_message_routing(pchannel);

      impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_view::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &tab_view::_001OnMenuMessage);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_view::_001OnSetFocus);

   }


   void tab_view::_001OnTabClick(index iTab)
   {

      ::user::tab::_001OnTabClick(iTab);

   }


   void tab_view::_001OnRemoveTab(class tab_pane * ptabpane)
   {

      synchronous_lock synchronouslock(mutex());

      ::user::tab::_001OnRemoveTab(ptabpane);

      if (ptabpane->m_pplaceholder.is_set())
      {

         __pointer(::user::interaction) puiChild;

         ptabpane->m_pplaceholder->get_child(puiChild);

         if (puiChild.is_set())
         {

            puiChild->display(e_display_none);

            //puiChild->post_predicate([puiChild]()
            //{

            //   puiChild->set_parent(nullptr);

            //});

         }

      }

      m_placeholdera.erase(ptabpane->m_pplaceholder);

      id idTab = ptabpane->m_id;

      ::user::impact_data * pimpactdata = m_impactdatamap[idTab];

      if (m_pimpactdata == pimpactdata)
      {

         m_pimpactdata = nullptr;

      }

      if (m_pimpactdataOld == pimpactdata)
      {

         m_pimpactdataOld = nullptr;

      }

      m_impactdatamap.erase_key(idTab);

   }


   void tab_view::_001OnDropTab(index iTab, enum_position eposition)
   {

      if (eposition != e_position_none)
      {

         id id1 = ::user::tab::index_id(::user::tab::get_current_tab_index());

         id id2 = ::user::tab::index_id(iTab);

         id id3 = payload(id1).string() + "->:<-" + payload(id2).string();

         ::user::tab_pane * ppane1 = get_tab_by_id(id1);

         ::user::tab_pane * ppane2 = get_tab_by_id(id2);

         string strName1 = ppane1->get_title();

         string strName2 = ppane2->get_title();

         auto pimpactdata = allocate_impact_data(id3);

         add_tab(strName1 + "->:<-" + strName2, id3, true, false, pimpactdata->m_pplaceholder);

         __pointer(::user::split_view) psplitview = impact::create_view < ::user::split_view >(pimpactdata);

         pimpactdata->m_puserinteraction = psplitview;

         if (eposition == e_position_top || eposition == e_position_bottom)
         {

            psplitview->SetSplitOrientation(e_orientation_horizontal);

         }
         else
         {

            psplitview->SetSplitOrientation(e_orientation_vertical);

         }

         psplitview->SetPaneCount(2);

         psplitview->set_position_rate(0, 0.5);

         psplitview->initialize_split_layout();

         __pointer(::user::interaction) puserinteraction1;

         __pointer(::user::interaction) puserinteraction2;

         ppane1->m_pplaceholder->get_child(puserinteraction1);

         ppane2->m_pplaceholder->get_child(puserinteraction2);

         if (eposition == e_position_top || eposition == e_position_left)
         {

            psplitview->SetPane(0, puserinteraction2, false);

            psplitview->SetPane(1, puserinteraction1, false);

         }
         else
         {

            psplitview->SetPane(0, puserinteraction1, false);

            psplitview->SetPane(1, puserinteraction2, false);

         }

         on_create_impact(pimpactdata);

         erase_tab_by_id(id1);

         erase_tab_by_id(id2);

         set_current_tab_by_id(id3);

      }

      get_data()->m_iClickTab = -1;

      get_data()->m_bDrag = false;

      m_estate = e_state_initial;

   }


   ::user::interaction * tab_view::_001GetTabWnd(index iTab)
   {

      if (m_pviewcreator == nullptr)
      {

         return nullptr;

      }

      if(get_impact_data(::user::tab::index_id(iTab)) != nullptr)
      {

         return get_impact_data(::user::tab::index_id(iTab))->m_puserinteraction;

      }
      else
      {

         return nullptr;

      }

   }


   void tab_view::_001DropTargetWindowInitialize(::user::tab * pchannel)
   {

      create_tab_by_id(::user::tab::index_id(pchannel->get_data()->m_iClickTab));

      m_pdroptargetwindow = __new(tab_drop_target_window());

      m_pdroptargetwindow->initialize_tab_drop_target_window(this, (i32)pchannel->get_data()->m_iClickTab);

      auto rectangle = pchannel->_001ClientToScreen(pchannel->get_data()->m_rectangleTabClient);

      m_pdroptargetwindow->m_bTransparent = true;

      m_pdroptargetwindow->create_host();

      m_pdroptargetwindow->order(e_zorder_top_most);

      m_pdroptargetwindow->place(rectangle);

      m_pdroptargetwindow->display(e_display_normal);

      m_pdroptargetwindow->set_mouse_capture();

   }


   void tab_view::_001DropTargetWindowRelay(::user::tab * pchannel)
   {

      __UNREFERENCED_PARAMETER(pchannel);

      set_need_redraw();

   }


   void tab_view::_001DropTargetWindowFinalize(::user::tab * pchannel)
   {
      __UNREFERENCED_PARAMETER(pchannel);
      if(m_pdroptargetwindow != nullptr)
      {
         //psystem->erase_frame(m_pdroptargetwindow);
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


   void tab_view::_on_change_cur_sel()
   {

      index iTab = get_current_tab_index();

      id id = index_id(iTab);

      ::id idSplit;

      auto ptabdata = get_data();

      ::rectangle_i32 rectangleTabClient = ptabdata->m_rectangleTabClient;

      ::user::impact_data * pimpactdata = get_impact_data(id, rectangleTabClient);

      if (pimpactdata == nullptr)
      {

         return;

      }

      if(iTab >= 0)
      {

         auto& tabpanecompositea = ptabdata->m_tabpanecompositea;

         auto & ptabpanecomposite = tabpanecompositea[iTab];

         if(ptabpanecomposite->m_pimpactdata != pimpactdata)
         {

            ptabpanecomposite->m_pimpactdata = pimpactdata;

            if (pimpactdata->m_pplaceholder != nullptr)
            {

               get_data()->m_tabpanecompositea[iTab]->m_pplaceholder = pimpactdata->m_pplaceholder;

            }
            else if (pimpactdata->m_puserinteraction != nullptr)
            {

               if (pane_holder(iTab) == nullptr)
               {

                  get_data()->m_tabpanecompositea[iTab]->m_pplaceholder = place_hold(pimpactdata->m_puserinteraction, get_data()->m_rectangleTabClient);

               }
               else
               {

                  get_data()->m_tabpanecompositea[iTab]->m_pplaceholder->m_puserinteractionpointeraChild.release();

                  get_data()->m_tabpanecompositea[iTab]->m_pplaceholder->place_hold(pimpactdata->m_puserinteraction);

               }

            }
            else
            {

               get_data()->m_tabpanecompositea[iTab]->m_pplaceholder = get_new_place_holder(get_data()->m_rectangleTabClient);

            }

            {

               synchronous_lock synchronouslock(mutex());

               if (pimpactdata->m_idTitle.has_char())
               {

                  index iTab = get_current_tab_index();

                  if (iTab >= 0 && get_data()->m_tabpanecompositea[iTab]->m_id == pimpactdata->m_id)
                  {

                     get_data()->m_tabpanecompositea[iTab]->set_title(pimpactdata->m_idTitle);

                  }

               }

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

         auto puserinteractionpointeraChild = m_pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild;

         if (puserinteractionpointeraChild && puserinteractionpointeraChild->has_interaction())
         {

            m_pimpactdata->m_puserinteraction = puserinteractionpointeraChild->first_interaction();

         }

      }

      if (m_pimpactdataOld 
         && m_pimpactdataOld->m_eflag & ::user::e_flag_hide_on_kill_focus
         && m_pimpactdataOld->m_id != MENU_IMPACT
         && m_pimpactdataOld->m_id != OPTIONS_IMPACT)
      {

         output_debug_string("::user::e_flag_hide_on_kill_focus");

         m_pimpactdataOld->m_pplaceholder->hide();

      }

      if (m_pimpactdata != nullptr)
      {

         if (m_pimpactdata->m_eflag.has(::user::e_flag_hide_all_others_on_show)
            || m_pimpactdata->m_eflag.has(::user::e_flag_hide_topic_on_show))
         {

            ::user::tab_pane_composite_array & panecompositea = get_data()->m_tabpanecompositea;

            for (i32 iTab = 0; iTab < panecompositea.get_count(); iTab++)
            {

               auto pimpactdataPane = panecompositea[iTab]->m_pimpactdata;

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

      ::rectangle_i32 rectangleClient;

      m_pimpactdata->m_pplaceholder->get_client_rect(rectangleClient);

      if (!rectangleTabClient.is_empty())
      {

         m_pimpactdata->m_pplaceholder->order(e_zorder_top);

         m_pimpactdata->m_pplaceholder->place(rectangleTabClient);

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

      auto pframe = get_parent_frame();

      if (::is_set(pframe))
      {

         pframe->set_active_view(pview);

      }

      auto papplication = get_application();

      papplication->on_change_cur_sel(this);



   }


   void tab_view::on_change_cur_sel()
   {

      _on_change_cur_sel();

      if (m_pimpactdata->m_id == MENU_IMPACT)
      {

         create_impact_menu(m_pimpactdata);

         __pointer(::user::menu) pmenu = get_view_uie();

         prepare_impact_menu(pmenu);

         return;

      }

   }


   ::user::tab_pane * tab_view::create_tab_by_id(const ::id & id)
   {

      if (get_impact_data(id, get_data()->m_rectangleTabClient) == nullptr)
      {

         return nullptr;

      }

      index iTab = id_index(id);

      if (iTab < 0)
      {

         return nullptr;

      }

      return get_data()->m_tabpanecompositea[iTab];

   }


   ::e_status tab_view::prepare_impact_menu(::user::menu * pmenu)
   {

      if (pmenu->load_xml_menu("matter://impact.menu"))
      {

         pmenu->create_inline_menu(this, m_pimpactdata->m_pplaceholder);

      }

      return ::success;

   }


   void tab_view::on_change_tab_count(::array < ::user::tab_pane * > array)
   {

      ::user::tab::on_change_tab_count(array);

      if (m_bCloseDocumentIfNoTabs && get_tab_count() <= 0)
      {

         if (get_document() != nullptr)
         {

            get_document()->close_document();

         }

      }

   }


   void tab_view::on_erase_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_erase_child(pinteraction);

      ::user::tab::on_erase_child(pinteraction);

   }


   void tab_view::on_erase_place_holder_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_erase_place_holder_child(pinteraction);

      ::user::tab::on_erase_place_holder_child(pinteraction);

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


   //::user::impact_data * tab_view::create_impact(id id, const ::rectangle_i32 & rectangleCreate, ::user::frame_window * pframewindow)

   //{

   //   if (m_pviewcreator == nullptr)
   //      return nullptr;

   //   ::user::impact_data * pimpactdata = m_pviewcreator->::user::impact_creator::create_impact(id, rectangleCreate);


   //   if (pimpactdata != nullptr)
   //   {

   //      if (id_pane(id) == -1)
   //      {

   //         ::user::tab::add_tab("", id);

   //      }

   //      ::user::tab_pane * ppane = get_tab_by_id(id);

   //      if (ppane != nullptr)
   //      {

   //         {

   //            synchronous_lock synchronouslock(mutex());

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

      auto puserinteraction = pimpactdata->m_puserinteraction;

      if (::is_set(puserinteraction))
      {

         return puserinteraction;

      }

      auto pplaceholder = pimpactdata->m_pplaceholder;

      if (::is_set(pplaceholder))
      {

         auto puserinteractionpointeraChild = pplaceholder->m_puserinteractionpointeraChild;

         if (::is_set(puserinteractionpointeraChild))
         {

            if (puserinteractionpointeraChild->interaction_count() == 1)
            {

               return puserinteractionpointeraChild->first_interaction();

            }

         }

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

            ::duration t1 = ::duration::now();

            _001DrawThis(pgraphics);

            ::duration d1 = t1.elapsed();

            if(d1 > 50_ms)
            {

               string strType = __type_name(this);

               CATEGORY_INFORMATION(prodevian, "(more than 50ms)(B) " << strType << "::_000DrawThis took " << integral_millisecond(d1) << ".\n");

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

      auto ptabpane = get_tab_by_id(pimpactdata->m_id);

      if (!ptabpane)
      {

         if (!add_tab(pimpactdata->m_idTitle, pimpactdata->m_id))
         {

            return false;

         }

         ptabpane = get_tab_by_id(pimpactdata->m_id);

      }

      if (ptabpane != nullptr)
      {

         pimpactdata->m_iIndex = ptabpane->m_iIndex;

         if (!pimpactdata->m_pplaceholder)
         {

            auto pplaceholder = get_new_place_holder(get_data()->m_rectangleTabClient);

            pimpactdata->m_pplaceholder = pplaceholder;

         }

         ptabpane->m_pplaceholder = pimpactdata->m_pplaceholder;

         ptabpane->m_pimpactdata = pimpactdata;

      }

      on_change_tab_count();

      return true;

   }


   void tab_view::on_after_host_impact(::user::impact_data * pimpactdata)
   {

      ::user::impact_host::on_after_host_impact(pimpactdata);

      __throw(todo, "experience");

      //__pointer(::user::frame) pframewindow = pimpactdata->m_puserinteraction;

      //if(pframewindow.is_set())
      //{

      //   pframewindow->m_bWindowFrame = true;

      //   pframewindow->enable_frame_experience();

      //   pframewindow->initialize_frame_window_experience();

      //}

   }


   void tab_view::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      impact::route_command(pcommand, bRouteToKeyDescendant);

   }


   tab_drop_target_window::tab_drop_target_window()
   {
   }


   tab_drop_target_window::~tab_drop_target_window()
   {

   }


   ::e_status tab_drop_target_window::initialize_tab_drop_target_window(::user::tab* ptab, index iTab)
   {

      auto estatus = ::user::interaction::initialize(ptab);

      if (!estatus)
      {

         return estatus;

      }



      m_positiona.add(e_position_top);

      m_positiona.add(e_position_right);

      m_positiona.add(e_position_bottom);

      m_positiona.add(e_position_left);

      m_ptab = ptab;

      m_iTab = iTab;

      return estatus;

   }


   void tab_drop_target_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tab_drop_target_window::on_message_left_button_up);

   }


   void tab_drop_target_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::color::color crBorderNormal = argb(80, 127, 127, 80);

      ::color::color crBorderSelect = argb(100, 40, 40, 20);

      ::color::color crBorder;

      ::color::color crBkNormal = argb(160, 150, 200, 255);

      ::color::color crBkSelect = argb(180, 255, 230, 155);

      ::color::color crBk;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pointCursor = _001ScreenToClient(pwindowing->get_cursor_position());

      enum_position epositionDrag = m_ptab->DragHitTest(pointCursor);

      for (auto eposition : m_positiona)
      {

         ::rectangle_i32 rectangle;

         m_ptab->GetDragRect(rectangle, eposition);

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

         pgraphics->fill_rectangle(rectangle, crBk);

         pgraphics->draw_inset_rectangle(rectangle, crBorder);

      }

   }


   //bool tab_drop_target_window::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction)
   //{

   //   etranslucency = e_translucency_present;

   //   return true;

   //}

   void tab_drop_target_window::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      pwindowing->release_mouse_capture();

      auto point(pmouse->m_point);

      screen_to_client(point);

      enum_position eposition = m_ptab->DragHitTest(point);

      m_ptab->_001OnDropTab(m_iTab, eposition);

      display(e_display_none);

      start_destroying_window();

      pmessage->m_bRet = true;

   }


   bool tab_drop_target_window::has_pending_graphical_update()
   {

      return true;

   }


} // namespace user

