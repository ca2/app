#pragma once


CLASS_DECL_AURA itask_t get_current_ithread();


#ifdef __cplusplus

CLASS_DECL_AURA void * __thread_get_data(itask_t thread,u32 dwIndex);
CLASS_DECL_AURA int_bool __thread_set_data(itask_t thread,u32 dwIndex,void * lpTlsValue);

#endif


void __node_init_cross_windows_threading();


void __node_term_cross_windows_threading();






