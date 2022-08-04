#include "framework.h"
#include "base/update.h"


namespace prompt
{


   pane_impact::pane_impact(::object * pobject) :
      ::object(pobject),
      ::user::tab_impact(pobject),
      ::userex::pane_tab_impact(pobject),
      place_holder_container(pobject)
   {


   }


   pane_impact::~pane_impact()
   {

   }



   void pane_impact::assert_ok() const
   {
      ::user::impact::assert_ok();
   }

   void pane_impact::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   void pane_impact::on_message_create(::message::message * pmessage)
   {

      if (pmessage->previous())
      {

         return;

      }

      add_tab("3-action-launch", impact_three_action_launch);
      add_tab("menu", CONTEXT_MENU_IMPACT);
      add_tab("primary verbing", impact_primary_command);
      add_tab("options", impact_configuration);
      add_tab("File Manager", FILEMANAGER_IMPACT);

      set_current_tab_by_id(impact_primary_command);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::tab_impact::handle(ptopic, pcontext);

   }


   void pane_impact::on_change_cur_sel()
   {
      ::userex::pane_tab_impact::on_change_cur_sel();
      __pointer(frame) pframe = GetTypedParent < frame > ();

      if(get_view_id() == FILEMANAGER_IMPACT)
      {
         pframe->m_bAutoHideOnOutClick = false;
         
         //pframe->ShowWindow(SW_MAXIMIZE);
         
         pframe->display();
         
      }
      else if(get_view_id() == CONTEXT_MENU_IMPACT)
      {
         __pointer(::filemanager::document) pdocument =  (get_view_uie());
         pdocument->browse(pcontext->m_papexcontext->dir().appdata()/ "command/menu", ::e_source_system);
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
         //pframe->OnHoverAction(false);
      }
   }


   void pane_impact::on_message_size(::message::message * pmessage)
   {
      pmessage->previous();

   }


