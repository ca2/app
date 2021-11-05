#pragma once



//typedef ::u32 ::u32;


CLASS_DECL_ACME ::u64 translate_processor_affinity(int iOrder);


// CLASS_DECL_ACME u32 thread_alloc(void);
// CLASS_DECL_ACME int_bool thread_free(u32 dwIndex);
// CLASS_DECL_ACME void * thread_get_data(u32 dwIndex);
// CLASS_DECL_ACME int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_ACME void thread_shutdown(void);



CLASS_DECL_ACME void set_main_hthread(htask_t htask);
CLASS_DECL_ACME void set_main_ithread(itask_t itask);
CLASS_DECL_ACME htask_t get_main_hthread(void);
CLASS_DECL_ACME itask_t get_main_ithread(void);






