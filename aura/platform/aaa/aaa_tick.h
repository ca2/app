#pragma once

enum e_tick_now
{

   tick_now,

};

class duration;

class ::duration;

inline double __double(const ::duration & duration);

// ::durations
//
// get_first_tick()
// ::get_tick()
class CLASS_DECL_AURA ::duration
{
public:


   i64 m_i;


   ::duration() { m_i = 0; }
   ::duration(enum e_tick_now) { m_i = get_tick(); }
   ::duration(enum enum_no_init) {}
   ::duration(i64 i) { m_i = i; }
   ::duration(const ::duration & count) { m_i = count.m_i; }

   ::duration & operator = (const ::duration & duration) { m_i = ::duration.m_i; return *this; }

   inline static ::duration now() { return ::duration(::get_tick()); }

   inline bool timeout(const ::duration & tickTimeout)
   {

      ::duration tickNow = now();

      if(tickNow.m_i - m_i < tickTimeout.m_i)
      {

         return false;

      }

      m_i = tickNow.m_i;

      return true;

   }

   inline bool done(const ::duration & duration) const { return elapsed(::duration) >= 0; }
   inline bool done() const { return elapsed() >= 0; }


   inline ::duration elapsed(const ::duration & duration) const
   {

      return ::duration.m_i - m_i;

   }

   inline double sawtooth(const ::duration & tickPeriod)
   {

      return __double(elapsed() % tickPeriod) / __double(tickPeriod);

   }

   inline double period_rate(const ::duration & tickPeriod)
   {

      return __double(elapsed()) / __double(tickPeriod);

   }

   inline ::duration elapsed() const
   {

      return elapsed(now());

   }

   inline ::u32 u32() const
   {

      return (::u32) (m_i % 0x100000000ULL);

   }

   inline i64 seconds()const { return m_i / 1000; }

   inline void Now()
   {

      operator = (now());

   }

   inline bool on_off(const ::duration & period) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i >> 1;


   }


   inline bool on_off(const ::duration & period, double dRate) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i * dRate;


   }

   inline bool operator == (const ::duration& duration) const;
   inline bool operator != (const ::duration& duration) const;
   inline bool operator < (const ::duration& duration) const ;
   inline bool operator <= (const ::duration& duration) const;
   inline bool operator > (const ::duration& duration) const ;
   inline bool operator >= (const ::duration& duration) const;
   inline ::duration operator - (const ::duration& duration) const ;
   inline ::duration operator + (const ::duration& duration) const ;
   inline ::duration& operator -= (const ::duration& duration) ;
   inline ::duration& operator += (const ::duration& duration) ;


   inline bool operator == (const ::duration & duration) const { return m_i == ::duration.m_i; }
   inline bool operator != (const ::duration & duration) const { return m_i != ::duration.m_i; }
   inline bool operator < (const ::duration & duration) const { return m_i < ::duration.m_i; }
   inline bool operator <= (const ::duration & duration) const { return m_i <= ::duration.m_i; }
   inline bool operator > (const ::duration & duration) const { return m_i > ::duration.m_i; }
   inline bool operator >= (const ::duration & duration) const { return m_i >= ::duration.m_i; }
   inline ::duration operator - (const ::duration & duration) const { return m_i - ::duration.m_i; }
   inline ::duration operator + (const ::duration & duration) const { return m_i + ::duration.m_i; }
   inline ::duration& operator -= (const ::duration & duration) { m_i -= ::duration.m_i; return *this; }
   inline ::duration& operator += (const ::duration & duration) { m_i += ::duration.m_i; return *this; }


   inline bool operator == (i64 i) const { return m_i== i; }
   inline bool operator != (i64 i) const { return m_i != i; }
   inline bool operator < (i64 i) const { return m_i < i; }
   inline bool operator <= (i64 i) const{ return m_i <= i; }
   inline bool operator > (i64 i) const { return m_i > i; }
   inline bool operator >= (i64 i) const { return m_i >= i; }
   inline ::duration operator - (i64 i) const { return m_i - i; }
   inline ::duration operator + (i64 i) const { return m_i + i; }
   inline ::duration& operator -= (i64 i) { m_i -= i; return *this; }
   inline ::duration& operator += (i64 i) { m_i += i; return *this; }


   inline ::duration operator * (double d) const { return (i64)(m_i *d); }
   inline ::duration& operator *= (double d) { m_i = (i64)(m_i * d); return *this; }

   inline i64 operator / (const ::duration& ::duration) const { return m_i / ::duration.m_i; }
   inline ::duration operator / (i64 i) const { return m_i / i; }
   inline ::duration& operator /= (i64 i)  { m_i /= i; return *this; }
   inline ::duration& operator %= (const ::duration & duration) { m_i %= ::duration.m_i; return *this; }


   inline ::duration operator % (i32 i) const { return m_i % i; }
   inline ::duration operator % (i64 i) const { return m_i % i; }
   inline ::duration operator % (const ::duration & duration) const { return m_i % ::duration.m_i; }


};

inline ::duration operator * (double d, const ::duration & duration) { return (i64)(d * ::duration.m_i); }

namespace papaya
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value();

      template <  >
      inline u32 default_value < u32 >()
      {

         return 0;

      }

      template <  >
      inline ::duration default_value < ::duration > ()
      {
         // estimate a delay of half of maximum ::duration positive value
         return ::get_tick() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


#define PRtick PRId64

#define __prtick "%" PRtick " ms"

inline double __double(const ::duration & duration) { return (double) ::duration.m_i; }

inline auto __pr(const ::duration & duration) { return ::duration.m_i; }

inline u32 __os(const ::duration & duration) { return ::duration.m_i > (i64) MAXI32 ? U32_INFINITE_TIMEOUT : ::duration.m_i < 0 ? 0 : (u32) ::duration.m_i; }

inline ::i32 __i32(const ::duration & duration) { return (::i32) ::duration.m_i; }

inline ::i64 __i64(const ::duration & duration) { return (::i64) ::duration.m_i; }

inline byte __byte(const ::duration & duration) { return (byte) minimummax(::duration.m_i, 0, 255); }

inline ::duration __tick(double d) { return (::i64) d; }


inline ::duration operator "" _tick(unsigned long long int u) { return u; }



typedef CLASS_DECL_AURA numeric_array < ::duration > musical_tick_array;
