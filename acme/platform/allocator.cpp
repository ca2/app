// Created by camilo on 2023-11-27 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "allocator.h"


#if REFERENCING_DEBUGGING

CLASS_DECL_ACME::reference_referer* refdbg_get_top_releaser();

#include "reference_item_array.h"
#include "referencing_debugging.h"

extern bool g_bDefaultEnableObjectReferenceCountDebug;

thread_local bool t_bThisDebug12321575 = false;
CLASS_DECL_ACME void set_ThisDebug12321575()
{

   t_bThisDebug12321575 = true;

}
void destruct_particle_reference_item_array(::subparticle * pparticle);


namespace allocator
{


   CLASS_DECL_ACME ::allocator::accessor * g_pacessorDefault;


   thread_local bool t_bDisableReferencingDebugging__ExpectedTemporarily__ = false;
   thread_local void * t_pStartConstruct = nullptr;
   thread_local memsize t_sStartConstruct = -1;
   //thread_local bool t_bStartConstructDisableReferencingDebugging = false;
   thread_local bool t_bStartConstructParticleAndHeapAllocation = false;
   thread_local ::subparticle * t_psubparticleTrackAllocation = nullptr;
   thread_local bool t_bGoodStackTrackingStart = false;
   thread_local ::reference_referer * t_preferencerefererTopic = nullptr;
   thread_local ::reference_referer * t_preferencerefererReleaser = nullptr;

   //void _push_referer(::reference_referer * preferer)
   //{

   //   if (!t_preferencerefererTopic)
   //   {

   //      t_preferencerefererTopic = preferer;

   //   }
   //   else
   //   {

   //      preferer->m_preferencerefererNext = t_preferencerefererTopic;

   //      t_preferencerefererTopic = preferer;

   //   }

   //}

   void _push_referer(::reference_referer * preferer)
   {

      if (t_preferencerefererTopic)
      {

         throw "123";

      }

      t_preferencerefererTopic = preferer;

   }


   ::reference_referer * new_referer(const ::reference_referer & referer)
   {

      //auto preferencereferer = ::platform::allocator::__callnew reference_referer (::transfer(referer));

      auto preferencereferer = __raw_new ::reference_referer(referer);

      return preferencereferer;

   }


   // ::reference_referer * defer_add_referer(const ::reference_referer & referer)
   // {
   //
   //    auto preferencereferer = get_referer();
   //
   //    if(!preferencereferer)
   //    {
   //
   //       preferencereferer = add_referer(referer);
   //
   //    }
   //
   //    return preferencereferer;
   //
   // }

   //
   // ::reference_referer * defer_get_referer(::subparticle * p, const ::reference_referer & referer)
   // {
   //
   //    if (referer.m_cstringType && referer.m_cstringType == "class pointer<class item>")
   //    {
   //
   //       ::string strDebugTitle = p->get_debug_title();
   //
   //       if (strDebugTitle.contains("e_element_none"))
   //       {
   //
   //          output_debug_string("");
   //
   //       }
   //
   //    }
   //
   //    auto preferencereferer = get_referer();
   //
   //    if(!preferencereferer)
   //    {
   //
   //       preferencereferer = add_referer(referer);
   //
   //    }
   //
   //    return preferencereferer;
   //
   // }
   //


   //::reference_referer * push_referer(const ::reference_referer & referer)
   //{

   //   auto prefererefererExisting = get_top_referer();

   //   if(prefererefererExisting && referer.m_bConstructor && prefererefererExisting->m_bConstructor)
   //   {

   //      return prefererefererExisting;

   //   }

   //   auto preferencereferer = new_referer(::transfer(referer));

   //   _push_referer(preferencereferer);

   //   return preferencereferer;

   //}


   ::reference_referer * push_referer(const ::reference_referer & referer)
   {

      auto prefererefererExisting = get_top_referer();

      if (prefererefererExisting)
      {

         //throw "23";
         return prefererefererExisting;

      }

      auto preferencereferer = new_referer(referer);

      _push_referer(preferencereferer);

      return preferencereferer;

   }

   CLASS_DECL_ACME ::reference_referer* get_top_referer()
   {

      return t_preferencerefererTopic;

   }


   //::reference_referer * defer_push_referer(::subparticle * psubparticleExisting, const ::reference_referer & referer)
   //{

