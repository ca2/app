#pragma once


using hthread_t = void *;


using ithread_t = iptr;


using thread_data_index = ::u32;


CLASS_DECL_ACME int ithread_equals(ithread_t a, ithread_t b);


CLASS_DECL_ACME int hthread_equals(ithread_t a, ithread_t b);


#define null_hthread ((hthread_t)0)


#define null_ithread ((ithread_t)0)



