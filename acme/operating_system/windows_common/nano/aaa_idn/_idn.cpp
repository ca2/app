// Created by camilo on 2024-06-04 00:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "idn.h"


IMPLEMENT_FACTORY(nano_idn_windows_common)
{

   pfactory->add_factory_item < ::windows_common::nano::idn::idn, ::nano::idn::idn >();

}
