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


      count _001GetItemCount() override;

      bool add_unique(const string_array & stra);
      bool erase(const string_array & stra);

      void GetSel(::user::list * plist , string_array & stra);


   };


} // namespace databaseuser