   //   auto preferencereferer = get_top_referer();

   //   if(!preferencereferer
   //      || preferencereferer->m_bConstructor
   //      || preferencereferer->m_psubparticleExisting != psubparticleExisting)
   //   {

   //      preferencereferer = new_referer(::transfer(referer));

   //      preferencereferer->m_psubparticleExisting = psubparticleExisting;

   //      _push_referer(preferencereferer);

   //   }

   //   return preferencereferer;

   //}

   ::reference_referer * defer_push_referer(::subparticle * psubparticleExisting, const ::reference_referer & referer)
   {

      auto preferencereferer = get_top_referer();

      if (!preferencereferer)
      {

         //::output_debug_string("hey! wait! deferedly pushing a referer?!");

         preferencereferer = new_referer(referer);

         _push_referer(preferencereferer);

      }

      return preferencereferer;

   }

   /*::reference_referer * pop_referer()
   {

      auto preferer = t_preferencerefererTopic;

      if(!preferer->m_bConstructor)
      {

         t_preferencerefererTopic = preferer->m_preferencerefererNext;

      }

      if (::is_null(preferer))
      {

         throw "error_wrong_state";

      }

      if (preferer->m_bConstructor)
      {

         t_preferencerefererTopic = new ::reference_referer(*preferer);

         return preferer;

      }
      else
      {

         return preferer;

      }

   }*/

   ::reference_referer * pop_referer()
   {

      auto preferer = t_preferencerefererTopic;

      if (::is_null(preferer))
      {

         throw "error_wrong_state";

      }

      t_preferencerefererTopic = nullptr;

      return preferer;

   }

   //::reference_referer * construct_pop_referer()
   //{

   //   auto preferer = t_preferencerefererTopic;

   //   t_preferencerefererTopic = preferer->m_preferencerefererNext;

   //   if (::is_null(preferer))
   //   {

   //      throw "error_wrong_state";

   //   }

   //   return preferer;

   //}

   ::reference_referer * construct_pop_referer()
   {

      auto preferer = t_preferencerefererTopic;

      if (::is_null(preferer))
      {

         throw "error_wrong_state";

      }

      return preferer;

   }

   //void defer_erase_referer()
   //{

   //   auto preferer = t_preferencerefererTopic;

   //   if (::is_set(preferer) && !preferer->m_bConstructor)
   //   {

   //      t_preferencerefererTopic = preferer->m_preferencerefererNext;

   //      if (preferer->m_psubparticle 
   //         && preferer->m_psubparticle->is_referencing_debugging_enabled())
   //      {
   //         
   //         ::output_debug_string("56");

   //      }
   //      else
   //      {
   //         
   //         return erase_referer(preferer);

   //      }

   //   }

   //}

   void defer_erase_referer()
   {

      auto preferer = t_preferencerefererTopic;

      if (::is_set(preferer))
      {

         t_preferencerefererTopic = nullptr;

         return erase_referer(preferer);

      }

   }

   //void defer_erase_referer(::subparticle * psubparticle)
   //{

   //   auto preferer = t_preferencerefererTopic;

   //   if (::is_set(preferer))
   //   {

   //      t_preferencerefererTopic = preferer->m_preferencerefererNext;

   //      if (!preferer->m_psubparticle
   //         || preferer->m_psubparticle == psubparticle
   //         || !preferer->m_psubparticle->is_referencing_debugging_enabled())
   //      {

   //         return erase_referer(preferer);

   //      }
   //      else
   //      {

   //         ::output_debug_string("67");

   //      }

   //   }

   //}


   void defer_erase_referer(::subparticle * psubparticle)
   {

      auto preferer = t_preferencerefererTopic;

      if (::is_set(preferer))
      {

         t_preferencerefererTopic = nullptr;

         return erase_referer(preferer);

      }

   }


   ::reference_referer * get_referer()
   {

      return t_preferencerefererTopic;

   }


   void erase_referer(::reference_referer * preferer)
   {

      //::platform::allocator::__delete(preferer);

      delete preferer;

   }




