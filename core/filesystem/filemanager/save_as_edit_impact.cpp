// From save_as_name_impact by camilo on 2023-05-05 19:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "save_as_edit_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/file_system.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/micro/user.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame_interaction.h"


namespace filemanager
{


   save_as_edit_impact::save_as_edit_impact()
   {

      m_bVoidSync = false;

   }


   void save_as_edit_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);

   }




   void save_as_edit_impact::browse_sync(const ::action_context & context)
   {

      if (m_bVoidSync)
      {

         return;

      }

      string strText;

      strText = as_text();

      if (strText != get_document()->m_strTopic.title())
      {

         set_text(get_document()->m_strTopic.title(), context);

      }

   }


   void save_as_edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      string str;

      str = as_text();

      // auto pcontext = get_context();

      if (directory()->is(str))
      {

         filemanager_document()->browse(str, context + ::e_source_sync);

      }
      else if (str.contains("/") || str.contains("\\"))
      {

         ::file::path strName = str;

         while (true)
         {

            strName = strName.folder();

            if (directory()->is(strName))
            {

               if (filemanager_item()->user_path() != strName)
               {

                  filemanager_document()->browse(strName, context + ::e_source_sync);

               }

               break;

            }

            if (strName.is_empty())
            {

               break;

            }

         }

      }

      if (filemanager_document() != nullptr)
      {

         filemanager_document()->m_strTopic = str;

      }

   }


   void save_as_edit_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
   {

      ::user::impact::handle(ptopic, phandlercontext);

      if (ptopic->id() == id_initialize && ptopic->m_puserelement == this)
      {
         //            filemanager_document() = pupdate->filemanager_document();
         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
         AddClient(this);
         SetDataInterface(&m_datainterface);
         AddClient(&m_datainterface);
         string str;
         str.formatf("file_list(%d,%d)", get_document()->m_iTemplate, get_document()->m_iDocument);
         if(get_document()->m_bTransparentBackground)
         {
         ::user::list::m_etranslucency = ::user::list::e_translucency_present;
         }
         DISetSection(str);
         _001UpdateColumns();*/
      }
      else if (ptopic->id() == id_filter)
      {
         /*if(ptopic->payload(id_filter).is_empty())
         {
         FilterClose();
         }
         else
         {
         FilterBegin();
         Filter1(ptopic->payload(id_filter));
         FilterApply();
         }*/
      }

   }




} // namespace filemanager



