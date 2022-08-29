#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "thumbnail.h"
#include "aura/graphics/draw2d/graphics.h"
#include "document.h"


namespace filemanager
{


   thumbnail::thumbnail()
   {

   }


   thumbnail::~thumbnail()
   {

   }


   void thumbnail::install_message_routing(::channel * pchannel)
   {
      ::user::impact::install_message_routing(pchannel);
   }



   void thumbnail::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      ::rectangle_i32 rectangleClient;
      get_client_rect(rectangleClient);
      pgraphics->fill_rectangle(rectangleClient, rgb(200, 200, 190));

      if(filemanager_document() == nullptr)
         return;

      if (m_iCurFile < 0)
      {
      }
      else if (m_iCurFile == 0 && filemanager_document()->m_listingUser2.get_size() == 0)
      {
         pgraphics->text_out(10, 10, "No files in this directory");
      }
      else if(m_iCurFile < filemanager_document()->m_listingUser2.get_size())
      {

         pgraphics->text_out(10,10,filemanager_document()->m_listingUser2.title(m_iCurFile));

      }

   }


   void thumbnail::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      if (ptopic->m_atom == INITIALIZE_ID)
      {

         /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                     AddClient(this);
                     SetDataInterface(&m_datainterface);
                     AddClient(&m_datainterface);
                     string str;
                     str.format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                     if(filemanager_data()->m_bTransparentBackground)
                     {
                     ::user::list::m_etranslucency = ::user::list::e_translucency_present;
                     }
                     DISetSection(str);
                     _001UpdateColumns();*/
      }
      else if (ptopic->m_atom == FILTER_ID)
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



