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
class CLASS_DECL_ACME millis
{
public:


   i64 m_iMilliseconds;


   millis() { m_iMilliseconds = 0; }
   millis(enum e_tick_now) { m_iMilliseconds = get_tick(); }
   millis(enum e_no_init) {}
   millis(i32 i) { m_iMilliseconds = i; }
   millis(u32 u) { m_iMilliseconds = u; }
   millis(i64 i) { m_iMilliseconds = i; }
   millis(u64 u) { m_iMilliseconds = u; }
#if defined(LINUX)
   millis(unsigned long long int u) { m_iMilliseconds = u; }
#endif
   millis(const secs & secs) { m_iMilliseconds = secs.m_iSeconds * 1'000; }
   millis(const millis & millis) { m_iMilliseconds = millis.m_iMilliseconds; }
   millis(const micros & micros);
   millis(const nanos & nanos);
   millis(const duration & duration);

   millis & operator = (const millis & millis) { m_iMilliseconds = millis.m_iMilliseconds; return *this; }

   inline static millis now() { return millis(::get_tick()); }

   inline static millis infinite() { return {-1}; }

   inline bool is_infinite() const { return m_iMilliseconds < 0; }

   inline bool is_infinity() const { return m_iMilliseconds < 0; }

   inline bool timeout(const millis & tickTimeout)
   {

      ::millis tickNow = now();

      if(tickNow.m_iMilliseconds - m_iMilliseconds < tickTimeout.m_iMilliseconds)
      {

         return false;

      }

      m_iMilliseconds = tickNow.m_iMilliseconds;

      return true;

   }

   inline bool done(const ::millis & millis) const;
   inline bool done() const;


   inline millis elapsed(const ::millis & millis) const
   {

      return millis.m_iMilliseconds - m_iMilliseconds;

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

      return (::u32) (m_iMilliseconds % 0x100000000ULL);

   }

   inline i64 seconds()const { return m_iMilliseconds / 1000; }

   inline void Now()
   {

      operator = (now());

   }


   inline void Null()
   {

      m_iMilliseconds = 0;

   }


   inline bool on_off(const ::millis & period) const
   {

      return (elapsed().m_iMilliseconds % period.m_iMilliseconds) < period.m_iMilliseconds >> 1;


   }


   inline bool on_off(const ::millis & period, double dRate) const
   {

      return (elapsed().m_iMilliseconds % period.m_iMilliseconds) < period.m_iMilliseconds * dRate;


   }

   //inline bool operator == (const ::duration& duration) const;
   //inline bool operator != (const ::duration& duration) const;
   //inline bool operator < (const ::duration& duration) const ;
   //inline bool operator <= (const ::duration& duration) const;
   //inline bool operator > (const ::duration& duration) const ;
   //inline bool operator >= (const ::duration& duration) const;
   //inline millis operator - (const ::duration& duration) const ;
   //inline millis operator + (const ::duration& duration) const ;
   //inline millis& operator -= (const ::duration& duration) ;
   //inline millis& operator += (const ::duration& duration) ;


   //inline bool operator == (const ::millis & millis) const { return m_iMilliseconds == millis.m_iMilliseconds; }
   //inline bool operator != (const ::millis & millis) const { return m_iMilliseconds != millis.m_iMilliseconds; }
   //inline bool operator < (const ::millis & millis) const { return m_iMilliseconds < millis.m_iMilliseconds; }
   //inline bool operator <= (const ::millis & millis) const { return m_iMilliseconds <= millis.m_iMilliseconds; }
   //inline bool operator > (const ::millis & millis) const { return m_iMilliseconds > millis.m_iMilliseconds; }
   //inline bool operator >= (const ::millis & millis) const { return m_iMilliseconds >= millis.m_iMilliseconds; }
   inline millis operator - (const ::millis & millis) const { return m_iMilliseconds - millis.m_iMilliseconds; }
   inline millis operator + (const ::millis & millis) const { return m_iMilliseconds + millis.m_iMilliseconds; }
   inline millis& operator -= (const ::millis & millis) { m_iMilliseconds -= millis.m_iMilliseconds; return *this; }
   inline millis& operator += (const ::millis & millis) { m_iMilliseconds += millis.m_iMilliseconds; return *this; }


   //inline bool operator == (i64 i) const { return m_iMilliseconds == i; }
   //inline bool operator != (i64 i) const { return m_iMilliseconds != i; }
   //inline bool operator < (i64 i) const { return m_iMilliseconds < i; }
   //inline bool operator <= (i64 i) const{ return m_iMilliseconds <= i; }
   //inline bool operator > (i64 i) const { return m_iMilliseconds > i; }
   //inline bool operator >= (i64 i) const { return m_iMilliseconds >= i; }
   //inline millis operator - (i64 i) const { return m_iMilliseconds - i; }
   //inline millis operator + (i64 i) const { return m_iMilliseconds + i; }
   //inline millis& operator -= (i64 i) { m_iMilliseconds -= i; return *this; }
   //inline millis& operator += (i64 i) { m_iMilliseconds += i; return *this; }


   inline millis operator * (double d) const { return (i64)(m_iMilliseconds * d); }
   inline millis& operator *= (double d) { m_iMilliseconds = (i64)(m_iMilliseconds * d); return *this; }

   inline i64 operator / (const millis& millis) const { return m_iMilliseconds / millis.m_iMilliseconds; }
   inline millis operator / (i64 i) const { return m_iMilliseconds / i; }
   inline millis& operator /= (i64 i)  { m_iMilliseconds /= i; return *this; }
   inline millis& operator %= (const millis & millis) { m_iMilliseconds %= millis.m_iMilliseconds; return *this; }


   inline millis operator % (i32 i) const { return m_iMilliseconds % i; }
   inline millis operator % (i64 i) const { return m_iMilliseconds % i; }
   inline millis operator % (const ::millis & millis) const { return m_iMilliseconds % millis.m_iMilliseconds; }


};

inline millis operator * (double d, const millis & millis) { return (i64)(d * millis.m_iMilliseconds); }

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
         // estimate a delay of half of max millis positive value
         return ::get_tick() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


#define PRtick PRId64

#define __prtick "%" PRtick " ms"

inline double __double(const ::millis & millis) { return (double) millis.m_iMilliseconds; }

inline auto __pr(const ::millis & millis) { return millis.m_iMilliseconds; }

inline u32 __os(const ::millis & millis) { return millis.m_iMilliseconds > (i64) MAXI32 ? U32_INFINITE_TIMEOUT : millis.m_iMilliseconds < 0 ? 0 : (u32) millis.m_iMilliseconds; }

inline ::i32 __i32(const ::millis & millis) { return (::i32) millis.m_iMilliseconds; }

inline ::i64 __i64(const ::millis & millis) { return (::i64) millis.m_iMilliseconds; }

inline byte __byte(const ::millis & millis) { return (byte) __minmax(millis.m_iMilliseconds, 0, 255); }

inline millis __tick(double d) { return (::i64) d; }


inline millis operator "" _tick(unsigned long long int u) { return u; }



typedef CLASS_DECL_ACME numeric_array < millis > tick_array;


inline secs::secs(const millis & millis) { m_iSeconds = millis.m_iMilliseconds / 1'000; }


inline millis operator "" _ms(unsigned long long int u) { return (::i64) u; }



