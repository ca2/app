#include "framework.h"


/// posting/sending particle with referencing forking
lparam::lparam(const ::particle * pparticle)
{

   if (is_null(pparticle))
   {

      m_lparam = 0;

      return;

   }

   ((particle *)pparticle)->m_prefererTransfer = ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });

   ((particle *)pparticle)->increment_reference_count();

   m_lparam = (iptr)(void *)pparticle;

}


/// posting/sending particle with referencing transfer
lparam::lparam(::particle * pparticle, ::reference_referer * preferer)
{

   if (is_null(pparticle))
   {

      m_lparam = 0;

      return;

   }

   pparticle->m_prefererTransfer = preferer;

   m_lparam = (iptr)(void *)pparticle;

}



