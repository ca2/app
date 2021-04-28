// Created on 2021-03-10 17:37 BRT <3ThomasBS_!!
#include "framework.h"


object::~object()
{

}


#ifdef DEBUG


i64 object::add_ref(OBJ_REF_DBG_PARAMS)
{

   return property_object::add_ref(OBJ_REF_DBG_ARGS);

}


i64 object::dec_ref(OBJ_REF_DBG_PARAMS)
{

   return property_object::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 object::release(OBJ_REF_DBG_PARAMS)
{

   return property_object::release(OBJ_REF_DBG_ARGS);

}


#else


i64 object::add_ref(OBJ_REF_DBG_PARAMS)
{

   return property_object::add_ref(OBJ_REF_DBG_ARGS);

}


i64 object::dec_ref(OBJ_REF_DBG_PARAMS)
{

   return property_object::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 object::release(OBJ_REF_DBG_PARAMS)
{

   return property_object::release(OBJ_REF_DBG_ARGS);

}


#endif


//::apex::system* object::get_system() const
//{
//
//
//}
//

void object::process_exit_status(const ::e_status& estatus)
{


}


::apex::application* object::_get_application()
{

   return m_papplication;

}


   //inline ::apex::application* object::application() { return m_papplication; }


   //template < typename BASE_TYPE >
   //__pointer(BASE_TYPE) file_as(const ::payload& varFile);


   void object::add_routine(const ::id& idRoutine, const ::routine& routine)
   {


    }


    void object::add_each_routine_from(const ::id& idRoutine, ::object* pobjectSource)
    {


    }


    array < ::routine >* object::routinea(const ::id& idRoutine)
    {

       return nullptr;

    }


    void object::call_routine(const ::id& idRoutine)
    {



    }


   //inline ::payload object::context_value(const ::payload& payload)



   void object::task_erase(::task* ptask)
   {


    }


       ::e_status object::sleep(const ::duration& duration)
    {

       return ::success;

    }


   //template < typename BASE_TYPE >
   //void save_to(const ::payload& varFile, BASE_TYPE* pobject);

   
   ::e_status object::initialize(::object * pobject)
   {
      auto estatus = ::success;

#if OBJ_TYP_CTR

      if (!m_eobject.is(e_object_obj_typ_ctr))
      {

         m_eobject += e_object_obj_typ_ctr;

         OBJ_TYP_CTR_INC;

      }

#endif

      //#if OBJ_REF_DBG
      //
      //   string strType = type_name();
      //
      //   if (strType.contains_ci("session"))
      //   {
      //
      //      if (m_pobjrefdbg->m_iStep == 39)
      //      {
      //
      //         output_debug_string("session");
      //
      //      }
      //
      //   }
      //
      //#endif

      if (!get_system())
      {

         m_psystem = pobject->get_system();

      }

      if (!m_papplication)
      {

         m_papplication = pobject->m_papplication;

      }

      if (!m_psession)
      {

         m_psession = pobject->m_psession;

      }

      //if (!psystem)
      //{

      //   set_context_system(::::apex::get_system(pobject) OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

      //}

      if (!get_context())
      {

         if (m_papplication)
         {

            m_pcontext = m_papplication;

         }
         else if (m_psession)
         {

            m_pcontext = m_psession;

         }
         else if (m_psystem)
         {

            m_pcontext = m_psystem;

         }

      }

      return estatus;

   }


    ::e_status object::finalize()
    {


    }


    ::thread_pointer object::launch(const ::routine& routine)
    {

       auto pthread = __create_new < ::thread >();

       pthread->m_pmatter = routine;

       pthread->m_id = pthread->m_pmatter->type_name();

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

   //inline ::apex::application* object::get_application() const { return m_papplication; }

   //inline ::apex::session* object::get_session() const { return m_psession; }

   //::apex::system * psystem const { return m_psystemContext; }

   //::object * get_context_user() const { return m_puserContext; }

   //inline ::apex::application * application() const { return m_papplication; }

    string object::get_text(const ::payload& payload, const ::id& id)
    {

       return "";

    }
//
//#ifdef DEBUG
//    void set_context(::context* pcontext OBJ_REF_DBG_COMMA_PARAMS);
//    void set_context_thread(::thread* pthread OBJ_REF_DBG_COMMA_PARAMS);
//    void set_context_app(::apex::application* pappContext OBJ_REF_DBG_COMMA_PARAMS);
//    void set_context_session(::apex::session* psessionContext OBJ_REF_DBG_COMMA_PARAMS);
//   // void set_context_system(::apex::system* psystemContext OBJ_REF_DBG_COMMA_PARAMS);
//   // void set_context_user(::object * puserContext);
//#else
//   inline void set_context(::context* pcontext);
//   inline void set_context_thread(::thread* pthread);
//   inline void set_context_app(::apex::application* pappContext);
//   inline void set_context_session(::apex::session* psessionContext);
//   //inline void set_context_system(::apex::system* psystemContext);
//   //inline void set_context_user(::object * puserContext);
//#endif


   // void set_object(::object * pobject) 


   //inline void defer_set_object(::object * pobject);

       ::e_status object::operator()()
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

   //::image_result create_image();
   //::image_result create_image(const ::size_i32 & size, ::eobject eobjectCreate = OK, int iGoodStride = -1, bool bPreserve = false);

   //::image_result get_image(const ::payload & varFile, bool bCache = true, bool bSync = true);
   //::image_result matter_image(const string & strMatter, bool bCache = true, bool bSync = true);

   //template < typename BASE_TYPE >
   //inline __transport(BASE_TYPE) __create();

   //template < typename BASE_TYPE >
   //inline __transport(BASE_TYPE) __id_create(const ::id& id);

   //template < typename TYPE >
   //inline __transport(TYPE) __create_new();

   //inline ::e_status __compose(__composite(::image) & pimage);

   //inline ::e_status __compose(__composite(::image) & pimage, ::image * pimageSource);

   //inline ::e_status __defer_compose(__composite(::image) & pimage) { return !pimage ? __compose(pimage) : ::e_status(::success); }

   // for composition (ownership)

   //template < typename BASE_TYPE >
   //inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline ::e_status __id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id);

   //template < typename BASE_TYPE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const SOURCE* psource);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __raw_compose(__composite(BASE_TYPE)& pusermessage, const __pointer(SOURCE)& psource);

   //template < typename TYPE >
   //inline ::e_status __raw_compose_new(__composite(TYPE)& ptype);

   //template < typename TYPE >
   //inline ::e_status __compose_new(__composite(TYPE)& ptype);




   //template < typename BASE_TYPE >
   //inline ::e_status __defer_compose(__composite(BASE_TYPE)& pusermessage) { return !pusermessage ? __compose(pusermessage) : ::e_status(::success); }

   //template < typename BASE_TYPE >
   //inline ::e_status __defer_id_compose(__composite(BASE_TYPE)& pusermessage, const ::id& id) { return !pusermessage ? __id_compose(pusermessage) : ::e_status(::success); }

   //template < typename TYPE >
   //inline ::e_status __defer_raw_compose_new(__composite(TYPE)& ptype) { return !ptype ? __raw_compose_new(ptype) : ::e_status(::success); }

   //template < typename TYPE >
   //inline ::e_status __defer_compose_new(__composite(TYPE)& ptype) { return !ptype ? __compose_new(ptype) : ::e_status(::success); }




   //template < typename BASE_TYPE >
   //inline ::e_status __construct(__pointer(BASE_TYPE)& pusermessage);

   //template < typename BASE_TYPE >
   //inline ::e_status __id_construct(__pointer(BASE_TYPE)& pusermessage, const ::id& id);

   //template < typename TYPE >
   //inline ::e_status __construct_new(__pointer(TYPE)& pusermessage);

   //template < typename BASE_TYPE >
   //inline ::e_status __release(__composite(BASE_TYPE)& pcomposite OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE >
   //inline ::e_status __release(__reference(BASE_TYPE)& preference OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status release_reference(__pointer(SOURCE)& psource OBJ_REF_DBG_COMMA_PARAMS);


   // ::e_status add_composite(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS) 
   // ::e_status add_reference(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS) 


   // ::e_status release_composite2(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS) 
   // ::e_status finalize_composite(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS) 
   // ::e_status release_reference(::matter* pobject OBJ_REF_DBG_COMMA_PARAMS) 


   //template < typename BASE_TYPE >
   //inline ::e_status add_composite(__composite(BASE_TYPE)& pcomposite OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE)& preference, const SOURCE* psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE)& preference, const __pointer(SOURCE)& psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename BASE_TYPE, typename SOURCE >
   //inline ::e_status __refer(__reference(BASE_TYPE)& preference, const ::primitive::member < SOURCE >& psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(SOURCE* psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(__pointer(SOURCE)& psource OBJ_REF_DBG_COMMA_PARAMS);

   //template < typename SOURCE >
   //inline ::e_status add_reference(__reference(SOURCE)& psource OBJ_REF_DBG_COMMA_PARAMS);

void object::delete_this()
{


    }

       void object::destruct()
    {


    }

    void object::system(const char* pszProjectName)
    {

   }

   ::e_status object::enable_application_events(bool bEnable)
   {

      return ::success;

    }

    ::e_status object::handle_exception(const ::exception::exception& e)
    {

       return ::success;

    }

    ::e_status object::top_handle_exception(const ::exception::exception& e)
    {

       return ::success;

    }


    ::e_status object::process_exception(const ::exception::exception& e)
    {

       return ::success;

    }


    ::property_object* object::parent_property_set_holder() const
    {

       if (m_papplication && m_papplication.m_p != this)
       {

          return m_papplication.m_p;

       }

       if (m_psession && m_psession.m_p != this)
       {

          return m_psession.m_p;

       }

       if (m_psystem && (::property_object*)m_psystem != (::property_object *) this)
       {

          return m_psystem;

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
    
    
    void object::child_post_quit(const char* pszTag)
    {


    }


    void object::child_post_quit_and_wait(const char* pszTag, const duration& duration)
    {


    }


    ::e_status object::finish(::property_object * pcontextobjectFinish)
    {

       return ::success;

    }

   ::e_status object::set_finish(::property_object* pcontextobjectFinish)
    {

       return ::success;

    }
    
       ::e_status object::set_finish_composites(::property_object* pcontextobjectFinish)
    {

          return ::success;

    }
    
       
       void object::on_finish()
    {


    }


       void object::defer_update_object_id()
    {


    }

    
    ::id object::calc_default_object_id() const
    {

       return ::id();

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


   ::e_status object::request_file(const ::payload& varFile)
   {

      return ::success;

    }


    ::e_status object::request_file(const ::payload& varFile, ::payload varQuery)
    {

      return ::success;

    }


    ::e_status object::request(arguments arguments)
    {

       return ::success;

    }


    ::e_status object::do_request(::create* pcreate)
    {

       return ::success;

    }


    __pointer(::extended::future < ::conversation >)  object::message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box& emessagebox)
    {

       return nullptr;

    }
   //{
   //
   //   return message_box(nullptr, pszMessage, pszTitle, emessagebox, process);

   //}


   // ::e_status message_box_timeout(const char * pszMessage, const char * pszTitle = nullptr, const ::duration & durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   //{

   //   return message_box_timeout(nullptr, pszMessage, pszTitle, durationTimeout, emessagebox, process);

   //}

   // ::e_status message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());
   // ::e_status message_box_timeout(::user::primitive* puserinteractionOwner, const char* pszMessage, const char* pszTitle = nullptr, const ::duration& durationTimeout = ::duration::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future());

    void object::release_references()
    {

    }

    __pointer(::matter) object::running(const char* pszTag) const
    {

       return nullptr;

    }

    bool object::___is_reference(::matter* pobject) const
    {

       return false;

    }

    bool object::__is_composite(::matter* pobject) const
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

    ::e_status object::call_request(::create* pcreate)
    {

       return ::success;

    }

   //// former user::server
   // ::user::document* open_new_document(::apex::application* pappOnBehalfOf);
    void object::on_request(::create* pcreate)
    {


    }

   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf);
   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& varFile, const ::payload & varOptions, ::user::interaction* puiParent = nullptr, ewindowflag eflag = e_window_flag_none, ::id id = ::id());
   // ::user::document* open_document_file(::apex::application* pappOnBehalfOf, const ::payload& varFile);
   // ::user::document* create_subdocument(::user::impact_data* pimpactdata);


    ::e_status object::run()
    {

       return ::success;

    }


    string object::lstr(const ::id& id, string strDefault)
    {

       return "";

    }


    string object::__get_text(string str)
    {

       return "";

    }



   //template < typename PRED >
   //::image_result get_image(const ::payload & varFile, ::u64 uTrait, PRED pred);

   // ::image_result load_image(const ::payload & varFile, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   // ::image_result load_matter_image(const char * pszMatter, bool bSync = true, bool bCache = true, bool bCreateHelperMaps = false);
   // ::image_result load_matter_icon(string_array & straMatter, string strIcon);
   // ::image_result load_thumbnail(const ::payload & varFile, int w, int h);
   // ::image_result load_thumbnail(const char * pszPath);
   // ::image_result load_dib(const ::file::path & pathDib);



   bool object::IsSerializable() const
   {

      return false;

   }


   void object::start()
   {


   }


   void object::single_fork(const ::routine_array& routinea)
   {


   }


   void object::multiple_fork(const ::routine_array& routinea)
   {


   }

//   using property_object::defer_fork;

  /* template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread, const ::routine& routine)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->start(routine);

      return pthread;

   }


   template < typename THREAD >
   inline __pointer(THREAD)& defer_fork(__pointer(THREAD)& pthread)
   {

      if (pthread && pthread->is_running())
      {

         return pthread;

      }

      pthread->begin_thread();

      return pthread;

   }*/


   //inline ::e_status object::defer_fork(::thread_pointer& pthread, const ::routine& routine);


   //template < typename THREAD >
   //inline __pointer(THREAD)& start(__pointer(THREAD) & pthread)
   //{

   //   pthread->_start(pthread);

   //   return pthread;

   //}


   //template < typename PRED >
   //inline ::thread_pointer fork(PRED pred);


   //inline ::thread_pointer lcontext_object::aunch(const ::routine& routine);


   //template < typename METHOD >
   //inline ::task_pointer object::opt_fork(const ::routine& routine)
   //{

   //   auto ptask = ::get_task();

   //   synchronous_lock synchronouslock(ptask->mutex());

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

   //::thread_pointer object::begin(::e_priority epriority, ::u32 nStackSize, u32 dwCreateFlags)
   //{

   //   return nullptr;

   //}
   //::thread_pointer defer_fork(string strThread = "");

//#ifdef __APPLE__
//    void ns_main_async(dispatch_block_t block);
//#endif

   //inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());
   //inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open & eopen = ::file::e_open());


   // void to_string(string & str) const 


    ::file_result object::get_file(const ::payload& varFile, const ::file::e_open& eopen)
    {

       return nullptr;

    }

   //inline ::file_result get_reader(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary);
   //inline ::file_result get_writer(const ::payload& varFile, const ::file::e_open& eopen = ::file::e_open_binary | ::file::e_open_defer_create_directory | ::file::e_open_create);



   //::e_status add_update_notification(property * pproperty);
   //::e_status add_update_notification(const ::id & id, bool bCreate = true);
   //::e_status property_notify(const ::id & id, ::matter * pmatter);


//   inline void format_topic_text(const char * psz, ...)
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
//   inline void format_topic_text_v(const char * psz, va_list valist)
//   {
//
//      string str;
//      str.FormatV(psz, valist);
//      set_topic_text(str);
//
//   }


   //template < typename TYPE >
   //auto member_fork(::e_status (TYPE:: * pfn)(), ::e_priority epriority = ::priority_normal)
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

   //   return fork(pfn, ::priority_below_normal);

   //}


   //template < typename TYPE >
   //::e_status __construct(::thread_pointer& p, void (TYPE::* pfn)(), e_priority epriority);

   //template < typename TYPE >
   //::e_status __construct_below_normal(::thread_pointer& p, void (TYPE::* pfn)());


   //template < typename TYPE >
   //::thread_pointer __start_thread(const ::id& id, void(TYPE::* pfn)(), e_priority epriority = priority_normal);


    matter* object::get_taskpool_container()
    {

       return nullptr;

    }

