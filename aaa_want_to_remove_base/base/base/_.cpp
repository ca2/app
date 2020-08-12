#include "framework.h"


//#define LIB_MAIN_DEBUG_BOX (lib_main_any | lib_main_process_attach | lib_main_process_detach  | lib_main_thread_attach  | lib_main_thread_detach)
//#define LIB_MAIN_INT_DELAY_MS {10000, 10000, 10000, 10000, 10000}


#include "aura/inline/_lib_impl.h"


#ifdef LIB_MAIN_DEBUG_BOX
#undef LIB_MAIN_DEBUG_BOX
#endif



/*
namespace std
{

   const nothrow_t nothrow;

} // namespace std

*/

//i32 ___()
//{
//
//   message_box(nullptr,"___ library of ca","___ library of ca",MB_ICONINFORMATION | MB_OK);
//
//   return 0;
//
//}
//


//string_map < INT_PTR,INT_PTR > * g_pmapLibrary = nullptr;
//
//string_map < INT_PTR, INT_PTR > & __library()
//{
//   return *g_pmapLibrary;
//}
//
//



int g_iBaseRefCount = 0;


CLASS_DECL_BASE int get_base_init()
{

   return g_iBaseRefCount;

}


//::aura::system * base_create_aura_system(app_core * pappcore)
::aura::system * base_create_aura_system()
{

   //return new ::base::system(nullptr, pappcore);
   return new ::base::system();

}

extern "C"
CLASS_DECL_BASE int_bool defer_base_init()
{

   g_iBaseRefCount++;

   if(g_iBaseRefCount > 1)
      return TRUE;

   if(!base_init())
      return FALSE;

   return TRUE;

}

extern "C"
CLASS_DECL_BASE int_bool defer_base_term()
{

   g_iBaseRefCount--;

   if(g_iBaseRefCount >= 1)
      return TRUE;

   base_term();

   return TRUE;

}



bool base_init()
{

   if(!defer_aura_init())
      return false;

   ::base::static_start::init();

//   if(!__node_base_pre_init())
//      return false;
//
//   if(!__node_base_pos_init())
//      return false;
//
   g_pfn_create_system = &base_create_aura_system;

   return true;

}


bool base_term()
{

   //__wait_threading_count(::millis((5000) * 8));

   ::multithreading::wait_threads(40_s);

//   __node_base_pre_term();
//
//   __node_base_pos_term();
//
   ::base::static_start::term();




   defer_aura_term();

   return true;

}


