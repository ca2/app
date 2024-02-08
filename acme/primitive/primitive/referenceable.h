// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#pragma once



#include "particle_flags.h"
#include "ptr.h"
#include "acme/primitive/primitive/interlocked_count.h"



struct PARTICLE :
   public PARTICLE_FLAGS
{


   mutable ::acme::context *           m_pcontext;
   mutable ::ptr < ::particle >        m_pparticleSynchronization;


   PARTICLE() :
      m_pcontext(nullptr)
   {}


};



class CLASS_DECL_ACME referenceable :
   virtual public PARTICLE
{
public:
   void * m_pAllocation = nullptr;
   ::interlocked_count                 m_countReference;

#if REFERENCING_DEBUGGING
   referenceable();
#else
   referenceable() : m_countReference(1) {}
#endif


   //referenceable();
   //~referenceable();


   virtual void call_run();


   virtual void run();


#ifdef _DEBUG


   virtual i64 increment_reference_count();
   virtual i64 decrement_reference_count();
   virtual i64 replace_reference();
   virtual i64 release();


#else


   inline i64 increment_reference_count();
   inline i64 decrement_reference_count();
   inline i64 replace_reference();
   inline i64 release();


#endif




#if REFERENCING_DEBUGGING


   ::particle * refdbg_this() const { return (::particle *)this; }

protected:

   ::particle * m_pparticleTopTrack = nullptr;

public:

   ::reference_referer * m_prefererTransfer = nullptr;

   ::particle * get_top_track() const;
   void add_top_track(::particle * pparticle);
   void erase_top_track(::particle * pparticle);
   bool contains_top_track(::particle * pparticle) const;
   bool find_top_track(::particle * pparticle, ::particle ** ppparticleParent) const;



   class reference_item_array * m_preferenceitema = nullptr;
   bool                          m_bHeapAllocation = false;
   void * m_pType = nullptr;
   memsize                       m_sType = sizeof(::particle);


   void set_size_type(memsize s) { m_sType = s; }

   bool contains_object_in_address_space(::particle * pparticle) const
   {

      return
         ::is_set(this->m_pType)
         && this->m_sType >= sizeof(::particle)
         && ((::u8 *)pparticle >= this->m_pType
         && (((::u8 *)pparticle) + pparticle->m_sType)
         <= (((::u8 *)this->m_pType) + this->m_sType));

   }

   class reference_item_array * reference_itema();

   bool is_referencing_debugging_enabled() const
   {

      return !m_eflagElement.is(e_flag_no_referencing_debugging);

   }

   void disable_referencing_debugging();

   //void add_initial_reference_item();
   void add_reference_item();
   //void _add_reference_item();
   void erase_reference_item();
   void check_pending_releases();

#else

   bool is_referencing_debugging_enabled() const { return false; }

#endif




};