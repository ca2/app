#pragma once



typedef ::u32 uint32;





// CLASS_DECL_ACME u32 thread_alloc(void);
// CLASS_DECL_ACME int_bool thread_free(u32 dwIndex);
// CLASS_DECL_ACME void * thread_get_data(u32 dwIndex);
// CLASS_DECL_ACME int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_ACME void thread_shutdown(void);



CLASS_DECL_ACME void set_main_hthread(HTHREAD hthread);
CLASS_DECL_ACME void set_main_ithread(ITHREAD ithread);
CLASS_DECL_ACME HTHREAD get_main_hthread(void);
CLASS_DECL_ACME ITHREAD get_main_ithread(void);






