#include "framework.h"
#include "mesh_data.h"
#include "acme/primitive/data/listener.h"
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


   void mesh_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
   {

      ::string strDataKey1;

      ::string strDataKey2;

      //if(Map(psubitem->m_pitem->m_pmesh, key1, key2, psubitem->m_pitem->m_iItem, psubitem->m_iSubItem, pitem->m_item.m_iListItem))
      if (Map(psubitem->m_pitem->m_pmesh, strDataKey1, strDataKey2, psubitem->m_pitem->m_iItem, psubitem->m_iSubItem, -1))
      {

         if(datastream()->get(strDataKey1 + strDataKey2, psubitem->m_strText))
         {

            return_(psubitem->m_bOk, true);

         }

      }

      return_(psubitem->m_bOk, false);

   }


   bool mesh_data::Map(::user::mesh * pmesh, ::string & strDataKey1, ::string & strDataKey2, index iItem, index iSubItem, index iListItem)
   {

      UNREFERENCED_PARAMETER(pmesh);

      // default implementation

      strDataKey1.formatf("%d", iSubItem);

      strDataKey2.formatf("%d.%d", iItem, iListItem);

      return true;

   }


   ::count mesh_data::_001GetItemCount()
   {

      return m_iItemCount;

   }


} // namespace guibase



