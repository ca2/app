////TBS__<3tbs
//  _start.h
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 16/09/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//  From acid by camilo on 2024-05-22 11:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acid/include/_ace.h"
#include "acid/release/_release.h"
#include "configuration_selection.h"
#include "acid/include/_features.h"
#include "debugbreak.h"
#include "operating_system/platform_setup.h"
#include "configuration/debug.h"
#include "operating_system/configuration.h"
#include "acid/include/_setup.h"


#if REFERENCING_DEBUGGING

#define REFDBG(...) __VA_ARGS__
#define COMMA_REFDBG(...) , REFDBG(__VA_ARGS__)

#else

#define REFDBG(...)
#define COMMA_REFDBG(...)

#endif


#include "__standard_type.h"
#include "acid/include/_operating_system.h"
#include "acid/include/_macro.h"
#include "operating_system/types.h"
#include "operating_system/system.h"
#ifdef	_STDIO_H_
#error "already included?!?! _____ (After including operating_system/system.h)"
#endif


#ifdef WINDOWS
#define WINDOWS_API __stdcall
#else
#define WINDOWS_API
#endif




// From __setup.h by camilo on 2022-11-25 14:53 <3ThomasBorregaardSorensen!!
#ifdef DEBUG
#ifndef _DEBUG
#define _DEBUG 1
#endif
#endif


#ifdef _DEBUG
#ifndef DEBUG
#define DEBUG 1
#endif
#endif


// From __setup.h by camilo on 2022-11-25 14:53 <3ThomasBorregaardSorensen!!
#ifdef _DEBUG
#ifndef __DEBUG
#define __DEBUG
#endif
#else
#define NNDEBUG
#endif


#define CA2_ACE


#if defined(__cplusplus)

//#include <atomic>
#include <initializer_list>
#ifdef	_STDIO_H_
#error "already included?!?! _____ (After including initializer_list)"
#endif
#include <typeinfo>
#ifdef	_STDIO_H_
#error "already included?!?! _____ (After including typeinfo)"
#endif
//#include <tuple>
//#ifdef	_STDIO_H_
//#error "already included?!?! _____ (After including tuple)"
//#endif
#include <type_traits>
#ifdef	_STDIO_H_
#error "already included?!?! _____ (After including type_traits)"
#endif


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

#elif defined(OPENBSD)

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


//#if defined(DEBUG) && !defined(NO_ace_MEMORY_MANAGEMENT)
//#define __new< new >(__FILE__, __LINE__)
//#else
//#define memory_new new
//#endif


#include "acid/include/_c.h"
#include "acid/constant/memory_heap.h"
#include "acid/memory/_new.h"
#ifdef	_STDIO_H_
#error "already included?!?! _____ (After including acid/memory/_new.h)"
#endif


//#include "acid/include/_new.h"
