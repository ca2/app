#include "framework.h"
#include "acme/id.h"
//#include "acme/primitive/primitive/layered.h"


#if OBJECT_REFERENCE_COUNT_DEBUG


void defer_delete(object_reference_count_debug* p);


#endif


matter::~matter()
{

#if OBJECT_REFERENCE_COUNT_DEBUG

   ::defer_delete(m_pobjrefdbg);

#endif

   if (m_eobject & e_object_any_hook)
   {

      ::release(m_pmutex);

      if (m_eobject & e_object_any_update)
      {

         erase_from_any_source();

      }

   }

}


void matter::assert_valid() const
{

}


void matter::dump(dump_context & dumpcontext) const
{

}


::enum_type matter::get_payload_type() const
{ 
   
   return e_type_element; 

}


::e_status matter::initialize_matter(::matter* pmatter)
{

   m_psystem = pmatter->m_psystem;

   return ::success;

}


::e_status matter::on_initialize_object()
{

   return ::success;

}



::e_status matter::initialize(::object * pobject)
{

   auto estatus = initialize_matter(pobject);

   return estatus;

}


//::e_status matter::set_object(::object* pobject)
//{
//
//   return ::success;
//
//}


//::e_status matter::on_finish()
//{
//
//   auto estatus = destroy();
//
//   return estatus;
//
//}


//::e_status matter::set_finish_composites(::property_object * pcontextobjectFinish)
::e_status matter::destroy_composites()
{

   return ::success;

}





//::e_status matter::set_finish(::property_object * pcontextobjectFinish)
//{
//
//   set_finish_bit();
//
//   return ::success;
//
//}


//::e_status matter::finish(::property_object * pcontextobjectFinish)
::e_status matter::destroy()
{

   //auto estatus = set_finish();

   //if (estatus == error_pending)
   //{

   //   //m_psystem->add_pending_finish(this);

   //   return estatus;

   //}

   ////estatus = on_finish();

   ////if (estatus == error_pending)
   ////{

   ////   //m_psystem->add_pending_finish(this);

   ////   return estatus;

   ////}

   //return estatus;

   return ::success;


}


void matter::post_quit()
{

   set_finish_bit();

}


::e_status matter::set_finish()
{

   set_finish_bit();

   //destroy();

   try
   {

      on_set_finish();

   }
   catch (...)
   {

   }

   return ::success;

}


//::e_status matter::destroy()
//{
//
//   return ::success;
//
//}


void matter::on_set_finish()
{


}


::e_status matter::set_library_name(const char* pszLibraryName)
{

   return error_none;

}


::e_status matter::set_application_id(const char* pszApplicationId)
{

   return error_none;

}


const char* matter::debug_note() const
{

   return nullptr;

}


#ifdef _DEBUG

i64 matter::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = ++m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   add_ref_history(pReferer, pszObjRefDbg);

#endif

   return c;

}


i64 matter::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   auto c = --m_countReference;

#if OBJECT_REFERENCE_COUNT_DEBUG

   if (c > 0)
   {

      dec_ref_history(pReferer, pszObjRefDbg);

   }

#endif

   return c;

}


i64 matter::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   if (i == 0)
   {

      delete_this();

   }

   return i;

}


#endif


::matter * matter::clone() const
{

   __throw(error_interface_only);

   return nullptr;

}


::e_status matter::call_member(::i64 iId)
{

   return ::success_none;

}


//::e_status matter::command_handler(const char * pszCommand)
//{
//   
//   return ::success_none;
//
//}



void matter::set_mutex(synchronization_object* psync)
{

   ::release(m_pmutex);

   m_pmutex = psync;

}


void matter::erase_from_any_source()
{

}


//::e_status matter::branch()
//{
//
////   if (has(e_object_synchronous))
////   {
////
////      return operator()();
////
////   }
////   else
////   {
//
//     auto ptask = m_psystem->branch(__routine([this](){this->operator()();}));
//
//     if(!ptask)
//     {
//
//        return error_failed;
//
//     }
//
//     return ::success_started;
//
//   //}
//
//}


void matter::defer_create_mutex()
{

   if (!m_pmutex)
   {

      m_pmutex = new ::mutex;

   }

   set(e_object_any_hook);

}


//::e_status matter::run()
//{
//
//   return ::success;
//
//}


//::e_status matter::on_task()
//{
//
//   return run();
//   
//}


bool matter::is_thread() const
{

   return false;

}


::thread * matter::get_thread()
{

   return nullptr;

}


bool matter::thread_is_running() const
{

   return true;

}


//::property_object * matter::_get_context_object()
//{
//
//   return nullptr;
//
//}


::task * matter::get_task()
{

   return ::get_task();

}


::application* matter::_get_application()
{

   return nullptr;

}


const char * matter::get_task_tag()
{

   return nullptr;

}

//::index matter::task_add(::task* ptask)
//{
//
//   return -1;
//
//}


void matter::task_erase(::task* ptask)
{


}


void matter::notify_on_destroy(::property_object * pobject)
{

}


void matter::kick_idle()
{


}


