#pragma once


#include "particle.h"
#include "pointer.h"
#include "atom.h"
#include "factory.h"
#include "function.h"
#include "acme/platform/tracer.h"
#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/collection/procedure_array.h"


class CLASS_DECL_ACME matter :
   virtual public ::particle
{
public:


   typedef void POSTING_PROCEDURE(const ::procedure & procedure);
   typedef ::payload RETURNING_PROCEDURE();

   
   union
   {

      unsigned int       m_uError;

      struct
      {

         bool        m_bTimeout : 1;

      };

   };


   class ::atom                        m_atomMatterId;

//   ::eobject                           m_eobject;

//#if REFERENCING_DEBUGGING
//   inline matter() : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_uObject(0), system()(nullptr) { increment_reference_count( REFERENCING_DEBUGGING_COMMA_NOTE("Initial Reference")); }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(eobject), m_uObject(0), system()(nullptr) { increment_reference_count( REFERENCING_DEBUGGING_COMMA_NOTE("Initial Reference (2)")); }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_pobjrefdbg(nullptr), m_countReference(0), m_eobject(matter.m_eobject), m_uObject(0), system()(nullptr) { if (matter.m_pmutex) defer_create_synchronization(); increment_reference_count( REFERENCING_DEBUGGING_COMMA_NOTE("Initial Reference (3)")); }
//   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_pobjrefdbg(matter.m_pobjrefdbg), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0), system()(nullptr) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
//#else
//   inline matter() : m_pmutex(nullptr), m_countReference(1), m_uObject(0), system()(nullptr) { }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_countReference(1), m_eobject(eobject), m_uObject(0), system()(nullptr) { }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_countReference(1), m_eobject(matter.m_eobject), m_uObject(0), system()(nullptr) { if (matter.m_pmutex) defer_create_synchronization(); }
//   inline matter(matter&& matter) : m_pmutex(matter.m_pmutex), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_uObject(0), system()(nullptr) { matter.m_pmutex = nullptr; }
//#endif

//#if REFERENCING_DEBUGGING
//   inline matter() : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(e_object_none), m_papplication(nullptr), m_pobjrefdbg(nullptr) { }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_countReference(0), m_eobject(eobject), m_papplication(nullptr), m_pobjrefdbg(nullptr) {  }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(0), m_eobject(matter.m_eobject), m_papplication(matter.m_papplication), m_pobjrefdbg(nullptr) {  }
//   inline matter(matter&& matter) : referenceable(matter),m_pmutex(matter.m_pmutex), m_estatus(e_status_none), m_ematter(matter.m_ematter), m_uError(matter.m_uError), m_countReference(matter.m_countReference), m_eobject(matter.m_eobject), m_papplication(matter.m_papplication), m_pobjrefdbg(matter.m_pobjrefdbg) { matter.m_pmutex = nullptr; matter.m_pobjrefdbg = nullptr; }
//   inline matter(::platform::context * pcontext) : m_papplication(pcontext), m_pmutex(nullptr), m_estatus(e_status_none), m_ematter(e_element_none), m_uError(0), m_eobject(e_object_none), m_pobjrefdbg(matter.m_pobjrefdbg) { }
//#else
//   inline matter() : m_pmutex(nullptr), m_uError(0), m_eobject(e_object_none) { }
//   inline matter(const eobject& eobject) : m_pmutex(nullptr), m_uError(0), m_eobject(eobject) { }
//   inline matter(const matter& matter) : m_pmutex(nullptr), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_papplication(matter.m_papplication) { if (matter.m_pmutex) defer_create_synchronization(); }
//   inline matter(matter&& matter) : element(matter), m_pmutex(matter.m_pmutex), m_uError(matter.m_uError), m_eobject(matter.m_eobject), m_papplication(matter.m_papplication) { matter.m_pmutex = nullptr; }
//   inline matter(::platform::context * pcontext) : m_papplication(pcontext), m_pmutex(nullptr), m_uError(0), m_eobject(e_object_none) { }
//#endif

   matter() {}
   ~matter() override;


   //virtual void  assert_ok() const;
   //virtual void  dump(dump_context& dumpcontext) const;


   ::atom & id() { return m_atomMatterId; }
   const ::atom & id() const { return m_atomMatterId; }
   


   void operator()(::topic * ptopic, ::handler_context * phandlercontext) override;


   virtual void operator()(::message::message * pmessage);
   //virtual void operator()(const ::payload & payload);


    //// <3TBS_!! handle -> command_handler <3TBS_(I need to suck you)!!
   virtual void handle_command(const ::atom & atom);
//{
//
//   //return ::success_none;
//
//}

   inline bool has_error() const {return m_uError != 0;}

   //inline bool is_set() const { return ::is_set(this); }




   virtual bool is_ready_to_quit() const;

   // synchronization/::pointer < ::mutex >

   //void branch();


   //::platform::context * get_context() const { return (::platform::context *) m_papplication; }
   //::platform::system * system() const;

   inline ::platform::application * get_app() { return _get_app(); }

   virtual ::platform::application * _get_app();

   virtual bool is_thread() const;
   virtual ::thread * get_thread();
   virtual bool thread_is_running() const;


   virtual ::task * get_task();
   virtual const char * get_task_tag();
   //virtual ::collection::index task_add(::task* pthread);
   virtual void task_erase(::task* pthread);

   virtual void notify_on_destroy(::property_object * pparticle);


   void set_finish() override;
   void destroy() override;

   virtual void on_set_finish();


   //virtual void do_task();
   //virtual void on_task();


   // virtual void task_osinit();
   // virtual void __task_init();
   // virtual void __task_main();
   // virtual void __task_term();
   // virtual void task_osterm();


//   virtual void add_composite(::particle * pparticle);
//   virtual void add_reference(::particle * pparticle);
//
//
//   virtual void release_composite2(::particle * pparticle);
//   virtual void finalize_composite(::particle * pparticle);
//   virtual void release_reference(::particle * pparticle);


   //virtual void set_generic_object_name(const ::scoped_string & scopedstrName);



   //virtual ::task * defer_branch(const ::atom & atom, const ::procedure & procedure);


   //::particle * clone() const override;


   using particle::has_flag;
   using particle::set_flag;
   using particle::clear_flag;


//   inline bool has(const ::eobject& eobject) const { return m_eobject.has(eobject); }
//   inline void set(const ::eobject& eobject, bool bSet) { if (bSet) set(eobject); else clear(eobject); }
//   inline void set(const ::eobject & eobject) { m_eobject |= eobject; }
//   inline void clear(const ::eobject& eobject) { m_eobject -= eobject; }


   //inline unsigned long long get_object_flag() { return m_eobject; }


   //inline bool is(enum_matter ematter) const { return (m_ematter & ematter) == ematter; }
   //inline void set(enum_matter ematter) { m_ematter = (enum_matter) ((unsigned int)(m_ematter) | (unsigned int)(ematter)); }
   //inline void unset(enum_matter ematter) { m_ematter = (enum_matter)((unsigned int)(m_ematter) & (~(unsigned int)(ematter))); }


   //inline bool is_finishing() const { return is(e_element_finishing); }
   //inline void set_finishing() { set(e_element_finishing); }
   //inline void unset_finishing() { unset(e_element_finishing); }


   //inline bool is_heap_allocated() const { return is(e_element_heap_allocated); }
   //inline void set_heap_allocated() { set(e_element_heap_allocated); }
   //inline void unset_heap_allocated() { unset(e_element_heap_allocated); }


   //inline bool is_destroying() const { return is(e_element_destroying); }
   //inline void set_destroying() { set(e_element_destroying); }
   //inline void unset_destroying() { unset(e_element_destroying); }


   //virtual void on_finish();
   //virtual void set_finish(::property_object * pcontextobjectFinish);
   //virtual void set_finish();


   // returns success when object is ready to have destroy called
   // returns error_pending if any child or ascendant is still active
   //virtual void finish(::property_object * pcontextobjectFinish = nullptr);
   //virtual void destroy_composites();

   virtual bool __get_posted_payload_synchronously(const ::function < void(const ::procedure &) > & functionPost, const ::function < ::payload(void) > & functionReturn, ::payload & payload);

   virtual void __send_procedure(const ::function < void(const ::procedure &) > & functionPost, const ::procedure & procedure);

   virtual void post_quit();





   inline const ::particle * context_trace_object() const { return this; }


   //virtual void __tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const;
   //virtual void __tracef(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, ...) const;
   //virtual void __tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args) const;

   //virtual void __simple_tracev(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstrFormat, va_list args) const;
   //virtual void __simple_tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, int iLine, const ::scoped_string & scopedstr) const;









   //using particle::trace;
   //using particle::trace_log_information;
   //using particle::trace_log_warning;
   //using particle::trace_log_error;
   //using particle::trace_log_fatal;


   virtual void trace_last_status();


   //virtual void on_sequence(const ::payload & payload);

   virtual void clear_member() { }



   //::pointer < ::subparticle > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr);


   //::topic_pointer create_topic(const ::atom & atom);


   bool _handle_uri(const ::string & strUri) override;
   bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset) override;


   virtual bool handle_uri(const ::string & stringUri);
   virtual bool handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset);


   inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());
   inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());
   inline ::file_pointer fully_shared_reader(const ::payload& payloadFile) { return get_reader(payloadFile, ::file::e_open_share_deny_none); }

   //virtual void to_string(string & str) const override;

   virtual ::string class_title();

   

};





