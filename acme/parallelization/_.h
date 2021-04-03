#pragma once


#include "common.h"

namespace factory
{


   template < typename TYPE, typename BASE_TYPE >
   class reusable_factory;


} // namespace factory

#ifndef WINDOWS


#define MAXIMUM_WAIT_OBJECTS 64


#endif


#ifdef APPLEOS
#include <semaphore.h>
#endif

#include "synchronization_result.h"

#ifdef PARALLELIZATION_PTHREAD

#define CRITICAL_SECTION_FUNCTION_RETURN int

CRITICAL_SECTION_FUNCTION_RETURN pthread_recursive_mutex_init(pthread_mutex_t* pmutex);

#else

#define CRITICAL_SECTION_FUNCTION_RETURN void

#endif


#define MAXIMUM_SYNCHRONIZING_OBJECTS 64

using hsync = void *;

#define INVALID_HSYNC_VALUE ((hsync)nullptr)



CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder);


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
//#define MUTEX_NAMED_VSEM // get_system() V Semaphore
#undef MUTEX_NAMED_VSEM

#endif



class synchronization_object;
class semaphore;
//class ::mutex;
class event;
class critical_section;
class single_lock;
class multi_lock;


CLASS_DECL_ACME ::e_status __call(const ::routine & routine);


//namespace parallelization
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
//               if (pobject->task_get_run())
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
//} // namespace parallelization



CLASS_DECL_ACME bool set_thread_name(const char * psz);
CLASS_DECL_ACME bool set_thread_name(htask_t hthread, const char* pszName);


typedef ::e_status     (*__THREADPROC)(void *);



class tool_task;
class task_tool;
class thread_tools;
//class thread_toolset;
//class predicate_set;
//class replace_thread;


class thread_startup;


namespace parallelization
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

   CLASS_DECL_ACME string thread_get_name();


} // namespace parallelization


class sync_interface;
class synchronous_lock;


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
//   virtual void wait(const duration & duration, ::synchronous_lock & synchronouslock);
//
//   thread_ptra & operator = (const thread_ptra & ptra) { __pointer_array(thread)::operator =(ptra); return *this; }
//   thread_ptra & operator = (thread_ptra && ptra) { __pointer_array(thread)::operator =(::move(ptra)); return *this; }
//
//};


#include "acme/platform/predicate_holder.h"


#include "synchronization_object.h"
#include "synchronization_array.h"
#include "semaphore.h"
#include "mutex.h"
#include "event.h"
#include "set_event_on_exit.h"
#include "critical_section.h"
#include "condition_variable.h"
#include "condition.h"
#include "socket_event.h"
#include "single_lock.h"
//#include "retry_single_lock.h"
#include "initial_single_lock.h"
#include "synchronous_lock.h"
#include "multiple_lock.h"
//#include "retry_multi_lock.h"

//#include "synch_index_ptr_array.h"
//#include "synch_index_iterator.h"


#ifdef ___ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "_impl.h"
#undef _AFXMT_INLINE
#endif


#include "manual_reset_event.h"


//#include "acme/parallelization/sync_method.h"


//#include "acme/parallelization/sync_future.h"


#include "acme/parallelization/task.h"


#include "synchronized_task.h"

//
//#ifdef WINDOWS
//#include <Winsvc.h>
//#endif

//#include "service_status.h"
#include "thread_os.h"


#include "create_thread.h"


//#include "service/thread_pool.h"

namespace windowing
{

   class window;

} // namespace windowing



//CLASS_DECL_ACME u32 random_processor_index_generator();

CLASS_DECL_ACME int_bool post_message(::windowing::window * pwindow, const ::id & id, wparam wparam, lparam lparam);




// namespace parallelization
// {


//    CLASS_DECL_ACME void os_tls_init();

//    CLASS_DECL_ACME void os_tls_term();

//    CLASS_DECL_ACME void os_tls_set(void * p);

//    CLASS_DECL_ACME void * os_tls_get();


// } // namespace parallelization


class thread;


//namespace parallelization
//{


   //CLASS_DECL_ACME bool task_registered(::task * ptask);
   //CLASS_DECL_ACME bool task_id_registered(itask_t id);

   //CLASS_DECL_ACME void task_register(itask_t itask, ::task * ptask);

   //CLASS_DECL_ACME void task_unregister(itask_t itask, ::task * ptask);


//} // namespace parallelization


//
//
//   void finish(::thread* pthread);
//
//
//} // namespace parallelization


//#define Thrd(pcontext)
//#define Thread

CLASS_DECL_ACME::task* get_task();
//CLASS_DECL_ACME ::thread* get_thread();
//CLASS_DECL_ACME ::thread* get_task(itask_t idthread);
CLASS_DECL_ACME void set_task(task * ptask OBJ_REF_DBG_COMMA_PARAMS);
CLASS_DECL_ACME void thread_release(OBJ_REF_DBG_PARAMS);


//typedef bool task_sleep(millis millis, ::synchronization_object* psync);
//using PFN_task_sleep = task_sleep*;

CLASS_DECL_ACME bool __simple_task_sleep();
CLASS_DECL_ACME bool __simple_task_sleep(millis millis);
CLASS_DECL_ACME bool __simple_task_sleep(::synchronization_object* psync);
CLASS_DECL_ACME bool __simple_task_sleep(millis millis, ::synchronization_object* psync);
CLASS_DECL_ACME bool task_sleep(millis millis = U32_INFINITE_TIMEOUT, ::synchronization_object * psync = nullptr);
//CLASS_DECL_ACME bool acme_task_sleep(millis millis = U32_INFINITE_TIMEOUT, ::synchronization_object* psync = nullptr);
//CLASS_DECL_ACME void set_taskhread_sleep(PFN_task_sleep pfnThreadSleep);

#ifdef _UWP

#include "acme/os/uwp/parallelization_winrt.h"

#endif


string get_thread_name(htask_t hthread);

#include "acme/primitive/collection/runnable_array.h"



typedef string GET_THREAD_NAME(::thread* pthread);

using LPFN_GET_THREAD_NAME = GET_THREAD_NAME*;

CLASS_DECL_ACME void set_get_thread_name(LPFN_GET_THREAD_NAME);
string get_thread_name(::thread* pthread);

CLASS_DECL_ACME void thread_name_abbreviate(string & strName, int len);

CLASS_DECL_ACME bool set_thread_name(htask_t hthread, const char * psz);
CLASS_DECL_ACME bool set_thread_name(const char * psz);

//#include "update_task_item_array.h"






CLASS_DECL_ACME bool __task_sleep(task* task);

CLASS_DECL_ACME bool __task_sleep(task* ptask, millis millis);

CLASS_DECL_ACME bool __task_sleep(::task* ptask, synchronization_object* psync);

CLASS_DECL_ACME bool __task_sleep(task* ptask, millis millis, synchronization_object* psync);

CLASS_DECL_ACME bool task_sleep(millis millis, synchronization_object* psync);


#include "synchronized_routine.h"


#include "synchronized_process.h"


#include "acme/platform/synchronized_predicate_routine.h"



