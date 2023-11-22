#include "framework.h"

::particle g_lparam_object_reference_count_debug;

::particle* lparam_object_reference_count_debug()
{

   return &g_lparam_object_reference_count_debug;

}

lparam::lparam(const ::particle * pelement)
{

   if (is_null(pelement))
   {

      m_lparam = 0;

      return;

   }

   ((particle*)pelement)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PTR(lparam_object_reference_count_debug()));

   m_lparam = (iptr)(void *)pelement;

}





