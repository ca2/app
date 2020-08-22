//
//  atomic.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 02/06/19.
//


#pragma once


inline i64 atomic_increment(i64 * pi)
{
   
#ifdef WINDOWS
   
   return InterlockedIncrement64(pi);
   
#elif defined(RASPBIAN) && defined(OS32BIT)
   
   return __sync_add_and_fetch_4(pi, 1);
   
#else
   
   return __sync_add_and_fetch(pi, 1);
   
#endif
   
}


inline i32 atomic_increment(i32* pi)
{

#ifdef WINDOWS

   return InterlockedIncrement((unsigned int *) pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

   return __sync_add_and_fetch_4(pi, 1);

#else

   return __sync_add_and_fetch(pi, 1);

#endif

}

inline i64 atomic_decrement(i64 * pi)
{
   
#ifdef WINDOWS
   
   return InterlockedDecrement64(pi);
   
#elif defined(RASPBIAN) && defined(OS32BIT)
   
   return __sync_sub_and_fetch_4(pi, 1);
   
#else
   
   return __sync_sub_and_fetch(pi, 1);
   
#endif
   
}


inline i32 atomic_decrement(i32* pi)
{

#ifdef WINDOWS

   return InterlockedDecrement((unsigned int*)pi);

#elif defined(RASPBIAN) && defined(OS32BIT)

   return __sync_sub_and_fetch_4(pi, 1);

#else

   return __sync_sub_and_fetch(pi, 1);

#endif

}


