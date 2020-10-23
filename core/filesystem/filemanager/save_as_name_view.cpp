#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"



namespace filemanager
{


   save_as_edit_view::save_as_edit_view()
   {

      m_bVoidSync = false;

   }


   void save_as_edit_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager::impact::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);

   }




   void save_as_edit_view::browse_sync(const ::action_context & context)
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


   void save_as_edit_view::_001OnAfterChangeText(const ::action_context & context)
   {

      string str;

      _001GetText(str);

      if (Context.dir().is(str))
      {

         filemanager_document()->browse(str, context + ::source_sync);

      }
      else if (str.find("/") >= 0 || str.find("\\") >= 0)
      {

         ::file::path strName = str;

         while (true)
         {

            strName = strName.folder();

            if (Context.dir().is(strName))
            {

               if (filemanager_item()->m_filepathUser != strName)
               {

                  filemanager_document()->browse(strName, context + ::source_sync);

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


   void save_as_edit_view::on_apply(::action * paction)
   {

      ::user::impact::on_apply(paction);

      if (paction->id() == INITIALIZE_ID && paction->m_puserinteraction == this)
      {
         //            filemanager_document() = pupdate->filemanager_document();
         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
         AddClient(this);
         SetDataInterface(&m_datainterface);
         AddClient(&m_datainterface);
         string str;
         str.Format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
         if(filemanager_data()->m_bTransparentBackground)
         {
         ::user::list::m_etranslucency = ::user::list::translucency_present;
         }
         DISetSection(str);
         _001UpdateColumns();*/
      }
      else if (paction->id() == FILTER_ID)
      {
         /*if(paction->value(id_filter).is_empty())
         {
         FilterClose();
         }
         else
         {
         FilterBegin();
         Filter1(paction->value(id_filter));
         FilterApply();
         }*/
      }

   }


   save_as_button::save_as_button()
   {

   }

   void save_as_button::install_message_routing(::channel * pchannel)
   {

      ::filemanager::impact::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void save_as_button::on_apply(::action * paction)
   {

      ::filemanager::impact::on_apply(paction);

   }


   bool save_as_button::on_click(const ::user::item & item)
   {


      ASSERT(filemanager_data()->m_pdocumentTopic != nullptr);

      ::file::path strTitle;

      ::file::path strPath;

      GetTypedParent<save_as_view>()->m_pedit->_001GetText(strTitle);

      if (strTitle.folder().has_char() && filemanager_document()->fs_data()->is_dir(strTitle.folder()))
      {

         strPath = strTitle;

      }
      else if (filemanager_document()->fs_data()->is_dir(filemanager_item()->m_filepathFinal))
      {

         strPath = filemanager_item()->m_filepathUser / strTitle;

      }
      else if (strTitle.has_char())
      {

         strPath = filemanager_item()->m_filepathUser / strTitle;

      }
      else
      {

         strPath = filemanager_item()->m_filepathUser;

      }

      if (filemanager_document()->m_emode == ::userfs::mode_import)
      {

         filemanager_data()->m_pdocumentTopic->open_document(strPath);

      }
      else
      {

         bool bSave = !Context.dir().is(strPath);

         if (bSave)
         {

            if (filemanager_document()->fs_data()->file_exists(strPath))
            {

               auto pfuture = __future([this, strPath](const ::var& var)
                  {

                     if (var == "yes")
                     {

                        save_document(strPath);

                     }
                     else
                     {

                        cancel_save_document();

                     }

                  });

               message_box("Do you want to replace the existing file " + strPath + "?", nullptr, message_box_yes_no, pfuture);

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

      if (filemanager_data()->m_pdocumentTopic->on_filemanager_save(filemanager_document(), path))
      {

         //paction->id() = id_topic_saved;

         //pupdate->m_pfileitem = __new(::file::item(path, path));

      }
      else
      {

         //message_box("Failed to save document");

         //paction->id() = id_topic_save_failed;

      }

   }


   void save_as_button::cancel_save_document()
   {

      auto paction = new_action(update(id_topic_cancel));

      get_document()->update_all_views(paction);

   }


   void save_as_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager::impact::install_message_routing(pchannel);
      ::user::split_view::install_message_routing(pchannel);

   }


   save_as_view::save_as_view()
   {



   }


   void save_as_view::on_apply(::action * paction)
   {

      ::user::impact::on_apply(paction);

      ////__update(::update)
      {

         if (paction->id() == id_topic_saved)
         {

            if (GetTopLevelFrame()->m_bModal)
            {

               GetTopLevelFrame()->EndModalLoop("yes");

            }

         }
         else if (paction->id() == id_topic_save_failed)
         {

            if (GetTopLevelFrame()->m_bModal)
            {

               GetTopLevelFrame()->EndModalLoop("no");

            }

         }
         else if (paction->m_puserinteraction == this && paction->id() == id_initialize)
         {
            //            filemanager_document() = pupdate->filemanager_document();
            /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                        AddClient(this);
                        SetDataInterface(&m_datainterface);
                        AddClient(&m_datainterface);
                        string str;
                        str.Format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                        if(filemanager_data()->m_bTransparentBackground)
                        {
                        ::user::list::m_etranslucency = ::user::list::translucency_present;
                        }
                        DISetSection(str);
                        _001UpdateColumns();*/
         }
         else if (paction->id() == id_filter)
         {
            /*if(paction->value(id_filter).is_empty())
            {
            FilterClose();
            }
            else
            {
            FilterBegin();
            Filter1(paction->value(id_filter));
            FilterApply();
            }*/
         }

      }

   }


   void save_as_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.8);

      initialize_split_layout();

      m_pedit = create_pane_view < save_as_edit_view >(0);

      if (!m_pedit)
      {

         message_box("Could not create file list ::user::impact");

      }

      m_pbutton = create_pane_view < save_as_button >(1);

      m_pbutton->set_window_text("Save");

   }


} // namespace filemanager



