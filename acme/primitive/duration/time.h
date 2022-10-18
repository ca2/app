// Created by camilo on 2022-05-31 05:43 AM <3ThomasLikesNumber5 (really will he raise ca-square)
#pragma once


#ifdef time
#undef time
#endif


class CLASS_DECL_ACME time
{
public:


   double      m_d; // seconds


   constexpr time() {}
   constexpr time(enum_zero) : m_d(0.) {}
   constexpr time(double d) : m_d(d) {}
   time(const class ::time& time) : m_d(time.m_d) {}
   inline time(const class duration & duration);
   inline time(const ::INTEGRAL_NANOSECOND & integral);
   inline time(const ::FLOATING_NANOSECOND & floating);
   inline time(const ::INTEGRAL_MICROSECOND & integral);
   inline time(const ::FLOATING_MICROSECOND & floating);
   inline time(const ::INTEGRAL_MILLISECOND & integral);
   inline time(const ::FLOATING_MILLISECOND & floating);
   inline time(const ::INTEGRAL_SECOND & integral);
   inline time(const ::FLOATING_SECOND & floating);
   inline time(const ::INTEGRAL_MINUTE & integral);
   inline time(const ::FLOATING_MINUTE & floating);
   inline time(const ::INTEGRAL_HOUR & integral);
   inline time(const ::FLOATING_HOUR & floating);
   inline time(const ::INTEGRAL_DAY & integral);
   inline time(const ::FLOATING_DAY & floating);


   static class ::time now();

   inline class ::time elapsed(const class ::time& waitSample = now()) { return waitSample.m_d - m_d; }


   inline bool operator !() const { return m_d <= 0.; }


   DECLARE_COMPARISON_WITH_DURATION


   inline class ::time operator + (const class ::time & timeduration2) const { return m_d + timeduration2.m_d; }
   inline class ::time operator - (const class ::time & timeduration2) const { return m_d - timeduration2.m_d; }


   template < primitive_number NUMBER >
   inline class time operator / (const NUMBER & number)const{ return (double)(m_d / number); }
   template < primitive_number NUMBER >
   inline class time operator * (const NUMBER & number) const{ return (double)(m_d * number); }


   
};


CLASS_DECL_ACME void preempt(const class ::time& duration);



