#include "framework.h"
#include "aura/os/_c.h"
#include "aura/os/_.h"
#include "aura/const/id.h"


namespace multithreading
{


   //CLASS_DECL_AURA comparable_eq_array<ITHREAD> * s_piaThread2 = nullptr;
   //CLASS_DECL_AURA __pointer_array(thread) * s_pthreadptra2 = nullptr;
   //CLASS_DECL_AURA::critical_section * s_pcs2 = nullptr;


   CLASS_DECL_AURA void init_multithreading()
   {

      //s_pcs2 = new ::critical_section();

      //s_piaThread2 = new comparable_eq_array<ITHREAD>;

      //s_pthreadptra2 = new __pointer_array(thread);

      __node_init_multithreading();

   }


   CLASS_DECL_AURA void term_multithreading()
   {

      __node_term_multithreading();

      //::aura::del(s_pthreadptra2);

      //::aura::del(s_piaThread2);

      //::aura::del(s_pcs2);

   }

   CLASS_DECL_AURA bool thread_id_registered(ITHREAD id)
   {

      //cslock lock(s_pcs2);

      //return s_piaThread2->contains(id);

      return ::get_context_system()->get_thread(id) != nullptr;

   }


   bool thread_registered(::thread * pthread)
   {

      return ::get_context_system()->get_thread_id(pthread) != 0;

   }


   void thread_register(ITHREAD ithread, ::thread * pthread)
   {

      //cslock lock(s_pcs2);

      //if (s_pthreadptra2->contains(pthread))
      //{

      //   __throw(invalid_argument_exception());

      //}

      //if(id == 0)
      //{

      //   TRACE("WHAT?!?!?");

      //}

      //if (s_piaThread2->contains(id))
      //{

      //   __throw(invalid_argument_exception());

      //}

      //pthread->set_os_int(id);

      //s_pthreadptra2->add(pthread);

      //s_piaThread2->add(id);

      ::get_context_system()->set_thread(ithread, pthread);

   }


   void thread_unregister(ITHREAD ithread, ::thread * pthread)
   {

      //cslock lock(s_pcs2);

      //if (!s_pthreadptra2->contains(pthread))
      //{

      //   __throw(invalid_argument_exception());

      //}

      //auto id = pthread->get_os_int();

      //if (!s_piaThread2->contains(id))
      //{

      //   __throw(invalid_argument_exception());

      //}

      //s_pthreadptra2->remove(pthread);

      //s_piaThread2->remove(id);

      ::get_context_system()->unset_thread(ithread, pthread);

   }


