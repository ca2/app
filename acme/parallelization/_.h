// Created by camilo on 2022-10-22 19:56 <3ThomasBorregaardSorensen!!
#pragma once


CLASS_DECL_ACME bool task_get_run();



CLASS_DECL_ACME::task * get_task();


CLASS_DECL_ACME void __call(const ::procedure & procedure);


CLASS_DECL_ACME bool main_synchronous(const ::duration & duration, const ::procedure & function);


CLASS_DECL_ACME void main_asynchronous(const ::procedure & procedure);




CLASS_DECL_ACME bool predicate_Sleep(int iTime, ::function < bool(void) > functionOkToSleep);


CLASS_DECL_ACME void preempt();


CLASS_DECL_ACME void preempt(const ::duration & duration);


CLASS_DECL_ACME void preempt(const ::INTEGRAL_SECOND & second);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_MILLISECOND & millisecond);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_MICROSECOND & microsecond);
CLASS_DECL_ACME void preempt(const ::INTEGRAL_NANOSECOND & nanosecond);


CLASS_DECL_ACME void precision_wait(const ::duration & duration);






//CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder);


typedef string GET_TASK_NAME(::task * ptask);
using LPFN_GET_TASK_NAME = GET_TASK_NAME*;


CLASS_DECL_ACME string get_task_name(htask_t htask);

CLASS_DECL_ACME void set_get_task_name(LPFN_GET_TASK_NAME);

CLASS_DECL_ACME void task_set_name(const char * psz);
CLASS_DECL_ACME void task_set_name(htask_t htask, const char* pszName);


CLASS_DECL_ACME string task_get_name();
CLASS_DECL_ACME string task_get_name(htask_t htask);


CLASS_DECL_ACME void thread_name_abbreviate(string & strName, int len);

CLASS_DECL_ACME bool is_single_main_user_thread();

CLASS_DECL_ACME bool is_main_thread();

CLASS_DECL_ACME itask_t get_main_user_itask();





CLASS_DECL_ACME itask_t get_current_itask();

CLASS_DECL_ACME htask_t get_current_htask();


CLASS_DECL_ACME void preempt();




CLASS_DECL_ACME bool task_sleep(const class ::wait & wait);

CLASS_DECL_ACME bool task_get_run();


CLASS_DECL_ACME void task_release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


CLASS_DECL_ACME ::task* get_task();

//CLASS_DECL_ACME::task* get_task();
CLASS_DECL_ACME void set_task(task * ptask OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

CLASS_DECL_ACME string get_task_name(::task * ptask);






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



