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


#include "acme/platform/allocator.h"
#include "acme/prototype/string/scoped_string_base.h"
//#include "acme/prototype/prototype/signal.h"
//#include "acme/prototype/prototype/post_procedure_continuation.h"


namespace platform
{

   
   class platform;


} // namespace platform


class tracer;

class extended_topic;

class trace_statement;


//CLASS_DECL_ACME ::factory::factory * get_system_factory();


//CLASS_DECL_ACME class tracer * tracer();



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
//};


#include "acme/handler/sequence_continuation.h"
#include "acme/platform/trace_statement.h"
#include "acme/prototype/string/string.h"


using particle_pointer = ::pointer <  ::particle  >;



//#if REFERENCING_DEBUGGING
//#include "acme/platform/reference_count_debug.h"
//#endif


namespace prototype
{

   class prototype;

} // namespace prototype

struct disable_referencing_debugging_t {};


// ThomasBorregaardSorensen!! Like handlers : now particle with handle::handlers*
class CLASS_DECL_ACME particle :
   virtual public signal_handler::base
{
public:


   mutable ::platform::application *            m_papplication;
   mutable ::particle_pointer                   m_pparticleSynchronization;


//#if REFERENCING_DEBUGGING
   particle() : m_papplication(nullptr), m_pparticleSynchronization(nullptr) { }


   //particle(const ::e_flag & eflag, const ::e_status & estatus = undefined) :
   //::quantum(eflag, estatus),
   //::subparticle(eflag, estatus),
   //::signal_handler::base(eflag, estatus),
   //   m_papplication(nullptr),
   //   m_pparticleSynchronization(nullptr)
   //{
   //      
   //      
   //}


   particle(const ::particle & particle) :
      ::quantum(particle),
      ::subparticle(particle),
      ::signal_handler::base(particle)
   {


   }

   particle(::particle&& particle) :
      ::quantum(::transfer(particle)),
      ::subparticle(::transfer(particle)),
      ::signal_handler::base(::transfer(particle))
   {


   }

   
//#else
//   particle() : m_countReference(1) {}
//#endif
   
//
//   particle(::particle * pparticleParent);
//#else
   ~particle() override;



   inline bool is_null() const { return ::is_null(this); }
   inline bool is_set() const { return !is_null() && _is_set(); }

   inline bool is_ok() const { return is_set() && _is_ok(); }
   inline bool nok() const { return !is_ok(); }



   void initialize(::particle * pparticle) override;
   void _initialize_particle(::particle* pparticle);
   virtual void _on_initialize_app_consumer();
   //void finalize() override;


   bool _is_ok() const override;


   virtual void on_notify(::particle * pparticle, enum_id eid);

   virtual bool on_command_final(const ::atom & atom, ::user::activation_token * puseractivationtoken);

//   virtual void delete_this();

   inline ::particle * trace_this() const { return (::particle *) this; }

   virtual ::particle * get_context_particle();

   inline ::particle * synchronization() const { return ::is_set(this) ? m_pparticleSynchronization.m_p : nullptr; }
   void set_synchronization(::particle * pparticleSynchronization);
   void defer_create_synchronization();

   void operator()(::topic * ptopic, ::handler_context * phandlercontext) override;
   //void operator()(::sequencer & sequencer) override;

   //virtual void destroy();

   //virtual void aggregate(::sequencer & psequence);
   //virtual void complete_step(::sequencer & sequence);
   //virtual ::sequencer get_current_sequencer();
   //virtual void set_current_sequencer(const ::sequencer & sequence);

   //virtual void initialize(::particle * pparticle);
   virtual void on_initialize_particle();


   virtual ::topic_pointer create_topic(const ::atom & atom);
   virtual ::extended_topic_pointer create_extended_topic(const ::atom & atom);


   //class ::platform::platform * platform() const;
   static class ::platform::platform * platform();

   //virtual class ::platform::platform * _platform() const;


   ::mathematics::mathematics * mathematics() const;

   ::prototype::prototype * prototype() const;


   ::image::image_context* image() const;
   ::image::imaging * imaging() const;
   ::draw2d::draw2d * draw2d() const;
   ::write_text::write_text * write_text() const;


   class ::user::user * user() const;


   ::platform::system * system() const;
   ::platform::session * session() const;
   ::platform::application * application() const;
   ::platform::node * node() const;
   //::platform::context * context() const;

   //::aura::application* auraapplication() const;

   void delete_this() override;


   //::file_system * file_system() const;
   //::directory_system * directory_system() const;
   //::platform::context* apexcontext() const;
   //::aura::context* auracontext() const;
   ::datetime::datetime * datetime() const;
   ::internet::internet * internet() const;
   ::url::url_context* url() const;
   ::crypto::crypto * crypto() const;
   ::nano::nano* nano() const;
   //::os_context * os_context() const;


   //::apex::application * apexapplication()  const;


   ::directory_context * directory() const;
   ::directory_system * directory_system() const;
   ::file_context * file() const;
   ::file_system * file_system() const;
   ::path_system * path_system() const;


   virtual ::file::watcher * file_watcher() const;


   ::networking::networking * networking() const;
   //::http_system * http_system() const;
   //::platform::context * http() const;
   ::platform::http * http() const;


   virtual ::factory::factory_pointer & factory() const;
   virtual ::factory::factory_pointer & factory(const ::scoped_string & scopedstrLibrary) const;
   virtual ::factory::factory_pointer & factory(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation) const;
   virtual ::factory::factory * component_factory(const ::scoped_string & scopedstrComponent) const;
   //::factory::factory* factory(const ::atom& atom);

   //virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);






   virtual void install_message_routing(::channel * pchannel);


//   virtual void init_task();
//
   //virtual void initialize_matter(::matter * pmatter);


   virtual ::payload get_result_payload();


//   virtual bool particle_step();
   //void on_sequence() override;


   virtual void set_finish();


   // <3TBS_!! handle -> call_member <3TBS_!!
   virtual void call_member(long long hi);
   // <3ThomasBS_!! handle -> handle <3ThomasBS_!!
   //void handle(const  emessage, long long iData = 0, ::matter * pmatter = nullptr) override;
   //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
   //void handle(::message::message * pmessage) override;


   virtual bool is_branch_current() const;




   virtual const_char_pointer topic_text() const;
   //virtual const_char_pointer raw_class_title() const;







   //PARTICLE(const class ::atom & atom) :
   //   id()(atom)
   //{

   //}


   //PARTICLE(const PARTICLE & topic) :
   //   id()(topic.id())
   //{

   //}


   //PARTICLE(PARTICLE && topic) :
   //   id()(topic.id())
   //{

   //}

   virtual enum_trace_category trace_category(const ::particle * pparticle) const;
   virtual enum_trace_category trace_category() const;



   //virtual void trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_information_arguments(enum_trace_category etracecategory, const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_warning_arguments(enum_trace_category etracecategory, const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_error_arguments(enum_trace_category etracecategory, const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_fatal_arguments(enum_trace_category etracecategory, const_char_pointer pszFormat, va_list & arguments);


   //virtual void trace_arguments(enum_trace_level etracelevel, const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_information_arguments(const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_warning_arguments(const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_error_arguments(const_char_pointer pszFormat, va_list & arguments);
   //virtual void trace_log_fatal_arguments(const_char_pointer pszFormat, va_list & arguments);


   //virtual void trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const_char_pointer pszFormat, ...);
   //virtual void trace_log_information() << enum_trace_category etracecategory, const_char_pointer pszFormat, ...;
   //virtual void trace_log_warning() << enum_trace_category etracecategory, const_char_pointer pszFormat, ...;
   //virtual void trace_log_error() << enum_trace_category etracecategory, const_char_pointer pszFormat, ...;
   //virtual void trace_log_fatal() << enum_trace_category etracecategory, const_char_pointer pszFormat, ...;


   //virtual void trace(enum_trace_level etracelevel, const_char_pointer pszFormat, ...);
   //virtual void trace_log_information() << const_char_pointer pszFormat, ...;
   //virtual void trace_log_warning() << const_char_pointer pszFormat, ...;
   //virtual void trace_log_error() << const_char_pointer pszFormat, ...;
   //virtual void trace_log_fatal() << const_char_pointer pszFormat, ...;


   virtual class tracer * tracer() const;


   virtual ::trace_statement trace_statement() const;


   virtual ::trace_statement & trace_statement_prefix(::trace_statement & statement) const;


   virtual ::trace_statement log_statement() const;


   //virtual trace_statement trace(enum_trace_level etracelevel);

   virtual ::trace_statement debug() const;
   virtual ::trace_statement information() const;
   virtual ::trace_statement warning() const;
   virtual ::trace_statement error() const;
   virtual ::trace_statement fatal() const;

   
   virtual void tracef(enum_trace_level etracelevel, const_char_pointer pszFormat, ...) const;

   virtual void formatf_trace(enum_trace_level etracelevel, const_char_pointer pszFormat, va_list & arguments) const;


   template<typename... Args>
   void print_line(std::format_string<Args...> fmt, Args&&... args) const
   {

      string str;

      str.format(fmt, ::std::forward < Args >(args)...);

      print_line(str);

   }


   template<typename... Args>
   void err_line(std::format_string<Args...> fmt, Args&&... args) const
   {

      string str;

      str.format(fmt, ::std::forward < Args >(args)...);

      err_line(str);

   }

   virtual void print_line(const ::scoped_string & scopedstr) const;
   virtual void print_out(const ::scoped_string & scopedstr) const;
   virtual void printf_line(const_char_pointer pszFormat, ...) const;
   virtual void printf_out(const_char_pointer pszFormat, ...) const;
   virtual void err_line(const ::scoped_string & scopedstr) const;
   virtual void err_out(const ::scoped_string & scopedstr) const;
   virtual void errf_line(const_char_pointer pszFormat, ...) const;
   virtual void errf_out(const_char_pointer pszFormat, ...) const;

   virtual void debugf(const_char_pointer pszFormat, ...) const;
   virtual void informationf(const_char_pointer pszFormat, ...) const;
   virtual void warningf(const_char_pointer pszFormat, ...) const;
   virtual void errorf(const_char_pointer pszFormat, ...) const;
   virtual void fatalf(const_char_pointer pszFormat, ...) const;


//#if defined(__STD_FORMAT__)
   
   // With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
   template<typename... Args>
   void trace(enum_trace_level etracelevel, std::format_string<Args...> fmt, Args&&... args) const
   {

      auto statement = ::transfer(log_statement());

      statement(etracelevel)(trace_category());

      statement.format_output(fmt, ::std::forward<Args>(args)...);

   }

   // With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
   template<typename... Args>
   void debug(std::format_string<Args...> fmt, Args &&...args) const
   {
      trace(e_trace_level_debug, fmt, ::std::forward<Args>(args)...);
   }
   template<typename... Args>
   void information(std::format_string<Args...> fmt, Args&&... args) const
   {
      trace(e_trace_level_information, fmt, ::std::forward<Args>(args)...);
   }
   // With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
   template<typename... Args>
   void warning(std::format_string<Args...> fmt, Args&&... args) const
   {
      trace(e_trace_level_warning, fmt, ::std::forward<Args>(args)...);
   }
   // With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
   template<typename... Args>
   void error(std::format_string<Args...> fmt, Args&&... args) const
   {
      trace(e_trace_level_error, fmt, ::std::forward<Args>(args)...);
   }
   // With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
   template<typename... Args>
   void fatal(std::format_string<Args...> fmt, Args&&... args) const
   {
      trace(e_trace_level_fatal, fmt, ::std::forward<Args>(args)...);
   }


//#endif
   

   void trace(enum_trace_level etracelevel, const ::scoped_string & scopedstr) const;
   void debug(const scoped_string & scopedstr) const;
   void information(const scoped_string & scopedstr) const;
   void warning(const scoped_string & scopedstr) const;
   void error(const scoped_string & scopedstr) const;
   void fatal(const scoped_string & scopedstr) const;

   //virtual trace_statement trace_log_warning() << ;
   //virtual trace_statement trace_log_error() << ;
   //virtual trace_statement trace_log_fatal() << ;


   //virtual trace_statement trace(enum_trace_level etracelevel, enum_trace_category etracecategory);
   //virtual trace_statement trace_log_information() << enum_trace_category etracecategory;
   //virtual trace_statement trace_log_warning() << enum_trace_category etracecategory;
   //virtual trace_statement trace_log_error() << enum_trace_category etracecategory;
   //virtual trace_statement trace_log_fatal() << enum_trace_category etracecategory;



   //virtual ::particle * raw_new() const;


   // ThomasBorregaardSorensen!! Like handlers
   //virtual void call(const enum_message, long long iData = 0, ::matter * pmatter = nullptr);
   //virtual void call(const enum_id, long long iData = 0, ::matter* pmatter = nullptr);
   
   ///virtual void send_call(const ::call & call);


   // ThomasBorregaardSorensen!! Like handlers
   virtual lresult message_handler(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);
   virtual void handle(::topic * ptopic, ::handler_context * phandlercontext);
   virtual void handle(const ::call & call);
   virtual void handle_message(::message::message * pmessage);
   virtual void handle_item(::item * pitem);

   using subparticle::call;
   // ThomasBorregaardSorensen!! Like handlers
   virtual lresult message_call(::user::enum_message eusermessage, ::wparam wparam = {}, ::lparam lparam = {});
   virtual void call_handle(::topic * ptopic, ::handler_context * phandlercontext);
   virtual void call_handle_message(::message::message* pmessage);
   virtual void call_handle_item(::item* pitem);

   virtual bool _handle_uri(const ::scoped_string & scopedstrUri);
   virtual bool _handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset);

   // <3ThomasBorregaardSorensen__!! likes handler concept...
   //void route(::signal * psignal) override;
   //void signal(::signal * psignal) override;
   //void route(::topic * ptopic, ::handler_context * phandlercontext) override;
   //void post_process(::topic * ptopic, ::handler_context * phandlercontext) override;



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



   virtual ::particle * get_taskpool_container();


   virtual ::task_pool * taskpool();



   virtual const_char_pointer debug_note() const;



   [[nodiscard]] virtual bool should_run_async() const;


   [[nodiscard]] virtual ::pointer < ::message_box > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   [[nodiscard]] virtual ::pointer < ::message_box > message_box(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = {}, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);


   //virtual ::pointer < ::message_box > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   //virtual ::pointer < ::message_box > exception_message_box(const ::exception& exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   //virtual ::pointer < ::message_box > message_console(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);
   //virtual ::pointer < ::message_box > exception_message_console(const ::exception& exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

   //virtual void display(::message_box * pmessagebox);
   //virtual void display_exception(const ::exception& exception, ::message_box * pmessagebox);

   virtual ::file_pointer get_file(const ::payload& payloadFile, ::file::e_open eopen, ::pointer < ::file::exception > * pfileexception = nullptr);
   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary);
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);


   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE>__call__create(::factory::factory * pfactory = nullptr);

   //::pointer<subparticle>__call__id_create(const ::atom& atom, ::factory::factory * pfactory = nullptr);

   template < typename TYPE >
   inline ::pointer<TYPE> __call__create_new();

   template < typename TYPE >
   inline ::pointer<TYPE> __call__create_new_clone(TYPE * p);

   template < typename T, typename ...Args >
   ::pointer < T > __call__allocate_and_initialize(Args &&... args)
   {

      auto p = ::transfer(
         øallocate T(
            ::std::forward<Args>(args)...));

      p->initialize(this);

      return ::transfer(p);

   }


   template < typename TYPE >
   inline TYPE*__initialize(TYPE * p)
   {
      p->initialize(this);
      return p;

   }

   template < typename TYPE >
   inline ::pointer < TYPE > __initialize(::pointer < TYPE > && p)
   {
      p.m_p->initialize(this);
      return ::transfer(p);

   }

   template < typename T >
   ::pointer < T > create_clone(const ::pointer < T > & psource)
   {

      return this->create_clone(psource.m_p REFERENCING_DEBUGGING_COMMA_P_FUNCTION_NOTE(psource.m_p, __FUNCTION__, __FILE_LINE__));

   }


   /// @brief consumes a referer
   template < typename T >
   ::pointer < T > create_clone(const T * pSource)
   {

      auto p = this->øcreate< T >();

      if (!p)
      {

         return nullptr;

      }

      *p = pSource;

      return p;

   }


   ///// consumes a referer
   //template < typename T >
   //::pointer < T > create_new_clone(const ::pointer < T > & psource )
   //{

   //   return this->create_new_clone(psource.m_p);

   //}


   /// consumes a referer
   template < typename T >
   ::pointer < T > __call__create_new_clone(const T * pSource)
   {

      auto p = this->øcreate_new< T >();

      if (!p)
      {

         return nullptr;

      }

      *p = *pSource;

      return p;

   }


   virtual void app_post(const ::procedure & procedure);
   virtual ::task_pointer app_fork(const ::procedure & procedure);

   virtual void task_post(const ::procedure & procedure);
   virtual ::task_pointer task_fork(const ::procedure & procedure);

   
   virtual void _user_send(const ::procedure & procedure);
   inline sequence_continuation user_send(const ::procedure & procedure);
   inline sequence_continuation user_send();
   inline sequence_continuation user_sync();


   virtual void _user_post(const ::procedure & procedure);
   inline sequence_continuation user_post(const ::procedure & procedure);
   inline sequence_continuation user_post();
   inline sequence_continuation user_async();


   virtual void _main_send(const ::procedure & procedure);
   inline sequence_continuation main_send(const ::procedure & procedure);
   inline sequence_continuation main_send();
   inline sequence_continuation main_sync();


   virtual void _main_post(const ::procedure & procedure);
   inline sequence_continuation main_post(const ::procedure & procedure);
   inline sequence_continuation main_post();
   inline sequence_continuation main_async();


   virtual class ::time get_default_run_timeout();


   virtual void _send(const ::procedure & procedure);
   inline sequence_continuation send(const ::procedure & procedure);
   inline sequence_continuation sync(const class ::time & timeout = {});
   inline sequence_continuation send();

   virtual void _post(const ::procedure & procedure);
   inline sequence_continuation post(const ::procedure & procedure);
   inline sequence_continuation async();
   inline sequence_continuation post();
   


   virtual void _call_procedure(enum_dispatch edispatch, const procedure & procedure);

   //inline post_procedure_continuation queue();


   //// this is object to be realized
   //virtual ::particle_pointer realize(::particle * pparticleReificator);


   //// this is reificator/director
   //virtual ::particle_pointer realize_particle(::particle * pparticleToRealize);

   //virtual void realize(::particle * pparticleAgent);
   //virtual void display_sync(::particle_pointer p);
   //virtual void display_async(::particle_pointer p);

   //virtual void _user_send_procedure(const ::procedure & procedure);
   //virtual void _user_post_procedure(const ::procedure & procedure);

   //virtual void _user_send(::subparticle * psubparticle);
   //virtual void _user_post(::subparticle * psubparticle);

   //virtual void _main_send_procedure(const ::procedure & procedure);
   //virtual void _main_post_procedure(const ::procedure & procedure);

   //virtual void _main_send(::subparticle * psubparticle);
   //virtual void _main_post(::subparticle * psubparticle);

   //virtual void _post_procedure(const ::procedure & procedure);
   //virtual void _send_procedure(const ::procedure & procedure);

   //virtual void _post(::subparticle * psubparticle);
   //virtual void _send(::subparticle * psubparticle);


   template < typename BASE_TYPE >
   inline bool __call__defer_construct(::pointer<BASE_TYPE>& ptype, ::factory::factory * pfactory = nullptr);

   template < typename TYPE >
   inline bool __call__defer_construct_new(::pointer<TYPE>& ptype);

   template < typename TYPE >
   inline bool __call__defer_raw_construct_new(::pointer<TYPE>& ptype);

   template < typename BASE_TYPE >
   inline void __call__construct(::pointer<BASE_TYPE>& ptype, ::factory::factory * pfactory = nullptr);

   //template < typename BASE_TYPE, typename TYPE >
   //inline void __call__construct(::pointer<BASE_TYPE>& ptype, const ::pointer < TYPE >& p);

   //template < typename BASE_TYPE, typename TYPE >
   //inline void __call__construct(::pointer<BASE_TYPE>& ptype, TYPE* p);



   template < typename BASE_TYPE >
   inline void __call__construct_by_type(::pointer<BASE_TYPE>& ptype, const ::platform::type & type, ::factory::factory * pfactory = nullptr);

   virtual ::pointer<::particle> __call__create_by_type(const ::platform::type & type, ::factory::factory *pfactory = nullptr);

   //template < typename BASE_TYPE >
   //inline void __call__construct_by_type_index(::pointer<BASE_TYPE>& ptype, const ::std::type_index & typeindex, ::factory::factory* pfactory = nullptr);

   //virtual ::pointer < ::particle > __call__create_by_type_index(const ::std::type_index & typeindex, ::factory::factory* pfactory = nullptr);

   template < typename TYPE >
   inline void __call__construct_new(::pointer<TYPE>& ptype);

   //template < typename TYPE >
   //inline void __call__raw_construct2( ::pointer<TYPE> & p, ::factory::factory * pfactory = nullptr);

   template < typename TYPE >
   inline void __call__raw_construct(::pointer<TYPE> & p, ::factory::factory * pfactory = nullptr COMMA_REFERENCING_DEBUGGING_PARAMETERS_DECLARATION);

   template < typename BASE_TYPE >
   inline ::pointer<BASE_TYPE> __raw_create(::factory::factory * pfactory = nullptr);


