#include "framework.h"
#include "manual_reset_event.h"
#include "task.h"
#include "task_flag.h"
#include "acme/constant/id.h"

//#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/prototype/payload.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/windowing/window.h"
//#include "acme/windowing/window_base.h"
#ifdef LINUX
#include "acme/operating_system/ansi/_pthread.h"
#endif


namespace parallelization
{




   //CLASS_DECL_ACME comparable_eq_array<itask_t> * s_piaThread2 = nullptr;
   //CLASS_DECL_ACME pointer_array < thread > * s_pthreadptra2 = nullptr;
   //CLASS_DECL_ACMEcritical_section * s_pcs2 = nullptr;


   //CLASS_DECL_ACME void init_multitasking()
   //{

   //   //s_pcs2 = ___new critical_section();

   //   //s_piaThread2 = aaa_memory_new comparable_eq_array<itask_t>;

   //   //s_pthreadptra2 = aaa_memory_new pointer_array < thread >;

   //   __node_init_multitasking();

   //}


   //CLASS_DECL_ACME void term_multitasking()
   //{

   //   __node_term_multitasking();

   //   //::acme::del(s_pthreadptra2);

   //   //::acme::del(s_piaThread2);

   //   //::acme::del(s_pcs2);

   //}

   //CLASS_DECL_ACME bool thread_id_registered(itask_t atom)
   //{

   //   //cslock lock(s_pcs2);

   //   //return s_piaThread2->contains(atom);

   //   return system()->get_task(atom) != nullptr;

   //}


   //bool thread_registered(::thread * pthread)
   //{

   //   return system()->get_thread_id(pthread) != 0;

   //}


   //void thread_register(itask_t itask, ::thread * pthread)
   //{

   //   system()->set_thread(itask, pthread);

   //}


   //void thread_unregister(itask_t itask, ::thread * pthread)
   //{

   //   auto psystem = ::get_context_system();

   //   psystem->unset_thread(itask, pthread);

   //}


   //bool is_child(::thread * pthreadChildCandidate)
   //{

   //   if (::is_null(pthreadChildCandidate))
   //   {

   //      return false;

   //   }

   //   if (pthreadChildCandidate->m_pthreadParent)
   //   {

   //      return true;

   //   }

   //   synchronous_lock synchronouslock(system()->m_pmutexThread);

   //   for (auto & pair : system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         if (pair.element1()->m_threada.contains(pthreadChildCandidate))
   //         {

   //            return true;

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //   return false;

   //}


   //void post_quit_to_all_threads()
   //{

   //   synchronous_lock synchronouslock(system()->m_pmutexThread);

   //   for (auto& pair : system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         pair.element1()->destroy();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}


   //CLASS_DECL_ACME ::task_pointer calc_parent(::thread * pthread)
   //{

   //   if (::is_null(pthread))
   //   {

   //      return nullptr;

   //   }

   //   if (pthread == ::get_context_system())
   //   {

   //      return nullptr;

   //   }

   //   auto pthreadContext = pthread->get_context_thread();

   //   if (::is_set(pthreadContext))
   //   {

   //      if (pthreadContext->is_set_finish() || !pthreadContext->m_bLastingThread)
   //      {

   //         pthreadContext = calc_parent(pthreadContext);

   //         if (::is_set(pthreadContext))
   //         {

   //            return pthreadContext;

   //         }

   //      }
   //      else
   //      {

   //         return pthreadContext;

   //      }

   //   }

   //   auto pappContext = pthread->get_app();

   //   if (::is_set(pappContext) && pappContext != pthread)
   //   {

   //      return pappContext;

   //   }

   //   auto psessionContext = pthread->get_session();

   //   if (psessionContext != pthread && ::is_set(psessionContext))
   //   {

   //      return psessionContext;

   //   }

   //   auto psystemContext = pthread->get_context_system();

   //   if (psystemContext != pthread && ::is_set(psystemContext))
   //   {

   //      return psystemContext;

   //   }

   //   return ::get_context_system();

   //}


} // namespace parallelization

//
//CLASS_DECL_ACME ::task * get_thread_raw()
//{
//
//   return ::get_task();
//
//}


//typedef bool THREAD_GET_RUN();
//using PFN_THREAD_GET_RUN = THREAD_GET_RUN*;


//PFN_THREAD_GET_RUN g_pthreadgetrun = nullptr;


