#pragma once


namespace databaseuser
{


   class CLASS_DECL_CORE data_key_mesh_data :
      public ::user::mesh_data,
      public ::database::client
   {
   public:


      data_key_mesh_data();
      virtual ~data_key_mesh_data();


      virtual void assert_valid() const override;
      virtual void dump(dump_context& dumpcontext) const override;


      virtual void _001GetItemText(::user::mesh_item * pitem) override;

      virtual count _001GetItemCount() override;

      bool add_unique(const string_array & stra);
      bool erase(const string_array & stra);

      void GetSel(::user::list * plist , string_array & stra);


   };


} // namespace databaseuser