#if REFERENCING_DEBUGGING


   ::particle * __call__add_referer2(const ::reference_referer & referer) const;


#endif
   
   
   virtual void * new_object(const_char_pointer psz);


   virtual string as_string() const;

   //virtual void to_string(string_exchange & str) const;


   //[[nodiscard]] ::enum_type get_payload_type() const;


   //virtual void exchange(::stream& s);
   //virtual void exchange(::payload_stream& s);



   //virtual void add_composite(::particle * pparticle);
   //virtual void add_reference(::particle * pparticle);


   //virtual void release_composite2(::particle * pparticle);
   //virtual void finalize_composite(::particle * pparticle);
   //virtual void release_reference(::particle * pparticle);




   virtual void kick_idle();

   particle & operator = (const particle & particle)
   {

      // all particle members are quite instance members.

      return *this;

   }


   //virtual ::subparticle_pointer clone();


   virtual ::user::user * user();
   // virtual ::axis::user * axisuser();
   // virtual ::berg::user * user();
   // virtual ::bred::user * breduser();
   // virtual ::core::user * coreuser();


   virtual void process_owned_procedure_list(::procedure_list_base & procedurelist, bool & bHandled);


   virtual memory_file_pointer create_memory_file();


   virtual memory_file_pointer create_memory_file(::memory_base& memory);


   virtual memory_file_pointer create_memory_file(const ::block& block);
   

   virtual memory_file_pointer create_memory_file_as_copy(const memory& memory);
   

   virtual memory_file_pointer create_memory_file_by_reading(::file::file* pfile);


