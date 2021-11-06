#pragma once


class xcb_hook :
virtual public ::matter
{
public:


   xcb_hook();


   virtual bool process_event(Display * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);

   ::e_status hook();
   ::e_status unhook();

   virtual void on_idle(Display * pdisplay);

};



