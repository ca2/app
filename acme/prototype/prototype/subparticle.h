// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#pragma once



#include "pointer.h"
#include "acme/prototype/prototype/interlocked_count.h"


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
   virtual public ::quantum
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


   virtual void initialize(::particle * pparticle);
   virtual void finalize();


   virtual bool defer_consume_main_arguments(int argc, char ** argv, int & iArgument);

   virtual void call();

   virtual ::string get_debug_title() const;

   virtual void run();

   virtual class ::time get_run_timeout();

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


   ::subparticle* refdbg_this() const { return (::subparticle*)this; }

protected:

   ::subparticle* m_psubparticleTopTrack = nullptr;

public:

   ::reference_referer * m_prefererTransfer = nullptr;

   ::subparticle * get_top_track() const;
   void add_top_track(::subparticle* psubparticle);
   void erase_top_track(::subparticle* psubparticle);
   bool contains_top_track(::subparticle* psubparticle) const;
   bool find_top_track(::subparticle* psubparticle, ::subparticle** ppsubparticleeParent) const;



   class reference_item_array * m_preferenceitema = nullptr;
   bool                          m_bHeapAllocation = false;
   void *                        m_pType = nullptr;
   memsize                       m_sType = sizeof(::subparticle);
   bool                          m_bReferencingDebuggingEnabled = true;


   void set_size_type(memsize s) { m_sType = s; }

   bool contains_object_in_address_space(::subparticle * psubparticle) const
   {

      return
         ::is_set(this->m_pType)
         && this->m_sType >= sizeof(::subparticle)
         && ((::u8 *)psubparticle >= this->m_pType
         && (((::u8 *)psubparticle) + psubparticle->m_sType)
         <= (((::u8 *)this->m_pType) + this->m_sType));

   }

   class reference_item_array * reference_itema();

   bool is_referencing_debugging_enabled() const
   {

      return m_bReferencingDebuggingEnabled;

   }

   void disable_referencing_debugging();

   //void add_initial_reference_item();
   void add_reference_item();
   void add_referer(::reference_referer * preferer);
   //void _add_reference_item();
   void erase_reference_item();
   void check_pending_releases();

#else

   bool is_referencing_debugging_enabled() const { return false; }

#endif


   virtual bool _is_set() const;
   virtual bool _is_ok() const;


   virtual enum_type get_payload_type() const;


   virtual void init_task();


   virtual void destroy();
   virtual void destroy_impl_data();
   virtual void destroy_os_data();



   virtual void delete_this();

   //void operator delete(void* p);



   virtual void write_to_stream(::binary_stream & stream);
   virtual void read_from_stream(::binary_stream & stream);

   [[nodiscard]] virtual class ::time timeout() const;


   virtual void set_timeout(const class time & time);



};


