#pragma once


class CLASS_DECL_CORE simple_printer_list_view :
   virtual public simple_list_view
{
public:


   __pointer(::user::impact)                   m_pimpact;


   simple_printer_list_view();
   virtual ~simple_printer_list_view();


   virtual void install_message_routing(::channel * pchannel);

   virtual bool on_click(const ::item & item);

   DECLARE_MESSAGE_HANDLER(on_message_create);


};

