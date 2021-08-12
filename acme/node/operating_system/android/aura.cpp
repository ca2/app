#include "framework.h"



CLASS_DECL_ACME bool _istlead(i32 ch)
{

   return false;

}


void sleep(::u32 dwMillis)
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



















bool __node_aura_pre_init()
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


















































bool __node_aura_pos_init()
{


   return true;

}


bool __node_aura_pre_term()
{


   return true;

}

bool __node_aura_pos_term()
{

   return true;

}




































































































CLASS_DECL_ACME int __node_is_debugger_attached()
{
   return 0;
}




int get_processor_count()
{
   return 1;
}

