#pragma once



class single_lock;







#ifdef __APPLE__
#include <semaphore.h>
#endif




class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class manual_reset_event;
class single_lock;
class multi_lock;







//class predicate_holder_base :
//   virtual public matter
//{
//public:
//
//   predicate_holder_base(::particle * pparticle) :
//      ::matter(pparticle),
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
//      ::matter(pparticle),
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

namespace primitive
{

   class command;

} // namespace primitive


//namespace exception
//{
//
//
//   class exception;
//   class base;
//
//
//} // namespace exception



//CLASS_DECL_ACME thread* __begin_thread(::particle * pparticle, __THREADPROC pfnThreadProc, LPVOID pParam, i32 epriority = ::e_priority_normal, ::u32 nStackSize = 0, u32 dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr, itask_t * puiId = nullptr, error * perror = nullptr);
