#include "framework.h"

//extern thread_pointer < os_thread > t_posthread;
//extern thread_pointer < htask > t_htask;


//CLASS_DECL_APEX string audio_get_default_implementation_name()
//{
//
//   return "audio_alsa";
//
//}


CLASS_DECL_APEX bool __node_apex_pre_init()
{

   return true;

}


CLASS_DECL_APEX bool __node_apex_pos_init()
{

//   t_htask = ___new htask();
//
//    //t_htask-
//
//   t_htask->m_bRun = true;

   return true;

}

//void __clear_mq(const ::scoped_string & scopedstrDebug, itask atom, bool bClose);
//void __clear_mq(const ::scoped_string & scopedstrDebug, bool bClose);

CLASS_DECL_APEX bool __node_apex_pre_term()
{

   //__node_term_cross_windows_threading();

   return true;

}





CLASS_DECL_APEX bool __node_apex_pos_term()
{

   return true;

}







//::file::path dir::sys_temp()
//{
//
//   return ::file::path(getenv("HOME")) / ".config/ca2/time";
//
//}


// // http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// // http://stackoverflow.com/users/1275169/l3x
// int get_proc_stat_core_count()
// {

//    string str = file_system()->as_string("/proc/stat");

//    string_array stra;

//    stra.add_lines(str);

//    return stra.predicate_get_count([](auto str) { return string_begins(str, "cpu"); });

// }



// // http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
// // http://stackoverflow.com/users/1275169/l3x
// int get_proc_cpuinfo_core_count()
// {

//    char str[256];

//    int procCount = 0;

//    FILE *fp;

//    if( (fp = fopen("/proc/cpuinfo", "r")) )
//    {

//       while(fgets(str, sizeof str, fp))
//       {

//          if( !__memcmp(str, "handler", 9) )
//          {

//             procCount++;

//          }

//       }

//    }

//    if ( !procCount )
//    {
//       printf("Unable to get proc count. Defaulting to 2");
//       procCount=2;
//    }

//    printf("Proc Count:%d\n", procCount);
//    return procCount;

// }

// int get_processor_count()
// {

//    return get_proc_cpuinfo_core_count();
// }





void apex_application_main(int argc, char* argv[], const ::scoped_string & scopedstrCommandLine)
{


}
