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

      return handler_sync(routine);

   }
   else
   {

      return handler_branch(routine);

   }

}


::e_status handler_manager::handler_sync(const ::routine & routine)
{

   if (m_bUseDedicatedThread)
   {

      auto estatus = __sync_routine(1_min, this, &handler_manager::handler_branch, routine);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }
   else
   {

      return routine();

   }

}


::e_status handler_manager::finish_composites()
{

   return ::object::finish_composites();

}


::e_status handler_manager::handler_branch(const ::routine & routine)
{

   {

      synchronous_lock synchronouslock(mutex());

      m_routinea.add(routine);

      m_pevTaskOnQueue->SetEvent();

   }

   if (!m_pthread)
   {

      m_pthread = fork([this]()
      {

         ::get_task()->task_set_name(m_strThreadName);

         loop();

         ::output_debug_string("handler_manager::async fork finished!!");

      });
      
   }

   return ::success;

}


::routine handler_manager::pick_new_task()
{

   synchronous_lock synchronouslock(mutex());

   if (m_routinea.is_empty())
   {

      synchronouslock.unlock();

      m_pevTaskOnQueue->wait(1_s);

      synchronouslock.lock();

   }

   if (m_routinea.is_empty())
   {

      return nullptr;

   }

   auto method = m_routinea.first();

   m_routinea.erase_at(0);

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