//template < typename INTERMEDIATE, typename RELEASEE >
//inline void release(INTERMEDIATE*, RELEASEE* & p)
//{
//
//   ::release(p);
//
//}
//


class __construct_site
{
public:


   template < typename T >
   __construct_site(::pointer < T >& p COMMA_REFERENCING_DEBUGGING_PARAMETERS_DECLARATION)
   {

      p = __pointer_site(__refdbg_referer__) << new T;

   }


};


template < typename TYPE >
inline void __call__raw_construct_new(::pointer<TYPE> & ptype)
{

   ptype = { transfer_t{}, __new_refdbg_continuation TYPE() };

}


template < typename TYPE >
inline bool __defer_raw_construct_new(::pointer<TYPE> & ptype)
{

   if(ptype.is_null())
   {

      __raw_construct_new(ptype);
      
      return ptype.is_set();

   }
   
   return false;

}


//template < typename TYPE >
//inline ::pointer<TYPE> matter::__øcreate(::factory::factory * pfactory)
//{
//
//   return ::__øcreate<TYPE>(this, pfactory);
//
//}



//
//template < typename TYPE >
//inline ::pointer<TYPE>matter::__id_create(const ::atom & atom, ::factory::factory * pfactory)
//{
//
//   auto pfactoryitem = pfactory->get_factory_item(atom);
//
//   if (!pfactoryitem)
//   {
//
//      throw_exception(error_no_factory);
//
//   }
//
//   auto ptypeNew = pfactoryitem->create_particle();
//
//   if (!ptypeNew)
//   {
//
//      throw_exception(error_no_memory);
//
//   }
//
//   ::pointer<TYPE>p;
//
//   p = ptypeNew;
//
//   if (!p)
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   p->set_flag(e_flag_factory);
//
//   //auto estatus = p->initialize(this);
//
//   p->initialize(this);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   return ::transfer(p);
//
//}
//

