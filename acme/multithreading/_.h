#pragma once


#include "common.h"


#ifdef APPLEOS
#include <semaphore.h>
#endif





// LPVOID thread_data_get(thread_data_index dataindex);
// int_bool thread_data_set(thread_data_index dataindex, void* pvalue);


// thread_data_index thread_data_allocate();
// int_bool thread_data_free(thread_data_index dataindex);


//
//thread_local __pointer(property_set) t_ppropertyset;
//
//
//
//property_set& _thread_property_set();
//
//
//property_set & thread_property_set();


#if defined(ANDROID)


//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(APPLEOS)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
#undef MUTEX_NAMED_VSEM

#elif defined(LINUX)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // System V Semaphore
#undef MUTEX_NAMED_VSEM

#endif



class sync;
class semaphore;
//class ::mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;


CLASS_DECL_ACME ::estatus __call(const ::method & method);



//namespace multithreading
//{
//
//
//   namespace array
//   {
//
//      template < typename ARRAY >
//      __pointer(::matter) is_running(ARRAY & array, const char * pszTag)
//      {
//
//         for (::index i = 0; i < array.get_size(); i++)
//         {
//
//            __pointer(::matter) pobject;
//
//            pobject = &__typed(array[i]);
//
//            if (pobject && pobject->is_thread())
//            {
//
//               if (pobject->thread_get_run())
//               {
//
//                  if (pobject->get_tag().compare(pszTag) == 0)
//                  {
//
//                     return pobject;
//
//                  }
//
//               }
//
//            }
//
//         }
//
//         return nullptr;
//
//      }
//
//
//   }
//
//
//} // namespace multithreading



CLASS_DECL_ACME bool set_thread_name(const char * psz);
CLASS_DECL_ACME bool set_thread_name(HTHREAD hthread, const char* pszName);


typedef ::estatus     (*__THREADPROC)(void *);



class tool_thread;
class thread_tool;
class thread_tools;
//class thread_toolset;
//class pred_set;
//class replace_thread;


class thread_startup;


namespace multithreading
{


   CLASS_DECL_ACME bool set_priority(e_priority epriority);

   CLASS_DECL_ACME i32 priority();


   //inline i32 get_priority_none()
   //{

   //   return priority_none;

   //}


   //inline i32 get_priority_normal()
   //{

   //   return priority_normal;

   //}


} // namespace multithreading


class sync_interface;
class sync_lock;


//class CLASS_DECL_ACME thread_ptra :
//   virtual public __pointer_array(thread)
//{
//public:
//
//
//   thread_ptra();
//   thread_ptra(const thread_ptra & ptra):__pointer_array(thread)(ptra) {}
//   thread_ptra(thread_ptra && ptra) :__pointer_array(thread)(::move(ptra)) {}
//   virtual ~thread_ptra();
//
//   virtual ::count get_count_except_current_thread();
//   virtual void finish();
//   virtual void wait(const duration & duration, ::sync_lock & sl);
//
//   thread_ptra & operator = (const thread_ptra & ptra) { __pointer_array(thread)::operator =(ptra); return *this; }
//   thread_ptra & operator = (thread_ptra && ptra) { __pointer_array(thread)::operator =(::move(ptra)); return *this; }
//
//};




#include "pred_holder.h"

#include "sync.h"
#include "sync_array.h"
#include "semaphore.h"
#include "mutex.h"
#include "event.h"
#include "set_event_on_exit.h"
#include "condition.h"
#include "file_change_event.h"
#include "socket_event.h"
#include "single_lock.h"
//#include "retry_single_lock.h"
#include "initial_single_lock.h"
#include "sync_lock.h"
#include "multi_lock.h"
//#include "retry_multi_lock.h"

//#include "synch_index_ptr_array.h"
//#include "synch_index_iterator.h"


#ifdef ___ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "_impl.h"
#undef _AFXMT_INLINE
#endif


