#pragma once


class CLASS_DECL_CORE simple_list_control :
   virtual public ::user::list
{
public:


   simple_list_control();


   virtual __pointer(::user::interaction) OnDrawInterfaceGetWnd();

   virtual bool pre_create_window(::user::create_struct& cs);
   virtual void pre_subclass_window();

   bool remove_item(i32 iItem);
   bool remove_item(::user::range & range);
   bool remove_item(::user::item_range & range);
   void get_data(string_array & stra);
   void set_data(string_array & stra);
   virtual ~simple_list_control();

   virtual void install_message_routing(::channel * pchannel);


};



