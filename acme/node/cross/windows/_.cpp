#include "framework.h"
#include "acme/os/_c.h"
#include "acme/os/_.h"
#include "acme/const/id.h"


namespace parallelization
{


   bool task_registered(::task * ptask)
   {

      return ::acme::get_system()->get_task_id(ptask) != 0;

   }


   void task_register(itask_t itask, ::task * ptask)
   {

      ::acme::get_system()->set_task(itask, ptask);

   }


   void task_unregister(itask_t itask, ::task * ptask)
   {

      auto psystem = ::get_context_system();

      psystem->unset_task(itask, ptask);

   }


   //CLASS_DECL_ACME comparable_eq_array<itask_t> * s_piaThread2 = nullptr;
   //CLASS_DECL_ACME __pointer_array(thread) * s_pthreadptra2 = nullptr;
   //CLASS_DECL_ACMEcritical_section * s_pcs2 = nullptr;


   //CLASS_DECL_ACME void init_multithreading()
   //{

   //   //s_pcs2 = new critical_section();

   //   //s_piaThread2 = new comparable_eq_array<itask_t>;

   //   //s_pthreadptra2 = new __pointer_array(thread);

   //   __node_init_multithreading();

   //}


   //CLASS_DECL_ACME void term_multithreading()
   //{

   //   __node_term_multithreading();

   //   //::acme::del(s_pthreadptra2);

   //   //::acme::del(s_piaThread2);

   //   //::acme::del(s_pcs2);

   //}

   //CLASS_DECL_ACME bool thread_id_registered(itask_t id)
   //{

   //   //critical_section_lock lock(s_pcs2);

   //   //return s_piaThread2->contains(id);

   //   return ::acme::get_system()->get_task(id) != nullptr;

   //}


   //bool thread_registered(::thread * pthread)
   //{

   //   return ::acme::get_system()->get_thread_id(pthread) != 0;

   //}


   //void thread_register(itask_t itask, ::thread * pthread)
   //{

   //   ::acme::get_system()->set_thread(itask, pthread);

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

   //   synchronous_lock synchronouslock(::acme::get_system()->m_mutexThread);

   //   for (auto & pair : ::acme::get_system()->m_threadidmap)
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

   //   synchronous_lock synchronouslock(::acme::get_system()->m_mutexThread);

   //   for (auto& pair : ::acme::get_system()->m_threadidmap)
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


   //CLASS_DECL_ACME void post_to_all_threads(const ::id & id, wparam wparam, lparam lparam)
   //{

   //   synchronous_lock synchronouslock(::acme::get_system()->m_mutexThread);

   //   for (auto& pair : ::acme::get_system()->m_threadidmap)
   //   {

   //      try
   //      {

   //         pair.element1()->post_message(message, wparam, lparam);

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

   //   auto papplicationContext = pthread->get_application();

   //   if (::is_set(papplicationContext) && papplicationContext != pthread)
   //   {

   //      return papplicationContext;

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
//         return ::acme::get_system()->task_get_run();
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


   //CLASS_DECL_ACME bool post_quit_and_wait(const duration & duration)
   //{

   //   return post_quit_and_wait(::get_task(), duration);

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


   //bool post_quit_and_wait(::thread * pthreadParam, const duration & duration)
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

   //      return pthread->wait(duration).succeeded();

   //   }
   //   catch (...)
   //   {

   //   }

   //   return true;

   //}


} // namespace parallelization


::mutex * s_pmutexMessageDispatch = nullptr;


::mutex & message_dispatch_mutex()
{


   return *s_pmutexMessageDispatch;

}




CLASS_DECL_ACME ::e_status call(const ::routine & routine)
{

   ::e_status estatus;

   try
   {

      estatus = routine();

   }
   catch (...)
   {

      estatus = ::error_exception;

   }

   return estatus;

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


string _001OnlyAlnumString(const char * psz)
{

   string strOnlyAlnum;

   while (*psz)
   {

      if (ansi_char_is_alphanumeric(*psz))
      {

         strOnlyAlnum += *psz;

      }

      psz++;

   }

   return strOnlyAlnum;

}


string _001OnlyAlnumNonVowelString(const char * psz)
{

   string strOnlyAlnum;

   while (*psz)
   {

      if (ansi_char_is_alphanumeric(*psz))
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


string _001CompactString(const string & str, int iSkip, int iSkipBegin = 0)
{

   string strCompact;

   strsize i = 0;

   for (; i < iSkipBegin; i++)
   {

      strCompact += str[i];

   }

   for (; i < str.get_length(); i += (iSkip + 1))
   {

      strCompact += str[i];

   }

   return strCompact;

}


void thread_name_abbreviate(string & strName, int len)
{

   if (strName.get_length() <= len)
   {

      return;

   }

   string_array stra;

   strsize iFindLast = 0;

   strsize iFind = 0;

   string strOnlyAlnum;

   while (iFind >= 0)
   {

      iFind = strName.find("::", iFindLast);

      stra.add(strName.Mid(iFindLast, iFind - iFindLast + 1));

      iFindLast = iFind + 2;

   }

   strName = stra.implode(":");

   if (strName.get_length() <= len)
   {

      return;

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumString(stra[i]);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001OnlyAlnumNonVowelString(stra[i]);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   for (index i = 0; i < stra.get_size(); i++)
   {

      stra[i] = _001CompactString(stra[i], 1, 1);

      strName = stra.implode(":");

      if (strName.get_length() <= len)
      {

         return;

      }

   }

   strName.truncate(len);

}


::e_status run_runnable(::matter * pmatter)
{

   ::e_status     estatus = error_exception;

   try
   {

      try
      {

         estatus = pmatter->operator()();

      }
      catch (...)
      {

      }

   }
   catch (...)
   {

   }

   return estatus;

}


::e_status run_routine(const ::routine & routine)
{

   ::e_status estatus = error_exception;

   try
   {

      estatus = routine();

   }
   catch (...)
   {

   }

   return estatus;

}


thread_local __pointer(task) t_ptask;


CLASS_DECL_ACME ::task * get_task()
{

   return t_ptask;

}



// CLASS_DECL_ACME ::thread * get_thread()
// {

//    return ___thread((layered *) t_ptask.m_p);

// }

CLASS_DECL_ACME void set_task(task * ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS_DEF)
{

   t_ptask.reset(ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_ARGS);

}


CLASS_DECL_ACME void thread_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   t_ptask.release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}



bool task_get_run()
{

   auto ptask = t_ptask.m_p;

   if (::is_null(ptask))
   {

      return true;

   }

   return ptask->task_get_run();

}