   bool pane_impact::pre_create_window(::user::system * pusersystem)
   {


      return ::user::impact::pre_create_window(pusersystem);
   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
      switch(pimpactdata->m_atom)
      {
      case CONTEXT_MENU_IMPACT:
      {

         auto pdata = psession->filemanager("filemanager::list");

         pdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;
         pdata->m_iIconSize = 16;
         pdata->m_bListText = true;
         pdata->m_bListSelection = false;
         pdata->m_datakey = "winactionarea_menu";
         pdata->m_pcallback = this;
         pdata->m_strXmlPopup = "matter://filemanager\\file_popup.xml";

         bool bOk = pdata->open(get_app(), pcontext->m_papexcontext->dir().appdata() / "command/menu", ::e_source_system);

         if(bOk && ::is_set(pdata->m_pdocument))
         {

            //pdocument->browse();

            ////pdocument->Initialize(true);
            ////pdocument->update_all_views(id_unknown); // 1234);
            ////pdocument->update_all_views(id_unknown); //123458);
            __pointer(::user::impact) pimpact = pdata->m_pdocument->get_view();

            if(pimpact != nullptr)
            {
               __pointer(::user::frame_window) pframe =  (pimpact->get_parent_frame());
               if(pframe != nullptr)
               {
#ifdef WINDOWS_DESKTOP
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
#endif
                  pframe->SetParent(this);
                  pimpactdata->m_pdocument = pdata->m_pdocument;
                  pimpactdata->m_puserinteraction = pframe;
               }
            }
         }
      }
      break;
      case impact_primary_command:
      {
         __pointer(::user::impact) pimpact = create_view < primary_view > ();
         if(pimpact != nullptr)
         {
            pimpactdata->m_pdocument = get_document();
            pimpactdata->m_puserinteraction = pimpact;
            pimpactdata->m_iExtendOnParent = 0;
         }
      }
      break;
//      case FILEMANAGER_IMPACT:
//      {
//         __pointer(::filemanager::document) pdocument = puser->filemanager()->open_child(false, true);
//         if(pdocument != nullptr)
//         {
//            pdocument->filemanager_data()->m_datakey = "winactionarea_filemanager";
//            pdocument->Initialize(true);
//            pdocument->update_all_views(id_unknown); //1234);
//            pdocument->update_all_views(id_unknown); //123458);
//            __pointer(::user::impact) pimpact = pdocument->get_view();
//            if(pimpact != nullptr)
//            {
//               __pointer(::user::frame_window) pframe =  (pimpact->get_parent_frame());
//               if(pframe != nullptr)
//               {
//#ifdef WINDOWS_DESKTOP
//                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
//#endif
//                  pframe->SetParent(this);
//                  pimpactdata->m_pdocument = pdocument;
//                  pimpactdata->m_puserinteraction = pframe;
//
//
//               }
//            }
//         }
//      }
//      break;
      case impact_three_action_launch:
      {

         auto pdata = psession->filemanager("filemanager::list");

         pdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;
         pdata->m_iIconSize = 48;
         pdata->m_bListText = false;
         pdata->m_bListSelection = false;
         pdata->m_datakey = "winactionarea_3-action-launch";
         pdata->m_pcallback = this;
         //pdata->m_strFilePopup = "filemanager\\file_popup.xml";

         //auto pdocument = pdata->browse(pcontext->m_papexcontext->dir().appdata() / "co
         pdata->open(get_app(), pcontext->m_papexcontext->dir().appdata() / "command\\3-action-launch", ::e_source_system);

         if(::is_set(pdata->m_pdocument))
         {
            //pdocument->filemanager_data()->m_iIconSize = 48;
            //pdocument->filemanager_data()->m_bListText = false;
            //pdocument->filemanager_data()->m_bListSelection = false;
            //pdocument->filemanager_data()->m_pcallback = this;
            //pdocument->filemanager_data()->m_datakey = "winactionarea_3-action-launch";
            //pdocument->Initialize(true);
            //pdocument->update_all_views(id_unknown); // 1234);
            //pdocument->update_all_views(id_unknown); //123458);
            __pointer(::user::impact) pimpact = pdata->m_pdocument->get_view();

            //pdocument->FileManagerBrowse();

            if(pimpact != nullptr)
            {
               __pointer(::user::frame_window) pframe =  (pimpact->get_parent_frame());
               if(pframe != nullptr)
               {
#ifdef WINDOWS_DESKTOP
                  pframe->ModifyStyle(WS_CAPTION, WS_CHILD, 0);
#endif
                  pframe->SetParent(this);
                  pimpactdata->m_pdocument = pdata->m_pdocument;
                  pimpactdata->m_puserinteraction = pframe;


               }
            }
         }
      }
      break;
      case impact_configuration:
      {
         __pointer(::user::document) pdocument = papp->create_form(this, this);
         if(pdocument == nullptr)
            return;
         ::user::impact_data * pimpactdata = new ::user::impact_data;
         __pointer(::user::impact) pimpact = pdocument->get_type_impact < ::user::impact > ();
         auto pupdate = new_update();
         pupdate->m_actioncontext = ::e_source_system;
         ptopic->m_atom = id_browse;
         ptopic->payload(id_form) = "filemanager\\replace_name_in_file_system.xhtml";
         pdocument->update_all_views(pupdate);

         ptopic->m_atom = id_get_form_impact;
         pdocument->update_all_views(pupdate);

         ptopic->m_atom = id_after_browse;
         pdocument->update_all_views(pupdate);


         pimpactdata->m_puserinteraction = (pimpact->get_parent_frame());
//         __pointer(form_child_frame) pframe = (pimpactdata->m_puserinteraction);
         //pframe->m_iTabId = iId;
         pimpactdata->m_pdocument = pdocument;
      }
      break;
      default:
         ASSERT(false);
         break;
      }

      pane_tab_impact::on_create_impact(pimpactdata);

   }


   void pane_impact::_001OnMenuMessage(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      set_current_tab_by_id(m_pimpactdataOld->m_atom);

   }


   void pane_impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &pane_impact::on_message_create);
      MESSAGE_LINK(e_message_size, pchannel, this, &pane_impact::on_message_size);
      MESSAGE_LINK(WM_USER + 1122, this, this, &pane_impact::_001OnMenuMessage);

   }


   void pane_impact::rotate()
   {

      atom idNew;

      if (get_view_id() == FILEMANAGER_IMPACT)
      {

         idNew = CONTEXT_MENU_IMPACT;

      }
      else
      {

         switch (get_view_id())
         {
         case CONTEXT_MENU_IMPACT:
            idNew = impact_primary_command;
            break;
         case impact_primary_command:
            idNew = FILEMANAGER_IMPACT;
            break;
         default:
            idNew = impact_primary_command;
         }

      }

      set_current_tab_by_id(idNew);

   }


   void pane_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::prompt::form_callback::handle(ptopic, pcontext);

      if(ptopic->m_bRet)
      {

         return;

      }

      ::userex::pane_tab_impact::handle(ptopic, pcontext);

   }


   void pane_impact::OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema)
   {

      __UNREFERENCED_PARAMETER(pdata);

      if(itema.get_size() > 0)
      {

         //iptr i = 0;

         pcontext->m_papexcontext->os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());

         //string str;

         //str.format("%d", i);

         ////message_box(str);

         //if(i == ERROR_FILE_NOT_FOUND)
         //{

         //}

      }

      //get_parent_frame()->hide();
      
      get_parent_frame()->display();

   }


} // namespace prompt