#include "manual_reset_event.h"


//#include "acme/multithreading/sync_method.h"


//#include "acme/multithreading/sync_future.h"


#include "acme/multithreading/task.h"


#include "sync_task.h"


#ifdef WINDOWS
#include <Winsvc.h>
#endif

//#include "service_status.h"
#include "thread_os.h"


#include "create_thread.h"


//#include "service/thread_pool.h"





//CLASS_DECL_ACME u32 random_processor_index_generator();


CLASS_DECL_ACME int_bool post_message(oswindow oswindow, const ::id & id, WPARAM wparam, LPARAM lparam);




// namespace multithreading
// {


//    CLASS_DECL_ACME void os_tls_init();

//    CLASS_DECL_ACME void os_tls_term();

//    CLASS_DECL_ACME void os_tls_set(void * p);

//    CLASS_DECL_ACME void * os_tls_get();


// } // namespace multithreading


class thread;


namespace multithreading
{


   CLASS_DECL_ACME bool task_registered(::task * ptask);
   CLASS_DECL_ACME bool task_id_registered(ITHREAD id);

   CLASS_DECL_ACME void task_register(ITHREAD itask, ::task * ptask);

   CLASS_DECL_ACME void task_unregister(ITHREAD itask, ::task * ptask);


} // namespace multithreading


//
//
//   void finish(::thread* pthread);
//
//
//} // namespace multithreading


//#define Thrd(pcontext)
//#define Thread

CLASS_DECL_ACME::task* get_task();
CLASS_DECL_ACME ::thread* get_thread();
//CLASS_DECL_ACME ::thread* get_task(ITHREAD idthread);
CLASS_DECL_ACME void set_task(task * ptask OBJ_REF_DBG_COMMA_PARAMS);
CLASS_DECL_ACME void thread_release(OBJ_REF_DBG_PARAMS);


//typedef bool task_sleep(tick tick, ::sync* psync);
//using PFN_task_sleep = task_sleep*;

CLASS_DECL_ACME bool __simple_task_sleep();
CLASS_DECL_ACME bool __simple_task_sleep(tick tick);
CLASS_DECL_ACME bool __simple_task_sleep(::sync* psync);
CLASS_DECL_ACME bool __simple_task_sleep(tick tick, ::sync* psync);
CLASS_DECL_ACME bool task_sleep(tick tick = INFINITE, ::sync * psync = nullptr);
//CLASS_DECL_ACME bool acme_task_sleep(tick tick = INFINITE, ::sync* psync = nullptr);
//CLASS_DECL_ACME void set_taskhread_sleep(PFN_task_sleep pfnThreadSleep);

#ifdef _UWP

#include "acme/os/uwp/multithreading_winrt.h"

#endif


string get_task_name(HTHREAD hthread);

#include "acme/primitive/collection/runnable_array.h"



typedef string GET_THREAD_NAME(::thread* pthread);

using LPFN_GET_THREAD_NAME = GET_THREAD_NAME*;

CLASS_DECL_ACME void set_get_thread_name(LPFN_GET_THREAD_NAME);
string get_thread_name(::thread* pthread);

CLASS_DECL_ACME void thread_name_abbreviate(string & strName, int len);

CLASS_DECL_ACME bool set_thread_name(HTHREAD hthread, const char * psz);
CLASS_DECL_ACME bool set_thread_name(const char * psz);

//#include "update_task_item_array.h"






CLASS_DECL_ACME bool __task_sleep(task* task);

CLASS_DECL_ACME bool __task_sleep(task* ptask, tick tick);

CLASS_DECL_ACME bool __task_sleep(::task* ptask, sync* psync);

CLASS_DECL_ACME bool __task_sleep(task* ptask, tick tick, sync* psync);

CLASS_DECL_ACME bool task_sleep(tick tick, sync* psync);


#include "sync_method.h"


#include "sync_future.h"


#include "pred_sync_method.h"



