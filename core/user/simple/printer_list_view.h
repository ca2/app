#pragma once


class CLASS_DECL_CORE simple_printer_list_view :
   virtual public simple_list_view
{
public:


   __pointer(::user::impact)                   m_pimpact;


   simple_printer_list_view();
   virtual ~simple_printer_list_view();


   void install_message_routing(::channel * pchannel) override;

   virtual bool on_click(::item * pitem) override;

   DECLARE_MESSAGE_HANDLER(on_message_create);


};

