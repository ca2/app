// Created by camilo on 2024-02-09 21:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "media_item.h"


namespace aqua
{


   media_item::media_item()
   {

      m_pplatformmediaitem = nullptr;

   }


   media_item::~media_item()
   {


   }


   void media_item::on_destroy_platform_media_item()
   {



   }

   
   void media_item::attach(platform_media_item_t * pplatformmediaitem)
   {

      on_destroy_platform_media_item();

      m_pplatformmediaitem = pplatformmediaitem;

      on_attach_platform_media_item();

   }


   void media_item::on_attach_platform_media_item()
   {



   }


} // namespace aqua


