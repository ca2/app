#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif

#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "core/user/account/_account.h"
#include "aura/update.h"
#include "base/user/user/tab_pane.h"


namespace core
{


   ::type user::get_pane_tab_view_type_info()
   {

      return __type(::userex::pane_tab_impact);

   }


} // namespace core


namespace userex
{


   pane_tab_impact::pane_tab_impact()
   {

      m_pcolorview = nullptr;

      //m_pfilemanager = nullptr;

      //m_pfilemanagerTabbed = nullptr;

   }


   pane_tab_impact::~pane_tab_impact()
   {

   }


   ::user::interaction * pane_tab_impact::get_view_uie()
   {

      return ::user::tab_view::get_view_uie();

   }


   atom pane_tab_impact::get_view_id()
   {

      return ::user::tab_view::get_view_id();

   }


   void pane_tab_impact::GetTabClientRect(RECTANGLE_I32 * prectangle)

   {

      if(m_pimpactdata == nullptr || m_pimpactdata->m_puserinteraction == nullptr || m_pimpactdata->m_iExtendOnParent == 0)
      {

         ::user::tab_view::GetTabClientRect(prectangle);


      }
      else if(m_pimpactdata->m_iExtendOnParent > 0)
      {

         i32 i = m_pimpactdata->m_iExtendOnParent;

         __pointer(::user::interaction) pinteraction = m_pimpactdata->m_puserinteraction;

         __pointer(::user::interaction) puiNext = m_pimpactdata->m_puserinteraction;

         for(; i > 0; i--)
         {

            puiNext = pinteraction->get_parent();

            if (puiNext == nullptr || !puiNext->is_window())
            {

               break;

            }

            pinteraction = puiNext;

         }

         pinteraction->get_window_rect(prectangle);


         screen_to_client(prectangle);


      }
      else if(m_pimpactdata->m_iExtendOnParent < 0)
      {

         __pointer(::user::interaction) pinteraction = m_pimpactdata->m_puserinteraction;

         __pointer(::user::interaction) puiNext = m_pimpactdata->m_puserinteraction;

         ::user::interaction_array uia;

         while(true)
         {

            uia.add_interaction(pinteraction);

            puiNext = pinteraction->get_parent();

            if (puiNext == nullptr || (pinteraction->m_pprimitiveimpl) != nullptr)
            {

               break;

            }

            pinteraction = puiNext;

         }

         pinteraction = uia.interaction_at(uia.interaction_count() + m_pimpactdata->m_iExtendOnParent);

         pinteraction->get_window_rect(prectangle);

         screen_to_client(prectangle);

      }

   }