//template < typename TYPE >
//inline ::pointer<TYPE>matter::__create_new()
//{
//
//   return ::__create_new<TYPE>(this);
//
//}



//template < typename BASE_TYPE >
//inline void matter::__raw_construct(::pointer<BASE_TYPE> & p, ::factory::factory * pfactory)
//{
//
//   ::__raw_construct(this, p, pfactory);
////   //{
////
////   auto & pfactory = factory_item < BASE_TYPE >();
////
////   if (!pfactory)
////   {
////
////      throw_exception(::error_no_factory);
////
////   }
////
////   auto pelement = pfactory->create_element();
////
////   if (!pelement)
////   {
////
////      throw_exception(::error_no_memory);
////
////   }
////
////   p = pelement;
////
////   if (!p)
////   {
////
////      throw_exception(error_wrong_type);
////
////   }
////
////   ///*auto estatus = */ add_composite(pusermessage);
////
////   //if (!estatus)
////   //{
////
////   //   return estatus;
////
////   //}
////
//////}
////
//////return ::success;
//
//}

//
//template < typename TYPE >
//inline void particle::__øconstruct(::pointer<TYPE> & p, ::factory::factory * pfactory)
//{
//
//   ::__øconstruct(this, p, pfactory);
//
//}


//template < typename BASE_TYPE, typename TYPE >
//inline void particle::__call__construct(::pointer<BASE_TYPE> & ptype, const ::pointer < TYPE > & p)
//{
//
//   __call__construct(ptype, p.m_p);
//
//}
//
//
//template < typename BASE_TYPE, typename TYPE >
//inline void particle::__call__construct(::pointer<BASE_TYPE> & ptype, TYPE * p)
//{
//
//   if (::is_null(p))
//   {
//
//      error() << "particle::__øconstruct p is null";
//
//      throw_exception(::error_null_pointer);
//
//   }
//
//   ptype = p;
//
//   if (::is_null(ptype))
//   {
//
//      error() <<"particle::__øconstruct p is null (is assignee type derived from BASE_TYPE?";
//
//      throw_exception(::error_null_pointer);
//
//   }
//
//   ptype->initialize(this);
//
//}


