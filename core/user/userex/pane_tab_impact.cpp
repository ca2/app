#include "framework.h"
#include "pane_tab_impact.h"
#include "font_impact.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/handler/request.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction_array.h"
#include "axis/account/credentials.h"
#include "berg/user/user/tab_pane.h"
#include "berg/user/user/frame_window.h"
#include "berg/user/form/impact.h"
#include "berg/user/user/tab_data.h"
#include "berg/user/user/impact_system.h"
#include "berg/user/user/multiple_document_template.h"
#include "core/user/user/font_list.h"
#include "core/user/user/user.h"
#include "core/filesystem/filemanager/document.h"
#include "core/filesystem/filemanager/data.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/platform/application.h"
#include "core/platform/session.h"
#include "core/user/account/impact.h"
#include "core/user/user/color_selector_impact.h"
#include "core/user/user/font_list_impact.h"


namespace core
{


   ::type_atom user::get_pane_tab_impact_type_info()
   {

      return ::type < ::userex::pane_tab_impact >();

   }


} // namespace core


namespace userex
{


   pane_tab_impact::pane_tab_impact()
   {

      //m_pcolorimpact = nullptr;

      //m_pfilemanager = nullptr;

      //m_pfilemanagerTabbed = nullptr;

   }


   pane_tab_impact::~pane_tab_impact()
   {

   }


   ::user::interaction * pane_tab_impact::get_impact_uie()
   {

      return ::user::tab_impact::get_impact_uie();

   }


   atom pane_tab_impact::get_impact_id()
   {

      return ::user::tab_impact::get_impact_id();

   }


   void pane_tab_impact::GetTabClientRect(::int_rectangle & rectangle)
   {

      if(m_pimpactdata == nullptr || m_pimpactdata->m_puserinteraction == nullptr || m_pimpactdata->m_iExtendOnParent == 0)
      {

         ::user::tab_impact::GetTabClientRect(rectangle);


      }
      else if(m_pimpactdata->m_iExtendOnParent > 0)
      {

         int i = m_pimpactdata->m_iExtendOnParent;

         ::pointer<::user::interaction>pinteraction = m_pimpactdata->m_puserinteraction;

         ::pointer<::user::interaction>puiNext = m_pimpactdata->m_puserinteraction;

         for(; i > 0; i--)
         {

            puiNext = pinteraction->get_parent();

            if (puiNext == nullptr || !puiNext->is_window())
            {

               break;

            }

            pinteraction = puiNext;

         }

         pinteraction->window_rectangle(rectangle);

         screen_to_client()(rectangle);

      }
      else if(m_pimpactdata->m_iExtendOnParent < 0)
      {

         ::pointer<::user::interaction>pinteraction = m_pimpactdata->m_puserinteraction;

         ::pointer<::user::interaction>puiNext = m_pimpactdata->m_puserinteraction;

         ::user::interaction_array uia;

         while(true)
         {

            uia.add_interaction(pinteraction);

            puiNext = pinteraction->get_parent();

            if (puiNext == nullptr || (pinteraction->m_pacmewindowingwindow) != nullptr)
            {

               break;

            }

            pinteraction = puiNext;

         }

         pinteraction = uia.interaction_at(uia.interaction_count() + m_pimpactdata->m_iExtendOnParent);

         pinteraction->window_rectangle(rectangle);

         screen_to_client()(rectangle);

      }

   }


