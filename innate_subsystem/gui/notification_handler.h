//
// Created by camilo on 2026-04-12 04:44 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace innate_subsystem
{


   class CLASS_DECL_INNATE_SUBSYSTEM notification_handler :
      virtual public ::Particle
   {
   public:


      virtual ::innate_subsystem::WindowInterface * get_window_implementation();

      virtual bool _001OnAction();
      virtual bool _001OnKeyDownNotification(::user::enum_key ekey);
      virtual bool _001OnColumnClick(int iColumn);
      virtual bool _001OnSelectionChange();
      virtual bool _001OnTabChanged();
      virtual bool _001OnTabChanging(bool & bOk);
      virtual bool _001OnUpDown(int iPos, int iDelta);



      virtual bool _002OnAction(int iControl);
      virtual bool _002OnKeyDownNotification(int iControl, ::user::enum_key ekey);
      virtual bool _002OnColumnClick(int iControl, int iColumn);
      virtual bool _002OnSelectionChange(int iControl);
      virtual bool _002OnTabChanged(int iControl);
      virtual bool _002OnTabChanging(int iControl, bool & bOk);
      virtual bool _002OnUpDown(int iControl, int iPos, int iDelta);

   };


   template<typename AGGREGATE >
   class WindowObject : virtual public Object < AGGREGATE >,
   virtual public ::innate_subsystem::notification_handler
   {
   public:
      using INTERFACE_TYPE = AGGREGATE::MAIN_AGGREGATE_INTERFACE_TYPE;
   };



} // innate_subsystem




