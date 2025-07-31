#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/application.h"
#include "apex/platform/system.h"
#include "apex/platform/session.h"


//#include "acme/_operating_system.h"


//void __node_init_multitasking();
//void __node_term_multitasking();


namespace parallelization
{


   //CLASS_DECL_APEX comparable_eq_array<itask> * s_piaThread2 = nullptr;
   //CLASS_DECL_APEX pointer_array < thread > * s_pthreadptra2 = nullptr;
   //CLASS_DECL_APEXcritical_section * s_pcs2 = nullptr;


   CLASS_DECL_APEX void initialize()
   {

      //s_pcs2 = ___new critical_section();

      //s_piaThread2 = aaa_memory_new comparable_eq_array<itask>;

      //s_pthreadptra2 = aaa_memory_new pointer_array < thread >;

      //__node_init_multitasking();

   }


   CLASS_DECL_APEX void destroy()
   {

      //__node_term_multitasking();

      //::acme::del(s_pthreadptra2);

      //::acme::del(s_piaThread2);

      //::acme::del(s_pcs2);

      //return ::success;

   }

   //CLASS_DECL_APEX bool thread_id_registered(itask atom)
   //{

   //   //critical_section_lock lock(s_pcs2);

   //   //return s_piaThread2->contains(atom);

   //   auto psystem = system();

   //   return psystem->get_task(atom) != nullptr;

   //}


   //bool thread_registered(::task * ptask)
   //{

   //   return psystem->get_task_id(ptask) != 0;

   //}


   //void thread_register(itask itask, ::task * ptask)
   //{

   //   psystem->set_task(itask, ptask);

   //}


   //void thread_unregister(itask itask, ::task * ptask)
   //{

   //   auto psystem = system();

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

   //   auto psystem = system();

   //   synchronous_lock synchronouslock(&psystem->m_pmutexTask);

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


   void post_quit_to_all_threads()
   {

      critical_section_lock criticalsectionlock(&::system()->m_criticalsectionThreadStorage);

      for (auto& pair : ::system()->m_mapThreadStorage)
      {

         try
         {

            pair.element2().m_ptask->set_finish();

         }
         catch (...)
         {

         }

      }

   }


