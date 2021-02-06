#include "framework.h"
#include "task.h"
#ifdef LINUX
#include <pthread.h>
#endif


task::task()
{

   m_bitCoInitialize = false;
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


::task * task::get_task()
{

   return this;

}


const char * task::get_task_tag()
{

   return m_strTaskTag;

}


//::context_object * task::calc_parent_thread()
//{
//
//   return ::get_task();
//
//}


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

   return !m_bSetFinish;

}


bool task::task_active() const
{

   return m_hthread != (hthread_t) 0;

}


bool task::is_running() const
{

   return m_bitIsRunning;

}


::object * task::thread_parent()
{

   return __object(m_pobjectParent);

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

      ::task* pthread = (::task*) p;

      ::set_task(pthread OBJ_REF_DBG_COMMA_P_FUNCTION_LINE(pthread));

      pthread->release(OBJ_REF_DBG_P_FUNCTION_LINE(pthread));

      pthread->do_task();

#if OBJ_REF_DBG

      if (pthread->m_countReference > 1)
      {

         __check_pending_releases(pthread);

      }

#endif

      ::thread_release(OBJ_REF_DBG_P_NOTE(pthread, ""));

   }
   catch (...)
   {

   }

   return 0;

}


void task::add_notify(::matter* pmatter)
{

   sync_lock sl(mutex());

   notify_array().add_item(pmatter OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

}


void task::remove_notify(::matter* pmatter)
{

   sync_lock sl(mutex());

   if (m_pnotifya)
   {

      m_pnotifya->remove_item(pmatter OBJ_REF_DBG_COMMA_THIS);

   }

}


bool task::on_get_thread_name(string & strThreadName)
{

   if (m_strTaskTag.has_char())
   {

      //::set_thread_name(m_strTaskTag);

      strThreadName = m_strTaskTag;

   }
   else
   {

      //::set_thread_name(type_name());

      strThreadName = type_name();

   }

   return true;

}


::e_status task::task_caller_on_init()
{

   return ::success;

}


void task::init_task()
{

   string strThreadName;

   if (on_get_thread_name(strThreadName))
   {

      set_thread_name(strThreadName);

   }

   if (string(type_name()).contains("synth_thread"))
   {

      output_debug_string("synth_thread thread::thread_proc");

   }
   else if (string(type_name()).ends_ci("out"))
   {

      output_debug_string("synth_thread thread::out");

   }

}


void task::term_task()
{

   try
   {

      finalize();

   }
   catch (...)
   {

   }

   sync_lock sl(mutex());

   //if (m_pnotifya)
   //{

   //   auto notifya = *m_pnotifya;

   //   sl.unlock();

   //   for (auto & pmatter : notifya)
   //   {

   //      pmatter->task_remove(this);

   //      pmatter->task_on_term(this);

   //   }

   //   sl.lock();

   //}

   //if (m_pthreadParent)
   //{

   //   m_pthreadParent->task_on_term(this);

   //   m_pthreadParent->task_remove(this);

   //   //m_pthreadParent->kick_idle();

   //}

}


::e_status task::do_task()
{

   init_task();

   auto estatus = on_task();

   term_task();

   return estatus;

}


::e_status task::on_task()
{

   ::e_status estatus = ::success;

   while (!m_bSetFinish)
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

         m_id = pmatter->type_name();

         set_thread_name(m_id);

         m_pmatter.m_p = nullptr;

      }

      pmatter->on_task();

   }

   return estatus;

}


::e_status task::start(
   ::matter* pmatter,
   ::e_priority epriority,
   u32 nStackSize,
   u32 uCreateFlags)
{

   m_pmatter = pmatter;

   m_id = pmatter->type_name();

   return begin_task(epriority, nStackSize, uCreateFlags);

}


