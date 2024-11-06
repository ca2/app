#pragma once



class single_lock;





//#ifdef WINDOWS
//
//typedef unsigned int itask_t;
//typedef unsigned int thread_data_index;
//
//#else
//
//using thread_data_index = unsigned int;
//
//#endif



// #ifdef __APPLE__
// #include <semaphore.h>
// #endif


// #if defined(ANDROID)


// #define MUTEX_COND_TIMED
// #undef MUTEX_NAMED_POSIX // as of 2016-11-26
// // not implemented (err=38) on android-19 (POSIX semaphore)
// #define MUTEX_NAMED_FD
// #undef MUTEX_NAMED_VSEM

// #elif defined(__APPLE__)

// #define MUTEX_COND_TIMED
// #undef MUTEX_NAMED_POSIX
// #define MUTEX_NAMED_FD // File Descriptor "Semaphore"
// #undef MUTEX_NAMED_VSEM

// #elif defined(LINUX)

// #define MUTEX_COND_TIMED
// #undef MUTEX_NAMED_POSIX
// #undef MUTEX_NAMED_FD
// #define MUTEX_NAMED_FD // File Descriptor "Semaphore"
// //#define MUTEX_NAMED_VSEM // psystem V Semaphore
// #undef MUTEX_NAMED_VSEM

// #endif


// class sync_object;
// class semaphore;
// class mutex;
// class event;
// class critical_section;
// class manual_reset_event;
// class single_lock;
// class multi_lock;





//typedef unsigned int(c_cdecl *__THREADPROC)(LPVOID);


//CLASS_DECL_APEX bool do_events();
//CLASS_DECL_APEX bool do_events(const class time & time);


//
//namespace parallelization
//{
//
//
//   CLASS_DECL_APEX bool set_priority(::enum_priority epriority);
//
//   CLASS_DECL_APEX ::enum_priority priority();
//
//
//   inline int get_priority_none()
//   {
//
//      return e_priority_none;
//
//   }
//
//
//   inline int get_priority_normal()
//   {
//
//      return e_priority_normal;
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
//   predicate_holder_base(::particle * pparticle) :
//      ::object(pparticle),
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
//   predicate_holder(::particle * pparticle, PRED pred) :
//      ::object(pparticle),
//      predicate_holder_base(pparticle),
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

namespace prototype
{

   class command;

} // namespace prototype


//namespace exception
//{
//
//
//   class exception;
//   class base;
//
//
//} // namespace exception
//


//CLASS_DECL_APEX thread* __begin_thread(::particle * pparticle, __THREADPROC pfnThreadProc, LPVOID pParam, int epriority = ::e_priority_normal, unsigned int nStackSize = 0, unsigned int dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr, itask_t * puiId = nullptr, error * perror = nullptr);
