#include "framework.h"
#include "impact_base.h"
#include "document.h"
#include "tab_impact.h"
#include "data.h"
#include "operation_document.h"
#include "operation_thread.h"
#include "operation.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"
#include "aura/user/user/copydesk.h"
#include "aura/message/user.h"
#include "aura/user/user/frame.h"
#include "core/platform/application.h"


filemanager_impact_base::filemanager_impact_base()
{

   m_bEditConnectInit = false;
   m_pfsdata = nullptr;
   m_pfilemanagerdocument = nullptr;

}


filemanager_impact_base::~filemanager_impact_base()
{

}


::core::application* filemanager_impact_base::get_app()
{

   auto pacmeapplication = acmeapplication();

   return ::is_set(pacmeapplication) ? pacmeapplication->m_pcoreapplication : nullptr;

}


::core::session* filemanager_impact_base::get_session()
{

   auto pacmesession = acmesession();

   return ::is_set(pacmesession) ? pacmesession->m_pcoresession : nullptr;

}


::core::system* filemanager_impact_base::get_system()
{

   auto pacmesystem = acmesystem();

   return ::is_set(pacmesystem) ? pacmesystem->m_pcoresystem : nullptr;

}


::filemanager::document * filemanager_impact_base::get_document()
{

   return filemanager_document();

}


void filemanager_impact_base::initialize_impact(::user::document * pdocument)
{

   ::user::impact::initialize_impact(pdocument);

   m_pfilemanagerdocument = dynamic_cast <::filemanager::document *>(pdocument);

   m_pfsdata = m_pfilemanagerdocument->fs_data();

}


void filemanager_impact_base::install_message_routing(::channel * pchannel)
{

   ::user::impact::install_message_routing(pchannel);

   add_command_prober("edit_paste", { this,  &filemanager_impact_base::_001OnUpdateEditPaste });

   add_command_handler("edit_paste", { this,  &filemanager_impact_base::_001OnEditPaste });

   MESSAGE_LINK(WM_APP + 1024,pchannel,this,&filemanager_impact_base::_001OnOperationDocMessage);

}


::file::item * filemanager_impact_base::filemanager_item()
{

   auto pdocument = filemanager_document();

   if (!pdocument)
   {

      return nullptr;

   }

   return pdocument->filemanager_item();

}


//::pointer<::fs::data>filemanager_impact_base::fs_data()
//{
//
//   return filemanager_document()->fs_data();
//
//}


::file::path filemanager_impact_base::filemanager_path()
{

   return filemanager_item()->user_path();

}

//
//::filemanager::document * filemanager_impact_base::filemanager_document()
//{
//
//   return dynamic_cast <::filemanager::document * > (get_document());
//
//}


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

   ::pointer<::message::command>pcommand(pmessage);

   auto pcopydesk = copydesk();
   
   bool bHasFile = pcopydesk->has_filea();
         
   pcommand->enable(bHasFile);

   pmessage->m_bRet = true;

}


void filemanager_impact_base::_001OnEditPaste(::message::message * pmessage)
{

   __UNREFERENCED_PARAMETER(pmessage);

   ::file::listing listing;

   ::user::copydesk::enum_op eop;

   auto pcopydesk = copydesk();
   
   bool bOk = pcopydesk->get_filea(listing, eop);

   if(!bOk || listing.is_empty())
   {

      pmessage->m_bRet = true;

      return;

   }

   string strDir;

   strDir = filemanager_item()->user_path();

   auto pimpact  = this;

   if(pimpact == nullptr)
   {

      return;

   }

   auto ptabimpact = get_typed_parent <::filemanager::tab_impact >();

   if(ptabimpact != nullptr)
   {

      bool bDeleteOriginOnSuccessfulCopy = eop == ::user::copydesk::e_op_cut;

      auto atomFileManager = filemanager_data()->m_atom;

      ptabimpact->filemanager_document(atomFileManager)->get_operation_doc(true)->m_poperationthread->queue_copy(listing, strDir, nullptr, true, false, bDeleteOriginOnSuccessfulCopy, this, WM_APP + 1024, 4096);

      ptabimpact->filemanager_document(atomFileManager)->get_operation_doc(true)->m_poperationthread->kick();

   }

   pmessage->m_bRet =true;

}


void filemanager_impact_base::_001OnOperationDocMessage(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

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

   if (ptopic->m_atom == id_initialize)
   {

      if (filemanager_document() == ptopic->cast < ::user::document >(ID_DOCUMENT))
      {

         ::pointer<::database::client>pclient = parent_frame();

         if (pclient != nullptr && !::string(pclient->m_atom).contains("::frame"))
         {

            string str;

            str.format("frame(%s)", ::string(filemanager_data()->m_atom).c_str());

            pclient->set_data_key_modifier(str);

         }

      }

   }
   else if (ptopic->m_atom == id_synchronize_path)
   {

      ::pointer<::core::application>papp = get_app();

      auto pfileitemTopic = ptopic->_extended_topic()->m_pfileitem;

      if (pfileitemTopic)
      {

         bool bSameFilePath = false;

         if (::is_set(filemanager_item()))
         {

            ::file::path pathTopicFinal = ptopic->_extended_topic()->m_pfileitem->final_path();

            ::file::path pathItemFinal = filemanager_item()->final_path();

            bSameFilePath = papp->is_equal_file_path(pathTopicFinal, pathItemFinal);

         }

         if (bSameFilePath)
         {

#define DBG_LOOP  1
            for (index i = 0; i < DBG_LOOP; i++)
            {

               browse_sync(ptopic->m_actioncontext + ::e_source_sync);

            }

         }
         else
         {

            ::file::path pathUser;

            pathUser = pfileitemTopic->user_path();

            knowledge(pathUser, ptopic->m_actioncontext + ::e_source_sync);

         }

         set_need_redraw();

      }

   }

}




