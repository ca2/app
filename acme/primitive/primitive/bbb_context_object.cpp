// Created on 2021-03-10 17:37 BRT <3ThomasBS_!!
#include "framework.h"


object::~object()
{

}


#ifdef _DEBUG


i64 object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 object::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#else


i64 object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 object::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
{

   return property_object::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif


//::apex::system* objectacmesystem() const
//{
//
//
//}
//

void object::process_exit_status(const ::e_status & estatus)
{


}


::application* object::_get_application()
{

   return m_papp;

}


   //inline ::application* object::application() { return m_papp; }


   //template < typename BASE_TYPE >
   //::pointer<BASE_TYPE>file_as(const ::payload& payloadFile);


   void object::add_procedure(const ::atom& idRoutine, const ::procedure & procedure)
   {


    }


    void object::add_each_routine_from(const ::atom& idRoutine, ::object* pobjectSource)
    {


    }


    array < ::procedure >* object::routinea(const ::atom& idRoutine)
    {

       return nullptr;

    }


    void object::call_routine(const ::atom& idRoutine)
    {



    }


   //inline ::payload object::context_value(const ::payload& payload)



   void object::task_erase(::task* ptask)
   {


    }


       void object::sleep(const class time & time)
    {

       return ::success;

    }


   //template < typename BASE_TYPE >
   //void save_to(const ::payload& payloadFile, BASE_TYPE* pparticle);

   
   void object::initialize(::particle * pparticle)
   {
      auto estatus = ::success;

#if OBJECT_TYPE_COUNTER

      if (!m_eobject.is(e_object_object_type_counter))
      {

         m_eobject += e_object_object_type_counter;

         OBJECT_TYPE_COUNTER_INCREMENT;

      }

#endif

      //#if OBJECT_REFERENCE_COUNT_DEBUG
      //
      //   string strType = __type_name(this);
      //
      //   if (strType.case_insensitive_contains("session"))
      //   {
      //
      //      if (m_pobjrefdbg->m_iStep == 39)
      //      {
      //
      //         information("session");
      //
      //      }
      //
      //   }
      //
      //#endif

      if (!acmesystem())
      {

         acmesystem() = pparticle->acmesystem();

      }

      if (!m_papp)
      {

         m_papp = pparticle->m_papp;

      }

      if (!m_psession)
      {

         m_psession = pparticle->m_psession;

      }

      //if (!psystem)
      //{

      //   set_context_system(::apex::get_system(pparticle) OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      //}

      if (!get_context())
      {

         if (m_papp)
         {

            m_pcontext = m_papp;

         }
         else if (m_psession)
         {

            m_pcontext = m_psession;

         }
         else if (acmesystem())
         {

            m_pcontext = acmesystem();

         }

      }

      return estatus;

   }


    void object::destroy()
    {


    }


    ::thread_pointer object::launch(const ::procedure & procedure)
    {

       auto pthread = __create_new < ::thread >();

       pthread->m_pmatter = routine;

       pthread->m_atom = __type_name(pthread->m_pmatter);

       pthread->begin_thread();

       return pthread;

    }



   //inline const char* object::topic_text();

    //context& object::__context(const ::payload& payload)
    //{


    //}

    //{

    //   return 

    //}

    ::payload object::__context_value(const ::payload& payload)
    {

       return ::payload();

   }

   void object::set_topic_text(const string& str)
   {


    }

   //void create_object_meta();

   //inline void defer_object_meta() { if (::is_null(m_pmeta)) create_object_meta(); }

   //inline ::object_meta * get_meta() { defer_object_meta(); return m_pmeta; }

   //inline ::context* object::get_context() const { return m_pcontext; }

   //inline ::thread* object::get_thread() const { return m_pthread; }

   //inline ::application* object::get_app() const { return m_papp; }

   //inline ::apex::session* object::get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::application * application() const { return m_papp; }

    string object::get_text(const ::payload& payload, const ::atom& atom)
    {

       return "";

    }
//
//#ifdef _DEBUG
//    void set_context(::context* pcontext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_thread(::thread* pthread OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_app(::apex::application* pappContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//    void set_context_session(::apex::session* psessionContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   // void set_context_system(::apex::system* psystemContext OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
//   // void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::apex::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   // void set_object(::particle * pparticle) 


   //inline void defer_set_object(::particle * pparticle);

       void object::operator()()
    {

       return ::success;

    }


   //inline i64 get_ref_count()
   //{

   //   return m_countReference;

   //}


   // ::user::primitive* get_user_interaction_host();
   // ::user::interaction * get_host_window();


       void object::dev_log(string str) const
    {


    }


    ::object& object::operator = (const ::payload& payload)
    {

       return *this;

   }




   //static u32 s_thread_proc(void* p);


   // void to_string(const string_exchange & str) const 

   //::image_pointer create_image();
   //::image_pointer create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_pointer get_image(const ::payload & payloadFile, bool bCache = true, bool bSync = true);
   //::image_pointer matter_image(const ::string & strMatter, bool bCache = true, bool bSync = true);

   //template < typename BASE_TYPE >
   //inline ::pointer<BASE_TYPE>__create();

   //template < typename BASE_TYPE >
   //inline ::pointer<BASE_TYPE>__id_create(const ::atom& atom);

   //template < typename TYPE >
   //inline ::pointer<TYPE>__create_new();

   //inline void __construct(::pointer<::image>& pimage);

   //inline void __construct(::pointer<::image>& pimage, ::image * pimageSource);

   //inline void __defer_construct(::pointer<::image>& pimage) { return !pimage ? __construct(pimage) : void(::success); }

   // for composition (ownership)

   //template < typename BASE_TYPE >
   //inline void __construct(::pointer<BASE_TYPE> pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __construct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __construct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

   //template < typename BASE_TYPE >
   //inline void __raw_construct(::pointer<BASE_TYPE> pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const SOURCE* psource);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __raw_construct(::pointer<BASE_TYPE> pusermessage, const ::pointer<SOURCE>psource);

   //template < typename TYPE >
   //inline void __raw_construct_new(::pointer<TYPE> ptype);

   //template < typename TYPE >
   //inline void __construct_new(::pointer<TYPE> ptype);




   //template < typename BASE_TYPE >
   //inline void __defer_construct(::pointer<BASE_TYPE> pusermessage) { return !pusermessage ? __construct(pusermessage) : void(::success); }

   //template < typename BASE_TYPE >
   //inline void __defer_id_compose(::pointer<BASE_TYPE> pusermessage, const ::atom& atom) { return !pusermessage ? __id_construct(pusermessage) : void(::success); }

   //template < typename TYPE >
   //inline void __defer_raw_compose_new(::pointer<TYPE> ptype) { return !ptype ? __raw_construct_new(ptype) : void(::success); }

   //template < typename TYPE >
   //inline void __defer_construct_new(::pointer<TYPE> ptype) { return !ptype ? __construct_new(ptype) : void(::success); }




   //template < typename BASE_TYPE >
   //inline void __construct(::pointer<BASE_TYPE> pusermessage);

   //template < typename BASE_TYPE >
   //inline void __id_construct(::pointer<BASE_TYPE> pusermessage, const ::atom& atom);

   //template < typename TYPE >
   //inline void __construct_new(::pointer<TYPE> pusermessage);

   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE> pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline void __release(::pointer<BASE_TYPE> preference OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void release_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


   // void add_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
   // void add_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 


   // void release_composite2(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
   // void finalize_composite(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 
   // void release_reference(::particle * pparticle OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS) 


   //template < typename BASE_TYPE >
   //inline void add_composite(::pointer<BASE_TYPE> pcomposite OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const ::pointer<SOURCE>psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline void __refer(::pointer<BASE_TYPE> preference, const ::primitive::member < SOURCE >& psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(SOURCE* psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline void add_reference(::pointer<SOURCE> psource OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

void object::delete_this()
{


    }

       void object::destruct()
    {


    }

    void object::system(const ::scoped_string & scopedstrProjectName)
    {

   }

   void object::enable_application_events(bool bEnable)
   {

      return ::success;

    }

    void object::handle_exception(const ::exception& e)
    {

       return ::success;

    }

    void object::top_handle_exception(const ::exception& e)
    {

       return ::success;

    }


    void object::process_exception(const ::exception& e)
    {

       return ::success;

    }


    ::property_object* object::parent_property_set_holder() const
    {

       if (m_papp && m_papp.m_p != this)
       {

          return m_papp.m_p;

       }

       if (m_psession && m_psession.m_p != this)
       {

          return m_psession.m_p;

       }

       if (acmesystem() && (::property_object*)acmesystem() != (::property_object *) this)
       {

          return acmesystem();

       }

       return nullptr;

   }


    void object::copy_from(const object& o)
    {


   }


    string object:: get_tag() const
   {

       return "";

    }


    bool object::is_thread() const
    {
       return false;

    }


       bool object::task_get_run() const
    {

          return true;
    }


    bool object::is_running() const
    {

       return true;

    }
    
    
    void object::child_post_quit(const ::scoped_string & scopedstrTag)
    {


    }


    void object::child_post_quit_and_wait(const ::scoped_string & scopedstrTag, const time& time)
    {


    }


    void object::finish(::property_object * pcontextobjectFinish)
    {

       return ::success;

    }

   void object::set_finish(::property_object* pcontextobjectFinish)
    {

       return ::success;

    }
    
       void object::set_finish_composites(::property_object* pcontextobjectFinish)
    {

          return ::success;

    }
    
       
       void object::on_finish()
    {


    }


       void object::defer_update_object_id()
    {


    }

    
    ::atom object::calc_default_object_id() const
    {

       return ::atom();

    }


    void object::install_message_routing(::channel* pchannel)
    {


    }

    void object::message_receiver_destruct()
    {



   }

   void object::_001OnUpdate(::message::message* pmessage)
   {


   }


   void object::request_file(const ::payload& payloadFile)
   {

      return ::success;

    }


    void object::request_file(const ::payload& payloadFile, ::payload varQuery)
    {

      return ::success;

    }


    void object::request(arguments arguments)
    {

       return ::success;

    }


    void object::do_request(::create* pcreate)
    {

       return ::success;

    }


    pointer< ::extended::future < ::conversation > >  object::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::e_message_box& emessagebox)
    {

       return nullptr;

    }
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   // void message_box_timeout(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, timeTimeout, emessagebox, process);

   //}

   // void message_box(::user::primitive* puiOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());
   // void message_box_timeout(::user::primitive* puserinteractionOwner, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future());

    void object::release_references()
    {

    }

    ::pointer<::matter>object::running(const ::scoped_string & scopedstrTag) const
    {

       return nullptr;

    }

    bool object::___is_reference(::particle * pparticle) const
    {

       return false;

    }

    bool object::__is_composite(::particle * pparticle) const
    {

       return false;

    }

    bool object::__is_child_task(::task* ptask) const
    {

       return false;

    }

    void object::on_finalize()
    {


    }

    void object::call_request(::create* pcreate)
    {

       return ::success;

    }

   //// former user::server
   // ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
    void object::on_request(::create* pcreate)
    {


    }

   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::atom atom = ::atom());
   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& payloadFile);
   // ::user::document* create_subdocument(::user::impact_data* pimpactdata);


    void object::run()
    {

       return ::success;

    }


    string object::lstr(const ::atom& atom, string strDefault)
    {

       return "";

    }


    string object::__get_text(string str)
    {

       return "";

    }



   //template < typename PRED >
   //::image_pointer get_image(const ::payload & payloadFile, ::u64 uTrait, PRED pred);

   // ::image_pointer load_image(const ::payload & payloadFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   // ::image_pointer load_matter_image(const ::scoped_string & scopedstrMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   // ::image_pointer load_matter_icon(string_array & straMatter, string strIcon);
   // ::image_pointer load_thumbnail(const ::payload & payloadFile, int w, int h);
   // ::image_pointer load_thumbnail(const ::file::path & path);
   // ::image_pointer load_dib(const ::file::path & pathDib);



   bool object::IsSerializable() const
   {

      return false;

   }


   void object::start()
   {


   }


   void object::single_fork(const ::procedure_array& routinea)
   {


   }


   void object::multiple_fork(const ::procedure_array& routinea)
   {


   }

