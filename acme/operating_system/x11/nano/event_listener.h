//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace x11
{


   class event_listener :
      virtual public ::element
   {
   public:


      virtual bool _on_event(XEvent * pevent) = 0;


   };


} // namespace x11



