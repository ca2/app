#pragma once


class CLASS_DECL_CORE simple_list_header_control :
   virtual public ::user::list_header
{
public:


   static const i32         s_iDividerWidth;


   simple_list_header_control();
   virtual ~simple_list_header_control();


   using ::user::list_header::create_window;
   virtual bool create_window(u32 uStyle, ::user::interaction * puiParent, ::id id);


   virtual void install_message_routing(::channel * pchannel);


   DECL_GEN_SIGNAL(_001OnEndTrack);
   DECL_GEN_SIGNAL(_001OnTrack);
   DECL_GEN_SIGNAL(_001OnEndDrag);
   DECL_GEN_SIGNAL(_001OnCreate);


};



