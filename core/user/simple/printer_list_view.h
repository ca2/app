#pragma once


class CLASS_DECL_CORE simple_printer_list_view :
   virtual public simple_list_view
{
public:


   __pointer(::user::impact)                   m_pview;


   simple_printer_list_view();
   virtual ~simple_printer_list_view();


   virtual void install_message_routing(::channel * pchannel);

   virtual bool on_click(const ::user::item & item);

   DECL_GEN_SIGNAL(_001OnCreate);


};

