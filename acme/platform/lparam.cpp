#include "framework.h"


lparam::lparam(const ::particle * pelement)
{

   if (is_null(pelement))
   {

      m_lparam = 0;

      return;

   }

   ((particle*)pelement)->increment_reference_count(REFERENCING_DEBUGGING_P_NOTE(pelement->platform(), "lparam_debug"));

   m_lparam = (iptr)(void *)pelement;

}



