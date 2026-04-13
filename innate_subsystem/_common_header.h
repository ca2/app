//
// Created by camilo on 2026-04-07 18:36 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "subsystem/_common_header.h"


#include "innate_subsystem/gui/notification_handler.h"


namespace innate_subsystem
{

   class DeviceContextInterface;
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


   enum enum_control
   {

      e_control_none,
      e_control_list_view,

   };



   template < typename PARTICLE_INTERFACE >
   class window_composite :
   virtual public ::subsystem::composite < PARTICLE_INTERFACE >,
   virtual public notification_handler
   {
      public:

   };

} // namespace innate_subsystem