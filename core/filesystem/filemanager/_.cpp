#include "framework.h"
#include "aura/graphics/draw2d/icon.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif

#include "aura/update.h"


namespace core
{


   bool user::do_prompt_file_name(::payload & payloadFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      if (::is_set(pdocument))
      {

         if (pdocument->get_view() != nullptr)
         {

            auto ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view >();

            if (ppanetabview)
            {

               ppanetabview = pdocument->get_view()->GetTypedParent < ::userex::pane_tab_view >();

               ppanetabview->FileManagerSaveAs(pdocument);

               if (ppanetabview->get_parent_frame()->RunModalLoop() != "yes")
               {

                  return false;

               }

               payloadFile = ppanetabview->filemanager_document()->m_strTopic;

               return true;

            }

         }

      }

      return filemanager(impact_filemanager_main)->do_prompt_file_name(payloadFile, strTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

   }


} // namespace aura



