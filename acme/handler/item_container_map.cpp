// From acme/user/user/container.h by camilo on 2023-07-21 12:33 <3ThomasBorregaardSorensen!!
// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "item_container_map.h"


item_container_map::item_container_map()
{

}


item_container_map::~item_container_map()
{

}


void item_container_map::destroy()
{


   m_itemcontainermap.clear();

   ::item::destroy();

}


::pointer < ::item_container > item_container_map::item_container(::index iId)
{

   return m_itemcontainermap[iId];

}



