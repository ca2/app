// Injected in acme (camilo) from apex(thomas) by camilo on ThomasMonth19-2021 12:27 BRT
// Merge with control_"topic" by camilo on day after ThomasBirthday2021 10:14
// Created by camilo on 2021-02-04 18:05 <3ThomasBorregaardSørensen!!
// Renamed to topic by camilo on 2021-02-04 18:05 <3ThomasBorregaardSørensen!!
// From handler: on 2022-10-30 08:15 <3ThomasBorregaardSørensen!!
//    From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
//    From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
//    From aura by camilo on ThomasBirthday2021 20:00 BRT
//
//    a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/primitive/primitive/e_flag.h"
#include "acme/platform/tracer.h"


class extended_topic;


CLASS_DECL_ACME ::factory::factory * get_system_factory();


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

#include "particle_flags.h"

struct PARTICLE :
   public PARTICLE_FLAGS
{


   ::acme::context *                   m_pcontext;
   ::particle *                        m_pparticleSynchronization;
   hsynchronization                    m_hsynchronization;


   PARTICLE() : 
      m_pcontext(nullptr), 
      m_pparticleSynchronization(nullptr),
      m_hsynchronization(nullptr)
   {}




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


   inline ::particle * synchronization() const { return ::is_set(this) ? m_pparticleSynchronization : nullptr; }
   void set_synchronization(::particle * pparticleSynchronization);
   void defer_create_synchronization();



   virtual enum_type get_payload_type() const;

   //virtual void destroy();

   //virtual void initialize(::particle * pparticle);
   virtual void on_initialize_particle();


   ::acme::application * acmeapplication();
   ::acme::session * acmesession();
   ::aura::application* auraapplication();


   ::acme_file * acmefile();
   ::acme_path * acmepath();
   ::acme_directory * acmedirectory();
   ::acme::node * acmenode();
   ::acme::system * acmesystem();
   ::acme::context* acmecontext();
   ::apex::context* apexcontext();
   ::aura::context* auracontext();
   ::sub_system * subsystem();
   ::datetime::datetime * datetime();
   ::url::url * url();
   ::crypto::crypto * crypto();
   ::nano::nano* nano();
   ::os_context * os_context();


   ::apex::application * apexapplication();


   ::dir_context * dir();
   ::dir_system * dirsystem();
   ::file_context * file();
   ::file_system * filesystem();


   virtual ::factory::factory_pointer & factory();
   virtual ::factory::factory_pointer & factory(const ::string& strLibrary);
   virtual ::factory::factory_pointer & factory(const ::string& strComponent, const ::string& strImplementation);
   //::factory::factory* factory(const ::atom& atom);

   //virtual void handle(::topic * ptopic, ::context * pcontext);




   inline bool is_null() const { return ::is_null(this); }
   inline bool is_set() const { return !is_null(); }

   virtual bool _is_ok() const;
   inline bool is_ok() const { return is_set() && _is_ok(); }
   inline bool nok() const { return !is_ok(); }

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
   //virtual const char * raw_class_title() const;



   // currently expected returned statuses:
   // ::error_failed
   // ::error_wait_timeout
   // ::success
   virtual ::e_status lock();
   virtual ::e_status lock(const class time & timeWait);

   virtual ::e_status wait();
   virtual ::e_status wait(const class time & timeWait);

   virtual void _lock();
   virtual bool _lock(const class time & timeWait);

   virtual void _wait();
   virtual bool _wait(const class time & timeWait);

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



   virtual void trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(enum_trace_category etracecategory, const ::ansi_character * pszFormat, va_list & arguments);


   virtual void trace_arguments(enum_trace_level etracelevel, const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_information_arguments(const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_warning_arguments(const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_error_arguments(const ::ansi_character * pszFormat, va_list & arguments);
   virtual void trace_log_fatal_arguments(const ::ansi_character * pszFormat, va_list & arguments);


   virtual void trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...);
   virtual void trace_log_information(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...);
   virtual void trace_log_warning(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...);
   virtual void trace_log_error(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...);
   virtual void trace_log_fatal(enum_trace_category etracecategory, const ::ansi_character * pszFormat, ...);


   virtual void trace(enum_trace_level etracelevel, const ::ansi_character * pszFormat, ...);
   virtual void trace_log_information(const ::ansi_character * pszFormat, ...);
   virtual void trace_log_warning(const ::ansi_character * pszFormat, ...);
   virtual void trace_log_error(const ::ansi_character * pszFormat, ...);
   virtual void trace_log_fatal(const ::ansi_character * pszFormat, ...);


   inline tracer trace(enum_trace_level etracelevel) { return tracer(m_pcontext, etracelevel, trace_category()); }
   inline tracer trace_log_information() { return tracer(m_pcontext, e_trace_level_information, trace_category()); }
   inline tracer trace_log_warning() { return tracer(m_pcontext, e_trace_level_warning, trace_category()); }
   inline tracer trace_log_error() { return tracer(m_pcontext, e_trace_level_error, trace_category()); }
   inline tracer trace_log_fatal() { return tracer(m_pcontext, e_trace_level_fatal, trace_category()); }


   inline tracer trace(enum_trace_level etracelevel, enum_trace_category etracecategory) { return tracer(m_pcontext, etracelevel, etracecategory); }
   inline tracer trace_log_information(enum_trace_category etracecategory) { return tracer(m_pcontext, e_trace_level_information, etracecategory); }
   inline tracer trace_log_warning(enum_trace_category etracecategory) { return tracer(m_pcontext, e_trace_level_warning, etracecategory); }
   inline tracer trace_log_error(enum_trace_category etracecategory) { return tracer(m_pcontext, e_trace_level_error, etracecategory); }
   inline tracer trace_log_fatal(enum_trace_category etracecategory) { return tracer(m_pcontext, e_trace_level_fatal, etracecategory); }



   virtual ::particle * clone() const;


   // ThomasBorregaardSørensen!! Like handlers
   //virtual void call(const enum_message, i64 iData = 0, ::matter * pmatter = nullptr);
   //virtual void call(const enum_id, i64 iData = 0, ::matter* pmatter = nullptr);
   virtual void call(const ::atom & atom, i64 wParam = 0, i64 lParam = 0, ::particle * pparticle = nullptr);


   // ThomasBorregaardSørensen!! Like handlers
   virtual void handle(::topic * ptopic, ::context * pcontext);
   virtual void handle(::message::message * pmessage);


   virtual bool _handle_uri(const ::string & strUri);
   virtual bool _handle_call(::payload & payload, const ::string & strObject, const ::string & strMember, ::property_set & propertyset);

   // <3ThomasBorregaardSørensen__!! likes handler concept...
   //void route(::signal * psignal) override;
   //void signal(::signal * psignal) override;
   //void route(::topic * ptopic, ::context * pcontext) override;
   //void post_process(::topic * ptopic, ::context * pcontext) override;



//   void run() override;
   virtual ::payload realize();


   //virtual ::element * clone() const;

   

   virtual void set_generic_object_name(const ::scoped_string & scopedstrName);
   virtual void set_library_name(const ::scoped_string & scopedstrLibraryName);
   // if this is an application/or nano application
   virtual void set_application_id(const ::scoped_string & scopedstrApplicationId);


//   // currently expected returned statuses:
//   // ::error_failed
//   // ::error_wait_timeout
//   // ::success
//   // also see synchronization//   virtual ::e_status wait();
//   virtual ::e_status wait(const class time & timeWait);


   [[nodiscard]] virtual class ::time timeout() const;


   virtual void set_timeout(const class time & time);


   virtual ::particle * get_taskpool_container();


   virtual ::task_pool * taskpool();



   virtual const char* debug_note() const;



   [[nodiscard]] virtual bool should_run_async() const;


   pointer < ::sequencer < ::conversation > > message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

   pointer < ::sequencer < ::conversation > > exception_message_box(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

   pointer < ::sequencer < ::conversation > > message_console(const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);

   pointer < ::sequencer < ::conversation > > exception_message_console(const ::exception& exception, const ::string& strMessage = nullptr, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);


   virtual ::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr);
   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary);
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);


   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE>__create(::factory::factory* pfactory = ::get_system_factory());

   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE>__id_create(const ::atom& atom, ::factory::factory* pfactory = ::get_system_factory());

   template < typename TYPE >
   inline ::pointer<TYPE>__create_new();

   //template < typename BASE_TYPE >
   //inline void __raw_construct(::pointer<BASE_TYPE> & p, ::factory::factory * pfactory = ::get_system_factory());

   template < typename BASE_TYPE >
   inline void __defer_construct(::pointer<BASE_TYPE>& ptype, ::factory::factory* pfactory = ::get_system_factory());

   template < typename TYPE >
   inline void __defer_construct_new(::pointer<TYPE>& ptype);

   template < typename BASE_TYPE >
   inline void __construct(::pointer<BASE_TYPE>& ptype, ::factory::factory* pfactory = ::get_system_factory());

   template < typename BASE_TYPE, typename TYPE >
   inline void __construct(::pointer<BASE_TYPE>& ptype, const ::pointer < TYPE >& p);

   template < typename BASE_TYPE, typename TYPE >
   inline void __construct(::pointer<BASE_TYPE>& ptype, TYPE* p);

   template < typename BASE_TYPE >
   inline void __id_construct(::pointer<BASE_TYPE>& ptype, const ::atom& atom, ::factory::factory* pfactory = ::get_system_factory());

   template < typename TYPE >
   inline void __construct_new(::pointer<TYPE>& ptype);


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


   virtual void kick_idle();


};

