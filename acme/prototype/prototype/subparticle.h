// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#pragma once



#include "pointer.h"
#include "acme/prototype/prototype/interlocked_count.h"
#include "acme/prototype/time/time/time.h"

#ifdef WINDOWS
using hsynchronization = void*;
#else
using hsynchronization = ::subparticle *;
#endif


class sequence;


//
//struct SUBPARTICLE :
//   public SUBPARTICLE_FLAGS
//{
//
//
//   mutable ::platform::context *           m_papplication;
//   mutable ::ptr < ::particle >        m_pparticleSynchronization;
//
//
//   SUBPARTICLE() :
//      m_papplication(nullptr)
//   {}
//
//
//};

#include "quantum.h"
//#include "subparticle_flags.h"



class CLASS_DECL_ACME subparticle :
   virtual public ::quantum
   //virtual public SUBPARTICLE_FLAGS
{
public:

   
   //void * m_pAllocation = nullptr;

   ::interlocked_count                 m_countReference;
   ::sequence *                        m_psequence;


#if REFERENCING_DEBUGGING
   subparticle();
#else
   subparticle() :
      m_countReference(1),
      m_psequence(nullptr)
   {
         
         
   }
#endif
   ~subparticle() override;


#if REFERENCING_DEBUGGING
   
   
   virtual void on_after_construct(::reference_referer* preferer);


#endif


   virtual void initialize(::particle * pparticle);
   virtual void finalize();


   ::platform::system* system() const;

   virtual void on_sequence();
   


   virtual bool defer_consume_main_arguments(int argc, char ** argv, int & iArgument);

   virtual void call();

   virtual ::string get_debug_title() const;

   virtual ::string get_short_debug_text(int i) const;

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

   ::subparticle * get_top_track() const;
   void add_top_track(::subparticle* psubparticle);
   void erase_top_track(::subparticle* psubparticle);
   bool contains_top_track(::subparticle* psubparticle) const;
   bool find_top_track(::subparticle* psubparticle, ::subparticle** ppsubparticleeParent) const;


   class ::time                        m_timeAllocation;
   class reference_item_array *        m_preferenceitema = nullptr;
   bool                                m_bHeapAllocation = false;
   void *                              m_pType = nullptr;
   memsize                             m_sType = sizeof(::subparticle);
   ::reference_referer *               m_prefererTransfer2 = nullptr;
   bool                                m_bReferencingDebuggingEnabled : 1 = true;
   bool                                m_bIncludeCallStackTrace : 1 = false;

   void set_size_type(memsize s) { m_sType = s; }

   bool contains_object_in_address_space(::subparticle * psubparticle) const
   {

      return
         ::is_set(this->m_pType)
         && this->m_sType >= sizeof(::subparticle)
         && ((unsigned char *)psubparticle >= this->m_pType
         && (((unsigned char *)psubparticle) + psubparticle->m_sType)
         <= (((unsigned char *)this->m_pType) + this->m_sType));

   }

   class reference_item_array * reference_itema();

   bool is_referencing_debugging_enabled() const
   {

      return m_bReferencingDebuggingEnabled;

   }

   void disable_referencing_debugging();

   //void add_initial_reference_item();
   void add_reference_item(bool bIncludeCallStackTrace);
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

//#if REFERENCING_DEBUGGING
//
//   virtual void set_creation_referer(::reference_referer* preferer);
//
//#endif

   virtual void delete_this();

   //void operator delete(void* p);



   virtual void write_to_stream(::binary_stream & stream);
   virtual void read_from_stream(::binary_stream & stream);

   [[nodiscard]] virtual class ::time timeout() const;


   virtual void set_timeout(const class time & time);

   virtual hsynchronization get_synchronization_handle();


   // currently expected returned statuses:
// ::error_failed
// ::error_wait_timeout
// ::success
   virtual ::e_status lock();
   virtual ::e_status lock(const class time& timeWait);

   virtual ::e_status wait();
   virtual ::e_status wait(const class time& timeWait);

   virtual void _lock();
   virtual bool _lock(const class time& timeWait);

   virtual void _wait();
   virtual bool _wait(const class time& timeWait);

   virtual bool is_locked() const;

   virtual void unlock();
   virtual void unlock(int lCount, int* pPrevCount=nullptr);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();

};






