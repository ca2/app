#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_list_data :
      virtual public ::user::list_data,
      virtual protected ::database::client
   {
   public:


      folder_list_data();
      virtual ~folder_list_data();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      ::e_status on_initialize_object() override;

      using ::database::client::set_data_key_modifier;

      virtual void _001GetItemText(::user::mesh_item * pitem) override;

      virtual count _001GetItemCount() override;

      virtual bool add_unique(const string_array & stra, i32_array & iaRecursive);
      virtual bool erase(const string_array & stra);

      virtual void GetSel(::user::list * plist , string_array & stra);

      virtual bool set_recursive(::index iItem, bool bRecursive);


   };


} // namespace filemanager



