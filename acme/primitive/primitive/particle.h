// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSorensen!!
// From handler: on 2022-10-30 08:15 <3ThomasBorregaardSorensen!!
//    From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
//    From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
//    From aura by camilo on ThomasBirthday2021 20:00 BRT
//
//    a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/primitive/primitive/e_flag.h"


class extended_topic;


//struct PARTICLE
//{
//public:
//
//
//
//   PARTICLE()
//   {
//
//   }
//
//
//
//
//};


#include "acme/primitive/primitive/interlocked_count.h"


using hsynchronization = void *;


struct PARTICLE
{


   ::acme::context *                   m_pcontext;
   ::e_flag                            m_eflagElement;
   union
   {
      mutable ::particle *             m_pparticleSynchronization;
      mutable hsynchronization         m_hsynchronization;
   };
   ::e_status                          m_estatus;



   PARTICLE() : m_pcontext(nullptr), m_pparticleSynchronization(nullptr), m_estatus(e_status_none)  {}


   [[nodiscard]] inline bool has(enum_flag eflag) const { return (m_eflagElement & eflag) == eflag; }
   inline void set(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) | (::u64)(eflag)); }
   inline void set(enum_flag eflag, bool bSet) { if (bSet) set(eflag); else clear(eflag); }
   inline void clear(enum_flag eflag) { m_eflagElement = (enum_flag)((::u64)(m_eflagElement) & (~(::u64)(eflag))); }


   inline void set_ok() { set(e_flag_success); clear(e_flag_timeout); clear(e_flag_failure); }
   inline void set_nok(enum_flag estatusFailure = e_flag_failure) { clear(e_flag_success); set(estatusFailure); }
   inline void set_modified(bool bModified = true) { set(e_flag_changed, bModified); }


   inline void set_fail() { set(e_flag_failure); clear(e_flag_success); }
   inline void set_timed_out() { set(e_flag_timeout); }
   inline void set_persistent(bool bSet = true) { set(e_flag_persist, bSet); }


   [[nodiscard]] inline bool is_ok() const { return has(e_flag_success); }
   [[nodiscard]] inline bool nok() const { return has(e_flag_failure) || has(e_flag_timeout); }
   [[nodiscard]] inline bool has_timed_out() { return has(e_flag_timeout); }
   [[nodiscard]] inline bool is_modified() const { return has(e_flag_changed); }
   [[nodiscard]] inline bool is_persistent() const { return has(e_flag_persist); }

   [[nodiscard]] inline bool is_shared2() const { return has(e_flag_shared); }
   inline void set_shared(bool bSet = true) { set(e_flag_shared, bSet); }


   [[nodiscard]] inline bool is_finishing() const { return has(e_flag_finishing); }
   inline void set_finishing() { set(e_flag_finishing); }
   inline void unset_finishing() { clear(e_flag_finishing); }


   [[nodiscard]] inline bool is_acquired() const { return has(e_flag_acquired); }
   inline void set_acquired() { set(e_flag_acquired); }
   inline void unset_acquired() { clear(e_flag_acquired); }

   [[nodiscard]] inline bool is_own_synchronization() const { return has(e_flag_own_synchronization); }
   inline void set_own_synchronization(bool bSet = true) { set(e_flag_own_synchronization, bSet); }
   inline void unset_own_synchronization() { clear(e_flag_own_synchronization); }


   [[nodiscard]] inline bool already_exists() const { return has(e_flag_already_exists); }
   inline void set_already_exists(bool bSet = true) { set(e_flag_already_exists, bSet); }
   inline void unset_already_exists() { clear(e_flag_already_exists); }


   // [[nodiscard]] inline bool is_heap_allocated() const { return has(e_flag_heap_allocated); }
   // inline void set_heap_allocated() { set(e_flag_heap_allocated); }
   // inline void unset_heap_allocated() { clear(e_flag_heap_allocated); }


   [[nodiscard]] inline bool is_destroying() const { return has(e_flag_destroying); }
   inline void set_destroying() { set(e_flag_destroying); }
   inline void unset_destroying() { clear(e_flag_destroying); }


   [[nodiscard]] inline bool is_storing() const { return has(e_flag_storing); }
   [[nodiscard]] inline bool is_loading() const { return !is_storing(); }


   inline void set_storing() { set(e_flag_storing); }
   inline void set_loading() { clear(e_flag_storing); }


   inline void defer_set_storing() { if (!is_storing()) set_storing(); }
   inline void defer_set_loading() { if (!is_loading()) set_loading(); }


   inline void set_statically_allocated() { set(e_flag_statically_allocated); }
   inline void set_verbose(bool bVerbose = true) { set(e_flag_verbose, bVerbose); }
   [[nodiscard]] inline bool is_verbose() const { return has(e_flag_verbose); }


};




