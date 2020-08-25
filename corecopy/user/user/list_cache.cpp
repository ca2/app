#include "framework.h"


namespace user
{


   list_cache::list_cache()
   {

   }


   list_cache::~list_cache()
   {


   }


   void list_cache::_001CacheHint(      ::user::mesh * pmesh,      index iItemStart,      index iItemCount)
   {

      single_lock sl(mutex(), false);

      ::user::list * plist = pmesh->m_plist;

      if(iItemStart  < 0)
      {

         iItemStart = 0;

      }

      index iItem;

      index iColumn;

      string str;

      index iItemEnd = iItemStart + iItemCount - 1;

      draw_list_item item(plist);

      for(iItem = iItemStart; iItem <= iItemEnd; iItem++)
      {

         index_to_string & m = m_map[iItem];

         for(iColumn = 0; iColumn < plist->m_columna.get_count(); iColumn++)
         {

            item.m_iItem = iColumn;

            item.m_iSubItem = plist->m_columna.get_by_index(iColumn)->m_iSubItem;

            item.m_iListItem = -1;

            item.m_strText.Empty();

            item.m_bOk = false;

            try
            {

               plist->_001GetItemText(&item);

            }
            catch(...)
            {

               item.m_bOk = false;

            }

            if(item.m_bOk)
            {

               sl.lock();

               m.set_at(item.m_iSubItem,item.m_strText);

               sl.unlock();

            }

         }

      }

   }


   void list_cache::_001GetItemText(::user::mesh_item * pitem)
   {

      if(pitem->m_iItem < 0)
         return_(pitem->m_bOk,false);

      sync_lock sl(mutex());

      auto pmap = m_map.plookup(pitem->m_iItem);

      if(pmap == nullptr)
      {

         return_(pitem->m_bOk,false);

      }

      auto passoc = pmap->element2().plookup(pitem->m_iItem);

      if(passoc == nullptr)
      {

         return_(pitem->m_bOk,false);

      }

      pitem->m_strText = passoc->element2();

      pitem->m_bOk = true;

   }


   void list_cache::_001Invalidate(::user::mesh * pmesh)
   {

      sync_lock sl(mutex());

      m_map.remove_all();

   }


} // namespace user


