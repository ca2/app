// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "container.h"
#include "acme/handler/item.h"


namespace user
{


   container::container()
   {


   }


   container::~container()
   {


   }


   bool container::is_item_selected(const ::item* pitem)
   {

      auto pitemSelected = selected_item();

      if (!pitemSelected)
      {

         return false;

      }

      return pitemSelected.m_p == pitem;

   }


   item_pointer container::selected_item()
   {

      auto iCount = get_child_as_item_count();

      for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex)
      {

         auto pitem = get_child_as_item(iIndex);

         if (is_item_selected(pitem))
         {

            return pitem;

         }

      }

      return nullptr;

   }


   void container::on_item_selected(::item* pitem)
   {


   }
   
   
   void container::on_item_hover(::item* pitem)
   {


   }



   bool container::is_item_hover(const ::item* pitem)
   {

      auto pitemHover = hover_item();

      if (!pitemHover)
      {

         return false;

      }

      return pitemHover.m_p == pitem;

   }


   item_pointer container::hover_item()
   {

      auto iCount = get_child_as_item_count();

      for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex)
      {

         auto pitem = get_child_as_item(iIndex);

         if (is_item_hover(pitem))
         {

            return pitem;

         }

      }

      return nullptr;

   }


   item_pointer container::get_child_as_item(::index iIndex)
   {

      return nullptr;

   }


   ::count container::get_child_as_item_count()
   {

      return 0;

   }



} // namespace user



