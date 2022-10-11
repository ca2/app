#include "framework.h"
#include "acme/constant/id.h"
//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < htask > t_htask;


namespace audio
{

   CLASS_DECL_ACME string get_default_library_name()
   {

      return "audio_alsa";

   }

} // namespace audio




CLASS_DECL_ACME void __node_acme_pre_init()
{

   //return true;

}


CLASS_DECL_ACME void __node_acme_pos_init()
{

//   t_htask = memory_new htask();
//
//    //t_htask-
//
//   t_htask->m_bRun = true;

   //return true;

}


//void __clear_mq(const char * pszDebug, itask_t atom, bool bClose);
//void __clear_mq(const char * pszDebug, bool bClose);


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





// http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// http://stackoverflow.com/users/1275169/l3x
int get_proc_cpuinfo_core_count()
{

   char str[256];

   int procCount = 0;

   FILE *fp;

   if( (fp = fopen("/proc/cpuinfo", "r")) )
   {

      while(fgets(str, sizeof str, fp))
      {

         if( !__memcmp(str, "handler", 9) )
         {

            procCount++;

         }

      }

   }

   if ( !procCount )
   {
      printf("Unable to get proc count. Defaulting to 2");
      procCount=2;
   }

   printf("Proc Count:%d\n", procCount);
   return procCount;

}

// int get_processor_count()
// {

//    return get_proc_cpuinfo_core_count();
// }


// int get_processor_count()
// {

//    return sysconf(_SC_NPROCESSORS_ONLN);

// }


::duration os_get_system_update_poll_time(const ::atom & atom)
{

   if(atom == id_operating_system_user_theme_change)
   {

      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;

      //return 300_ms;
      return e_zero;

   }
   else if(atom == id_operating_system_user_color_change)
   {

      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;

      return e_zero;

   }

   return e_zero;

}

