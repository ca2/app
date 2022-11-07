#pragma once

#include "__unicode_character.h"

//#include "__str.h"

//#include "international.h"

#include "_base_impl.h"

#include "_ch_impl.h"

#include "_impl_prio.h"

//#include "_str_impl.h"

#include "_refactor_impl.h"

#include "__sz_impl.h"

#include "__unicode_impl.h"

#include "_impl.h"

#include "_c_impl.h"

#include "acme/memory/malloc.h"

template < typename POINTER >
inline ::string __string(const ::acme::memory_allocate < POINTER > & memoryallocpointer)
{

   string str;

   str.assign(memoryallocpointer.m_p, memoryallocpointer.m_iSize);

   return str;

}




