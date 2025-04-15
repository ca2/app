//
// Created by camilo on 2025-03-31 03:41 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/handler/item.h"
#include "acme/user/user/item_base.h"


template < prototype_item ITEM>
class simple_item_base :
   virtual public ::user::item_base
{
public:


   ::pointer < ITEM > m_pitem;


   simple_item_base()
   {


   }


   ~simple_item_base() override
   {


   }


   ::item * _item() override
   {

      return m_pitem;

   }


   void _set_item(::item * pitem) override
   {

      m_pitem = pitem;

   }


};



