// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "content.h"
#include "container.h"
#include "tool.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"


namespace user
{


   acme_container::acme_container()
   {


   }


   acme_container::~acme_container()
   {


   }



   void acme_container::destroy()
   {

      m_useritemmap.clear();
      m_pacmetool.release();
      m_pacmecontentMain.release();
      m_pitemHover.release();
      m_pitemPressed.release();

      item_container_map::destroy();

   }

   bool acme_container::_is_set() const
   {

      return true;

   }


   void acme_container::create_tool()
   {

      if (m_pacmetool)
      {

         return;

      }

      __construct_new(m_pacmetool);

      m_itemcontainermap[id_tool] = m_pacmetool;

   }


   void acme_container::create_main_content()
   {

      if (m_pacmecontentMain)
      {

         return;

      }

      __construct_new(m_pacmecontentMain);

      m_itemcontainermap[id_content] = m_pacmecontentMain;

   }


   //::count acme_container::item_count() const
   //{

   //   if (!m_pitema)
   //   {

   //      return 0;

   //   }

   //   return m_pitema->count();

   //}


   //void acme_container::clear_items()
   //{

   //   if (!m_pitema)
   //   {

   //      return;

   //   }

   //   m_pitema->clear();

   //}


   //::item * acme_container::item_at(::index iIndex)
   //{

   //   if (iIndex < 0 || iIndex >= m_pitema->size())
   //   {

   //      throw ::exception(::error_index_out_of_bounds);

   //   }

   //   return (*m_pitema)[iIndex];

   //}


   //void acme_container::default_set_item_at(::index iIndex, ::item * pitem)
   //{

   //   if (iIndex < 0)
   //   {

   //      throw ::exception(error_index_out_of_bounds);

   //   }

   //   pitem->m_item.m_iItem = iIndex;

   //   m_pitema->set_at_grow(iIndex, pitem);

   //}


   //void acme_container::default_add_item(::item * pitem)
   //{

   //   pitem->m_item.m_iItem = add_item(pitem);

   //}


   //::index acme_container::add_item(::item * pitem)
   //{

   //   if (!m_pitema)
   //   {

   //      __defer_construct_new(m_pitema);

   //   }

   //   return m_pitema->add(pitem);

   //}


   //::user::item * acme_container::user_item_at(::index iIndex)
   //{

   //   auto pitem = item_at(iIndex);

   //   return user_item(pitem);

   //}


   //::index acme_container::item_index(const ::item * pitem)
   //{

   //   return m_pitemaContent->find_first(pitem);

   //}


   ::user::item * acme_container::user_item(const ::item * pitem)
   {

      auto & puseritem = m_useritemmap[pitem];

      if (!puseritem)
      {

         __construct_new(puseritem);

      }

      if (!puseritem->m_pitem && pitem)
      {

         puseritem->m_pitem = (::item *)pitem;

      }

      return puseritem;

   }


   //::user::item * acme_container::user_item(const ::atom & atom)
   //{

   //   auto pitem = item(atom);

   //   return user_item(pitem);

   //}


   //::item_pointer acme_container::item(const ::atom & atom)
   //{

   //   auto iIndex = item_index(atom);

   //   if (iIndex < 0)
   //   {

   //      return nullptr;

   //   }

   //   return (*m_pitema)[iIndex];

   //}


   //::item_pointer acme_container::item(const item_t & item)
   //{

   //   if (!m_pitema)
   //   {

   //      return nullptr;

   //   }

   //   for (auto & pitem : *m_pitema)
   //   {

   //      if (::is_item_equivalent(&pitem->m_item, &item))
   //      {

   //         return pitem;

   //      }

   //   }

   //   return nullptr;

   //}


   //::item_pointer acme_container::defer_item(const item_t & item)
   //{

   //   auto pitem = this->item(item);

   //   if (!pitem)
   //   {

   //      pitem = add_item(item);

   //   }

   //   return pitem;

   //}


   //::item_pointer acme_container::add_item(const ::item_t & item)
   //{

   //   auto pitem = __allocate< ::item >(item);

   //   pitem->initialize(this);

   //   add_item(pitem);

   //   return pitem;

   //}


   //::index acme_container::item_index() const
   //{
   //
   //   return m_item.item_index();
   //
   //}


   //::index acme_container::item_index(const ::atom & atom) const
   //{

   //   auto iIndex = atom.as_index();

   //   if (!m_pitema->is_index_ok(iIndex))
   //   {

   //      iIndex = -1;

   //      for (::index iItem = 0; iItem < m_pitema->size(); iItem++)
   //      {

   //         auto pitem = (*m_pitema)[iItem];

   //         if (atom.m_etype == ::atom::e_type_element)
   //         {

   //            if (pitem->m_item.m_eelement == atom.m_eelement)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }
   //         else
   //         {

   //            if (pitem->m_atom == atom)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }

   //      }

