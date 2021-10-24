#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"



namespace filemanager
{


   form::form()
   {

   }


   void form::handle(::subject * psubject, ::context * pcontext)
   {

      if(psubject->m_id == ::e_subject_click)
      {

         if(psubject->user_interaction()->m_id == "lfs")
         {

            ::subject subject(BROWSE_ID);

            subject.payload(id_form) = "filemanager_add_location_lfs.xhtml";

            get_document()->update_all_views(&subject);

            auto pinteraction = get_child_by_name("lfs");

            pinteraction->_001SetText(filemanager_item()->m_filepathUser,::e_source_user);

         }
         else if(psubject->user_interaction()->m_id == "ftp")
         {

            ::subject subject(id_browse);

            subject.payload(id_form) = "filemanager_add_location_ftp.xhtml";

            get_document()->update_all_views(&subject);

         }
         else if(psubject->user_interaction()->m_id == "submit")
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

               ::subject subject(id_replace_name);

               auto pinteraction = get_child_by_name("find");

               pinteraction->_001GetText(subject.payload(id_find).as_string());

               pinteraction = get_child_by_name("replace");

               pinteraction->_001GetText(subject.payload(id_replace).as_string());

               auto pdocument =  filemanager_document();

               pdocument->update_all_views(&subject);

            }
            else if (m_idCreator == "new_folder")
            {
               
               ::subject subject(id_new_folder);

               auto pinteraction = get_child_by_name("name");

               pinteraction->_001GetText(subject.payload(id_text).as_string());

               auto pdocument = filemanager_document();

               pdocument->update_all_views(&subject);

            }

         }

      }

   }


} // namespace filemanager