   void pane_tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_tab_impact::on_message_create);

      add_command_handler("file_save_as", this, &pane_tab_impact::_001OnFileSaveAs);
      add_command_prober("file_save_as", this, &pane_tab_impact::_001OnUpdateFileSaveAs);

   }


   void pane_tab_impact::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      //m_pusersystem->m_pcreate = (::create *) pcreate->get_create();

      //if (papp->m_pmainpane == nullptr)
      //{

      //   papp->m_pmainpane = this;

      //}

      auto papp = get_app();

      if (papp->m_puiMainContainer == nullptr)
      {

         papp->m_puiMainContainer = this;

      }

      if (pmessage->previous())
      {

         return;

      }


      //__pointer(simple_frame_window) pframe = get_parent();

      //if (pframe.is_set())
      //{

      //   string strAppOptions(pframe->m_varFrame["options_impact"]["resource"]);

      //   if (strAppOptions.has_char())
      //   {

      //      string strTitle(pframe->m_varFrame["options_impact"]["title"]);

      //      if(strTitle.is_empty())

      //      add_tab(strTitle, "options_impact");

      //   }

      //}

   }


   void pane_tab_impact::_001OnFileSaveAs(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      auto pdocument = m_pimpactdata->m_pdocument.cast < ::user::document >();

      if (::is_set(pdocument))
      {

         set_current_tab_by_id("file_manager_save");

         filemanager_document("file_manager_save")->FileManagerSaveAs(pdocument);

      }

   }

   void pane_tab_impact::_001OnUpdateFileSaveAs(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      auto pdocument = m_pimpactdata->m_pdocument;

      pcommand->enable(::is_set(pdocument));

   }


   void pane_tab_impact::on_change_cur_sel()
   {

      ::user::tab_view::on_change_cur_sel();

      if (m_pimpactdataOld != nullptr && is_filemanager(m_pimpactdataOld->m_atom))
      {

         if (get_parent_frame()->ContinueModal())
         {

            get_parent_frame()->EndModalLoop("yes");

         }

         if (::is_set(filemanager_document("file_manager_save")))
         {

            filemanager_document("file_manager_save")->filemanager_data()->m_pdocumentTopic = nullptr;

         }

      }
      else if(m_pimpactdata->m_atom == OPTIONS_IMPACT)
      {

         if (::is_set(m_pdocumentMenu))
         {

            auto strOptionsImpact = get_app()->preparimpact_options();

#if defined(_DEBUG) && !defined(_UWP) && !defined(APPLE_IOS)

            auto pcontext = m_pcontext->m_papexcontext;

            ::file::path path;
            
            path = pcontext->dir().appdata() / "debug_ca2/menu_view" / (get_app()->m_strAppId + ".html");

            pcontext->file().put_memory(path, strOptionsImpact);

#endif

            if (!m_pdocumentMenu->open_document(strOptionsImpact))
            {

               output_error_message("Failed to open the menu.");

               return;

            }

            auto pformview = m_pdocumentMenu->get_type_impact < ::user::form_view>();

            pformview->get_form()->add_handler(get_app());

            pformview->set_need_load_form_data();

         }

      }


   }


   bool pane_tab_impact::on_preparimpact_data(::user::impact_data * pimpactdata)
   {

      pimpactdata->m_pplaceholder = get_new_place_holder(get_data()->m_rectangleTabClient);

      if (pimpactdata->m_pplaceholder == nullptr)
      {

         return false;

      }

      return true;

   }


   bool pane_tab_impact::on_after_creatimpact_data(::user::impact_data * pimpactdata)
   {

      ::index iVisibleIndex = id_visible_index(pimpactdata->m_atom);

      if (iVisibleIndex < 0)
      {

         __keep(m_bDisableSavingRestorableTabs, true);

         if (!add_tab(pimpactdata->m_strTitle, pimpactdata->m_atom, true, false, pimpactdata->m_pplaceholder))
         {

            return false;

         }

         iVisibleIndex = id_visible_index(pimpactdata->m_atom);

         if (iVisibleIndex < 0)
         {

            return false;

         }

      }

      auto ptabpane = get_visible_tab(iVisibleIndex);

      if (ptabpane == nullptr)
      {

         return false;

      }

      ptabpane->m_pimpactdata = pimpactdata;

      ptabpane->m_pplaceholder = pimpactdata->m_pplaceholder;

      if (ptabpane->m_pplaceholder == nullptr)
      {

         return false;

      }

      pimpactdata->m_pimpactdata = (void *)pimpactdata;

      if (matches_restorable_tab(pimpactdata->m_atom, pimpactdata->m_pplaceholder))
      {

         save_restorable_tabs();

      }

      return true;

   }


   bool pane_tab_impact::on_place_hold(::user::interaction * pinteraction,::user::place_holder * pholder)
   {

      if (!::user::place_holder_container::on_place_hold(pinteraction, pholder))
      {

         return false;

      }

      auto & panea = get_data()->m_tabpanecompositea;

      for(i32 iTab = 0; iTab < panea.get_count(); iTab++)
      {

         if(panea[iTab]->m_pplaceholder == pholder)
         {

            ::user::impact_data * pimpactdata = get_impact_data(panea[iTab]->m_atom, false);

            if(pimpactdata != nullptr)
            {

               if(pimpactdata->m_puserinteraction == nullptr)
               {

                  pimpactdata->m_puserinteraction = pinteraction;

               }

            }

            break;

         }

      }

      return true;

   }


   ::user::tab_pane * pane_tab_impact::create_tab_by_id(const ::atom & atom)
   {

      ::user::impact_data * pimpactdata = get_impact_data(atom, get_data()->m_rectangleTabClient);

      if(pimpactdata == nullptr)
      {

         return nullptr;

      }

      index iIndex = id_index(pimpactdata->m_atom);

      if (iIndex < 0)
      {

         return nullptr;

      }

      auto ptabpane = get_tab(iIndex);

      return ptabpane;

   }


   void pane_tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      ::acme::library * plibrary = nullptr;

      auto psystem = m_psystem->m_paurasystem;

