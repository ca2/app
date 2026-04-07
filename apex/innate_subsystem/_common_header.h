//
// Created by camilo on 2026-04-07 18:36 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/subsystem/_common_header.h"



namespace innate_subsystem
{
   struct draw_item_t {
      unsigned int        CtlType;
      unsigned int        CtlID;
      unsigned int        itemID;
      unsigned int        itemAction;
      unsigned int        itemState;
      ::operating_system::window        operatingsystemwindowItem;
      DeviceContextInterface * m_pdevicecontext;
      ::int_rectangle & m_rectangleItem;
      ::uptr   itemData;
   };


} // namespace innate_subsystem