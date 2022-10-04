////TBS__<3tbs
//  _start.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 16/09/20.
//  Copyright © 2020 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


#include "acme/include/_acme.h"
#include "acme/version/version.h"
#include "acme/platform/_features.h"
#include "debugbreak/debugbreak.h"
#include "operating_system/platform_setup.h"
#include "setup/debug.h"
#include "operating_system/config.h"
#include "include/_setup.h"


#include "acme/include/_macro.h"
#include "__standard_type.h"
#include "acme/constant/memory_heap.h"
#include "operating_system/types.h"
#include "operating_system/system.h"


#ifdef WINDOWS
#define WINDOWS_API __stdcall
#else
#define WINDOWS_API
#endif


#if defined(_ACME_LIBRARY)
#define CLASS_DECL_ACME  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_ACME  CLASS_DECL_IMPORT
#endif


#ifdef _UWP
#define INLINE_CLASS_DECL_ACME CLASS_DECL_ACME
#else
#define INLINE_CLASS_DECL_ACME
#endif



#ifdef DEBUG
#ifndef _DEBUG
#define _DEBUG
#endif
#endif


#ifdef _DEBUG
#ifndef __DEBUG
#define __DEBUG
#endif
#else
#define NNDEBUG
#endif

#define CA2_ACME


#define IMPL_OPERATOR_PLUS(type) \
template < typename TYPE > \
type operator + (const TYPE & t) const { auto copy = *this; copy.add(t); return copy; }


#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define TOKEN_AT_LINE(token) TOKENPASTE2(TOKENPASTE2(token, _atLine_), __LINE__)


#define __DEBUG_POWER


#if defined(__cplusplus)

#define DECL_EXTERN_C      extern "C"
#define BEGIN_EXTERN_C      extern "C" {
#define END_EXTERN_C         }

#else

#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C

#endif


#if defined(__cplusplus)

#include <atomic>

#endif





typedef iptr memsize_storage;
typedef iptr strsize_storage;


typedef iptr memsize;
typedef iptr strsize;
typedef i64 filesize;


#if WCHAR_T_SIZE == 16
#define __END_CHARBIT(xxx) __CONCAT(xxx, 16)
#define __MID_CHARBIT(xxx, zzz) __CONCAT3(xxx, 16, zzz)
#elif WCHAR_T_SIZE == 32
#define __END_CHARBIT(xxx) __CONCAT(xxx, 32)
#define __MID_CHARBIT(xxx, zzz) __CONCAT3(xxx, 32, zzz)
#else
#error "Please define WCHAR_T_SIZE"
#endif


#define __found_index(i) ((i) >= 0)
#define __not_found_index(i) ((i) < 0)


#if defined(DEBUG)


#define RELEASE_INLINE


#else


#define RELEASE_INLINE inline


#endif


#define MEMORY_INLINE RELEASE_INLINE


#if defined(FREEBSD)

#define inplace_new_throw_spec throw()
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL

#elif defined(WINDOWS)

//#define inplace_new_throw_spec
#define inplace_new_throw_spec noexcept
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL __cdecl

#elif defined(SOLARIS)

#define inplace_new_throw_spec
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()
#define MEMORY_DECL

#elif defined(LINUX)
#define inplace_new_throw_spec noexcept
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL

#elif defined(__APPLE__)

#define inplace_new_throw_spec throw()
#define new_throw_spec
#define del_throw_spec throw()
#define MEMORY_DECL

#elif defined(ANDROID)

#define inplace_new_throw_spec noexcept
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL

#else

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec
#define MEMORY_DECL

#endif


#if defined(DEBUG) && !defined(NO_ACME_MEMORY_MANAGEMENT)
#define memory_new new(__FILE__, __LINE__)
#else
#define memory_new new
#endif


#include "_forward_declaration.h"



