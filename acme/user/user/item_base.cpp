//
// Created by camilo on 2025-03-30 23:29 <3ThomasBorregaardSoresen!!
//
#include "framework.h"
#include "item_base.h"
#include "acme/exception/interface_only.h"
#include "acme/handler/item.h"


namespace user
{


   item_base::item_base()
   {


   }


   item_base::~item_base()
   {


   }


   void item_base::_set_item(::item * pitem)
   {

      throw ::interface_only();

   }


   ::item * item_base::_item()
   {

      throw ::interface_only();

      return nullptr;

   }


   string item_base::get_user_item_text()
   {

      if (!_item())
      {

         return "";

      }

      return _item()->get_item_text(this);

   }


   ::collection::index item_base::get_user_item_image()
   {

      if (!_item())
      {

         return -1;

      }

      return _item()->get_item_image(this);

   }


   ::image::image_list * item_base::get_user_item_image_list()
   {

      if (!_item())
      {

         return nullptr;

      }

      return _item()->get_item_image_list(this);

   }


} // namespace user



