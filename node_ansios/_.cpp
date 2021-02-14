#include "framework.h"
#include <gtk/gtk.h>


bool g_bInitGtk = false;


::e_status g_estatusInitGtk = ::error_none;


::e_status os_defer_init_gtk()
{

   if (!g_bInitGtk)
   {

      g_bInitGtk = true;

      if (!gtk_init_check(process_get_pargc(), process_get_pargv()))
      {

         g_estatusInitGtk = ::error_failed;

      }
      else
      {

         g_estatusInitGtk = ::success;

      }

   }

   return g_estatusInitGtk;


}


