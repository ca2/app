// Created by camilo on 2022-10-22 19:56 <3ThomasBorregaardSorensen!!
#pragma once


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
//#define MUTEX_NAMED_VSEM // acmesystem() V Semaphore
#undef MUTEX_NAMED_VSEM

#endif


CLASS_DECL_ACME bool task_get_run();



CLASS_DECL_ACME::task * get_task();


CLASS_DECL_ACME void __call(const ::procedure & procedure);


CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function);


CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure);




CLASS_DECL_ACME bool predicate_Sleep(int iTime, ::function < bool(void) > functionOkToSleep);


CLASS_DECL_ACME void preempt();


CLASS_DECL_ACME void preempt(const class time & time);



//CLASS_DECL_ACME void precision_wait(const class time & time);



CLASS_DECL_ACME bool is_single_main_user_thread();

CLASS_DECL_ACME bool is_main_thread();

CLASS_DECL_ACME itask_t get_main_user_itask();





CLASS_DECL_ACME itask_t get_current_itask();

CLASS_DECL_ACME htask_t get_current_htask();


CLASS_DECL_ACME void preempt();




CLASS_DECL_ACME bool task_sleep(const class time & timeWait);

CLASS_DECL_ACME bool task_get_run();


CLASS_DECL_ACME void task_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);







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