::e_status task::begin_task(
   ::e_priority epriority,
   u32 nStackSize,
   u32 uCreateFlags)
{

   if (m_id.is_empty())
   {

      if (m_pmatter)
      {

         m_id = m_pmatter->type_name();

      }
      else
      {

         m_id = type_name();

      }

   }

   if (m_id.is_empty() || m_id == "task" || m_id == "thread")
   {

      __throw(invalid_argument_exception());

      return ::error_failed;

   }

   auto estatus = task_caller_on_init();

   if (!estatus)
   {

      return estatus;

   }

   //if (m_pobjectParent && m_bitIsPred)
   //{

   //   //auto pthreadParent = calc_parent_thread();

   //   m_pobjectParent->task_add(this);


   //   if (pthreadParent)
   //   {

   //

   //   }

   //}

   // __task_procedure() should release this (pmatter)
   add_ref(OBJ_REF_DBG_THIS_FUNCTION_LINE);

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_hthread = ::CreateThread(nullptr, nStackSize, &::task::s_os_task, (LPVOID)(task*)this, uCreateFlags, &dwThread);

   m_ithread = dwThread;

#else

   pthread_attr_t taskAttr;

   pthread_attr_init(&taskAttr);

   if (nStackSize > 0)
   {

      pthread_attr_setstacksize(&taskAttr, nStackSize); // Set the stack size_i32 of the task

   }

   pthread_attr_setdetachstate(&taskAttr, PTHREAD_CREATE_DETACHED); // Set task to detached state. No need for pthread_join

   pthread_create(
      &m_hthread,
      &taskAttr,
      &task::s_os_task,
      this);

#endif

   if (!m_hthread)
   {

      return ::error_failed;

   }

   return ::success;

}


::task_pointer task::launch(::matter * pmatter, ::e_priority epriority, ::u32 nStackSize, u32 uCreateFlags)
{

   auto ptask = __new(task);

   ptask->start(pmatter, epriority, nStackSize, uCreateFlags);

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

      sleep(100_ms);

   }

   return false;

}


CLASS_DECL_ACME bool __task_sleep(task* pthread, millis millis)
{

   if (millis.m_i < 1000)
   {

      if (!pthread->thread_get_run())
      {

         return false;

      }

      sleep(millis);

      return pthread->thread_get_run();

   }

   auto iTenths = millis.m_i / 10;

   auto iMillis = millis.m_i % 10;

   try
   {

      __pointer(manual_reset_event) spev;

      {

         sync_lock sl(pthread->mutex());

         if (pthread->m_pevSleep.is_null())
         {

            pthread->m_pevSleep = __new(manual_reset_event());

            pthread->m_pevSleep->ResetEvent();

         }

         spev = pthread->m_pevSleep;

      }

      if (!pthread->thread_get_run())
      {

         return false;

      }

      //while(iTenths > 0)
      //{

      pthread->m_pevSleep->wait(millis);

      if (!pthread->thread_get_run())
      {

         return false;

      }

      //iTenths--;

   //}

   }
   catch (...)
   {

   }

   return pthread->thread_get_run();

}


CLASS_DECL_ACME bool __task_sleep(::task* pthread, sync* psync)
{

   try
   {

      while (pthread->thread_get_run())
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

   return pthread->thread_get_run();

}


CLASS_DECL_ACME bool __task_sleep(task* pthread, millis millis, sync* psync)
{

   if (millis.m_i < 1000)
   {

      if (!pthread->thread_get_run())
      {

         return false;

      }

      psync->wait(millis);

      return pthread->thread_get_run();

   }

   auto iTenths = millis.m_i / 100;

   auto iMillis = millis.m_i % 100;

   try
   {

      {

         pthread->m_pevSleep->wait(100);

         if (!pthread->thread_get_run())
         {

            return false;

         }

         iTenths--;

      }

   }
   catch (...)
   {

   }

   return pthread->thread_get_run();

}


CLASS_DECL_ACME bool task_sleep(millis millis, sync* psync)
{

   auto pthread = ::get_task();

   if (::is_null(pthread))
   {

      if (::is_null(psync))
      {

         if (__os(millis) == U32_INFINITE_TIMEOUT)
         {

         }
         else
         {

            ::sleep(millis);

         }

      }
      else
      {

         if (__os(millis) == U32_INFINITE_TIMEOUT)
         {

            return psync->lock();

         }
         else
         {

            return psync->lock(millis);

         }

      }

      return true;

   }

   if (::is_null(psync))
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __task_sleep(pthread);

      }
      else
      {

         return __task_sleep(pthread, millis);

      }

   }
   else
   {

      if (__os(millis) == U32_INFINITE_TIMEOUT)
      {

         return __task_sleep(pthread, psync);

      }
      else
      {

         return __task_sleep(pthread, millis, psync);

      }

   }
}



