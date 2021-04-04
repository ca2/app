#include "framework.h"


//#define LIB_MAIN_DEBUG_BOX (lib_main_any | lib_main_process_attach | lib_main_process_detach  | lib_main_thread_attach  | lib_main_thread_detach)
//#define LIB_MAIN_INT_DELAY_MS {10000, 10000, 10000, 10000, 10000}


#include "aura/inline/_lib_impl.h"


#ifdef LIB_MAIN_DEBUG_BOX 
#undef LIB_MAIN_DEBUG_BOX 
#endif





void axis_on_init_thread();
void axis_on_term_thread();

int g_iAxisRefCount = 0;


CLASS_DECL_AXIS int get_axis_init()
{

   return g_iAxisRefCount;

}

//::aura::system * axis_create_aura_system(app_core * pappcore)
::aura::system * axis_create_aura_system()
{

   //return new ::axis::system(nullptr, pappcore);
   return new ::axis::system();

}

extern "C"
CLASS_DECL_AXIS int_bool defer_axis_init()
{


   if(!defer_aura_init())
      return false;


   g_iAxisRefCount++;

   if(g_iAxisRefCount > 1)
      return true;

   ::axis::static_start::init();

   if(!__node_axis_pre_init())
      return false;

   if(!axis_init())
      return false;

   if(!__node_axis_pos_init())
      return false;

   return true;

}

extern "C"
CLASS_DECL_AXIS int_bool defer_axis_term()
{

   g_iAxisRefCount--;

   if(g_iAxisRefCount >= 1)
      return true;

   __node_axis_pre_term();

   axis_term();

   __node_axis_pos_term();

   ::axis::static_start::term();

   defer_aura_term();

   return true;

}



bool axis_init()
{

   g_axisoninitthread = &axis_on_init_thread;
   g_axisontermthread = &axis_on_term_thread;

   g_pfn_create_system = &axis_create_aura_system;

   return true;

}


bool axis_term()
{

//#ifndef WINDOWS

//#ifdef BSD_STYLE_SOCKETS
//
//   ERR_erase_state(::GetCurrentProcessId());
//
//#endif

   //__throw(todo);
   //try
   //{

   //   FreeImage_DeInitialise();

   //}
   //catch(...)
   //{

   //}
//#endif
   /*__wait_threading_count(::millis((5000) * 8));

   __node_axis_pre_term();
   */
//   ::user::term_windowing();
   /*
   ::parallelization::term_multithreading();

   //__term_threading_count();

   __node_axis_pos_term();*/

//   ::axis::static_start::term();

   //defer_axis_term();

   return true;

}

void axis_on_init_thread()
{

}


void axis_on_term_thread()
{


}



