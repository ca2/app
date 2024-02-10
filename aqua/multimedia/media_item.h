// Created by camilo on 2024-02-09 21:15 <3ThomasBorregaardSorensen!!
#pragma once




namespace aqua
{


   class CLASS_DECL_AQUA media_item :
      virtual public ::particle
   {
   public:


      platform_media_item_t * m_pplatformmediaitem;


      media_item();
      ~media_item() override;


      virtual void on_destroy_platform_media_item();

      virtual void attach(platform_media_item_t * pplatformmediaitem);

      virtual void on_attach_platform_media_item();


   };


} // namespace aqua