//      if(pimpactdata->m_atom.is_text() && psystem->m_idmapCreateImpactLibrary.lookup(pimpactdata->m_atom,plibrary) && plibrary != nullptr)
//      {
//
//
//      }
//      else
         if (pimpactdata->m_atom == "account")
      {

         __pointer(::account::impact) pimpact = create_view < ::account::impact >();

         if (pimpact.is_set())
         {

            pimpactdata->m_pdocument = get_document();

            pimpactdata->m_puserinteraction = pimpact;

            pimpactdata->m_iExtendOnParent = 0;

         }

      }
      else if (pimpactdata->m_atom == MENU_IMPACT)
      {

//         create_menu_impact(pimpactdata);

      }
      else if (pimpactdata->m_atom == OPTIONS_IMPACT)
      {

            if (!pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild
               || pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild->has_no_interaction())
            {

               auto puser = user()->m_pcoreuser;

               m_pdocumentMenu = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

               pimpactdata->m_eflag.add(::user::e_flag_hide_on_kill_focus);

            }

      }
      else if (is_font_sel(pimpactdata->m_atom))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         puser->will_use_view_hint(FONTSEL_IMPACT);

         //auto pcreate = __new(create(this));

         //pcreate->m_pusersystem = __new(user::create);

         //pcreate->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //pcreate->m_bMakeVisible = false;

         //pcreate->m_pusersystem

//         auto pdocument = puser->m_mapimpactsystem[FONTSEL_IMPACT]->do_request(get_app(), ::e_type_null, false, pimpactdata->m_pplaceholder);

         auto ptemplate = puser->m_mapimpactsystem[FONTSEL_IMPACT];

         auto pdocument = ptemplate->open_document_file(get_app(), ::e_type_null, __visible(true).is_true(), pimpactdata->m_pplaceholder);

         m_pfontview = pdocument->get_type_impact < font_view >();

         m_pfontview->set_need_layout();

         pdocument->m_pviewTopic->set_notify_user_interaction(this);

         pimpactdata->m_puserinteraction = pdocument->m_pviewTopic;
         
         m_pfontview->m_pimpact->add_handler(this);

         __pointer(::user::interaction) pimpact = psession->get_bound_ui(FONTSEL_IMPACT);

         if(pimpact)
         {

            m_pfontview->m_pimpact->add_handler(pimpact);

         }

      }
      else if (is_color_sel(pimpactdata->m_atom))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         puser->will_use_view_hint(COLORSEL_IMPACT);

         auto pimpactsystem = puser->m_mapimpactsystem[COLORSEL_IMPACT];

         //auto pdocument = pimpactsystem->open_document_file(get_app(), ::e_type_null, __visible(false).is_true(), pimpactdata->m_pplaceholder);

         m_pcolorview = create_view < color_view >(pimpactdata);

