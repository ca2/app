#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_list_data :
      public ::user::list_data,
      public ::database::client
   {
   public:


      folder_list_data();
      virtual ~folder_list_data();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual void _001GetItemText(::user::mesh_item * pitem);

      virtual count _001GetItemCount();

      bool add_unique(const string_array & stra, int_array & iaRecursive);
      bool remove(const string_array & stra);

      void GetSel(::user::list * plist , string_array & stra);


   private:


      folder_list_data(const folder_list_data & )
      {
      }


   };


} // namespace filemanager



