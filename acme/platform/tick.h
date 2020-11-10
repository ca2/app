#pragma once

enum e_tick_now
{

   tick_now,

};

class duration;

class tick;

inline double __double(const ::tick & tick);

// milliseconds
//
// get_first_tick()
// ::get_tick()
class CLASS_DECL_ACME tick
{
public:


   i64 m_i;


   tick() { m_i = 0; }
   tick(enum e_tick_now) { m_i = get_tick(); }
   tick(enum e_no_init) {}
   tick(i64 i) { m_i = i; }
   tick(const tick & count) { m_i = count.m_i; }

   tick & operator = (const tick & tick) { m_i = tick.m_i; return *this; }

   inline static tick now() { return tick(::get_tick()); }

   inline bool timeout(const tick & tickTimeout)
   {

      ::tick tickNow = now();

      if(tickNow.m_i - m_i < tickTimeout.m_i)
      {

         return false;

      }

      m_i = tickNow.m_i;

      return true;

   }

   inline bool done(const ::tick & tick) const { return elapsed(tick) >= 0; }
   inline bool done() const { return elapsed() >= 0; }


   inline tick elapsed(const ::tick & tick) const
   {

      return tick.m_i - m_i;

   }

   inline double sawtooth(const ::tick & tickPeriod)
   {

      return __double(elapsed() % tickPeriod) / __double(tickPeriod);

   }

   inline double period_rate(const ::tick & tickPeriod)
   {

      return __double(elapsed()) / __double(tickPeriod);

   }

   inline tick elapsed() const
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

   inline bool on_off(const ::tick & period) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i >> 1;


   }


   inline bool on_off(const ::tick & period, double dRate) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i * dRate;


   }

   inline bool operator == (const ::duration& duration) const;
   inline bool operator != (const ::duration& duration) const;
   inline bool operator < (const ::duration& duration) const ;
   inline bool operator <= (const ::duration& duration) const;
   inline bool operator > (const ::duration& duration) const ;
   inline bool operator >= (const ::duration& duration) const;
   inline tick operator - (const ::duration& duration) const ;
   inline tick operator + (const ::duration& duration) const ;
   inline tick& operator -= (const ::duration& duration) ;
   inline tick& operator += (const ::duration& duration) ;


   inline bool operator == (const ::tick & tick) const { return m_i == tick.m_i; }
   inline bool operator != (const ::tick & tick) const { return m_i != tick.m_i; }
   inline bool operator < (const ::tick & tick) const { return m_i < tick.m_i; }
   inline bool operator <= (const ::tick & tick) const { return m_i <= tick.m_i; }
   inline bool operator > (const ::tick & tick) const { return m_i > tick.m_i; }
   inline bool operator >= (const ::tick & tick) const { return m_i >= tick.m_i; }
   inline tick operator - (const ::tick & tick) const { return m_i - tick.m_i; }
   inline tick operator + (const ::tick & tick) const { return m_i + tick.m_i; }
   inline tick& operator -= (const ::tick & tick) { m_i -= tick.m_i; return *this; }
   inline tick& operator += (const ::tick & tick) { m_i += tick.m_i; return *this; }


   inline bool operator == (i64 i) const { return m_i== i; }
   inline bool operator != (i64 i) const { return m_i != i; }
   inline bool operator < (i64 i) const { return m_i < i; }
   inline bool operator <= (i64 i) const{ return m_i <= i; }
   inline bool operator > (i64 i) const { return m_i > i; }
   inline bool operator >= (i64 i) const { return m_i >= i; }
   inline tick operator - (i64 i) const { return m_i - i; }
   inline tick operator + (i64 i) const { return m_i + i; }
   inline tick& operator -= (i64 i) { m_i -= i; return *this; }
   inline tick& operator += (i64 i) { m_i += i; return *this; }


   inline tick operator * (double d) const { return (i64)(m_i *d); }
   inline tick& operator *= (double d) { m_i = (i64)(m_i * d); return *this; }

   inline i64 operator / (const tick& tick) const { return m_i / tick.m_i; }
   inline tick operator / (i64 i) const { return m_i / i; }
   inline tick& operator /= (i64 i)  { m_i /= i; return *this; }
   inline tick& operator %= (const tick & tick) { m_i %= tick.m_i; return *this; }


   inline tick operator % (i32 i) const { return m_i % i; }
   inline tick operator % (i64 i) const { return m_i % i; }
   inline tick operator % (const ::tick & tick) const { return m_i % tick.m_i; }


};

inline tick operator * (double d, const tick & tick) { return (i64)(d * tick.m_i); }

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
      inline tick default_value < tick > ()
      {
         // estimate a delay of half of max tick positive value
         return ::get_tick() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


#define PRtick PRId64

#define __prtick "%" PRtick " ms"

inline double __double(const ::tick & tick) { return (double) tick.m_i; }

inline auto __pr(const ::tick & tick) { return tick.m_i; }

inline u32 __os(const ::tick & tick) { return tick.m_i > (i64) MAXI32 ? U32_INFINITE_TIMEOUT : tick.m_i < 0 ? 0 : (u32) tick.m_i; }

inline ::i32 __i32(const ::tick & tick) { return (::i32) tick.m_i; }

inline ::i64 __i64(const ::tick & tick) { return (::i64) tick.m_i; }

inline byte __byte(const ::tick & tick) { return (byte) __minmax(tick.m_i, 0, 255); }

inline tick __tick(double d) { return (::i64) d; }


inline tick operator "" _tick(unsigned long long int u) { return u; }



typedef CLASS_DECL_ACME numeric_array < tick > tick_array;
