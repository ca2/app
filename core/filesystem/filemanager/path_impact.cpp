#include "framework.h"
#include "path_impact.h"
#include "document.h"
#include "data.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/platform/keep.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "apex/filesystem/fs/set.h"


namespace filemanager
{


   path_impact::path_impact()
   {

      m_bVoidSync = false;

   }


   void path_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);

   }


   void path_impact::browse_sync(const ::action_context & context)
   {

      if (m_bVoidSync)
      {

         return;

      }

      if (filemanager_document() == nullptr)
      {

         return;

      }

      string strOld;

      strOld = as_text();

      string strPath = filemanager_item()->user_path();

      if (strOld == strPath)
      {

         return;

      }

      set_text(filemanager_item()->user_path(), ::e_source_sync);

   }


   //void path_impact::_001OnAfterChangeText(const ::action_context & context)
   //{

   //   //if (!context.is_user_source())
   //   //{

   //   //   return;

   //   //}

   //   //string str;

   //   //get_text(str);

   //   //::pointer<document>pdocument = filemanager_document();

   //   //if (pdocument == nullptr)
   //   //{

   //   //   return;

   //   //}

   //   //::fs::data * pfsdata = pdocument->fs_data();

   //   //if (pfsdata->is_dir(str))
   //   //{

   //   //   ::file::path strPreviousPath = filemanager_path();

   //   //   ::file::path strPath = str;

   //   //   if (strPreviousPath != strPath)
   //   //   {

   //   //      filemanager_data()->browse(str, context + ::e_source_sync);

   //   //   }

   //   //}
   //   //else
   //   //{

   //   //   // auto pcontext = get_context();

   //   //   ::file::path pathAddress = str;

   //   //   while (true)
   //   //   {

   //   //      bool bIsDir = false;

   //   //      ::file::path path = m_papplication->defer_process_matter_path(pathAddress | ::file::e_flag_resolve_alias);

   //   //      bIsDir = filemanager_document()->fs_data()->is_dir(path);

   //   //      if (bIsDir)
   //   //      {

   //   //         if (filemanager_item()->m_filepathFinal != path)
   //   //         {

   //   //            KEEP(m_bVoidSync);

   //   //            filemanager_data()->browse(pathAddress, context + ::e_source_sync);

   //   //         }

   //   //         break;

   //   //      }

   //   //      if (pathAddress.is_empty())
   //   //      {

   //   //         break;

   //   //      }

   //   //      pathAddress = pathAddress.folder();

   //   //   }

   //   //}

   //   //get_document()->m_strTopic = str;


   //}


   void path_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //::color::color crBackground = 0;

      //get_color(crBackground, ::user::color_background);

      //if ((crBackground & argb(255, 0, 0, 0)) != 0)
      //{

      //   ::rectangle_i32 rectangleX;

      //   this->rectangle(rectangleX);

      //   pgraphics->fill_rectangle(rectangleX, argb(255, 255, 255, 255));

      ::user::plain_edit::_001OnDraw(pgraphics);

      //}

   }


   void path_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      if (ptopic->m_atom == ID_INITIALIZE)
      {

         //            filemanager_document() = pupdate->filemanager_document();
         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                     AddClient(this);
                     SetDataInterface(&m_datainterface);
                     AddClient(&m_datainterface);
                     string str;
                     str.formatf("::filemanager::file_list(%d,%d)", get_document()->m_iTemplate, get_document()->m_iDocument);
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
      else if(ptopic->m_atom == id_after_change_text)
      {

      if (!ptopic->m_actioncontext.is_user_source())
      {

         return;

      }

      string str;

      str = as_text();

      ::pointer<document>pdocument = filemanager_document();

      if (pdocument == nullptr)
      {

         return;

      }

      auto pfilemanagerdata = filemanager_data();

      auto pfsdata = pfilemanagerdata->fs_data();

      //::fs::data * pfsdata = pdocument->filemanager_data();

      if (pfsdata->is_dir(str))
      {

         ::file::path strPreviousPath = filemanager_path();

         ::file::path strPath = str;

         if (strPreviousPath != strPath)
         {

            filemanager_document()->browse(str, ptopic->m_actioncontext + ::e_source_sync);

         }

      }
      else
      {

         // auto pcontext = get_context();

         ::file::path pathAddress = str;

         while (true)
         {

            bool bIsDir = false;

            auto pathToProcess = pathAddress;

            pathToProcess.flags() += ::file::e_flag_resolve_alias;

            ::file::path path = m_papplication->defer_process_matter_path(pathToProcess);

            bIsDir = filemanager_data()->fs_data()->is_dir(path);

            if (bIsDir)
            {

               if (filemanager_item()->final_path() != path)
               {

                  KEEP(m_bVoidSync);

                  filemanager_document()->browse(pathAddress, ptopic->m_actioncontext + ::e_source_sync);

               }

               break;

            }

            if (pathAddress.is_empty())
            {

               break;

            }

            pathAddress = pathAddress.folder();

         }

      }

      //get_document()->m_strTopic = str;
      get_document()->m_strTopic = str;

   }

   }


} // namespace filemanager



