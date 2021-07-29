#include "framework.h"
#include "acme/operating_system.h"


namespace parallelization
{


   //CLASS_DECL_APEX comparable_eq_array<itask_t> * s_piaThread2 = nullptr;
   //CLASS_DECL_APEX __pointer_array(thread) * s_pthreadptra2 = nullptr;
   //CLASS_DECL_APEXcritical_section * s_pcs2 = nullptr;


   CLASS_DECL_APEX void initialize()
   {

      //s_pcs2 = new critical_section();

      //s_piaThread2 = new comparable_eq_array<itask_t>;

      //s_pthreadptra2 = new __pointer_array(thread);

      __node_init_multithreading();

   }


   CLASS_DECL_APEX ::e_status finalize()
   {

      __node_term_multithreading();

      //::acme::del(s_pthreadptra2);

      //::acme::del(s_piaThread2);

      //::acme::del(s_pcs2);

      return ::success;

   }

   //CLASS_DECL_APEX bool thread_id_registered(itask_t id)
   //{

   //   //critical_section_lock lock(s_pcs2);

   //   //return s_piaThread2->contains(id);

   //   auto psystem = get_system()->m_papexsystem;

   //   return psystem->get_task(id) != nullptr;

   //}


   //bool thread_registered(::task * ptask)
   //{

   //   return psystem->get_task_id(ptask) != 0;

   //}


   //void thread_register(itask_t itask, ::task * ptask)
   //{

   //   psystem->set_task(itask, ptask);

   //}


   //void thread_unregister(itask_t itask, ::task * ptask)
   //{

   //   auto psystem = get_system()->m_papexsystem;

   //   psystem->unset_task(itask, ptask);

   //}


   //bool is_child(::task * ptaskChildCandidate)
   //{

   //   if (::is_null(ptaskChildCandidate))
   //   {

   //      return false;

   //   }

   //   if (ptaskChildCandidate->m_pobjectParent)
   //   {

   //      return true;

   //   }

   //   auto psystem = get_system()->m_papexsystem;

   //   synchronous_lock synchronouslock(&psystem->m_mutexTask);

   //   for (auto & pair : psystem->m_taskidmap)
   //   {

   //      try
   //      {

   //         auto pcompositea = ___thread(pair.element1())->_composite_array();

   //         if (pcompositea && pcompositea->contains(ptaskChildCandidate))
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


   void post_quit_to_all_threads(class ::system * psystem)
   {

      //auto psystem = get_system()->m_papexsystem;

      synchronous_lock synchronouslock(&psystem->m_mutexTask);

      for (auto& pair : psystem->m_taskidmap)
      {

         try
         {

            pair.element1()->destroy();

         }
         catch (...)
         {

         }

      }

   }


