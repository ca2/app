#pragma once


#include "core/user/user/list_data.h"
#include "apex/database/client.h"


namespace filemanager
{


   namespace folder
   {


      class CLASS_DECL_CORE list_data :
         virtual public ::user::list_data,
         virtual protected ::database::client
      {
      public:


         list_data();
         ~list_data() override;


         //      // void assert_ok() const override;
         //      // void dump(dump_context & dumpcontext) const override;


         void on_initialize_particle() override;

         using ::database::client::set_data_key_modifier;

         void _001GetSubItemText(::user::mesh_subitem * pitem) override;

         virtual ::collection::count _001GetItemCount() override;

         virtual bool add_unique(const string_array_base & stra);
         virtual bool add_unique(const string_array_base & stra, int_array_base & iaRecursive);
         virtual bool erase(const string_array_base & stra);

         virtual void GetSel(::user::list_base * plist, string_array_base & stra);

         virtual bool set_recursive(::collection::index iItem, bool bRecursive);

         virtual bool get_recursive(::collection::index iItem);


      };


   } // namespace folder


} // namespace filemanager