//template < typename T, typename ...Args >
//inline ::pointer < T > __call__allocate(Args &&... args);


   //inline ::particle * __call__add_referer(const ::reference_referer & referer) const;


   virtual void assert_particle_ok() const;



};


//
//
//#define OPTIONAL_BASE_BODY                                                          \
//public:                                                                             \
//   void on_initialize_particle() override {}         \
//   void handle(::topic *, ::handler_context *) override {}
//
////   void assert_ok() const override {}                                    \
////   void dump(dump_context&) const override {}                               \
//   //void on_subject(::topic::topic*, ::handler_context*) override {} \
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

//template < typename T >
//inline long long release(T*& p REFERENCING_DEBUGGING_COMMA_PARAMS_DEF);
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
//      informationf("exception release p = nullptr; \n");
//
//   }
//
//   try
//   {
//
//      return pparticle->release();
//
//   }
//   catch (...)
//   {
//
//      informationf("exception release pparticle->release() \n");
//
//   }
//
//   return -1;
//
//}


template < typename T >
inline long long global_release(T*& p);
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
//      auto i = p->release();
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
//      informationf("exception release pparticle->release() \n");
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
//long long particle::increment_reference_count()
//{
//
//   auto c = ++m_countReference;
//
//#if REFERENCING_DEBUGGING
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
//long long particle::decrement_reference_count()
//{
//
//   auto c = --m_countReference;
//
//#if REFERENCING_DEBUGGING
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
//long long particle::release()
//{
//
//   long long i = decrement_reference_count();
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






