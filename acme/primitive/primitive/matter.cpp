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

   ::release(m_pmutex);

   if (m_eobject & e_object_any_hook && m_psystem)
   {

      m_psystem->erase_from_any_hook(this);

   }

}


void matter::assert_valid() const
{

}


void matter::dump(dump_context & dumpcontext) const
{

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




void matter::post_quit()
{

   set_finishing();

}


::e_status matter::set_finish()
{

   set_finishing();

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


::element * matter::clone() const
{

   throw ::interface_only_exception();

   return nullptr;

}


bool matter::is_ready_to_quit() const
{

   return true;

}


void matter::set_mutex(synchronization_object* psync)
{

   if (::is_set(psync))
   {

      psync->increment_reference_count();

   }

   ::release(m_pmutex);

   m_pmutex = psync;

}


//void matter::erase_from_any_source()
//{
//
//}


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

      set_mutex(__new(::mutex));

   }

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




void matter::on_future(const ::payload & payload)
{

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


//void matter::__tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFile, int iLine, const char * psz) const
//{
//
//   m_psystem->__tracea(elevel, pszFunction, pszFile, iLine, psz);
//
//}
//
//
//void matter::__tracef(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...) const
//{
//
//   va_list valist;
//
//   va_start(valist, pszFormat);
//
//   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, valist);
//
//   va_end(valist);
//
//}


//void matter::__tracev(enum_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list valist) const
//{
//
//   string str;
//
//   va_list ptr1;
//
//   va_copy(ptr1, valist);
//
//   str.FormatV(pszFormat, valist);
//
//   va_end(ptr1);
//
//   __tracea(elevel, pszFunction, pszFile, iLine, str);
//
//}


//void matter::__simple_tracev(enum_trace_level elevel, const char* pszFunction, const char* pszFile, i32 iLine, const char* pszFormat, va_list args) const
//{
//
//   __tracev(elevel, pszFunction, pszFile, iLine, pszFormat, args);
//
//}
//
//
//void matter::__simple_tracea(enum_trace_level elevel, const char* pszFunction, const char* pszFileName, i32 iLine, const char* psz) const
//{
//
//   __tracea(elevel, pszFunction, pszFileName, iLine, psz);
//
//}


enum_trace_category matter::trace_category() const
{

   return e_trace_category_general;

}


enum_trace_category matter::trace_category(const ::matter * pobject) const
{

   return pobject->trace_category();

}


string matter::topic_text() const
{

   return __type_name(this);

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
//      handle(psubject, pcontext);
//
//      if(!psubject->m_bitProcessed)
//      {
//
//         handle(psubject, pcontext);
//
//      }
//
//      if(psubject->m_bitProcessed)
//      {
//
//         handle(psubject, pcontext);
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


//void matter::to_string(const class string_exchange & str) const
//{
//
//   str = __type_name(this);
//
//}
//


//void matter::route(::signal * psignal)
//{
//
//
//}

//
//void matter::signal(::signal * psignal)
//{
//
//
//}

//
//void matter::signal(::signal * psignal)
//{
//
//
//}


//void matter::route(::subject * psubject, ::context * pcontext)
//{
//
//
//}


//void matter::post_process(::subject * psubject, ::context * pcontext)
//{
//
//
//}





CLASS_DECL_ACME ::e_status __call(const ::routine & routine)
{

   return routine();

}