//
//CLASS_DECL_ACME void set_thread_get_run(PFN_THREAD_GET_RUN pthreadrun)
//{
//
//   g_pthreadgetrun = pthreadrun;
//
//}


//bool task_get_run()
//{
//
//   try
//   {
//
//      if(::is_null(::get_task()) || !::get_task()->is_thread()) // system threads don't have generally associated ca2 thread matter
//      {
//         ////////// and have short life, so it is safe to keep it running
//         //return true;
//         return system()->task_get_run();
//
//      }
//
//      return ::get_task()->task_get_run();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return false;
//
//}


namespace parallelization
{


   //CLASS_DECL_ACME void finish()
   //{

   //   finish(::get_task());

   //}


   //CLASS_DECL_ACME bool post_quit_and_wait(const class time & time)
   //{

   //   return post_quit_and_wait(::get_task(), time);

   //}


   //void finish(::thread * pthread)
   //{

   //   if (pthread == nullptr)
   //   {

   //      return;

   //   }

   //   try
   //   {

   //      pthread->destroy();

   //   }
   //   catch (...)
   //   {


   //   }

   //}


   //bool post_quit_and_wait(::thread * pthreadParam, const class time & time)
   //{

   //   ::task_pointer pthread;

   //   try
   //   {

   //      pthread = pthreadParam;

   //   }
   //   catch (...)
   //   {

   //      return true;

   //   }

   //   if (pthread.is_null())
   //   {

   //      return true;

   //   }

   //   try
   //   {

   //      pthread->destroy();

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      return pthread->wait(time).succeeded();

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


} // namespace parallelization



//::pointer < ::mutex > & message_dispatch_mutex()
//{
//
//
//   return *s_pmutexMessageDispatch;
//
//}


CLASS_DECL_ACME void call(const ::procedure & procedure)
{

   procedure();

}


bool isvowel_dup(int i)
{

   if (i == 'a')
   {
      return true;
   }
   else if (i == 'e')
   {
      return true;
   }
   else if (i == 'i')
   {
      return true;
   }
   else if (i == 'o')
   {
      return true;
   }
   else if (i == 'u')
   {
      return true;
   }
   if (i == 'A')
   {
      return true;
   }
   else if (i == 'E')
   {
      return true;
   }
   else if (i == 'I')
   {
      return true;
   }
   else if (i == 'O')
   {
      return true;
   }
   else if (i == 'U')
   {
      return true;
   }
   else
   {
      return false;
   }

}


string _001OnlyAlnumString(const ::scoped_string & scopedstr)
{

   string strOnlyAlnum;

   auto psz = scopedstr.begin();

   auto end = scopedstr.end();

   while (psz < end)
   {

      if (character_isalnum(*psz))
      {

         strOnlyAlnum += *psz;

      }

      psz++;

   }

   return strOnlyAlnum;

}


string _001OnlyAlnumNonVowelString(const ::scoped_string & scopedstr)
{

   string strOnlyAlnum;

   auto psz = scopedstr.begin();

   while (*psz)
   {

      if (character_isalnum(*psz))
      {

         if (!isvowel_dup(*psz))
         {

            strOnlyAlnum += *psz;

         }

      }

      psz++;

   }

   return strOnlyAlnum;

}


string _001CompactString(const ::string & str, int iSkip, int iSkipBegin = 0)
{

   string strCompact;

   strsize i = 0;

   for (; i < iSkipBegin; i++)
   {

      strCompact += str[i];

   }

   for (; i < str.length(); i += (iSkip + 1))
   {

      strCompact += str[i];

   }

   return strCompact;

}


void thread_name_abbreviate(string & strName, int len)
{

   if (strName.length() <= len)
   {

      return;

   }

   string_array stra;

   strsize iFindLast = 0;

   string strOnlyAlnum;

   auto range = strName();

   auto pfind = range.m_begin;

   while (range.is_set())
   {

      auto pfindNext = range(pfind).find("::");

      if(::not_found(pfindNext))
      {

         stra.add(range(pfind));

         break;

      }

      stra.add({ pfind, pfindNext + 1 });

      pfind = pfindNext + 2;

   }

   strName = stra.implode(":");

   if (strName.length() <= len)
   {

      return;

   }

   for (::collection::index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumString(stra[i]);

      strName = stra.implode(":");

      if (strName.length() <= len)
      {

         return;

      }

   }

   for (::collection::index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumNonVowelString(stra[i]);

      strName = stra.implode(":");

      if (strName.length() <= len)
      {

         return;

      }

   }

   for (::collection::index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001CompactString(stra[i], 1, 1);

      strName = stra.implode(":");

      if (strName.length() <= len)
      {

         return;

      }

   }

   strName.truncate(len);

}