   //      if (iIndex < 0)
   //      {

   //         // still not ok? couldn't find then, right?!...;

   //         return -1;

   //      }

   //   }

   //   return iIndex;

   //}


   //::index acme_container::item_index(::item_array * pitema, const ::atom & atom)
   //{

   //   if (::is_null(pitema))
   //   {

   //      return -1;

   //   }

   //   auto iIndex = atom.as_index();

   //   if (!pitema->is_index_ok(iIndex))
   //   {

   //      iIndex = -1;

   //      for (::index iItem = 0; iItem < pitema->size(); iItem++)
   //      {

   //         auto pitem = (*pitema)[iItem];

   //         if (atom.m_etype == ::atom::e_type_element)
   //         {

   //            if (pitem->m_item.m_eelement == atom.m_eelement)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }
   //         else
   //         {

   //            if (pitem->m_atom == atom)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }

   //      }

   //      if (iIndex < 0)
   //      {

   //         // still not ok? couldn't find then, right?!...;

   //         return -1;

   //      }

   //   }

   //   return iIndex;

   //}


   //::index acme_container::item_index(const ::atom & atom) const
   //{

   //   auto iIndex = atom.as_index();

   //   if (!m_pitema->is_index_ok(iIndex))
   //   {

   //      iIndex = -1;

   //      for (::index iItem = 0; iItem < m_pitema->size(); iItem++)
   //      {

   //         auto pitem = (*m_pitema)[iItem];

   //         if (atom.m_etype == ::atom::e_type_element)
   //         {

   //            if (pitem->m_item.m_eelement == atom.m_eelement)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }
   //         else
   //         {

   //            if (pitem->m_atom == atom)
   //            {

   //               iIndex = iItem;

   //               break;

   //            }

   //         }

   //      }

   //      if (iIndex < 0)
   //      {

   //         // still not ok? couldn't find then, right?!...;

   //         return -1;

   //      }

   //   }

   //   return iIndex;

   //}


   //bool acme_container::is_item_pressed_by_index(::index iIndex) const
   //{

   //   return ::is_item_index(m_pitemPressed, iIndex);

   //}


   //bool acme_container::is_item_hover_by_index(::index iIndex) const
   //{

   //   return ::is_item_index(m_pitemHover, iIndex);

   //}


   //bool acme_container::is_item_pressed(const ::atom & atom) const
   //{

   //   auto iIndex = item_index(atom);

   //   return is_item_pressed_by_index(iIndex);

   //}


   //bool acme_container::is_item_hover(const ::atom & atom) const
   //{

   //   auto iIndex = item_index(atom);

   //   return is_item_hover_by_index(iIndex);

   //}



   bool acme_container::is_item_selected(::item* pitem)
   {

      auto pitemSelected = selected_item();

      if (!pitemSelected)
      {

         return false;

      }

      return pitemSelected.m_p == pitem;

   }


   //::item_pointer acme_container::selected_item()
   //{

   //   auto iCount = get_child_as_item_count();

   //   for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex++)
   //   {

   //      auto pitem = get_child_as_item(iIndex);

   //      if (is_item_selected(pitem))
   //      {

   //         return pitem;

   //      }

   //   }

   //   return nullptr;

   //}


   //void acme_container::on_item_selected(::item* pitem)
   //{


   //}
   
   
   void acme_container::on_item_hover(::item* pitem)
   {


   }


   bool acme_container::is_item_hover(::item* pitem)
   {

      auto pitemHover = hover_item();

      if (!pitemHover)
      {

         return false;

      }

      return pitemHover.m_p == pitem;

   }


   //::item_pointer acme_container::hover_item()
   //{

   //   auto iCount = get_child_as_item_count();

   //   for (decltype(iCount) iIndex = 0; iIndex < iCount; iIndex++)
   //   {

   //      auto pitem = get_child_as_item(iIndex);

   //      if (is_item_hover(pitem))
   //      {

   //         return pitem;

   //      }

   //   }

   //   return nullptr;

   //}


   //::item_pointer acme_container::get_child_as_item(::index iIndex)
   //{

   //   return nullptr;

   //}


   //::count acme_container::get_child_as_item_count()
   //{

   //   return 0;

   //}


   bool acme_container::is_item_pressed(const ::item_t & item) const
   {

      if (!::is_item_set(m_pitemPressed))
      {

         return false;

      }

      return m_pitemPressed->m_item == item;

   }


   bool acme_container::is_item_hover(const ::item_t & item) const
   {

      if (!::is_item_set(m_pitemHover))
      {

         return false;

      }

      return m_pitemHover->m_item == item;

   }


   ::item_pointer acme_container::pressed_item()
   {

      return m_pitemPressed;

   }


   ::item_pointer acme_container::hover_item()
   {

      return m_pitemHover;

   }


   ::item_pointer acme_container::selected_item()
   {

      return main_content().selected_item();

   }





} // namespace user



