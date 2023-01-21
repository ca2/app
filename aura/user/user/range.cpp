#include "framework.h"
#include "range.h"
//#include "acme/primitive/collection/numeric_array.h"


namespace user
{


   range::range()
   {

   }


   range::range(const range& range)
   {

      m_itemrangea = range.m_itemrangea;

   }


   bool range::has_item(index iItem) const
   {

      for (index i = 0; i < m_itemrangea.get_size(); i++)
      {
         const auto& itemrange = m_itemrangea[i];
         if (itemrange.has_item(iItem))
            return true;
      }
      return false;
   }


   ::count range::get_item_indexes(index_array& ia) const
   {

      for (index i = 0; i < m_itemrangea.get_size(); i++)
      {

         const auto& itemrange = m_itemrangea[i];

         itemrange.get_item_indexes(ia);

      }

      return ia.get_size();

   }


   bool range::has_sub_item(index iItem, index iSubItem) const
   {

      for (index i = 0; i < m_itemrangea.get_size(); i++)
      {

         const auto& itemrange = m_itemrangea[i];

         if (itemrange.has_item(iItem))
         {

            if (itemrange.has_sub_item(iSubItem))
            {

               return true;

            }

         }

      }

      return false;

   }


   // erase the specified item
   bool range::erase_item(index iItem)
   {
      for (index i = 0; i < m_itemrangea.get_size();)
      {
         auto& itemrange = m_itemrangea[i];
         if (itemrange.has_item(iItem))
         {
            if (itemrange.get_lower_bound() == iItem)
            {
               itemrange.set_lower_bound(itemrange.get_lower_bound() + 1);
               if (itemrange.get_lower_bound() > itemrange.get_upper_bound())
               {
                  m_itemrangea.erase_at(i);
                  continue;
               }
            }
            else if (itemrange.get_upper_bound() == iItem)
            {
               itemrange.set_upper_bound(itemrange.get_upper_bound() - 1);
            }
            else
            {
               // split the current range as it will be segmented
               item_range itemrangeL;
               item_range itemrangeU;
               itemrangeL = itemrange;
               itemrangeU = itemrange;
               itemrangeL.set_upper_bound(iItem - 1);
               itemrangeU.set_lower_bound(iItem + 1);
               m_itemrangea.erase_at(i);
               m_itemrangea.add(itemrangeL);
               m_itemrangea.add(itemrangeU);
               continue;
            }
         }
         i++;
      }
      return false;
   }

   // erase the specified item and offset remaining items.
   bool range::OnRemoveItem(index iItem)
   {
      erase_item(iItem);
      // All ranges that has item "iItem + 1",
      // must have all items greater or equal "iItem + 1"
      // decremented by one
      iItem++;
      for (index i = 0; i < m_itemrangea.get_size();)
      {
         auto& itemrange = m_itemrangea[i];
         if (itemrange.has_item(iItem))
         {
            if (itemrange.get_lower_bound() >= iItem)
            {
               itemrange.offset(-1);
            }
            else if (itemrange.get_upper_bound() >= iItem)
            {
               itemrange.set_upper_bound(itemrange.get_upper_bound() - 1);
            }
         }
         i++;
      }
      return false;
   }

   void item_range::get_item_indexes(index_array& ia) const
   {

      if (m_iLowerBound == -1 || m_iUpperBound == -1)
         return;

      for (index iItem = m_iLowerBound; iItem <= m_iUpperBound; iItem++)
      {

         ia.add_unique(iItem);

      }

   }

   bool item_range::has_item(index iItem) const
   {
      if (m_iLowerBound == -1 || m_iUpperBound == -1)
         return false;
      if (iItem >= m_iLowerBound
         && iItem <= m_iUpperBound)
         return true;
      else
         return false;
   }

   bool item_range::has_sub_item(index iSubItem) const
   {
      return m_subitemrange.has_sub_item(iSubItem);
   }

   //void mesh::LayoutHeaderCtrl()
   //{

   //   if(m_pmeshheader == nullptr)
   //      return;

   //   if(m_bHeaderCtrl)
   //   {
   //      ::rectangle_i32 rectangleClient;

   //      client_rectangle(&rectangleClient);

   //      m_pmeshheader->set_window_position(
   //         e_zorder_top,
   //         0,0,
   //         maximum(m_iItemWidth + 10,rectangleClient.width()),
   //         m_iItemHeight,
   //         SWP_SHOWWINDOW);
   //   }
   //   else
   //   {
   //      m_pmeshheader->display(e_display_none);
   //   }
   //}


