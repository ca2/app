#pragma once


#include "core/user/user/mesh_data.h"


namespace databaseuser
{


   class CLASS_DECL_CORE mesh_data :
      public ::user::mesh_data,
      public ::database::client
   {
   public:


      ::count m_iItemCount;


      mesh_data();
      virtual ~mesh_data();


      void assert_ok() const override;
      virtual void dump(dump_context& dumpcontext) const override;


      void _001GetSubItemText(::user::mesh_subitem * pitem) override;

      virtual count _001GetItemCount() override;

      virtual bool Map(::user::mesh * pmesh, ::database::key & key1, ::database::key & key2, index iItem, index iSubItem, index iListItem);


   };


} // namespace user



