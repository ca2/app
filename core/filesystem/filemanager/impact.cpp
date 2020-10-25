#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   impact::impact()
   {

      m_bEditConnectInit = false;

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      connect_command_probe("edit_paste",&impact::_001OnUpdateEditPaste);

      connect_command("edit_paste",&impact::_001OnEditPaste);

      MESSAGE_LINK(WM_APP + 1024,pchannel,this,&impact::_001OnOperationDocMessage);

   }



   ::user::impact * impact::this_view()
   {

      return dynamic_cast <::user::impact *> (this);

   }


   ::file::item * impact::filemanager_item()
   {

      auto pdocument = filemanager_document();

      if (!pdocument)
      {

         return nullptr;

      }

      return pdocument->filemanager_item();

   }


   __pointer(::fs::data) impact::fs_data()
   {

      return filemanager_document()->fs_data();

   }


   ::file::path impact::filemanager_path()
   {

      return filemanager_item()->m_filepathUser;

   }


   document * impact::filemanager_document()
   {

      return dynamic_cast < document * > (get_document());

   }


   data * impact::filemanager_data()
   {

      return  filemanager_document()->filemanager_data();

   }


   void impact::_001Refresh()
   {

      filemanager_document()->browse(filemanager_item(),::source_sync);

   }


   void impact::browse_sync(const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(context);

   }


   void impact::knowledge(const string & pathUser, const ::action_context & context)
   {

      UNREFERENCED_PARAMETER(pathUser);
      UNREFERENCED_PARAMETER(context);

   }


   void impact::_001OnUpdateEditPaste(::message::message * pmessage)
   {

      SCAST_PTR(::user::command,pcommand,pmessage);

      pcommand->enable(Session.copydesk().has_filea());

      pmessage->m_bRet = true;

   }


   void impact::_001OnEditPaste(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

      ::file::listing listing;

      ::user::copydesk::e_op eop;

      if(!Session.copydesk().get_filea(listing, eop) || listing.is_empty())
      {

         pmessage->m_bRet = true;

         return;

      }

      string strDir;

      strDir = filemanager_item()->m_filepathUser;

      ::user::impact * pview  = this_view();

      if(pview == nullptr)
      {

         return;

      }

      tab_view * ptabview = this_view()->GetTypedParent < tab_view >();

      if(ptabview != nullptr)
      {

         bool bDeleteOriginOnSuccessfulCopy = eop == ::user::copydesk::op_cut;

         ptabview->filemanager_document()->get_operation_doc(true)->m_thread.queue_copy(listing, strDir, nullptr, true, false, bDeleteOriginOnSuccessfulCopy, this, WM_APP + 1024, 4096);

         ptabview->filemanager_document()->get_operation_doc(true)->m_thread.kick();

      }

      pmessage->m_bRet =true;

   }


   void impact::_001OnOperationDocMessage(::message::message * pmessage)
   {

      SCAST_PTR(::message::base,pbase,pmessage);

      if(pbase->m_wparam == 4096)
      {

         if(pbase->m_lparam == 0)
         {

            _001Refresh();

         }

      }

   }



   void impact::on_apply(::action * paction)
   {

      ::user::impact::on_apply(paction);

      if (paction->id() == INITIALIZE_ID)
      {

         if (filemanager_document() == paction->cast < ::user::document >(DOCUMENT_ID))
         {

            __pointer(::database::client) pclient = GetParentFrame();

            if (pclient != nullptr && !pclient->m_id.to_string().contains("::frame"))
            {

               string str;

               str.Format("frame(%s)", filemanager_data()->m_id.str().c_str());

               pclient->set_data_key_modifier(str);

            }

         }

      }
      else if (paction->id() == SYNCHRONIZE_PATH_ID)
      {

         if (paction->m_pfileitem &&
            (::is_set(filemanager_item())
               && Application.is_equal_file_path(paction->m_pfileitem->m_filepathFinal, filemanager_item()->m_filepathFinal)))
         {

#define DBG_LOOP  1
            for (index i = 0; i < DBG_LOOP; i++)
            {

               browse_sync(paction->m_actioncontext + ::source_sync);

            }

         }
         else
         {

            knowledge(paction->m_pfileitem->m_filepathUser, paction->m_actioncontext + ::source_sync);

         }

         set_need_redraw();

      }

   }


} // namespace filemanager




