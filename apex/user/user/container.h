// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/user/user/item.h"


namespace user
{


   class CLASS_DECL_APEX container :
      virtual public ::particle
   {
   public:


      container();
      ~container() override;


      virtual bool is_item_selected(::item* pitem);
      virtual ::item_pointer selected_item();

      virtual bool is_item_hover(::item* pitem);
      virtual ::item_pointer hover_item();


      virtual void on_item_selected(::item* pitem);
      virtual void on_item_hover(::item* pitem);

      virtual ::item_pointer get_child_as_item(::index iIndex);
      virtual ::count get_child_as_item_count();


   };


} // namespace user



