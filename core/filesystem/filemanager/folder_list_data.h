#pragma once


#include "core/user/user/list_data.h"
#include "apex/database/client.h"


namespace filemanager
{


   class CLASS_DECL_CORE folder_list_data :
      virtual public ::user::list_data,
      virtual protected ::database::client
   {
   public:


      folder_list_data();
      ~folder_list_data() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void on_initialize_particle() override;

      using ::database::client::set_data_key_modifier;

      void _001GetSubItemText(::user::mesh_subitem * pitem) override;

      virtual count _001GetItemCount() override;

      virtual bool add_unique(const string_array& stra);
      virtual bool add_unique(const string_array & stra, i32_array & iaRecursive);
      virtual bool erase(const string_array & stra);

      virtual void GetSel(::user::list * plist , string_array & stra);

      virtual bool set_recursive(::index iItem, bool bRecursive);

      virtual bool get_recursive(::index iItem);


   };


} // namespace filemanager