::e_status matter::operator()()
{

   ::e_status estatus;

   try
   {

      estatus = run();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

}


void matter::operator()(::message::message * pmessage)
{


}


void matter::operator()(const ::payload & payload)
{

}


void matter::on_future(const ::payload & payload)
{

}


::e_status matter::run()
{

   while(true)
   {

      auto estatus = step();

      if(!estatus)
      {

         break;

      }

   }

   return ::success;

}


::e_status matter::step()
{

   return ::error_failed;

}


::payload matter::realize()
{

   return ::success;

}


::e_status matter::add_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   //__throw(error_not_implemented);

   pmatter->increment_reference_count();

   return ::success;

   //return ::error_not_implemented;

}


::e_status matter::add_reference(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


::e_status matter::release_composite2(::matter * pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


::e_status matter::finalize_composite(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


::e_status matter::release_reference(::matter* pmatter OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   return ::success_none;

}


::matter* matter::get_taskpool_container()
{

   return nullptr;

}


::task_pool* matter::taskpool()
{

   auto pcontainer = get_taskpool_container();

   if (pcontainer)
   {

      auto ptaskpool = pcontainer->taskpool();

      if (ptaskpool)
      {

         return ptaskpool;

      }

   }

   return nullptr;

}


//::task* matter::defer_branch(const ::id& id, const ::routine & routine)
//{
//
//   auto ptasktool = taskpool();
//
//   if (!ptasktool)
//   {
//
//      return nullptr;
//
//   }
//
//   return ptasktool->defer_branch(id, routine);
//
//}


::e_status matter::set_generic_object_name(const char* pszName)
{

   return ::success_none;

}


void matter::delete_this()
{

   try
   {

      delete this;

   }
   catch (...)
   {

   }

}


void matter::__tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const
{

   m_psystem->__tracea(elevel, pszFunction, pszFile, iLine, psz);

}


void matter::__tracef(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...) const
{

   va_list valist;

   va_start(valist, pszFormat);

   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, valist);

   va_end(valist);

}


void matter::__tracev(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist) const
{

   string str;

   str.FormatV(pszFormat, valist);

   __tracea(elevel, pszFunction, pszFile, iLine, str);

}


void matter::__simple_tracev(enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args) const
{

   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);

}


void matter::__simple_tracea(enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz) const
{

   __tracea(elevel, pszFunction, pszFileName, iLine, psz);

}


e_trace_category matter::trace_category() const
{

   return trace_category_general;

}


e_trace_category matter::trace_category(const ::matter * pobject) const
{

   return pobject->trace_category();

}


const char * matter::topic_text() const
{

   return typeid(*this).name();

}


::synchronization_result matter::sync_wait()
{

   return e_synchronization_result_error;

}


::synchronization_result matter::sync_wait(const ::duration & duration)
{

   return e_synchronization_result_error;

}


//void matter::future(const ::id & id, const ::payload & payload)
//{
//
//
//}


//void matter::future(::promise::update * psubject)
//{
//
//   if (!psubject->is_up_to_date())
//   {
//
//      on_subject(psubject, pcontext);
//
//      if(!psubject->m_bitProcessed)
//      {
//
//         on_subject(psubject, pcontext);
//
//      }
//
//      if(psubject->m_bitProcessed)
//      {
//
//         on_subject(psubject, pcontext);
//
//      }
//
//   }
//
//}


//void matter::on_subject(::promise::update *psubject)
//{
//
//
//}


//void matter::on_subject(::promise::update *psubject)
//{
//
//
//}


//void matter::on_subject(::promise::update *psubject)
//{
//
//
//}


strsize matter::sz_len() const
{

   return strlen(typeid(*this).name());

}


void matter::to_sz(char * sz, strsize len) const
{

   strncpy(sz, typeid(*this).name(), len);

}


bool matter::should_run_async() const
{

   return false;

}


::e_status matter::__thread_main()
{

   ::e_status estatus = operator()();

   return estatus;

}




//::e_status matter::__thread_procedure()
//{
//
//   ::u32 u = -1;
//
//   ::e_status estatus = error_failed;
//
//   ::e_status estatusOs = error_failed;
//
//   ::e_status estatusStart = error_failed;
//
//   {
//
//      estatusOs = osthread_init();
//
//      if (::succeeded(estatusOs))
//      {
//
//         estatusStart = __thread_init();
//
//      }
//
//   }
//
//   if (::succeeded(estatusStart))
//   {
//
//      estatus = __thread_main();
//
//   }
//
//   if (::succeeded(estatusOs))
//   {
//
//      __thread_term();
//
//      osthread_term();
//
//   }
//
//#if OBJECT_REFERENCE_COUNT_DEBUG
//
//   //release(OBJECT_REFERENCE_COUNT_DEBUG_P_NOTE(this, nullptr));
//
//   try
//   {
//
//      if (m_countReference > 1)
//      {
//
//         __check_pending_releases(this);
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//#endif
//
//   return estatus;
//
//}


::e_status matter::osthread_init()
{

   return ::success;

}


::e_status matter::__thread_init()
{

   return ::success;

}


::e_status matter::__thread_term()
{

   return ::success;

}


::e_status matter::osthread_term()
{

   return ::success;

}


void matter::exchange(stream& s)
{

}


stream & matter::write(stream& s) const
{

   return s;

}


stream& matter::read(stream& s)
{

   return s;

}


void matter::to_string(const class string_exchange & str) const
{

   str = type_c_str();

}


void matter::subject_handler(::subject::subject * psubject)
{


}


void matter::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
{


}


CLASS_DECL_ACME ::e_status __call(const ::routine & routine)
{

   return routine();

}



