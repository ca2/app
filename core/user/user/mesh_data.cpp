#include "framework.h"
#include "core/user/user/_user.h"


namespace user
{


   mesh_data::mesh_data()
   {

   }


   mesh_data::~mesh_data()
   {

   }


   count mesh_data::_001GetItemCount()
   {
      
      return 0;

   }
   
   
   count mesh_data::_001GetColumnCount(mesh * pmesh)
   {
      
      return 0;

   }

   void mesh_data::_001GetItemText(::user::mesh_item* pitem)
   {
      pitem->m_bOk = false;
   }

   void mesh_data::_001GetItemImage(::user::mesh_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void mesh_data::_001GetItemColor(::user::mesh_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void mesh_data::_001GetGroupText(::user::mesh_item * pitem)
   {
      pitem->m_bOk = false;
   }

   void mesh_data::_001GetGroupImage(::user::mesh_item * pitem)
   {
      pitem->m_bOk = false;
   }

   ::count mesh_data::_001GetGroupCount()
   {
      return -1;
   }

   ::count mesh_data::_001GetGroupMetaItemCount(index iGroup)
   {
      __UNREFERENCED_PARAMETER(iGroup);
      return 0;
   }


   void mesh_data::_001OnDeleteRange(::user::range & range)
   {

      __UNREFERENCED_PARAMETER(range);

   }


} // namespace user



