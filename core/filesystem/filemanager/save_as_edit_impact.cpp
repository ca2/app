// From save_as_name_impact by camilo on 2023-05-05 19:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "save_as_edit_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/context.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/nano/user/nano.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame.h"


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

      _001GetText(strText);

      if (strText != get_document()->m_strTopic.title())
      {

         _001SetText(get_document()->m_strTopic.title(), context);

      }

   }


   void save_as_edit_impact::_001OnAfterChangeText(const ::action_context & context)
   {

      string str;

      _001GetText(str);

      auto pcontext = get_context();

      if (dir()->is(str))
      {

         filemanager_document()->browse(str, context + ::e_source_sync);

      }
      else if (str.contains("/") || str.contains("\\"))
      {

         ::file::path strName = str;

         while (true)
         {

            strName = strName.folder();

            if (dir()->is(strName))
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


   void save_as_edit_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == ID_INITIALIZE && ptopic->m_puserelement == this)
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
      else if (ptopic->m_atom == ID_FILTER)
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



