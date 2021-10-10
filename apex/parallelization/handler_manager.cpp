#include "framework.h"
#include "handler_manager.h"

//handler_manager::handler_manager(const string& strThreadName, bool bSingleThread, int iAliveCount) :
//   m_strThreadName(strThreadName),
//   m_bSingleThread(bSingleThread),
//   m_iAliveCount(iAliveCount),
//   m_pevTaskOnQueue(e_create_new),
//   m_iAlive(0),
//   m_bUseDedicatedThread(false)
//{
//
//   defer_create_mutex();
//
//}
//


handler_manager::handler_manager()
{
   
   defer_create_mutex();
   
}
   

handler_manager::~handler_manager()
{


}


//::e_status handler_manager::initialize_handler_manager(::object * pobject, const string & strThreadName, bool bSingleThread, int iAliveCount)
::e_status handler_manager::initialize_handler_manager(::object * pobject, const string & strThreadName, int iAliveCount)
{

   auto estatus = initialize(pobject);

   if (!estatus)
   {

      return estatus;

   }

   m_strThreadName = strThreadName;
   //m_bSingleThread = bSingleThread;
   m_iAliveCount = iAliveCount;
   __construct_new(m_pevTaskOnQueue);
   m_iAlive = 0;
   m_bUseDedicatedThread = false;

   return estatus;

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

      auto estatus = __send_routine(this, &handler_manager::handler_branch, routine);

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


::e_status handler_manager::destroy_composites()
{

   auto estatus = ::object::destroy_composites();

   if (!estatus)
   {

      return estatus;

   }

   return estatus;

}


bool handler_manager::is_branch_current() const
{

   if(::is_null(m_pthread))
   {

      return false;

   }

   return m_pthread->is_current_task();

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


void handler_manager::on_start_loop()
{


//#ifdef WINDOWS
//
//   if (m_bSingleThread)
//   {
//
//      auto psystem = m_psystem;
//
//      auto pnode = psystem->node();
//
//      pnode->on_start_
//
//   }
//
//#endif


}


void handler_manager::loop()
{

   on_start_loop();

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

