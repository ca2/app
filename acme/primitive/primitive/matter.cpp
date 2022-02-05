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


void matter::assert_ok() const
{

}


void matter::dump(dump_context & dumpcontext) const
{

}


void matter::initialize_matter(::matter* pmatter)
{

   m_psystem = pmatter->m_psystem;

   //return ::success;

}


void matter::on_initialize_object()
{

   //return ::success;

}



//void matter::set_object(::object* pobject)
//{
//
//   return ::success;
//
//}


//void matter::on_finish()
//{
//
//   auto estatus = destroy();
//
//   return estatus;
//
//}


//void matter::set_finish_composites(::property_object * pcontextobjectFinish)
void matter::destroy_composites()
{

   //return ::success;

}





//void matter::set_finish(::property_object * pcontextobjectFinish)
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


void matter::set_finish()
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

   //return ::success;

}


//void matter::destroy()
//{
//
//   return ::success;
//
//}


void matter::on_set_finish()
{


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


//void matter::branch()
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


//void matter::run()
//{
//
//   return ::success;
//
//}


//void matter::on_task()
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



void matter::on_sequence(const ::payload & payload)
{

}


//::task* matter::defer_branch(const ::atom& atom, const ::routine & routine)
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
//   return ptasktool->defer_branch(atom, routine);
//
//}



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
//   str.format_arguments(pszFormat, valist);
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


void matter::trace_arguments(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{


   tracer(m_psystem, etracelevel, etracecategory).format_output_arguments(pszFormat, arguments);


}


void matter::trace_log_information_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_information, etracecategory).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_warning_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_warning, etracecategory).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_error_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_error, etracecategory).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_fatal_arguments(enum_trace_category etracecategory, const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_fatal, etracecategory).format_output_arguments(pszFormat, arguments);

}




void matter::trace_arguments(enum_trace_level etracelevel, const char * pszFormat, va_list & arguments)
{


   tracer(m_psystem, etracelevel, trace_category()).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_information_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_information, trace_category()).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_warning_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_warning, trace_category()).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_error_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_error, trace_category()).format_output_arguments(pszFormat, arguments);

}


void matter::trace_log_fatal_arguments(const char * pszFormat, va_list & arguments)
{

   tracer(m_psystem, e_trace_level_fatal, trace_category()).format_output_arguments(pszFormat, arguments);

}





void matter::trace(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(etracelevel, etracecategory, psz, arguments);

   va_end(arguments);

}


void matter::trace_log_information(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_information, etracecategory, psz, arguments);

   va_end(arguments);

}


void matter::trace_log_warning(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_warning, etracecategory, psz, arguments);

   va_end(arguments);

}


void matter::trace_log_error(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_error, etracecategory, psz, arguments);

   va_end(arguments);

}


void matter::trace_log_fatal(enum_trace_category etracecategory, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_fatal, etracecategory, psz, arguments);

   va_end(arguments);

}


void matter::trace(enum_trace_level etracelevel, const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(etracelevel, trace_category(), psz, arguments);

   va_end(arguments);

}


void matter::trace_log_information(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_information, trace_category(), psz, arguments);

   va_end(arguments);

}


void matter::trace_log_warning(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_warning, trace_category(), psz, arguments);

   va_end(arguments);

}


void matter::trace_log_error(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_error, trace_category(), psz, arguments);

   va_end(arguments);

}


void matter::trace_log_fatal(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   trace_arguments(e_trace_level_fatal, trace_category(), psz, arguments);

   va_end(arguments);

}



//void matter::future(const ::atom & atom, const ::payload & payload)
//{
//
//
//}


//void matter::future(::promise::update * ptopic)
//{
//
//   if (!ptopic->is_up_to_date())
//   {
//
//      handle(ptopic, pcontext);
//
//      if(!ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, pcontext);
//
//      }
//
//      if(ptopic->m_bitProcessed)
//      {
//
//         handle(ptopic, pcontext);
//
//      }
//
//   }
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}


//void matter::on_subject(::promise::update *ptopic)
//{
//
//
//}




void matter::__thread_main()
{

   //::e_status estatus = operator()();

   operator()();

   //return estatus;

}




//void matter::__thread_procedure()
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


void matter::osthread_init()
{

   //return ::success;

}


void matter::__thread_init()
{

   //return ::success;

}


void matter::__thread_term()
{

   //return ::success;

}


void matter::osthread_term()
{

   //return ::success;

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


//void matter::route(::topic * ptopic, ::context * pcontext)
//{
//
//
//}


//void matter::post_process(::topic * ptopic, ::context * pcontext)
//{
//
//
//}





CLASS_DECL_ACME void __call(const ::routine & routine)
{

   //return routine();

   routine();

}


__pointer(::sequence < ::conversation >) matter::message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox)
{

   auto psequence = m_psystem->message_box(strMessage, strTitle, emessagebox);

   return psequence;

}