   void pane_tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_tab_impact::on_message_create);

      add_command_handler("file_save_as", { this,  &pane_tab_impact::_001OnFileSaveAs });
      add_command_prober("file_save_as", { this,  &pane_tab_impact::_001OnUpdateFileSaveAs });

   }


   ::user::interaction * pane_tab_impact::get_font_interaction()
   {
     
      if(::is_null(m_pfontimpact))
      {
         
         return nullptr;
         
      }
      
      auto pimpact = m_pfontimpact->m_pimpact;
      
      if(::is_null(pimpact))
      {
         
         return nullptr;
         
      }
      
      return pimpact;
      
   }


   ::user::interaction * pane_tab_impact::get_color_interaction()
   {
  
      if(::is_null(m_pcolorselectorimpact))
      {
         
         return nullptr;
         
      }
      
      auto pimpact = m_pcolorselectorimpact;
      
      if(::is_null(pimpact))
      {
         
         return nullptr;
         
      }
      
      return pimpact;
      
   }


   void pane_tab_impact::add_pane_tab_impact_handler_library(const ::scoped_string & scopedstrLibrary)
   {

      auto & pfactory = system()->factory(scopedstrLibrary);

      auto phandler = __øcreate <handler>(pfactory);

      phandler->initialize(this);

      m_handlera.add(phandler);

   }


   // ::core::application* pane_tab_impact::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session* pane_tab_impact::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system* pane_tab_impact::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   void pane_tab_impact::on_message_create(::message::message * pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      if (!get_app()->m_ppaneimpactCore)
      {

         get_app()->m_ppaneimpactCore = this;
       
      }

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


      //::pointer<simple_frame_window>pframe = get_parent();

      //if (pframe.is_set())
      //{

      //   string strAppOptions(pframe->m_varFrame["options_impact"]["resource"]);

      //   if (strAppOptions.has_character())
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

      ::pointer<::message::command>pcommand(pmessage);

      auto pdocument = m_pimpactdata->m_pdocument;

      pcommand->enable(::is_set(pdocument));

   }


   void pane_tab_impact::on_change_cur_sel()
   {

      ::user::tab_impact::on_change_cur_sel();

      if (m_pimpactdataOld != nullptr && is_filemanager(m_pimpactdataOld->id()))
      {

         if (parent_frame()->is_waiting_for_dialog_result())
         {

            parent_frame()->set_dialog_result("yes");

         }

         if (::is_set(filemanager_document("file_manager_save")))
         {

            filemanager_document("file_manager_save")->filemanager_data()->m_pdocumentTopic = nullptr;

         }

      }
//      else if(m_pimpactdata->id() == OPTIONS_IMPACT)
//      {
//
//         if (::is_set(m_pformdocumentMenu))
//         {
//
//            auto strOptionsImpact = get_app()->prepare_impact_options();
//
//#if defined(_DEBUG) && !defined(UNIVERSAL_WINDOWS) && !defined(APPLE_IOS)
//
//            auto pcontext = m_papplication;
//
//            ::file::path path;
//            
//            path = pcontext->directory()->appdata() / "debug_ca2/menu_impact" / (get_app()->m_strAppId + ".html");
//
//            pcontext->file()->put_memory(path, strOptionsImpact);
//
//#endif
//
//            if (!m_pformdocumentMenu->open_document(strOptionsImpact))
//            {
//
//               output_error_message("Failed to open the menu.");
//
//               return;
//
//            }
//
//            auto pformview = m_pformdocumentMenu->get_typed_impact < ::user::form_impact>();
//
//            pformview->get_form()->add_handler(get_app());
//
//            pformview->set_need_load_form_data();
//
//         }
//
//      }


   }


   bool pane_tab_impact::on_prepare_impact_data(::user::impact_data * pimpactdata)
   {

      pimpactdata->m_pplaceholder = get_new_place_holder(get_data()->m_rectangleHosting);

      if (pimpactdata->m_pplaceholder == nullptr)
      {

         return false;

      }

      return true;

   }


   bool pane_tab_impact::on_after_create_impact_data(::user::impact_data * pimpactdata)
   {

      ::collection::index iVisibleIndex = id_visible_index(pimpactdata->id());

      if (iVisibleIndex < 0)
      {

         KEEP(m_bDisableSavingRestorableTabs, true);

         if (!add_tab(pimpactdata->m_strTitle, pimpactdata->id(), true, false, pimpactdata->m_pplaceholder))
         {

            return false;

         }

         iVisibleIndex = id_visible_index(pimpactdata->id());

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

      ptabpane->m_pplaceholder->m_bExtendOnParentHostingArea = true;

      ptabpane->m_pplaceholder->place(this->hosting_rectangle());

      pimpactdata->m_pimpactdata = (void *)pimpactdata;

      if (matches_restorable_tab(pimpactdata->id(), pimpactdata->m_pplaceholder))
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

      auto & panea = get_data()->m_tabpanea;

      for(int iTab = 0; iTab < panea.get_count(); iTab++)
      {

         if(panea[iTab]->m_pplaceholder == pholder)
         {

            ::user::impact_data * pimpactdata = get_impact_data(panea[iTab]->id(), false);

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

      //::user::impact_data * pimpactdata = get_impact_data(atom, get_data()->m_rectangleHosting);

      ::user::impact_data * pimpactdata = get_impact_data(atom, true);

      if(pimpactdata == nullptr)
      {

         return nullptr;

      }

      ::collection::index iIndex = id_index(pimpactdata->id());

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

      auto psystem = system();

//      if(pimpactdata->id().is_text() && psystem->m_idmapCreateImpactLibrary.find(pimpactdata->id(),plibrary) && plibrary != nullptr)
//      {
//
//
//      }
//      else
         if (pimpactdata->id() == "account")
      {

         ::pointer<::account::impact>pimpact = create_impact < ::account::impact >();

         if (pimpact.is_set())
         {

            pimpactdata->m_pdocument = get_document();

            pimpactdata->m_puserinteraction = pimpact;

            pimpactdata->m_iExtendOnParent = 0;

         }

      }
      else if (pimpactdata->id() == MENU_IMPACT)
      {

//         create_menu_impact(pimpactdata);

      }
      //else if (pimpactdata->id() == OPTIONS_IMPACT)
      //{

      //   if (!pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild
      //      || pimpactdata->m_pplaceholder->m_puserinteractionpointeraChild->has_no_interaction())
      //   {

      //      auto puser = coreuser();

      //      m_pformdocumentMenu = puser->create_child_form(this, nullptr, this, pimpactdata->m_pplaceholder);

      //      pimpactdata->m_eflag.add(::user::e_flag_hide_on_kill_focus);

      //   }

      //}
      else if (is_font_sel(pimpactdata->id()))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         puser->will_use_impact_hint(FONTSEL_IMPACT);

         //auto pcreate = __allocate create(this);

         //pcreate->m_pusersystem = __allocate user::create();

         //pcreate->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //pcreate->m_bMakeVisible = false;

         //pcreate->m_pusersystem

//         auto pdocument = puser->m_mapimpactsystem[FONTSEL_IMPACT]->do_request(get_app(), ::e_type_null, false, pimpactdata->m_pplaceholder);

         auto ptemplate = puser->impact_system(FONTSEL_IMPACT);

         auto pdocument = ptemplate->open_document_file(get_app(), ::e_type_null, __visible(true).is_true(), pimpactdata->m_pplaceholder);

         m_pfontimpact = pdocument->get_typed_impact < font_impact >();

         m_pfontimpact->set_need_layout();

         pdocument->m_pimpactTopic->set_notify_user_interaction(this);

         pimpactdata->m_puserinteraction = pdocument->m_pimpactTopic;
         
         m_pfontimpact->m_pimpact->add_handler(this);

         ::pointer<::user::interaction>pimpact = psession->get_bound_ui(FONTSEL_IMPACT);

         if(pimpact)
         {

            m_pfontimpact->m_pimpact->add_handler(pimpact);

         }

      }
      else if (is_color_sel(pimpactdata->id()))
      {

         pimpactdata->m_eflag.add(::user::e_flag_modifier_impact);

         auto pcontext = m_papplication;
         
         auto psession = pcontext->m_psession;
         
         auto puser = psession->m_puser;

         puser->will_use_impact_hint(COLORSEL_IMPACT);

         auto pimpactsystem = puser->impact_system(COLORSEL_IMPACT);

         //auto pdocument = pimpactsystem->open_document_file(get_app(), ::e_type_null, __visible(false).is_true(), pimpactdata->m_pplaceholder);

         m_pcolorselectorimpact = create_impact < ::user::color_selector_impact >(pimpactdata);

//         pdocument->m_pviewTopic->set_notify_user_interaction(this);

  //       pimpactdata->m_puserinteraction = pdocument->m_pviewTopic;
         
         m_pcolorselectorimpact->add_handler(this);

         ::pointer<::user::interaction>pimpact = psession->get_bound_ui(COLORSEL_IMPACT);

         if(pimpact)
         {

            m_pcolorselectorimpact->add_handler(pimpact);

         }

      }
      else if(is_filemanager(pimpactdata->id()))
      {

         pimpactdata->m_eflag.add(::user::e_flag_tool_impact);

         //auto pfilemanagerdata = cast < ::filemanager::data >("data." + pimpactdata->id());

         //auto pcontext = m_papplication;
         //
         //auto psession = pcontext->m_psession;
         //
         //auto puser = psession->m_puser;

         //if (pfilemanagerdata.is_null())
         //{

         //   pfilemanagerdata = puser->filemanager(pimpactdata->id());

         //}

         auto pfilemanager = application()->filemanager();

         auto pfilemanagerdata = pfilemanager->create_filemanager_data();

         pfilemanagerdata->id() = pimpactdata->id();

         auto pfilemanagerdocument = pfilemanager->impact_system()->create_subdocument(pimpactdata, pfilemanagerdata);

         pfilemanagerdata->m_pfilemanagerdocument = pfilemanagerdocument;

   /*      if (find_int("filemanager_icon_size") > 0)
         {

            pfilemanagerdata->m_iIconSize = find_int("filemanager_icon_size");

         }*/

         //pfilemanagerdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         //if (has_property("filemanager_toolbar")
         //      && payload("filemanager_toolbar").m_etype == ::e_type_property_set)
         //{

         //   auto & set = payload("filemanager_toolbar");

         //   if (set[::userfs::e_mode_normal].is_set())
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_normal] = set[::userfs::e_mode_normal];
         //   else
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_normal] = "filemanager_toolbar.xml";

         //   if (set[::userfs::e_mode_saving].is_set())
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_saving] = set[::userfs::e_mode_saving];
         //   else
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_saving] = "filemanager_saving_toolbar.xml";

         //   if (set[::userfs::e_mode_import].is_set())
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_import] = set[::userfs::e_mode_import];
         //   else
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_import] = "filemanager_import_toolbar.xml";

         //   if (set[::userfs::e_mode_export].is_set())
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_export] = set[::userfs::e_mode_export];
         //   else
         //      pfilemanagerdata->m_setToolbar[::userfs::e_mode_export] = "filemanager_export_toolbar.xml";

         //}
