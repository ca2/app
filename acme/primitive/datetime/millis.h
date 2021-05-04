#pragma once


inline millis operator -(const ::millis& millis1, const ::millis& millis2);

enum enum_now
{

   e_now,

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


   ::i64       m_i;


   millis() { m_i = 0; }
   millis(enum enum_now) { m_i = get_millis(); }
   millis(enum enum_no_initialize) {}
   template < primitive_integral INTEGRAL >
   millis(INTEGRAL i) { m_i = i; }
   millis(const secs & secs) { m_i = secs.m_i * 1'000; }
   millis(const millis & millis) { m_i = millis.m_i; }
   millis(const micros & micros);
   millis(const nanos & nanos);
   millis(const duration & duration);

   millis & operator = (const millis & millis) { m_i = millis.m_i; return *this; }

   inline static millis now() { return get_millis(); }

   inline static millis infinite() { return {-1}; }

   inline bool is_infinite() const { return m_i < 0; }

   inline bool is_infinity() const { return m_i < 0; }

   inline bool timeout(const millis & tickTimeout)
   {

      auto millisNow = get_millis();

      if(millisNow - m_i < tickTimeout.m_i)
      {

         return false;

      }

      m_i = millisNow;

      return true;

   }

   inline ::millis remaining(const millis & millisTimeout)
   {

      auto millisNow = now();

      auto millisRemaining = millisTimeout - millisNow + *this;

      return millisRemaining;

   }


   inline bool done(const ::millis & millis) const;
   inline bool done() const;


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


   inline void Null()
   {

      m_i = 0;

   }


   inline bool on_off(const ::millis & period) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i >> 1;


   }


   inline bool on_off(const ::millis & period, double dRate) const
   {

      return (elapsed().m_i % period.m_i) < period.m_i * dRate;


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


   //inline bool operator == (const ::millis & millis) const { return m_i == millis.m_i; }
   //inline bool operator != (const ::millis & millis) const { return m_i != millis.m_i; }
   //inline bool operator < (const ::millis & millis) const { return m_i < millis.m_i; }
   //inline bool operator <= (const ::millis & millis) const { return m_i <= millis.m_i; }
   //inline bool operator > (const ::millis & millis) const { return m_i > millis.m_i; }
   //inline bool operator >= (const ::millis & millis) const { return m_i >= millis.m_i; }
   //inline millis operator - (const ::millis & millis) const { return m_i - millis.m_i; }
   inline millis operator + (const ::millis & millis) const { return m_i + millis.m_i; }
   inline millis& operator -= (const ::millis & millis) { m_i -= millis.m_i; return *this; }
   inline millis& operator += (const ::millis & millis) { m_i += millis.m_i; return *this; }


   //inline bool operator == (i64 i) const { return m_i == i; }
   //inline bool operator != (i64 i) const { return m_i != i; }
   //inline bool operator < (i64 i) const { return m_i < i; }
   //inline bool operator <= (i64 i) const{ return m_i <= i; }
   //inline bool operator > (i64 i) const { return m_i > i; }
   //inline bool operator >= (i64 i) const { return m_i >= i; }
   //inline millis operator - (i64 i) const { return m_i - i; }
   //inline millis operator + (i64 i) const { return m_i + i; }
   //inline millis& operator -= (i64 i) { m_i -= i; return *this; }
   //inline millis& operator += (i64 i) { m_i += i; return *this; }


   inline millis operator * (double d) const { return (::i64)(m_i * d); }
   inline millis& operator *= (double d) { m_i = (::i64)(m_i * d); return *this; }

   inline ::i64 operator / (const millis& millis) const { return m_i / millis.m_i; }
   inline millis& operator /= (::i64 i)  { m_i /= i; return *this; }
   inline millis& operator %= (const millis & millis) { m_i %= millis.m_i; return *this; }


   inline millis operator % (::i32 i) const { return m_i % i; }
   inline millis operator % (::i64 i) const { return m_i % i; }
   inline millis operator % (const ::millis & millis) const { return m_i % millis.m_i; }


   void sleep() const;


};


inline millis operator * (double d, const millis & millis) { return (::i64)(d * millis.m_i); }


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
         return ::get_millis() - (MAXI64 >> 1);

      }


   } // namespace chill


} // namespace papaya


#define PRtick PRId64


#define __prtick "%" PRtick " ms"


#define U32_INFINITE_TIMEOUT ((u32)0xffffffffu)


inline double __double(const ::millis & millis) { return (double) millis.m_i; }


inline auto __pr(const ::millis & millis) { return millis.m_i; }


inline u32 __os(const ::millis & millis)
{

   if (millis.m_i > (i64) MAXI32)
   {

      return U32_INFINITE_TIMEOUT;

   }
   else if (millis.m_i < 0)
   {

      return 0;

   }
   else
   {

      return (u32) millis.m_i;

   }

}

inline ::i32 __i32(const ::millis & millis) { return (::i32) millis.m_i; }


inline ::i64 __i64(const ::millis & millis) { return (::i64) millis.m_i; }


inline byte __byte(const ::millis & millis) { return (byte) minimummax(millis.m_i, 0, 255); }


inline millis __tick(double d) { return (::i64) d; }


inline millis operator "" _tick(unsigned long long int u) { return u; }


typedef CLASS_DECL_ACME numeric_array < millis > tick_array;


inline secs::secs(const millis & millis) { m_i = millis.m_i / 1'000; }


inline millis operator "" _ms(unsigned long long int u) { return (::i64) u; }


inline millis operator -(const ::millis& millis1, const ::millis& millis2)
{

   return millis1.m_i - millis2.m_i;

}


template < primitive_integral INTEGRAL >
inline millis operator /(const ::millis& millis, const INTEGRAL& integral)
{

   return millis.m_i / integral;

}





