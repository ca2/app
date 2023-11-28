// Created by camilo on 2023-11-27 03:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "allocator.h"
#include "reference_item_array.h"
#include "referencing_debugging.h"


void destruct_particle_reference_item_array(::particle * pparticle);


namespace allocator
{


   thread_local void * t_pStartConstruct = nullptr;
   thread_local memsize t_sStartConstruct = -1;
   thread_local bool t_bStartConstructDisableReferencingDebugging = false;
   thread_local bool t_bStartConstructParticleAndHeapAllocation = true;
   thread_local ::particle * t_pparticleTrackAllocation = nullptr;
   thread_local bool t_bGoodStackTrackingStart = false;


   void __on_start_construct(void * p, memsize s, bool bDisableReferencingDebugging, bool bParticleAndHeapAllocation)
   {

      t_pStartConstruct = p;
      t_sStartConstruct = s;
      t_bStartConstructDisableReferencingDebugging = bDisableReferencingDebugging;
      t_bStartConstructParticleAndHeapAllocation = bParticleAndHeapAllocation;

   }


   void on_construct_particle(::particle * pparticle)
   {

      if (((::u8 *)pparticle) >= t_pStartConstruct && pparticle->m_sType <= t_sStartConstruct)
      {

         pparticle->m_pType = t_pStartConstruct;
         pparticle->m_sType = t_sStartConstruct;

      }

      pparticle->m_bHeapAllocation = t_bStartConstructParticleAndHeapAllocation;

      bool bDisableReferencingDebugging = t_bStartConstructDisableReferencingDebugging;

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

      if (!pparticle->m_bHeapAllocation)
      {

         bDisableReferencingDebugging = true;

      }

      ::particle * pparticleParent = nullptr;
      
      if (::is_set(t_pparticleTrackAllocation)
         && t_pparticleTrackAllocation->contains_top_track(pparticle))
      {

         throw ::exception(::error_wrong_state, "particle already tracked");

      }
      else 
      {

         if (::is_null(t_pparticleTrackAllocation))
         {

            t_pparticleTrackAllocation = pparticle;

            if (!pparticle->is_referencing_debugging_enabled())
            {

               bDisableReferencingDebugging = true;

            }

         }
         else
         {

            auto pparticleTopTrack = t_pparticleTrackAllocation->get_top_track();

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
               else
               {

                  pparticleTopTrack->add_top_track(pparticle);

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

         pparticle->m_preferenceitema = ::platform::raw_allocator::__new < reference_item_array >(pparticle, pparticleParent);

         //on_after_construct_particle(pparticle->m_preferenceitema);

         pparticle->add_reference_item();

      }

   }


   ::particle * task_get_top_track()
   {

      if (::is_null(t_pparticleTrackAllocation))
      {

         return nullptr;

      }

      return t_pparticleTrackAllocation->get_top_track();

   }


   void on_after_construct_particle(::particle * pparticle)
   {

      auto ptoptrack = task_get_top_track();

      // if This is enabled
                  // TODO: Enable tracking and referencing_debugging
                  // for particle heap allocation inside non particle/non heap
                  // objects (Noisy/Non Hierarchical Reports Feature Flag?)
                  // pparticleTopTrack->add_top_track(pparticle);
      //one can enable this:
      //ASSERT(ptoptrack == pparticle);

      if (::is_set(t_pparticleTrackAllocation))
      {

         if (t_pparticleTrackAllocation == pparticle)
         {

            t_pparticleTrackAllocation = nullptr;

         }
         else
         {
            // if This is enabled
                        // TODO: Enable tracking and referencing_debugging
                        // for particle heap allocation inside non particle/non heap
                        // objects (Noisy/Non Hierarchical Reports Feature Flag?)
                        // pparticleTopTrack->add_top_track(pparticle);
            //one can disable the contains top track check:

            if (t_pparticleTrackAllocation->contains_top_track(pparticle))
            {

               t_pparticleTrackAllocation->erase_top_track(pparticle);

            }

         }

      }

   }


   void __on_after_construct()
   {

      t_pStartConstruct = nullptr;
      t_sStartConstruct = -1;
      t_bStartConstructDisableReferencingDebugging = false;
      t_bStartConstructParticleAndHeapAllocation = false;

   }


   void on_destruct_particle(::particle * pparticle)
   {

      ::destruct_particle_reference_item_array(pparticle);

   }


   //CLASS_DECL_ACME void task_on_operator_new(void * p, memsize s)
   //{
   //
   //   t_pOperatorNew = p;
   //   t_sOperatorNew = s;
   //
   //}


} // namespace platform


void particle::disable_referencing_debugging()
{

   m_eflagElement.set(e_flag_no_referencing_debugging);

   if (::is_set(::allocator::t_pparticleTrackAllocation))
   {

      if (::allocator::t_pparticleTrackAllocation == this)
      {

         //::acme::get()->m_preferencingdebugging->m_item2a.erase_last(this);

         ::allocator::t_pparticleTrackAllocation = nullptr;

      }
      else
      {

         ::particle * pparticleParent = ::allocator::t_pparticleTrackAllocation;

         if (::allocator::t_pparticleTrackAllocation->find_top_track(this, &pparticleParent))
         {

            pparticleParent->erase_top_track(this);

         }

      }

   }

   ::destruct_particle_reference_item_array(this);

   m_pparticleTopTrack = nullptr;

}




