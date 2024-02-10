// Created by camilo on 2024-02-10 00:31 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "media_item_picker.h"
#include "acme/exception/interface_only.h"


namespace aqua
{


   media_item_picker::media_item_picker()
   {
   
      m_ppickercallback = nullptr;
   
   }


   media_item_picker::~media_item_picker()
   {



   }


   void media_item_picker::set_windowing_window(::windowing::window * pwindow)
   {


   }
   

   void media_item_picker::set_callback(::media_item_picker_callback * ppickercallback)
   {

      m_ppickercallback = ppickercallback;

   }

   
   void media_item_picker::pick_media(const char * pszUTType)
   {


   }


   ::pointer < ::aqua::media_item > media_item_picker::create_media_item()
   {

      throw interface_only();

      return nullptr;

   }


   void media_item_picker::did_pick_media(platform_media_item_t * pplatformediaitem)
   {

      auto pmediaitem = create_media_item();

      pmediaitem->attach(pplatformediaitem);

      m_pcallback->did_pick_media_item(pmediaitem);

   }


} // namespace aqua



