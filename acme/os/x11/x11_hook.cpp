#include "framework.h"
#include "_x11.h"


__pointer_array(x11_hook) * g_px11hooka;

void x11_hook_init()
{

  g_px11hooka = new __pointer_array(x11_hook);

}


void x11_hook_term()
{

   ::acme::del(g_px11hooka);

}

//LPFN_X11_PROCESS_EVENT g_x11processeventa[8];


x11_hook::x11_hook()
{

}


::estatus x11_hook::hook()
{

   sync_lock sl(x11_mutex());

   g_px11hooka->add(this);

   return ::success;

}


::estatus x11_hook::unhook()
{

   sync_lock sl(x11_mutex());

   g_px11hooka->remove(this);

   return ::success;

}


void x11_hook::on_idle(Display * pdisplay)
{

}

bool __x11_hook_list_is_empty()
{

   return g_px11hooka->is_empty();

}


bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
{

   for(auto & phook : *g_px11hooka)
   {

      if(phook->process_event(pdisplay, e, cookie))
      {

         return true;

      }

   }

   return false;

}


void __x11_hook_on_idle(Display * pdisplay)
{

   for(auto & phook : *g_px11hooka)
   {

      phook->on_idle(pdisplay);

   }

}



//   for(int i = 0; i < g_cX11; i++)
//   {
//
//      if(g_x11processeventa[i] == pfn)
//      {
//
//         memmove(g_x11processeventa + i, g_x11processeventa + i + 1, g_cX11 - i - 1);
//
//         g_cX11--;
//
//         return ::success;
//
//      }
//
//   }
//
//   return ::error_failed;
//
//}

#if !defined(RASPBIAN)
bool x11_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);
#else
bool x11_process_event(Display * pdisplay, XEvent & e);
#endif

bool __x11_hook_process_event(Display * pdisplay, XEvent & e);





bool x11_hook::process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
{

   return false;

}

