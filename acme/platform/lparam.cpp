#include "framework.h"


lparam::lparam(const ::matter * p)
{

   if (is_null(p))
   {

      m_lparam = 0;

      return;

   }

   ((matter *) p)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PTR(&lparam_debug()));

   m_lparam = (iptr)(void *) p;

}



