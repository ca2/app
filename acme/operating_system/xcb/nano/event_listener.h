//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <xcb/xcb.h>


namespace xcb
{


   class event_listener :
      virtual public ::particle
   {
   public:


      virtual bool _on_event(xcb_generic_event_t * pevent) = 0;


   };


} // namespace xcb



