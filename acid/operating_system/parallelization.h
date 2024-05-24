#pragma once



//typedef ::u32 ::u32;


//CLASS_DECL_ACID ::u64 translate_processor_affinity(int iOrder);


// CLASS_DECL_ACID u32 thread_alloc(void);
// CLASS_DECL_ACID int_bool thread_free(u32 dwIndex);
// CLASS_DECL_ACID void * thread_get_data(u32 dwIndex);
// CLASS_DECL_ACID int_bool thread_set_data(u32 dwIndex,void * pTlsValue);

// CLASS_DECL_ACID void thread_shutdown(void);



CLASS_DECL_ACID void set_main_user_htask(htask_t htask);
CLASS_DECL_ACID void set_main_user_itask(itask_t itask);
CLASS_DECL_ACID htask_t main_user_htask();
CLASS_DECL_ACID itask_t main_user_itask();