   CLASS_DECL_APEX void post_to_all_threads(::apex::system * psystem, const ::id & id, wparam wparam, lparam lparam)
   {

      synchronous_lock synchronouslock(&psystem->m_mutexTask);

      for (auto& pair : psystem->m_taskidmap)
      {

         try
         {

            __pointer(::thread) pthread = pair.element1();

            pthread->post_message(id, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }

} // namespace parallelization


//CLASS_DECL_APEX ::thread * get_thread_raw()
//{
//
//   return ::get_task();
//
//}


//bool apex_thread_get_run()
//{
//
//   try
//   {
//
//      
//
//      if(::is_null(::get_task()) || !::get_task()->is_thread()) // system threads don't have generally associated ca2 thread object
//      {
//         ////////// and have short life, so it is safe to keep it running
//         //return true;
//         return psystem->task_get_run();
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


//namespace parallelization
//{
//
//
//   //CLASS_DECL_APEX void finish()
//   //{
//
//   //   finish(::get_task());
//
//   //}
//
//
//   //CLASS_DECL_APEX bool post_quit_and_wait(const duration & duration)
//   //{
//
//   //   return post_quit_and_wait(::get_thread(), duration);
//
//   //}
//
//
//   //void finish(::task * ptask)
//   //{
//
//   //   if (::is_null(ptask))
//   //   {
//
//   //      return;
//
//   //   }
//
//   //   try
//   //   {
//
//   //      ptask->clear_finish_bit();
//
//   //   }
//   //   catch (...)
//   //   {
//
//
//   //   }
//
//   //}
//
//
//   bool post_quit_and_wait(::thread * pthreadParam, const duration & duration)
//   {
//
//      ::task_pointer pthread;
//
//      try
//      {
//
//         pthread = pthreadParam;
//
//      }
//      catch (...)
//      {
//
//         return true;
//
//      }
//
//      if (pthread.is_null())
//      {
//
//         return true;
//
//      }
//
//      try
//      {
//
//         pthread->finalize();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      try
//      {
//
//         return pthread->wait(duration).succeeded();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      return true;
//
//   }
//
//
//} // namespace parallelization
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


//::context * get_context()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if (pthread->get_context())
//   {
//
//      if (::is_null(pthread->m_pcontext->m_papexcontext->file()))
//      {
//
//         pthread->m_pcontext->m_papexcontext->initialize_context();
//
//      }
//
//      return pthread->get_context();
//
//   }
//
//   if (pthread->application())
//   {
//
//      return pthread->application();
//
//   }
//
//   return nullptr;
//
//}

//
//::application * g_papp;
//
//
//void set_global_application(::application* papp)
//{
//
//    g_papp = papp;
//
//}
//
//
//::application * get_global_application()
//{
//
//   return g_papp;
//
//}


//::application * get_application()
//{
//
//   task* ptask = get_task();
//
//   if (ptask == nullptr)
//   {
//
//      return get_global_application();
//
//   }
//
//   ::thread* pthread = ___thread(ptask);
//
//   if (pthread != nullptr)
//   {
//
//      auto papplication = pthread->get_application();
//
//      if (papplication)
//      {
//
//         return papplication;
//
//      }
//
//   }
//
//   auto pobject = ptask;
//
//   if (!pobject)
//   {
//
//      return get_global_application();
//
//   }
//
//   auto papplication = pobject->get_context();
//
//   if (!pobject)
//   {
//
//      return get_global_application();
//
//   }
//
//   return papplication;
//
//}


//::apex::session * get_session()
//{
//
//   thread * pthread = get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      return psystem->get_session();
//
//   }
//
//   return pthread->get_session();
//
//}

//::apex::system * g_papexsystem = nullptr;
//
//CLASS_DECL_APEX ::apex::system * psystem
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
//   ::apex::system * psystem = pthread->psystem;
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


namespace apex
{


   bool system::do_events()
   {

      bool bProcess = false;

      bool bProcessed = false;

      do
      {

         bool bProcess1 = false;

         try
         {

            auto ptask = ::get_task();

            if (::is_set(ptask))
            {

               bProcess1 = ptask->do_events();

            }

         }
         catch (...)
         {

         }

         bool bProcess2 = false;

         bool bProcess3 = false;

         try
         {

            auto psystem = get_system()->m_papexsystem;

            if (::is_set(psystem))
            {

               bProcess2 = psystem->do_events();

               try
               {

                  ::apex::session* psession = psystem->get_session();

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




   //CLASS_DECL_APEX ::e_status call(const ::method & method)
   //{
   //
   //   ::e_status estatus;
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
   //::e_status     run_runnable(::matter* pobjectTask)
   //{
   //
   //   ::e_status     estatus = error_exception;
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


//   void __post_quit_message(i32 nExitCode)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      ::PostQuitMessage(nExitCode);
//
//#else
//
//      ::parallelization::finish(::get_application());
//
//#endif
//
//   }




} // namespace apex





::e_status thread_ptra::destroy()
{

   try
   {

      //synchronous_lock synchronouslock(mutex());

      for (index i = 0; i < get_count(); i++)
      {

         ::thread* pthread = element_at(i);

         try
         {

            /// this is quite dangerous
            //synchronous_lock slThread(pthread->mutex());

            pthread->destroy();

         }
         catch (...)
         {

            erase(pthread);

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

   auto ptask = ::get_task();

   ::count c = 0;

   for (index i = 0; i < __pointer_array(thread)::get_count(); i++)
   {

      ::thread* pthreadItem = element_at(i);

      if (pthreadItem != ptask && pthreadItem != nullptr)
      {

         TRACE("\nthread_ptra::get_count_except_current_thread %s", typeid(*pthreadItem).name());

         c++;

      }

   }

   return c;

}


void thread_ptra::wait(const duration& duration, synchronous_lock& synchronouslock)
{

   ::datetime::time timeEnd = ::datetime::time::get_current_time() + maximum(seconds(2), duration);

   try
   {

      //      synchronous_lock synchronouslock(psyncParent);
      //
      ::count cCount = get_count_except_current_thread();

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      while (cCount > 0 && timeNow < timeEnd)
      {

         synchronouslock.unlock();

         timeNow = ::datetime::time::get_current_time();

         cCount = get_count_except_current_thread();

         sleep(500_ms);

         synchronouslock.lock();

      }

   }
   catch (...)
   {

   }

}





::task_pointer thread::calc_parent()
{

   //if (::is_null(pthread))
   //{

   //   return nullptr;

   //}

   //if (pthread == psystem)
   //{

   //   return nullptr;

   //}

   //auto pthreadContext = get_thread();

   //if (::is_set(pthreadContext))
   //{

   //   if (pthreadContext->finish_bit() || !pthreadContext->m_bLastingThread)
   //   {

   //      pthreadContext = pthreadContext->calc_parent();

   //      if (::is_set(pthreadContext))
   //      {

   //         return pthreadContext;

   //      }

   //   }
   //   else
   //   {

   //      return pthreadContext;

   //   }

   //}

   auto papplicationContext = get_application();

   if (::is_set(papplicationContext) && papplicationContext != this)
   {

      return papplicationContext;

   }

   auto psessionContext = get_session();

   if (psessionContext != this && ::is_set(psessionContext))
   {

      return psessionContext;

   }

   auto psystemContext = get_system();

   if (psystemContext != (::task*) this && ::is_set(psystemContext))
   {

      return psystemContext;

   }

   return psystemContext;

}