//template < typename TYPE >
//inline void particle::__id_construct(::pointer<TYPE> & p, const ::atom & atom)
//{
//
//   ::__id_construct(this, p, atom);
//
//}


//
//template < typename TYPE >
//inline void matter::__construct_new(::pointer<TYPE> & p)
//{
//
//   ::__construct_new(this, p);
//
//}


//template < typename BASE_TYPE >
//inline void matter::__release(::pointer<BASE_TYPE> pcomposite)
//{
//
//   if (::is_set(pcomposite))
//   {
//
//      //synchronous_lock synchronouslock(this->synchronization());
//
//      //if (m_pcompositea)
//      //{
//
//      //   if (m_pcompositea->erase(pcomposite.get()) >= 0)
//      //   {
//
//            pcomposite.clear_member();
//
//      //   }
//
//      //}
//
//   }
//
//   //return ::success;
//
//}
//
//
//template < typename BASE_TYPE >
//inline void matter::__release(::pointer<BASE_TYPE> preference)
//{
//
//   if (::is_set(preference))
//   {
//
//      //synchronous_lock synchronouslock(this->synchronization());
//
//      //if (m_preferencea)
//      //{
//
//      //   if (m_preferencea->erase(preference.get()) >= 0)
//      //   {
//
//            //preference->release();
//
//            preference.clear_member();
//
//   //      }
//   //      else
//   //      {
//
//   //         return ::error_failed;
//
//   //      }
//
//   //   }
//
//   }
//
//   //return ::success;
//
//}
//
//
//template < typename SOURCE >
//inline void matter::__release(::pointer<SOURCE> psource)
//{
//
//   release_reference(psource.m_p);
//
//}


//CLASS_DECL_ACME void object_on_add_composite(const element* pusermessage);


//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource )
//{
//
//   __refer(preference, psource.get() );
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE> preference, const ::primitive::member < SOURCE >& pmember)
//{
//
//   __refer(preference, pmember.get() );
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__refer(::pointer<BASE_TYPE> preference, const SOURCE* psource)
//{
//
//   preference = psource;
//
//   if (!preference)
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   add_reference(preference);
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__defer_refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource )
//{
//
//   __defer_refer(preference, psource.get() );
//
//}
//
//
//template < typename BASE_TYPE, typename SOURCE >
//inline void matter::__defer_refer(::pointer<BASE_TYPE> preference, const SOURCE* psource)
//{
//
//   if (preference.get() != psource)
//   {
//
//      __release(preference);
//
//      preference = psource;
//
//      if (preference)
//      {
//
//         add_reference(preference);
//
//      }
//
//   }
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(::pointer<SOURCE> psource )
//{
//
//   add_reference(psource.get());
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(::pointer<SOURCE> preference)
//{
//
//   add_reference(preference.get());
//
//}
//
//
//template < typename SOURCE >
//inline void matter::add_reference(SOURCE* psource)
//{
//
//   ::particle * pparticle = psource;
//
//   if (::is_null(pelement))
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   add_reference(pelement);
//
//}


inline ::file_pointer matter::get_reader(const ::payload & payloadFile, ::file::e_open eopen)
{

   return get_file(payloadFile, eopen | ::file::e_open_read);

}


inline ::file_pointer matter::get_writer(const ::payload & payloadFile, ::file::e_open eopen)
{

   return get_file(payloadFile, eopen | ::file::e_open_write);

}




