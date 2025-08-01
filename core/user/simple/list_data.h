#pragma once


#include "core/user/user/list_data.h"


class CLASS_DECL_CORE simple_list_data:
   virtual public ::user::list_data
{
public:


   bool                                   m_bEnable;

   pointer_array < string_array >         m_array;


   simple_list_data();
   ~simple_list_data() override;


   bool erase_item(::collection::index iItem);
   void get_data(string_array & stra);
   void get_column_data(string_array & stra, ::collection::index iColumn);
   void set_data(::user::mesh * pmesh,string_array & stra);
   void set_column_data(::user::mesh * pmesh,string_array & stra, ::collection::index iColumn);
   void enable(bool bEnable);
   void set_item_text(::user::mesh * pmesh, ::collection::index iItem, ::collection::index iSubItem, const ::scoped_string & scopedstr);



   void _001GetSubItemText(::user::mesh_subitem * pitem) override;

   void _001OnDeleteRange(::user::range & range) override;


   virtual ::collection::count _001GetItemCount() override;

   void set_item_text(::collection::index iItem, ::collection::index iSubItem, const ::scoped_string & scopedstr);


};



