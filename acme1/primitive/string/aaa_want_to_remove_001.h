#pragma once





#if defined(SOLARIS)
#include <atomic.h>
#if defined(OS64BIT)
#define _gen_InterlockedIncrement(ptr) atomic_inc_64(ptr)
#define _gen_InterlockedDecrement(ptr) atomic_dec_64(ptr)
#else
#define _gen_InterlockedIncrement(ptr) atomic_inc_32((volatile u32 *) ptr)
#define _gen_InterlockedDecrement(ptr) atomic_dec_32((volatile u32 *) ptr)
#endif
#elif defined(LINUX) || defined(APPLEOS) || defined(ANDROID)
#if (defined(RASPBIAN)) && defined(OS32BIT)
#define _gen_InterlockedIncrement(ptr) __sync_add_and_fetch_4(ptr, 1)
#define _gen_InterlockedDecrement(ptr) __sync_sub_and_fetch_4(ptr, 1)
#else
#define _gen_InterlockedIncrement(ptr) __sync_add_and_fetch(ptr, 1)
#define _gen_InterlockedDecrement(ptr) __sync_sub_and_fetch(ptr, 1)
#endif
#else
#ifdef _M_IX86
#ifndef _M_CEE
#define _gen_InterlockedIncrement InterlockedIncrement
#define _gen_InterlockedDecrement InterlockedDecrement
#else
#define _gen_InterlockedIncrement InterlockedIncrement
#define _gen_InterlockedDecrement InterlockedDecrement
/* managed code must use the non-intrinsics */
#ifdef InterlockedIncrement
#undef InterlockedIncrement
#endif
#ifdef InterlockedDecrement
#undef InterlockedDecrement
#endif
#endif  // !_M_CEE
#else
#define _gen_InterlockedIncrement InterlockedIncrement
#define _gen_InterlockedDecrement InterlockedDecrement
#endif  // _M_IX86_
#endif // ! LINUX


