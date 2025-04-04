#include "framework.h"
#include "data.h"
#include "thumbnail.h"
#include "acme/handler/topic.h"
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



      auto rectangleX = this->rectangle();
      pgraphics->fill_rectangle(rectangleX, rgb(200, 200, 190));

      if(filemanager_document() == nullptr)
         return;

      if (m_iCurFile < 0)
      {
      }
      else if (m_iCurFile == 0 && filemanager_data()->m_listingUser2.get_size() == 0)
      {
         pgraphics->text_out(10, 10, "No files in this directory");
      }
      else if(m_iCurFile < filemanager_data()->m_listingUser2.get_size())
      {

         pgraphics->text_out(10,10,filemanager_data()->m_listingUser2.title(m_iCurFile));

      }

   }


   void thumbnail::handle(::topic * ptopic, ::handler_context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, phandlercontext);

      if (ptopic->id() == id_initialize)
      {

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