   CLASS_DECL_APEX void post_to_all_threads(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      critical_section_lock criticalsectionlock(&::system()->m_criticalsectionThreadStorage);

      for (auto& pair : ::system()->m_mapThreadStorage)
      {

         try
         {

            ::pointer<::thread>pthread = pair.element2().m_ptask;

            pthread->post_message(emessage, wparam, lparam);

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
//   //CLASS_DECL_APEX bool post_quit_and_wait(const class time & time)
//   //{
//
//   //   return post_quit_and_wait(::get_thread(), time);
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
//   bool post_quit_and_wait(::thread * pthreadParam, const class time & time)
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
//         pthread->destroy();
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
//         return pthread->wait(time).succeeded();
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
//::pointer< ::mutex > s_pmutexMessageDispatch = nullptr;
//
//
//::pointer < ::mutex > & message_dispatch_mutex()
//{
//
//
//   return *s_pmutexMessageDispatch;
//
//}


//::handler_context * get_context()
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
//      if (::is_null(pthread->m_papplication->file()))
//      {
//
//         pthread->m_papplication->initialize_context();
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
//void set_global_application(::apex::application* papp)
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


//::application * get_app()
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
//      auto papp = pthread->get_app();
//
//      if (papp)
//      {
//
//         return papp;
//
//      }
//
//   }
//
//   auto pparticle = ptask;
//
//   if (!pparticle)
//   {
//
//      return get_global_application();
//
//   }
//
//   auto papp = pparticle->get_context();
//
//   if (!pparticle)
//   {
//
//      return get_global_application();
//
//   }
//
//   return papp;
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


   //bool system::do_tasks()
   //{

   //   bool bProcess = false;

   //   bool bProcessed = false;

   //   do
   //   {

   //      bool bProcess1 = false;

   //      try
   //      {

   //         auto ptask = ::get_task();

   //         if (::is_set(ptask))
   //         {

   //            if (ptask == this)
   //            {

   //               ::platform::system::do_tasks();

   //            }
   //            else
   //            {

   //               bProcess1 = ptask->do_tasks();

   //            }

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //      bool bProcess2 = false;

   //      bool bProcess3 = false;

   //      try
   //      {

   //         auto psystem = this;

   //         if (::is_set(psystem) && psystem != this)
   //         {

   //            bProcess2 = psystem->do_tasks();

   //            try
   //            {

   //               auto psession = session();

   //               if (::is_set(psession))
   //               {

   //                  bProcess3 = psystem->do_tasks();

   //               }

   //            }
   //            catch (...)
   //            {

   //            }

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //      bool bProcess = bProcess1 || bProcess2 || bProcess3;

   //      if (bProcess)
   //      {

   //         bProcessed = bProcess;

   //      }

   //   } while (bProcess);

   //   return bProcessed;

   //}


   //bool do_tasks(const class time & time)
   //{
   //
   //   ::thread * pthread = ::get_task();
   //
   //   if(pthread == nullptr)
   //      return;
   //
   //   pthread->do_tasks(time);
   //
   //}




   //CLASS_DECL_APEX void call(const ::method & method)
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
   //string _001OnlyAlnumString(const ::scoped_string & scopedstr)
   //{
   //
   //   string strOnlyAlnum;
   //
   //   while (*psz)
   //   {
   //
   //      if (character_isalnum(*psz))
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
   //string _001OnlyAlnumNonVowelString(const ::scoped_string & scopedstr)
   //{
   //
   //   string strOnlyAlnum;
   //
   //   while (*psz)
   //   {
   //
   //      if (character_isalnum(*psz))
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
   //string _001CompactString(const ::scoped_string & scopedstr, int iSkip, int iSkipBegin = 0)
   //{
   //
   //   string strCompact;
   //
   //   character_count i = 0;
   //
   //   for (; i < iSkipBegin; i++)
   //   {
   //
   //      strCompact += str[i];
   //
   //   }
   //
   //   for (; i < str.length(); i += (iSkip + 1))
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
   //   if (strName.length() <= len)
   //   {
   //
   //      return;
   //
   //   }
   //
   //   string_array stra;
   //
   //   character_count iFindLast = 0;
   //
   //   auto pFind = 0;
   //
   //   string strOnlyAlnum;
   //
   //   while (::is_set(pFind))
   //   {
   //
   //      iFind = strName.find("::", iFindLast);
   //
   //      stra.add(strName.substr(iFindLast, iFind - iFindLast + 1));
   //
   //      iFindLast = iFind + 2;
   //
   //   }
   //
   //   strName = stra.implode(":");
   //
   //   if (strName.length() <= len)
   //   {
   //
   //      return;
   //
   //   }
   //
   //   for (::collection::index i = 0; i < stra.get_size(); i++)
   //   {
   //
   //      stra[i] = _001OnlyAlnumString(stra[i]);
   //
   //      strName = stra.implode(":");
   //
   //      if (strName.length() <= len)
   //      {
   //
   //         return;
   //
   //      }
   //
   //   }
   //
   //   for (::collection::index i = 0; i < stra.get_size(); i++)
   //   {
   //
   //      stra[i] = _001OnlyAlnumNonVowelString(stra[i]);
   //
   //      strName = stra.implode(":");
   //
   //      if (strName.length() <= len)
   //      {
   //
   //         return;
   //
   //      }
   //
   //   }
   //
   //   for (::collection::index i = 0; i < stra.get_size(); i++)
   //   {
   //
   //      stra[i] = _001CompactString(stra[i], 1, 1);
   //
   //      strName = stra.implode(":");
   //
   //      if (strName.length() <= len)
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
   //void     run_runnable(::matter* pobjectTask)
   //{
   //
   //   void     estatus = error_exception;
   //
   //   try
   //   {
   //
   //      ::pointer<matter>pparticle(e_pointer_transfer, pobjectTask);
   //
   //      try
   //      {
   //
   //         estatus = pparticle->call();
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


//   void __post_quit_message(int nExitCode)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      ::PostQuitMessage(nExitCode);
//
//#else
//
//      ::parallelization::finish(::get_app());
//
//#endif
//
//   }




} // namespace apex





void thread_ptra::destroy()
{

   try
   {

      //synchronous_lock synchronouslock(this->synchronization());

      for (::collection::index i = 0; i < get_count(); i++)
      {

         ::thread* pthread = element_at(i);

         try
         {

            /// this is quite dangerous
            //synchronous_lock slThread(pthread->synchronization());

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


   //return ::success;

}


::collection::count thread_ptra::get_count_except_current_thread()
{

   auto ptask = ::get_task();

   ::collection::count c = 0;

   for (::collection::index i = 0; i < pointer_array < thread >::get_count(); i++)
   {

      ::thread* pthreadItem = element_at(i);

      if (pthreadItem != ptask && pthreadItem != nullptr)
      {

         informationf("thread_ptra::get_count_except_current_thread \"%s\"", ::type(pthreadItem).name().c_str());

         c++;

      }

   }

   return c;

}


void thread_ptra::wait(const class time & timeWait, ::particle & particleSynchronization)
{

   auto timeStart = ::time::now();

   try
   {

      //      synchronous_lock synchronouslock(psyncParent);
      //
      ::collection::count cCount = get_count_except_current_thread();

      while (cCount > 0 && timeStart.elapsed() < timeWait)
      {

         particleSynchronization.unlock();

         cCount = get_count_except_current_thread();

         preempt(500_ms);

         particleSynchronization.lock();

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

   auto papplication = application();

   if (::is_set(papplication))
   {

      auto pthreadApplication = dynamic_cast < ::thread * >(papplication);

      if(::is_set(pthreadApplication))
      {

         return pthreadApplication;

      }

   }

   auto psession = session();

   if (::is_set(psession))
   {

      auto pthreadSession = dynamic_cast < ::thread * >(psession);

      if(::is_set(pthreadSession))
      {

         return pthreadSession;

      }

   }

   auto psystem = system();

   if (::is_set(psystem))
   {

      auto pthreadSystem = dynamic_cast < ::thread * >(psystem);

      if(::is_set(pthreadSystem))
      {

         return pthreadSystem;

      }

   }

   return nullptr;

}





