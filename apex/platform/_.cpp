#include "framework.h"
//#include "apex/message.h"
#include <stdio.h>

CLASS_DECL_APEX ::i32_bool defer_apex_init();

CLASS_DECL_APEX ::i32_bool defer_apex_term();


::i32 g_iApexRefCount = 0;


CLASS_DECL_APEX ::i32 get_apex_init()
{

   return g_iApexRefCount;

}



