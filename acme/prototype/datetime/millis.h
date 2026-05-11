#pragma once


inline millis operator -(const ::millis& millis1, const ::millis& millis2);
inline millis operator +(const ::millis& millis1, const ::millis& millis2);

enum enum_now
{

   now_t{},

};


class time;


class millis;


inline double __double(const ::millis & millis);


// milliseconds
//
// get_first_tick()
// ::get_tick()
class CLASS_DECL_ACME millis
{
public:


   ::i64       m_i32;


   millis() { m_i32 = 0; }
   millis(enum enum_now);
   millis(enum no_initialize_t) {}
    
   template < prototype_integral INTEGRAL >
   millis(INTEGRAL i) { m_i32 = i; }
    
   millis(const secs & secs) { m_i32 = secs.m_i32 * 1'000; }
   millis(const millis & millis) { m_i32 = millis.m_i32; }
   millis(const micros & micros);
   millis(const nanos & nanos);
   millis(const class time & time);

   millis & operator = (const millis & millis) { m_i32 = millis.m_i32; return *this; }

   inline static millis now();

   inline static millis infinite() { return {-1}; }

   inline bool is_infinite() const { return m_i32 < 0; }

   inline bool is_infinity() const { return m_i32 < 0; }

   inline bool timeout(const millis& tickTimeout);

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

      return millis.m_i32 - m_i32;

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


   inline ::u32 ::u32() const
   {

      return (::u32) (m_i32 % 0x100000000ULL);

   }

   inline ::i64 seconds()const { return m_i32 / 1000; }

   inline void Now()
   {

      operator = (now());

   }


   inline void Null()
   {

      m_i32 = 0;

   }


   inline bool on_off(const ::millis & period) const
   {

      return (elapsed().m_i32 % period.m_i32) < period.m_i32 >> 1;


   }


   inline bool on_off(const ::millis & period, double dRate) const
   {

      return (elapsed().m_i32 % period.m_i32) < period.m_i32 * dRate;


   }

   //inline bool operator == (const class ::time& time) const;
   //inline bool operator != (const class ::time& time) const;
   //inline bool operator < (const class ::time& time) const ;
   //inline bool operator <= (const class ::time& time) const;
   //inline bool operator > (const class ::time& time) const ;
   //inline bool operator >= (const class ::time& time) const;
   //inline millis operator - (const class ::time& time) const ;
   //inline millis operator + (const class ::time& time) const ;
   //inline millis& operator -= (const class ::time& time) ;
   //inline millis& operator += (const class ::time& time) ;


   //inline bool operator == (const ::millis & millis) const { return m_i32 == millis.m_i32; }
   //inline bool operator != (const ::millis & millis) const { return m_i32 != millis.m_i32; }
   //inline bool operator < (const ::millis & millis) const { return m_i32 < millis.m_i32; }
   //inline bool operator <= (const ::millis & millis) const { return m_i32 <= millis.m_i32; }
   //inline bool operator > (const ::millis & millis) const { return m_i32 > millis.m_i32; }
   //inline bool operator >= (const ::millis & millis) const { return m_i32 >= millis.m_i32; }
   //inline millis operator - (const ::millis & millis) const { return m_i32 - millis.m_i32; }
   //inline millis operator + (const ::millis & millis) const { return m_i32 + millis.m_i32; }
   inline millis& operator -= (const ::millis & millis) { m_i32 -= millis.m_i32; return *this; }
   inline millis& operator += (const ::millis & millis) { m_i32 += millis.m_i32; return *this; }


   //inline bool operator == (::i64 i) const { return m_i32 == i; }
   //inline bool operator != (::i64 i) const { return m_i32 != i; }
   //inline bool operator < (::i64 i) const { return m_i32 < i; }
   //inline bool operator <= (::i64 i) const{ return m_i32 <= i; }
   //inline bool operator > (::i64 i) const { return m_i32 > i; }
   //inline bool operator >= (::i64 i) const { return m_i32 >= i; }
   //inline millis operator - (::i64 i) const { return m_i32 - i; }
   //inline millis operator + (::i64 i) const { return m_i32 + i; }
   //inline millis& operator -= (::i64 i) { m_i32 -= i; return *this; }
   //inline millis& operator += (::i64 i) { m_i32 += i; return *this; }


   inline millis& operator *= (double d) { m_i32 = (::i64)(m_i32 * d); return *this; }

   inline ::i64 operator / (const millis& millis) const { return m_i32 / millis.m_i32; }
   inline millis& operator /= (::i64 i)  { m_i32 /= i; return *this; }
   inline millis& operator %= (const millis & millis) { m_i32 %= millis.m_i32; return *this; }


   inline millis operator % (int i) const { return m_i32 % i; }
   inline millis operator % (::i64 i) const { return m_i32 % i; }
   inline millis operator % (const ::millis & millis) const { return m_i32 % millis.m_i32; }


   void sleep() const;


};


inline millis operator * (double d, const millis & millis) { return (::i64)(d * millis.m_i32); }


namespace acme
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value();

      template <  >
      inline ::u32 default_value < ::u32 >()
      {

         return 0;

      }
      template <  >
      inline millis default_value < millis >();



   } // namespace chill


} // namespace acme


#define PRtick PRId64


#define __prtick "%" PRtick " ms"


#define U32_INFINITE_TIMEOUT ((::u32)0xffffffffu)


inline double __double(const ::millis & millis) { return (double) millis.m_i32; }


inline auto __pr(const ::millis & millis) { return millis.m_i32; }


inline ::u32 __os(const ::millis & millis)
{

   if (millis.m_i32 > (::i64) I32_MAXIMUM)
   {

      return U32_INFINITE_TIMEOUT;

   }
   else if (millis.m_i32 < 0)
   {

      return 0;

   }
   else
   {

      return (::u32) millis.m_i32;

   }

}

inline int __int(const ::millis & millis) { return (int) millis.m_i32; }


inline ::i64 __long_long(const ::millis & millis) { return (::i64) millis.m_i32; }


inline unsigned char as_byte(const ::millis & millis) { return (unsigned char) minimummax(millis.m_i32, 0, 255); }


inline millis __tick(double d) { return (::i64) d; }


inline millis operator""_tick(::u64 u) { return u; }


#ifdef CPP20


typedef CLASS_DECL_ACME numeric_array < millis > millis_array;


#endif


inline secs::secs(const millis & millis) { m_i32 = millis.m_i32 / 1'000; }


inline millis operator""_ms(::u64 u) { return (::i64) u; }


inline millis operator -(const ::millis& millis1, const ::millis& millis2)
{

   return millis1.m_i32 - millis2.m_i32;

}


inline millis operator +(const ::millis& millis1, const ::millis& millis2)
{

   return millis1.m_i32 + millis2.m_i32;

}





template < prototype_number NUMBER >
inline millis operator *(const ::millis& millis, const NUMBER& number)
{

   return (::i64)(millis.m_i32 * number);

}


template < prototype_number NUMBER >
inline millis operator /(const ::millis& millis, const NUMBER& number)
{

   return (::i64) (millis.m_i32 / number);

}





inline ::i64 _first_milli();
inline ::i64 _get_millis();
inline double _millis() { return _get_nanos() / 1'000'000.0; }


inline ::millis first_milli() { return _first_milli(); }
inline ::millis get_millis() { return _get_millis(); }