   void set_releaser(::reference_referer * preferer)
   {

      if (t_bThisDebug12321575)
      {

         if (::is_null(preferer))
         {

            return;

         }

      }
      else
      {

         if (::is_null(preferer))
         {

            return;

         }

      }

      //ASSERT(!t_preferencerefererReleaser);

      if (t_preferencerefererReleaser)
      {

         throw ::exception(error_wrong_state);

      }

      t_preferencerefererReleaser = preferer;

   }


   void add_releaser(::reference_referer * preferer)
   {

      //auto preferencereferer = ::platform::raw_allocator::new reference_referer (::transfer(referer));

      set_releaser(preferer);

   }


   ::reference_referer * pop_releaser()
   {

      auto preferer = t_preferencerefererReleaser;

      t_preferencerefererReleaser = nullptr;

      return preferer;

   }


   ::reference_referer * get_releaser()
   {

      return t_preferencerefererReleaser;

   }


   void defer_erase_releaser(bool bParticleReferencingDebuggingEnabled)
   {

      auto preleaser = t_preferencerefererReleaser;

      if (g_bDefaultEnableObjectReferenceCountDebug
         && bParticleReferencingDebuggingEnabled)
      {
         ASSERT(preleaser);
      }
      else
      {

         ASSERT(!preleaser);
      }

      if (::is_set(preleaser))
      {

         t_preferencerefererReleaser = nullptr;

         erase_releaser(preleaser);

      }

   }


   void erase_releaser(::reference_referer * preferer)
   {

      //::platform::allocator::__delete(preferer);

      delete preferer;

   }


   void __on_start_construct(void * p, memsize s, bool bParticleAndHeapAllocation)
   {

      t_pStartConstruct = p;
      t_sStartConstruct = s;
      //t_bStartConstructDisableReferencingDebugging = bDisableReferencingDebugging;
      t_bStartConstructParticleAndHeapAllocation = bParticleAndHeapAllocation;

   }


   void on_construct_subparticle(::subparticle * pparticle)
   {

      if (((unsigned char *)pparticle) >= t_pStartConstruct && pparticle->m_sType <= t_sStartConstruct)
      {

         pparticle->m_pType = t_pStartConstruct;
         pparticle->m_sType = t_sStartConstruct;
         pparticle->m_bHeapAllocation = t_bStartConstructParticleAndHeapAllocation;

      }
      else if(!t_pStartConstruct || t_sStartConstruct <= 0)
      {

         ASSERT(!t_bStartConstructParticleAndHeapAllocation);

      }


      bool bDisableReferencingDebugging = 
         !pparticle->m_bHeapAllocation
         || ::allocator::t_bDisableReferencingDebugging__ExpectedTemporarily__;

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      //t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

      if (!pparticle->m_bHeapAllocation)
      {

         bDisableReferencingDebugging = true;

      }

      if (!g_bDefaultEnableObjectReferenceCountDebug)
      {

         bDisableReferencingDebugging = true;

      }

      ::subparticle * pparticleParent = nullptr;

      if (!bDisableReferencingDebugging)
      {

         if (::is_set(t_psubparticleTrackAllocation)
            && t_psubparticleTrackAllocation->contains_top_track(pparticle))
         {

            throw ::exception(::error_wrong_state, "particle already tracked");

         }
         else
         {

            if (::is_null(t_psubparticleTrackAllocation))
            {

               if (pparticle->m_bHeapAllocation)
               {

                  t_psubparticleTrackAllocation = pparticle;

               }

               if (!pparticle->is_referencing_debugging_enabled())
               {

                  bDisableReferencingDebugging = true;

               }

            }
            else
            {

               auto pparticleTopTrack = t_psubparticleTrackAllocation->get_top_track();

               pparticleParent = pparticleTopTrack;

               if (!pparticleTopTrack->is_referencing_debugging_enabled())
               {

                  bDisableReferencingDebugging = true;

                  if (!pparticleTopTrack->contains_object_in_address_space(pparticle)
                     && pparticle->m_bHeapAllocation)
                  {

                     // TODO: Enable tracking and referencing_debugging
                     // for particle heap allocation inside non particle/non heap
                     // objects (Noisy/Non Hierarchical Reports Feature Flag?)
                     // pparticleTopTrack->add_top_track(pparticle);

                  }

               }
               else
               {

                  if (pparticleTopTrack->contains_object_in_address_space(pparticle))
                  {
                     // Much probably pparticle is "physical" member of pparticleTopTrack,
                     // directly or indirectly.

                     bDisableReferencingDebugging = true;

                  }
                  else if (pparticle->m_bHeapAllocation)
                  {

                     pparticleTopTrack->add_top_track(pparticle);

                  }

               }

            }

         }

      }

      if (bDisableReferencingDebugging)
      {

         pparticle->disable_referencing_debugging();

      }

      if(pparticle->is_referencing_debugging_enabled())
      {

         pparticle->m_preferenceitema = __raw_new reference_item_array (pparticle, pparticleParent);

         //on_after_construct_particle(pparticle->m_preferenceitema);

         pparticle->add_reference_item(pparticle->m_bIncludeCallStackTrace);

         // if (!pparticle->m_prefererTransfer
         //    && pparticle->m_preferenceitema->m_itema[0])
         // {
         //
         //    pparticle->m_prefererTransfer = pparticle->m_preferenceitema->m_itema[0]->m_preferer;
         //
         // }


      }
      else
      {

         defer_erase_referer();

      }

   }


