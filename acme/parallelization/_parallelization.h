#pragma once


class task;


CLASS_DECL_ACME ::task* get_task();

CLASS_DECL_ACME bool task_get_run();


inline void preempt();


CLASS_DECL_ACME itask_t get_current_itask();

CLASS_DECL_ACME htask_t get_current_htask();



CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder);
CLASS_DECL_ACME bool is_single_main_user_thread();


CLASS_DECL_ACME bool is_main_thread();


CLASS_DECL_ACME itask_t get_main_user_itask();


#ifdef PARALLELIZATION_PTHREAD


#if defined(ANDROID)


//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(__APPLE__)

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

#elif defined(FREEBSD)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // get_system() V Semaphore
#undef MUTEX_NAMED_VSEM

#else

#error "Operating system not supported..."

#endif

#endif


class synchronization_object;
class semaphore;
class event;
class critical_section;
class single_lock;
class multi_lock;


CLASS_DECL_ACME void __call(const ::procedure & procedure);


CLASS_DECL_ACME bool main_synchronous(const ::duration & duration, ::procedure function);


CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure);


//namespace parallelization
//{
//
//
//   namespace array
//   {
//
//      template < typename ARRAY >
//      ::pointer<::matter>is_running(ARRAY & array, const char * pszTag)
//      {
//
//         for (::index i = 0; i < array.get_size(); i++)
//         {
//
//            ::pointer<::matter>pobject;
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



CLASS_DECL_ACME void task_set_name(const char * psz);
CLASS_DECL_ACME void task_set_name(htask_t htask, const char* pszName);


CLASS_DECL_ACME string task_get_name();
CLASS_DECL_ACME string task_get_name(htask_t htask);



typedef void     (*__THREADPROC)(void *);



class tool_task;
class task_tool;
class thread_tools;
//class thread_toolset;
//class predicate_set;
//class replace_thread;


class thread_startup;


namespace parallelization
{


   CLASS_DECL_ACME bool set_priority(enum_priority epriority);

   CLASS_DECL_ACME bool set_priority(htask_t htask, enum_priority epriority);

   CLASS_DECL_ACME enum_priority get_priority();

   CLASS_DECL_ACME enum_priority get_priority(htask_t htask);


   //inline i32 get_priority_none()
   //{

   //   return e_priority_none;

   //}


   //inline i32 get_priority_normal()
   //{

   //   return e_priority_normal;

   //}


} // namespace parallelization


class sync_interface;
class synchronous_lock;
class _synchronous_lock;


//class CLASS_DECL_ACME thread_ptra :
//   virtual public pointer_array < thread >
//{
//public:
//
//
//   thread_ptra();
//   thread_ptra(const thread_ptra & ptra):pointer_array < thread >(ptra) {}
//   thread_ptra(thread_ptra && ptra) :pointer_array < thread >(::move(ptra)) {}
//   virtual ~thread_ptra();
//
//   virtual ::count get_count_except_current_thread();
//   virtual void finish();
//   virtual void wait(const duration & duration, ::synchronous_lock & synchronouslock);
//
//   thread_ptra & operator = (const thread_ptra & ptra) { pointer_array < thread >::operator =(ptra); return *this; }
//   thread_ptra & operator = (thread_ptra && ptra) { pointer_array < thread >::operator =(::move(ptra)); return *this; }
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
//#include "multiple_lock.h"
//#include "retry_multi_lock.h"

//#include "synch_index_ptr_array.h"
//#include "synch_index_iterator.h"


CLASS_DECL_ACME ::pointer<mutex>open_mutex(::matter * pmatter, const char * lpszName);


#ifdef ___ENABLE_INLINES
#define _AFXMT_INLINE inline
#include "_impl.h"
#undef _AFXMT_INLINE
#endif


#include "manual_reset_event.h"


#include "counter.h"


#include "acme/platform/implementable.h"


#include "acme/parallelization/task.h"


#include "acme/parallelization/task_keep.h"


#include "acme/parallelization/task_payload.h"


namespace windowing
{

   class window;

} // namespace windowing


CLASS_DECL_ACME void post_message(::windowing::window * pwindow, const ::atom & atom, wparam wparam, lparam lparam);


class thread;



CLASS_DECL_ACME::task* get_task();
CLASS_DECL_ACME void set_task(task * ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);
CLASS_DECL_ACME void thread_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);



#ifdef __cplusplus_winrt

#include "acme/operating_system/universal_windows/parallelization_winrt.h"

#endif


string get_task_name(htask_t htask);


typedef string GET_THREAD_NAME(::thread* pthread);

using LPFN_GET_THREAD_NAME = GET_THREAD_NAME*;

CLASS_DECL_ACME void set_get_thread_name(LPFN_GET_THREAD_NAME);
string get_task_name(::thread* pthread);

CLASS_DECL_ACME void thread_name_abbreviate(string & strName, int len);


CLASS_DECL_ACME::mutex& message_dispatch_mutex();



#ifdef WINDOWS

inline bool wait(synchronization_object* psync, const duration& duration = duration::infinite())
{
   return psync->wait(duration);
}

void wait(i32 numberOfItems, synchronization_object* psync, const duration& duration = duration::infinite(), bool waitForAll = false);

#else

void wait(synchronization_object* psynchronizationobject, const duration& duration = duration::infinite());

void wait(size_t numberOfItems, synchronization_object** psynchronizationobject, const duration& duration = duration::infinite(), bool waitForAll = false);

#endif




//CLASS_DECL_ACME bool __task_sleep(task* task);
//
//CLASS_DECL_ACME bool __task_sleep(task* ptask, ::duration ::duration);
//
//CLASS_DECL_ACME bool __task_sleep(::task* ptask, synchronization_object* psync);
//
//CLASS_DECL_ACME bool __task_sleep(task* ptask, ::duration ::duration, synchronization_object* psync);
//
//CLASS_DECL_ACME bool task_sleep(const ::duration & duration, synchronization_object* psync);
CLASS_DECL_ACME bool task_sleep(const class ::wait & wait);


//#include "synchronized_routine.h"


#include "synchronized_process.h"


#include "acme/primitive/promise/signalization.h"


#include "acme/platform/synchronized_predicate_routine.h"





