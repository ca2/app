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


   ::string media_item::get_id()
   {
   
      return {};
      
   }


   ::aqua::enum_media_type media_item::get_media_type()
   {
      
      return ::aqua::e_media_type_unknown;
      
   }


   void media_item::assign_media_player()
   {
      
      
   }


} // namespace aqua


