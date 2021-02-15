#pragma once



class single_lock;





#ifdef WINDOWS

typedef u32 ithread_t;
typedef ::u32 thread_data_index;

#else

using thread_data_index = ::u32;

#endif



#ifdef APPLEOS
#include <semaphore.h>
#endif


#if defined(ANDROID)


#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(APPLEOS)

#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
#undef MUTEX_NAMED_VSEM

#elif defined(LINUX)

#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // System V Semaphore
#undef MUTEX_NAMED_VSEM

#endif


class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class manual_reset_event;
class single_lock;
class multi_lock;





//typedef ::u32(c_cdecl *__THREADPROC)(LPVOID);


CLASS_DECL_APEX bool do_events();
//CLASS_DECL_APEX bool do_events(const duration & duration);


//
//namespace parallelization
//{
//
//
//   CLASS_DECL_APEX bool set_priority(::e_priority epriority);
//
//   CLASS_DECL_APEX ::e_priority priority();
//
//
//   inline i32 get_priority_none()
//   {
//
//      return priority_none;
//
//   }
//
//
//   inline i32 get_priority_normal()
//   {
//
//      return priority_normal;
//
//   }
//
//
//} // namespace parallelization
//
//
//
//
//
//
//
//namespace user
//{
//
//
//   class frame_array;
//
//
//} // namespace user
//



//class predicate_holder_base :
//   virtual public object
//{
//public:
//
//   predicate_holder_base(::layered * pobjectContext) :
//      ::object(pobject),
//      m_pholdref(pholdref)
//   {
//
//   }
//
//   virtual void run() {}
//
//};

//template < typename PRED >
//class predicate_holder :
//   virtual public predicate_holder_base
//{
//public:
//
//   PRED m_predicate;
//
//   predicate_holder(::object * pobject, PRED pred) :
//      ::object(pobject),
//      predicate_holder_base(pobject),
//      m_predicate(pred)
//   {
//
//   }
//
//   virtual void run() { m_predicate(); }
//
//};

//class user_interaction_ptr_array;

class thread_startup;

namespace primitive
{

   class command;

} // namespace primitive


namespace exception
{


   class exception;
   class base;


} // namespace exception



//CLASS_DECL_APEX thread* __begin_thread(::object * pobject, __THREADPROC pfnThreadProc, LPVOID pParam, i32 epriority = ::priority_normal, ::u32 nStackSize = 0, u32 dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr, ithread_t * puiId = nullptr, error * perror = nullptr);
