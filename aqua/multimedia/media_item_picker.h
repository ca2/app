// Created by camilo on 2024-02-10 00:31 <3ThomasBorregaardSorensen!!
#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA media_item_picker :
      virtual public ::particle
   {
   public:


      void * m_pPlatformMediaItemPicker;
      ::pointer < ::aqua::media_item_picker_callback > m_ppickercallback;


      media_item_picker();
      ~media_item_picker() override;


      virtual void set_windowing_window(::windowing::window * pwindow);

      virtual void set_callback(::aqua::media_item_picker_callback * ppickercallback);


      virtual void pick_media(const_char_pointer  pszUTType);


      virtual ::pointer < ::aqua::media_item > create_media_item();


      virtual void did_pick_media(platform_media_item_t * pplatformmediaitem);


   };


} // namespace aqua



