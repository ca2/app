// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSørensen!!
#pragma once


//#include "acme/primitive/time/time.h"


#ifdef wait
#undef wait
#endif // wait


struct WAIT
{

   ::i64 m_iNanosecond;

};


class CLASS_DECL_ACME wait :
   public WAIT
{
public:


   wait(enum_no_initialize) {}
   constexpr wait() {}
   constexpr wait(::i64 iNanosecond) { m_iNanosecond = iNanosecond; }
   constexpr wait(::i64 iSecond, ::i64 iNanosecond): wait(iNanosecond + iSecond * 1'000'000'000) { }
   wait(double dWait): wait((::i64) (dWait * 1'000'000'000.0)) {}
   wait(const struct TIME& time) : wait(time.m_iSecond, time.m_iNanosecond) {}
   wait(const class wait& wait) : wait(wait.m_iNanosecond) {}

   static inline ::wait infinite() { return {infinite_milliseconds().m_i, 0}; }

   static inline integral_millisecond infinite_milliseconds() { return numeric_info<::u32>::maximum(); }

   constexpr WAIT infinite_nanoseconds() { return { numeric_info<::u32>::maximum() * 1'000'000'000 }; }

   constexpr bool is_infinite() { return m_iNanosecond >= infinite_nanoseconds().m_iNanosecond; }

   constexpr bool is_null() const { return m_iNanosecond <= 0; }


};



