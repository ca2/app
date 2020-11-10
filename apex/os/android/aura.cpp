#include "framework.h"



//::u32 get_nanos()
//{
//   timeval ts;
//   gettimeofday(&ts,0);
//   return (ts.tv_sec * 1000 * 1000 * 1 + (ts.tv_usec / 1000)) % 0xffffffffu;
//
//}
//
//thread_int_ptr < ::u32 > t_dwLastError;


//CLASS_DECL_APEX ::u32 get_last_error()
//{
//
//   tick t_tickLastError;
//
//}
//
//
//CLASS_DECL_APEX void set_last_error(::u32 dw)
//{
//
//   t_dwLastError = dw;
//
//}


CLASS_DECL_APEX bool _istlead(i32 ch)
{

   return false;

}


void Sleep(::u32 dwMillis)
{
   timespec t;
   t.tv_sec = dwMillis / 1000;
   t.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
   nanosleep(&t, nullptr);
}







//void output_debug_string(const char * psz)
//{
//
//   output_debug_string(psz);
//
//}
//



















bool __node_apex_pre_init()
{

   //c_xstart();

   return true;

}

bool __node_pos_init()
{

   return true;

}

bool __node_pre_term()
{

   return true;

}


bool __node_pos_term()
{

   return true;

}


















































bool __node_apex_pos_init()
{


   return true;

}


bool __node_apex_pre_term()
{


   return true;

}

bool __node_apex_pos_term()
{

   return true;

}




































































































CLASS_DECL_APEX int __node_is_debugger_attached()
{
   return 0;
}




int get_processor_count()
{
   return 1;
}

