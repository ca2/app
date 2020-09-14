#include "framework.h"
#include "base/update.h"


namespace prompt
{


   pane_view::pane_view(::layered * pobjectContext) :
      ::object(pobject),
      ::user::tab_view(pobject),
      ::userex::pane_tab_view(pobject),
      place_holder_container(pobject)
   {


   }


   pane_view::~pane_view()
   {

   }



   void pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }


   void pane_view::_001OnCreate(::message::message * pmessage)
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

      set_cur_tab_by_id(impact_primary_command);

   }


   void pane_view::update(::update * pupdate)
   {

      ::user::tab_view::update(pupdate);

   }


   void pane_view::on_change_cur_sel()
   {
      ::userex::pane_tab_view::on_change_cur_sel();
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
         pdocument->browse(Context.dir().appdata()/ "command/menu", ::source_system);
      }
      else
      {
         pframe->m_bAutoHideOnOutClick = true;
         //pframe->OnHoverAction(false);
      }
   }


   void pane_view::_001OnSize(::message::message * pmessage)
   {
      pmessage->previous();

   }


   bool pane_view::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {
      switch(pimpactdata->m_id)
      {
      case CONTEXT_MENU_IMPACT:
      {

         auto pdata = Session.filemanager("filemanager::list");

         pdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;
         pdata->m_iIconSize = 16;
         pdata->m_bListText = true;
         pdata->m_bListSelection = false;
         pdata->m_datakey = "winactionarea_menu";
         pdata->m_pcallback = this;
         pdata->m_strXmlPopup = "matter://filemanager\\file_popup.xml";

         bool bOk = pdata->open(get_context_application(), Context.dir().appdata() / "command/menu", ::source_system);

         if(bOk && ::is_set(pdata->m_pdocument))
         {

            //pdocument->browse();

            ////pdocument->Initialize(true);
            ////pdocument->update_all_views(id_unknown); // 1234);
            ////pdocument->update_all_views(id_unknown); //123458);
            __pointer(::user::impact) pview = pdata->m_pdocument->get_view();

            if(pview != nullptr)
            {
               __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
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
         __pointer(::user::impact) pview = create_view < primary_view > ();
         if(pview != nullptr)
         {
            pimpactdata->m_pdocument = get_document();
            pimpactdata->m_puserinteraction = pview;
            pimpactdata->m_iExtendOnParent = 0;
         }
      }
      break;
//      case FILEMANAGER_IMPACT:
//      {
//         __pointer(::filemanager::document) pdocument = User.filemanager()->open_child(false, true);
//         if(pdocument != nullptr)
//         {
//            pdocument->filemanager_data()->m_datakey = "winactionarea_filemanager";
//            pdocument->Initialize(true);
//            pdocument->update_all_views(id_unknown); //1234);
//            pdocument->update_all_views(id_unknown); //123458);
//            __pointer(::user::impact) pview = pdocument->get_view();
//            if(pview != nullptr)
//            {
//               __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
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

         auto pdata = Session.filemanager("filemanager::list");

         pdata->m_puserinteractionParent = pimpactdata->m_pplaceholder;
         pdata->m_iIconSize = 48;
         pdata->m_bListText = false;
         pdata->m_bListSelection = false;
         pdata->m_datakey = "winactionarea_3-action-launch";
         pdata->m_pcallback = this;
         //pdata->m_strFilePopup = "filemanager\\file_popup.xml";

         //auto pdocument = pdata->browse(Context.dir().appdata() / "co
         pdata->open(get_context_application(), Context.dir().appdata() / "command\\3-action-launch", ::source_system);

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
            __pointer(::user::impact) pview = pdata->m_pdocument->get_view();

            //pdocument->FileManagerBrowse();

            if(pview != nullptr)
            {
               __pointer(::user::frame_window) pframe =  (pview->GetParentFrame());
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
         __pointer(::user::document) pdocument = Application.create_form(this, this);
         if(pdocument == nullptr)
            return;
         ::user::impact_data * pimpactdata = new ::user::impact_data;
         __pointer(::user::impact) pview = pdocument->get_typed_view < ::user::impact > ();
         auto pupdate = new_update();
         pupdate->m_actioncontext = ::source_system;
         pupdate->m_id = id_browse;
         pupdate->value(id_form) = "filemanager\\replace_name_in_file_system.xhtml";
         pdocument->update_all_views(pupdate);

         pupdate->m_id = id_get_form_view;
         pdocument->update_all_views(pupdate);

         pupdate->m_id = id_after_browse;
         pdocument->update_all_views(pupdate);


         pimpactdata->m_puserinteraction = (pview->GetParentFrame());
//         __pointer(form_child_frame) pframe = (pimpactdata->m_puserinteraction);
         //pframe->m_iTabId = iId;
         pimpactdata->m_pdocument = pdocument;
      }
      break;
      default:
         ASSERT(FALSE);
         break;
      }

      pane_tab_view::on_create_impact(pimpactdata);

   }


   void pane_view::_001OnMenuMessage(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      set_cur_tab_by_id(m_pimpactdataOld->m_id);

   }


   void pane_view::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &pane_view::_001OnCreate);
      IGUI_MSG_LINK(WM_SIZE, pchannel, this, &pane_view::_001OnSize);
      IGUI_MSG_LINK(WM_USER + 1122, this, this, &pane_view::_001OnMenuMessage);

   }


   void pane_view::rotate()
   {

      id idNew;

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

      set_cur_tab_by_id(idNew);

   }


   void pane_view::on_control_event(::user::control_event * pevent)
   {

      ::prompt::form_callback::on_control_event(pevent);

      if(pevent->m_bRet)
      {

         return;

      }

      ::userex::pane_tab_view::on_control_event(pevent);

   }


   void pane_view::OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if(itema.get_size() > 0)
      {

         //iptr i = 0;

         Context.os().file_open(this, itema[0]->m_filepathFinal, "", itema[0]->m_filepathFinal.folder());

         //string str;

         //str.Format("%d", i);

         ////Application.message_box(str);

         //if(i == ERROR_FILE_NOT_FOUND)
         //{

         //}

      }

      //GetParentFrame()->hide();
      
      GetParentFrame()->display();

   }


} // namespace prompt


