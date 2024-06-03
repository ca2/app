// Created by camilo on 2023-04-25 16:18 <3ThomasBorregaardSorensen!!
// From nano_archive_libarchive by camilo on 2024-06-02 17:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_idn_libidn.h"


IMPLEMENT_FACTORY(nano_idn_libidn)
{

   pfactory->add_factory_item< ::libidn::nano::idn::idn, ::nano::idn::idn >();

}



