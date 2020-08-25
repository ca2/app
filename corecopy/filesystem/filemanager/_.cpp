#include "framework.h"
//#include "_filemanager.h"
#include "aura/update.h"



namespace core
{


   bool user::do_prompt_file_name(var & varFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      if (::is_set(pdocument))
      {

         if (pdocument->get_view() != nullptr)
         {

            auto ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view >();

            if(ppanetabview->is_set())


            ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view >();

            ppanetabview->FileManagerSaveAs(pdocument);

            if (ppanetabview->GetParentFrame()->RunModalLoop() != "yes")
            {

               return false;

            }

            varFile = ppanetabview->filemanager_document()->m_strTopic;

            return true;

         }

      }
      
      return User.filemanager(impact_filemanager_main)->do_prompt_file_name(varFile, strTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);
      
   }


} // namespace aura



