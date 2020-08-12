#include "framework.h"


//#define LIB_MAIN_DEBUG_BOX (lib_main_any | lib_main_process_attach | lib_main_process_detach  | lib_main_thread_attach  | lib_main_thread_detach)
//#define LIB_MAIN_INT_DELAY_MS {10000, 10000, 10000, 10000, 10000}


#include "aura/inline/_lib_impl.h"


#ifdef LIB_MAIN_DEBUG_BOX 
#undef LIB_MAIN_DEBUG_BOX 
#endif



