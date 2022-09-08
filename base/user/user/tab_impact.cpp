#include "framework.h"
#include "tab_impact.h"
#include "tab_pane.h"
#include "tab_data.h"
#include "aura/user/user/window_util.h"
#include "frame_window.h"
#include "aura/message/user.h"
#include "split_impact.h"
#include "tab_drop_target_window.h"
#include "base/platform/application.h"
#include "base/user/menu/menu.h"
#include "document.h"
#include "base/user/menu/list_impact.h"


namespace user
{


   tab_impact::tab_impact()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_pimpactdata                    = nullptr;
      m_pimpactdataOld                 = nullptr;
      m_bCloseDocumentIfNoTabs         = false;
      m_bAutoCreateTabsOnCreate        = false;

   }


   tab_impact::~tab_impact()
   {

   }


   void tab_impact::assert_ok() const
   {

      impact::assert_ok();

   }


   void tab_impact::dump(dump_context & dumpcontext) const
   {

      impact::dump(dumpcontext);

   }


   void tab_impact::on_message_create(::message::message * pmessage)
   {

      auto pdata = get_data();

      pdata->m_pcallback = this;

      if (pmessage->previous())
      {

         return;

      }

   }


   void tab_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      tab::handle(ptopic, pcontext);

      impact::handle(ptopic, pcontext);

      if (!m_bCreatedTabs)
      {

         if (ptopic->m_atom == id_new_document || ptopic->m_atom == id_open_document)
         {

            create_tabs();

         }

      }

   }


   void tab_impact::on_message_set_focus(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if(get_impact_uie() != nullptr)
      {

         get_impact_uie()->set_keyboard_focus();

      }

   }


   bool tab_impact::add_impact(const ::string & strName, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplacehoder)
   {

      return add_tab(strName, atomImpact, bVisible, bPermanent, pplacehoder);

   }


   bool tab_impact::add_impact_with_icon(const ::string & strName, const ::string & strIcon, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplacehoder)
   {

      return add_tab_with_icon(strName, strIcon, atomImpact, bVisible, bPermanent, pplacehoder);

   }


   void tab_impact::OnActivateImpact(bool bActivate, __pointer(impact) pActivateImpact, __pointer(impact) pDeactiveImpact)
   {

      __pointer(::user::interaction) pinteraction = get_impact_uie();

      __pointer(::user::impact) pimpact = pinteraction;

      if (pimpact.is_null() && pinteraction.is_set())
      {

         if (pinteraction->is_place_holder())
         {

            auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
            pimpact = puserinteractionpointeraChild->first_interaction();

         }
         else
         {

            __pointer(::user::frame_window) pframe = pinteraction;

            if (pframe.is_set())
            {

               pimpact = pframe->get_active_impact();

            }

         }

      }

      if (pimpact.is_set() && pimpact != this)
      {

         pimpact->OnActivateImpact(bActivate, pActivateImpact, pDeactiveImpact);

      }
      else
      {

         ::user::impact::OnActivateImpact(bActivate, pActivateImpact, pDeactiveImpact);

      }

   }


   bool tab_impact::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return impact::pre_create_window(pusersystem);

   }


   void tab_impact::rotate()
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


   void tab_impact::_001OnMenuMessage(::message::message * pmessage)
   {
      
      __pointer(::user::message) pusermessage(pmessage);

      if(pusermessage->m_wparam == 0 && pusermessage->m_lparam == 0)
      {

         set_current_tab_by_id(m_pimpactdataOld->m_atom);

      }

   }


   void tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab::install_message_routing(pchannel);

      impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_impact::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &tab_impact::_001OnMenuMessage);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_impact::on_message_set_focus);

   }


   void tab_impact::_001OnTabClick(index iTab)
   {

      ::user::tab::_001OnTabClick(iTab);

   }


   void tab_impact::_001OnRemoveTab(class tab_pane * ptabpane)
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

      atom idTab = ptabpane->m_atom;

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


   void tab_impact::_001OnDropTab(index iTab, enum_position eposition)
   {

      if (eposition != e_position_none)
      {

         atom id1 = ::user::tab::index_id(::user::tab::get_current_tab_index());

         atom id2 = ::user::tab::index_id(iTab);

         atom id3 = payload(id1).string() + "->:<-" + payload(id2).string();

         ::user::tab_pane * ppane1 = get_tab_by_id(id1);

         ::user::tab_pane * ppane2 = get_tab_by_id(id2);

         string strName1 = ppane1->get_title();

         string strName2 = ppane2->get_title();

         auto pimpactdata = allocate_impact_data(id3);

         add_tab(strName1 + "->:<-" + strName2, id3, true, false, pimpactdata->m_pplaceholder);

         __pointer(::user::split_impact) psplitview = impact::create_impact < ::user::split_impact >(pimpactdata);

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


   ::user::interaction * tab_impact::_001GetTabWnd(index iTab)
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


   void tab_impact::_001DropTargetWindowInitialize(::user::tab * pchannel)
   {

      create_tab_by_id(::user::tab::index_id(pchannel->get_data()->m_iClickTab));

      m_pdroptargetwindow = __new(tab_drop_target_window());

      m_pdroptargetwindow->initialize_tab_drop_target_window(this, (i32)pchannel->get_data()->m_iClickTab);

      auto rectangle = pchannel->get_data()->m_rectangleTabClient+pchannel->client_to_screen();

      m_pdroptargetwindow->m_bTransparent = true;

      m_pdroptargetwindow->create_host();

      m_pdroptargetwindow->order(e_zorder_top_most);

      m_pdroptargetwindow->place(rectangle);

      m_pdroptargetwindow->display(e_display_restored);

      m_pdroptargetwindow->set_mouse_capture();

   }


   void tab_impact::_001DropTargetWindowRelay(::user::tab * pchannel)
   {

      __UNREFERENCED_PARAMETER(pchannel);

      set_need_redraw();

   }


   void tab_impact::_001DropTargetWindowFinalize(::user::tab * pchannel)
   {
      __UNREFERENCED_PARAMETER(pchannel);
      if(m_pdroptargetwindow != nullptr)
      {
         //psystem->erase_frame(m_pdroptargetwindow);
         //m_pdroptargetwindow->DestroyWindow();
         //m_pdroptargetwindow = nullptr;
      }
   }


   void tab_impact::_001OnShowTab(tab * ptab)
   {

      if(ptab == this)
      {

         on_change_cur_sel();

         on_change_cur_sel();

      }

   }


   void tab_impact::_on_change_cur_sel()
   {

      index iTab = get_current_tab_index();

      atom atom = index_id(iTab);

      ::atom idSplit;

      auto ptabdata = get_data();

      ::rectangle_i32 rectangleTabClient = ptabdata->m_rectangleTabClient;

      ::user::impact_data * pimpactdata = get_impact_data(atom, rectangleTabClient);

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

               if (pimpactdata->m_strTitle.has_char())
               {

                  index iTab = get_current_tab_index();

                  if (iTab >= 0 && get_data()->m_tabpanecompositea[iTab]->m_atom == pimpactdata->m_atom)
                  {

                     get_data()->m_tabpanecompositea[iTab]->set_title(pimpactdata->m_strTitle);

                  }

               }

            }

         }

      }

      idSplit = pimpactdata->m_atomSplit;

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
         && m_pimpactdataOld->m_atom != MENU_IMPACT
         && m_pimpactdataOld->m_atom != OPTIONS_IMPACT)
      {

         output_debug_string("::user::e_flag_hide_on_kill_focus");

         m_pimpactdataOld->m_pplaceholder->hide();

      }

      if (m_pimpactdata != nullptr)
      {

         if (m_pimpactdata->m_eflag.has(::user::e_flag_hide_all_others_on_show)
            || m_pimpactdata->m_eflag.has(::user::e_flag_hidid_on_show))
         {

            ::user::tab_pane_composite_array & panecompositea = get_data()->m_tabpanecompositea;

            for (i32 iTab = 0; iTab < panecompositea.get_count(); iTab++)
            {

               auto pimpactdataPane = panecompositea[iTab]->m_pimpactdata;

               if (pimpactdataPane.is_null() || pimpactdataPane == m_pimpactdata)
               {

                  continue;

               }

               else if (m_pimpactdata->m_eflag & ::user::e_flag_hidid_on_show)
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

//         m_pimpactdata->m_pplaceholder->set_need_redraw();
//
//         m_pimpactdata->m_pplaceholder->set_need_layout();
//
//         m_pimpactdata->m_pplaceholder->post_redraw();

      }

      ::user::impact * pimpact = nullptr;

      if (m_pimpactdata->m_puserinteraction)
      {

         pimpact = m_pimpactdata->m_puserinteraction.cast < ::user::impact >();

      }

      if (pimpact == nullptr)
      {

         pimpact = this;

      }

      auto pframe = parent_frame();

      if (::is_set(pframe))
      {

         pframe->set_active_impact(pimpact);

      }

      auto papp = get_app();

      papp->on_change_cur_sel(this);

   }


   void tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
   
      if(pimpactdata->m_atom == MENU_IMPACT)
      {
         
         create_impact_menu(pimpactdata);
         
      }
      
   }

   void tab_impact::on_change_cur_sel()
   {

      _on_change_cur_sel();

      if (m_pimpactdata->m_atom == MENU_IMPACT)
      {

       //  create_impact_menu(m_pimpactdata);

         __pointer(::user::menu) pmenu = get_impact_uie();
         
         if(pmenu)
         {
         
            pmenu->m_menua.erase_all();
            
            pmenu->m_pmenuitem.release();
            
            pmenu->m_puserinteractionpointeraChild.release();

            prepare_impact_menu(pmenu);
            
         }

         return;

      }

   }


   ::user::tab_pane * tab_impact::create_tab_by_id(const ::atom & atom)
   {

      if (get_impact_data(atom, get_data()->m_rectangleTabClient) == nullptr)
      {

         return nullptr;

      }

      index iTab = id_index(atom);

      if (iTab < 0)
      {

         return nullptr;

      }

      return get_data()->m_tabpanecompositea[iTab];

   }


   void tab_impact::prepare_impact_menu(::user::menu * pmenu)
   {

      if (pmenu->load_xml_menu("matter://impact.menu"))
      {

         pmenu->create_inline_menu(this, m_pimpactdata->m_pplaceholder);

      }

      //return ::success;

   }


   void tab_impact::on_change_tab_count(::array < ::user::tab_pane * > array)
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


   void tab_impact::on_erase_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_erase_child(pinteraction);

      ::user::tab::on_erase_child(pinteraction);

   }


   void tab_impact::on_erase_place_holder_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_erase_place_holder_child(pinteraction);

      ::user::tab::on_erase_place_holder_child(pinteraction);

   }



   void tab_impact::on_hide_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_hide_child(pinteraction);

      ::user::tab::on_hide_child(pinteraction);

   }


   void tab_impact::on_hide_place_holder_child(::user::interaction* pinteraction)
   {

      ::user::impact_host::on_hide_place_holder_child(pinteraction);

      ::user::tab::on_hide_place_holder_child(pinteraction);

   }


   //::user::impact_data * tab_impact::create_impact(atom atom, const ::rectangle_i32 & rectangleCreate, ::user::frame_window * pframewindow)

   //{

   //   if (m_pviewcreator == nullptr)
   //      return nullptr;

   //   ::user::impact_data * pimpactdata = m_pviewcreator->::user::impact_creator::create_impact(atom, rectangleCreate);


   //   if (pimpactdata != nullptr)
   //   {

   //      if (id_pane(atom) == -1)
   //      {

   //         ::user::tab::add_tab("", atom);

   //      }

   //      ::user::tab_pane * ppane = get_tab_by_id(atom);

   //      if (ppane != nullptr)
   //      {

   //         {

   //            synchronous_lock synchronouslock(mutex());

   //            if (pimpactdata->m_strCreatorDataTitle.has_char() && ppane->m_atom == pimpactdata->m_atom)
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

   atom tab_impact::get_impact_id()
   {

      if (m_pimpactdata == nullptr)
      {

         return ::atom();

      }

      return m_pimpactdata->m_atom;

   }


   ::user::impact_data * tab_impact::get_impact_creator_data()
   {

      return m_pimpactdata;

   }


   ::user::interaction * tab_impact::get_impact_uie()
   {

      ::user::impact_data * pimpactdata = get_impact_creator_data();

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


   ::user::document * tab_impact::get_impact_document()
   {

      if(m_pimpactdata == nullptr)
      {

         return nullptr;

      }

      return m_pimpactdata->m_pdocument.cast < ::user::document > ();

   }


   void tab_impact::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      bool bUpdateBuffer = false;

      bool bUpdateWindow = false;

      sketch_to_design(bUpdateBuffer, bUpdateWindow);

      if (!is_this_visible())
      {

         return;

      }

      if (m_bSketchToDesignLayout)
      {

         m_bSketchToDesignLayout = false;

         design_layout(pgraphics);

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

#ifdef VERBOSE_LOG               

               CATEGORY_INFORMATION(prodevian, "(more than 50ms)(B) " << strType << "::_000DrawThis took " << integral_millisecond(d1) << ".\n");

#endif

            }

         }

      }

   }


   bool tab_impact::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      //if (!add_tab(pimpactdata->m_atom, pimpactdata->m_atomTitle))
      //{

      //   return false;

      //}

      auto ptabpane = get_tab_by_id(pimpactdata->m_atom);

      if (!ptabpane)
      {

         if (!add_tab(pimpactdata->m_strTitle, pimpactdata->m_atom))
         {

            return false;

         }

         ptabpane = get_tab_by_id(pimpactdata->m_atom);

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


   void tab_impact::on_after_host_impact(::user::impact_data * pimpactdata)
   {

      ::user::impact_host::on_after_host_impact(pimpactdata);

      //throw ::exception(todo, "experience");

      //__pointer(::user::frame) pframewindow = pimpactdata->m_puserinteraction;

      //if(pframewindow.is_set())
      //{

      //   pframewindow->m_bWindowFrame = true;

      //   pframewindow->enable_frame_experience();

      //   pframewindow->initialize_frame_window_experience();

      //}

   }


   void tab_impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

//      if(m_pimpactTopic)
//      {
//
//         m_pimpactTopic->route_command(pcommand, true);
//
//         if(pcommand->m_bRet)
//         {
//
//            return;
//
//         }
//
//      }

      impact::route_command(pcommand, bRouteToKeyDescendant);

   }




   void tab_impact::create_impact_menu(::user::impact_data * pimpactdata)
   {

      ::user::impact::create_impact < ::user::menu_list_impact >(pimpactdata);

   }


} // namespace user

