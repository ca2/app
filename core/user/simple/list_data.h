#pragma once


class CLASS_DECL_CORE simple_list_data:
   virtual public ::user::list_data
{
public:


   bool                 m_bEnable;

   __pointer_array(string_array)         m_array;


   simple_list_data();
   virtual ~simple_list_data();


   bool erase_item(index iItem);
   void get_data(string_array & stra);
   void get_column_data(string_array & stra,index iColumn);
   void set_data(::user::mesh * pmesh,string_array & stra);
   void set_column_data(::user::mesh * pmesh,string_array & stra,index iColumn);
   void enable(bool bEnable);
   void set_item_text(::user::mesh * pmesh,index iItem,index iSubItem, const ::string & pcsz);



   virtual void _001GetItemText(::user::mesh_item * pitem) override;

   virtual void _001OnDeleteRange(::user::range & range) override;


   virtual ::count _001GetItemCount() override;

   void set_item_text(index iItem, index iSubItem, const ::string & pcsz);


};



