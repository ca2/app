#include "framework.h"
#include "launch.h"


___launch::___launch(::matter* pmatter) :
   m_pmatter(pmatter)
{

}


___launch::~___launch()
{


}


CLASS_DECL_ACME ::estatus __launch(
   matter* pmatter,
   ::e_priority epriority,
   u32 nStackSize,
   u32 dwCreateFlags,
   ITHREAD* pithread,
   HTHREAD* phthread)
{

   auto plaunch = new ___launch(pmatter);

   plaunch->launch();

   return ::success;

}



#ifdef WINDOWS


DWORD WINAPI ___launch::s_os_thread_proc(void* p)
{

   try
   {

      ::___launch* plaunch = (::___launch*) p;

      plaunch->__thread_procedure();

      delete plaunch;

   }
   catch (...)
   {

   }

   return 0;

}


#else


void* ___launch::s_os_thread_proc(void* p)
{

   try
   {

      ::___launch* plaunch = (::___launch*) p;

      plaunch->__thread_procedure();

      delete plaunch;

   }
   catch (...)
   {

   }

   return NULL;

}


#endif


::estatus ___launch::fork(::e_priority epriority, UINT nStackSize, u32 uiCreateFlags, ITHREAD* pithread, HTHREAD* phthread)
{

   HTHREAD hthread = NULL_HTHREAD;

   ITHREAD ithread = NULL_ITHREAD;

#ifdef WINDOWS

   DWORD dwThread = 0;

   hthread = ::CreateThread(nullptr, nStackSize, &::___launch::s_os_thread_proc, (LPVOID)(___launch*)this, uiCreateFlags, &dwThread);

   ithread = dwThread;

#else

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if (nStackSize > 0)
   {

      pthread_attr_setstacksize(&threadAttr, nStackSize); // Set the stack size of the thread

   }

   pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(
      &hthread,
      &threadAttr,
      &___launch::s_os_thread_proc,
      (LPVOID)plaunch);

#endif

   if (phthread)
   {

      *phthread = hthread;

   }

   if (pithread)
   {

      *pithread = ithread;

   }

   if (!hthread)
   {

      return ::error_failed;

   }

   return ::success;

}


//::estatus ___launch::__thread_procedure()
//{
//
//   try
//   {
//
//      m_pmatter->run();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return ::success;
//
//}



