#include "framework.h"


handler_manager::handler_manager(const string& strThreadName, bool bSingleThread, int iAliveCount) :
   m_strThreadName(strThreadName),
   m_bSingleThread(bSingleThread),
   m_iAliveCount(iAliveCount),
   m_pevTaskOnQueue(e_create_new),
   m_iAlive(0),
   m_bUseDedicatedThread(false)
{

   defer_create_mutex();

}


handler_manager::~handler_manager()
{


}


::e_status handler_manager::handle(const ::routine & routine, bool bSync)
{

   if (bSync)
   {

      return synchronization_object(routine);

   }
   else
   {

      return async(routine);

   }

}


::e_status handler_manager::synchronization_object(const ::routine & routine)
{

   if (m_bUseDedicatedThread)
   {

      auto proutine = ___sync_routine(routine);

      async(proutine);

      proutine->wait(one_minute());

      return ::success;

   }
   else
   {

      return routine();

   }

}


::e_status handler_manager::set_finish_composites(::property_object * pcontextobjectFinish)
{

   return ::object::set_finish_composites(pcontextobjectFinish);

}



::e_status handler_manager::async(const ::routine & routine)
{

   {

      synchronization_lock synchronizationlock(mutex());

      m_routinea.add(routine);

      m_pevTaskOnQueue->SetEvent();

   }

   if (!m_pthread)
   {

      m_pthread = fork([this]()
      {

         ::get_task()->set_thread_name(m_strThreadName);

         loop();

         ::output_debug_string("handler_manager::async fork finished!!");

      });
      
   }

   return ::success;

}


::routine handler_manager::pick_new_task()
{

   synchronization_lock synchronizationlock(mutex());

   if (m_routinea.is_empty())
   {

      synchronizationlock.unlock();

      m_pevTaskOnQueue->wait(1_s);

      synchronizationlock.lock();

   }

   if (m_routinea.is_empty())
   {

      return nullptr;

   }

   auto method = m_routinea.first();

   m_routinea.remove_at(0);

   if (m_routinea.is_empty())
   {

      m_pevTaskOnQueue->ResetEvent();

   }

   return method;

}


void handler_manager::loop()
{

#ifdef WINDOWS

   if (m_bSingleThread)
   {

      defer_co_initialize_ex(false, true);

   }

#endif

   int iAlive = 0;

   while (::task_get_run())
   {

      auto method = pick_new_task();

      if(!method)
      {

         continue;

      }

      method();

   }

   m_pthread.release();

};

