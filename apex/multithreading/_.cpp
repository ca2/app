#include "framework.h"
#include "apex/os/_c.h"
#include "apex/os/_.h"
#include "apex/const/id.h"


namespace multithreading
{


   //CLASS_DECL_APEX comparable_eq_array<ITHREAD> * s_piaThread2 = nullptr;
   //CLASS_DECL_APEX __pointer_array(thread) * s_pthreadptra2 = nullptr;
   //CLASS_DECL_APEX::critical_section * s_pcs2 = nullptr;


   CLASS_DECL_APEX void init_multithreading()
   {

      //s_pcs2 = new ::critical_section();

      //s_piaThread2 = new comparable_eq_array<ITHREAD>;

      //s_pthreadptra2 = new __pointer_array(thread);

      __node_init_multithreading();

   }


   CLASS_DECL_APEX void term_multithreading()
   {

      __node_term_multithreading();

      //::acme::del(s_pthreadptra2);

      //::acme::del(s_piaThread2);

      //::acme::del(s_pcs2);

   }

   CLASS_DECL_APEX bool thread_id_registered(ITHREAD id)
   {

      //cslock lock(s_pcs2);

      //return s_piaThread2->contains(id);

      return System.get_task(id) != nullptr;

   }


   bool thread_registered(::task * ptask)
   {

      return System.get_task_id(ptask) != 0;

   }


   void thread_register(ITHREAD ithread, ::task * ptask)
   {

      System.set_task(ithread, ptask);

   }


   void thread_unregister(ITHREAD ithread, ::task * ptask)
   {

      auto psystem = ::get_context_system();

      psystem->unset_task(ithread, ptask);

   }


   bool is_child(::task * ptaskChildCandidate)
   {

      if (::is_null(ptaskChildCandidate))
      {

         return false;

      }

      if (ptaskChildCandidate->m_pobjectParent)
      {

         return true;

      }

      sync_lock sl(&System.m_mutexTask);

      for (auto & pair : System.m_taskidmap)
      {

         try
         {

            auto pcompositea = ___thread(pair.element1())->_composite_array();

            if (pcompositea && pcompositea->contains(ptaskChildCandidate))
            {

               return true;

            }

         }
         catch (...)
         {

         }

      }

      return false;

   }


   void post_quit_to_all_threads()
   {

      sync_lock sl(&System.m_mutexTask);

      for (auto& pair : System.m_taskidmap)
      {

         try
         {

            ___thread(pair.element1())->finish(get_context_system());

         }
         catch (...)
         {

         }

      }

   }


