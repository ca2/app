#include "framework.h"
#include "mesh_cache_interface.h"
#include "mesh_item.h"


namespace user
{


   mesh_cache_interface::mesh_cache_interface()
   {

      defer_create_synchronization();

   }


   mesh_cache_interface::~mesh_cache_interface()
   {

   }


   void mesh_cache_interface::_001GetGroupItemText(::user::mesh_group * pgroup)
   {


      pgroup->m_bOk = false;


   }


   void mesh_cache_interface::_001Invalidate(mesh * pmesh)
   {

   }


} // namespace user



