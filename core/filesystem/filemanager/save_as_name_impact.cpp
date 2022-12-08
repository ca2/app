#include "framework.h"
#include "save_as_name_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
////#include "acme/exception/exception.h"
#include "acme/platform/context.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/nano/nano.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame.h"


namespace filemanager
{


   save_as_edit_impact::save_as_edit_impact()
   {

      m_bVoidSync = false;

   }


   void save_as_edit_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);

   }




   void save_as_edit_impact::browse_sync(const ::action_context & context)
   {

      if (m_bVoidSync)
      {

         return;

      }

      string strText;

      _001GetText(strText);

      if (strText != filemanager_data()->m_pdocument->m_strTopic.title())
      {

         _001SetText(filemanager_data()->m_pdocument->m_strTopic.title(), context);

      }

   }


   void save_as_edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      string str;

      _001GetText(str);

      auto pcontext = get_context();

      if (dir()->is(str))
      {

         filemanager_document()->browse(str, context + ::e_source_sync);

      }
      else if (str.find("/") >= 0 || str.find("\\") >= 0)
      {

         ::file::path strName = str;

         while (true)
         {

            strName = strName.folder();

            if (dir()->is(strName))
            {

               if (filemanager_item()->user_path() != strName)
               {

                  filemanager_document()->browse(strName, context + ::e_source_sync);

               }

               break;

            }

            if (strName.is_empty())
            {

               break;

            }

         }

      }

      if (filemanager_document() != nullptr)
      {

         filemanager_document()->m_strTopic = str;

      }

   }


   void save_as_edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == ID_INITIALIZE && ptopic->m_puserelement == this)
      {
         //            filemanager_document() = pupdate->filemanager_document();
         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
         AddClient(this);
         SetDataInterface(&m_datainterface);
         AddClient(&m_datainterface);
         string str;
         str.format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
         if(filemanager_data()->m_bTransparentBackground)
         {
         ::user::list::m_etranslucency = ::user::list::e_translucency_present;
         }
         DISetSection(str);
         _001UpdateColumns();*/
      }
      else if (ptopic->m_atom == ID_FILTER)
      {
         /*if(ptopic->payload(id_filter).is_empty())
         {
         FilterClose();
         }
         else
         {
         FilterBegin();
         Filter1(ptopic->payload(id_filter));
         FilterApply();
         }*/
      }

   }


   save_as_button::save_as_button()
   {

   }

   void save_as_button::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void save_as_button::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

   }


   bool save_as_button::on_click(::item * pitem)
   {


      ASSERT(filemanager_data()->m_pdocumentTopic != nullptr);

      ::file::path strTitle;

      ::file::path strPath;

      get_typed_parent<save_as_impact>()->m_pedit->_001GetText(strTitle);

      auto pcontext = get_context();

      if (strTitle.folder().has_char() && filemanager_document()->fs_data()->is_dir(strTitle.folder()))
      {

         strPath = strTitle;

      }
      else if (filemanager_document()->fs_data()->is_dir(filemanager_item()->final_path()))
      {

         strPath = filemanager_item()->user_path() / strTitle;

      }
      else if (strTitle.has_char())
      {

         strPath = filemanager_item()->user_path() / strTitle;

      }
      else
      {

         strPath = filemanager_item()->final_path();

      }

      if (filemanager_document()->m_emode == ::userfs::e_mode_import)
      {

         filemanager_data()->m_pdocumentTopic->open_document(strPath);

      }
      else
      {

         bool bSave = !dir()->is(strPath);

         if (bSave)
         {

            if (filemanager_document()->fs_data()->acmefile()->exists(strPath))
            {

               //auto pfuture = __process([this, strPath](const ::payload & payload)
               //   {

               //      if (payload == "yes")
               //      {

               //         save_document(strPath);

               //      }
               //      else
               //      {

               //         cancel_save_document();

               //      }

               //   });

               auto psequencer = nano()->message_box("Do you want to replace the existing file " + strPath + "?", nullptr, e_message_box_yes_no);

               psequencer->then([this, strPath](auto pconversation)
                     {

                        if (pconversation->m_payloadResult == e_dialog_result_yes)
                        {

                           save_document(strPath);

                        }
                        else
                        {

                           cancel_save_document();

                        }


                     });

               psequencer->do_asynchronously();

            }
            else
            {

               save_document(strPath);

            }

         }
         else
         {

            cancel_save_document();

         }

      }

      return true;

   }


   void save_as_button::save_document(::file::path path)
   {

      //auto pupdate = new_update();

      auto pdocumentTopic = filemanager_data()->m_pdocumentTopic;

      if (pdocumentTopic->on_filemanager_save(filemanager_document(), path))
      {

         //ptopic->m_atom = id_topic_saved;

         //pupdate->m_pfileitem = __new(::file::item(path, path));

      }
      else
      {

         //output_error_message("Failed to save document");

         //ptopic->m_atom = id_topic_save_failed;

      }

   }


   void save_as_button::cancel_save_document()
   {

      throw ::exception(todo, "new_action?? (->new_subject)");

      //auto ptopic = new_action(topic(id_topic_cancel));

      //get_document()->update_all_impacts(ptopic);

   }


   void save_as_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::split_impact::install_message_routing(pchannel);

   }


   save_as_impact::save_as_impact()
   {



   }


   void save_as_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      ////__update(::update)
      {

         if (ptopic->m_atom == id_topic_saved)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->EndModalLoop("yes");

            }

         }
         else if (ptopic->m_atom == id_topic_save_failed)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->EndModalLoop("no");

            }

         }
         else if (ptopic->m_puserelement == this && ptopic->m_atom == id_initialize)
         {
            //            filemanager_document() = pupdate->filemanager_document();
            /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                        AddClient(this);
                        SetDataInterface(&m_datainterface);
                        AddClient(&m_datainterface);
                        string str;
                        str.format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                        if(filemanager_data()->m_bTransparentBackground)
                        {
                        ::user::list::m_etranslucency = ::user::list::e_translucency_present;
                        }
                        DISetSection(str);
                        _001UpdateColumns();*/
         }
         else if (ptopic->m_atom == id_filter)
         {
            /*if(ptopic->payload(id_filter).is_empty())
            {
            FilterClose();
            }
            else
            {
            FilterBegin();
            Filter1(ptopic->payload(id_filter));
            FilterApply();
            }*/
         }

      }

   }


   void save_as_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.8);

      initialize_split_layout();

      m_pedit = create_pane_impact < save_as_edit_impact >(0);

      if (!m_pedit)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      m_pbutton = create_pane_impact < save_as_button >(1);

      m_pbutton->set_window_text("Save");

   }


} // namespace filemanager



