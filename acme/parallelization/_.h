// Created by camilo on 2022-10-22 19:56 <3ThomasBorregaardSorensen!!
#pragma once


#if defined(ANDROID)


//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(__APPLE__) || defined(__BSD__)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
#undef MUTEX_NAMED_VSEM

#elif defined(LINUX)

//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX
#undef MUTEX_NAMED_FD
#define MUTEX_NAMED_FD // File Descriptor "Semaphore"
//#define MUTEX_NAMED_VSEM // system() V Semaphore
#undef MUTEX_NAMED_VSEM

#endif

CLASS_DECL_ACME bool task_get_run();

CLASS_DECL_ACME::task * get_task();

CLASS_DECL_ACME void __call(const ::procedure & procedure);


//CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function);


//CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure);




CLASS_DECL_ACME bool predicate_Sleep(int iTime, ::function < bool(void) > functionOkToSleep);

CLASS_DECL_ACME void preempt();

CLASS_DECL_ACME void preempt(const class time & time);

CLASS_DECL_ACME bool is_single_main_user_thread();

CLASS_DECL_ACME bool is_main_thread();

CLASS_DECL_ACME itask_t main_itask();

CLASS_DECL_ACME htask_t main_htask();

CLASS_DECL_ACME itask_t current_itask();

CLASS_DECL_ACME htask_t current_htask();

CLASS_DECL_ACME itask_t as_itask(htask_t htask);

CLASS_DECL_ACME void set_main_thread();

CLASS_DECL_ACME void set_main_htask(htask_t htask);

CLASS_DECL_ACME void set_main_itask(itask_t itask);

CLASS_DECL_ACME void preempt();

CLASS_DECL_ACME bool task_sleep(const class time & timeWait);

CLASS_DECL_ACME bool task_get_run();

#ifdef WINDOWS_DESKTOP

CLASS_DECL_ACME void attach_thread_input_to_main_thread(bool bAttach);

#endif


namespace parallelization
{


   class queue;


   CLASS_DECL_ACME bool set_priority(enum_priority epriority);

   CLASS_DECL_ACME bool set_priority(htask_t htask, enum_priority epriority);

   CLASS_DECL_ACME enum_priority get_priority();

   CLASS_DECL_ACME enum_priority get_priority(htask_t htask);


   //inline int get_priority_none()
   //{

   //   return e_priority_none;

   //}


   //inline int get_priority_normal()
   //{

   //   return e_priority_normal;

   //}


} // namespace parallelization



