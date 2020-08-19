#include "framework.h"


handler_manager::handler_manager(const string& strThreadName, bool bSingleThread, int iAliveCount) :
   m_strThreadName(strThreadName),
   m_bSingleThread(bSingleThread),
   m_iAliveCount(iAliveCount),
   m_pev(e_create_new),
   m_iAlive(0),
   m_bUseDedicatedThread(false)
{

   defer_create_mutex();

}


handler_manager::~handler_manager()
{


}


::estatus handler_manager::handle(::object * pobject, bool bSync)
{

   if (bSync)
   {

      sync(pobject);

   }
   else
   {

      pobject->m_estatus = ::error_not_ready;

      async(pobject);

   }

   return pobject->m_estatus;

}


void handler_manager::sync(::object * pobject)
{

   if (m_bUseDedicatedThread)
   {

      auto pevReady = __new(::manual_reset_event);

      pevReady->ResetEvent();

      pobject->value("ready_event") = pevReady;

      async(pobject);

      pevReady->wait();

   }
   else
   {

      try
      {

         pobject->call();

      }
      catch (...)
      {

      }

   }

}


void handler_manager::async(::object * pobject)
{

   sync_lock sl(mutex());

   m_objecta.add(pobject);

   m_pev->SetEvent();

   if (!m_pthread)
   {

      m_pthread = fork([this]()
      {

         ::get_thread()->m_pevSync = m_pev;

         ::get_thread()->set_thread_name(m_strThreadName);

         loop();

      });

   }


}


bool handler_manager::wait()
{

   if (m_iAliveCount < 0)
   {

      m_pev->wait();

   }
   else
   {

      if (!m_pev->wait(1_s).succeeded())
      {

         m_iAlive++;

         if (m_iAlive > m_iAliveCount)
         {

            return false;

         }

      }

   }

   return true;


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

      if (!wait())
      {

         break;

      }

      __pointer(::context_object) pobject;

      {

         single_lock sl(mutex());

         if (m_objecta.isEmpty())
         {

            m_pev->ResetEvent();

            continue;

         }
         else
         {

            pobject = m_objecta.first_pointer();

            m_objecta.remove_at(0);

         }

      }

      if (!pobject)
      {

         continue;

      }

      pobject->m_estatus = pobject->call();

      auto pevReady = pobject->value("ready_event").cast < ::manual_reset_event>();

      if (pevReady)
      {

         pevReady->SetEvent();

      }

   }

   m_pthread.release();

};