//virtual trace_statement trace(enum_trace_level etracelevel);


//CLASS_DECL_ACME ::trace_statement log_statement();
//
//
//CLASS_DECL_ACME ::trace_statement information();
//CLASS_DECL_ACME ::trace_statement warning();
//CLASS_DECL_ACME ::trace_statement error();
//CLASS_DECL_ACME ::trace_statement fatal();
//
//
//CLASS_DECL_ACME void informationf(const_char_pointer pszFormat, ...);
//CLASS_DECL_ACME void warningf(const_char_pointer pszFormat, ...);
//CLASS_DECL_ACME void errorf(const_char_pointer pszFormat, ...);
//CLASS_DECL_ACME void fatalf(const_char_pointer pszFormat, ...);
//
//
//inline void information(const ::scoped_string & scopedstr)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_information);
//
//   statement << scopedstr;
//
//}
//
//
//inline void warning(const ::scoped_string & scopedstr)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_warning);
//
//   statement << scopedstr;
//
//}
//
//
//inline void error(const ::scoped_string & scopedstr)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_error);
//
//   statement << scopedstr;
//
//}
//
//
//
//inline void fatal(const ::scoped_string & scopedstr)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_fatal);
//
//   statement << scopedstr;
//
//}


//#if defined(__STD_FORMAT__)
//
//
//// With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
//template<typename... Args>
//inline void information(const std::format_string<Args...> fmt, Args&&... args)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_information);
//
//   statement.format_output(fmt, std::forward<Args>(args)...);
//
//}
//
//
//// With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
//template<typename... Args>
//inline void warning(const std::format_string<Args...> fmt, Args&&... args)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_warning);
//
//   statement.format_output(fmt, std::forward<Args>(args)...);
//
//}
//
//// With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
//template<typename... Args>
//void error(const std::format_string<Args...> fmt, Args&&... args)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_error);
//
//   statement.format_output(fmt, std::forward<Args>(args)...);
//
//}
//
//
//// With help from speccylad(twitch)/turd(discord) 2023-10-27 ~09:00 BRT
//template<typename... Args>
//void fatal(const std::format_string<Args...> fmt, Args&&... args)
//{
//
//   auto statement = log_statement();
//
//   statement(e_trace_level_fatal);
//
//   statement.format_output(fmt, std::forward<Args>(args)...);
//
//}
//
//
//#endif


