#include "framework.h"
#include "core/user/simple/_simple.h"


simple_mesh_data::simple_mesh_data()
{


}


simple_mesh_data::~simple_mesh_data()
{

}



void simple_mesh_data::_001GetItemText(::user::mesh_item * pitem)
{

   if(pitem->m_iItem < 0)
   {

      return_(pitem->m_bOk,false);

   }

   auto passoc = m_map.plookup(pitem->m_iItem);

   if(passoc != nullptr)
   {

      auto passoc2 = passoc->element2().plookup(pitem->m_iColumn);

      if(passoc2 != nullptr)
      {

         pitem->m_strText = passoc2->element2();

         return_(pitem->m_bOk,true);

      }

   }


   return_(pitem->m_bOk,false);

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

   m_map.remove_all();

}


