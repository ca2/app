#include "framework.h"
#include "tab_impact.h"
#include "tab_pane.h"
#include "tab_data.h"
#include "frame_window.h"
#include "split_impact.h"
#include "document.h"
#include "handler_impact.h"
#include "aura/user/user/notify_icon.h"
#include "tab_drop_target_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/prototype/data/listener.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/interaction_array.h"
#include "aura/message/user.h"
#include "berg/platform/application.h"
#include "berg/platform/session.h"
#include "berg/user/form/document.h"
#include "berg/user/menu/item.h"
#include "berg/user/menu/item_ptra.h"
#include "berg/user/menu/list_impact.h"
#include "berg/user/menu/menu.h"
#include "berg/user/user/user.h"
#include "berg/user/user/tab_drop_target_window.h"


namespace user
{


   tab_impact::tab_impact()
   {

      m_flagNonClient.erase(e_non_client_background);
      m_flagNonClient.erase(e_non_client_focus_rect);

      m_pimpactdata                    = nullptr;
      m_pimpactdataOld                 = nullptr;
      m_bCloseDocumentIfNoTabs         = false;
      //m_bAutoCreateTabsOnCreate        = false;

   }


   tab_impact::~tab_impact()
   {

   }


   void tab_impact::on_message_create(::message::message * pmessage)
   {

      auto pdata = get_data();

      pdata->m_pcallback = this;

      if (!application()->m_ptabimpactBase)
      {

         application()->m_ptabimpactBase = this;

      }

      if (pmessage->previous())
      {

         return;

      }

   }


   void tab_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      tab::handle(ptopic, phandlercontext);

      impact::handle(ptopic, phandlercontext);

      if (!m_bCreatedTabs)
      {

         if (ptopic->id() == id_incoming_document)
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


   void tab_impact::on_command_display_about(::message::message * pmessage)
   {

      ::pointer < ::message::command > pcommand(pmessage);

      show_about_tab_pane();

   }


   void tab_impact::show_about_tab_pane()
   {

      if (!contains_tab_with_id(ABOUT_IMPACT))
      {

         add_tab("About", ABOUT_IMPACT);

      }

      set_current_tab_by_id(ABOUT_IMPACT);


   }


   bool tab_impact::add_impact(const ::scoped_string & scopedstrName, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplacehoder)
   {

      return add_tab(scopedstrName, atomImpact, bVisible, bPermanent, pplacehoder);

   }


   bool tab_impact::add_impact_with_icon(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrIcon, const ::atom & atomImpact, bool bVisible, bool bPermanent, ::user::place_holder * pplacehoder)
   {

      return add_tab_with_icon(scopedstrName, scopedstrIcon, atomImpact, bVisible, bPermanent, pplacehoder);

   }


   void tab_impact::OnActivateImpact(bool bActivate, ::pointer<impact>pActivateImpact, ::pointer<impact>pDeactiveImpact)
   {

      return impact_host::OnActivateImpact(bActivate, pActivateImpact, pDeactiveImpact);

      //::pointer<::user::interaction>pinteraction = get_impact_uie();

      //::pointer<::user::impact>pimpact = pinteraction;

      //if (pimpact.is_null() && pinteraction.is_set())
      //{

      //   if (pinteraction->is_place_holder())
      //   {

      //      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
      //      pimpact = puserinteractionpointeraChild->first_interaction();

      //   }
      //   else
      //   {

      //      ::pointer<::user::frame_window>pframe = pinteraction;

      //      if (pframe.is_set())
      //      {

      //         pimpact = pframe->get_active_impact();

      //      }

      //   }

      //}

      //if (pimpact.is_set() && pimpact != this)
      //{

      //   pimpact->OnActivateImpact(bActivate, pActivateImpact, pDeactiveImpact);

      //}
      //else
      //{

      //   ::user::impact::OnActivateImpact(bActivate, pActivateImpact, pDeactiveImpact);

      //}

   }


   bool tab_impact::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return impact::pre_create_window(pusersystem);

   }


