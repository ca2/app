#pragma once

enum e_tick_now
{

   tick_now,

};

class duration;

class millis;

inline double __double(const ::millis & millis);

// milliseconds
//
// get_first_tick()
// ::get_tick()
class CLASS_DECL_AURA millis
{
public:


   i64 m_i;


   millis() { m_i = 0; }
   millis(enum e_tick_now) { m_i = get_tick(); }
   millis(enum enum_no_init) {}
   millis(i64 i) { m_i = i; }
   millis(const millis & count) { m_i = count.m_i; }

   millis & operator = (const millis & millis) { m_i = millis.m_i; return *this; }

   inline static millis now() { return millis(::get_tick()); }

   inline bool timeout(const millis & tickTimeout)
   {

      ::millis tickNow = now();

      if(tickNow.m_i - m_i < tickTimeout.m_i)
      {

         return false;

      }

      m_i = tickNow.m_i;

      return true;

   }

   inline bool done(const ::millis & millis) const { return elapsed(millis) >= 0; }
   inline bool done() const { return elapsed() >= 0; }


   inline millis elapsed(const ::millis & millis) const
   {

      return millis.m_i - m_i;

   }

   inline double sawtooth(const ::millis & tickPeriod)
   {

      return __double(elapsed() % tickPeriod) / __double(tickPeriod);

   }

   inline double period_rate(const ::millis & tickPeriod)
   {

      return __double(elapsed()) / __double(tickPeriod);

   }

   inline millis elapsed() const
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

   inline bool on_off(const ::millis & period) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i >> 1;


   }


   inline bool on_off(const ::millis & period, double dRate) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i * dRate;


   }

   inline bool operator == (const ::duration& duration) const;
   inline bool operator != (const ::duration& duration) const;
   inline bool operator < (const ::duration& duration) const ;
   inline bool operator <= (const ::duration& duration) const;
   inline bool operator > (const ::duration& duration) const ;
   inline bool operator >= (const ::duration& duration) const;
   inline millis operator - (const ::duration& duration) const ;
   inline millis operator + (const ::duration& duration) const ;
   inline millis& operator -= (const ::duration& duration) ;
   inline millis& operator += (const ::duration& duration) ;


   inline bool operator == (const ::millis & millis) const { return m_i == millis.m_i; }
   inline bool operator != (const ::millis & millis) const { return m_i != millis.m_i; }
   inline bool operator < (const ::millis & millis) const { return m_i < millis.m_i; }
   inline bool operator <= (const ::millis & millis) const { return m_i <= millis.m_i; }
   inline bool operator > (const ::millis & millis) const { return m_i > millis.m_i; }
   inline bool operator >= (const ::millis & millis) const { return m_i >= millis.m_i; }
   inline millis operator - (const ::millis & millis) const { return m_i - millis.m_i; }
   inline millis operator + (const ::millis & millis) const { return m_i + millis.m_i; }
   inline millis& operator -= (const ::millis & millis) { m_i -= millis.m_i; return *this; }
   inline millis& operator += (const ::millis & millis) { m_i += millis.m_i; return *this; }


   inline bool operator == (i64 i) const { return m_i== i; }
   inline bool operator != (i64 i) const { return m_i != i; }
   inline bool operator < (i64 i) const { return m_i < i; }
   inline bool operator <= (i64 i) const{ return m_i <= i; }
   inline bool operator > (i64 i) const { return m_i > i; }
   inline bool operator >= (i64 i) const { return m_i >= i; }
   inline millis operator - (i64 i) const { return m_i - i; }
   inline millis operator + (i64 i) const { return m_i + i; }
   inline millis& operator -= (i64 i) { m_i -= i; return *this; }
   inline millis& operator += (i64 i) { m_i += i; return *this; }


   inline millis operator * (double d) const { return (i64)(m_i *d); }
   inline millis& operator *= (double d) { m_i = (i64)(m_i * d); return *this; }

   inline i64 operator / (const millis& millis) const { return m_i / millis.m_i; }
   inline millis operator / (i64 i) const { return m_i / i; }
   inline millis& operator /= (i64 i)  { m_i /= i; return *this; }
   inline millis& operator %= (const millis & millis) { m_i %= millis.m_i; return *this; }


   inline millis operator % (i32 i) const { return m_i % i; }
   inline millis operator % (i64 i) const { return m_i % i; }
   inline millis operator % (const ::millis & millis) const { return m_i % millis.m_i; }


};

inline millis operator * (double d, const millis & millis) { return (i64)(d * millis.m_i); }

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
      inline millis default_value < millis > ()
      {
         // estimate a delay of half of maximum millis positive value
         return ::get_tick() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


#define PRtick PRId64

#define __prtick "%" PRtick " ms"

inline double __double(const ::millis & millis) { return (double) millis.m_i; }

inline auto __pr(const ::millis & millis) { return millis.m_i; }

inline u32 __os(const ::millis & millis) { return millis.m_i > (i64) MAXI32 ? U32_INFINITE_TIMEOUT : millis.m_i < 0 ? 0 : (u32) millis.m_i; }

inline ::i32 __i32(const ::millis & millis) { return (::i32) millis.m_i; }

inline ::i64 __i64(const ::millis & millis) { return (::i64) millis.m_i; }

inline byte __byte(const ::millis & millis) { return (byte) minimummax(millis.m_i, 0, 255); }

inline millis __tick(double d) { return (::i64) d; }


inline millis operator "" _tick(unsigned long long int u) { return u; }



typedef CLASS_DECL_AURA numeric_array < millis > tick_array;
