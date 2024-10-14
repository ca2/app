#include "framework.h"


/// posting/sending particle with referencing forking
lparam::lparam(const ::subparticle * psubparticle)
{

   if (is_null(psubparticle))
   {

      m_lparam = 0;

      return;

   }

#if REFERENCING_DEBUGGING

   if (psubparticle->m_bReferencingDebuggingEnabled)
   {

      ((subparticle*)psubparticle)->m_prefererTransfer = ::allocator::defer_add_referer({ this, __FUNCTION_FILE_LINE__ });

   }

#endif

   ((subparticle *)psubparticle)->increment_reference_count();

   m_lparam = (iptr)(void *)psubparticle;

}


#if REFERENCING_DEBUGGING


/// posting/sending particle with referencing transfer
lparam::lparam(::subparticle * psubparticle, ::reference_referer * preferer)
{

   if (is_null(psubparticle))
   {

      m_lparam = 0;

      return;

   }

   psubparticle->m_prefererTransfer = preferer;

   m_lparam = (iptr)(void *)psubparticle;

}


#endif