//         pdocument->m_pviewTopic->set_notify_user_interaction(this);

  //       pimpactdata->m_puserinteraction = pdocument->m_pviewTopic;
         
         m_pcolorview->add_handler(this);

         __pointer(::user::interaction) pimpact = psession->get_bound_ui(COLORSEL_IMPACT);

         if(pimpact)
         {

            m_pcolorview->add_handler(pimpact);

         }

      }
      else if(is_filemanager(pimpactdata->m_atom))
      {

         pimpactdata->m_eflag.add(::user::e_flag_tool_impact);

         auto pfilemanagerdata = cast < ::filemanager::data >("data." + pimpactdata->m_atom.str());

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_paurasession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         if (pfilemanagerdata.is_null())
         {

            pfilemanagerdata = puser->filemanager(pimpactdata->m_atom);

         }

         if (find_i32("filemanager_icon_size") > 0)
         {

            pfilemanagerdata->m_iIconSize = find_i32("filemanager_icon_size");

         }

         pfilemanagerdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //pfilemanagerdata->m_atom = pimpactdata->m_atom;

         if (has_property("filemanager_toolbar")
               && payload("filemanager_toolbar").m_etype == ::e_type_property_set)
         {

            auto & set = payload("filemanager_toolbar").as_propset();

            if (set[::userfs::mode_normal].is_set())
               pfilemanagerdata->m_setToolbar[::userfs::mode_normal] = set[::userfs::mode_normal];
            else
               pfilemanagerdata->m_setToolbar[::userfs::mode_normal] = "filemanager_toolbar.xml";

            if (set[::userfs::mode_saving].is_set())
               pfilemanagerdata->m_setToolbar[::userfs::mode_saving] = set[::userfs::mode_saving];
            else
               pfilemanagerdata->m_setToolbar[::userfs::mode_saving] = "filemanager_saving_toolbar.xml";

            if (set[::userfs::mode_import].is_set())
               pfilemanagerdata->m_setToolbar[::userfs::mode_import] = set[::userfs::mode_import];
            else
               pfilemanagerdata->m_setToolbar[::userfs::mode_import] = "filemanager_import_toolbar.xml";

            if (set[::userfs::mode_export].is_set())
               pfilemanagerdata->m_setToolbar[::userfs::mode_export] = set[::userfs::mode_export];
            else
               pfilemanagerdata->m_setToolbar[::userfs::mode_export] = "filemanager_export_toolbar.xml";

         }
//         else
//         {
//
//            pfilemanagerdata->m_setToolbar[::userfs::mode_normal] = "filemanager_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_saving] = "filemanager_saving_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_import] = "filemanager_import_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_export] = "filemanager_export_toolbar.xml";
//
//         }

         if(pfilemanagerdata->m_pcreate.is_null())
         {

            pfilemanagerdata->m_pcreate = __create_new< ::create>();

            pfilemanagerdata->m_pcreate->finish_initialization();

         }

         pfilemanagerdata->open();

         __pointer(::filemanager::document) pdocument = pfilemanagerdata->m_pdocument;

         if(pdocument != nullptr)
         {

            m_mapFileManager[pimpactdata->m_atom] = pdocument;

            __pointer(::user::impact) pimpact = pdocument->get_view();

            if(pimpact != nullptr)
            {

               __pointer(::user::frame_window) pframe = (__pointer(::user::frame_window)) pimpact->get_parent_frame();

               if(pframe != nullptr)
               {

                  pimpactdata->m_pdocument = pdocument;

               }

            }

         }

      }
      //else if(pimpactdata->m_atom == "tabbed_file_manager")
      //{

      //   __pointer(::create) cc(e_create);
      //   cc->m_bTransparentBackground     = true;
      //   cc->m_bMakeVisible               = true;
      //   cc->m_puserinteractionParent                  = pimpactdata->m_pplaceholder;

      //   __pointer(::filemanager::document) pmanager = puser->filemanager()->open(get_app(), -1, cc);

      //   if(pmanager != nullptr)
      //   {

      //      m_pfilemanagerTabbed = pmanager;

      //      __pointer(::user::impact) pimpact = pmanager->get_view();

      //      if(pimpact != nullptr)
      //      {

      //         __pointer(::user::frame_window) pframe = (__pointer(::user::frame_window)) pimpact->get_parent_frame();

      //         if(pframe != nullptr)
      //         {

      //            pimpactdata->m_pdocument = pmanager;

      //            pimpactdata->m_puserinteraction = pframe;

      //         }

      //      }

      //   }

      //}
      //else if (pimpactdata->m_atom == "app_options")
      //{

      //   create_app_options(pimpactdata);

      //}
      else if (pimpactdata->m_atom.is_text())
      {

         if (::str::begins_ci(pimpactdata->m_atom.m_psz, "form_"))
         {

            auto pcontext = m_pcontext;
            
            auto psession = pcontext->m_pcoresession;
            
            auto puser = psession->m_puser->m_pcoreuser;

            __pointer(form_document) pdocument = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

            if (pdocument.is_set())
            {

               m_mapForm[pimpactdata->m_atom] = pdocument;

               pdocument->m_atom = string("document.") + string(pimpactdata->m_atom);

               ::user::impact * pimpact = pdocument->get_view(0);

               pimpactdata->m_puserinteraction = pimpact->get_parent_frame();

               prepare_form(pimpactdata->m_atom, pdocument);

            }

         }

      }

      ::user::tab_view::on_create_impact(pimpactdata);
      
   }


   ::filemanager::document * pane_tab_impact::filemanager_document(const ::atom & atomFileManager)
   {

      auto pobject = m_mapFileManager[atomFileManager];

      return  (pobject == nullptr ? nullptr : dynamic_cast < ::filemanager::document * > (pobject.m_p));

   }


//   ::filemanager::document * pane_tab_impact::tabbed_filemanager_manager()
//   {
//
//      return  (m_pfilemanagerTabbed == nullptr ? nullptr : dynamic_cast < ::filemanager::document * > (m_pfilemanagerTabbed));
//
//   }


