// Created by camilo on 2024-08-26 20:06 ThomasBorregaardSorensen!!
// At an OpenBSD 7.5 box...
#include "framework.h"
#include "message_box.h"


void motif_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::motif::message_box, ::operating_system::message_box >();

}




