#pragma once


#include "list_impact.h"


class CLASS_DECL_CORE simple_printer_list_impact :
   virtual public simple_list_impact
{
public:


   ::pointer<::user::impact>                   m_pimpact;


   simple_printer_list_impact();
   virtual ~simple_printer_list_impact();


   void install_message_routing(::channel * pchannel) override;

   bool on_click(::item * pitem, ::user::mouse * pmouse) override;

   DECLARE_MESSAGE_HANDLER(on_message_create);


};

