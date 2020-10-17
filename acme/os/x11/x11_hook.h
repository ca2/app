#pragma once


class x11_hook :
virtual public ::matter
{
public:



   x11_hook();


   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);

   ::estatus hook();
   ::estatus unhook();

   virtual void on_idle(Display * pdisplay);

};



