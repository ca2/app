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


   long long       m_i;


   millis() { m_i = 0; }
   millis(enum enum_now);
   millis(enum no_initialize_t) {}
    
   template < prototype_integral INTEGRAL >
   millis(INTEGRAL i) { m_i = i; }
    
   millis(const secs & secs) { m_i = secs.m_i * 1'000; }
   millis(const millis & millis) { m_i = millis.m_i; }
   millis(const micros & micros);
   millis(const nanos & nanos);
   millis(const class time & time);

   millis & operator = (const millis & millis) { m_i = millis.m_i; return *this; }

   inline static millis now();

   inline static millis infinite() { return {-1}; }

   inline bool is_infinite() const { return m_i < 0; }

   inline bool is_infinity() const { return m_i < 0; }

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


   inline unsigned int unsigned int() const
   {

      return (unsigned int) (m_i % 0x100000000ULL);

   }

   inline long long seconds()const { return m_i / 1000; }

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


   //inline bool operator == (const ::millis & millis) const { return m_i == millis.m_i; }
   //inline bool operator != (const ::millis & millis) const { return m_i != millis.m_i; }
   //inline bool operator < (const ::millis & millis) const { return m_i < millis.m_i; }
   //inline bool operator <= (const ::millis & millis) const { return m_i <= millis.m_i; }
   //inline bool operator > (const ::millis & millis) const { return m_i > millis.m_i; }
   //inline bool operator >= (const ::millis & millis) const { return m_i >= millis.m_i; }
   //inline millis operator - (const ::millis & millis) const { return m_i - millis.m_i; }
   //inline millis operator + (const ::millis & millis) const { return m_i + millis.m_i; }
   inline millis& operator -= (const ::millis & millis) { m_i -= millis.m_i; return *this; }
   inline millis& operator += (const ::millis & millis) { m_i += millis.m_i; return *this; }


   //inline bool operator == (long long i) const { return m_i == i; }
   //inline bool operator != (long long i) const { return m_i != i; }
   //inline bool operator < (long long i) const { return m_i < i; }
   //inline bool operator <= (long long i) const{ return m_i <= i; }
   //inline bool operator > (long long i) const { return m_i > i; }
   //inline bool operator >= (long long i) const { return m_i >= i; }
   //inline millis operator - (long long i) const { return m_i - i; }
   //inline millis operator + (long long i) const { return m_i + i; }
   //inline millis& operator -= (long long i) { m_i -= i; return *this; }
   //inline millis& operator += (long long i) { m_i += i; return *this; }


   inline millis& operator *= (double d) { m_i = (long long)(m_i * d); return *this; }

   inline long long operator / (const millis& millis) const { return m_i / millis.m_i; }
   inline millis& operator /= (long long i)  { m_i /= i; return *this; }
   inline millis& operator %= (const millis & millis) { m_i %= millis.m_i; return *this; }


   inline millis operator % (int i) const { return m_i % i; }
   inline millis operator % (long long i) const { return m_i % i; }
   inline millis operator % (const ::millis & millis) const { return m_i % millis.m_i; }


   void sleep() const;


};


inline millis operator * (double d, const millis & millis) { return (long long)(d * millis.m_i); }


namespace acme
{


   namespace chill
   {


      template < typename TYPE >
      inline TYPE default_value();

      template <  >
      inline unsigned int default_value < unsigned int >()
      {

         return 0;

      }
      template <  >
      inline millis default_value < millis >();



   } // namespace chill


} // namespace acme


#define PRtick PRId64


#define __prtick "%" PRtick " ms"


#define U32_INFINITE_TIMEOUT ((unsigned int)0xffffffffu)


inline double __double(const ::millis & millis) { return (double) millis.m_i; }


inline auto __pr(const ::millis & millis) { return millis.m_i; }


inline unsigned int __os(const ::millis & millis)
{

   if (millis.m_i > (long long) I32_MAXIMUM)
   {

      return U32_INFINITE_TIMEOUT;

   }
   else if (millis.m_i < 0)
   {

      return 0;

   }
   else
   {

      return (unsigned int) millis.m_i;

   }

}

inline int __int(const ::millis & millis) { return (int) millis.m_i; }


inline long long __long_long(const ::millis & millis) { return (long long) millis.m_i; }


inline unsigned char as_byte(const ::millis & millis) { return (unsigned char) minimummax(millis.m_i, 0, 255); }


inline millis __tick(double d) { return (long long) d; }


inline millis operator""_tick(unsigned long long u) { return u; }


#ifdef CPP20


typedef CLASS_DECL_ACME numeric_array < millis > millis_array;


#endif


inline secs::secs(const millis & millis) { m_i = millis.m_i / 1'000; }


inline millis operator""_ms(unsigned long long u) { return (long long) u; }


inline millis operator -(const ::millis& millis1, const ::millis& millis2)
{

   return millis1.m_i - millis2.m_i;

}


inline millis operator +(const ::millis& millis1, const ::millis& millis2)
{

   return millis1.m_i + millis2.m_i;

}





template < prototype_number NUMBER >
inline millis operator *(const ::millis& millis, const NUMBER& number)
{

   return (long long)(millis.m_i * number);

}


template < prototype_number NUMBER >
inline millis operator /(const ::millis& millis, const NUMBER& number)
{

   return (long long) (millis.m_i / number);

}





inline long long _first_milli();
inline long long _get_millis();
inline double _millis() { return _get_nanos() / 1'000'000.0; }


inline ::millis first_milli() { return _first_milli(); }
inline ::millis get_millis() { return _get_millis(); }



