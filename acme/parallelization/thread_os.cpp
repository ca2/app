#include "framework.h"


//class thread_proc_runner :
//   virtual public matter
//{
//public:
//
//
//   ::thread_proc     m_proc;
//   void *            m_p;
//
//
//   thread_proc_runner(::thread_proc proc, void * p) :
//      m_proc(proc),
//      m_p(p)
//   {
//
//   }
//
//   virtual u32 thread_proc();
//
//
//};









//// very close to the operating system
//CLASS_DECL_ACME hthread_t create_thread(
//thread_proc proc,
//void * p,
//::e_priority epriority,
//::u32 nStackSize,
//u32 uiCreateFlags,
//LPSECURITY_ATTRIBUTES psa,
//
//ithread_t * puiId)
//{
//
//   thread_proc_runner * pdata = new thread_proc_runner(proc, p);
//
//   return pdata->create_thread(epriority, nStackSize, uiCreateFlags, psa, puiId);
//
//
//}





CLASS_DECL_ACME PPROC_SIMPLE g_axisoninitthread = nullptr;
CLASS_DECL_ACME PPROC_SIMPLE g_axisontermthread = nullptr;

//u32 thread_proc_runner::thread_proc()
//{
//
//   if (g_axisoninitthread)
//   {
//
//      g_axisoninitthread();
//
//   }
//
//   if (!on_init_thread())
//   {
//
//      return error_failed;
//
//   }
//
//   u32 u = m_proc(m_p);
//
//   try
//   {
//
//      if (g_axisontermthread)
//      {
//
//         g_axisontermthread();
//
//      }
//
//      on_term_thread();
//
//   }
//   catch (...)
//   {
//
//   }
//
//   return u;
//
//}


//thread_local ＿＿pointer(::thread) t_pthread;


//::thread* get_task()
//{
//   
//   return t_pthread; 
//
//}


//void set_thread(thread* pthread)
//{
//
//   t_pthread = pthread;
//
//}


//void thread_release()
//{
//
//   t_pthread.release();
//
//}



