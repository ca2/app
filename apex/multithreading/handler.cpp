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

      pobject->m_estatus = ::success_not_ready;

      pobject->m_eobject = NOK_IMAGE_OBJECT;

      async(pobject);

   }

   return pobject->m_estatus;

}


void handler_manager::sync(::layered * pobjectContext)
{

   if (m_bUseDedicatedThread)
   {

      //__throw(todo("thread"));
      //__throw(todo("dedicated_thread"));
      auto pevReady = __new(::manual_reset_event);

      pevReady->ResetEvent();

      __object(pobjectContext)->value("ready_event") = pevReady;

      async(pobjectContext);

      pevReady->wait();

   }
   else
   {

      try
      {

         pobjectContext->call();

      }
      catch (...)
      {

      }

   }

}


void handler_manager::async(::layered * pobjectContext)
{

   {

      sync_lock sl(mutex());

      m_objecta.add(pobjectContext);

      m_pev->SetEvent();

   }

   if (!m_pthread)
   {

      m_pthread = fork([this]()
      {

         // ::get_task()->m_pevSync = m_pev;

         ::get_task()->set_thread_name(m_strThreadName);

         loop();

         m_pev->SetEvent();

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

         sync_lock sl(mutex());

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