// ThomasBorregaardSørensen!! Like handlers : now particle with handle::handlers*
class CLASS_DECL_ACME particle :
   virtual public PARTICLE
{
public:


   ::interlocked_count                 m_countReference;


#if OBJECT_REFERENCE_COUNT_DEBUG
   inline particle() { increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_THIS OBJECT_REFERENCE_COUNT_DEBUG_COMMA_NOTE("Initial Reference")); }
#else
   inline particle() : m_countReference(1) { }
#endif


   virtual ~particle();


   virtual void initialize(::particle * pparticle);


#ifdef _DEBUG

   virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#else

   inline i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
   inline i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);

#endif

   virtual void delete_this();


   inline ::particle * synchronization() const { return ::is_set_ptr(this) ? m_pparticleSynchronization : nullptr; }
   void set_synchronization(::particle * pparticleSynchronization);
   void defer_create_synchronization();


   virtual enum_type get_payload_type() const;

   //virtual void destroy();

   //virtual void initialize(::particle * pparticle);
   virtual void on_initialize_particle();


   ::acme::application * acmeapplication();


   ::acme_file * acmefile();
   ::acme_path * acmepath();
   ::acme_directory * acmedirectory();
   ::acme::node * acmenode();
   ::acme::system * acmesystem();
   ::sub_system * subsystem();


   ::apex::application * apexapplication();


   ::dir_context * dir();
   ::dir_system * dirsystem();
   ::file_context * file();
   ::file_system * filesystem();



   //virtual void handle(::topic * ptopic, ::context * pcontext);


   virtual ::topic_pointer create_topic(const ::atom & atom);
   virtual ::extended_topic_pointer create_extended_topic(const ::atom & atom);


   virtual void install_message_routing(::channel * pchannel);


   virtual void init_task();

   //virtual void initialize_matter(::matter * pmatter);
   virtual void call_run();


   virtual void run();
   virtual bool step();
   virtual void on_sequence();


   virtual void set_finish();


   // <3TBS_!! handle -> call_member <3TBS_!!
   virtual void call_member(::i64 i64);
   // <3ThomasBS_!! handle -> handle <3ThomasBS_!!
   //void handle(const  emessage, i64 iData = 0, ::matter * pmatter = nullptr) override;
   //void handle(::topic * ptopic, ::context * pcontext) override;
   //void handle(::message::message * pmessage) override;


   virtual bool is_branch_current() const;



   [[nodiscard]] virtual strsize sz_len() const;
   virtual void to_sz(char * sz, strsize len) const;

   virtual const char * topic_text() const;
   virtual const char * class_title() const;



   // currently expected returned statuses:
   // ::error_failed
   // ::error_wait_timeout
   // ::success
   virtual ::e_status lock();
   virtual ::e_status lock(const class ::wait & wait);

   virtual ::e_status wait();
   virtual ::e_status wait(const class ::wait & wait);

   virtual void _lock();
   virtual bool _lock(const class ::wait & wait);

   virtual void _wait();
   virtual bool _wait(const class ::wait & wait);

   virtual bool is_locked() const;

   virtual void unlock();
   virtual void unlock(::i32 /* lCount */, ::i32 * /* pPrevCount=nullptr */);


   virtual void init_wait();
   virtual void exit_wait();


   virtual void acquire_ownership();
   virtual void release_ownership();



   //PARTICLE(const class ::atom & atom) :
   //   m_atom(atom)
   //{

   //}


   //PARTICLE(const PARTICLE & topic) :
   //   m_atom(topic.m_atom)
   //{

   //}


   //PARTICLE(PARTICLE && topic) :
   //   m_atom(topic.m_atom)
   //{

   //}

   virtual enum_trace_category trace_category(const ::particle * pparticle) const;
   virtual enum_trace_category trace_category() const;



   virtual void trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments);


   virtual void trace_arguments(enum_trace_level etracelevel, const char * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(const char * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(const char * pszFormat, va_list & arguments);


   virtual void trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_information(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_warning(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_error(enum_trace_category etracecategory, const char * pszFormat, ...);
   virtual void trace_log_fatal(enum_trace_category etracecategory, const char * pszFormat, ...);


   virtual void trace(enum_trace_level etracelevel, const char * pszFormat, ...);
   virtual void trace_log_information(const char * pszFormat, ...);
   virtual void trace_log_warning(const char * pszFormat, ...);
   virtual void trace_log_error(const char * pszFormat, ...);
   virtual void trace_log_fatal(const char * pszFormat, ...);


   virtual ::particle * clone() const;


   // ThomasBorregaardSørensen!! Like handlers
   //virtual void call(const enum_message, i64 iData = 0, ::matter * pmatter = nullptr);
   //virtual void call(const enum_id, i64 iData = 0, ::matter* pmatter = nullptr);
   virtual void call(const ::atom & atom, i64 wParam = 0, i64 lParam = 0, ::matter * pmatter = nullptr);


   // ThomasBorregaardSørensen!! Like handlers
   virtual void handle(::topic * ptopic, ::context * pcontext);
   virtual void handle(::message::message * pmessage);


   virtual bool _handle_uri(const ::block & blockUri);
   virtual bool _handle_call(::payload & payload, const ::block & blockObject, const ::block & blockMember, ::property_set & propertyset);

   // <3ThomasBorregaardSørensen__!! likes handler concept...
   //void route(::signal * psignal) override;
   //void signal(::signal * psignal) override;
   //void route(::topic * ptopic, ::context * pcontext) override;
   //void post_process(::topic * ptopic, ::context * pcontext) override;



//   void run() override;
   virtual ::payload realize();


   //virtual ::element * clone() const;



   virtual void set_generic_object_name(const char* pszName);
   virtual void set_library_name(const char* pszLibraryName);
   // if this is an application/or nano application
   virtual void set_application_id(const char* pszApplicationId);


//   // currently expected returned statuses:
//   // ::error_failed
//   // ::error_wait_timeout
//   // ::success
//   // also see synchronization//   virtual ::e_status wait();
//   virtual ::e_status wait(const class ::wait & wait);


   [[nodiscard]] virtual ::duration timeout() const;


   virtual void set_timeout(const ::duration & duration);


   virtual ::particle * get_taskpool_container();


   virtual ::task_pool * taskpool();






   [[nodiscard]] virtual bool should_run_async() const;


   //virtual void to_string(string_exchange & str) const;


   //[[nodiscard]] ::enum_type get_payload_type() const;


   //virtual void exchange(::stream& s);
   //virtual void exchange(::payload_stream& s);

   //virtual void write(::binary_stream < FILE >& stream) const;
   //virtual void read(::binary_stream < FILE >& stream);


   //virtual void add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //virtual void add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   //virtual void release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //virtual void finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
   //virtual void release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   virtual void destroy();
   virtual void destroy_impl_data();
   virtual void destroy_os_data();




};



#define OPTIONAL_BASE_BODY                                                          \
public:                                                                             \
   void on_initialize_particle() override {}         \
   void handle(::topic*,::context*) override {}

//   void assert_ok() const override {}                                    \
//   void dump(dump_context&) const override {}                               \
   //void on_subject(::topic::topic*, ::context*) override {} \

#define OPTIONAL_INTERACTION_BODY                                                   \
   OPTIONAL_BASE_BODY                                                               \
   void install_message_routing(::channel*) override {}                     \
   void on_layout(::draw2d::graphics_pointer&) {}


class optional_base1 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base2 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base3 : virtual public ::particle { OPTIONAL_BASE_BODY };
class optional_base4 : virtual public ::particle { OPTIONAL_BASE_BODY };

class optional_interaction1 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction2 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction3 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
class optional_interaction4 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };




