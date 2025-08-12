#pragma once


#include "apex/database/client.h"
#include "core/user/user/mesh_data.h"


namespace databaseuser
{


   class CLASS_DECL_CORE data_key_mesh_data :
      virtual public ::user::mesh_data,
      virtual public ::database::client
   {
   public:


      data_key_mesh_data();
      ~data_key_mesh_data() override;


      // void assert_ok() const override;
      //void dump(dump_context& dumpcontext) const override;


      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;


      ::collection::count _001GetItemCount() override;

      bool add_unique(const string_array_base & stra);
      bool erase(const string_array_base & stra);

      void GetSel(::user::list_base * plist , string_array_base & stra);


   };


} // namespace databaseuser



