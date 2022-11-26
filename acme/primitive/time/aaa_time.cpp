// Created by camilo on 2022-05-31 05:57 AM <3ThomasLikesNumber5 (really will he raise ca-square)
#include "framework.h"


class ::time time::now()
{

   struct timespec timespec;

   if (timespec_get(&timespec, TIME_UTC) != TIME_UTC)
   {

      throw "timespec_get failed!!";

   }

   return { timespec.tv_sec, timespec.tv_nsec };

}


CLASS_DECL_ACME void preempt(const class time& time)
{

   preempt((INTEGRAL_MILLISECOND)((::i64)(time.u32())));

}


DEFINE_COMPARISON_WITH_DURATION(NON_INLINE, time)



