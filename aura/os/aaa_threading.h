#pragma once


typedef ::u32 ::u32;






// CLASS_DECL_AURA u32 thread_alloc(void);
// CLASS_DECL_AURA int_bool thread_free(u32 dwIndex);
// CLASS_DECL_AURA void * thread_get_data(u32 dwIndex);
// CLASS_DECL_AURA int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_AURA void thread_shutdown(void);



CLASS_DECL_AURA void set_main_hthread(hthread_t hthread);
CLASS_DECL_AURA void set_main_ithread(ithread_t ithread);
CLASS_DECL_AURA hthread_t get_main_hthread(void);
CLASS_DECL_AURA ithread_t get_main_ithread(void);