   void tab_impact::rotate()
   {

      ::collection::index iIndex = get_current_tab_index();

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
      
      ::pointer<::user::message>pusermessage(pmessage);

      if(pusermessage->m_wparam == 0 && pusermessage->m_lparam == 0)
      {

         set_current_tab_by_id(m_pimpactdataOld->id());

      }

   }


   void tab_impact::destroy()
   {

      ::user::impact_host::destroy();
      ::user::tab::destroy();

   }

   void tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab::install_message_routing(pchannel);

      impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_impact::on_message_create);
      MESSAGE_LINK(WM_USER + 1122, pchannel, this, &tab_impact::_001OnMenuMessage);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_impact::on_message_set_focus);

   }


   void tab_impact::_001OnTabClick(::collection::index iTab)
   {

      ::user::tab::_001OnTabClick(iTab);

   }


   void tab_impact::_001OnRemoveTab(class tab_pane * ptabpane)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (ptabpane->m_pplaceholder.is_set())
      {

         //::pointer<::user::interaction>puiChild;

         auto puiChild = ptabpane->m_pplaceholder->first_child();

         if (::is_set(puiChild))
         {

            puiChild->display(e_display_none);

            //puiChild->post_predicate([puiChild]()
            //{

            //   puiChild->set_parent(nullptr);

            //});

         }

      }

      m_placeholdera.erase(ptabpane->m_pplaceholder);

      atom idTab = ptabpane->id();

      ::user::impact_data * pimpactdata = m_impactdatamap[idTab];

      if (m_pimpactdata == pimpactdata)
      {

         // erased tab pane was current pane,
         // set current tab to null

         m_pimpactdata = nullptr;

         // if there is pane that was previously opened,
         // get top one and set it current

         auto ptabpaneTop = top_pane();

         if (ptabpaneTop)
         {

            set_current_tab_by_id(ptabpaneTop->id());

         }

      }

      if (m_pimpactdataOld == pimpactdata)
      {

         m_pimpactdataOld = nullptr;

      }

      m_impactdatamap.erase_key(idTab);

      ::user::tab::_001OnRemoveTab(ptabpane);

   }


   void tab_impact::prepare_form(const ::atom & atom, ::form_document * pformdocument)
   {

   }


   void tab_impact::_001OnDropTab(::collection::index iTab, enum_position eposition)
   {

      if (eposition != e_position_none)
      {

         atom id1 = ::user::tab::index_id(::user::tab::get_current_tab_index());

         atom id2 = ::user::tab::index_id(iTab);

         atom id3 = payload(id1).as_string() + "->:<-" + payload(id2).as_string();

         ::user::tab_pane * ppane1 = get_tab_by_id(id1);

         ::user::tab_pane * ppane2 = get_tab_by_id(id2);

         string strName1 = ppane1->get_title();

         string strName2 = ppane2->get_title();

         auto pimpactdata = allocate_impact_data(id3);

         add_tab(strName1 + "->:<-" + strName2, id3, true, false, pimpactdata->m_pplaceholder);

         ::pointer<::user::split_impact>psplitview = impact::create_impact < ::user::split_impact >(pimpactdata);

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

         auto puserinteraction1 = ppane1->m_pplaceholder->first_child();

         auto puserinteraction2 = ppane2->m_pplaceholder->first_child();

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


   ::user::interaction * tab_impact::_001GetTabWnd(::collection::index iTab)
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

      m_pdroptargetwindow = __allocate tab_drop_target_window();

      m_pdroptargetwindow->initialize_tab_drop_target_window(this, (int)pchannel->get_data()->m_iClickTab);

      auto rectangle = pchannel->get_data()->m_rectangleHosting;

      pchannel->client_to_screen()(rectangle);

      m_pdroptargetwindow->m_bTransparent = true;

      //m_pdroptargetwindow->create_host(e_parallelization_synchronous);

      m_pdroptargetwindow->create_window();

      m_pdroptargetwindow->order(e_zorder_top_most);

      m_pdroptargetwindow->place(rectangle);

      m_pdroptargetwindow->display(e_display_normal);

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

//         on_change_cur_sel();

      }

   }


   void tab_impact::_on_change_cur_sel()
   {

      __check_refdbg

      ::collection::index iTab = get_current_tab_index();

      __check_refdbg

      atom atom = index_id(iTab);

      __check_refdbg

      ::atom idSplit;

      __check_refdbg

      auto ptabdata = get_data();

      //::int_rectangle rectangleHosting = ptabdata->m_rectangleHosting;

      //::user::impact_data * pimpactdata = get_impact_data(atom, rectangleHosting);

      __check_refdbg

      ::user::impact_data * pimpactdata = get_impact_data(atom, true);

      __check_refdbg
      
      if (pimpactdata == nullptr)
      {

         return;

      }

      __check_refdbg

      if (atom != CONTEXT_OPTIONS_IMPACT)
      {

         __check_refdbg

         m_poptionsimpacthandlerContext = pimpactdata->m_pplaceholder->typed_descendant < ::user::options_impact_handler >();

         __check_refdbg

      }

      __check_refdbg

      if(iTab >= 0)
      {

         __check_refdbg

         auto& tabpanecompositea = ptabdata->m_tabpanea;

         __check_refdbg

         auto & ptabpanecomposite = tabpanecompositea[iTab];

         __check_refdbg

         if(ptabpanecomposite->m_pimpactdata != pimpactdata)
         {

            __check_refdbg

            ptabpanecomposite->m_pimpactdata = pimpactdata;

            __check_refdbg

            if (pimpactdata->m_pplaceholder != nullptr)
            {

               __check_refdbg

               get_data()->m_tabpanea[iTab]->m_pplaceholder = pimpactdata->m_pplaceholder;

               __check_refdbg

            }
            else if (pimpactdata->m_puserinteraction != nullptr)
            {

               __check_refdbg

               if (pane_holder(iTab) == nullptr)
               {

                  __check_refdbg

                  get_data()->m_tabpanea[iTab]->m_pplaceholder = place_hold(pimpactdata->m_puserinteraction, get_data()->m_rectangleHosting);

                  __check_refdbg

               }
               else
               {

                  __check_refdbg

                  get_data()->m_tabpanea[iTab]->m_pplaceholder->m_pacmeuserinteractionaChildren.release();

                  __check_refdbg

                  get_data()->m_tabpanea[iTab]->m_pplaceholder->place_hold(pimpactdata->m_puserinteraction);

                  __check_refdbg

               }

            }
            else
            {

               __check_refdbg

               get_data()->m_tabpanea[iTab]->m_pplaceholder = get_new_place_holder(get_data()->m_rectangleHosting);

               __check_refdbg

            }

            {

               __check_refdbg

               _synchronous_lock synchronouslock(this->synchronization());

               __check_refdbg

               if (pimpactdata->m_strTitle.has_character())
               {

                  __check_refdbg

                  ::collection::index iTab = get_current_tab_index();

                  __check_refdbg

                  if (iTab >= 0 && get_data()->m_tabpanea[iTab]->id() == pimpactdata->id())
                  {

                     __check_refdbg

                     get_data()->m_tabpanea[iTab]->set_title(pimpactdata->m_strTitle);

                     __check_refdbg

                  }

               }

            }

         }

      }

      __check_refdbg

      if (pimpactdata->m_pplaceholder)
      {

         __check_refdbg

         ::string strPlaceHolderId;

         __check_refdbg

         strPlaceHolderId = "place_holder : " + pimpactdata->id().as_string();

         __check_refdbg

         pimpactdata->m_pplaceholder->id() = strPlaceHolderId;

         __check_refdbg

      }

      __check_refdbg

      idSplit = pimpactdata->m_atomSplit;

      __check_refdbg

      if(pimpactdata != m_pimpactdata)
      {

         __check_refdbg

         m_pimpactdataOld = m_pimpactdata;

         __check_refdbg

         m_pimpactdata = pimpactdata;

         __check_refdbg

      }

      __check_refdbg

      if (m_pimpactdata == nullptr || m_pimpactdata->m_pplaceholder == nullptr)
      {

         return;

      }

      __check_refdbg

      if (m_pimpactdata->m_puserinteraction == nullptr)
      {

         __check_refdbg
         
         ::pointer<::user::interaction>pinteraction;

         __check_refdbg
         
         pinteraction = m_pimpactdata->m_pplaceholder->first_child();

         __check_refdbg

         if(pinteraction)
         {

            __check_refdbg
            
            ::pointer<::user::frame_window>pframewindow = pinteraction;

            __check_refdbg

            if(pframewindow && pframewindow->first_child())
            {

               __check_refdbg
               
               pinteraction = pframewindow->first_child();

               __check_refdbg
               
            }

            __check_refdbg
            
            m_pimpactdata->m_puserinteraction = pinteraction;

            __check_refdbg

            auto p1 = m_pimpactdata->m_puserinteraction.m_p;

            string strType =  typeid(*p1).name();

            __check_refdbg

            information("the type is " + strType);
            
         }

      }

   }


   void tab_impact::on_after_change_cur_sel()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto ptabdata = get_data();

      if (m_pimpactdataOld
         && m_pimpactdataOld->m_eflag & ::user::e_flag_hide_on_kill_focus
         && m_pimpactdataOld->id() != MENU_IMPACT
         && m_pimpactdataOld->id() != OPTIONS_IMPACT
         && m_pimpactdataOld->id() != APP_OPTIONS_IMPACT
         && m_pimpactdataOld->id() != CONTEXT_OPTIONS_IMPACT
         && m_pimpactdataOld->id() != ABOUT_IMPACT)
      {

         informationf("::user::e_flag_hide_on_kill_focus");

         m_pimpactdataOld->m_pplaceholder->hide();

      }

      if (m_pimpactdata != nullptr)
      {

         if (m_pimpactdata->m_eflag.has(::user::e_flag_hide_all_others_on_show)
            || m_pimpactdata->m_eflag.has(::user::e_flag_hidid_on_show))
         {

            ::user::tab_pane_array & panecompositea = get_data()->m_tabpanea;

            for (int iTab = 0; iTab < panecompositea.get_count(); iTab++)
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

      if (!ptabdata->m_bNoClient)
      {
         
         m_pimpactdata->m_pplaceholder->order(e_zorder_top);

         m_pimpactdata->m_pplaceholder->display();

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

         auto pframeImpact = pimpact->parent_frame();

         if (pframe && pframeImpact)
         {

            if (pframeImpact != pframe)
            {

               pframe->set_active_impact(this);

               pframeImpact->set_active_impact(pimpact);

            }
            else
            {

               pframe->set_active_impact(pimpact);

            }

         }

      }

      auto papp = get_app();

      papp->on_change_cur_sel(this);
      
      if(m_pimpactdata->m_pplaceholder)
      {
         
         if(m_pimpactdata->m_pplaceholder->m_bLockGraphicalUpdate)
         {
            
            m_pimpactdata->m_pplaceholder->m_bLockGraphicalUpdate = false;
         }
         
      }

   }


   void tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
   
      if (pimpactdata->id() == OPTIONS_IMPACT
         || pimpactdata->id() == APP_OPTIONS_IMPACT
         || pimpactdata->id() == CONTEXT_OPTIONS_IMPACT
         || pimpactdata->id() == ABOUT_IMPACT)
      {

         m_maphandlerimpact[pimpactdata->id()] = create_impact < handler_impact >(pimpactdata);

         if (pimpactdata->id() == APP_OPTIONS_IMPACT)
         {

            auto phandlerimpact = m_maphandlerimpact[pimpactdata->id()];

            auto functionHandler = [this](auto puserinteraction)
               {

               ::cast < ::user::options_impact_handler > poptionsimpacthandler = application();

               if(poptionsimpacthandler)
               {

                  poptionsimpacthandler->create_options_impact(puserinteraction);

               }

               };

            phandlerimpact->call_handler(functionHandler);

         }
         else if (pimpactdata->id() == ABOUT_IMPACT)
         {

            auto phandlerimpact = m_maphandlerimpact[pimpactdata->id()];

            auto functionHandler = [this](auto puserinteraction)
               {

                  application()->create_about_impact(puserinteraction);

               };

            phandlerimpact->call_handler(functionHandler);

         }

         //pimpactdata->m_eflag += ::user::e_flag_hide_all_others_on_show;

      }
      else if (pimpactdata->id().is_text())
      {

         if (case_insensitive_string_begins(pimpactdata->id().m_str, "form_"))
         {

            auto puser = user();

            ::pointer<form_document>pformdocument = puser->create_child_form(this, nullptr, this, pimpactdata->m_pplaceholder);

            if (pformdocument)
            {

               m_mapformdocument[pimpactdata->id()] = pformdocument;

               pformdocument->id() = string("document.") + string(pimpactdata->id());

               ::user::impact * pimpact = pformdocument->get_impact(0);

               pimpactdata->m_puserinteraction = pimpact->parent_frame();

               prepare_form(pimpactdata->id(), pformdocument);

            }

         }

      }
      else if(pimpactdata->id() == MENU_IMPACT)
      {
         
         create_impact_menu(pimpactdata);
         
      }
      
   }


   void tab_impact::on_change_cur_sel()
   {

      _on_change_cur_sel();

      if (m_pimpactdata->id() == MENU_IMPACT)
      {
         
         // create_impact_menu(m_pimpactdata);
         
         ::pointer<::user::menu>pmenu = get_impact_uie();
         
         if(pmenu)
         {
            
            pmenu->m_menua.erase_all();
            
            pmenu->m_pmenuitem.defer_destroy();
            
            pmenu->destroy_children();

            information() << "::user::tab_impact::on_change_cur_sel Going to call prepare_impact_menu";
            
            prepare_impact_menu(pmenu);
            
            //m_bNeedPerformLayout = true;
            
            //pmenu->get_parent()->m_bNeedPerformLayout = true;
            
            pmenu->m_bNeedPerformLayout = true;
            
            //pmenu->get_parent()->set_need_layout();
            
         }
         
         return;
         
      }
      else if (m_pimpactdata->id() == CONTEXT_OPTIONS_IMPACT && m_maphandlerimpact[m_pimpactdata->id()])
      {

         auto poptionsimpacthandler = m_poptionsimpacthandlerContext;

         auto phandlerimpact = m_maphandlerimpact[m_pimpactdata->id()];

         if(poptionsimpacthandler && phandlerimpact)
         {

            phandlerimpact->call_handler(
               [poptionsimpacthandler](auto puserinteractionParent)
               {

                  poptionsimpacthandler->create_options_impact(puserinteractionParent);

               });

         }

      }

   }


   ::user::tab_pane * tab_impact::create_tab_by_id(const ::atom & atom)
   {

      //if (get_impact_data(atom, get_data()->m_rectangleHosting) == nullptr)
      if (get_impact_data(atom, true) == nullptr)
      {

         return nullptr;

      }

      ::collection::index iTab = id_index(atom);

      if (iTab < 0)
      {

         return nullptr;

      }

      return get_data()->m_tabpanea[iTab];

   }


   void tab_impact::prepare_impact_menu(::user::menu * pmenu)
   {

      ::file::path path;

      path = "matter://impact.menu";

      auto strXml = get_app()->file()->safe_get_string(path);

      if (strXml.has_character())
      {

         if (!pmenu->load_xml_menu(strXml))
         {

            throw ::exception(error_failed, "tab_impact::prepare_impact_menu Failed to load \"" + path + "\".");

         }

      }

      application()->on_after_prepare_impact_menu(pmenu);

      auto pframe = top_level_frame();

      if (pframe 
         && pframe->should_inline_notify_context_menu()
         && pframe->notify_icon())
      {

         __defer_construct_new(pmenu->m_pmenuitem);

         user()->from_application_menu(
            pmenu->m_pmenuitem,
            pframe->notify_icon()->menu(),
            pmenu);

         //pmenu->m_pmenuitem->m_pmenu = pmenu;

         //if (!pmenu->m_pmenuitem->m_pmenuitema)
         //{

         //   pmenu->m_pmenuitem->m_pmenuitema = __allocate ::menu::item_ptra(pmenu->m_pmenuitem);

         //}

         //for(::collection::index i = 0; i < pframe->notify_icon()->m_notifyiconitema.get_count(); i++)
         //{

         //   auto pnotifyiconitem = pframe->notify_icon()->m_notifyiconitema[i];

         //   if (pnotifyiconitem->m_bStockItem)
         //   {

         //      continue;

         //   }

         //   auto pmenuitem = __create_new < ::menu::item >();

         //   pmenuitem->m_pmenu = pmenu;

         //   pmenuitem->id() = pnotifyiconitem->m_strId;

         //   pmenuitem->m_strTitle = pnotifyiconitem->m_strName;

         //   pmenu->m_pmenuitem->m_pmenuitema->add(pmenuitem);

         //}

         pmenu->add_handler(pframe);

      }

      information() << "::user::tab_impact::prepare_impact_menu Going to call menu::create_inline_menu";

      pmenu->create_inline_menu(this, m_pimpactdata->m_pplaceholder);

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


   //::user::impact_data * tab_impact::create_impact(atom atom, const ::int_rectangle & rectangleCreate, ::user::frame_window * pframewindow)

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

   //            _synchronous_lock synchronouslock(this->synchronization());

   //            if (pimpactdata->m_strCreatorDataTitle.has_character() && ppane->id() == pimpactdata->id())
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

      return m_pimpactdata->id();

   }


   ::user::impact_data * tab_impact::get_impact_creator_data()
   {

      return m_pimpactdata;

   }


   ::user::place_holder * tab_impact::place_holder_by_id(const ::atom & atom)
   {

      auto ppane = get_tab_by_id(atom);

      if (::is_null(ppane))
      {

         return nullptr;

      }

      if (!ppane->m_pplaceholder)
      {

         auto pplaceholder = get_new_place_holder(get_data()->m_rectangleHosting);

         ppane->m_pplaceholder = pplaceholder;

      }

      return ppane->m_pplaceholder;

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

         auto pacmeuserinteractionaChildren = pplaceholder->m_pacmeuserinteractionaChildren;

         if (::is_set(pacmeuserinteractionaChildren))
         {

            if (pacmeuserinteractionaChildren->count() == 1)
            {

               ::cast < ::user::interaction > puserinteractionFirst = pacmeuserinteractionaChildren->first();

               return puserinteractionFirst;

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

      //bool bUpdateBuffer = false;

      //bool bUpdateWindow = false;

      //layout_to_design(bUpdateBuffer, bUpdateWindow);

      //if (!is_this_visible())
      //{

      //   return;

      //}

      if (m_bLadingToLayout)
      {

         m_bLadingToLayout = false;

         layout_layout(pgraphics);

      }

      //on_context_offset(pgraphics);

      {

         ::int_point pointOffset;

         if (m_puserinteractionParent != nullptr)
         {

            pointOffset = const_layout().layout().origin();

            if (pointOffset.y() == 31)
            {

               //information() << "31";

            }

         }

         pgraphics->shift_impact_area(pointOffset, const_layout().layout().size());

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

            auto timeStart = ::time::now();

            _001DrawThis(pgraphics);

            auto timeEllapsed = timeStart.elapsed();

            if(timeEllapsed > 50_ms)
            {

               string strType = ::type(this).name();

#ifdef VERBOSE_LOG               

               information()(e_trace_category_prodevian) << "(more than 50ms)(B) " << strType << "::_000DrawThis took " << integral_millisecond(d1) << ".\n";

#endif

            }

         }

      }

   }


   bool tab_impact::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      //if (!add_tab(pimpactdata->id(), pimpactdata->m_atomTitle))
      //{

      //   return false;

      //}

      auto ptabpane = get_tab_by_id(pimpactdata->id());

      if (!ptabpane)
      {

         if (!add_tab(pimpactdata->m_strTitle, pimpactdata->id()))
         {

            return false;

         }

         ptabpane = get_tab_by_id(pimpactdata->id());

      }

      if (ptabpane != nullptr)
      {

         pimpactdata->m_iIndex = ptabpane->m_iIndex;

         if (!pimpactdata->m_pplaceholder)
         {

            auto pplaceholder = get_new_place_holder(get_data()->m_rectangleHosting);

            pimpactdata->m_pplaceholder = pplaceholder;

            pplaceholder->m_bExtendOnParentHostingArea = true;

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

      //::pointer<::user::frame_interaction>pframewindow = pimpactdata->m_puserinteraction;

      //if(pframewindow.is_set())
      //{

      //   pframewindow->m_bWindowFrame = true;

      //   pframewindow->enable_frame_experience();

      //   pframewindow->initialize_frame_window_experience();

      //}

   }


   void tab_impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      if (m_pimpactdata 
         && m_pimpactdata->m_puserinteraction
         && !m_pimpactdata->m_puserinteraction->is_menu())
      {

         m_pimpactdata->m_puserinteraction->route_command(pcommand, true);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

      if(m_pimpactTopic && (!m_pimpactdata || m_pimpactTopic != m_pimpactdata->m_puserinteraction))
      {

         m_pimpactTopic->route_command(pcommand, true);

         if(pcommand->m_bRet)
         {

            return;

         }

      }

      impact::route_command(pcommand, bRouteToKeyDescendant);

   }




   void tab_impact::create_impact_menu(::user::impact_data * pimpactdata)
   {

      ::user::impact::create_impact < ::user::menu_list_impact >(pimpactdata);

   }


   void tab_impact::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::tab::on_perform_top_down_layout(pgraphics);

      auto ptabdata = get_data();

      if (!ptabdata->m_bNoClient && m_pimpactdata)
      {

         ::int_rectangle rectangleHosting = ptabdata->m_rectangleHosting;

         ::int_rectangle rectangleX;

         rectangleX = m_pimpactdata->m_pplaceholder->rectangle();

         if (!rectangleHosting.is_empty())
         {

            {

               auto pchild = m_pimpactdata->m_pplaceholder;

               ::string strType = ::type(pchild).name();

               if (strType.case_insensitive_contains("place_holder"))
               {

                  if (pchild->m_pacmeuserinteractionaChildren
                     && pchild->m_pacmeuserinteractionaChildren->has_elements())
                  {

                     ::cast <::user::interaction> puserinteractionChild = pchild->m_pacmeuserinteractionaChildren->first();

                     ::string strTypePlaceHolderChild = ::type(puserinteractionChild).name();

                     if (strTypePlaceHolderChild.case_insensitive_contains("simple_frame_window"))
                     {

                        ::cast <::user::interaction> puserinteractionChild2 = puserinteractionChild->m_pacmeuserinteractionaChildren->first();

                        ::string strTypePlaceHolderChild2 = ::type(puserinteractionChild2).name();

                        if (strTypePlaceHolderChild2.case_insensitive_contains("font_impact"))
                        {

                           information() << "going to display " << strTypePlaceHolderChild2;

                           if (m_pacmeuserinteractionaChildren->contains(pchild))
                           {

                              //information() << "tab impact has font_list place_holder as child window";

                           }

                        }

                     }

                  }

               }

            }

            m_pimpactdata->m_pplaceholder->place(rectangleHosting);

            //         m_pimpactdata->m_pplaceholder->set_need_redraw();
            //
            //         m_pimpactdata->m_pplaceholder->set_need_layout();
            //
            //         m_pimpactdata->m_pplaceholder->post_redraw();

         }

      }

   }


} // namespace user



