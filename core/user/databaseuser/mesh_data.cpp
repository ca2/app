#include "framework.h"
#include "mesh_data.h"
#include "apex/database/_binary_stream.h"


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


   void mesh_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      ::database::key key1;

      ::database::key key2;

      //if(Map(psubitem->m_pitem->m_pmesh, key1, key2, psubitem->m_pitem->m_iItem, psubitem->m_iSubItem, pitem->m_iListItem))
      if (Map(psubitem->m_pitem->m_pmesh, key1, key2, psubitem->m_pitem->m_iItem, psubitem->m_iSubItem, -1))
      {

         if(datastream()->get(key1 + key2, psubitem->m_strText))
         {

            return_(psubitem->m_bOk, true);

         }

      }

      return_(psubitem->m_bOk, false);

   }


   bool mesh_data::Map(::user::mesh * pmesh, ::database::key & key1, ::database::key & key2, index iItem, index iSubItem, index iListItem)
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