//   void pane_tab_impact::FileManagerSaveAs(::user::document * pdocument)
//   {
//
//      set_current_tab_by_id(impact_filemanager_main);
//
//      filemanager_document()->FileManagerSaveAs(pdocument);
//
//   }
//
//
//   void pane_tab_impact::TabbedFileManagerSaveAs(::user::document * pdocument)
//   {
//
//      set_current_tab_by_id("tabbed_file_manager");
//
//      tabbed_filemanager_manager()->FileManagerSaveAs(pdocument);
//
//   }


   void pane_tab_impact::_001OnTabClose(index iTab)
   {

      ::user::tab::_001OnTabClose(iTab);

      if(get_parent_frame()->ContinueModal() && ::is_set(filemanager_document("file_manager_save"))
            && filemanager_document("file_manager_save")->filemanager_data()->m_pdocumentTopic!= nullptr)
      {

         get_parent_frame()->EndModalLoop("yes");

      }

   }


   void pane_tab_impact::interactive_credentials(::account::credentials * pcredentials)
   {

      pcredentials->m_estatus = error_credentials;

      set_current_tab_by_id("account");

      __pointer(::account::impact) pimpact = get_view();

      if (pimpact.is_null())
      {

         return;

      }

      pimpact->interactive_credentials(pcredentials);

   }


   void pane_tab_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::tab_view::handle(ptopic, pcontext);

      if (ptopic->m_atom == ::id_context_menu_close)
      {

         if (m_pimpactdataOld != nullptr)
         {

            set_current_tab_by_id(m_pimpactdataOld->m_atom);

            ptopic->m_bRet = true;

            return;

         }

      }

      ::user::tab_view::handle(ptopic, pcontext);


   }


//   void pane_tab_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//
//      ::user::tab_view::_001OnNcDraw(pgraphics);
//
//
//   }


   //void pane_tab_impact::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   if (ptopic->m_atom == ::id_context_menu_close)
   //   {

   //      if (m_pimpactdataOld != nullptr)
   //      {

   //         set_current_tab_by_id(m_pimpactdataOld->m_atom);

   //         ptopic->m_bRet = true;

   //         return;

   //      }

   //   }

   //   ::user::tab_view::handle(ptopic, pcontext);

   //}


   //bool pane_tab_impact::create_app_options(::user::impact_data * pimpactdata)
   //{

   //   string strAppOptions = "matter://options.html";

   //   __pointer(simple_frame_window) pframe = get_parent();

   //   if (pframe.is_set())
   //   {

   //      strAppOptions = pframe->m_varFrame["app_options"]["resource"];

   //   }

   //   payload("app_options_title") = get_tab_by_id(pimpactdata->m_atom)->get_title();

   //   auto pcontext = m_pcontext;
   //   
   //   auto psession = pcontext->m_pcoresession;
   //   
   //   auto puser = psession->m_puser->m_pcoreuser;

   //   m_pdocAppOptions = puser->create_child_form(this, this, pimpactdata->m_pplaceholder, strAppOptions);

   //   //auto pform = m_pdocAppOptions->get_type_impact<::user::form>();

   //   //if (pform)
   //   //{

   //   //   if (pform->m_puserinteractionpointeraChild)
   //   //   {

   //   //      for (auto& p : pform->m_puserinteractionpointeraChild->interactiona())
   //   //      {

   //   //         p->add_control_event_handler(this);

   //   //      }

   //   //   }

   //   //}

   //   return true;

   //}


   void pane_tab_impact::prepare_form(atom atom, ::form_document * pdocument)
   {

      auto papp = get_app();

      papp->prepare_form(atom, pdocument);

   }


   void pane_tab_impact::_001OnRemoveTab(::user::tab_pane * ptab)
   {

      ::user::tab_view::_001OnRemoveTab(ptab);

      m_impactdatamap.erase_key(ptab->m_atom);

   }


   //::form_property_set * pane_tab_impact::get_form_property_set()
   //{
   //
   //   auto pset = form_callback::get_form_property_set();
   //
   //   if(pset)
   //   {
   //
   //      return pset;
   //
   //   }
   //
   //   pset = ::user::impact::get_form_property_set();
   //
   //   if(pset)
   //   {
   //
   //      return pset;
   //
   //   }
   //
   //   return nullptr;
   //
   //}


} // namespace userex

//namespace aura
//{
//
//::type system::get_pane_tab_view_type_info()
//{
//
//   return __type(userex::pane_tab_impact);
//
//}
//
//
//} // namespace aura
