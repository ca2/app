#pragma once


class thread;


class task_pool;


using htask_t = void *;


using itask_t = iptr;


using thread_data_index = ::u32;


CLASS_DECL_ACME int itask_equals(itask_t a, itask_t b);


CLASS_DECL_ACME int htask_equals(itask_t a, itask_t b);


#define null_htask ((htask_t)0)


#define null_itask ((itask_t)0)



