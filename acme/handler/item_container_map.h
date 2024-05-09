// From acme/user/user/container.h by camilo on 2023-07-21 12:05 <3ThomasBorregaardSorensen!!
// Created by camilo on 2023-07-18 13:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "item_container.h"
#include "acme/primitive/collection/int_map.h"


class CLASS_DECL_ACME item_container_map :
   virtual public ::item
{
public:


   ::index_map < ::pointer < ::item_container > > m_itemcontainermap;


   item_container_map();
   ~item_container_map() override;


   void destroy() override;


   virtual ::pointer < ::item_container > item_container(::collection::index iId);


   //virtual bool is_item_pressed(const ::item_t & item) const;

   //virtual bool is_item_hover(const ::item_t & item) const;



};


