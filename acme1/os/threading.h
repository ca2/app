#pragma once


typedef ::u32 uint32;


#ifdef WINDOWS


typedef HANDLE HTHREAD;

typedef uint32 ITHREAD;


#define NULL_HTHREAD ((HTHREAD)0)
#define NULL_ITHREAD ((ITHREAD)0)


inline int ithread_equals(ITHREAD a, ITHREAD b) {return a==b;}

#else



#define HTHREAD pthread_t

#define ITHREAD pthread_t

#define NULL_HTHREAD ((HTHREAD)0)
#define NULL_ITHREAD ((ITHREAD)0)

inline int ithread_equals(ITHREAD a, ITHREAD b) { return pthread_equal(a, b); }


#endif




// CLASS_DECL_ACME u32 thread_alloc(void);
// CLASS_DECL_ACME int_bool thread_free(u32 dwIndex);
// CLASS_DECL_ACME void * thread_get_data(u32 dwIndex);
// CLASS_DECL_ACME int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_ACME void thread_shutdown(void);



CLASS_DECL_ACME void set_main_hthread(HTHREAD hthread);
CLASS_DECL_ACME void set_main_ithread(ITHREAD ithread);
CLASS_DECL_ACME HTHREAD get_main_hthread(void);
CLASS_DECL_ACME ITHREAD get_main_ithread(void);

