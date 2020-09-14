#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   item & item::operator = (e_element eelement)
   {

      m_eelement = eelement;

      if (m_eelement != element_none)
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

         m_eelement = element_none;

      }
      else
      {

         if (m_eelement == element_none)
         {

            m_eelement = element_item;

         }

      }

      return *this;

   }


} // namespace user



