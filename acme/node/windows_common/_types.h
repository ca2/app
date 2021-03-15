#pragma once





#ifdef WINDOWS

typedef u32 itask_t;
typedef ::u32 thread_data_index;

#else

using thread_data_index = ::u32;

#endif


#ifdef WINDOWS


typedef iptr htask_t;

//typedef ::u32 itask_t;


#define null_hthread ((htask_t)0)
#define null_ithread ((itask_t)0)


inline int ithread_equals(itask_t a, itask_t b) { return a == b; }

#else



#define htask_t pthread_t

#define itask_t pthread_t

#define null_hthread ((htask_t)0)
#define null_ithread ((itask_t)0)

inline int ithread_equals(itask_t a, itask_t b) { return pthread_equal(a, b); }


#endif

