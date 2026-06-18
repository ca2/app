// From lparam.cpp by camilo on 2026-04-18 12:10 <3ThomasBorregaardSørensen!!
#include "framework.h"


/// posting/sending particle with referencing forking
wparam::wparam(const ::subparticle * psubparticle)
{

   if (is_null(psubparticle))
   {

      m_wparam = 0;

      return;

   }

#if REFERENCING_DEBUGGING

   if (psubparticle->is_referencing_debugging_enabled())
   {

      //((subparticle*)psubparticle)->m_prefererTransfer = ::allocator::defer_push_referer((::subparticle *)psubparticle, { (::subparticle *)psubparticle, this, __FUNCTION_FILE_LINE__ });

      ((subparticle *)psubparticle)->m_prefererTransfer2 = __refdbg_add_referer;

   }

#endif

   ((subparticle *)psubparticle)->increment_reference_count();

   m_wparam = (iptr)(void *)psubparticle;

}


#if REFERENCING_DEBUGGING


/// posting/sending particle with referencing transfer
wparam::wparam(::subparticle * psubparticle, ::reference_referer * preferer)
{

   if (is_null(psubparticle))
   {

      m_wparam = 0;

      return;

   }

   psubparticle->m_prefererTransfer2 = preferer;

   m_wparam = (iptr)(void *)psubparticle;

}


#endif



