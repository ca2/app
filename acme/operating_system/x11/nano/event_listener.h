//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSørensen!!
//
#pragma once


#include <X11/Xlib.h>
//#include "acme/primitive/primitive/element.h"


namespace x11
{


   class event_listener :
      virtual public ::particle
   {
   public:


      virtual bool _on_event(XEvent * pevent) = 0;


   };


} // namespace x11



