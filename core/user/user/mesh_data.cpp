#include "framework.h"
#include "mesh_data.h"
#include "acme/prototype/data/listener.h"


namespace user
{


   mesh_data::mesh_data()
   {

   }


   mesh_data::~mesh_data()
   {

   }


   ::collection::count mesh_data::_001GetItemCount()
   {
      
      return 0;

   }
   
   
   ::collection::count mesh_data::_001GetColumnCount(mesh * pmesh)
   {
      
      return 0;

   }

   
   void mesh_data::_001GetSubItemText(::user::mesh_subitem* psubitem)
   {

      psubitem->m_bOk = false;

   }


   void mesh_data::_001GetSubItemImage(::user::mesh_subitem * psubitem)
   {
      
      psubitem->m_bOk = false;

   }


   void mesh_data::_001GetSubItemColor(::user::mesh_subitem * psubitem)
   {
      
      psubitem->m_bOk = false;

   }


   void mesh_data::_001GetGroupItemText(::user::mesh_group * pgroup)
   {

      pgroup->m_bOk = false;

   }


   void mesh_data::_001GetGroupImage(::user::mesh_group * pgroup)
   {

      pgroup->m_bOk = false;

   }


   ::collection::count mesh_data::_001GetGroupCount()
   {
      return -1;
   }

   ::collection::count mesh_data::_001GetGroupMetaItemCount(::collection::index iGroup)
   {
      __UNREFERENCED_PARAMETER(iGroup);
      return 0;
   }


   void mesh_data::_001OnDeleteRange(::user::range & range)
   {

      __UNREFERENCED_PARAMETER(range);

   }


} // namespace user