//   using property_object::defer_fork;

  /* template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread, const ::procedure & procedure)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline ::pointer<THREAD> defer_fork(::pointer<THREAD>pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }*/


   //inline void object::defer_fork(::thread_pointer& pthread, const ::procedure & procedure);


   //template < typename THREAD >
   //inline ::pointer<THREAD> start(::pointer<THREAD> pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer lcontext_object::aunch(const ::procedure & procedure);


   //template < typename METHOD >
   //inline ::task_pointer object::opt_fork(const ::procedure & procedure)
   //{

   //   auto ptask = ::get_task();

   //   synchronous_lock synchronouslock(ptask->synchronization());

   //   if (ptask && ptask->m_bIsPredicate)
   //   {

   //      routine();

   //      return ptask;

   //   }

   //   return launch(routine);

   //}


   //template < typename METHOD >
   //inline ::thread_pointer fork(METHOD method);


   //template < typename PRED >
   //inline auto new_predicateicate_thread(PRED pred);

   //template < typename TYPE >
   //inline auto async(void (TYPE::* pfnMemberProcedure)())
   //{

   //   return fork([this, pfnMemberProcedure]()
   //      {

   //         TYPE* ptype = dynamic_cast <TYPE*> (this);

   //         (ptype->*pfnMemberProcedure)();

   //      });

   //}

   //template < typename PRED >
   //inline ::thread_pointer predicate_run(bool bSync, PRED pred);

   //::thread_pointer object::begin(::enum_priority epriority, ::u32 nStackSize, u32 dwCreateFlags)
   //{

   //   return nullptr;

   //}
   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//    void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open());


   // void to_string(string & str) const 


    ::file_pointer object::get_file(const ::payload& payloadFile, ::file::e_open eopen)
    {

       return nullptr;

    }

   //inline ::file_pointer get_reader(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary);
   //inline ::file_pointer get_writer(const ::payload& payloadFile, ::file::e_open eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //void add_update_notification(property * pproperty);
   //void add_update_notification(const ::atom & atom, bool bCreate = true);
   //void property_notify(const ::atom & atom, ::matter * pmatter);


