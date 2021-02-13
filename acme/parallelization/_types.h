#pragma once





#ifdef WINDOWS

typedef u32 ithread_t;
typedef ::u32 thread_data_index;

#else

using thread_data_index = ::u32;

#endif


#ifdef WINDOWS


using hthread_t = void *;

//typedef ::u32 ithread_t;


#define NULL_HTHREAD ((hthread_t)0)
#define NULL_ITHREAD ((ithread_t)0)


inline int ithread_equals(ithread_t a, ithread_t b) { return a == b; }

#else



#define hthread_t pthread_t

#define ithread_t pthread_t

#define NULL_HTHREAD ((hthread_t)0)
#define NULL_ITHREAD ((ithread_t)0)


int ithread_equals(ithread_t a, ithread_t b);


#endif

