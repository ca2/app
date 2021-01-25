#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "core/user/account/_account.h"
#endif
#include "aura/update.h"


namespace core
{


   ::type user::get_pane_tab_view_type_info()
   {

      return __type(::userex::pane_tab_view);

   }


} // namespace core


namespace userex
{


   pane_tab_view::pane_tab_view()
   {

      m_pcolorview = nullptr;

      m_pfilemanager = nullptr;
      m_pfilemanagerTabbed = nullptr;



   }


   pane_tab_view::~pane_tab_view()
   {

   }


   ::user::interaction * pane_tab_view::get_view_uie()
   {

      return ::user::tab_view::get_view_uie();

   }


   id pane_tab_view::get_view_id()
   {

      return ::user::tab_view::get_view_id();

   }


   void pane_tab_view::GetTabClientRect(RECT32 * prect)

   {

      if(m_pimpactdata == nullptr || m_pimpactdata->m_puserinteraction == nullptr || m_pimpactdata->m_iExtendOnParent == 0)
      {

         ::user::tab_view::GetTabClientRect(prect);


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

         pinteraction->get_window_rect(prect);


         _001ScreenToClient(prect);


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

            if (puiNext == nullptr || (pinteraction->m_pimpl) != nullptr)
            {

               break;

            }

            pinteraction = puiNext;

         }

         pinteraction = uia.interaction_at(uia.interaction_count() + m_pimpactdata->m_iExtendOnParent);

         pinteraction->get_window_rect(prect);

         _001ScreenToClient(prect);

      }

   }


   void pane_tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_tab_view::_001OnCreate);

      connect_command("file_save_as", &pane_tab_view::_001OnFileSaveAs);
      connect_command_probe("file_save_as", &pane_tab_view::_001OnUpdateFileSaveAs);

   }


   void pane_tab_view::_001OnCreate(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      m_pcreate = (::create *) pcreate->get_create();

      //if (Application.m_pmainpane == nullptr)
      //{

      //   Application.m_pmainpane = this;

      //}

      if (Application.m_puiMainContainer == nullptr)
      {

         Application.m_puiMainContainer = this;

      }

      if (pmessage->previous())
      {

         return;

      }


      __pointer(simple_frame_window) pframe = get_parent();

      if (pframe.is_set())
      {

         string strAppOptions(pframe->m_varFrame["app_options"]["resource"]);

         if (strAppOptions.has_char())
         {

            string strTitle(pframe->m_varFrame["app_options"]["title"]);

            add_tab(strTitle, "app_options");

         }

      }

   }


   void pane_tab_view::_001OnFileSaveAs(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      auto pdocument = m_pimpactdata->m_pdocument.cast < ::user::document >();

      if (::is_set(pdocument))
      {

         FileManagerSaveAs(pdocument);

      }

   }

   void pane_tab_view::_001OnUpdateFileSaveAs(::message::message * pmessage)
   {

      __pointer(::user::command) pcommand(pmessage);

      auto pdocument = m_pimpactdata->m_pdocument;

      pcommand->enable(::is_set(pdocument));

   }


   void pane_tab_view::on_change_cur_sel()
   {

      ::user::tab_view::on_change_cur_sel();

      if(m_pimpactdataOld != nullptr && is_filemanager(m_pimpactdataOld->m_id))
      {

         if(get_parent_frame()->ContinueModal())
         {

            get_parent_frame()->EndModalLoop("yes");

         }

         if(::is_set(filemanager_document()))
         {

            filemanager_document()->filemanager_data()->m_pdocumentTopic = nullptr;

         }

      }

   }


   bool pane_tab_view::on_prepare_impact_data(::user::impact_data * pimpactdata)
   {

      pimpactdata->m_pplaceholder = get_new_place_holder(get_data()->m_rectTabClient);

      if (pimpactdata->m_pplaceholder == nullptr)
      {

         return false;

      }

      return true;

   }


   bool pane_tab_view::on_after_create_impact_data(::user::impact_data * pimpactdata)
   {

      ::index iPane = id_pane(pimpactdata->m_id);

      if (iPane < 0)
      {

         __keep(m_bDisableSavingRestorableTabs, true);

         if (!add_tab(pimpactdata->m_idTitle, pimpactdata->m_id, true, false, pimpactdata->m_pplaceholder))
         {

            return false;

         }

         iPane = id_pane(pimpactdata->m_id);

         if (iPane < 0)
         {

            return false;

         }

      }

      ::user::tab_pane * ppane = (::user::tab_pane *)get_data()->m_panea.element_at(iPane);

      if (ppane == nullptr)
      {

         return false;

      }

      ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

      if (ppane->m_pplaceholder == nullptr)
      {

         return false;

      }

      pimpactdata->m_pimpactdata = (void *)ppane;

      if (matches_restorable_tab(pimpactdata->m_id, pimpactdata->m_pplaceholder))
      {

         save_restorable_tabs();

      }

      return true;

   }


   bool pane_tab_view::on_place_hold(::user::interaction * pinteraction,::user::place_holder * pholder)
   {

      if (!::user::place_holder_container::on_place_hold(pinteraction, pholder))
      {

         return false;

      }

      ::user::tab_pane_array & panea = get_data()->m_panea;

      for(i32 iTab = 0; iTab < panea.get_count(); iTab++)
      {

         if(panea[iTab]->m_pplaceholder == pholder)
         {

            ::user::impact_data * pimpactdata = get_impact_data(panea[iTab]->m_id, false);

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


   ::index pane_tab_view::create_tab_by_id(id id)
   {

      ::user::impact_data * pimpactdata = get_impact_data(id, get_data()->m_rectTabClient);

      if(pimpactdata == nullptr)
      {

         return -1;

      }

      index iTab = id_tab(pimpactdata->m_id);

      if (iTab < 0)
      {

         return -1;

      }

      return iTab;

   }


   void pane_tab_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      ::apex::library * plibrary = nullptr;

      if(pimpactdata->m_id.is_text() && System.m_idmapCreateViewLibrary.lookup(pimpactdata->m_id,plibrary) && plibrary != nullptr)
      {


      }
      else if (pimpactdata->m_id == "account")
      {

         __pointer(::account::view) pview = create_view < ::account::view >();

         if (pview.is_set())
         {

            pimpactdata->m_pdocument = get_document();

            pimpactdata->m_puserinteraction = pview;

            pimpactdata->m_iExtendOnParent = 0;

         }

      }
      else if (is_font_sel(pimpactdata->m_id))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto puser = User;

         puser->will_use_view_hint(FONTSEL_IMPACT);

         //auto pcreate = __new(create(this));

         //pcreate->m_pusersystem = __new(user::create);

         //pcreate->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //pcreate->m_bMakeVisible = false;

         //pcreate->m_pusersystem

//         auto pdocument = puser->m_mapimpactsystem[FONTSEL_IMPACT]->do_request(get_context_application(), ::e_type_null, false, pimpactdata->m_pplaceholder);
         auto pdocument = puser->m_mapimpactsystem[FONTSEL_IMPACT]->open_document_file(get_context_application(), ::e_type_null, __visible(true), pimpactdata->m_pplaceholder);

         m_pfontview = pdocument->get_typed_view < font_view >();

         m_pfontview->set_need_layout();

         pdocument->m_pviewTopic->set_notify_user_interaction(this);

         pimpactdata->m_puserinteraction = pdocument->m_pviewTopic;

      }
      else if (is_color_sel(pimpactdata->m_id))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto puser = User;

         puser->will_use_view_hint(COLORSEL_IMPACT);

         auto pimpactsystem = puser->m_mapimpactsystem[COLORSEL_IMPACT];

         auto pdocument = pimpactsystem->open_document_file(get_context_application(), ::e_type_null, __visible(false), pimpactdata->m_pplaceholder);

         m_pcolorview = pdocument->get_typed_view < color_view >();

         pdocument->m_pviewTopic->set_notify_user_interaction(this);

         pimpactdata->m_puserinteraction = pdocument->m_pviewTopic;

      }
      else if(is_filemanager(pimpactdata->m_id))
      {

         pimpactdata->m_eflag.add(::user::e_flag_tool_impact);

         auto pfilemanagerdata = cast < ::filemanager::data >("data." + pimpactdata->m_id.str());

         if (pfilemanagerdata.is_null())
         {

            auto puser = User;

            pfilemanagerdata = puser->filemanager(pimpactdata->m_id);

         }

         if (find_i32("filemanager_icon_size") > 0)
         {

            pfilemanagerdata->m_iIconSize = find_i32("filemanager_icon_size");

         }

         pfilemanagerdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //pfilemanagerdata->m_id = pimpactdata->m_id;

         if (has_property("filemanager_toolbar")
               && payload("filemanager_toolbar").m_etype == ::e_type_propset)
         {

            auto & set = payload("filemanager_toolbar").propset();

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

         auto puser = User;

         puser->filemanager(pimpactdata->m_id)->open();

         __pointer(::filemanager::document) pdocument = puser->filemanager(pimpactdata->m_id)->m_pdocument;

         if(pdocument != nullptr)
         {

            m_pfilemanager = pdocument;

            __pointer(::user::impact) pview = pdocument->get_view();

            if(pview != nullptr)
            {

               __pointer(::user::frame_window) pframe = (__pointer(::user::frame_window)) pview->get_parent_frame();

               if(pframe != nullptr)
               {

                  pimpactdata->m_pdocument = pdocument;

               }

            }

         }

      }
      //else if(pimpactdata->m_id == "tabbed_file_manager")
      //{

      //   __pointer(::create) cc(e_create);
      //   cc->m_bTransparentBackground     = true;
      //   cc->m_bMakeVisible               = true;
      //   cc->m_puserinteractionParent                  = pimpactdata->m_pplaceholder;

      //   __pointer(::filemanager::document) pmanager = puser->filemanager()->open(get_context_application(), -1, cc);

      //   if(pmanager != nullptr)
      //   {

      //      m_pfilemanagerTabbed = pmanager;

      //      __pointer(::user::impact) pview = pmanager->get_view();

      //      if(pview != nullptr)
      //      {

      //         __pointer(::user::frame_window) pframe = (__pointer(::user::frame_window)) pview->get_parent_frame();

      //         if(pframe != nullptr)
      //         {

      //            pimpactdata->m_pdocument = pmanager;

      //            pimpactdata->m_puserinteraction = pframe;

      //         }

      //      }

      //   }

      //}
      else if (pimpactdata->m_id == "app_options")
      {

         create_app_options(pimpactdata);

      }
      else if (pimpactdata->m_id.is_text())
      {

         if (::str::begins_ci(pimpactdata->m_id.m_psz, "form_"))
         {

            auto puser = User;

            __pointer(form_document) pdocument = puser->create_child_form(this, this, pimpactdata->m_pplaceholder);

            if (pdocument.is_set())
            {

               m_mapForm[pimpactdata->m_id] = pdocument;

               pdocument->m_id = string("document.") + string(pimpactdata->m_id);

               ::user::impact * pview = pdocument->get_view(0);

               pimpactdata->m_puserinteraction = pview->get_parent_frame();

               prepare_form(pimpactdata->m_id, pdocument);

            }

         }

      }

   }


   ::filemanager::document * pane_tab_view::filemanager_document()
   {

      return  (m_pfilemanager == nullptr ? nullptr : dynamic_cast < ::filemanager::document * > (m_pfilemanager));

   }


   ::filemanager::document * pane_tab_view::tabbed_filemanager_manager()
   {

      return  (m_pfilemanagerTabbed == nullptr ? nullptr : dynamic_cast < ::filemanager::document * > (m_pfilemanagerTabbed));

   }


   void pane_tab_view::FileManagerSaveAs(::user::document * pdocument)
   {

      set_cur_tab_by_id(impact_filemanager_main);

      filemanager_document()->FileManagerSaveAs(pdocument);

   }


   void pane_tab_view::TabbedFileManagerSaveAs(::user::document * pdocument)
   {

      set_cur_tab_by_id("tabbed_file_manager");

      tabbed_filemanager_manager()->FileManagerSaveAs(pdocument);

   }


   void pane_tab_view::_001OnTabClose(index iTab)
   {

      ::user::tab::_001OnTabClose(iTab);

      if(get_parent_frame()->ContinueModal() && ::is_set(filemanager_document())
            && filemanager_document()->filemanager_data()->m_pdocumentTopic!= nullptr)
      {

         get_parent_frame()->EndModalLoop("yes");

      }

   }


   void pane_tab_view::interactive_credentials(::account::credentials * pcredentials)
   {

      pcredentials->m_estatus = error_credentials;

      set_cur_tab_by_id("account");

      __pointer(::account::view) pview = get_view();

      if (pview.is_null())
      {

         return;

      }

      pview->interactive_credentials(pcredentials);

   }


   void pane_tab_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::user::tab_view::on_subject(psubject, pcontext);

   }


   void pane_tab_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {


      ::user::tab_view::_001OnNcDraw(pgraphics);


   }

   void pane_tab_view::on_control_event(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::e_event_context_menu_close)
      {

         if (m_pimpactdataOld != nullptr)
         {

            set_cur_tab_by_id(m_pimpactdataOld->m_id);

            pevent->m_bRet = true;

            return;

         }

      }

      ::user::tab_view::on_control_event(pevent);

   }


   bool pane_tab_view::create_app_options(::user::impact_data * pimpactdata)
   {

      string strAppOptions = "matter://options.html";

      __pointer(simple_frame_window) pframe = get_parent();

      if (pframe.is_set())
      {

         strAppOptions = pframe->m_varFrame["app_options"]["resource"];

      }

      payload("app_options_title") = get_pane_by_id(pimpactdata->m_id)->get_title();

      auto puser = User;

      m_pdocAppOptions = puser->create_child_form(this, this, pimpactdata->m_pplaceholder, strAppOptions);

      return true;

   }


   void pane_tab_view::prepare_form(id id, ::form_document * pdocument)
   {

      Application.prepare_form(id, pdocument);

   }


   void pane_tab_view::_001OnRemoveTab(::user::tab_pane * ptab)
   {

      ::user::tab_view::_001OnRemoveTab(ptab);

      m_impactdatamap.remove_key(ptab->m_id);

   }


   //::form_property_set * pane_tab_view::get_form_property_set()
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
//   return __type(userex::pane_tab_view);
//
//}
//
//
//} // namespace aura
