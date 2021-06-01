#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"


filemanager_impact::filemanager_impact()
{

   m_bEditConnectInit = false;

}


filemanager_impact::~filemanager_impact()
{

}


void filemanager_impact::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);

   connect_command_probe("edit_paste",&filemanager_impact::_001OnUpdateEditPaste);

   connect_command("edit_paste",&filemanager_impact::_001OnEditPaste);

   MESSAGE_LINK(WM_APP + 1024,pchannel,this,&filemanager_impact::_001OnOperationDocMessage);

}



//::filemanager_impact * filemanager_impact::this_view()
//{
//
//   return dynamic_cast <::filemanager_impact *> (this);
//
//}


::file::item * filemanager_impact::filemanager_item()
{

   auto pdocument = filemanager_document();

   if (!pdocument)
   {

      return nullptr;

   }

   return pdocument->filemanager_item();

}


__pointer(::fs::data) filemanager_impact::fs_data()
{

   return filemanager_document()->fs_data();

}


::file::path filemanager_impact::filemanager_path()
{

   return filemanager_item()->m_filepathUser;

}


::filemanager::document * filemanager_impact::filemanager_document()
{

   return dynamic_cast <::filemanager::document * > (get_document());

}


::filemanager::data * filemanager_impact::filemanager_data()
{

   return  filemanager_document()->filemanager_data();

}


void filemanager_impact::_001Refresh()
{

   filemanager_document()->browse(filemanager_item(),::e_source_sync);

}


void filemanager_impact::browse_sync(const ::action_context & context)
{

   UNREFERENCED_PARAMETER(context);

}


void filemanager_impact::knowledge(const string & pathUser, const ::action_context & context)
{

   UNREFERENCED_PARAMETER(pathUser);
   UNREFERENCED_PARAMETER(context);

}


void filemanager_impact::_001OnUpdateEditPaste(::message::message * pmessage)
{

   __pointer(::message::command) pcommand(pmessage);

   auto psession = get_session();
   
   auto pcopydesk = psession->copydesk();
   
   bool bHasFile = pcopydesk->has_filea();
         
   pcommand->enable(bHasFile);

   pmessage->m_bRet = true;

}


void filemanager_impact::_001OnEditPaste(::message::message * pmessage)
{

   UNREFERENCED_PARAMETER(pmessage);

   ::file::listing listing;

   ::user::copydesk::e_op eop;

   auto psession = get_session();
   
   auto pcopydesk = psession->copydesk();
   
   bool bOk = pcopydesk->get_filea(listing, eop);

   if(!bOk || listing.is_empty())
   {

      pmessage->m_bRet = true;

      return;

   }

   string strDir;

   strDir = filemanager_item()->m_filepathUser;

   auto pview  = this;

   if(pview == nullptr)
   {

      return;

   }

   auto ptabview = GetTypedParent <::filemanager::tab_view >();

   if(ptabview != nullptr)
   {

      bool bDeleteOriginOnSuccessfulCopy = eop == ::user::copydesk::op_cut;

      ptabview->filemanager_document()->get_operation_doc(true)->m_thread.queue_copy(listing, strDir, nullptr, true, false, bDeleteOriginOnSuccessfulCopy, this, WM_APP + 1024, 4096);

      ptabview->filemanager_document()->get_operation_doc(true)->m_thread.kick();

   }

   pmessage->m_bRet =true;

}


void filemanager_impact::_001OnOperationDocMessage(::message::message * pmessage)
{

   __pointer(::user::message) pusermessage(pmessage);

   if(pusermessage->m_wparam == 4096)
   {

      if(pusermessage->m_lparam == 0)
      {

         _001Refresh();

      }

   }

}



void filemanager_impact::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
{

   ::user::impact::on_subject(psubject, pcontext);

   if (psubject->id() == INITIALIZE_ID)
   {

      if (filemanager_document() == psubject->cast < ::user::document >(DOCUMENT_ID))
      {

         __pointer(::database::client) pclient = get_parent_frame();

         if (pclient != nullptr && !pclient->m_id.to_string().contains("::frame"))
         {

            string str;

            str.Format("frame(%s)", filemanager_data()->m_id.str().c_str());

            pclient->set_data_key_modifier(str);

         }

      }

   }
   else if (psubject->id() == SYNCHRONIZE_PATH_ID)
   {

      __pointer(::core::application) papplication = get_application();

      if (psubject->m_pfileitem &&
         (::is_set(filemanager_item())
            && papplication->is_equal_file_path(psubject->m_pfileitem->m_filepathFinal, filemanager_item()->m_filepathFinal)))
      {

#define DBG_LOOP  1
         for (index i = 0; i < DBG_LOOP; i++)
         {

            browse_sync(psubject->m_actioncontext + ::e_source_sync);

         }

      }
      else
      {

         knowledge(psubject->m_pfileitem->m_filepathUser, psubject->m_actioncontext + ::e_source_sync);

      }

      set_need_redraw();

   }

}




