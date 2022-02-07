#include "framework.h"


CLASS_DECL_APEX bool _istlead(i32 ch)
{

   return false;

}


void sleep(const ::duration & duration)
{
   timespec t;
   t.tv_sec = ::duration.m_i::durations / 1000;
   t.tv_nsec = (::duration.m_i::durations % 1000) * 1000 * 1000;
   nanosleep(&t, nullptr);
}



















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




//int get_processor_count()
//{
//   return 1;
//}