//         else
//         {
//
//            pfilemanagerdata->m_setToolbar[::userfs::mode_normal] = "filemanager_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_saving] = "filemanager_saving_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_import] = "filemanager_import_toolbar.xml";
//            pfilemanagerdata->m_setToolbar[::userfs::mode_export] = "filemanager_export_toolbar.xml";
//
//         }

         //if(pfilemanagerdata->m_prequest.is_null())
         //{

         //   pfilemanagerdata->m_prequest = __create_new< ::request>();

         //   pfilemanagerdata->m_prequest->finish_initialization();

         //}

         //pfilemanagerdata->open();

         ::pointer<::filemanager::document>pdocument = pfilemanagerdata->m_pfilemanagerdocument;

         if(pdocument != nullptr)
         {

            m_mapFileManager[pimpactdata->id()] = pdocument;

            ::pointer<::user::impact>pimpact = pdocument->get_impact();

            if(pimpact != nullptr)
            {

               ::pointer<::user::frame_window>pframe = pimpact->parent_frame();

               if(pframe != nullptr)
               {

                  pimpactdata->m_pdocument = pdocument;

               }

            }

         }

      }
      //else if(pimpactdata->id() == "tabbed_file_manager")
      //{

      //   ::pointer<::create>cc(e_create);
      //   cc->m_bTransparentBackground     = true;
      //   cc->m_bMakeVisible               = true;
      //   cc->m_puserinteractionParent                  = pimpactdata->m_pplaceholder;

      //   ::pointer<::filemanager::document>pmanager = puser->filemanager()->open(get_app(), -1, cc);

      //   if(pmanager != nullptr)
      //   {

      //      m_pfilemanagerTabbed = pmanager;

      //      ::pointer<::user::impact>pimpact = pmanager->get_impact();

      //      if(pimpact != nullptr)
      //      {

      //         ::pointer<::user::frame_window>pframe = (::pointer<::user::frame_window>pimpact->get_parent_frame();

      //         if(pframe != nullptr)
      //         {

      //            pimpactdata->m_pdocument = pmanager;

      //            pimpactdata->m_puserinteraction = pframe;

      //         }

      //      }

      //   }

      //}
      //else if (pimpactdata->id() == "app_options")
      //{

      //   create_app_options(pimpactdata);

      //}

      ::user::tab_impact::on_create_impact(pimpactdata);
      
   }


   ::filemanager::document * pane_tab_impact::filemanager_document(const ::atom & atomFileManager)
   {

      auto pparticle = m_mapFileManager[atomFileManager];

      return  (pparticle == nullptr ? nullptr : dynamic_cast < ::filemanager::document * > (pparticle.m_p));

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


   void pane_tab_impact::_001OnTabClose(::collection::index iTab)
   {

      ::user::tab::_001OnTabClose(iTab);

      if(parent_frame()->is_waiting_for_dialog_result() && ::is_set(filemanager_document("file_manager_save"))
            && filemanager_document("file_manager_save")->filemanager_data()->m_pdocumentTopic!= nullptr)
      {

         parent_frame()->set_dialog_result("yes");

      }

   }


   void pane_tab_impact::interactive_credentials(::account::credentials * pcredentials)
   {

      pcredentials->m_estatus = error_credentials;

      set_current_tab_by_id("account");

      ::pointer<::account::impact>pimpact = get_impact();

      if (pimpact.is_null())
      {

         return;

      }

      pimpact->interactive_credentials(pcredentials);

   }


   void pane_tab_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::tab_impact::handle(ptopic, phandlercontext);

      for (auto & phandler : m_handlera)
      {

         phandler->handle(this, ptopic, phandlercontext);

         if(ptopic->m_bRet)
         {

            return;

         }

      }

      if (ptopic->id() == ::id_context_menu_close)
      {

         if (m_pimpactdataOld != nullptr)
         {

            set_current_tab_by_id(m_pimpactdataOld->id());

            ptopic->m_bRet = true;

            return;

         }

      }

      ::user::tab_impact::handle(ptopic, phandlercontext);


   }


