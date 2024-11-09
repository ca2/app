#pragma once



class single_lock;







#ifdef __APPLE__
#include <semaphore.h>
#endif




//class sync_object;
class semaphore;
class mutex;
class event;
class critical_section;
class manual_reset_happening;
class single_lock;
class multiple_lock;







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



//CLASS_DECL_ACME thread* __begin_thread(::particle * pparticle, __THREADPROC pfnThreadProc, LPVOID pParam, int epriority = ::e_priority_normal, unsigned int nStackSize = 0, unsigned int dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = nullptr, itask_t * puiId = nullptr, error * perror = nullptr);
