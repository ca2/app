// Created by camilo on 2023-11-16 03:44 <3ThomasBorregaardSorensen!!
// Refactor and Tidy core filemanager component a bit Fix ca2/app#61
#include "framework.h"
#include "document.h"


namespace filemanager
{


   namespace folder
   {


      document::document()
      {

         //m_bInitialized = false;

         //m_filewatchid = -1;

         //m_bFullBrowse = false;

         ////m_pfilewatcherlistenerthread = nullptr;

         ////command_signalid atom;

         //add_command_prober("levelup", { this,  &document::_001OnUpdateLevelUp });
         //add_command_handler("levelup", { this,  &document::_001OnLevelUp });
         //add_command_prober("add_location", { this,  &document::_001OnUpdateAddLocation });
         //add_command_handler("add_location", { this,  &document::_001OnAddLocation });
         //add_command_prober("replace_text_in_file_system", { this,  &document::_001OnUpdateReplaceText });
         //add_command_handler("replace_text_in_file_system", { this,  &document::_001OnReplaceText });
         //add_command_prober("edit_paste", { this,  &document::_001OnUpdateEditPaste });
         //add_command_handler("edit_paste", { this,  &document::_001OnEditPaste });
         //add_command_prober("file_save", { this,  &document::_001OnUpdateFileSaveAs });
         //add_command_handler("file_save", { this,  &document::_001OnFileSaveAs });
         //add_command_prober("cancel", { this,  &document::_001OnUpdateEditPaste });
         //add_command_handler("cancel", { this,  &document::_001OnEditPaste });
         //add_command_prober("new_manager", { this,  &document::_001OnUpdateNewManager });
         //add_command_handler("new_manager", { this,  &document::_001OnNewManager });
         //add_command_prober("del_manager", { this,  &document::_001OnUpdateDelManager });
         //add_command_handler("del_manager", { this,  &document::_001OnDelManager });
         //add_command_prober("new_folder", { this,  &document::_001OnUpdateNewFolder });
         //add_command_handler("new_folder", { this,  &document::_001OnNewFolder });

      }


      document::~document()
      {

      }




      bool document::on_new_document()
      {

         if (!::user::document::on_new_document())
         {

            return false;

         }

         return true;

      }



      bool document::on_open_document(const ::payload & payloadFile)
      {

         return true;

      }


   } // namespace folder


} // namespace filemanager