   ::subparticle * task_get_top_track()
   {

      if (::is_null(t_psubparticleTrackAllocation))
      {

         return nullptr;

      }

      return t_psubparticleTrackAllocation->get_top_track();

   }


   void on_after_construct_particle(::subparticle * pparticle)
   {

      auto ptoptrack = task_get_top_track();

      // if This is enabled
                  // TODO: Enable tracking and referencing_debugging
                  // for particle heap allocation inside non particle/non heap
                  // objects (Noisy/Non Hierarchical Reports Feature Flag?)
                  // pparticleTopTrack->add_top_track(pparticle);
      //one can enable this:
      //ASSERT(ptoptrack == pparticle);

      if (::is_set(t_psubparticleTrackAllocation))
      {

         if (t_psubparticleTrackAllocation == pparticle)
         {

            t_psubparticleTrackAllocation = nullptr;

         }
         else
         {
            // if This is enabled
                        // TODO: Enable tracking and referencing_debugging
                        // for particle heap allocation inside non particle/non heap
                        // objects (Noisy/Non Hierarchical Reports Feature Flag?)
                        // pparticleTopTrack->add_top_track(pparticle);
            //one can disable the contains top track check:

            if (t_psubparticleTrackAllocation->contains_top_track(pparticle))
            {

               t_psubparticleTrackAllocation->erase_top_track(pparticle);

            }

         }

      }

   }


   void __on_after_construct()
   {

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      //t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

   }


   CLASS_DECL_ACME void start_suppressing_referencing_debugging()
   {

      t_bDisableReferencingDebugging__ExpectedTemporarily__ = true;

   }

   
   CLASS_DECL_ACME void cease_referencing_debugging_suppression()
   {

      t_bDisableReferencingDebugging__ExpectedTemporarily__ = false;

   }


   CLASS_DECL_ACME bool is_suppressing_referencing_debugging()
   {

      return t_bDisableReferencingDebugging__ExpectedTemporarily__;

   }


   void __on_after_construct_subparticle(::subparticle * psubparticle)
   {

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      //t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

      if (psubparticle->m_preferenceitema)
      {

         psubparticle->m_preferenceitema->m_strDebug = psubparticle->get_debug_title();

         if (get_top_referer()
            && psubparticle->m_preferenceitema->m_itema[0]
            && psubparticle->m_preferenceitema->m_itema[0]->m_preferer)
         {

            if (get_top_referer()->m_iSerial == psubparticle->m_preferenceitema->m_itema[0]->m_preferer->m_iSerial)
            {

               defer_erase_referer();

            }

         }

      }
      else
      {

         defer_erase_referer();

      }

      refdbg_erase_top_track(psubparticle);



   }


   CLASS_DECL_ACME void __on_after_construct_non_subparticle()
   {

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      //t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

   }


   //void __on_after_construct_subparticle_cleanup(::subparticle* psubparticle)
   //{

   //   t_pStartConstruct = nullptr;
   //   t_sStartConstruct = -1;
   //   //t_bStartConstructDisableReferencingDebugging = false;
   //   t_bStartConstructParticleAndHeapAllocation = false;

   //   ASSERT(!psubparticle->m_preferenceitema);
   //   //{

