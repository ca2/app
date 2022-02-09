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


   void form::handle(::topic * ptopic, ::context * pcontext)
   {

      if(ptopic->m_atom == ::id_click)
      {

         if(ptopic->user_interaction()->m_atom == "lfs")
         {

            auto ptopic = __new(::topic(BROWSE_ID));

            ptopic->_extended_topic()->payload(id_form) = "filemanager_add_location_lfs.xhtml";

            get_document()->update_all_views(ptopic);

            auto pinteraction = get_child_by_name("lfs");

            pinteraction->_001SetText(filemanager_item()->m_filepathUser,::e_source_user);

         }
         else if(ptopic->user_interaction()->m_atom == "ftp")
         {

            auto ptopic = __new(::topic(id_browse));

            ptopic->_extended_topic()->payload(id_form) = "filemanager_add_location_ftp.xhtml";

            get_document()->update_all_views(ptopic);

         }
         else if(ptopic->user_interaction()->m_atom == "submit")
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
            else if(m_atomCreator == "replace_name")
            {

               auto ptopic = __new(::topic(id_replace_name));

               auto pinteraction = get_child_by_name("find");

               pinteraction->_001GetText(ptopic->_extended_topic()->payload(id_find).as_string());

               pinteraction = get_child_by_name("replace");

               pinteraction->_001GetText(ptopic->_extended_topic()->payload(id_replace).as_string());

               auto pdocument =  filemanager_document();

               pdocument->update_all_views(ptopic);

            }
            else if (m_atomCreator == "new_folder")
            {
               
               auto ptopic = __new(::topic(id_new_folder));

               auto pinteraction = get_child_by_name("name");

               pinteraction->_001GetText(ptopic->_extended_topic()->payload(id_text).as_string());

               auto pdocument = filemanager_document();

               pdocument->update_all_views(ptopic);

            }

         }

      }

   }


} // namespace filemanager




