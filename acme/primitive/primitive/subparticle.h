// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#pragma once



#include "subparticle_flags.h"
#include "pointer.h"
#include "acme/primitive/primitive/interlocked_count.h"


//
//struct SUBPARTICLE :
//   public SUBPARTICLE_FLAGS
//{
//
//
//   mutable ::acme::context *           m_pcontext;
//   mutable ::ptr < ::particle >        m_pparticleSynchronization;
//
//
//   SUBPARTICLE() :
//      m_pcontext(nullptr)
//   {}
//
//
//};

#include "quantum.h"

class CLASS_DECL_ACME subparticle :
   virtual public ::quantum,
   virtual public SUBPARTICLE_FLAGS
{
public:

   
   //void * m_pAllocation = nullptr;

   ::interlocked_count                 m_countReference;

#if REFERENCING_DEBUGGING
   subparticle();
#else
   subparticle() : m_countReference(1) {}
#endif
   ~subparticle() override;



   virtual bool defer_consume_main_arguments(int argc, char ** argv, int & iArgument);

   virtual void call_run();


   virtual void run();


   virtual bool subparticle_step();


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


   virtual bool _is_set() const;
   inline bool is_null() const { return ::is_null(this); }
   inline bool is_set() const { return !is_null() && _is_set(); }

   virtual bool _is_ok() const;
   inline bool is_ok() const { return is_set() && _is_ok(); }
   inline bool nok() const { return !is_ok(); }



   virtual enum_type get_payload_type() const;


   virtual void init_task();


   virtual void destroy();
   virtual void destroy_impl_data();
   virtual void destroy_os_data();



   virtual void delete_this();


};