inline bool is_ok(const ::particle * pparticleConst)
{

   ::particle * pparticle = (::particle *)pparticleConst;

   return ::is_set(pparticle) && pparticle->is_ok();

}


/// @brief consumes a releaser (a referer used to decrement reference count)
template < typename T >
inline long long release(T *& p);
//inline long long release(T *& p COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION);


/// @brief consumes a releaser (a referer used to decrement reference count)
template < typename T >
inline long long global_release(T *& p);


template < typename TYPE, typename T >
void assign(::pointer<TYPE> & ptr, T * p);

template < typename TYPE >
long long release(::pointer<TYPE> & ptr);
//long long release(::pointer<TYPE> & ptr COMMA_REFERENCING_DEBUGGING_RELEASER_PARAMETERS_DECLARATION);

//template < typename TYPE >
//long long release(TYPE *& p);




//#if REFERENCING_DEBUGGING
//
//
//namespace allocator
//{
//
//
//   CLASS_DECL_ACME ::reference_referer * aaa_defer_add_referer(const ::reference_referer & referer);
//   CLASS_DECL_ACME ::reference_referer * aaa_add_referer(const ::reference_referer & referer);
//   CLASS_DECL_ACME ::reference_referer * aaa_defer_get_referer(::particle * p, const ::reference_referer & referer);
//   CLASS_DECL_ACME ::reference_referer * aaa_get_referer();
//   CLASS_DECL_ACME ::reference_referer * aaa_pop_referer();
//   CLASS_DECL_ACME void aaa_defer_erase_referer();
//   CLASS_DECL_ACME void aaa_erase_referer(::reference_referer * preferer);
//
//
//   CLASS_DECL_ACME void aaa_add_releaser(::reference_referer * preferer);
//   CLASS_DECL_ACME::reference_referer * aaa_get_releaser();
//   CLASS_DECL_ACME::reference_referer * aaa_pop_releaser();
//   CLASS_DECL_ACME void aaa_defer_erase_releaser();
//   CLASS_DECL_ACME void aaa_erase_releaser(::reference_referer * preferer);
//
//
//} // namespace allocator
//
//
//#endif