   CLASS_DECL_APEX void post_to_all_threads(const ::id & id, WPARAM wparam, LPARAM lparam)
   {

      sync_lock sl(&System.m_mutexTask);

      for (auto& pair : System.m_taskidmap)
      {

         try
         {

            auto pthread = ___thread(pair.element1());

            pthread->post_message(id, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }


   CLASS_DECL_APEX __pointer(::thread) calc_parent(::thread * pthread)
   {

      if (::is_null(pthread))
      {

         return nullptr;

      }

      if (pthread == &System)
      {

         return nullptr;

      }

      auto pthreadContext = pthread->get_context_thread();

      if (::is_set(pthreadContext))
      {

         if (pthreadContext->finish_bit() || !pthreadContext->m_bLastingThread)
         {

            pthreadContext = calc_parent(pthreadContext);

            if (::is_set(pthreadContext))
            {

               return pthreadContext;

            }

         }
         else
         {

            return pthreadContext;

         }

      }

      auto papplicationContext = pthread->get_context_application();

      if (::is_set(papplicationContext) && papplicationContext != pthread)
      {

         return papplicationContext;

      }

      auto psessionContext = pthread->get_context_session();

      if (psessionContext != pthread && ::is_set(psessionContext))
      {

         return psessionContext;

      }

      auto psystemContext = &System;

      if (psystemContext != pthread && ::is_set(psystemContext))
      {

         return psystemContext;

      }

      return ::get_context_system();

   }


} // namespace multithreading


//CLASS_DECL_APEX ::thread * get_thread_raw()
//{
//
//   return ::get_task();
//
//}


bool apex_thread_get_run()
{

   try
   {

      if(::is_null(::get_task()) || !::get_task()->is_thread()) // system threads don't have generally associated ca2 thread object
      {
         ////////// and have short life, so it is safe to keep it running
         //return true;
         return System.thread_get_run();

      }

      return ::get_task()->thread_get_run();

   }
   catch (...)
   {

   }

   return false;

}


namespace multithreading
{


   CLASS_DECL_APEX void finish()
   {

      finish(::get_task());

   }


   CLASS_DECL_APEX bool post_quit_and_wait(const duration & duration)
   {

      return post_quit_and_wait(::get_thread(), duration);

   }


   void finish(::task * ptask)
   {

      if (::is_null(ptask))
      {

         return;

      }

      try
      {

         ptask->clear_finish_bit();

      }
      catch (...)
      {


      }

   }


   bool post_quit_and_wait(::thread * pthreadParam, const duration & duration)
   {

      __pointer(::thread) pthread;

      try
      {

         pthread = pthreadParam;

      }
      catch (...)
      {

         return true;

      }

      if (pthread.is_null())
      {

         return true;

      }

      try
      {

         pthread->finalize();

      }
      catch (...)
      {

      }

      try
      {

         return pthread->wait(duration).succeeded();

      }
      catch (...)
      {

      }

      return true;

   }


} // namespace multithreading
//
//
//::mutex * s_pmutexMessageDispatch = nullptr;
//
//
//::mutex & message_dispatch_mutex()
//{
//
//
//   return *s_pmutexMessageDispatch;
//
//}


::context * get_context()
{

   thread * pthread = get_thread();

   if (pthread == nullptr)
   {

      return nullptr;

   }

   if (pthread->get_context())
   {

      if (::is_null_ref(pthread->get_context()->file()))
      {

         pthread->get_context()->initialize_context();

      }

      return pthread->get_context();

   }

   if (pthread->get_context_application())
   {

      return pthread->get_context_application();

   }

   return nullptr;

}


::apex::application * g_papp;


void set_global_application(::apex::application* papp)
{

    g_papp = papp;

}


::apex::application * get_global_application()
{

   return g_papp;

}


::apex::application * get_context_application()
{

   task* ptask = get_task();

   if (ptask == nullptr)
   {

      return get_global_application();

   }

   ::thread* pthread = ___thread(ptask);

   if (pthread != nullptr)
   {

      auto papp = pthread->get_context_application();

      if (papp)
      {

         return papp;

      }

   }

   auto pobject = ptask->get_context_object();

   if (!pobject)
   {

      return get_global_application();

   }

   auto papp = pobject->get_context_application();

   if (!pobject)
   {

      return get_global_application();

   }

   return papp;

}


::apex::session * get_context_session()
{

   thread * pthread = get_thread();

   if (pthread == nullptr)
   {

      return nullptr;

   }

   return pthread->get_context_session();

}

//::apex::system * g_papexsystem = nullptr;
//
//CLASS_DECL_APEX ::apex::system * get_context_system()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return g_papexsystem;
//
//   }
//
//   ::apex::system * psystem = pthread->get_context_system();
//
//   if (!psystem)
//   {
//
//      psystem = g_papexsystem;
//
//   }
//
//   return psystem;
//
//}


bool do_events()
{

   bool bProcess = false;

   bool bProcessed = false;

   do
   {

      bool bProcess1 = false;

      try
      {

         ::thread* pthread = ::get_thread();

         if (::is_set(pthread))
         {

            bProcess1 = pthread->do_events();

         }

      }
      catch (...)
      {

      }

      bool bProcess2 = false;

      bool bProcess3 = false;

      try
      {

         auto psystem = &System;

         if (::is_set(psystem))
         {

            bProcess2 = psystem->do_events();

            try
            {

               ::apex::session* psession = psystem->get_context_session();

               if (::is_set(psession))
               {

                  bProcess3 = psystem->do_events();

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      bool bProcess = bProcess1 || bProcess2 || bProcess3;

      if (bProcess)
      {

         bProcessed = bProcess;

      }

   } while (bProcess);

   return bProcessed;

}


//bool do_events(const duration & duration)
//{
//
//   ::thread * pthread = ::get_task();
//
//   if(pthread == nullptr)
//      return;
//
//   pthread->do_events(duration);
//
//}



::estatus thread_ptra::finish(::context_object * pcontextobjectFinish)
{

   try
   {

      //sync_lock sl(mutex());

      for (index i = 0; i < get_count(); i++)
      {

         ::thread * pthread = element_at(i);

         try
         {

            /// this is quite dangerous
            //sync_lock slThread(pthread->mutex());

            pthread->finish(pcontextobjectFinish);

         }
         catch (...)
         {

            remove(pthread);

            break;

         }

      }

   }
   catch (...)
   {

   }


   return ::success;

}


::count thread_ptra::get_count_except_current_thread()
{

   thread * pthread = ::get_thread();

   ::count c = 0;

   for(index i = 0; i < __pointer_array(thread)::get_count(); i++)
   {

      ::thread * pthreadItem = element_at(i);

      if(pthreadItem != pthread && pthreadItem != nullptr)
      {

         TRACE("\nthread_ptra::get_count_except_current_thread %s", typeid(*pthreadItem).name());

         c++;

      }

   }

   return c;

}


void thread_ptra::wait(const duration & duration, sync_lock & sl)
{

   ::datetime::time timeEnd = ::datetime::time::get_current_time() + max(seconds(2), duration);

   try
   {

//      sync_lock sl(psyncParent);
//
      ::count cCount = get_count_except_current_thread();

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      while (cCount > 0 &&  timeNow < timeEnd)
      {

         sl.unlock();

         timeNow = ::datetime::time::get_current_time();

         cCount = get_count_except_current_thread();

         Sleep(500);

         sl.lock();

      }

   }
   catch (...)
   {

   }

}


//CLASS_DECL_APEX ::estatus call(const ::method & method)
//{
//
//   ::estatus estatus;
//
//   try
//   {
//
//      estatus = method();
//
//   }
//   catch (...)
//   {
//
//      estatus = ::error_exception;
//
//   }
//
//   return estatus;
//
//}
//
//
//bool isvowel_dup(int i)
//{
//
//   if (i == 'a')
//   {
//      return true;
//   }
//   else if (i == 'e')
//   {
//      return true;
//   }
//   else if (i == 'i')
//   {
//      return true;
//   }
//   else if (i == 'o')
//   {
//      return true;
//   }
//   else if (i == 'u')
//   {
//      return true;
//   }
//   if (i == 'A')
//   {
//      return true;
//   }
//   else if (i == 'E')
//   {
//      return true;
//   }
//   else if (i == 'I')
//   {
//      return true;
//   }
//   else if (i == 'O')
//   {
//      return true;
//   }
//   else if (i == 'U')
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//
//}

//
//string _001OnlyAlnumString(const char * psz)
//{
//
//   string strOnlyAlnum;
//
//   while (*psz)
//   {
//
//      if (ansi_char_is_alphanumeric(*psz))
//      {
//
//         strOnlyAlnum += *psz;
//
//      }
//
//      psz++;
//
//   }
//
//   return strOnlyAlnum;
//
//}

//
//string _001OnlyAlnumNonVowelString(const char * psz)
//{
//
//   string strOnlyAlnum;
//
//   while (*psz)
//   {
//
//      if (ansi_char_is_alphanumeric(*psz))
//      {
//
//         if (!isvowel_dup(*psz))
//         {
//
//            strOnlyAlnum += *psz;
//
//         }
//
//      }
//
//      psz++;
//
//   }
//
//   return strOnlyAlnum;
//
//}

//
//string _001CompactString(const string & str, int iSkip, int iSkipBegin = 0)
//{
//
//   string strCompact;
//
//   strsize i = 0;
//
//   for (; i < iSkipBegin; i++)
//   {
//
//      strCompact += str[i];
//
//   }
//
//   for (; i < str.get_length(); i += (iSkip + 1))
//   {
//
//      strCompact += str[i];
//
//   }
//
//   return strCompact;
//
//}


//void thread_name_abbreviate(string & strName, int len)
//{
//
//   if (strName.get_length() <= len)
//   {
//
//      return;
//
//   }
//
//   string_array stra;
//
//   strsize iFindLast = 0;
//
//   strsize iFind = 0;
//
//   string strOnlyAlnum;
//
//   while (iFind >= 0)
//   {
//
//      iFind = strName.find("::", iFindLast);
//
//      stra.add(strName.Mid(iFindLast, iFind - iFindLast + 1));
//
//      iFindLast = iFind + 2;
//
//   }
//
//   strName = stra.implode(":");
//
//   if (strName.get_length() <= len)
//   {
//
//      return;
//
//   }
//
//   for (index i = 0; i < stra.get_size(); i++)
//   {
//
//      stra[i] = _001OnlyAlnumString(stra[i]);
//
//      strName = stra.implode(":");
//
//      if (strName.get_length() <= len)
//      {
//
//         return;
//
//      }
//
//   }
//
//   for (index i = 0; i < stra.get_size(); i++)
//   {
//
//      stra[i] = _001OnlyAlnumNonVowelString(stra[i]);
//
//      strName = stra.implode(":");
//
//      if (strName.get_length() <= len)
//      {
//
//         return;
//
//      }
//
//   }
//
//   for (index i = 0; i < stra.get_size(); i++)
//   {
//
//      stra[i] = _001CompactString(stra[i], 1, 1);
//
//      strName = stra.implode(":");
//
//      if (strName.get_length() <= len)
//      {
//
//         return;
//
//      }
//
//   }
//
//   strName.truncate(len);
//
//}
//
//
//
//

//
//
//::estatus     run_runnable(::matter* pobjectTask)
//{
//
//   ::estatus     estatus = error_exception;
//
//   try
//   {
//
//      __pointer(matter) pobject(e_move_transfer, pobjectTask);
//
//      try
//      {
//
//         estatus = pobject->call();
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return estatus;
//
//}







void __post_quit_message(i32 nExitCode)
{

#ifdef WINDOWS_DESKTOP

   ::PostQuitMessage(nExitCode);

#else

   ::multithreading::finish(::get_context_application());

#endif

}
