#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/simple/_simple.h"
#endif


simple_list_data::simple_list_data()
{
   m_bEnable = true;
}

simple_list_data::~simple_list_data()
{

}

void simple_list_data::_001GetItemText(::user::mesh_item * pitem)
{

   if(!m_bEnable)
      return_(pitem->m_bOk,false);

   if(pitem->m_iSubItem < 0)
      return_(pitem->m_bOk,false);

   if(pitem->m_iSubItem >= m_array.get_size())
      return_(pitem->m_bOk,false);

   string_array & stra = m_array(pitem->m_iSubItem);

   if(pitem->m_iItem < 0)
      return_(pitem->m_bOk,false);

   if(pitem->m_iItem >= stra.get_size())
      return_(pitem->m_bOk,false);


   pitem->m_strText = stra.element_at(pitem->m_iItem);

   pitem->m_bOk = true;


}


void simple_list_data::set_item_text(index iItem,index iSubItem,const char * pcsz)
{

   while(iSubItem >= m_array.get_size())
   {
      m_array.add(new string_array());
   }

   m_array[iSubItem]->set_at_grow(iItem,pcsz);


}

void simple_list_data::set_item_text(::user::mesh * pmesh,index iItem,index iSubItem,const char * pcsz)

{

   set_item_text(iItem,iSubItem,pcsz);


   pmesh->_001OnUpdateItemCount();

}

void simple_list_data::Enable(bool bEnable)
{
   m_bEnable = bEnable;
}


void simple_list_data::get_column_data(string_array & stra,index iColumn)
{
   stra = m_array[iColumn];

}


void simple_list_data::get_data(string_array &stra)
{

   get_column_data(stra,0);

}


void simple_list_data::set_column_data(::user::mesh * pmesh,string_array & stra,index iColumn)
{
   m_array.set_at_grow(iColumn,new string_array(stra));
   for(i32 iSubItem = 0; iSubItem < m_array.get_count(); iSubItem++)
   {
      if(iColumn != iSubItem)
      {
         m_array[iSubItem]->set_size(stra.get_count());
      }
   }
   pmesh->_001OnUpdateItemCount();

}


void simple_list_data::set_data(::user::mesh * pmesh,string_array &stra)
{

   set_column_data(pmesh,stra,0);

}


bool simple_list_data::remove_item(index iItem)
{

   if(iItem < 0)
      return false;
   if(iItem >= m_array.get_size())
      return false;
   for(i32 iSubItem = 0; iSubItem < m_array.get_size(); iSubItem++)
   {
      m_array[iSubItem]->remove_at(iItem);
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

   m_array._001RemoveIndexes(ia);

}



