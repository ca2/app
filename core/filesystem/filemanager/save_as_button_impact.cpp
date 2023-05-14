// From save_as_name_impact by camilo on 2023-05-05 19:09 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "save_as_button_impact.h"
#include "save_as_edit_impact.h"
#include "save_as_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
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


   bool save_as_button_impact::on_click(::item * pitem)
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


   void save_as_button_impact::save_document(::file::path path)
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


   void save_as_button_impact::cancel_save_document()
   {

      throw ::exception(todo, "new_action?? (->new_subject)");

      //auto ptopic = new_action(topic(id_topic_cancel));

      //get_document()->update_all_impacts(ptopic);

   }



} // namespace filemanager



