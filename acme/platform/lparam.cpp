#include "framework.h"
#include "acme/primitive/primitive/particle.h"


lparam::lparam(const ::particle * pelement)
{

   if (is_null(pelement))
   {

      m_lparam = 0;

      return;

   }

   ((particle*)pelement)->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PTR(&lparam_debug()));

   m_lparam = (iptr)(void *)pelement;

}





