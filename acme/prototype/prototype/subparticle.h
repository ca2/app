// Created by camilo on 2024-02-07 22:52 <3ThomasBorregaardSorensen!!
#pragma once


#include "pointer.h"
#include "acme/prototype/prototype/interlocked_count.h"
#include "acme/prototype/time/time/time.h"
//#include "parallelization/manual_reset_happening.h"

class notify_lock;
#ifdef WINDOWS
using hsynchronization = void*;
#else
using hsynchronization = ::subparticle *;
#endif


class sequence;

#include "quantum.h"




class CLASS_DECL_ACME subparticle :
   virtual public ::quantum
{
public:


   ::interlocked_count                 m_countReference;
   ::pointer < ::sequence >            m_psequence;


#if REFERENCING_DEBUGGING
   subparticle(const ::e_flag & eflag = e_flag_none, const ::e_status & estatus = undefined);
#else
   subparticle(const ::e_flag & eflag = e_flag_none, const ::e_status & estatus = undefined) :
      ::quantum(eflag, estatus),
      m_countReference(1)
   {
         
         
   }
#endif
   ~subparticle() override;


   virtual void initialize(::particle * pparticle);
   //virtual void finalize();


   //virtual bool is_proto() const;
   inline bool should_disable_referencing_debugging() const { return this->has_proto_flag(); }


   ::platform::system* system() const;

   virtual void on_sequence();
   
   virtual bool should_create_sequence_on_synchronicity();

   virtual bool defer_consume_main_arguments(int argc, char ** argv, int & iArgument);

   virtual void call();

   virtual void get_debug_title(char * sz, character_count c) const;

   virtual ::string get_short_debug_text(int i) const;

   virtual void operator()();
   virtual void run();

   virtual class ::time get_run_timeout();

   virtual bool subparticle_step();


   inline ::collection::count reference_count() const { return m_countReference; }


#ifdef _DEBUG


   virtual long long increment_reference_count();
   virtual long long decrement_reference_count();
   virtual long long replace_reference();
   virtual long long release();


#else


   inline long long increment_reference_count();
   inline long long decrement_reference_count();
   inline long long replace_reference();
   inline long long release();


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
   bool                                m_bReferencingDebuggingEnabled5 = true;
   bool                                m_bIncludeCallStackTrace = false;

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

      return !this->should_disable_referencing_debugging() && m_bReferencingDebuggingEnabled5;

   }

   virtual void on_after_construct(::reference_referer* preferer);


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
   virtual void term_task();


   virtual void destroy();
   virtual void destroy_impl_data();
   virtual void destroy_os_data();

   template < typename TYPE >
   ::cast < TYPE > cast() { return this; }

   template < typename TYPE >
   ::cast < TYPE > cast() const { return ((::subparticle *)this)->cast < TYPE >() ; }

   virtual ::subparticle_pointer clone();

//#if REFERENCING_DEBUGGING
//
//   virtual void set_creation_referer(::reference_referer* preferer);
//
//#endif

   virtual void delete_this();

   virtual void call_member(enum_id eid);


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


   [[nodiscard]] virtual character_count sz_len() const;
   virtual void to_sz(char * sz, character_count len) const;


   virtual void on_timed_out();


   virtual bool start_notify_lock(::notify_lock * pnotifylock);
   virtual void end_notify_lock(::notify_lock * pnotifylock);

};


inline bool is_nok(const ::subparticle * p) { return !::is_set(p) || !p->_is_ok(); }




template < typename TYPE >
class proto :
   public TYPE
{
public:


   using TYPE::TYPE;
   using TYPE::operator =;


   proto(const ::e_flag & eflag = e_flag_none, const ::e_status & estatus = undefined):
   TYPE(eflag | e_flag_proto, estatus)
   {

   }


   //
   //
   // ~no_referencing_debugging() override
   // {
   //
   //
   // }

   //
   // bool is_proto() const override
   // {
   //
   //    // if (!(this->m_eflagElement & e_flag_disable_referencing_debugging))
   //    // {
   //    //
   //    //    ((proto *) this)->m_eflagElement |= e_flag_disable_referencing_debugging;
   //    //
   //    // }
   //    //
   //    // if (!this->m_bReferencingDebuggingEnabled3)
   //    // {
   //    //
   //    //    ((proto *) this)->m_bReferencingDebuggingEnabled3 = false;
   //    //
   //    // }
   //
   //    return true;
   //
   // }


};