void run_runnable(::matter * pmatter)
{

   //void     estatus = error_exception;

   //try
   //{

   //   try
   //   {

         //estatus = pmatter->operator()();

   pmatter->call();

   //   }
   //   catch (...)
   //   {

   //   }

   //}
   //catch (...)
   //{

   //}

   //return estatus;

}


//void run_routine(const ::procedure & procedure)
//{
//
//   procedure();
//
//}


thread_local ::task * t_ptask;


CLASS_DECL_ACME ::task * _get_task()
{
   
   return t_ptask;
   
}


CLASS_DECL_ACME ::task * get_task()
{

   return t_ptask;

   //if (!t_ptask)
   //{

   //   auto pplatform = ::system()->platform();

   //   if(::is_set(pplatform))
   //   {

   //      auto psystem = pplatform->system();

   //      if(::is_set(psystem))
   //      {

   //         t_ptask = { transfer_t{}, ___new ::task() };

   //         t_ptask->initialize(pplatform->system());

   //      }

   //   }

   //}

   return t_ptask;

}


//thread_local task_bitset t_bitset;


//thread_local payload t_payloada[e_task_payload_count];




//CLASS_DECL_ACME ::thread * get_thread()
//{
//
//   return ___thread((layered *) t_ptask.m_p);
//
//}


CLASS_DECL_ACME void set_task(task * ptask)
{

   auto ptaskOld = t_ptask;
// #if REFERENCING_DEBUGGING
//
//    ::allocator::add_referer({ ::system()->platform(), __FUNCTION_FILE_LINE__ });
// #endif
//    //::increment_reference_count(ptask);

   t_ptask = ptask;

   if (::is_set(ptask))
   {

      ptask->m_itask = ::current_itask();

      ptask->m_htask = ::current_htask();

   }

   ::release(ptaskOld);

}


CLASS_DECL_ACME void task_release()
{

   //auto ptask = t_ptask;

   //t_ptask = nullptr;

   //::release(ptask);

   //::acme::windowing::window::nanowindowimplementationa().clear();

   //::acme::windowing::window::nanowindowimplementationa().free_extra();

   //auto ptask = t_ptask;

   /*if(ptask)
   {

      printf_line("::task_release() ptask=%s", typeid(*ptask).name());

      ptask->set_flag(e_flag_task_terminated);

   }*/

   t_ptask = nullptr;

}


bool task_get_run()
{

   auto ptask = t_ptask;

   if (::is_null(ptask))
   {

      return true;

   }

   return ptask->task_get_run();

}


#ifdef PARALLELIZATION_PTHREAD


//CRITICAL_SECTION_FUNCTION_RETURN pthread_recursive_mutex_init(pthread_mutex_t * pmutex)
//{
//
//   pthread_mutexattr_t attribute;
//
//   pthread_mutexattr_init(&attribute);
//
//   pthread_mutexattr_settype(&attribute, PTHREAD_MUTEX_RECURSIVE);
//
//   return pthread_mutex_init(pmutex, &attribute);
//
//}


#endif


thread_local task_bitset t_taskbitset;

task_bitset& task_flag()
{ 

   return t_taskbitset;

}


thread_local payload t_payloada[e_task_payload_count];


::payload & task_payload(enum_task_payload etaskpayload)
{ 
   
   return t_payloada[etaskpayload]; 

}


//CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
//{
//
//   auto pevent = __allocate manual_reset_event();
//
//   main_asynchronous([ function, &pevent ]
//   {
//
//      if(pevent)
//      {
//
//         function();
//
//         if(pevent)
//         {
//
//            pevent->SetEvent();
//
//         }
//
//      }
//
//   });
//
//   if(!pevent->wait(time))
//   {
//
//      pevent.release();
//
//      return false;
//
//   }
//
//   return true;
//
//}


CLASS_DECL_ACME bool is_single_main_user_thread()
{

#if defined(WINDOWS_DESKTOP)

   return false;

#else

   return true;

#endif

}



