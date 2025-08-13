#pragma once


#include "core/user/user/list.h"


class CLASS_DECL_CORE simple_list_control :
   virtual public ::user::list
{
public:


   simple_list_control();


   virtual ::pointer<::user::interaction>OnDrawInterfaceGetWnd();

   virtual bool pre_create_window(::user::system * pusersystem) override;
   virtual void pre_subclass_window() override;

   bool erase_item(int iItem);
   bool erase_item(::user::range & range);
   bool erase_item(::user::item_range & range);
   void get_data(string_array_base & stra);
   void set_data(string_array_base & stra);
   virtual ~simple_list_control();

   void install_message_routing(::channel * pchannel) override;


};



