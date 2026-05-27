//
// Created by camilo on 2026-04-12 04:44 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "notification_handler.h"
#include "Window.h"


namespace innate_subsystem
{
   
   
   ::innate_subsystem::WindowInterface* notification_handler::get_window_implementation()
   {

      auto pwindow = this->impl<WindowInterface>();

      return pwindow;

   }


   bool notification_handler::_001OnAction()
   {

      return false;

   }
   bool notification_handler::_001OnKeyDownNotification(::user::enum_key ekey)
   {

      return false;

   }
   bool notification_handler::_001OnColumnClick(::i32 iColumn)
   {

      return false;

   }
   bool notification_handler::_001OnSelectionChange()
   {

      return false;

   }

   bool notification_handler::_001OnTabChanged()
   {

      return false;

   }

   bool notification_handler::_001OnTabChanging(bool & bOk)
   {

      return false;

   }


   bool notification_handler::_001OnUpDown(::i32 iPos, ::i32 iDelta)
   {

      return false;

   }

   bool notification_handler::_002OnAction(::i32 iControl)
   {

      return false;

   }


   bool notification_handler::_002OnKeyDownNotification(::i32 iControl, ::user::enum_key ekey)
   {

      return false;

   }


   bool notification_handler::_002OnColumnClick(::i32 iControl, ::i32 iColumn)
   {

      return false;

   }


   bool notification_handler::_002OnSelectionChange(::i32 iControl)
   {

      return false;

   }

   bool notification_handler::_002OnTabChanged(::i32 iControl)
   {

      return false;

   }

   bool notification_handler::_002OnTabChanging(::i32 iControl, bool & bOk)
   {

      return false;

   }


   bool notification_handler::_002OnUpDown(::i32 iControl, ::i32 iPos, ::i32 iDelta)
   {

      return false;

   }

} // innate_subsystem