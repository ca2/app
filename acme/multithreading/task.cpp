#include "framework.h"
#include "task.h"



task::task()
{

   m_bitRunThisThread = true;
   m_bitIsRunning = false;
   m_hthread = nullptr;
   m_ithread = 0;

}


task::~task()
{


}

//
//__pointer(task) task::fork(
//   ::matter* pmatter,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags,
//   ITHREAD* pithread,
//   HTHREAD* phthread)
//{
//
//
//
//}


bool task::thread_get_run() const
{

   return m_bitRunThisThread;

}


void task::set_thread_run(bool bRun)
{

   m_bitRunThisThread = bRun;

}


bool task::is_thread() const
{

   return false;

}



//m::___fork(::matter* pmatter)
//{
//
//   m_pmatter.reset(pmatter OBJ_REF_DBG_ADD_THIS_FUNCTION_LINE);
//
//}
//
//
//___fork::~___fork()
//{
//
//   m_pmatter.release(OBJ_REF_DBG_THIS_FUNCTION_LINE);
//
//}


//CLASS_DECL_ACME::estatus __fork(
//   matter* pmatter,
//   ::e_priority epriority,
//   u32 nStackSize,
//   u32 dwCreateFlags,
//   ITHREAD* pithread,
//   HTHREAD* phthread)
//{
//
//   return pmatter->fork(epriority, nStackSize, dwCreateFlags, pithread, phthread);
//
//}



#ifdef WINDOWS
DWORD WINAPI task::s_os_task(void* p)
#else
void* task::s_os_task(void* p)
#endif
{

   try
   {

      ::task* ptask = (::task*) p;

      ::set_task(ptask OBJ_REF_DBG_ADD_P_FUNCTION_LINE(ptask));

      ptask->release();

      ptask->on_task();

      ::thread_release(OBJ_REF_DBG_P_NOTE(ptask, ""));

   }
   catch (...)
   {

   }

   return 0;

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
      &ptask->m_hthread,
      &threadAttr,
      &matter::s_os_thread_procedure,
      (LPVOID)(::matter*) this);

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






bool task::set_thread_name(const char* pszThreadName)
{

   if (!::set_thread_name(m_hthread, pszThreadName))
   {

      return false;

   }

   return true;

}

//
//void task::set_thread_run(bool bRun)
//{
//
//   m_bRunThisThread = bRun;
//
//}
