#include "framework.h"
#include "acme/id.h"
#include <jni.h>
#include "acme/operating_system/android/_os_object.h"
#include "acme/operating_system/android/_os_remote.h"


__pointer(os_local) g_poslocal;
__pointer(os_remote) g_posremote;


os_local * oslocal()
{

   return g_poslocal;

}

os_remote * osremote()
{

   return g_posremote;

}


void set_oslocal(os_local * poslocal)
{

   g_poslocal = poslocal;

}


void set_osremote(os_remote * posremote)
{

   g_posremote = posremote;

}


::duration os_get_system_update_poll_time(const ::atom & atom)
{

   if (atom == id_operating_system_user_theme_change)
   {

      return e_zero;

   }
   else if (atom == id_operating_system_user_color_change)
   {

      return e_zero;

   }
   //else if (atom == id_operating_system_font_change)
   //{

   //   return e_zero;

   //}
   //else if (atom == id_operating_system_font_enumeration)
   //{

   //   return e_zero;

   //}

   return e_zero;

}


CLASS_DECL_ACME void __node_acme_pre_init()
{

}


CLASS_DECL_ACME void __node_acme_pos_init()
{

}


//CLASS_DECL_ACME void __node_term_cross_windows_threading();


CLASS_DECL_ACME void __node_acme_pre_term()
{

   //__node_term_cross_windows_threading();

}


CLASS_DECL_ACME void __node_acme_pos_term()
{

}



CLASS_DECL_ACME int __node_is_debugger_attached()
{

   return false;

}
