#include "framework.h"
#include "task.h"


task::task()
{

   m_bitRunThisThread = true;
   m_bitIsRunning = false;
   m_bitIsPred = true;
   m_hthread = NULL_HTHREAD;
   m_ithread = 0;

}


task::~task()
{


}


string task::get_tag() const
{

   return m_strTaskTag;

}



string task::thread_get_name() const
{

   return m_strTaskName;

}


::context_object * task::calc_parent_thread()
{

   return ::get_task();

}


bool task::set_thread_name(const char* pszThreadName)
{

   m_strTaskName = pszThreadName;

   if (m_strTaskTag.is_empty() && m_strTaskName.has_char())
   {

      m_strTaskTag = m_strTaskName;

   }

   if (!::set_thread_name(m_hthread, pszThreadName))
   {

      return false;

   }

   return true;

}

bool task::thread_get_run() const
{

   return m_bitRunThisThread;

}


bool task::task_active() const
{

   return m_hthread != (HTHREAD) 0;

}


bool task::is_running() const
{

   return m_bitIsRunning;

}


void task::set_thread_run(bool bRun)
{

   m_bitRunThisThread = bRun;

}


void task::set_finish()
{

   m_bitRunThisThread = false;

}


::thread* task::parent_thread()
{

   return ___thread(m_pthreadParent);

}


bool task::is_thread() const
{

   return false;

}


#ifdef WINDOWS
DWORD WINAPI task::s_os_task(void* p)
#else
void* task::s_os_task(void* p)
#endif
{

   try
   {

      ::task* ptask = (::task*) p;

      ::set_task(ptask OBJ_REF_DBG_COMMA_P_FUNCTION_LINE(ptask));

      ptask->release();

      ptask->on_task();

      ptask->term_task();

      ::thread_release(OBJ_REF_DBG_P_NOTE(ptask, ""));

   }
   catch (...)
   {

   }

   return 0;

}


