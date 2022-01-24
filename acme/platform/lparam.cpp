#include "framework.h"


lparam::lparam(const ::element * pelement)
{

   if (is_null(pelement))
   {

      m_lparam = 0;

      return;

   }

   ((element*)pelement)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PTR(&lparam_debug()));

   m_lparam = (iptr)(void *)pelement;

}



