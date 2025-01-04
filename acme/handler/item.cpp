// From aura by camilo on ThomasBirthday2021 21:12 BRT
#include "framework.h"
#include "item.h"


::string get_e_element_text(enum_element eelement)
{

   ::string str;

   switch (eelement)
   {
   case e_element_none:
      str = "e_element_none";
      break;
   case e_element_item:
      str = "e_element_item";
      break;
   default:
      str.formatf("(enum_element=%lld)", (huge_integer)eelement);
      break;
   }

   return str;
}


void item::get_debug_title(char * sz, character_count c) const
{

   char sz1[256];

   particle::get_debug_title(sz1, 256);

   ::string strTitle = sz1;

   strTitle.append_formatf("(%s, item=%lld)",
      get_e_element_text(m_item.m_eelement).c_str(),
      m_item.m_iItem);

   ::string_count_copy(sz, strTitle.c_str(), c);


}


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

      //m_item.m_iSubItem = -1;

      //m_item.m_iListItem = -1;

   }

   return *this;

}


item & item::operator = (::collection::index iItem)
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


::string item::get_item_text(::collection::index iSubItem)
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



