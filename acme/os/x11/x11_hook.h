#pragma once


class x11_hook :
virtual public ::element
{
public:



   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);

   ::estatus hook();
   ::estatus unhook();


};



