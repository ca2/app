//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSørensen!!
//
#pragma once


#include <xcb/xcb.h>


namespace xcb
{


   class event_listener :
      virtual public ::element
   {
   public:


      virtual bool _on_event(xcb_generic_event_t * pevent) = 0;


   };


} // namespace xcb



