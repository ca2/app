// From aura by camilo on ThomasBirthday2021 21:12 BRT
#include "framework.h"
#include "item.h"


bool item_base::_is_set() const
{

   return m_eelement != e_element_none;

}


item & item::operator = (enum_element eelement)
{

   m_eelement = eelement;

   if (m_eelement != e_element_none)
   {

      if (m_iItem < 0)
      {

         m_iItem = 0;

      }

   }
   else
   {

      m_iItem = -1;

      m_iSubItem = -1;

      m_iListItem = -1;

   }

   return *this;

}


item & item::operator = (::index iItem)
{

   m_iItem = iItem;

   if (m_iItem < 0)
   {

      m_eelement = e_element_none;

   }
   else
   {

      if (m_eelement == e_element_none)
      {

         m_eelement = e_element_item;

      }

   }

   return *this;

}


bool item::is_hidden() const
{

   return false;

}


CLASS_DECL_ACME bool is_item_equivalent(const ::item * pitem1, const ::item * pitem2)
{

   if(!::is_item_set(pitem1) || !::is_item_set(pitem2))
   {

      return false;

   }

   if(pitem1 == pitem2)
   {

      return true;

   }

   if(pitem1->m_eelement != pitem2->m_eelement)
   {

      return false;

   }

   if(pitem1->m_iItem != pitem2->m_iItem)
   {

      return false;

   }

   if(pitem1->m_iSubItem != pitem2->m_iSubItem)
   {

      return false;

   }

   if(pitem1->m_iListItem != pitem2->m_iListItem)
   {

      return false;

   }

   if(pitem1->m_rectangle != pitem2->m_rectangle)
   {

      return false;

   }

   return true;

}



