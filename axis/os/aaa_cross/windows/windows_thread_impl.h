#pragma once


CLASS_DECL_AXIS ithread_t get_current_ithread();


#ifdef __cplusplus

CLASS_DECL_AXIS void * __thread_get_data(ithread_t thread,u32 dwIndex);
CLASS_DECL_AXIS int_bool __thread_set_data(ithread_t thread,u32 dwIndex,void * lpTlsValue);

#endif


void __node_init_cross_windows_threading();


void __node_term_cross_windows_threading();






