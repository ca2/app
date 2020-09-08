#pragma once


typedef ::u32 uint32;






// CLASS_DECL_AURA u32 thread_alloc(void);
// CLASS_DECL_AURA int_bool thread_free(u32 dwIndex);
// CLASS_DECL_AURA void * thread_get_data(u32 dwIndex);
// CLASS_DECL_AURA int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_AURA void thread_shutdown(void);



CLASS_DECL_AURA void set_main_hthread(HTHREAD hthread);
CLASS_DECL_AURA void set_main_ithread(ITHREAD ithread);
CLASS_DECL_AURA HTHREAD get_main_hthread(void);
CLASS_DECL_AURA ITHREAD get_main_ithread(void);

