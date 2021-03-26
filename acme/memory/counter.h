// Created on 2021-03-42 16:35 <3ThomasBS_!!
#pragma once


CLASS_DECL_ACME bool memory_counter_on();

CLASS_DECL_ACME bool initialize_memory_counter(::matter* pmatter);

CLASS_DECL_ACME void _memory_counter_increment(const char* psz);
CLASS_DECL_ACME void _memory_counter_decrement(const char* psz);


///CLASS_DECL_ACME ::file::path memory_counter_base_path(::matter * pmatter);


template < typename T >
const char * memory_counter_id(T* pthis);

template < typename T >
void memory_counter_increment(T* pthis);

template < typename T >
void memory_counter_decrement(T* pthis);




