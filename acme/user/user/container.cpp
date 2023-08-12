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


   ::count container::item_count() const
   {

      return m_itema.count();

   }


   ::item * container::item_at(::index iIndex)
   {

      if (iIndex < 0 || iIndex >= m_itema.size())
      {

         throw ::exception(::error_index_out_of_bounds);

      }

      return m_itema[iIndex];

   }


   void container::default_set_item_at(::index iIndex, ::item * pitem)
   {

      if (iIndex < 0)
      {

         throw ::exception(error_index_out_of_bounds);

      }

      pitem->m_iItem = iIndex;

      m_itema.set_at_grow(iIndex, pitem);

   }


   void container::default_add_item(::item * pitem)
   {

      pitem->m_iItem = add_item(pitem);

   }


   ::index container::add_item(::item * pitem)
   {

      return m_itema.add(pitem);

   }


   ::user::item * container::user_item_at(::index iIndex)
   {

      auto pitem = item_at(iIndex);

      return user_item(pitem);

   }


   ::index container::item_index(const ::item * pitem)
   {

      return m_itema.find_first(pitem);

   }


   ::user::item * container::user_item(const ::item * pitem)
   {

      auto & useritem = m_useritemmap[pitem];

      if (!useritem.m_pitem && pitem)
      {

         useritem.m_pitem = (::item *)pitem;

      }

      return &useritem;

   }


   ::user::item * container::user_item(const ::atom & atom)
   {

      auto pitem = item(atom);

      return user_item(pitem);

   }


   ::item_pointer container::item(const ::atom & atom)
   {

      auto iIndex = item_index(atom);

      if (iIndex < 0)
      {

         return nullptr;

      }

      return m_itema[iIndex];

   }


   ::index container::item_index(const ::atom & atom) const
   {

      auto iIndex = atom.as_index();

      if (!m_itema.is_index_ok(iIndex))
      {

         iIndex = -1;

         for (::index iItem = 0; iItem < m_itema.size(); iItem++)
         {

            auto pitem = m_itema[iItem];

            if (atom.m_etype == ::atom::e_type_element)
            {

               if (pitem->m_eelement == atom.m_eelement)
               {

                  iIndex = iItem;

                  break;

               }

            }
            else
            {

               if (pitem->m_atom == atom)
               {

                  iIndex = iItem;

                  break;

               }

            }

         }

         if (iIndex < 0)
         {

            // still not ok? couldn't find then, right?!...;

            return -1;

         }

      }

      return iIndex;

   }


   bool container::is_item_pressed_by_index(::index iIndex) const
   {

      return ::is_item_index(m_pitemPressed, iIndex);

   }


   bool container::is_item_hover_by_index(::index iIndex) const
   {

      return ::is_item_index(m_pitemHover, iIndex);

   }


   bool container::is_item_pressed(const ::atom & atom) const
   {

      auto iIndex = item_index(atom);

      return is_item_pressed_by_index(iIndex);

   }


   bool container::is_item_hover(const ::atom & atom) const
   {

      auto iIndex = item_index(atom);

      return is_item_hover_by_index(iIndex);

   }



   bool container::is_item_selected(::item* pitem)
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

      for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex++)
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


   bool container::is_item_hover(::item* pitem)
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

      for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex++)
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



