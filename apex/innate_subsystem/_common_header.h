//
// Created by camilo on 2026-04-07 18:36 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/subsystem/_common_header.h"



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


   class CLASS_DECL_APEX notification_handler :
      virtual public ::particle
   {
   public:


      virtual bool _001OnAction();
      virtual bool _001OnKeyDownNotification(::user::enum_key ekey);
      virtual bool _001OnColumnClick(int iColumn);
      virtual bool _001OnSelectionChange();



      virtual bool _002OnAction(int iControl);
      virtual bool _002OnKeyDownNotification(int iControl, ::user::enum_key ekey);
      virtual bool _002OnColumnClick(int iControl, int iColumn);
      virtual bool _002OnSelectionChange(int iControl);

   };

   template < typename PARTICLE_INTERFACE >
   class window_composite :
   virtual public ::subsystem::composite < PARTICLE_INTERFACE >,
   virtual public notification_handler
   {
      public:

   };

} // namespace innate_subsystem