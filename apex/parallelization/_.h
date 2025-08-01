#pragma once


#include "common.h"


//#ifdef __APPLE__
//#include <semaphore.h>
//#endif





// LPVOID thread_data_get(thread_data_index dataindex);
// int_bool thread_data_set(thread_data_index dataindex, void* pvalue);


// thread_data_index thread_data_allocate();
// int_bool thread_data_free(thread_data_index dataindex);


//extern thread_local ::pointer<::property_set>t_ppropertyset;


//CLASS_DECL_APEX void main_branch(::element * pelementTask, enum_priority epriority);


//::property_set& _thread_property_set();
//
//
//::property_set & thread_property_set();
//
//
//#if defined(__ANDROID__)
//
//
////#define MUTEX_COND_TIMED
//#undef MUTEX_NAMED_POSIX // as of 2016-11-26
//// not implemented (err=38) on android-19 (POSIX semaphore)
//#define MUTEX_NAMED_FD
//#undef MUTEX_NAMED_VSEM
//
//#elif defined(__APPLE__)
//
////#define MUTEX_COND_TIMED
//#undef MUTEX_NAMED_POSIX
//#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#undef MUTEX_NAMED_VSEM
//
//#elif defined(LINUX)
//
////#define MUTEX_COND_TIMED
//#undef MUTEX_NAMED_POSIX
//#undef MUTEX_NAMED_FD
//#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
////#define MUTEX_NAMED_VSEM // psystem V Semaphore
//#undef MUTEX_NAMED_VSEM
//
//#endif
//
//
//
//class synchronization;
//class semaphore;
////class ::pointer < ::mutex >;
//class happening;
//class critical_section;
//class single_lock;
//class multi_lock;
//

//CLASS_DECL_APEX void __call(::particle * pparticle);


//
//namespace parallelization
//{
//
//
//   namespace array
//   {
//
//      template < typename ARRAY >
//      ::pointer<::object>is_running(ARRAY & array, const ::scoped_string & scopedstrTag)
//      {
//
//         for (::collection::index i = 0; i < array.get_size(); i++)
//         {
//
//            ::pointer<::object>pparticle;
//
//            pparticle = &__typed(array[i]);
//
//            if (pparticle && pparticle->is_thread())
//            {
//
//               if (pparticle->task_get_run())
//               {
//
//                  if (pparticle->get_tag().compare(scopedstrTag) == 0)
//                  {
//
//                     return pparticle;
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
//


//CLASS_DECL_APEX bool task_set_name(const ::scoped_string & scopedstr);
//CLASS_DECL_APEX bool task_set_name(htask htask, const ::scoped_string & scopedstrName);

// Use instead of PostQuitMessage in OLE server applications
//CLASS_DECL_APEX void __post_quit_message(int nExitCode);

//typedef void     (*__THREADPROC)(void *);


//CLASS_DECL_APEX bool do_events();
//CLASS_DECL_APEX bool do_events(const class time & time);

class tool_task;
class task_tool;
class thread_tools;
//class thread_toolset;
//class predicate_set;
//class replace_thread;

namespace user
{


   class interaction;


} // namespace user

//using user_interaction_ptr_array = address_array < ::user::interaction * >;

class thread_startup;

//
//namespace parallelization
//{
//
//
//   //CLASS_DECL_APEX bool set_priority(enum_priority epriority);
//
//   //CLASS_DECL_APEX int priority();
//
//
//   //inline int get_priority_none()
//   //{
//
//   //   return e_priority_none;
//
//   //}
//
//
//   //inline int get_priority_normal()
//   //{
//
//   //   return e_priority_normal;
//
//   //}
//
//
//} // namespace parallelization

//
//class sync_interface;
//class synchronous_lock;
//



//#include "predicate_holder.h"

//#include "synchronization.h"
//#include "synchronization_array.h"
//#include "semaphore.h"
//#include "::pointer < ::mutex >.h"
//#include "happening.h"
//#include "set_event_on_exit.h"
//#include "condition.h"
//#include "file_change_event.h"
//#include "socket_event.h"
//#include "critical_section.h"
//#include "single_lock.h"
//#include "retry_single_lock.h"
//#include "initial_single_lock.h"
//#include "synchronous_lock.h"
//#include "multi_lock.h"
//#include "retry_multi_lock.h"

//#include "synch_index_ptr_array.h"
//#include "synch_index_iterator.h"

//
//#ifdef ___ENABLE_INLINES
//#define inline inline
//#include "_impl.h"
//#undef inline
//#endif


//#include "manual_reset_happening.h"


//#include "sync_task.h"


//#ifdef WINDOWS
//#include <Winsvc.h>
//#endif

//#include "service_status.h"
//#include "thread_os.h"

//
//#include "create_thread.h"


//#include "service/pool.h"





//CLASS_DECL_APEX unsigned int random_processor_index_generator();


//CLASS_DECL_APEX int_bool post_message(::windowing::window * pwindow, ::enum_message emessage, ::wparam wparam, ::lparam lparam);




// namespace parallelization
// {


//    CLASS_DECL_APEX void os_tls_init();

//    CLASS_DECL_APEX void os_tls_term();

//    CLASS_DECL_APEX void os_tls_set(void * p);

//    CLASS_DECL_APEX void * os_tls_get();


// } // namespace parallelization


//CLASS_DECL_APEX ::thread* get_task();
//CLASS_DECL_APEX ::thread * get_task(itask idthread);
//CLASS_DECL_APEX void set_thread(thread * pthread);




//#ifdef UNIVERSAL_WINDOWS
//
//#include "apex/os/universal_windows/multitasking_winrt.h"
//
//#endif


CLASS_DECL_ACME string get_task_name(htask htask);


// Use instead of PostQuitMessage in OLE server applications
//CLASS_DECL_APEX void __post_quit_message(int nExitCode);


//#if !defined(UNIVERSAL_WINDOWS)
//
//
//
//inline void main_async(const ::procedure & procedure, enum_priority epriority = e_priority_normal)
//{
//
//   main_branch(routine, epriority);
//
//}
//
//
//#endif





