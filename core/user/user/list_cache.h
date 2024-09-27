#pragma once


#include "mesh_cache_interface.h"
#include "acme/prototype/collection/string_map.h"


namespace user
{


   class CLASS_DECL_CORE list_cache:
      virtual public mesh_cache_interface
   {
   public:


      index_to_index_to_string        m_map;


      list_cache();
      ~list_cache() override;


      void _001Invalidate(mesh * pmesh) override;

      void _001CacheHint(mesh * pmesh, ::collection::index iItemStart, ::collection::index iItemCount) override;

      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;


   };


} // namespace user





