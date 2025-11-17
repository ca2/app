#pragma once


#include "core/user/user/_.h"


namespace user
{


   class list;


   class CLASS_DECL_CORE mesh_cache_interface :
      virtual public ::object
   {
   public:


      mesh_cache_interface();
      ~mesh_cache_interface() override;


      virtual void _001CacheHint(mesh * pmesh, ::collection::index iItemStart, ::collection::count nItemCount) = 0;
      virtual void _001GetSubItemText(::user::mesh_subitem * psubitem) = 0;
      virtual void _001GetGroupItemText(::user::mesh_group * pgroup);

      
      virtual void _001Invalidate(mesh * pmesh);


   };


} // namespace user

