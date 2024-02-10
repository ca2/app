// Created by camilo on 2024-02-09 21:15 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "media_item.h"


namespace aqua
{


   media_item::media_item()
   {

      m_pPlatformObject = nullptr;

   }


   media_item::media_item()
   {

      //if (::is_set(m_pPlatformObject))
      //{
      // 
      //   node()->free_platform_media_item(me)

      //}

   }

   
   void media_item::attach(platform_media_item_t * pplatformmediaitem)
   {

      m_pplatformmediaitem = pplatformmediaitem;

      on_attach();

   }


   void media_item::on_attach()
   {



   }


} // namespace aqua


