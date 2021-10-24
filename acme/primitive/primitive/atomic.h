//
//  atomic.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//
#pragma once


#ifdef WINDOWS

// To declare an interlocked function for use as an intrinsic,
// include intrin.h and put the function in a #pragma intrinsic
// statement.
#include <intrin.h>


#pragma intrinsic (_InterlockedIncrement)
#pragma intrinsic (_InterlockedDecrement)


#endif


inline i64 atomic_increment(i64 * pi)
{
  
#ifdef WINDOWS
  
  return _interlockedincrement64(pi);
  
#elif defined(RASPBIAN) && defined(OS32BIT)
  
  return __sync_add_and_fetch_4(pi, 1);
  
#else
  
  return __sync_add_and_fetch(pi, 1);
  
#endif
  
}


inline i32 atomic_increment(i32* pi)
{

#ifdef WINDOWS

  return _InterlockedIncrement((long *) pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

  return __sync_add_and_fetch_4(pi, 1);

#else

  return __sync_add_and_fetch(pi, 1);

#endif

}


inline i64 atomic_decrement(i64 * pi)
{
  
#ifdef WINDOWS
  
  return _interlockeddecrement64(pi);
  
#elif defined(RASPBIAN) && defined(OS32BIT)
  
  return __sync_sub_and_fetch_4(pi, 1);
  
#else
  
  return __sync_sub_and_fetch(pi, 1);
  
#endif
  
}


inline i32 atomic_decrement(i32* pi)
{

#ifdef WINDOWS

  return _InterlockedDecrement((long*)pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

  return __sync_sub_and_fetch_4(pi, 1);

#else

  return __sync_sub_and_fetch(pi, 1);

#endif

}



