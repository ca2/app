#include "framework.h"
#include "form.h"
#include "document.h"
#include "data.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/file/item.h"
#include "acme/prototype/collection/_array_binary_stream.h"
#include "apex/database/_binary_stream.h"
#include "core/platform/application.h"


namespace filemanager
{


   form::form()
   {

   }


   void form::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      if(ptopic->id() == ::id_click)
      {

         if(ptopic->user_interaction()->id() == "lfs")
         {

            auto ptopic = create_topic(id_browse);

            ptopic->payload(id_form) = "filemanager_add_location_lfs.xhtml";

            ::user::form_impact::get_document()->update_all_impacts(ptopic);

            auto pinteraction = get_child_by_name("lfs");

            //pinteraction->set_text(filemanager_item()->user_path(), ::e_source_user);
            pinteraction->set_text(filemanager_item()->user_path(), ::e_source_user);

         }
         else if(ptopic->user_interaction()->id() == "ftp")
         {

            auto ptopic = create_topic(id_browse);

            ptopic->payload(id_form) = "filemanager_add_location_ftp.xhtml";

            ::user::form_impact::get_document()->update_all_impacts(ptopic);

         }
         //else if(ptopic->user_interaction()->id() == "submit")
         //{

         //   if(m_strPath == "filemanager_add_location_lfs.xhtml")
         //   {
         //      
         //      string_array_base stra;

         //      auto papp = ::user::form_impact::get_app();

         //      papp->datastream()->get(get_document()->m_strDataKeyStatic,stra);

         //      auto pinteraction = get_child_by_name("lfs");

         //      string str;

         //      pinteraction->get_text(str);

         //      stra.add_unique(str);
         //      papp->datastream()->set(get_document()->m_strDataKeyStatic,stra);

         //   }
         //   else if(m_strPath == "filemanager_add_location_ftp.xhtml")
         //   {
         //   }
         //   else if(m_atomCreator == "replace_name")
         //   {

         //      auto ptopic = create_topic(id_replace_name);

         //      auto pinteraction = get_child_by_name("find");

         //      pinteraction->get_text(ptopic->payload(id_find).string_reference());

         //      pinteraction = get_child_by_name("replace");

         //      pinteraction->get_text(ptopic->payload(id_replace).string_reference());

         //      auto pdocument =  filemanager_document();

         //      pdocument->update_all_impacts(ptopic);

         //   }
         //   else if (m_atomCreator == "new_folder")
         //   {
         //      
         //      auto ptopic = create_topic(id_new_folder);

         //      auto pinteraction = get_child_by_name("name");

         //      pinteraction->get_text(__reference(ptopic->payload(id_text)));

         //      auto pdocument = filemanager_document();

         //      pdocument->update_all_impacts(ptopic);

         //   }

         //}

      }

   }


} // namespace filemanager




