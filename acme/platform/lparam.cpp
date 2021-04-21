#include "framework.h"


lparam::lparam(const ::matter * p)
{

   if (is_null(p))
   {

      m_lparam = 0;

      return;

   }

   ((matter *) p)->add_ref(OBJ_REF_DBG_PTR(&lparam_debug()));

   m_lparam = (iptr)(void *) p;

}