namespace allocator
{

   class accessor;

} // namespace allocator


#if REFERENCING_DEBUGGING


class refdbg_top_track
{
public:

   ::particle* m_p;
   refdbg_top_track(::particle* p)

   {
      if (refdbg_add_top_track(p))
      {
         m_p = p;
      }
      else
      {
         m_p = nullptr;
      }
   }
   ~refdbg_top_track()
   {
      if (m_p)
      {
         ::refdbg_erase_top_track(m_p);
      }
   }

};




//class abc
//{
//public:
//
//   template < typename T >
//   T * operator << (T* p)
//   {
//
//      return p;
//   }
//
//};
//CLASS_DECL_ACME  __call__add_referer(const ::reference_referer & referer, ::reference_referer ** ppreferer = nullptr);

#endif


template < non_particle NON_PARTICLE >
class now_a_particle :
   public NON_PARTICLE,
   virtual public ::particle
{
public:

   template < typename... Args >
   now_a_particle(Args&&...  args) :
      NON_PARTICLE(::std::forward<Args>(args)...)
   {

   }

};


CLASS_DECL_ACME ::trace_statement debug();
CLASS_DECL_ACME ::trace_statement information();
CLASS_DECL_ACME ::trace_statement warning();
CLASS_DECL_ACME ::trace_statement error();
CLASS_DECL_ACME ::trace_statement fatal();


