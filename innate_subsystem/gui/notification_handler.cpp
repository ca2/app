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
   bool notification_handler::_001OnColumnClick(int iColumn)
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


   bool notification_handler::_001OnUpDown(int iPos, int iDelta)
   {

      return false;

   }

   bool notification_handler::_002OnAction(int iControl)
   {

      return false;

   }


   bool notification_handler::_002OnKeyDownNotification(int iControl, ::user::enum_key ekey)
   {

      return false;

   }


   bool notification_handler::_002OnColumnClick(int iControl, int iColumn)
   {

      return false;

   }


   bool notification_handler::_002OnSelectionChange(int iControl)
   {

      return false;

   }

   bool notification_handler::_002OnTabChanged(int iControl)
   {

      return false;

   }

   bool notification_handler::_002OnTabChanging(int iControl, bool & bOk)
   {

      return false;

   }


   bool notification_handler::_002OnUpDown(int iControl, int iPos, int iDelta)
   {

      return false;

   }

} // innate_subsystem