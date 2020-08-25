#include "framework.h"


namespace user
{


   mesh_cache_interface::mesh_cache_interface()
   {

      defer_create_mutex();

   }


   mesh_cache_interface::~mesh_cache_interface()
   {

   }


   void mesh_cache_interface::_001GetGroupText(::user::mesh_item * pitem)
   {


      pitem->m_bOk = false;


   }


} // namespace user