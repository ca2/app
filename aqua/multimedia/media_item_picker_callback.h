// Created by camilo on 2024-02-10 00:36 <3ThomasBorregaardSorensen!!
#pragma once


namespace aqua
{


   class media_item_picker_callback :
      virtual public ::particle
   {
   public:


      media_item_picker_callback();
      ~media_item_picker_callback() override;


      virtual void did_pick_media_item(::aqua::media_item * pitem);


   };


} // namespace aqua




