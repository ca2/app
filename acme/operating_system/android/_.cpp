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

   if (atom == id_os_dark_mode)
   {

      return 0;

   }
   else if (atom == id_os_font_change)
   {

      return 0;

   }
   else if (atom == id_font_enumeration)
   {

      return 0;

   }

   return 0;

}







CLASS_DECL_ACME bool __node_acme_pre_init()
{

   return true;

}


CLASS_DECL_ACME bool __node_acme_pos_init()
{

   //   t_htask = new htask();
   //
   //    //t_htask-
   //
   //   t_htask->m_bRun = true;

   return true;

}


//void __clear_mq(const char * pszDebug, itask_t atom, bool bClose);
//void __clear_mq(const char * pszDebug, bool bClose);


CLASS_DECL_ACME void __node_term_cross_windows_threading();


CLASS_DECL_ACME bool __node_acme_pre_term()
{

   __node_term_cross_windows_threading();

   return true;

}


CLASS_DECL_ACME bool __node_acme_pos_term()
{

   return true;

}



CLASS_DECL_ACME int __node_is_debugger_attached()
{

   return false;

}
