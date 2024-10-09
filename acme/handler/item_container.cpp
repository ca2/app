// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "item_container.h"
#include "acme/handler/item.h"


item_container::item_container()
{


}


item_container::~item_container()
{


}


bool item_container::_is_set() const
{

   return true;

}


::collection::count item_container::item_count() const
{

   if (!m_pitema)
   {

      return 0;

   }

   return m_pitema->count();

}


void item_container::clear_items()
{

   if (!m_pitema)
   {

      return;

   }

   m_pitema->clear();

}


//::item * item_container::item_at(::collection::index iIndex)
//{
//
//   if (iIndex < 0 || iIndex >= m_pitema->size())
//   {
//
//      throw ::exception(::error_index_out_of_bounds);
//
//   }
//
//   return (*m_pitema)[iIndex];
//
//}


void item_container::indexed_set_item_at(::collection::index iIndex, ::item * pitem)
{

   if (iIndex < 0)
   {

      throw ::exception(error_index_out_of_bounds);

   }

   pitem->m_item.m_iItem = iIndex;

   m_pitema->set_at_grow(iIndex, pitem);

}


void item_container::indexed_add_item(::item * pitem)
{

   pitem->m_item.m_iItem = m_pitema->add(pitem);

}


::collection::index item_container::add_item(::item * pitem)
{

   if (!m_pitema)
   {

      __defer_construct_new(m_pitema);

   }

   return m_pitema->add(pitem);

}


//::user::item * item_container::user_item_at(::collection::index iIndex)
//{
//
//   auto pitem = item_at(iIndex);
//
//   return user_item(pitem);
//
//}


::collection::index item_container::item_index(const ::item * pitem)
{

   return m_pitema->find_first(pitem);

}


//::item * item_container::item_at(::)
//{
//
//   if()
//
//
//}


//::user::item * item_container::user_item(const ::item * pitem)
//{
//
//   auto & puseritem = m_useritemmap[pitem];
//
//   if (!puseritem)
//   {
//
//      __construct_new(puseritem);
//
//   }
//
//   if (!puseritem->m_pitem && pitem)
//   {
//
//      puseritem->m_pitem = (::item *)pitem;
//
//   }
//
//   return puseritem;
//
//}

//
//::user::item * item_container::user_item(const ::atom & atom)
//{
//
//   auto pitem = item(atom);
//
//   return user_item(pitem);
//
//}


::item_pointer item_container::item(const ::atom & atom)
{

   auto iIndex = item_index(atom);

   if (iIndex < 0)
   {

      return nullptr;

   }

   return (*m_pitema)[iIndex];

}


const ::item * item_container::item(const ::atom & atom) const
{

   return ((item_container *)this)->item(atom);

}


bool item_container::contains_item(const ::atom & atom) const
{

   return item(atom) != nullptr;

}


::item_pointer item_container::find_item(enum_element eelement, ::collection::index iItem)
{

   if (!m_pitema)
   {

      return nullptr;

   }

   for (auto & pitem : *m_pitema)
   {

      if (pitem->m_item.m_eelement != eelement)
      {

         continue;

      }

      if(pitem->m_item.m_iItem == iItem)
      { 
      
         return pitem;
      
      }

   }

   return nullptr;

}


::item_pointer item_container::defer_item(enum_element eelement, ::collection::index iItem)
{

   auto pitem = this->find_item(eelement, iItem);

   if (!pitem)
   {

      pitem = add_item(eelement, iItem);

   }

   return pitem;

}


::item_pointer item_container::add_item(enum_element eelement, ::collection::index iItem)
{

   auto pitem = __new ::item(eelement, iItem);

   pitem->initialize(this);

   add_item(pitem);

   return pitem;

}


::collection::index item_container::item_index() const
{

   return m_item.m_iItem;

}


::collection::index item_container::item_index(const ::atom & atom) const
{

   //information() << "item_container::item_index";

   if(atom.m_etype == ::atom::e_type_element && atom.m_eelement == e_element_resize)
   {

      //information() << "item_container::item_index e_element_resize";

   }

   if (::is_null(m_pitema))
   {

      //information() << "item_container::item_index m_pitema IS NULL";

      return -1;

   }

   //information() << "item_container::item_index m_pitema IS SET";

   if (atom.m_etype == ::atom::e_type_integer)
   {

      //information() << "item_container::item_index atom.m_etype == ::atom::e_type_integer";

      auto iItem = atom.as_index();

      if (m_pitema->is_index_ok(iItem))
      {

         //information() << "item_container::item_index FOUND(A) : " << iItem;

         return iItem;

      }

   }
   else if (atom.m_etype == ::atom::e_type_element)
   {

      //information() << "item_container::item_index atom.m_etype == ::atom::e_type_element";

      for (::collection::index iItem = 0; iItem < m_pitema->size(); iItem++)
      {

         auto pitem = (*m_pitema)[iItem];

         if (pitem->m_item.m_eelement == atom.m_eelement)
         {

            //information() << "item_container::item_index FOUND(B) : " << iItem;

            return iItem;

         }

      }

   }
   else
   {

      //information() << "item_container::item_index searching for atom";

      for (::collection::index iItem = 0; iItem < m_pitema->size(); iItem++)
      {

         auto pitem = (*m_pitema)[iItem];

         if (pitem->m_atom == atom)
         {

            //information() << "item_container::item_index FOUND(D) : " << iItem;

            return iItem;

         }

      }

   }

   //information() << "item_container::item_index NOT FOUND";

   return -1;

}



//bool item_container::is_item_pressed_by_index(::collection::index iIndex) const
//{
//
//   return ::is_item_index(m_pitemPressed, iIndex);
//
//}
//
//
//bool item_container::is_item_hover_by_index(::collection::index iIndex) const
//{
//
//   return ::is_item_index(m_pitemHover, iIndex);
//
//}


//bool item_container_map::is_item_pressed(const ::atom & atom) const
//{
//
//   auto iIndex = item_index(atom);
//
//   return is_item_pressed_by_index(iIndex);
//
//}
//
//
//bool item_container_map::is_item_hover(const ::atom & atom) const
//{
//
//   auto iIndex = item_index(atom);
//
//   return is_item_hover_by_index(iIndex);
//
//}



bool item_container::is_item_selected(::item * pitem)
{

   auto pitemSelected = selected_item();

   if (!pitemSelected)
   {

      return false;

   }

   return pitemSelected.m_p == pitem;

}


::item_pointer item_container::selected_item()
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


void item_container::on_item_selected(::item * pitem)
{


}


void item_container::on_item_hover(::item * pitem)
{


}


bool item_container::is_item_hover(::item * pitem)
{

   auto pitemHover = hover_item();

   if (!pitemHover)
   {

      return false;

   }

   return pitemHover.m_p == pitem;

}


::item_pointer item_container::hover_item()
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


::item_pointer item_container::get_child_as_item(::collection::index iIndex)
{

   return nullptr;

}


::collection::count item_container::get_child_as_item_count()
{

   return 0;

}



