#include "framework.h"
#include "core/user/databaseuser/_databaseuser.h"


namespace databaseuser
{


   mesh_data::mesh_data()
   {

      m_iItemCount = 0;

   }


   mesh_data::~mesh_data()
   {

   }


   void mesh_data::assert_ok() const
   {

   }


   void mesh_data::dump(dump_context& dumpcontext) const
   {

   }


   void mesh_data::_001GetItemText(::user::mesh_item * pitem)
   {

      ::database::key key1;

      ::database::key key2;

      if(Map(pitem->m_pmesh, key1, key2, pitem->m_iItem, pitem->m_iSubItem, pitem->m_iListItem))
      {

         if(data_get(key1 + key2, pitem->m_strText))
         {

            return_(pitem->m_bOk, true);

         }

      }

      return_(pitem->m_bOk, false);

   }

   bool mesh_data::Map(
   ::user::mesh * pmesh,
   ::database::key & key1,
   ::database::key & key2,
   index iItem,
   index iSubItem,
   index iListItem)
   {

      __UNREFERENCED_PARAMETER(pmesh);

      // default implementation

      key1.m_strDataKey.format("%d", iSubItem);

      key2.m_strDataKey.format("%d.%d", iItem, iListItem);

      return true;

   }


   ::count mesh_data::_001GetItemCount()
   {

      return m_iItemCount;

   }


} // namespace guibase



