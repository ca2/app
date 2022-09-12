#pragma once


#include "core/user/user/list_header.h"


class CLASS_DECL_CORE simple_list_header_control :
   virtual public ::user::list_header
{
public:


   static const i32         s_iDividerWidth;


   simple_list_header_control();
   virtual ~simple_list_header_control();


   //using ::user::list_header::create_window;
   //virtual bool create_window(u32 uStyle, ::user::interaction * puiParent, ::atom atom);


   void install_message_routing(::channel * pchannel) override;


   DECLARE_MESSAGE_HANDLER(_001OnEndTrack);
   DECLARE_MESSAGE_HANDLER(_001OnTrack);
   DECLARE_MESSAGE_HANDLER(_001OnEndDrag);
   DECLARE_MESSAGE_HANDLER(on_message_create);


};



