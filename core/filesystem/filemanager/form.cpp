#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "aura/update.h"



namespace filemanager
{


   form::form()
   {

   }


   void form::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::e_event_click)
      {

         if(pevent->m_puserinteraction->m_id == "lfs")
         {

            auto psubject = subject(BROWSE_ID);

            psubject->payload(id_form) = "filemanager_add_location_lfs.xhtml";

            get_document()->update_all_views(psubject);

            auto pinteraction = get_child_by_name("lfs");

            pinteraction->_001SetText(filemanager_item()->m_filepathUser,::e_source_user);

         }
         else if(pevent->m_puserinteraction->m_id == "ftp")
         {

            auto psubject = subject(id_browse);

            psubject->payload(id_form) = "filemanager_add_location_ftp.xhtml";

            get_document()->update_all_views(psubject);

         }
         else if(pevent->m_puserinteraction->m_id == "submit")
         {
            if(m_strPath == "filemanager_add_location_lfs.xhtml")
            {
               
               string_array stra;

               auto papplication = get_application();

               papplication->data_get(filemanager_data()->m_dataidStatic,stra);

               auto pinteraction = get_child_by_name("lfs");

               string str;

               pinteraction->_001GetText(str);

               stra.add_unique(str);
               papplication->data_set(filemanager_data()->m_dataidStatic,stra);

            }
            else if(m_strPath == "filemanager_add_location_ftp.xhtml")
            {
            }
            else if(m_idCreator == "replace_name")
            {

               auto psubject = subject(id_replace_name);

               auto pinteraction = get_child_by_name("find");

               pinteraction->_001GetText(psubject->payload(id_find));

               pinteraction = get_child_by_name("replace");

               pinteraction->_001GetText(psubject->payload(id_replace));

               auto pdocument =  filemanager_document();

               pdocument->update_all_views(psubject);

            }
            else if (m_idCreator == "new_folder")
            {
               
               auto psubject = subject(id_new_folder);

               auto pinteraction = get_child_by_name("name");

               pinteraction->_001GetText(psubject->payload(id_text));

               auto pdocument = filemanager_document();

               pdocument->update_all_views(psubject);

            }

         }

      }

   }


} // namespace filemanager




