#pragma once


CLASS_DECL_ACME itask_t get_current_ithread();


#ifdef __cplusplus

CLASS_DECL_ACME void * __thread_get_data(itask_t thread,u32 dwIndex);
CLASS_DECL_ACME int_bool __thread_set_data(itask_t thread,u32 dwIndex,void * lpTlsValue);

#endif


// CLASS_DECL_ACME void __node_init_cross_windows_threading();


// CLASS_DECL_ACME void __node_term_cross_windows_threading();






