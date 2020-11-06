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


::estatus handler_manager::handle(const ::procedure & procedure, bool bSync)
{

   if (bSync)
   {

      return sync(procedure);

   }
   else
   {

      return async(procedure);

   }

}


::estatus handler_manager::sync(const ::procedure & procedure)
{

   if (m_bUseDedicatedThread)
   {

      auto pprocedure = ___sync_procedure(procedure);

      async(pprocedure);

      pprocedure->wait(one_minute());

      return ::success;

   }
   else
   {

      return procedure();

   }

}


::estatus handler_manager::set_finish_composites(::context_object * pcontextobjectFinish)
{

   return ::object::set_finish_composites(pcontextobjectFinish);

}



::estatus handler_manager::async(const ::procedure & procedure)
{

   {

      sync_lock sl(mutex());

      m_procedurea.add(procedure);

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


procedure handler_manager::pick_new_task()
{

   sync_lock sl(mutex());

   if (m_procedurea.is_empty())
   {

      sl.unlock();

      m_pevTaskOnQueue->wait(1_s);

      sl.lock();

   }

   if (m_procedurea.is_empty())
   {

      return nullptr;

   }

   auto method = m_procedurea.first();

   m_procedurea.remove_at(0);

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

   while (::thread_get_run())
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

