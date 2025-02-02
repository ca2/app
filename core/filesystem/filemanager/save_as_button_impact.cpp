// From save_as_name_impact by camilo on 2023-05-05 19:09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "save_as_button_impact.h"
#include "save_as_edit_impact.h"
#include "save_as_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/platform/application.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/file_system.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/micro/user.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/filesystem/fs/set.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame_interaction.h"


namespace filemanager
{


   save_as_button_impact::save_as_button_impact()
   {

      m_bEmptyAreaIsClientArea = true;

   }


   save_as_button_impact::~save_as_button_impact()
   {


   }


   void save_as_button_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::button::install_message_routing(pchannel);

   }


   void save_as_button_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

   }


   bool save_as_button_impact::on_click(::item * pitem, ::user::mouse * pmouse)
   {

      ASSERT(filemanager_data()->m_pdocumentTopic != nullptr);

      ::file::path strTitle;

      ::file::path strPath;

      strTitle = get_typed_parent<save_as_impact>()->m_pedit->as_text();

      // auto pcontext = get_context();

      if (strTitle.folder().has_character() && filemanager_data()->fs_data()->is_dir(strTitle.folder()))
      {

         strPath = strTitle;

      }
      else if (filemanager_data()->fs_data()->is_dir(filemanager_item()->final_path()))
      {

         strPath = filemanager_item()->user_path() / strTitle;

      }
      else if (strTitle.has_character())
      {

         strPath = filemanager_item()->user_path() / strTitle;

      }
      else
      {

         strPath = filemanager_item()->final_path();

      }

      if (filemanager_data()->m_emode == ::userfs::e_mode_import)
      {

         filemanager_data()->m_pdocumentTopic->open_document(strPath);

      }
      else
      {

         bool bSave = !directory()->is(strPath);

         if (bSave)
         {

            if (filemanager_data()->fs_data()->file_system()->exists(strPath))
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

               auto pmessagebox = __initialize_new ::message_box("Do you want to replace the existing file " + strPath + "?", nullptr, e_message_box_yes_no);

               pmessagebox->async()
                  << [this, pmessagebox, strPath]()
                     {

                        if (pmessagebox->m_payloadResult == e_dialog_result_yes)
                        {

                           save_document(strPath);

                        }
                        else
                        {

                           cancel_save_document();

                        }


                     };

               //pmessagebox->async();

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


   void save_as_button_impact::save_document(::file::path path)
   {

      //auto pupdate = new_update();

      auto pdocumentTopic = filemanager_data()->m_pdocumentTopic;

      if (pdocumentTopic->on_filemanager_save(filemanager_document(), path))
      {

         //ptopic->id() = id_topic_saved;

         //pupdate->m_pfileitem = __allocate ::file::item(path, path);

      }
      else
      {

         //output_error_message("Failed to save document");

         //ptopic->id() = id_topic_save_failed;

      }

   }


   void save_as_button_impact::cancel_save_document()
   {

      throw ::exception(todo, "new_action?? (->new_subject)");

      //auto ptopic = new_action(topic(id_topic_cancel));

      //get_document()->update_all_impacts(ptopic);

   }



} // namespace filemanager