void task::add_notify(::matter* pmatter)
{

   sync_lock sl(mutex());

   m_elementaNotify.add_item(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

}


void task::remove_notify(::matter* pmatter)
{

   sync_lock sl(mutex());

   m_elementaNotify.remove_item(pmatter OBJ_REF_DBG_COMMA_THIS);

}


void task::term_task()
{

   sync_lock sl(mutex());

   auto elementaNotify = m_elementaNotify;

   for (auto& pelement : elementaNotify)
   {

      pelement->task_remove(this);

      pelement->task_on_term(this);

   }

   if (m_pthreadParent)
   {

      ::task* ptaskParent = m_pthreadParent.cast < task>();

      ptaskParent->task_remove(this);

      ptaskParent->task_on_term(this);

      ptaskParent->kick_idle();

   }

}


::estatus task::on_task()
{

   ::estatus estatus = ::success;

   while (m_bitRunThisThread)
   {

      ::matter* pmatter;

      {

         sync_lock sl(mutex());

         pmatter = m_pmatter.m_p;

         m_bitIsRunning = pmatter != nullptr;

         if (!m_bitIsRunning)
         {

            break;

         }

         m_pmatter.m_p = nullptr;

      }

      pmatter->on_task();

   }

   return estatus;

}


::estatus task::_start(
   ::matter* pmatter,
   ::e_priority epriority,
   u32 nStackSize,
   u32 uCreateFlags)
{

   m_pmatter = pmatter;

   return fork(epriority, nStackSize, uCreateFlags);

}


::estatus task::fork(
   ::e_priority epriority,
   u32 nStackSize,
   u32 uCreateFlags)
{

   if (!m_pthreadParent && m_bitIsPred)
   {

      auto ptaskParent = calc_parent_thread();

      if (ptaskParent)
      {

         ptaskParent->task_add(this);

      }

   }

   // __task_procedure() should release this (pmatter)
   add_ref(OBJ_REF_DBG_THIS_FUNCTION_LINE);

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_hthread = ::CreateThread(nullptr, nStackSize, &::task::s_os_task, (LPVOID)(task*)this, uCreateFlags, &dwThread);

   m_ithread = dwThread;

#else

   ptask_attr_t taskAttr;

   ptask_attr_init(&taskAttr);

   if (nStackSize > 0)
   {

      ptask_attr_setstacksize(&taskAttr, nStackSize); // Set the stack size of the task

   }

   ptask_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for ptask_join

   ptask_create(
      &m_hthread,
      &taskAttr,
      &task::s_os_task,
      (LPVOID)(::task*) this);

#endif

   if (!m_hthread)
   {

      return ::error_failed;

   }

   return ::success;

}


__pointer(task) task::start(::matter * pmatter, ::e_priority epriority, UINT nStackSize, u32 uiCreateFlags)
{

   auto ptask = __new(task);

   ptask->_start(pmatter, epriority, nStackSize, uiCreateFlags);

   return ptask;


}





//
//bool task::set_task_name(const char* pszThreadName)
//{
//
//   if (!::set_task_name(m_hthread, pszThreadName))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}

//
//void task::set_task_run(bool bRun)
//{
//
//   m_bRunThisThread = bRun;
//
//}


void task::kick_idle()
{


}







CLASS_DECL_ACME bool __task_sleep(task* task)
{

   while (task->thread_get_run())
   {

      Sleep(100);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, tick tick)
{

   if (tick.m_i < 1000)
   {

      if (!ptask->thread_get_run())
      {

         return false;

      }

      Sleep(tick);

      return ptask->thread_get_run();

   }

   auto iTenths = tick.m_i / 10;

   auto iMillis = tick.m_i % 10;

   try
   {

      __pointer(manual_reset_event) spev;

      {

         sync_lock sl(ptask->mutex());

         if (ptask->m_pevSleep.is_null())
         {

            ptask->m_pevSleep = __new(manual_reset_event());

            ptask->m_pevSleep->ResetEvent();

         }

         spev = ptask->m_pevSleep;

      }

      if (!ptask->thread_get_run())
      {

         return false;

      }

      //while(iTenths > 0)
      //{

      ptask->m_pevSleep->wait(tick);

      if (!ptask->thread_get_run())
      {

         return false;

      }

      //iTenths--;

   //}

   }
   catch (...)
   {

   }

   return ptask->thread_get_run();

}


CLASS_DECL_ACME bool __task_sleep(::task* ptask, sync* psync)
{

   try
   {

      while (ptask->thread_get_run())
      {

         if (psync->wait(100).succeeded())
         {

            break;

         }

      }

   }
   catch (...)
   {

   }

   return ptask->thread_get_run();

}


CLASS_DECL_ACME bool __task_sleep(task* ptask, tick tick, sync* psync)
{

   if (tick.m_i < 1000)
   {

      if (!ptask->thread_get_run())
      {

         return false;

      }

      psync->wait(tick);

      return ptask->thread_get_run();

   }

   auto iTenths = tick.m_i / 100;

   auto iMillis = tick.m_i % 100;

   try
   {

      {

         ptask->m_pevSleep->wait(100);

         if (!ptask->thread_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return ptask->thread_get_run();

}


CLASS_DECL_ACME bool task_sleep(tick tick, sync* psync)
{

   auto ptask = ::get_task();

   if (::is_null(ptask))
   {

      if (::is_null(psync))
      {

         if (__os(tick) == INFINITE)
         {

         }
         else
         {

            ::Sleep(tick);

         }

      }
      else
      {

         if (__os(tick) == INFINITE)
         {

            return psync->lock();

         }
         else
         {

            return psync->lock(tick);

         }

      }

      return true;

   }

   if (::is_null(psync))
   {

      if (__os(tick) == INFINITE)
      {

         return __task_sleep(ptask);

      }
      else
      {

         return __task_sleep(ptask, tick);

      }

   }
   else
   {

      if (__os(tick) == INFINITE)
      {

         return __task_sleep(ptask, psync);

      }
      else
      {

         return __task_sleep(ptask, tick, psync);

      }

   }
}



