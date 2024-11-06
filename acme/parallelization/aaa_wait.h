// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/prototype/time/time.h"


#ifdef wait
#undef wait
#endif // wait


struct WAIT
{

   huge_integer m_iNanosecond;

};


class CLASS_DECL_ACME wait :
   public WAIT
{
public:


   wait(no_initialize_t) {}
   constexpr wait() {}
   constexpr wait(huge_integer iNanosecond) { m_iNanosecond = iNanosecond; }
   constexpr wait(huge_integer iSecond, huge_integer iNanosecond): wait(iNanosecond + iSecond * 1'000'000'000) { }
   wait(double dWait): wait((huge_integer) (dWait * 1'000'000'000.0)) {}
   wait(const struct TIME& time) : wait(time.m_iSecond, time.m_iNanosecond) {}
   wait(const class wait& wait) : wait(wait.m_iNanosecond) {}

   static inline ::wait infinite() { return {infinite_milliseconds().m_i, 0}; }

   static inline integral_millisecond infinite_milliseconds() { return numeric_info<unsigned int>::maximum(); }

   constexpr WAIT infinite_nanoseconds() { return { numeric_info<unsigned int>::maximum() * 1'000'000'000 }; }

   constexpr bool is_infinite() { return m_iNanosecond >= infinite_nanoseconds().m_iNanosecond; }

   constexpr bool is_null() const { return m_iNanosecond <= 0; }


};



