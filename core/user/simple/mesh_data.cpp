#include "framework.h"
#include "core/user/simple/_simple.h"


simple_mesh_data::simple_mesh_data()
{


}


simple_mesh_data::~simple_mesh_data()
{

}



void simple_mesh_data::_001GetSubItemText(::user::mesh_subitem * psubitem)
{

   if(psubitem->m_pitem->m_iItem < 0)
   {

      return_(psubitem->m_bOk,false);

   }

   auto passoc = m_map.plookup(psubitem->m_pitem->m_iItem);

   if(passoc != nullptr)
   {

      auto passoc2 = passoc->element2().plookup(psubitem->m_pcolumn->m_iColumn);

      if(passoc2 != nullptr)
      {

         psubitem->m_strText = passoc2->element2();

         return_(psubitem->m_bOk,true);

      }

   }

   return_(psubitem->m_bOk,false);

}


index simple_mesh_data::_001GetItemCount()
{

   return 32768;

}


::count simple_mesh_data::_001GetColumnCount(::user::mesh * pmesh)
{

   return 32768;

}


void simple_mesh_data::clear()
{

   m_map.erase_all();

}


