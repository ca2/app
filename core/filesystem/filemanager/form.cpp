﻿#include "framework.h"
#include "form.h"
#include "document.h"
#include "data.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/primitive/collection/_array_binary_stream.h"
#include "apex/database/_binary_stream.h"
#include "core/platform/application.h"


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

            auto ptopic = create_topic(ID_BROWSE);

            ptopic->payload(ID_FORM) = "filemanager_add_location_lfs.xhtml";

            ::user::form_impact::get_document()->update_all_impacts(ptopic);

            auto pinteraction = get_child_by_name("lfs");

            pinteraction->_001SetText(filemanager_item()->user_path(), ::e_source_user);

         }
         else if(ptopic->user_interaction()->m_atom == "ftp")
         {

            auto ptopic = create_topic(ID_BROWSE);

            ptopic->payload(ID_FORM) = "filemanager_add_location_ftp.xhtml";

            ::user::form_impact::get_document()->update_all_impacts(ptopic);

         }
         else if(ptopic->user_interaction()->m_atom == "submit")
         {

            if(m_strPath == "filemanager_add_location_lfs.xhtml")
            {
               
               string_array stra;

               auto papp = ::user::form_impact::get_app();

               papp->datastream()->get(filemanager_data()->m_dataidStatic,stra);

               auto pinteraction = get_child_by_name("lfs");

               string str;

               pinteraction->_001GetText(str);

               stra.add_unique(str);
               papp->datastream()->set(filemanager_data()->m_dataidStatic,stra);

            }
            else if(m_strPath == "filemanager_add_location_ftp.xhtml")
            {
            }
            else if(m_atomCreator == "replace_name")
            {

               auto ptopic = create_topic(id_replace_name);

               auto pinteraction = get_child_by_name("find");

               pinteraction->_001GetText(ptopic->payload(id_find).string_reference());

               pinteraction = get_child_by_name("replace");

               pinteraction->_001GetText(ptopic->payload(id_replace).string_reference());

               auto pdocument =  filemanager_document();

               pdocument->update_all_impacts(ptopic);

            }
            else if (m_atomCreator == "new_folder")
            {
               
               auto ptopic = create_topic(id_new_folder);

               auto pinteraction = get_child_by_name("name");

               pinteraction->_001GetText(__reference(ptopic->payload(id_text)));

               auto pdocument = filemanager_document();

               pdocument->update_all_impacts(ptopic);

            }

         }

      }

   }


} // namespace filemanager




