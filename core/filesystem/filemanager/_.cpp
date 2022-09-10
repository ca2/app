#include "framework.h"
#include "aura/graphics/image/icon.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "core/user/user/user.h"
#include "core/user/userex/pane_tab_impact.h"
#include "document.h"
#include "data.h"
#include "aura/user/user/frame.h"


namespace core
{


   bool user::do_prompt_file_name(::payload & payloadFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument, const ::atom & atomFileManager)
   {

      if (::is_set(pdocument))
      {

         if (pdocument->get_impact() != nullptr)
         {

            auto ppanetabview = pdocument->get_impact()->get_typed_parent < ::userex::pane_tab_impact >();

            if (ppanetabview)
            {

               ppanetabview = pdocument->get_impact()->get_typed_parent < ::userex::pane_tab_impact >();

               auto pfilemanagerdocument = ppanetabview->filemanager_document(atomFileManager);

               pfilemanagerdocument->FileManagerSaveAs(pdocument);

               if (ppanetabview->parent_frame()->RunModalLoop() != "yes")
               {

                  return false;

               }

               payloadFile = ppanetabview->filemanager_document(atomFileManager)->m_strTopic;

               return true;

            }

         }

      }

      return filemanager(atomFileManager)->do_prompt_file_name(payloadFile, strTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

   }


} // namespace aura



