// Created by camilo on 2022-10-22 19:56 <3ThomasBorregaardSorensen!!
#pragma once


#if defined(ANDROID)


//#define MUTEX_COND_TIMED
#undef MUTEX_NAMED_POSIX // as of 2016-11-26
// not implemented (err=38) on android-19 (POSIX semaphore)
#define MUTEX_NAMED_FD
#undef MUTEX_NAMED_VSEM

#elif defined(__APPLE__) || defined(FREEBSD) || defined(OPENBSD)

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

CLASS_DECL_ACID bool task_get_run();

CLASS_DECL_ACID::task * get_task();

CLASS_DECL_ACID void __call(const ::procedure & procedure);


//CLASS_DECL_ACID bool main_synchronous(const class time & time, const ::procedure & function);


//CLASS_DECL_ACID void main_asynchronous(const ::procedure & procedure);




CLASS_DECL_ACID bool predicate_Sleep(int iTime, ::function < bool(void) > functionOkToSleep);

CLASS_DECL_ACID void preempt();

CLASS_DECL_ACID void preempt(const class time & time);

CLASS_DECL_ACID bool is_single_main_user_thread();

CLASS_DECL_ACID bool is_main_thread();

CLASS_DECL_ACID itask_t main_user_itask();

CLASS_DECL_ACID itask_t current_itask();

CLASS_DECL_ACID htask_t current_htask();

CLASS_DECL_ACID itask_t as_itask(htask_t htask);

CLASS_DECL_ACID void set_main_user_thread();

CLASS_DECL_ACID void set_main_user_thread(htask_t htask);

CLASS_DECL_ACID void preempt();

CLASS_DECL_ACID bool task_sleep(const class time & timeWait);

CLASS_DECL_ACID bool task_get_run();



namespace parallelization
{


   class queue;


   CLASS_DECL_ACID bool set_priority(enum_priority epriority);

   CLASS_DECL_ACID bool set_priority(htask_t htask, enum_priority epriority);

   CLASS_DECL_ACID enum_priority get_priority();

   CLASS_DECL_ACID enum_priority get_priority(htask_t htask);


   //inline i32 get_priority_none()
   //{

   //   return e_priority_none;

   //}


   //inline i32 get_priority_normal()
   //{

   //   return e_priority_normal;

   //}


} // namespace parallelization



