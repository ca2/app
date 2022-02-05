#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


filemanager_impact_base::filemanager_impact_base()
{

   m_bEditConnectInit = false;

}


filemanager_impact_base::~filemanager_impact_base()
{

}


void filemanager_impact_base::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);

   add_command_prober("edit_paste", this, &filemanager_impact_base::_001OnUpdateEditPaste);

   add_command_handler("edit_paste", this, &filemanager_impact_base::_001OnEditPaste);

   MESSAGE_LINK(WM_APP + 1024,pchannel,this,&filemanager_impact_base::_001OnOperationDocMessage);

}



//::filemanager_impact_base * filemanager_impact_base::this_view()
//{
//
//   return dynamic_cast <::filemanager_impact_base *> (this);
//
//}


::file::item * filemanager_impact_base::filemanager_item()
{

   auto pdocument = filemanager_document();

   if (!pdocument)
   {

      return nullptr;

   }

   return pdocument->filemanager_item();

}


__pointer(::fs::data) filemanager_impact_base::fs_data()
{

   return filemanager_document()->fs_data();

}


::file::path filemanager_impact_base::filemanager_path()
{

   return filemanager_item()->m_filepathUser;

}


::filemanager::document * filemanager_impact_base::filemanager_document()
{

   return dynamic_cast <::filemanager::document * > (get_document());

}


::filemanager::data * filemanager_impact_base::filemanager_data()
{

   return  filemanager_document()->filemanager_data();

}


void filemanager_impact_base::_001Refresh()
{

   filemanager_document()->browse(filemanager_item(),::e_source_sync);

}


void filemanager_impact_base::browse_sync(const ::action_context & context)
{

   __UNREFERENCED_PARAMETER(context);

}


void filemanager_impact_base::knowledge(const ::file::path & pathUser, const ::action_context & context)
{

   __UNREFERENCED_PARAMETER(pathUser);
   __UNREFERENCED_PARAMETER(context);

}


void filemanager_impact_base::_001OnUpdateEditPaste(::message::message * pmessage)
{

   __pointer(::message::command) pcommand(pmessage);

   auto pwindow = window();
   
   auto pcopydesk = pwindow->copydesk();
   
   bool bHasFile = pcopydesk->has_filea();
         
   pcommand->enable(bHasFile);

   pmessage->m_bRet = true;

}


void filemanager_impact_base::_001OnEditPaste(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   ::file::listing listing;

   ::user::copydesk::enum_op eop;

   auto pwindow = window();
   
   auto pcopydesk = pwindow->copydesk();
   
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

      bool bDeleteOriginOnSuccessfulCopy = eop == ::user::copydesk::e_op_cut;

      ptabview->filemanager_document()->get_operation_doc(true)->m_thread.queue_copy(listing, strDir, nullptr, true, false, bDeleteOriginOnSuccessfulCopy, this, WM_APP + 1024, 4096);

      ptabview->filemanager_document()->get_operation_doc(true)->m_thread.kick();

   }

   pmessage->m_bRet =true;

}


void filemanager_impact_base::_001OnOperationDocMessage(::message::message * pmessage)
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



void filemanager_impact_base::handle(::topic * ptopic, ::context * pcontext)
{

   ::user::impact::handle(ptopic, pcontext);

   if (ptopic->m_id == id_initialize)
   {

      if (filemanager_document() == ptopic->cast < ::user::document >(DOCUMENT_ID))
      {

         __pointer(::database::client) pclient = get_parent_frame();

         if (pclient != nullptr && !pclient->m_id.to_string().contains("::frame"))
         {

            string str;

            str.format("frame(%s)", filemanager_data()->m_id.str().c_str());

            pclient->set_data_key_modifier(str);

         }

      }

   }
   else if (ptopic->m_id == id_synchronize_path)
   {

      __pointer(::core::application) papplication = get_application();

      auto pfileitem = ptopic->m_pfileitem;

      auto bFileManagerItemSet = ::is_set(filemanager_item());

      bool bEqualFilePath = bFileManagerItemSet && papplication->is_equal_file_path(ptopic->m_pfileitem->m_filepathFinal, filemanager_item()->m_filepathFinal);

      if (pfileitem && (bFileManagerItemSet && bEqualFilePath))
      {

#define DBG_LOOP  1
         for (index i = 0; i < DBG_LOOP; i++)
         {

            browse_sync(ptopic->m_pextendedtopic->m_actioncontext + ::e_source_sync);

         }

      }
      else
      {

         knowledge(ptopic->m_pfileitem->m_filepathUser, ptopic->m_pextendedtopic->m_actioncontext + ::e_source_sync);

      }

      set_need_redraw();

   }

}




