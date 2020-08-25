#pragma once


namespace user
{


   class CLASS_DECL_CORE list_cache:
      virtual public mesh_cache_interface
   {
   public:



      index_to_index_to_string        m_map;


      list_cache();
      virtual ~list_cache();


      void _001Invalidate(mesh * pmesh);

      virtual void _001CacheHint(mesh * pmesh, index iItemStart, index iItemCount);

      virtual void _001GetItemText(::user::mesh_item * pitem);


   };


} // namespace user