//   void pane_tab_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
//   {
//
//
//      ::user::tab_impact::_001OnNcDraw(pgraphics);
//
//
//   }


   //void pane_tab_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   if (ptopic->id() == ::id_context_menu_close)
   //   {

   //      if (m_pimpactdataOld != nullptr)
   //      {

   //         set_current_tab_by_id(m_pimpactdataOld->id());

   //         ptopic->m_bRet = true;

   //         return;

   //      }

   //   }

   //   ::user::tab_impact::handle(ptopic, phandlercontext);

   //}


   //bool pane_tab_impact::create_app_options(::user::impact_data * pimpactdata)
   //{

   //   string strAppOptions = "matter://options.html";

   //   ::pointer<simple_frame_window>pframe = get_parent();

   //   if (pframe.is_set())
   //   {

   //      strAppOptions = pframe->m_varFrame["app_options"]["resource"];

   //   }

   //   payload("app_options_title") = get_tab_by_id(pimpactdata->id())->get_title();

   //   auto pcontext = m_papplication;
   //   
   //   auto psession = pcontext->m_psession;
   //   
   //   auto puser = psession->m_puser;

   //   m_pdocAppOptions = puser->create_child_form(this, this, pimpactdata->m_pplaceholder, strAppOptions);

   //   //auto pform = m_pdocAppOptions->get_typed_impact<::user::form>();

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


   void pane_tab_impact::prepare_form(const ::atom & atom, ::form_document * pdocument)
   {

      auto papp = get_app();

      papp->prepare_form(atom, pdocument);

   }


   void pane_tab_impact::_001OnRemoveTab(::user::tab_pane * ptab)
   {

      ::user::tab_impact::_001OnRemoveTab(ptab);

      m_impactdatamap.erase_key(ptab->id());

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
//::type system::get_pane_tab_impact_type_info()
//{
//
//   return ::type < userex::pane_tab_impact >();
//
//}
//
//
//} // namespace aura
