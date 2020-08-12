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


      virtual void _001GetItemText(::user::mesh_item * pitem);

      virtual count _001GetItemCount();

      bool add_unique(const string_array & stra);
      bool remove(const string_array & stra);

      void GetSel(::user::list * plist , string_array & stra);


   };


} // namespace databaseuser



