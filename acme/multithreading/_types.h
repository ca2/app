#pragma once





#ifdef WINDOWS

typedef u32 ITHREAD;
typedef DWORD thread_data_index;

#else

using thread_data_index = ::u32;

#endif


#ifdef WINDOWS


typedef HANDLE HTHREAD;

//typedef uint32 ITHREAD;


#define NULL_HTHREAD ((HTHREAD)0)
#define NULL_ITHREAD ((ITHREAD)0)


inline int ithread_equals(ITHREAD a, ITHREAD b) { return a == b; }

#else



#define HTHREAD pthread_t

#define ITHREAD pthread_t

#define NULL_HTHREAD ((HTHREAD)0)
#define NULL_ITHREAD ((ITHREAD)0)

inline int ithread_equals(ITHREAD a, ITHREAD b) { return pthread_equal(a, b); }


#endif