//   inline void format_topic_text(const ::scoped_string & scopedstr, ...)
//   {
//
//      va_list valist;
//      va_start(valist, psz);
//      format_topic_text_v(psz, valist);
//      va_end(valist);
//
//   }
//
//
//   inline void format_topic_text_v(const ::scoped_string & scopedstr, va_list valist)
//   {
//
//      string str;
//      str.format_arguments(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(void (TYPE:: * pfn)(), ::enum_priority epriority = ::e_priority_normal)
   //{

   //   TYPE * ptype = dynamic_cast <TYPE *>(this);

   //   return ptype->fork([ptype, pfn]()
   //      {

   //         return (ptype->*pfn)();

   //      }, NULL, 0, epriority);

   //}


   //template < typename TYPE >
   //::thread_pointer start_below_normal(void (TYPE::* pfn)())
   //{

   //   return fork(pfn, ::e_priority_below_normal);

   //}


   //template < typename TYPE >
   //void __construct(::thread_pointer& p, void (TYPE::* pfn)(), enum_priority epriority);

   //template < typename TYPE >
   //void __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::thread_pointer __start_thread(const ::atom& atom, void(TYPE::* pfn)(), enum_priority epriority = e_priority_normal);


    matter* object::get_taskpool_container()
    {

       return nullptr;

    }

