#pragma once


#include "core/user/user/mesh_data.h"
#include "apex/database/client.h"


namespace databaseuser
{


   class CLASS_DECL_CORE mesh_data :
      public ::user::mesh_data,
      public ::database::client
   {
   public:


      ::collection::count m_iItemCount;


      mesh_data();
      ~mesh_data() override;


      // void assert_ok() const override;
      // virtual void dump(dump_context& dumpcontext) const override;


      void _001GetSubItemText(::user::mesh_subitem * pitem) override;

      virtual ::collection::count _001GetItemCount() override;

      virtual bool Map(::user::mesh * pmesh, string & strDataKey1, string & strDataKey2, ::collection::index iItem, ::collection::index iSubItem, ::collection::index iListItem);


   };


} // namespace user



