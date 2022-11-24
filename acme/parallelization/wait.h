// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/primitive/duration/time.h"


#ifdef wait
#undef wait
#endif // wait


class CLASS_DECL_ACME wait :
   public time
{
public:


   wait(enum_no_initialize) {}
   constexpr wait():time() {}
   constexpr wait(::i64 iSecond, ::i64 iNanosecond) : time(iSecond, iNanosecond) {}
   wait(double dWait): time(dWait) {}
   wait(const class time& timeWait) : time(timeWait) {}
   wait(const class wait& waitTime) : time(waitTime) {}
   using time::time;

   static inline ::wait infinite() { return {infinite_milliseconds().m_i, 0}; }

   static inline INTEGRAL_MILLISECOND infinite_milliseconds() { return numeric_info<::u32>::maximum(); }


   constexpr bool is_infinite() const { return m_iSecond >= numeric_info<::u32>::maximum(); }

   inline bool is_null() const { return m_iSecond <= 0; }


   //DECLARE_COMPARISON_WITH_DURATION




};