   sub_item_range::sub_item_range()
   {
      m_iLowerBound = -1;
      m_iUpperBound = -1;
   }

   sub_item_range::sub_item_range(const sub_item_range& subitemrange)
   {
      operator =(subitemrange);
   }


   sub_item_range& sub_item_range::operator =(const sub_item_range& subitemrange)
   {

      m_iLowerBound = subitemrange.m_iLowerBound;
      m_iUpperBound = subitemrange.m_iUpperBound;
      m_listitemrange = subitemrange.m_listitemrange;

      return *this;

   }


   bool sub_item_range::has_sub_item(index iSubItem) const
   {
      if (m_iLowerBound == -1 || m_iUpperBound == -1)
         return false;
      if (iSubItem >= m_iLowerBound
         && iSubItem <= m_iUpperBound)
         return true;
      else
         return false;
   }




   void item_range::set(index iLowerBoundItem, index iUpperBoundItem, index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem)
   {

      m_iLowerBound = iLowerBoundItem;
      m_iUpperBound = iUpperBoundItem;
      m_subitemrange.set(
         iLowerBoundSubItem,
         iUpperBoundSubItem,
         iLowerBoundListItem,
         iUpperBoundListItem);
   }

   void item_range::set_lower_bound(index iLowerBoundItem)
   {
      m_iLowerBound = iLowerBoundItem;
   }

   void item_range::set_upper_bound(index iUpperBoundItem)
   {
      m_iUpperBound = iUpperBoundItem;
   }

   void sub_item_range::set(index iLowerBoundSubItem, index iUpperBoundSubItem, index iLowerBoundListItem, index iUpperBoundListItem)
   {
      m_iLowerBound = iLowerBoundSubItem;
      m_iUpperBound = iUpperBoundSubItem;
      m_listitemrange.set(
         iLowerBoundListItem,
         iUpperBoundListItem);
   }

   void list_item_range::set(index iLowerBoundListItem, index iUpperBoundListItem)
   {
      m_iLowerBound = iLowerBoundListItem;
      m_iUpperBound = iUpperBoundListItem;

   }


   void range::clear()
   {
      m_itemrangea.erase_all();
   }

   void range::add_item(const item_range& itemrange)
   {
      m_itemrangea.add(itemrange);
   }

   item_range::item_range()
   {
      m_iLowerBound = -1;
      m_iUpperBound = -1;
   }

   index item_range::get_lower_bound() const
   {
      return m_iLowerBound;
   }

   index item_range::get_upper_bound() const
   {
      return m_iUpperBound;
   }



   item_range::item_range(const item_range& itemrange)
   {
      operator =(itemrange);
   }

   item_range& item_range::operator =(const item_range& itemrange)
   {
      m_iLowerBound = itemrange.m_iLowerBound;
      m_iUpperBound = itemrange.m_iUpperBound;
      m_subitemrange = itemrange.m_subitemrange;
      return *this;
   }




   void item_range::offset(index iOffset)
   {

      m_iLowerBound += iOffset;
      m_iUpperBound += iOffset;

   }





   range& range::operator = (const range& range)
   {
      m_itemrangea.copy(range.m_itemrangea);
      return *this;
   }

   ::index range::get_current_item()
   {

      if(m_itemrangea.get_count() != 1)
      {

         return -1;

      }

      auto & itemrange = m_itemrangea[0];

      if(itemrange.m_iLowerBound != itemrange.m_iUpperBound)
      {

         return -1;

      }

      if(itemrange.m_iLowerBound < 0)
      {

         return -1;

      }

      return itemrange.m_iLowerBound;

   }


   ::count range::get_item_count() const
   {
      return m_itemrangea.get_size();
      /*   index iCount = 0;

      for(index i = 0; i < m_itemrangea.get_size(); i++)
      {
      auto & itemrange = m_itemrangea[i];
      iCount += itemrange.get_count();
      }

      return iCount;*/
   }

   ::count range::get_items(index_array& ia) const
   {
      return get_item_indexes(ia);
      /*   index iCount = 0;

      for(index i = 0; i < m_itemrangea.get_size(); i++)
      {
      auto & itemrange = m_itemrangea[i];
      iCount += itemrange.get_count();
      }

      return iCount;*/
   }

   item_range& range::ItemAt(index iItem)
   {
      return m_itemrangea.element_at(iItem);
   }




} // namespace user



