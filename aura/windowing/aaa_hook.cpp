// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "_windowing.h"


namespace windowing
{


   hook::hook()
   {

   }


   pointer_array < hook > g_x11hooka;


   void hook::do_hook()
   {


      auto pwindowing = ::auraacmesystem()->windowing();

      auto estatus = pwindowing->hook(this);

      if(!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void hook::unhook()
   {

      auto pwindowing = ::auraacmesystem()->windowing();

      auto estatus = pwindowing->unhook(this);

      if(!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   void hook::on_idle(display *pdisplay)
   {

   }




#if !defined(RASPBERRYPIOS)

   bool x11_process_event(display *pdisplay, void * pevent, void *cookie);

#else

   bool x11_process_event(display * pdisplay, void * pevent);

#endif


   bool hook::process_event(display *pdisplay, event * pevent)
   {

      return false;

   }




} // namespace windowing




