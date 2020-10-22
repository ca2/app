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

      auto pthreadParent = calc_parent_thread();

      if (pthreadParent)
      {

         pthreadParent->task_add(this);

      }

   }

   // __thread_procedure() should release this (pmatter)
   add_ref(OBJ_REF_DBG_THIS_FUNCTION_LINE);

#ifdef WINDOWS

   DWORD dwThread = 0;

   m_hthread = ::CreateThread(nullptr, nStackSize, &::task::s_os_task, (LPVOID)(task*)this, uCreateFlags, &dwThread);

   m_ithread = dwThread;

#else

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if (nStackSize > 0)
   {

      pthread_attr_setstacksize(&threadAttr, nStackSize); // Set the stack size of the thread

   }

   pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(
      &m_hthread,
      &threadAttr,
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
//bool task::set_thread_name(const char* pszThreadName)
//{
//
//   if (!::set_thread_name(m_hthread, pszThreadName))
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
//void task::set_thread_run(bool bRun)
//{
//
//   m_bRunThisThread = bRun;
//
//}


void task::kick_idle()
{


}



