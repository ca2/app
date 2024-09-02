#include "framework.h"
#include "acme/constant/id.h"


#include <stdio.h>

//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < htask > t_htask;


//CLASS_DECL_ACME string audio_get_default_implementation_name()
//{
//
//   return "audio_alsa";
//
//}


CLASS_DECL_ACME void __node_acme_pre_init()
{

   //return true;

}


CLASS_DECL_ACME void __node_acme_pos_init()
{

//   t_htask = new htask();
//
//    //t_htask-
//
//   t_htask->m_bRun = true;

   //return true;

}


//void __clear_mq(const ::scoped_string & scopedstrDebug, itask_t atom, bool bClose);
//void __clear_mq(const ::scoped_string & scopedstrDebug, bool bClose);


//CLASS_DECL_ACME void __node_term_cross_windows_threading();


CLASS_DECL_ACME void __node_acme_pre_term()
{

   //__node_term_cross_windows_threading();

   //return true;

}


CLASS_DECL_ACME void __node_acme_pos_term()
{

   //return true;

}


//::file::path dir::sys_temp()
//{
//
//   return ::file::path(getenv("HOME")) / ".config/ca2/time";
//
//}






// int get_processor_count()
// {

//    return sysconf(_SC_NPROCESSORS_ONLN);

// }


class ::time os_get_system_update_poll_time(const ::atom & atom)
{

   if(atom == id_operating_system_user_theme_change)
   {

      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;

      //return 300_ms;
      return zero_t{};

   }
   else if(atom == id_operating_system_user_color_change)
   {

      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;

      return zero_t{};

   }

   return zero_t{};

}

