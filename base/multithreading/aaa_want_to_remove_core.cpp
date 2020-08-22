#include "framework.h"


//::mutex * g_pmutexThreading = nullptr;
//
//int g_iThreadingCount = 0;
//
//
//CLASS_DECL_AURA void __init_threading_count()
//{
//
//   g_pmutexThreading = new ::mutex();
//
//   g_iThreadingCount = 0;
//
//}
//
//
//CLASS_DECL_AURA void __term_threading_count()
//{
//
//   delete g_pmutexThreading;
//
//   g_pmutexThreading = nullptr;
//
//}
//
//
//CLASS_DECL_AURA void __inc_threading_count()
//{
//
//   single_lock sl(g_pmutexThreading,false);
//
//   g_iThreadingCount++;
//
//}
//
//
//CLASS_DECL_AURA void __dec_threading_count()
//{
//
//   single_lock sl(g_pmutexThreading,false);
//
//   g_iThreadingCount--;
//
//}


//CLASS_DECL_AURA bool __wait_threading_count(::duration duration)
//{
//
//   tick tickStart = ::tick::now();
//
//   tick tickDelay = duration.total_milliseconds();
//
//   single_lock sl(::multithreading::s_pmutex);
//
//   while(tickStart.elapsed() < tickDelay)
//   {
//
//      sl.lock();
//
//      if (::multithreading::s_pthreadptra->get_count() <= 0)
//      {
//
//         return true;
//
//      }
//
//      for(index i = 0; i < ::multithreading::s_pthreadptra->get_count(); i++)
//      {
//
//         try
//         {
//
//            ::multithreading::s_pthreadptra->element_at(i)->finalize();
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      sl.unlock();
//
//      Sleep(100);
//
//   }
//
//   return false;
//
//}
//
//
//CLASS_DECL_AURA bool __wait_threading_count_except(::thread * pthread, ::duration duration)
//{
//
//   tick tickStart = ::tick::now();
//
//   tick tickDelay = duration.total_milliseconds();
//
//   single_lock sl(::multithreading::s_pmutex);
//
//   while (tickStart.elapsed() < tickDelay)
//   {
//
//      sl.lock();
//
//      if(::multithreading::s_pthreadptra->get_count() <= 0)
//      {
//
//         return true;
//
//      }
//
//      if(::multithreading::s_pthreadptra->get_count() == 1)
//      {
//
//         ::thread * pthreadOne = ::multithreading::s_pthreadptra->element_at(0);
//
//         if (pthreadOne == pthread)
//         {
//
//            return true;
//
//         }
//
//      }
//
//      for(index i = 0; i < ::multithreading::s_pthreadptra->get_count(); i++)
//      {
//
//         try
//         {
//
//            if (::multithreading::s_pthreadptra->element_at(i) != pthread)
//            {
//
//               ::multithreading::s_pthreadptra->element_at(i)->finalize();
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      sl.unlock();
//
//      Sleep(100);
//
//   }
//
//   return false;
//
//}



//void replace_thread::replace(::thread * pcanew)
//{
//
//   {
//
//      single_lock sl(&m_mutex,true);
//
//      pcanew->m_preplacethread = this;
//
//      m_pthreadNew = pcanew;
//
//   }
//
//   pcanew->begin();
//
//}
//



::estatus     run_runnable(::generic_object * pobjectTask)
{

   ::estatus     estatus = error_exception;

   try
   {

      __pointer(generic_object) pobject(e_move_transfer, pobjectTask);

      try
      {

         estatus = pobject->call();

      }
      catch(...)
      {

      }

   }
   catch(...)
   {

   }

   return estatus;

}
