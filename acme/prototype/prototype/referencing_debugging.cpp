//
// Created by camilo on 2026-09-12 16:33 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "platform.h"
#if REFERENCING_DEBUGGING
#include "subparticle.h"
#include "acme/platform/referencing_debugging.h"


#if REFERENCING_DEBUGGING

//::particle * particle::__call__add_referer(const ::reference_referer & referer) const
//{
//
//   ::allocator::add_referer(referer);
//
//   return (::particle *)this;
//
//}


subparticle::referencing_debugging::referencing_debugging(::subparticle * psubparticle)
{

   m_psubparticle = nullptr;
   m_psubparticleTopTrack = nullptr;

   //::time                        m_timeAllocation;
   m_preferenceitema = nullptr;
   m_bHeapAllocation = false;
   m_pType = nullptr;
   m_sType = sizeof(::subparticle);
   m_prefererTransfer2 = nullptr;
   m_prefererLast2 = nullptr;
   m_bReferencingDebuggingEnabled5 = true;
   m_bIncludeCallStackTrace = false;

}


void subparticle::referencing_debugging::add_top_track(::subparticle* psubparticle)
{

   if (::is_null(psubparticle))
   {

      throw ::exception(::error_wrong_state, "cannot track null particle");

   }

   if (contains_top_track(psubparticle))
   {

      throw ::exception(::error_wrong_state, "particle is already tracked");

   }

   auto psubparticleTop = get_top_track();

   psubparticleTop->m_referencingdebugging.m_psubparticleTopTrack = psubparticle;

}


::subparticle* subparticle::referencing_debugging::get_top_track() const
{

   return ::is_null(m_psubparticleTopTrack) ?
      (::subparticle *) this :
      m_psubparticleTopTrack->m_referencingdebugging.get_top_track();

}


void subparticle::referencing_debugging::erase_top_track(::subparticle * psubparticle)
{

   if (::is_null(psubparticle))
   {

      return;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      throw ::exception(error_wrong_state);

   }

   if (psubparticle == m_psubparticleTopTrack)
   {

      m_psubparticleTopTrack = m_psubparticleTopTrack->m_referencingdebugging.m_psubparticleTopTrack;

   }
   else
   {

      auto pNextTop = m_psubparticleTopTrack;

      if (::is_set(pNextTop))
      {

         pNextTop->m_referencingdebugging.erase_top_track(psubparticle);

         return;

      }

   }

}


bool subparticle::referencing_debugging::find_top_track(::subparticle * psubparticle, ::subparticle ** psubparticleParent) const
{

   if (::is_null(psubparticle))
   {

      return false;

   }

   if (psubparticle == m_psubparticle)
   {

      return true;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      return false;

   }

   if (m_psubparticleTopTrack == psubparticle)
   {

      if (psubparticleParent)
      {

         *psubparticleParent = (::subparticle*)this;

      }

      return true;

   }

   if (psubparticleParent)
   {

      *psubparticleParent = (::subparticle *)this;

   }

   return m_psubparticleTopTrack->m_referencingdebugging.find_top_track(psubparticle, psubparticleParent);

}


bool subparticle::referencing_debugging::contains_top_track(::subparticle* psubparticle) const
{

   if (::is_null(psubparticle))
   {

      return false;

   }

   if (psubparticle == m_psubparticle)
   {

      return true;

   }

   if (::is_null(m_psubparticleTopTrack))
   {

      return false;

   }

   if (m_psubparticleTopTrack == psubparticle)
   {

      return true;

   }

   return m_psubparticleTopTrack->m_referencingdebugging.contains_top_track(psubparticle);

}


reference_item_array * subparticle::referencing_debugging::reference_itema()
{

   if (!m_bReferencingDebuggingEnabled5)
   {

      return nullptr;

   }

   //if (::is_null(m_preferenceitema))
   //{

   //   m_preferenceitema = allocateø reference_item_array(this);

   //}

   return m_preferenceitema;

}


#endif



//void check_all_pending_releases()
//{
//
//   auto c = ::acme::get()->m_pobjectreferencecountdebuga->size();
//
//   {
//
//      ::string strDump;
//
//      strDump.append_formatf("Inspected Items : %d\n", g_iInspectedItems);
//
//      strDump.append_formatf("Found %d items with pending releases.\n", c);
//
//      ::output_debug_string(strDump);
//
//   }
//
//   for (::collection::index i = 0; i < c; i++)
//   {
//
//      auto p = g_pobjectreferencecountdebuga->element_at(i);
//
//      {
//
//         ::string strDump;
//
//         strDump.append_formatf("\n\n%d:\n", i);
//
//         try
//         {
//
//            p->dump_pending_releases(strDump);
//
//         }
//         catch (...)
//         {
//
//
//         }
//
//         ::output_debug_string(strDump);
//
//      }
//
//   }
//
//}
//
//
//namespace platform
//{
//
//
//   extern thread_local void * t_pStartConstruct;
//   extern thread_local memsize t_sStartConstruct;
//
//
//} // namespace platform
//



void destruct_particle_reference_item_array(::subparticle::referencing_debugging * preferencingdebugging)
{

   auto preferenceitema = preferencingdebugging->m_preferenceitema;

   if (::is_set(preferenceitema))
   {

      preferencingdebugging->m_preferenceitema = nullptr;

      delete preferenceitema;

   }

}





CLASS_DECL_ACME::critical_section * refdbg_cs()
{

   return &::acme::get()->m_preferencingdebugging->m_criticalsection;

}


#endif