   //   //   psubparticle->m_preferenceitema->m_strDebug = psubparticle->get_debug_title();

   //   //}

   //   refdbg_erase_top_track(psubparticle);

   //}
   
   
   void on_destruct_subparticle(::subparticle * psubparticle)
   {

      ::destruct_particle_reference_item_array(psubparticle);

   }


   //CLASS_DECL_ACME void task_on_operator_new(void * p, memsize s)
   //{
   //
   //   t_pOperatorNew = p;
   //   t_sOperatorNew = s;
   //
   //}


} // namespace platform


void subparticle::disable_referencing_debugging()
{

   m_bReferencingDebuggingEnabled = false;

   //m_eflagElement.set(e_flag_no_referencing_debugging);

   //if (::is_set(::allocator::t_pparticleTrackAllocation))
   //{

   //   if (::allocator::t_pparticleTrackAllocation == this)
   //   {

   //      //::system()->m_preferencingdebugging->m_item2a.erase_last(this);

   //      ::allocator::t_pparticleTrackAllocation = nullptr;

   //   }
   //   else
   //   {

   //      ::particle * pparticleParent = ::allocator::t_pparticleTrackAllocation;

   //      if (::allocator::t_pparticleTrackAllocation->find_top_track(this, &pparticleParent))
   //      {

   //         pparticleParent->erase_top_track(this);

   //      }

   //   }

   //}

   ::destruct_particle_reference_item_array(this);

//   m_pparticleTopTrack = nullptr;

}


CLASS_DECL_ACME bool refdbg_add_top_track(::subparticle * pparticle)
{

   if (!::allocator::t_psubparticleTrackAllocation)
   {

      ::allocator::t_psubparticleTrackAllocation = pparticle;

   }
   else if (::allocator::t_psubparticleTrackAllocation->contains_top_track(pparticle))
   {

      return false;

   }
   else
   {

      auto p = ::allocator::t_psubparticleTrackAllocation->get_top_track();

      p->add_top_track(pparticle);

   }

   return true;


}


CLASS_DECL_ACME void refdbg_erase_top_track(::subparticle* pparticle)
{

   if (::is_set(::allocator::t_psubparticleTrackAllocation))
   {

      if (::allocator::t_psubparticleTrackAllocation == pparticle)
      {

         ::allocator::t_psubparticleTrackAllocation = nullptr;

      }
      else
      {

         ::subparticle* pparticleParent = ::allocator::t_psubparticleTrackAllocation;

         if (::allocator::t_psubparticleTrackAllocation->find_top_track(pparticle, &pparticleParent))
         {

            pparticleParent->erase_top_track(pparticle);

         }

      }

   }

}





bool g_bIntermediateThreadReferencingDebugging = false;



//::particle * __call__add_referer(const ::reference_referer & referer)
//{
//
//   return ::system()->platform()->__call__add_referer(referer);
//
//}
CLASS_DECL_ACME::reference_referer* refdbg_get_top_referer();
CLASS_DECL_ACME::subparticle* refdbg_get_track_allocation();

CLASS_DECL_ACME void check_refdbg()
{

   auto psubparticleTrackAllocation = refdbg_get_track_allocation();
   if (psubparticleTrackAllocation)
   {

      ::string strType = typeid(*psubparticleTrackAllocation).name();

      output_debug_string("check_refdbg:track_allocation;");

   }

   auto prefererReleaser = refdbg_get_top_releaser();
   if (prefererReleaser)
   {

      ::string strType = typeid(*prefererReleaser).name();

      output_debug_string("check_refdbg:top_releaser;");

   }

   auto prefererReferer = refdbg_get_top_referer();
   if (prefererReferer)
   {

      ::string strType = typeid(*prefererReferer).name();

      output_debug_string("check_refdbg:top_referer;");

   }

}


CLASS_DECL_ACME::subparticle* refdbg_get_track_allocation()
{

   return ::allocator::t_psubparticleTrackAllocation;

}

CLASS_DECL_ACME::reference_referer* refdbg_get_top_referer()
{

   return ::allocator::t_preferencerefererTopic;
}


CLASS_DECL_ACME::reference_referer* refdbg_get_top_releaser()
{

   return ::allocator::t_preferencerefererReleaser;

}


#endif //  REFERENCING_DEBUGGING


