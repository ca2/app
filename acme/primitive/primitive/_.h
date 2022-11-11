#pragma once


#include "acme/user/user/_constant_key.h"


#if OBJECT_REFERENCE_COUNT_DEBUG


template < typename TYPE, typename T >
void assign(::pointer<TYPE>& ptr, T * p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < typename TYPE >
void release(::pointer<TYPE>& ptr OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);

template < typename TYPE >
void release(TYPE *& p OBJECT_REFERENCE_COUNT_DEBUG_COMMA_PARAMS);


#endif


namespace acme
{

   CLASS_DECL_ACME void transfer_to(::file::file * pfileOut, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from_begin(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);

   CLASS_DECL_ACME void transfer_from(::file::file * pfileIn, memory_base & mem, memsize uiBufferSize = 1024 * 1024);


} // namespace acme

