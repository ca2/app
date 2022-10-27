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

