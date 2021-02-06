#include "framework.h"
#include "acme/id.h"
//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < hthread > t_hthread;


namespace audio
{

   CLASS_DECL_ACME string get_default_library_name()
   {

      return "audio_alsa";

   }

} // namespace audio




CLASS_DECL_ACME bool __node_acme_pre_init()
{

   return true;

}


CLASS_DECL_ACME bool __node_acme_pos_init()
{

//   t_hthread = new hthread();
//
//    //t_hthread-
//
//   t_hthread->m_bRun = true;

   return true;

}


//void __clear_mq(const char * pszDebug, ithread_t id, bool bClose);
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


::file::path dir::sys_temp()
{

   return ::file::path(getenv("HOME")) / ".config/ca2/time";

}


// http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// http://stackoverflow.com/users/1275169/l3x
int get_proc_stat_core_count()
{

   string str = file_as_string("/proc/stat");

   string_array stra;

   stra.add_lines(str);

   return stra.pred_get_count([](auto str) { return ::str::begins(str, "cpu"); });

}



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


::millis os_get_system_update_poll_time(const ::id & id)
{

   if(id == id_os_dark_mode)
   {

      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;
      return 0;

   }
   else if(id == id_os_user_theme)
   {
      // On Gnome you can?
      // ... hook to the gtk-theme-name property change event of GTK Settings default object
      //return 300_ms;

      //return 300_ms;
      return 0;

   }

   return 0;

}



