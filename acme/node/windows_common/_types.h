#pragma once





#ifdef WINDOWS

typedef u32 ithread_t;
typedef ::u32 thread_data_index;

#else

using thread_data_index = ::u32;

#endif


#ifdef WINDOWS


typedef iptr hthread_t;

//typedef ::u32 ithread_t;


#define null_hthread ((hthread_t)0)
#define null_ithread ((ithread_t)0)


inline int ithread_equals(ithread_t a, ithread_t b) { return a == b; }

#else



#define hthread_t pthread_t

#define ithread_t pthread_t

#define null_hthread ((hthread_t)0)
#define null_ithread ((ithread_t)0)

inline int ithread_equals(ithread_t a, ithread_t b) { return pthread_equal(a, b); }


#endif

