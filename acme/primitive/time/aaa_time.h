// Created by camilo on 2022-05-31 05:43 AM <3ThomasLikesNumber5 (really will he raise ca-square)
#pragma once


#ifdef time
#undef time
#endif

// time : Duration "with-no-templates"

class CLASS_DECL_ACME time :
   public DURATION
{
public:


   //double      m_d; // seconds


   constexpr time(enum_no_initialize) {}
   constexpr time():time(0, 0) {}
   constexpr time(::i64 iSecond, ::i64 iNanosecond)  {m_iSecond = iSecond; m_iNanosecond = iNanosecond; normalize();}
   constexpr time(enum_zero)  :time(0, 0) {}
   time(double d) {m_iSecond = (::i64)d; m_iNanosecond = (::i64) ((d - floor(d)) * 1'000'000'000.0); normalize();}
   constexpr time(const class ::time& time)  {m_iSecond = time.m_iSecond; m_iNanosecond = time.m_iNanosecond;}
   constexpr time(const struct ::timespec& timespec)  {m_iSecond = timespec.tv_sec; m_iNanosecond = timespec.tv_nsec; normalize(); }
   inline time(const class duration & duration);
   inline time(const ::integral_nanosecond & integral);
   inline time(const ::floating_nanosecond & floating);
   inline time(const ::integral_microsecond & integral);
   inline time(const ::floating_microsecond & floating);
   inline time(const ::integral_millisecond & integral);
   inline time(const ::floating_millisecond & floating);
   inline time(const ::integral_second & integral);
   inline time(const ::floating_second & floating);
   inline time(const ::integral_minute & integral);
   inline time(const ::floating_minute & floating);
   inline time(const ::integral_hour & integral);
   inline time(const ::floating_hour & floating);
   inline time(const ::integral_day & integral);
   inline time(const ::floating_day & floating);


   static class ::time now();

   inline class ::time elapsed(const class ::time& waitSample = now()) { return waitSample - *this; }


   constexpr class ::time &operator =(const struct ::timespec & timespec)
   {

      m_iSecond = timespec.tv_sec;
      m_iNanosecond = timespec.tv_nsec;

      return *this;

   }

   constexpr class ::time & normalize()
   {

      normalize_second_nanosecond(m_iSecond, m_iNanosecond);

      return *this;

   }


   constexpr time & operator += (const time & time)
   {

      add_second_nanosecond(m_iSecond, m_iNanosecond, time.m_iSecond, time.m_iNanosecond);

      return *this;

   }


   constexpr time &  operator -= (const time & time)
   {

      subtract_second_nanosecond(m_iSecond, m_iNanosecond, time.m_iSecond, time.m_iNanosecond);

      return *this;

   }


   constexpr class ::time operator + (const time & time) const
   {

      class ::time timeResult(*this);

      timeResult += time;

      return timeResult;

   }


   constexpr class ::time operator - (const time & time) const
   {

      class ::time timeResult(*this);

      timeResult -= time;

      return timeResult;
   }

   inline bool operator !() const { return m_iSecond != 0 && m_iNanosecond != 0; }


   constexpr integral_millisecond integral_milliseconds() const { return m_iSecond * 1'000 + m_iNanosecond / 1'000'000;}


   constexpr ::u32 u32() const { return constrain_u32(integral_milliseconds().m_i); }

   constexpr operator ::u32() const { return this->u32(); }



   DECLARE_COMPARISON_WITH_DURATION(NON_INLINE)


   template < primitive_number NUMBER >
   inline class time operator / (const NUMBER & number)const{ return time(m_iSecond / number, m_iNanosecond / number); }
   template < primitive_number NUMBER >
   inline class time operator * (const NUMBER & number) const{ return time(m_iSecond * number, m_iNanosecond * number); }


   
};


CLASS_DECL_ACME void preempt(const class ::time& duration);



