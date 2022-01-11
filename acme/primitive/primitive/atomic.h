//
//  atomic.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//
#pragma once


#ifdef WINDOWS

//// To declare an interlocked function for use as an intrinsic,
//// include intrin.h and put the function in a #pragma intrinsic
//// statement.
#include <intrin.h>


//#pragma intrinsic (_InterlockedIncrement)
//#pragma intrinsic (_InterlockedDecrement)


#endif

#ifdef WINDOWS
  
#define atomic_increment64(pi) _interlockedincrement64((::i64 *) (pi))
  
#else

inline i64 atomic_increment64(i64 * pi)
{


#if defined(RASPBIAN) && defined(OS32BIT)
  
  return __sync_add_and_fetch_4(pi, 1);
  
#else
  
  return __sync_add_and_fetch(pi, 1);
  
#endif
  
}


#endif


#ifdef WINDOWS

#define atomic_increment32(pi) _InterlockedIncrement((long *)(pi))

#else
   
inline i32 atomic_increment32(i32* pi)
{

#if defined(RASPBIAN) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, 1);

#endif

}

#endif



#ifdef WINDOWS
  
   #define atomic_decrement64(pi) _interlockeddecrement64((::i64 *)(pi))
  
#else
   
   inline i64 atomic_decrement64(i64 * pi)
   {
   
#if defined(RASPBIAN) && defined(OS32BIT)
  
      return __sync_sub_and_fetch_4(pi, 1);
  
#else
  
      return __sync_sub_and_fetch(pi, 1);
  
#endif
  
   }

#endif


#ifdef WINDOWS

   #define atomic_decrement32(pi) _InterlockedDecrement((long*)(pi))

#else
   
   inline i32 atomic_decrement32(i32 * pi)
   {

#if defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(pi, 1);

#else

      return __sync_sub_and_fetch(pi, 1);

#endif

   }

#endif



#ifdef WINDOWS

   #define atomic_add64(pi, i) _interlockedadd64((::i64 *)(pi),(::i64) (i))

#else
   
inline i64 atomic_add64(i64* pi, i64 i)
{

#if defined(RASPBIAN) && defined(OS32BIT)

   **return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

   #define atomic_add32(pi, i) _interlockedadd((long *)(pi),(long) (i))

#else

inline i32 atomic_add32(i32* pi, i32 i)
{

#if defined(RASPBIAN) && defined(OS32BIT)

   **return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

#define atomic_subtract64(pi, i) _interlockedadd64((::i64 *)(pi), (::i64) (-(i)))

#else
   
   inline i64 atomic_subtract64(i64* pi, i64 i)
   {

#if defined(RASPBIAN) && defined(OS32BIT)

   **return __sync_sub_and_fetch_4(pi, 1);

#else

   return __sync_sub_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

#define   atomic_subtract32(pi, i) _interlockedadd((long*)(pi), (long)(-(i)))

#else

inline i32 atomic_subtract32(i32* pi, i32 i)
{

#if defined(RASPBIAN) && defined(OS32BIT)
   ** return __sync_sub_and_fetch_4(pi, 1);

#else

   return __sync_sub_and_fetch(pi, i);

#endif

}

#endif



