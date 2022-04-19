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


//void handler_manager::initialize_handler_manager(::object * pobject, const string & strThreadName, bool bSingleThread, int iAliveCount)
void handler_manager::initialize_handler_manager(::object * pobject, const string & strThreadName, int iAliveCount)
{

   //auto estatus = initialize(pobject);
   initialize(pobject);

   /*if (!estatus)
   {

      return estatus;

   }*/

   m_strThreadName = strThreadName;
   //m_bSingleThread = bSingleThread;
   m_iAliveCount = iAliveCount;
   __construct_new(m_pevTaskOnQueue);
   m_iAlive = 0;
   m_bUseDedicatedThread = false;

   //return estatus;

}


void handler_manager::handle(const ::procedure & procedure, bool bSynchronously)
{

   if (bSynchronously)
   {

      return handle_synchronously(procedure);

   }
   else
   {

      return handle_asynchronously(procedure);

   }

}


void handler_manager::handle_synchronously(const ::procedure & procedure)
{

   if (m_bUseDedicatedThread)
   {

      __send_procedure(this, &handler_manager::handle_asynchronously, procedure);

   }
   else
   {

      return procedure();

   }

}


void handler_manager::destroy_composites()
{

   ::object::destroy_composites();

}


bool handler_manager::is_branch_current() const
{

   if(::is_null(m_pthread))
   {

      return false;

   }

   return m_pthread->is_current_task();

}


void handler_manager::handle_asynchronously(const ::procedure & procedure)
{

   {

      synchronous_lock synchronouslock(mutex());

      m_procedurea.add(procedure);

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

   //return ::success;

}


::procedure handler_manager::pick_new_task()
{

   synchronous_lock synchronouslock(mutex());

   if (m_procedurea.is_empty())
   {

      synchronouslock.unlock();

      m_pevTaskOnQueue->wait(1_s);

      synchronouslock.lock();

   }

   if (m_procedurea.is_empty())
   {

      return nullptr;

   }

   auto method = m_procedurea.first();

   m_procedurea.erase_at(0);

   if (m_procedurea.is_empty())
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

