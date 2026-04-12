//
// Created by camilo on 2026-04-12 04:44 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace innate_subsystem
{


   class CLASS_DECL_APEX notification_handler :
      virtual public ::particle
   {
   public:


      virtual ::innate_subsystem::WindowInterface * get_window_implementation() = 0;

      virtual bool _001OnAction();
      virtual bool _001OnKeyDownNotification(::user::enum_key ekey);
      virtual bool _001OnColumnClick(int iColumn);
      virtual bool _001OnSelectionChange();



      virtual bool _002OnAction(int iControl);
      virtual bool _002OnKeyDownNotification(int iControl, ::user::enum_key ekey);
      virtual bool _002OnColumnClick(int iControl, int iColumn);
      virtual bool _002OnSelectionChange(int iControl);

   };

} // innate_subsystem




