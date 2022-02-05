#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif


namespace filemanager
{


   path_view::path_view()
   {

      m_bVoidSync = false;

   }


   void path_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::plain_edit::install_message_routing(pchannel);

   }


   void path_view::browse_sync(const ::action_context & context)
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

      _001GetText(strOld);

      string strPath = filemanager_item()->get_user_path();

      if (strOld == strPath)
      {

         return;

      }

      _001SetText(filemanager_item()->get_user_path(), ::e_source_sync);

   }


   //void path_view::_001OnAfterChangeText(const ::action_context & context)
   //{

   //   //if (!context.is_user_source())
   //   //{

   //   //   return;

   //   //}

   //   //string str;

   //   //_001GetText(str);

   //   //__pointer(document) pdocument = filemanager_document();

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

   //   //      filemanager_document()->browse(str, context + ::e_source_sync);

   //   //   }

   //   //}
   //   //else
   //   //{

   //   //   auto pcontext = get_context();

   //   //   ::file::path pathAddress = str;

   //   //   while (true)
   //   //   {

   //   //      bool bIsDir = false;

   //   //      ::file::path path = pcontext->m_papexcontext->defer_process_path(pathAddress | ::file::e_flag_resolve_alias);

   //   //      bIsDir = filemanager_document()->fs_data()->is_dir(path);

   //   //      if (bIsDir)
   //   //      {

   //   //         if (filemanager_item()->m_filepathFinal != path)
   //   //         {

   //   //            __keep(m_bVoidSync);

   //   //            filemanager_document()->browse(pathAddress, context + ::e_source_sync);

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

   //   //filemanager_data()->m_pdocument->m_strTopic = str;


   //}


   void path_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //::color::color crBackground = 0;

      //get_color(crBackground, ::user::color_background);

      //if ((crBackground & argb(255, 0, 0, 0)) != 0)
      //{

      //   ::rectangle_i32 rectangleClient;

      //   get_client_rect(rectangleClient);

      //   pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      ::user::plain_edit::_001OnDraw(pgraphics);

      //}

   }


   void path_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      if (ptopic->m_id == INITIALIZE_ID)
      {

         //            filemanager_document() = pupdate->filemanager_document();
         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                     AddClient(this);
                     SetDataInterface(&m_datainterface);
                     AddClient(&m_datainterface);
                     string str;
                     str.format("::filemanager::file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                     if(filemanager_data()->m_bTransparentBackground)
                     {
                     ::user::list::m_etranslucency = ::user::list::e_translucency_present;
                     }
                     DISetSection(str);
                     _001UpdateColumns();*/
      }
      else if (ptopic->m_id == FILTER_ID)
      {
         /*if(ptopic->m_pextendedtopic->payload(id_filter).is_empty())
         {
         FilterClose();
         }
         else
         {
         FilterBegin();
         Filter1(ptopic->m_pextendedtopic->payload(id_filter));
         FilterApply();
         }*/
      }
      else if(ptopic->m_id == id_after_change_text)
      {

      if (!ptopic->m_pextendedtopic->m_actioncontext.is_user_source())
      {

         return;

      }

      string str;

      _001GetText(str);

      __pointer(document) pdocument = filemanager_document();

      if (pdocument == nullptr)
      {

         return;

      }

      ::fs::data * pfsdata = pdocument->fs_data();

      if (pfsdata->is_dir(str))
      {

         ::file::path strPreviousPath = filemanager_path();

         ::file::path strPath = str;

         if (strPreviousPath != strPath)
         {

            filemanager_document()->browse(str, ptopic->m_pextendedtopic->m_actioncontext + ::e_source_sync);

         }

      }
      else
      {

         auto pcontext = get_context();

         ::file::path pathAddress = str;

         while (true)
         {

            bool bIsDir = false;

            ::file::path path = pcontext->m_papexcontext->defer_process_path(pathAddress | ::file::e_flag_resolve_alias);

            bIsDir = filemanager_document()->fs_data()->is_dir(path);

            if (bIsDir)
            {

               if (filemanager_item()->m_filepathFinal != path)
               {

                  __keep(m_bVoidSync);

                  filemanager_document()->browse(pathAddress, ptopic->m_pextendedtopic->m_actioncontext + ::e_source_sync);

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

      filemanager_data()->m_pdocument->m_strTopic = str;


   }

   }


} // namespace filemanager