CLASS_DECL_ACME void debug(const ::scoped_string& scopedstr);
CLASS_DECL_ACME void information(const ::scoped_string& scopedstr);
CLASS_DECL_ACME void warning(const ::scoped_string& scopedstr);
CLASS_DECL_ACME void error(const ::scoped_string& scopedstr);
CLASS_DECL_ACME void fatal(const ::scoped_string& scopedstr);


template <typename... Args>
void debug(std::string_view fmt, Args&&... args)
{
   ::debug(::format(fmt, std::make_format_args(args...)));
}
template <typename... Args>
void information(const std::format_string<Args...> fmt, Args&&... args)
{
   ::information(::format<Args...>(fmt, std::forward<Args>(args)...));
}
template <typename... Args>
void warning(const std::format_string<Args...> fmt, Args&&... args)
{
   ::warning(::format<Args...>(fmt, std::forward<Args>(args)...));
}
template <typename... Args>
void error(const std::format_string<Args...> fmt, Args&&... args)
{
   ::error(::format<Args...>(fmt, std::forward<Args>(args)...));
}
template <typename... Args>
void fatal(const std::format_string<Args...> fmt, Args&&... args)
{
   ::fatal(::format<Args...>(fmt, std::forward<Args>(args)...));
}


CLASS_DECL_ACME void debugf(const ::ansi_character* pszFormat, ...);
CLASS_DECL_ACME void informationf(const ::ansi_character* pszFormat, ...);
CLASS_DECL_ACME void warningf(const ::ansi_character* pszFormat, ...);
CLASS_DECL_ACME void errorf(const ::ansi_character* pszFormat, ...);
CLASS_DECL_ACME void fatalf(const ::ansi_character* pszFormat, ...);



// template < typename TYPE, ::enum_flag t_eflag = e_flag_none, ::enum_status t_estatus = undefined >
// class make_particle :
//     public TYPE,
//     virtual public ::particle
// {
// public:
//
//
//    // Universal forwarding constructor
//    template <typename... Args>
//    make_particle(Args&&... args):
//       ::particle(t_eflag, t_estatus),
//       ::quantum(t_eflag, t_estatus),
//       TYPE(std::forward<Args>(args)...) // forward to TYPE's ctor
//    {
//
//    }
//
//
//    template <typename Arg>
//    TYPE & operator=(Arg&& arg)
//    {
//       return TYPE::operator=(arg);
//    }
//
// };


template < primitive_container CONTAINER >
inline void __assert_container_ok(const CONTAINER * pcontainer, const_char_pointer pszFileName, int nLine)
{

   if (pcontainer == nullptr)
   {

      if(!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(pcontainer, sizeof(::particle)))
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(pcontainer, sizeof(CONTAINER)))
   {

      if (!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   pcontainer->container_ok();

}


