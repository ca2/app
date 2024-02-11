// Created by camilo on 2024-02-09 21:15 <3ThomasBorregaardSorensen!!
#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA media_item :
      virtual public ::particle
   {
   public:


      platform_media_item_t * m_pplatformmediaitem;
      ::pointer < ::aqua::media_player > m_pmediaplayer;

      
      media_item();
      ~media_item() override;


      virtual void on_destroy_platform_media_item();

      virtual void attach(platform_media_item_t * pplatformmediaitem);

      virtual void on_attach_platform_media_item();

      virtual ::string get_id();
      
      virtual ::aqua::enum_media_type get_media_type();
      
      virtual void assign_media_player();
      

   };


} // namespace aqua



