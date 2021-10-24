#pragma once


class CLASS_DECL_CORE simple_list_control :
   virtual public ::user::list
{
public:


   simple_list_control();


   virtual __pointer(::user::interaction) OnDrawInterfaceGetWnd();

   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void pre_subclass_window() override;

   bool erase_item(i32 iItem);
   bool erase_item(::user::range & range);
   bool erase_item(::user::item_range & range);
   void get_data(string_array & stra);
   void set_data(string_array & stra);
   virtual ~simple_list_control();

   void install_message_routing(::channel * pchannel) override;


};



