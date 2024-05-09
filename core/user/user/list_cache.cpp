#include "framework.h"
#include "list_cache.h"
#include "mesh.h"
#include "mesh_item.h"
#include "list.h"
#include "list_column.h"
#include "list_column_array.h"
#include "acme/parallelization/synchronous_lock.h"


namespace user
{


   list_cache::list_cache()
   {

   }


   list_cache::~list_cache()
   {


   }


   void list_cache::_001CacheHint(::user::mesh * pmesh, ::collection::index iItemStart, ::collection::index iItemCount)
   {

      single_lock synchronouslock(synchronization(), false);

      ::user::list * plist = pmesh->m_plist;

      if(iItemStart  < 0)
      {

         iItemStart = 0;

      }

      ::collection::index iItem;

      ::collection::index iColumn;

      string str;

      ::collection::index iItemEnd = iItemStart + iItemCount - 1;

      for(iItem = iItemStart; iItem <= iItemEnd; iItem++)
      {

         index_to_string & m = m_map[iItem];

         for(iColumn = 0; iColumn < plist->m_pcolumna->get_count(); iColumn++)
         {

            auto iSubItem = plist->m_pcolumna->get_by_index(iColumn)->m_iSubItem;

            auto & psubitem = plist->get_subitem(iItem, iSubItem);

            //psubitem->m_iListItem = -1;

            psubitem->m_strText.empty();

            psubitem->m_bOk = false;

            try
            {

               plist->_001GetSubItemText(psubitem);

            }
            catch(...)
            {

               psubitem->m_bOk = false;

            }

            if(psubitem->m_bOk)
            {

               synchronouslock.lock();

               m.set_at(psubitem->m_iSubItem, psubitem->m_strText);

               synchronouslock.unlock();

            }

         }

      }

   }


   void list_cache::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      if (psubitem->m_pitem->m_iItem < 0)
      {

         return_(psubitem->m_bOk, false);

      }

      synchronous_lock synchronouslock(this->synchronization());

      auto pmap = m_map.plookup(psubitem->m_pitem->m_iItem);

      if(!pmap)
      {

         return_(psubitem->m_bOk,false);

      }

      auto passoc = pmap->element2().plookup(psubitem->m_pitem->m_iItem);

      if(!passoc)
      {

         return_(psubitem->m_bOk,false);

      }

      psubitem->m_strText = passoc->element2();

      psubitem->m_bOk = true;

   }


   void list_cache::_001Invalidate(::user::mesh * pmesh)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_map.erase_all();

   }


} // namespace user


