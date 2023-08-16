// From aura by camilo on ThomasBirthday2021 21:12 BRT
#include "framework.h"
#include "item.h"


bool item::_is_set() const
{

   return m_item.m_eelement != e_element_none;

}


item & item::operator = (enum_element eelement)
{

   m_item.m_eelement = eelement;

   if (m_item.m_eelement == e_element_none)
   {

      m_item.m_iItem = -1;

      m_item.m_iSubItem = -1;

      m_item.m_iListItem = -1;

   }

   return *this;

}


item & item::operator = (::index iItem)
{

   m_item.m_iItem = iItem;

   if (m_item.m_iItem < 0)
   {

      m_item.m_eelement = e_element_none;

   }
   else
   {

      if (m_item.m_eelement == e_element_none)
      {

         m_item.m_eelement = e_element_item;

      }

   }

   return *this;

}


bool item::is_hidden() const
{

   return false;

}


::string item::get_text(::index iSubItem)
{

   return "";

}


//CLASS_DECL_ACME bool is_item_equivalent(const ::ITEM_PRIMARY_KEY * pitem1, const ::ITEM_PRIMARY_KEY * pitem2)
//{
//
//   if(!::is_item_set(pitem1) || !::is_item_set(pitem2))
//   {
//
//      return false;
//
//   }
//
//   if(pitem1 == pitem2)
//   {
//
//      return true;
//
//   }
//
//   //if(pitem1->m_item.m_eelement != pitem2->m_item.m_eelement)
//   //{
//
//   //   return false;
//
//   //}
//
//   if(pitem1->m_item.m_iItem != pitem2->m_item.m_iItem)
//   {
//
//      return false;
//
//   }
//
//   if(pitem1->m_item.m_iSubItem != pitem2->m_item.m_iSubItem)
//   {
//
//      return false;
//
//   }
//
//   if(pitem1->m_item.m_iListItem != pitem2->m_item.m_iListItem)
//   {
//
//      return false;
//
//   }
//
//   //if(pitem1->m_rectangle != pitem2->m_rectangle)
//   //{
//
//   //   return false;
//
//   //}
//
//   return true;
//
//}



