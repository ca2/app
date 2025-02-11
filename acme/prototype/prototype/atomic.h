//
//  atomic.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 02/06/19.
//
#pragma once


#ifdef WINDOWS

//// To declare an interlocked function for use as an intrinsic,
//// include intrin.h and put the function in a #pragma intrinsic
//// statement.
#include <intrin.h>


#pragma intrinsic (_InterlockedIncrement)
#pragma intrinsic (_InterlockedDecrement)
#pragma intrinsic (_interlockedincrement64)
#pragma intrinsic (_interlockeddecrement64)
#pragma intrinsic (_interlockedadd64)
#pragma intrinsic (_interlockedadd)


#endif

#ifdef WINDOWS

#define atomic_assign64(pi, i) _interlockedexchange64((long long *) (pi), i)

#else

inline long long atomic_assign64(long long * pi, long long i)
{


#if defined(RASPBERRYPIOS) && defined(OS32BIT)
  
  return __sync_lock_test_and_set_4(pi, i);
  
#else
  
  return __sync_lock_test_and_set(pi, i);
  
#endif
  
}


#endif


#ifdef WINDOWS

#define atomic_increment64(pi) _interlockedincrement64((long long *) (pi))
  
#else

inline long long atomic_increment64(long long * pi)
{


#if defined(RASPBERRYPIOS) && defined(OS32BIT)
  
  return __sync_add_and_fetch_4(pi, 1);
  
#else
  
  return __sync_add_and_fetch(pi, 1);
  
#endif
  
}


#endif


#ifdef WINDOWS

#define atomic_assign32(pi, i) _InterlockedExchange((long *)(pi), i)

#else
   
inline int atomic_assign32(int* pi, int i)
{

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

   return __sync_lock_test_and_set_4(pi, i);

#else

   return __sync_lock_test_and_set(pi, i);

#endif

}

#endif


#ifdef WINDOWS

#define atomic_increment32(pi) _InterlockedIncrement((long *)(pi))

#else
   
inline int atomic_increment32(int* pi)
{

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, 1);

#endif

}

#endif



#ifdef WINDOWS

   #define atomic_decrement64(pi) _interlockeddecrement64((long long *)(pi))
  
#else
   
   inline long long atomic_decrement64(long long * pi)
   {
   
#if defined(RASPBERRYPIOS) && defined(OS32BIT)
  
      return __sync_sub_and_fetch_4(pi, 1);
  
#else
  
      return __sync_sub_and_fetch(pi, 1);
  
#endif
  
   }

#endif


#ifdef WINDOWS

   #define atomic_decrement32(pi) _InterlockedDecrement((long*)(pi))

#else
   
   inline int atomic_decrement32(int * pi)
   {

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(pi, 1);

#else

      return __sync_sub_and_fetch(pi, 1);

#endif

   }

#endif



#ifdef WINDOWS

   #define atomic_add64(pi, i) _interlockedadd64((long long *)(pi),(long long) (i))

#else
   
inline long long atomic_add64(long long* pi, long long i)
{

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

   #define atomic_add32(pi, i) _interlockedadd((long *)(pi),(long) (i))

#else

inline int atomic_add32(int* pi, int i)
{

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

#define atomic_subtract64(pi, i) _interlockedadd64((long long *)(pi), (long long) (-(i)))

#else
   
   inline long long atomic_subtract64(long long* pi, long long i)
   {

#if defined(RASPBERRYPIOS) && defined(OS32BIT)

   return __sync_sub_and_fetch_4(pi, 1);

#else

   return __sync_sub_and_fetch(pi, i);

#endif

   }

#endif



#ifdef WINDOWS

#define   atomic_subtract32(pi, i) _interlockedadd((long*)(pi), (long)(-(i)))

#else

inline int atomic_subtract32(int* pi, int i)
{

#if defined(RASPBERRYPIOS) && defined(OS32BIT)
   
   return __sync_sub_and_fetch_4(pi, 1);

#else

   return __sync_sub_and_fetch(pi, i);

#endif

}

#endif