   bool is_child(::thread * pthreadChildCandidate)
   {

      if (::is_null(pthreadChildCandidate))
      {

         return false;

      }

      if (pthreadChildCandidate->m_pthreadParent)
      {

         return true;

      }

      sync_lock sl(&::get_context_system()->m_mutexThread);

      for (auto & pair : ::get_context_system()->m_threadidmap)
      {

         try
         {

            if (pair.element1()->m_threada.contains(pthreadChildCandidate))
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

      sync_lock sl(&::get_context_system()->m_mutexThread);

      for (auto& pair : ::get_context_system()->m_threadidmap)
      {

         try
         {

            pair.element1()->finalize();

         }
         catch (...)
         {

         }

      }

   }


   CLASS_DECL_AURA void post_to_all_threads(UINT message, WPARAM wparam, LPARAM lparam)
   {

      sync_lock sl(&::get_context_system()->m_mutexThread);

      for (auto& pair : ::get_context_system()->m_threadidmap)
      {

         try
         {

            pair.element1()->post_message(message, wparam, lparam);

         }
         catch (...)
         {

         }

      }

   }

   //CLASS_DECL_AURA bool __wait_threading_count(::duration duration)
   //{

   //   tick tickStart = ::tick::now();

   //   tick tickDelay = duration.total_milliseconds();

   //   single_lock sl(::multithreading::s_pmutex);

   //   while (tickStart.elapsed() < tickDelay)
   //   {

   //      sl.lock();

   //      if (::multithreading::s_pthreadptra->get_count() <= 0)
   //      {

   //         return true;

   //      }

   //      for (index i = 0; i < ::multithreading::s_pthreadptra->get_count(); i++)
   //      {

   //         try
   //         {

   //            ::multithreading::s_pthreadptra->element_at(i)->finalize();

   //         }
   //         catch (...)
   //         {

   //         }

   //      }

   //      sl.unlock();

   //      Sleep(100);

   //   }

   //   return false;

   //}



   CLASS_DECL_AURA __pointer(::thread) calc_parent(::thread * pthread)
   {

      if (::is_null(pthread))
      {

         return nullptr;

      }

      if (pthread == ::get_context_system())
      {

         return nullptr;

      }

      auto pthreadContext = pthread->get_context_thread();

      if (::is_set(pthreadContext))
      {

         if (pthreadContext->is_set_finish() || !pthreadContext->m_bLastingThread)
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

      auto psystemContext = pthread->get_context_system();

      if (psystemContext != pthread && ::is_set(psystemContext))
      {

         return psystemContext;

      }

      return ::get_context_system();

   }


//   CLASS_DECL_AURA bool wait_threads(::duration duration, __pointer_array(::thread) threadaExcept)
//   {
//
//      tick tickStart = ::tick::now();
//
//      tick tickDelay = duration.total_milliseconds();
//
//      __pointer_array(::thread) threada;
//
//      bool bFound;
//
//      while (tickStart.elapsed() < tickDelay)
//      {
//
//         bFound = false;
//
//         {
//
//            cslock lock(s_pcs2);
//
//            for (auto & pthread : *s_pthreadptra2)
//            {
//
//               if (!threadaExcept.contains(pthread))
//               {
//
//                  bFound = true;
//
//                  break;
//
//               }
//
//            }
//
//         }
//
//         if (!bFound)
//         {
//
//            return true;
//
//         }
//
//         for (auto & pthread : threada)
//         {
//
//            try
//            {
//
//               pthread->finalize();
//
//            }
//            catch (...)
//            {
//
//            }
//
//         }
//
//         Sleep(100);
//
//      }
//
//      return false;
//
//   }


} // namespace multithreading


//cflag < e_thread_flag > & thread_flags()
//{
//
//   if (t_pflags == nullptr)
//   {
//
//      t_pflags = new u64;
//
//      *t_pflags = 0ULL;
//
//   }
//
//   return (cflag < e_thread_flag > &) *t_pflags;
//
//}


//CLASS_DECL_AURA void thread_set_flag(const cflag < e_thread_flag > & eflag, bool bSet)
//{
//
//   auto & u = thread_flags();
//
//   if (bSet)
//   {
//
//      u.add(eflag);
//
//   }
//   else
//   {
//
//      u.remove(eflag);
//
//   }
//
//}

//CLASS_DECL_AURA bool thread_get_flag(e_thread_flag eflag)
//{
//
//   if(t_pflags == nullptr)
//   {
//
//      return false;
//
//   }
//
//   return (thread_flags() & eflag) != 0ULL;
//
//}


//CLASS_DECL_AURA void thread_set_fast_path(bool bFastPath)
//{
//
//   thread_set_flag(thread_flag_fast_path, bFastPath);
//
//}
//
//
//CLASS_DECL_AURA bool thread_is_fast_path()
//{
//
//   return thread_get_flag(thread_flag_fast_path);
//
//}


//CLASS_DECL_AURA void thread_set_zip_is_dir(bool bZipIsDir)
//{
//
//   thread_set_flag(thread_flag_zip_is_dir, bZipIsDir);
//
//}
//
//
//CLASS_DECL_AURA bool thread_set(id_thread_zip_is_dir)
//{
//
//   return thread_get_flag(thread_flag_zip_is_dir);
//
//}


//CLASS_DECL_AURA void thread_set_is_timer(bool bIsTimer)
//{
//
//   thread_set_flag(thread_flag_is_timer, bIsTimer);
//
//}
//
//
//CLASS_DECL_AURA bool thread_is_timer()
//{
//
//   return thread_get_flag(thread_flag_is_timer);
//
//}
//
//
//CLASS_DECL_AURA void thread_set_resolve_alias(bool bResolveAlias)
//{
//
//   thread_set_flag(thread_flag_resolve_alias, bResolveAlias);
//
//}
//
//
//CLASS_DECL_AURA bool thread_resolve_alias()
//{
//
//   return thread_get_flag(thread_flag_resolve_alias);
//
//}


//thread_pointer ::get_thread();

//::thread * get_thread(const ::set & setCreateThread)
//{
//
//   ::thread * pthread = ::get_thread();
//
//   if (pthread == nullptr)
//   {
//
//      //if (__optional_is_true(setCreateThread, !thread_get_flag(thread_flag_prevent_create_thread)))
//      //{
//
//      //   __keep(thread_flag_prevent_create_thread);
//
//      //   //sleep(10_s);
//
//      //   //thread_
//
//      //   pthread = new thread();
//
//      //   pthread->initialize(::get_context_system());
//
//      //   ::get_thread() = pthread;
//
//      //}
//
//   }
//
//   return pthread;
//
//}


CLASS_DECL_AURA ::thread * get_thread_raw()
{

   return ::get_thread();

}

bool thread_get_run()
{

   try
   {

      if(::is_null(::get_thread()) || !::get_thread()->is_thread()) // system threads don't have generally associated ca2 thread object
      {
         ////////// and have short life, so it is safe to keep it running
         //return true;
         return ::get_context_system()->thread_get_run();

      }

      return ::get_thread()->thread_get_run();

   }
   catch (...)
   {

   }

   return false;

}


//void defer_run_thread()
//{
//
//   if (!thread_get_run())
//   {
//
//      __throw(exit_exception(::get_thread()));
//
//   }
//
//}



namespace multithreading
{


   CLASS_DECL_AURA void set_finish()
   {

      set_finish(::get_thread());

   }


   CLASS_DECL_AURA bool post_quit_and_wait(const duration & duration)
   {

      return post_quit_and_wait(::get_thread(), duration);

   }



   void set_finish(::thread * pthread)
   {

      if (pthread == nullptr)
      {

         return;

      }

      try
      {

         pthread->finalize();

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








//__pointer(thread) begin_thread(
//::object * pobject,
//thread_procedure procedure,
//thread_parameter parameter,
//e_priority epriority,
//UINT nStackSize,
//u32 dwCreateFlags,
//LPSECURITY_ATTRIBUTES pSecurityAttrs,

//ITHREAD * puiId,
//::status::result * presult)
//{
//
//   ASSERT(procedure != nullptr);
//
//   auto pthread = __new(thread(pobject, procedure, parameter));
//
//   ASSERT_VALID(pthread);
//
//   if(!pthread->simplecreate_thread(epriority, nStackSize, dwCreateFlags, pSecurityAttrs, puiId, presult))

//   {
//
//      return nullptr;
//
//   }
//
//   return pthread;
//
//}







//::mutex & user_mutex()
//{
//
//   //static ::mutex * s_pmutexUser = new ::mutex();
//
//   //return *s_pmutexUser;
//   return *((::mutex *)nullptr);
//
//}

::mutex * s_pmutexMessageDispatch = nullptr;

::mutex & message_dispatch_mutex()
{


   return *s_pmutexMessageDispatch;

}



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


::aura::application * g_papp;


void set_global_application(::aura::application* papp)
{

    g_papp = papp;

}


::aura::application * get_global_application()
{

   return g_papp;

}


::aura::application * get_context_application()
{

   thread * pthread = get_thread();

   if (pthread == nullptr)
   {

      return get_global_application();

   }

   return pthread->get_context_application();

}


::aura::session * get_context_session()
{

   thread * pthread = get_thread();

   if (pthread == nullptr)
   {

      return nullptr;

   }

   return pthread->get_context_session();

}


::aura::system * get_context_system()
{

   thread * pthread = get_thread();

   if (pthread == nullptr)
   {

      return ::get_context_system();

   }

   return pthread->get_context_system();

}


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

         ::aura::system* psystem = ::get_context_system();

         if (::is_set(psystem))
         {

            bProcess2 = psystem->do_events();

            try
            {

               ::aura::session* psession = psystem->get_context_session();

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
//   ::thread * pthread = ::get_thread();
//
//   if(pthread == nullptr)
//      return;
//
//   pthread->do_events(duration);
//
//}



void thread_ptra::set_finish()
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

            pthread->finalize();

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

   ::datetime::time timeEnd = ::datetime::time::get_current_time() + MAX(seconds(2), duration);

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


CLASS_DECL_AURA ::estatus call(::object * pobject)
{

   ::estatus estatus;

   try
   {

      estatus = pobject->call();

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







::estatus     run_runnable(::generic_object* pobjectTask)
{

   ::estatus     estatus = error_exception;

   try
   {

      __pointer(generic_object) pobject(e_move_transfer, pobjectTask);

      try
      {

         estatus = pobject->call();

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