//
//
//#define OPTIONAL_BASE_BODY                                                          \
//public:                                                                             \
//   void on_initialize_particle() override {}         \
//   void handle(::topic*,::context*) override {}
//
////   void assert_ok() const override {}                                    \
////   void dump(dump_context&) const override {}                               \
//   //void on_subject(::topic::topic*, ::context*) override {} \
//
//#define OPTIONAL_INTERACTION_BODY                                                   \
//   OPTIONAL_BASE_BODY                                                               \
//   void install_message_routing(::channel*) override {}                     \
//   void on_layout(::draw2d::graphics_pointer&) {}
//
//
//class optional_base1 : virtual public ::particle { OPTIONAL_BASE_BODY };
//class optional_base2 : virtual public ::particle { OPTIONAL_BASE_BODY };
//class optional_base3 : virtual public ::particle { OPTIONAL_BASE_BODY };
//class optional_base4 : virtual public ::particle { OPTIONAL_BASE_BODY };
//
//class optional_interaction1 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
//class optional_interaction2 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
//class optional_interaction3 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
//class optional_interaction4 : virtual public ::particle { OPTIONAL_INTERACTION_BODY };
//

template < typename T >
inline i64 release(T*& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//{
//
//   if (::is_null(p))
//   {
//
//      return -1;
//
//   }
//
//   ::particle* pparticle = p;
//
//   try
//   {
//
//      p = nullptr;
//
//   }
//   catch (...)
//   {
//
//      ::output_debug_string("exception release p = nullptr; \n");
//
//   }
//
//   try
//   {
//
//      return pparticle->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   }
//   catch (...)
//   {
//
//      ::output_debug_string("exception release pparticle->release() \n");
//
//   }
//
//   return -1;
//
//}


template < typename T >
inline i64 global_release(T*& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//{
//
//   if (::is_null(p))
//   {
//
//      return -1;
//
//   }
//
//   try
//   {
//
//      auto i = p->release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//      if (i <= 0)
//      {
//
//         p = nullptr;
//
//      }
//
//      return i;
//
//   }
//   catch (...)
//   {
//
//      ::output_debug_string("exception release pparticle->release() \n");
//
//   }
//
//   return -1;
//
//}
//
//


//
//
//#if !defined(_DEBUG)
//
//
//i64 particle::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//{
//
//   auto c = ++m_countReference;
//
//#if OBJECT_REFERENCE_COUNT_DEBUG
//
//   add_ref_history(pReferer, pszObjRefDbg);
//
//#endif
//
//   return c;
//
//}
//
//
//i64 particle::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//{
//
//   auto c = --m_countReference;
//
//#if OBJECT_REFERENCE_COUNT_DEBUG
//
//   if (c > 0)
//   {
//
//      dec_ref_history(pReferer, pszObjRefDbg);
//
//   }
//
//#endif
//
//   return c;
//
//}
//
//
//i64 particle::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//{
//
//   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//   if (i == 0)
//   {
//
//      delete_this();
//
//   }
//
//   return i;
//
//}
//
//
//#endif
