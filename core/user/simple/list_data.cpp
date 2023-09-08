#include "framework.h"
#include "acme/primitive/collection/_function.h"
#include "acme/primitive/data/listener.h"
#include "core/user/simple/list_data.h"
#include "core/user/user/mesh.h"


simple_list_data::simple_list_data()
{

   m_bEnable = true;

}


simple_list_data::~simple_list_data()
{


}


void simple_list_data::_001GetSubItemText(::user::mesh_subitem * pmeshsubitem)
{

   if (!m_bEnable)
   {
    
      return_(pmeshsubitem->m_bOk, false);

   }

   if (pmeshsubitem->m_iSubItem < 0)
   {

      return_(pmeshsubitem->m_bOk, false);

   }

   if (pmeshsubitem->m_iSubItem >= m_array.get_size())
   {
    
      return_(pmeshsubitem->m_bOk, false);

   }

   string_array & stra = m_array(pmeshsubitem->m_iSubItem);

   auto pmeshitem = pmeshsubitem->m_pitem;

   if (pmeshitem->m_iItem < 0)
   {

      return_(pmeshsubitem->m_bOk, false);

   }

   if (pmeshitem->m_iItem >= stra.get_size())
   {

      return_(pmeshsubitem->m_bOk, false);

   }

   pmeshsubitem->m_strText = stra.element_at(pmeshitem->m_iItem);

   pmeshsubitem->m_bOk = true;

}


void simple_list_data::set_item_text(index iItem,index iSubItem, const ::string & pcsz)
{

   while(iSubItem >= m_array.get_size())
   {
      m_array.add(memory_new string_array());
   }

   m_array[iSubItem]->set_at_grow(iItem,pcsz);


}

void simple_list_data::set_item_text(::user::mesh * pmesh,index iItem,index iSubItem, const ::string & pcsz)
{

   set_item_text(iItem,iSubItem,pcsz);

   pmesh->update_impact();

}


void simple_list_data::enable(bool bEnable)
{

   m_bEnable = bEnable;

}


void simple_list_data::get_column_data(string_array & stra,index iColumn)
{

   stra = *m_array[iColumn];

}


void simple_list_data::get_data(string_array &stra)
{

   get_column_data(stra,0);

}


void simple_list_data::set_column_data(::user::mesh * pmesh,string_array & stra,index iColumn)
{
   m_array.set_at_grow(iColumn,memory_new string_array(stra));
   for(i32 iSubItem = 0; iSubItem < m_array.get_count(); iSubItem++)
   {
      if(iColumn != iSubItem)
      {
         m_array[iSubItem]->set_size(stra.get_count());
      }
   }

   pmesh->update_impact();

}


void simple_list_data::set_data(::user::mesh * pmesh,string_array &stra)
{

   set_column_data(pmesh,stra,0);

}


bool simple_list_data::erase_item(index iItem)
{

   if(iItem < 0)
      return false;
   if(iItem >= m_array.get_size())
      return false;
   for(i32 iSubItem = 0; iSubItem < m_array.get_size(); iSubItem++)
   {
      m_array[iSubItem]->erase_at(iItem);
   }
   return true;
}


::count simple_list_data::_001GetItemCount()
{

   if(m_array.get_size() <= 0)
      return 0;
   else
      return m_array[0]->get_size();

}


void simple_list_data::_001OnDeleteRange(::user::range & range)
{

   index_array ia;

   range.get_item_indexes(ia);

   _001RemoveIndexes(m_array, ia);

}



